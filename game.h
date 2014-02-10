/*
 * Hocoslamfy, game header
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

#ifndef _GAME_H_
#define _GAME_H_

// All speed and acceleration modifiers follow the same directions.
// Vertically: Positive values go upward, and negative values go downward.
// Horizontally: Positive values go rightward, and negative values go leftward.

// The vertical boost given to speed whenever a boost key or button is pressed.
// Given in meters per second (m/s).
#define SPEED_BOOST      3.41f

// The gravitational force exerted by the bottom of the screen.
// Given in (meters per second) per second (m/s^2).
#define GRAVITY         -9.78f /* like Earth */

// The speed at which the screen scrolls.
// Given in meters per second (m/s).
#define FIELD_SCROLL    -2.00f

// The distance between the edges of two successive rectangles to begin with.
// Given in meters.
#define RECT_GEN_START   2.00f

// The change in distance between the edges of two successive rectangles as
// the player passes through each of them.
// Given in meters (per rectangle).
#define RECT_GEN_SPEED  -0.01f

// The width of each rectangle.
// Given in meters.
#define RECT_WIDTH       0.42f

// The height of the area to leave empty for the player to pass through.
// Given in meters.
#define GAP_HEIGHT       1.33f

// The width and height of the player's character.
// Given in meters.
#define PLAYER_SIZE      0.26f

// The time between animation frames for the player's character when ascending.
// Given in milliseconds.
#define ANIMATION_TIME  50

// The number of animation frames for the player's character when ascending.
#define ANIMATION_FRAMES 2

// The height of the playing field.
// Given in meters.
#define FIELD_HEIGHT     4.00f

#define FIELD_WIDTH    (SCREEN_WIDTH * (FIELD_HEIGHT / SCREEN_HEIGHT))

struct HocoslamfyRect
{
	float Left;
	float Top;
	float Right;
	float Bottom;
	bool  Passed;
};

extern void ToGame(void);

#endif /* !defined(_GAME_H_) */
