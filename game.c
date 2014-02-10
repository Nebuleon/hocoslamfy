/*
 * Hocoslamfy, game code file
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
#include <stdlib.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include "SDL.h"
#include "SDL_image.h"

#include "main.h"
#include "init.h"
#include "platform.h"
#include "game.h"
#include "score.h"
#include "bg.h"
#include "text.h"

static uint32_t               Score;

static bool                   Boost;
static bool                   Pause;

// Where the player is. (Upper-left corner, meters.)
static float                  PlayerX;
static float                  PlayerY;
// Where the player is going. (Meters per second.)
static float                  PlayerSpeed;
// Animation frame for the player when ascending.
static uint8_t                PlayerFrame;
// Time the player has had the current animation frame. (In milliseconds.)
static uint32_t               PlayerFrameTime;

// What the player avoids.
static struct HocoslamfyRect* Rectangles     = NULL;
static uint32_t               RectangleCount = 0;

static float                  GenDistance;

void GameGatherInput(bool* Continue)
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		if (IsBoostEvent(&ev))
			Boost = true;
		else if (IsPauseEvent(&ev))
			Pause = !Pause;
		else if (IsExitGameEvent(&ev))
		{
			*Continue = false;
			return;
		}
	}
}

static void AnimationControl(Uint32 Milliseconds)
{
	PlayerFrameTime = (PlayerFrameTime + Milliseconds) % (ANIMATION_TIME * ANIMATION_FRAMES);
	PlayerFrame = (PlayerFrame + (PlayerFrameTime / ANIMATION_TIME)) % ANIMATION_FRAMES;
}

void GameDoLogic(bool* Continue, bool* Error, Uint32 Milliseconds)
{
	if (!Pause)
	{
		bool PointAwarded = false;
		uint32_t Millisecond;
		for (Millisecond = 0; Millisecond < Milliseconds; Millisecond++)
		{
			// Scroll all rectangles to the left.
			int32_t i;
			for (i = RectangleCount - 1; i >= 0; i--)
			{
				Rectangles[i].Left += FIELD_SCROLL / 1000;
				Rectangles[i].Right += FIELD_SCROLL / 1000;
				// If a rectangle is past the player, award the player with a
				// point. But there is a pair of them per column!
				if (!Rectangles[i].Passed
				 && Rectangles[i].Right < PlayerX)
				{
					Rectangles[i].Passed = true;
					if (!PointAwarded)
					{
						Score++;
						PointAwarded = true;
					}
				}
				// If a rectangle is past the left side, remove it.
				if (Rectangles[i].Right < 0.0f)
				{
					memmove(&Rectangles[i], &Rectangles[i + 1], (RectangleCount - i) * sizeof(struct HocoslamfyRect));
					RectangleCount--;
				}
			}
			// Generate a pair of rectangles now if needed.
			if (RectangleCount == 0 || FIELD_WIDTH - Rectangles[RectangleCount - 1].Right >= GenDistance)
			{
				float Left;
				if (RectangleCount == 0)
					Left = FIELD_WIDTH + FIELD_SCROLL / 1000;
				else
				{
					Left = Rectangles[RectangleCount - 1].Right + GenDistance;
					GenDistance += RECT_GEN_SPEED;
				}
				Rectangles = realloc(Rectangles, (RectangleCount + 2) * sizeof(struct HocoslamfyRect));
				RectangleCount += 2;
				Rectangles[RectangleCount - 2].Passed = Rectangles[RectangleCount - 1].Passed = false;
				Rectangles[RectangleCount - 2].Left = Rectangles[RectangleCount - 1].Left = Left;
				Rectangles[RectangleCount - 2].Right = Rectangles[RectangleCount - 1].Right = Left + RECT_WIDTH;
				// Where's the place for the player to go through?
				float GapTop = GAP_HEIGHT + 1.0f + ((float) rand() / (float) RAND_MAX) * (FIELD_HEIGHT - GAP_HEIGHT - 2.0f);
				Rectangles[RectangleCount - 2].Top = FIELD_HEIGHT;
				Rectangles[RectangleCount - 2].Bottom = GapTop;
				Rectangles[RectangleCount - 1].Top = GapTop - GAP_HEIGHT;
				Rectangles[RectangleCount - 1].Bottom = 0.0f;
			}
			// Update the speed at which the player is going.
			PlayerSpeed += GRAVITY / 1000;
			if (Boost)
			{
				// The player expects to rise a constant amount with each press of
				// the triggering key or button, so set his or her speed to
				// boost him or her from zero, even if the speed was positive.
				// For a more physically-realistic version of thrust, use
				// [PlayerSpeed += SPEED_BOOST;].
				PlayerSpeed = SPEED_BOOST;
				Boost = false;
			}
			// Update the player's position.
			// If the player's position has collided with the borders of the field,
			// the player's game is over.
			PlayerY += PlayerSpeed / 1000;
			if (PlayerY > FIELD_HEIGHT || PlayerY - PLAYER_SIZE < 0.0f)
			{
				ToScore(Score, FIELD_BORDER_COLLISION);
				return;
			}
			// Collision detection.
			for (i = 0; i < RectangleCount; i++)
			{
				if (((PlayerY               > Rectangles[i].Bottom
				   && PlayerY               < Rectangles[i].Top)
				  || (PlayerY - PLAYER_SIZE > Rectangles[i].Bottom
				   && PlayerY - PLAYER_SIZE < Rectangles[i].Top))
				 && ((PlayerX               > Rectangles[i].Left
				   && PlayerX               < Rectangles[i].Right)
				  || (PlayerX + PLAYER_SIZE > Rectangles[i].Left
				   && PlayerX + PLAYER_SIZE < Rectangles[i].Right)))
				{
					ToScore(Score, RECTANGLE_COLLISION);
					return;
				}
			}
		}

		AdvanceBackground(Milliseconds);

		AnimationControl(Milliseconds);
	}
}

void GameOutputFrame()
{
	// Draw the background.
	DrawBackground();

	// Draw the rectangles.
	uint32_t i;
	for (i = 0; i < RectangleCount; i++)
	{
		SDL_Rect ColumnDestRect = {
			.x = (int) (Rectangles[i].Left * SCREEN_WIDTH / FIELD_WIDTH),
			.y = SCREEN_HEIGHT - (int) (Rectangles[i].Top * SCREEN_HEIGHT / FIELD_HEIGHT),
			.w = (int) ((Rectangles[i].Right - Rectangles[i].Left) * SCREEN_WIDTH / FIELD_WIDTH),
			.h = (int) ((Rectangles[i].Top - Rectangles[i].Bottom) * SCREEN_HEIGHT / FIELD_HEIGHT)
		};
		SDL_Rect ColumnSourceRect = { .x = 0, .y = 0, .w = ColumnDestRect.w, .h = ColumnDestRect.h };
		// Odd-numbered rectangle indices are at the bottom of the field,
		// so start their column image from the top.
		if (i & 1) {
			ColumnSourceRect.y = 0;
		} else {
			ColumnSourceRect.y = 240 - ColumnDestRect.h;
		}
		SDL_BlitSurface(ColumnImage, &ColumnSourceRect, Screen, &ColumnDestRect);
	}

	// Draw the character.
	SDL_Rect PlayerDestRect = {
		.x = (int) (PlayerX * SCREEN_WIDTH / FIELD_WIDTH),
		.y = (int) (SCREEN_HEIGHT - (PlayerY * SCREEN_HEIGHT / FIELD_HEIGHT)),
		.w = (int) (PLAYER_SIZE * SCREEN_HEIGHT / FIELD_HEIGHT),
		.h = (int) (PLAYER_SIZE * SCREEN_HEIGHT / FIELD_HEIGHT)
	};
	SDL_Rect PlayerSourceRect = {
		.x = 0,
		.y = 0,
		.w = 16,
		.h = 16
	};
	PlayerSourceRect.x = 16 * PlayerFrame;
	if ((PlayerSpeed < 0.0f) && (PlayerSpeed > -1.0f)) {
		PlayerSourceRect.x = 32;
	}
	else if (PlayerSpeed <= -1.0f) {
		PlayerSourceRect.x = 48;
	}
	SDL_BlitSurface(CharacterFrames, &PlayerSourceRect, Screen, &PlayerDestRect);

	// Draw the player's current score.
	char ScoreString[17];
	sprintf(ScoreString, "Score%10" PRIu32, Score);
	if (SDL_MUSTLOCK(Screen))
		SDL_LockSurface(Screen);
	PrintStringOutline(ScoreString,
		SDL_MapRGB(Screen->format, 255, 255, 255),
		SDL_MapRGB(Screen->format, 0, 0, 0),
		Screen->pixels,
		Screen->pitch,
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		RIGHT,
		TOP);
	if (SDL_MUSTLOCK(Screen))
		SDL_UnlockSurface(Screen);

	SDL_Flip(Screen);
}

void ToGame(void)
{
	Score = 0;
	Boost = false;
	Pause = false;
	PlayerX = FIELD_WIDTH / 8;
	PlayerY = (FIELD_HEIGHT - PLAYER_SIZE) / 2;
	PlayerSpeed = 0.0f;
	if (Rectangles != NULL)
	{
		free(Rectangles);
		Rectangles = NULL;
	}
	RectangleCount = 0;
	GenDistance = RECT_GEN_START;

	GatherInput = GameGatherInput;
	DoLogic     = GameDoLogic;
	OutputFrame = GameOutputFrame;
}
