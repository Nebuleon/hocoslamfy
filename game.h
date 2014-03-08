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

// The width and height of the player's frame image.
// Given in pixels.
#define PLAYER_FRAME_SIZE      32

// The width and height of the player's collision rectangles.
// Given in meters.
                                               //       _______
#define COLLISION_A_WIDTH      0.36f           //   ..--|  B  |--.. <- Bee
#define COLLISION_A_HEIGHT     0.18f           // .-____|_____|____-.
#define COLLISION_B_WIDTH      0.16f           // |  A  | A+B |  A  |
#define COLLISION_B_HEIGHT     0.32f           // -.____|_____|____.-
                                               //   --..|_____|..--

// The time between animation frames for the player's character when ascending
// or descending.
// Given in milliseconds.
#define ANIMATION_TIME  50

// The number of animation frames for the player's character when ascending or
// descending.
#define ANIMATION_FRAMES 2

// The time the player's character should blink each time it does.
// Given in milliseconds.
#define BLINK_TIME     200

// The minimum time there can be between two times the player's character is
// seen blinking. Given in milliseconds.
#define NONBLINK_TIME_MIN  800

// The maximum time there can be between two times the player's character is
// seen blinking. Given in milliseconds.
#define NONBLINK_TIME_MAX 5000

// The time the collision frame should be displayed upon death.
// Given in milliseconds.
#define COLLISION_TIME 200

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
	int   Frame;
};

enum PlayerStatus
{
	ALIVE,
	COLLIDED,
	DYING
};

extern void ToGame(void);

#endif /* !defined(_GAME_H_) */
