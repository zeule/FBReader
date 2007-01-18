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

#include "AddObjectMode.h"
#include "../document/Document.h"
#include "../model/Point.h"

AddObjectMode::AddObjectMode(DiagramView &view) : BaseAddMode(view) {
}

void AddObjectMode::release() {
	myNewObject.reset();
	myMousePoint.reset();
	mySelectedPoint.reset();
	mySelectedObject0.reset();
	mySelectedObject1.reset();
}

bool AddObjectMode::isAvailable() const {
	const std::list<ObjectPtr> &objects = document()->scene()->objects();
	int pointCounter = 0;
	for (std::list<ObjectPtr>::const_iterator it = objects.begin(); it != objects.end(); it++) {
		if ((*it)->rtti() == Object::POINT) {
			if (view().ExistingPointsOnlyOption.value()) {
				pointCounter++;
				if (pointCounter == 2) {
					return true;
				}
			} else {
				return true;
			}
		}
	}
	return false;
}

bool AddObjectMode::isObjectSelectable(ObjectPtr object) const {
	if (mySelectedPoint.isNull()) {
		return object->rtti() == Object::POINT;
	} else {
		if (view().ExistingPointsOnlyOption.value()) {
			return (object != mySelectedPoint) && (object->rtti() == Object::POINT);
		} else {
			return (object != mySelectedPoint) && (object != mySelectedObject0);
		}
	}
}

void AddObjectMode::onMousePress(int x, int y) {
	if (!mySelectedPoint.isNull() && myMousePoint.isNull()) {
		myMousePoint = IndependentPoint::create(x, y);
		document()->addTemporary(myMousePoint);
		
		myNewObject = createObject(mySelectedPoint, myMousePoint);
		document()->addTemporary(myNewObject);
		
		if (!view().ExistingPointsOnlyOption.value()) {
			select(myMousePoint);
			select(myNewObject);
		}

		onMousePressedMove(x, y);
	}
}

void AddObjectMode::onMouseRelease(int x, int y) {
	if (!myNewObject.isNull()) {
		unselect(myNewObject); document()->remove(myNewObject); myNewObject = 0;
		unselect(myMousePoint); document()->remove(myMousePoint); myMousePoint = 0;
		unselect(mySelectedPoint);

	  myMousePoint = getPoint(x, y, !view().ExistingPointsOnlyOption.value());
		if (!myMousePoint.isNull()) {
			myNewObject = createObject(mySelectedPoint, myMousePoint);
			if (myMousePoint == mySelectedObject0) {
				document()->add(myNewObject);
			} else {
				myMousePoint->moveTo(x, y);
    
				document()->startTransaction();
				document()->add(myMousePoint);
				document()->add(myNewObject);
				document()->endTransaction();
			}
		}

		release();

		repaintView();
	}
}

void AddObjectMode::onMouseMove(int x, int y) {
	bool doRepaint = isSelected(mySelectedPoint);
	unselect(mySelectedPoint);
	mySelectedPoint.reset();
	mySelectedPoint = closestObject(x, y);
	if (!mySelectedPoint.isNull()) {
		doRepaint = true;
		select(mySelectedPoint);
	}
	if (doRepaint) {
		repaintView();
	}
}

void AddObjectMode::onMousePressedMove(int x, int y) {
	if (!mySelectedPoint.isNull() && !myMousePoint.isNull()) {
		PointPtr point = getPoint(x, y, !view().ExistingPointsOnlyOption.value());
		if (!point.isNull()) {
			myMousePoint->moveTo(point->coordinates());
			select(mySelectedObject0);
			select(mySelectedObject1);
			select(myMousePoint);
			select(myNewObject);
		} else {
			myMousePoint->moveTo(x, y);
			unselect(myMousePoint);
			unselect(myNewObject);
		}
		repaintView();
	}
}