/*
 * Geometric Calculator -- interactive geometry program
 * Copyright (C) 2003-2007 Nikolay Pultsin <geometer@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __ADDPOINTBASEMODE_H__
#define __ADDPOINTBASEMODE_H__

#include "../model/PointPtr.h"
#include "BaseAddMode.h"

class AddPointBaseMode : public BaseAddMode {

protected:
	AddPointBaseMode(DiagramView &view);
	//PointPtr createCrossing(const Coordinates &coords) const;

public:
	void release();

	void onMousePressedMove(int x, int y);
	void onMouseRelease(int x, int y);

protected:
	PointPtr myPoint;
};

#endif /* __ADDPOINTBASEMODE_H__ */