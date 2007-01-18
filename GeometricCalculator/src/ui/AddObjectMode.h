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

#ifndef __ADDOBJECTMODE_H__
#define __ADDOBJECTMODE_H__

#include "BaseAddMode.h"
#include "../model/Point.h"

class AddObjectMode : public BaseAddMode {
	protected:
		AddObjectMode(DiagramView &view);
    virtual ObjectPtr createObject(PointPtr point0, PointPtr point1) const = 0;
		
	public:

		bool isAvailable() const;
		bool isObjectSelectable(ObjectPtr object) const;
		void release();

		void onMousePress(int x, int y);
		void onMouseRelease(int x, int y);
		void onMouseMove(int x, int y);
		void onMousePressedMove(int x, int y);

	private:
		PointPtr mySelectedPoint;
		PointPtr myMousePoint;
		ObjectPtr myNewObject;
};

#endif /* __ADDOBJECTMODE_H__ */