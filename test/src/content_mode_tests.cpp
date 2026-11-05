#ifdef LANGUAGE_SELECT
#include "tonuino_fixture.hpp"

class content_mode_test_fixture : public tonuino_fixture {
public:
  content_mode_test_fixture() {
    getMFRC522().use_test_blocks = false;
    getMFRC522().card_sak = 0x08;
    getSettings().language = 0;
    card_out();
    goto_idle();
  }

  void language_button(bool longPress) {
    press_button(buttonLangPin);
    execute_cycle();
    if (longPress)
      execute_cycle_for_ms(buttonLongPress);
    release_button(buttonLangPin);
    execute_cycle();
  }

  void start_audio() {
    ASSERT_TRUE(SM_tonuino::is_in_state<StartPlay<Play>>());
    execute_cycle_for_ms(dfPlayer_timeUntilStarts);
    execute_cycle();
    ASSERT_TRUE(SM_tonuino::is_in_state<Play>());
    ASSERT_TRUE(getMp3().is_playing_folder());
  }

  void goto_play(const folderSettings &card, uint16_t trackCount = 99) {
    card_in(card, trackCount);
    start_audio();
    card_out();
  }

  void goto_admin() {
    button_for_command(command::admin, state_for_command::idle_pause);
    execute_cycle();
    execute_cycle();
    ASSERT_TRUE(SM_tonuino::is_in_state<Admin_Entry>());
  }
};

TEST_F(content_mode_test_fixture, toggles_in_idle_play_pause_but_not_admin) {
  EXPECT_FALSE(tonuino.isMusicMode());
  language_button(true);
  EXPECT_TRUE(tonuino.isMusicMode());
  EXPECT_EQ(getSettings().language, 0);
  language_button(true);
  EXPECT_FALSE(tonuino.isMusicMode());

  goto_play({1, pmode_t::album, 0, 0}, 3);
  language_button(true);
  EXPECT_TRUE(tonuino.isMusicMode());
  EXPECT_TRUE(SM_tonuino::is_in_state<Play>());
  EXPECT_EQ(tonuino.getFolder(), 1);
  EXPECT_EQ(getMp3().getCurrentFolder(), 1);
  EXPECT_EQ(getMp3().getCurrentTrack(), 1);
  button_for_command(command::pause, state_for_command::play);
  language_button(true);
  EXPECT_FALSE(tonuino.isMusicMode());
  EXPECT_TRUE(SM_tonuino::is_in_state<Pause>());
  EXPECT_EQ(getMp3().getCurrentFolder(), 1);
  EXPECT_EQ(getMp3().getCurrentTrack(), 1);
  button_for_command(command::pause, state_for_command::idle_pause);
  execute_cycle();
  getMp3().end_track();
  execute_cycle();
  goto_admin();
  language_button(true);
  EXPECT_FALSE(tonuino.isMusicMode());
  EXPECT_TRUE(SM_tonuino::is_in_state<Admin_Entry>());
}

TEST_F(content_mode_test_fixture, short_press_keeps_mode_and_long_press_keeps_language) {
  getSettings().language = 0;
  language_button(true);
  EXPECT_EQ(getSettings().language, 0);
  EXPECT_TRUE(tonuino.isMusicMode());
  language_button(false);
  EXPECT_EQ(getSettings().language, 1);
  EXPECT_TRUE(tonuino.isMusicMode());
  language_button(true);
  EXPECT_EQ(getSettings().language, 1);
  EXPECT_FALSE(tonuino.isMusicMode());
}

TEST_F(content_mode_test_fixture, folder_pairs_preserve_parameters_and_special_cards) {
  language_button(true);
  for (uint8_t base = 1; base <= 99; ++base) {
    folderSettings card{base, pmode_t::single_track, 3, 7};
    ASSERT_TRUE(tonuino.resolveContentFolder(card));
    EXPECT_EQ(card.folder, base == 50 ? 50 : base < 50 ? base + 50 : base - 50);
    EXPECT_EQ(card.mode, pmode_t::single_track);
    EXPECT_EQ(card.special, 3);
    EXPECT_EQ(card.special2, 7);
  }
  for (folderSettings card : {folderSettings{0, pmode_t::sleep_timer, 5, 0},
                             folderSettings{1, pmode_t::admin, 0, 0},
                             folderSettings{255, pmode_t::none, 0, 0}}) {
    auto original = card;
    EXPECT_TRUE(tonuino.resolveContentFolder(card));
    EXPECT_EQ(card, original);
  }
  folderSettings range{48, pmode_t::audiobook, 0, 2};
  EXPECT_FALSE(tonuino.resolveContentFolder(range));
  range = {50, pmode_t::audiobook, 0, 1};
  EXPECT_FALSE(tonuino.resolveContentFolder(range));
  range = {47, pmode_t::audiobook_single, 2, 2};
  EXPECT_TRUE(tonuino.resolveContentFolder(range));
  EXPECT_EQ(range.folder, 97);
  EXPECT_EQ(range.special2, 2);
}

TEST_F(content_mode_test_fixture, magic_cookie_same_card_switches_audio_without_rewriting) {
  const folderSettings card{1, pmode_t::single_track, 3, 0};
  card_in(card, 5);
  start_audio();
  EXPECT_EQ(getMp3().df_folder, 1);
  EXPECT_EQ(getMp3().df_folder_track, 3);
  language_button(true);
  card_out();
  getMp3().set_folder_track_count(51, 5);
  card_in(card, 5);
  start_audio();
  EXPECT_EQ(getMp3().df_folder, 51);
  EXPECT_EQ(getMp3().df_folder_track, 3);
  EXPECT_EQ(card_decode(), card);
  language_button(true);
  card_out();
  card_in(card, 5);
  start_audio();
  EXPECT_EQ(getMp3().df_folder, 1);
  EXPECT_EQ(getMp3().df_folder_track, 3);
}

TEST_F(content_mode_test_fixture, legacy_magic_cookie_language_offset_precedes_music_offset) {
  getSettings().language = 2;
  language_button(true);
  getMp3().set_folder_track_count(49, 5);
  card_in(cardCookie, 1, 97, 9, 3, 0, 5);
  start_audio();
  EXPECT_EQ(getMp3().df_folder, 49);
  EXPECT_EQ(getMp3().df_folder_track, 3);
}

TEST_F(content_mode_test_fixture, disney_fudan_mickey_and_ul_a_use_music_directories) {
  language_button(true);
  getMFRC522().use_test_blocks = true;
  for (uint8_t family = 0; family < 3; ++family) {
    for (uint8_t lang = 0; lang < numLanguages; ++lang) {
      if (SM_tonuino::is_in_state<Play>()) {
        Mp3Notify::ResetLastTrackFinished();
        getMp3().end_track();
        execute_cycle();
        execute_cycle();
      }
      card_out();
      getSettings().language = lang;
      auto &reader = getMFRC522();
      memset(reader.test_blocks, 0, sizeof(reader.test_blocks));
      for (auto &status : reader.test_block_status)
        status = MFRC522::STATUS_OK;
      reader.card_sak = family == 0 ? 0x0A : 0x00;
      reader.test_blocks[0][0] = 3;
      reader.test_blocks[2][0] = family == 2 ? 0x5F : 3;
      if (family == 1)
        reader.test_block_status[8] = MFRC522::STATUS_MIFARE_NACK;
      if (family == 2) {
        reader.test_blocks[0][12] = 0xE1;
        reader.test_blocks[0][13] = 0x10;
        reader.test_blocks[0][14] = 0x12;
        reader.test_block_status[4] = MFRC522::STATUS_MIFARE_NACK;
      }
      const uint8_t folder = family == 2 ? 46 : 47 + lang;
      getMp3().set_folder_track_count(folder, 5);
      card_in({97, pmode_t::single_track, 3, 0}, 5);
      start_audio();
      EXPECT_EQ(getMp3().df_folder, folder);
      EXPECT_EQ(getMp3().df_folder_track, 3);
    }
  }
}

TEST_F(content_mode_test_fixture, shortcuts_resolve_without_changing_saved_settings) {
  const folderSettings shortcut{2, pmode_t::single_track, 3, 0};
  getSettings().setShortCut(1, shortcut);
  getMp3().set_folder_track_count(52, 5);
  language_button(true);
  button_for_command(command::shortcut1, state_for_command::idle_pause);
  start_audio();
  EXPECT_EQ(getMp3().df_folder, 52);
  EXPECT_EQ(getMp3().df_folder_track, 3);
  EXPECT_EQ(getSettings().getShortCut(1), shortcut);
}

TEST_F(content_mode_test_fixture, restart_returns_to_stories) {
  language_button(true);
  EXPECT_TRUE(tonuino.isMusicMode());
  tonuino.setup();
  EXPECT_FALSE(tonuino.isMusicMode());
}
#endif
