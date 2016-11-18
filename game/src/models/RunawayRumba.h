#ifndef RUNAWAY_RUMBA_H

#include "Rumba.h"
#include "CustomizedRumba.h"
#include "Equipment.h"
#include "../utils/LinkedList.h"
#include "../views/GameWindow.h"

#define RUNAWAY_RUMBA_H
#define MAX_SPEED 4.0

class RunawayRumba : public Rumba {
	private:
		bool judgeCollision(Equipment* equipment);
		bool judgeCollision(CustomizedRumba* rumba);
		Vector<int> speed_vec;
		Vector<int> getReflectedVector(Equipment* equipment);
		Vector<int> getReflectedVector(CustomizedRumba* rumba);
		void getReflectedVector(GameWindow* field);
	public:
		RunawayRumba(int x, int y, int r) : Rumba(x, y, r) {
			speed_vec = Vector<int>(0.0, 0.0);
		}
		void behave();
		void behaveCollision(GameWindow* window, LinkedList<Equipment>* equip_list, LinkedList<CustomizedRumba>* rumba_list);
};

Vector<int> RunawayRumba::getReflectedVector(Equipment* equipment) {
	Vector<int>* list = equipment->getAllApexes();
	Vector<int> tmp_vec;
	double vertical_len;
	int i;
	for( i = 0; i < 4; i++) {
		tmp_vec = list[(i+1)%4] - list[i];
		vertical_len = (center_pos - list[i]).getInnerProduct(tmp_vec) / pow(tmp_vec.getMagnitude(), 2.0);
		if( vertical_len < radius ) {
			equipment->decreaseLife();
			delete list;
			return ( (tmp_vec * vertical_len) + list[i]) - center_pos;
		}
	}
	delete list;
	return Vector<int>(0,0);
}

Vector<int> RunawayRumba::getReflectedVector(CustomizedRumba* rumba) {
	Vector<int> tmp_vec = rumba->getCenterPos() - center_pos;
	if( tmp_vec.getMagnitude() < (rumba->getRadius()) + radius) {
		tmp_vec /= tmp_vec.getMagnitude();
		tmp_vec *= (-1 * rumba->getSpeedVector().getMagnitude());
		return tmp_vec;
	}
	return Vector<int>(0, 0);
}

void RunawayRumba::getReflectedVector(GameWindow* field) {
	if(
			// judge both side (left and right)
			(field->getWidth() - (center_pos.getX() + radius)) < 0 || 
			center_pos.getX() < radius || 
			// judge both side (top and bottom)
			(field->getHeight() - (center_pos.getY() + radius)) < 0 || 
			center_pos.getY() < radius
	) speed_vec *= -1;
}

void RunawayRumba::behave() { center_pos = center_pos + speed_vec; }

void RunawayRumba::behaveCollision(GameWindow* field, LinkedList<Equipment>* equip_list, LinkedList<CustomizedRumba>* rumba_list) {
	Object obj;
	Vector<int> tmp_vec = speed_vec;
	int i;

	equip_list->resetCurrent();
	rumba_list->resetCurrent();
	for(i = 0; i < equip_list->getSize(); i++) tmp_vec += getReflectedVector( equip_list->getPtr() );
	for(i = 0; i < rumba_list->getSize(); i++) tmp_vec += getReflectedVector( rumba_list->getPtr() );

	if(tmp_vec.getMagnitude() > MAX_SPEED) {
		tmp_vec /= tmp_vec.getMagnitude();
		tmp_vec *= MAX_SPEED;
	}
}

#endif
