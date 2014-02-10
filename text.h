/*
 * Hocoslamfy, text rendering header
 * Copyright (C) 2013 Nebuleon Fumika <nebuleon@gcw-zero.com>
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

#ifndef _TEXT_H_
#define _TEXT_H_

#include <stdint.h>

enum HorizontalAlignment {
	LEFT,
	CENTER,
	RIGHT
};

enum VerticalAlignment {
	TOP,
	MIDDLE,
	BOTTOM
};

struct StringCut {
	uint32_t Start;  // Starting character index of the cut, inclusive.
	uint32_t End;    // Ending character index of the cut, exclusive.
};

void PrintString16(const char* String, uint16_t TextColor,
	void* Dest, uint32_t DestPitch, uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height,
	enum HorizontalAlignment HorizontalAlignment, enum VerticalAlignment VerticalAlignment);

void PrintStringOutline16(const char* String, uint16_t TextColor, uint16_t OutlineColor,
	void* Dest, uint32_t DestPitch, uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height,
	enum HorizontalAlignment HorizontalAlignment, enum VerticalAlignment VerticalAlignment);

void PrintString32(const char* String, uint32_t TextColor,
	void* Dest, uint32_t DestPitch, uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height,
	enum HorizontalAlignment HorizontalAlignment, enum VerticalAlignment VerticalAlignment);

void PrintStringOutline32(const char* String, uint32_t TextColor, uint32_t OutlineColor,
	void* Dest, uint32_t DestPitch, uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height,
	enum HorizontalAlignment HorizontalAlignment, enum VerticalAlignment VerticalAlignment);

extern uint32_t GetRenderedWidth(const char* str);

extern uint32_t GetRenderedHeight(const char* str);

#endif /* !defined(_TEXT_H_) */
