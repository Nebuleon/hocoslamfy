/*
 * Hocoslamfy, title screen code file
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

#include "SDL.h"

#include "main.h"
#include "init.h"
#include "game.h"
#include "title.h"
#include "text.h"
#include "SDL_image.h"

static int BGCounterA = 0;
static int BGCounterB = 0;
static int BGCounterC = 0;
static int BGCounterD = 0;
static int BGCounterE = 0;
static int CounterB = 0;
static int CounterC = 0;
static int CounterD = 0;
static int CounterE = 0;
static int BeeCounter = -60;

static bool WaitingForRelease = false;

void TitleScreenGatherInput(bool* Continue)
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
			case SDL_KEYDOWN:
				if (ev.key.keysym.sym == SDLK_LCTRL  /* GCW Zero: A */
				 || ev.key.keysym.sym == SDLK_RETURN /* GCW Zero: Start */)
					WaitingForRelease = true;
				else if (ev.key.keysym.sym == SDLK_LALT   /* GCW Zero: B */
				      || ev.key.keysym.sym == SDLK_ESCAPE /* GCW Zero: Select */)
				{
					*Continue = false;
					return;
				}
				break;
			case SDL_KEYUP:
				if (ev.key.keysym.sym == SDLK_LCTRL  /* GCW Zero: A */
				 || ev.key.keysym.sym == SDLK_RETURN /* GCW Zero: Start */)
				{
					WaitingForRelease = false;
					ToGame();
					return;
				}
				break;
			default:
				break;
		}
	}
}

void TitleScreenDoLogic(bool* Continue, bool* Error)
{
}

void TitleScreenOutputFrame()
{
	//Draw the background E.
	SDL_Rect BGRectE;
			BGRectE.x=BGCounterE;
			BGRectE.y=54;
			BGRectE.w=320;
			BGRectE.h=138;
	SDL_Rect BGRectEdst;
			BGRectEdst.x=0;
			BGRectEdst.y=54;
			BGRectEdst.w=320;
			BGRectEdst.h=138;
	if (CounterE < 4) {
		CounterE++;
	} else {
		CounterE = 0;
		if (BGCounterE < 160) {
			BGCounterE++;
		} else {
			BGCounterE = 0;
		}
	}
	SDL_BlitSurface(frames_bg, &BGRectE, Screen, &BGRectEdst);
	
	//Draw the background D.
	SDL_Rect BGRectD;
			BGRectD.x=BGCounterD;
			BGRectD.y=192;
			BGRectD.w=320;
			BGRectD.h=8;
	SDL_Rect BGRectDdst;
			BGRectDdst.x=0;
			BGRectDdst.y=192;
			BGRectDdst.w=320;
			BGRectDdst.h=8;
	if (CounterD < 3) {
		CounterD++;
	} else {
		CounterD = 0;
		if (BGCounterD < 160) {
			BGCounterD++;
		} else {
			BGCounterD = 0;
		}
	}
	SDL_BlitSurface(frames_bg, &BGRectD, Screen, &BGRectDdst);
	
	//Draw the background C.
	SDL_Rect BGRectC;
			BGRectC.x=BGCounterC;
			BGRectC.y=42;
			BGRectC.w=320;
			BGRectC.h=12;
	SDL_Rect BGRectCdst;
			BGRectCdst.x=0;
			BGRectCdst.y=42;
			BGRectCdst.w=320;
			BGRectCdst.h=12;
	SDL_Rect BGRectC2;
			BGRectC2.x=BGCounterC;
			BGRectC2.y=200;
			BGRectC2.w=320;
			BGRectC2.h=10;
	SDL_Rect BGRectC2dst;
			BGRectC2dst.x=0;
			BGRectC2dst.y=200;
			BGRectC2dst.w=320;
			BGRectC2dst.h=10;
	if (CounterC < 2) {
		CounterC++;
	} else {
		CounterC = 0;
		if (BGCounterC < 160) {
			BGCounterC++;
		} else {
			BGCounterC = 0;
		}
	}
	SDL_BlitSurface(frames_bg, &BGRectC, Screen, &BGRectCdst);
	SDL_BlitSurface(frames_bg, &BGRectC2, Screen, &BGRectC2dst);
	
	//Draw the background B.
	SDL_Rect BGRectB;
			BGRectB.x=BGCounterB;
			BGRectB.y=28;
			BGRectB.w=320;
			BGRectB.h=14;
	SDL_Rect BGRectBdst;
			BGRectBdst.x=0;
			BGRectBdst.y=28;
			BGRectBdst.w=320;
			BGRectBdst.h=14;
	SDL_Rect BGRectB2;
			BGRectB2.x=BGCounterB;
			BGRectB2.y=210;
			BGRectB2.w=320;
			BGRectB2.h=12;
	SDL_Rect BGRectB2dst;
			BGRectB2dst.x=0;
			BGRectB2dst.y=210;
			BGRectB2dst.w=320;
			BGRectB2dst.h=12;
	if (CounterB < 1) {
		CounterB++;
	} else {
		CounterB = 0;
		if (BGCounterB < 160) {
			BGCounterB++;
		} else {
			BGCounterB = 0;
		}
	}
	SDL_BlitSurface(frames_bg, &BGRectB, Screen, &BGRectBdst);
	SDL_BlitSurface(frames_bg, &BGRectB2, Screen, &BGRectB2dst);
	
	//Draw the background A.
	SDL_Rect BGRectA;
			BGRectA.x=BGCounterA;
			BGRectA.y=0;
			BGRectA.w=320;
			BGRectA.h=28;
	SDL_Rect BGRectAdst;
			BGRectAdst.x=0;
			BGRectAdst.y=0;
			BGRectAdst.w=320;
			BGRectAdst.h=28;
	SDL_Rect BGRectA2;
			BGRectA2.x=BGCounterA;
			BGRectA2.y=222;
			BGRectA2.w=320;
			BGRectA2.h=18;
	SDL_Rect BGRectA2dst;
			BGRectA2dst.x=0;
			BGRectA2dst.y=222;
			BGRectA2dst.w=320;
			BGRectA2dst.h=18;
	if (BGCounterA < 160) {
		BGCounterA++;
	} else {
		BGCounterA = 0;
	}
	SDL_BlitSurface(frames_bg, &BGRectA, Screen, &BGRectAdst);
	SDL_BlitSurface(frames_bg, &BGRectA2, Screen, &BGRectA2dst);
	
	// Draw the character.
	SDL_Rect PlayerPixels;
		PlayerPixels.x = -60;
		PlayerPixels.y = (SCREEN_HEIGHT - (126 * SCREEN_HEIGHT / FIELD_HEIGHT) -1);
		PlayerPixels.w = (int) (PLAYER_SIZE * SCREEN_HEIGHT / FIELD_HEIGHT) +2;
		PlayerPixels.h = (int) (PLAYER_SIZE * SCREEN_HEIGHT / FIELD_HEIGHT) +2;
	if (BeeCounter < 600) {
		PlayerPixels.x=BeeCounter;
		BeeCounter++;
	} else {
		PlayerPixels.x=-60;
		BeeCounter=-60;
	}
	SDL_Rect P1Rect;
			P1Rect.x=0;
			P1Rect.y=0;
			P1Rect.w=16;
			P1Rect.h=16;
	if (CounterB < 1) {
		P1Rect.x=16;
	} else {
		P1Rect.x=0;
	}
	SDL_BlitSurface(frames_player, &P1Rect, Screen, &PlayerPixels);

	if (SDL_MUSTLOCK(Screen))
		SDL_LockSurface(Screen);
	PrintStringOutline("Welcome to HOCOSLAMFY\n\nPress A or Start to play\nor B or Select to exit\n\nIn-game:\nA or B to rise\nStart to pause\nSelect to exit",
		SDL_MapRGB(Screen->format, 255, 255, 255),
		SDL_MapRGB(Screen->format, 0, 0, 0),
		Screen->pixels,
		Screen->pitch,
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		CENTER,
		MIDDLE);
	if (SDL_MUSTLOCK(Screen))
		SDL_UnlockSurface(Screen);

	SDL_Flip(Screen);
}

void ToTitleScreen(void)
{
	GatherInput = TitleScreenGatherInput;
	DoLogic     = TitleScreenDoLogic;
	OutputFrame = TitleScreenOutputFrame;
}
