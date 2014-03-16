/*
 * Hocoslamfy, sound playback header
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

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <stdbool.h>

extern bool InitializeAudio();
extern void FinalizeAudio();
extern void StartBGM();
extern void StopBGM();
extern void PlaySFXFly();
extern void PlaySFXPass();
extern void PlaySFXCollision();
extern void PlaySFXHighScore();

#endif /* !defined(_AUDIO_H_) */
