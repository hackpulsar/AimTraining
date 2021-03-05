#pragma once

// Textures
#define CURSOR_FILEPATH "./Sprites/scope.png"
#define HEART_FILEPATH "./Sprites/heart.png"
#define TARGET_FILEPATH "./Sprites/target.png"

// Buttons textures
#define PLAY_BUTTON_FILEPATH "./Sprites/Buttons/play_button.png"
#define QUIT_BUTTON_FILEPATH "./Sprites/Buttons/quit_button.png"
#define MENU_BUTTON_FILEPATH "./Sprites/Buttons/menu_button.png"

// Fonts and sounds
#define BASIC_FONT_FILEPATH "./Fonts/Roboto-Thin.ttf"
#define POP_SOUND_FILEPATH "./Sounds/pop.wav"
#define HURT_SOUND_FILEPATH "./Sounds/hurt.wav"

// Timers
constexpr auto TIME_BEFORE_GAME_OVER_APEARS = 0.5f;

enum class GameStates
{
	Playing,
	GameOver
};

// Const variables
constexpr auto FLASH_SPEED = 1500.0f;