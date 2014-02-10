/*
 * Hocoslamfy, platform-specific functions, header
 * Copyright (C) 2014 Nebuleon Fumika <nebuleon@gcw-zero.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <stdbool.h>
#include <stdint.h>

void InitializePlatform(void);

/*
 * Advances the game by a platform-appropriate time, and returns the number of
 * milliseconds that have been skipped over.
 */
Uint32 ToNextFrame(void);

// Is???Event returns true if the specified event is used to trigger the ???
// function.
//   EnterGamePressing: true if the event can be used to start a game from the
//     title and score screens.
//   EnterGameReleasing: true if the event releases buttons from the above.
//   ExitGame: true if the event can be used to exit the entire application.
//   Boost: true if the event can be used to boost the player's character.
//   Pause: true if the event can be used to pause a game in progress.

// Get???Prompt returns the text that can be used to describe the actions that
// can trigger a feature on the platform.

bool IsEnterGamePressingEvent(const SDL_Event* event);
bool IsEnterGameReleasingEvent(const SDL_Event* event);
const char* GetEnterGamePrompt(void);

bool IsExitGameEvent(const SDL_Event* event);
const char* GetExitGamePrompt(void);

bool IsBoostEvent(const SDL_Event* event);
const char* GetBoostPrompt(void);

bool IsPauseEvent(const SDL_Event* event);
const char* GetPausePrompt(void);
