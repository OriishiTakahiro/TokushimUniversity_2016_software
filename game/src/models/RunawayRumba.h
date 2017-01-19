#ifndef RUNAWAY_RUMBA_H
#define RUNAWAY_RUMBA_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <cmath>
#include "Rumba.h"
#include "CustomizedRumba.h"
#include "Equipment.h"
#include "../Setting.h"

#include <iostream>

class RunawayRumba : public Rumba {
	private:
		bool judgeCollision(Equipment* equipment);
		bool judgeCollision(CustomizedRumba* rumba);
		Vector<float> speed_vec;
		Vector<float> getReflectedVector(Equipment equipment);
		Vector<float> getReflectedVector(CustomizedRumba rumba);
		Vector<float> getReflectedVector(SDL_Rect field);
	public:
		RunawayRumba(int x, int y) : Rumba(x, y) {
			speed_vec = Vector<float>(ROOMBA_SPEED*0.7, ROOMBA_SPEED*0.3);
		}
		void straight();
		void calcSpeedVector(SDL_Rect field, vector<Equipment> equip_list, vector<CustomizedRumba> rumba_list);
		Vector<float> getSpeedVec() { return speed_vec; }
		bool isInEquipment(Equipment equip);
};

Vector<float> RunawayRumba::getReflectedVector(Equipment equipment) {
	Vector<int>* list = equipment.getAllApexes();
	Vector<int> tmp_vec;
	int i;
	for( i = 0; i < 4; i++) {

		if( isInEquipment(equipment) ) break;

		// r.f. http://marupeke296.com/COL_2D_No5_PolygonToCircle.html
		Vector<int> S = list[(i+1)%4] - list[i];
		Vector<int> A = center_pos - list[i];
		Vector<int> B = center_pos - list[(i+1)%4];
		double distance = S.getOuterProduct(A)/S.getMagnitude();

		if( fabs(distance) < radius && (A.getInnerProduct(S)*B.getInnerProduct(S) < 0) ) {

			if( i%2 == 0 && (speed_vec.getY()*A.getY() < 0) ) {	// horizontal edge (hit edge is horizontal and roomba turns to the edge)
				equipment.decreaseLife();
				delete[] list;
				return Vector<float>( speed_vec.getX(), -speed_vec.getY() );
			}
			if( i%2 == 1 && (speed_vec.getX()*A.getX() < 0) ) {	// vertical edge
				equipment.decreaseLife();
				delete[] list;
				return Vector<float>( -speed_vec.getX(), speed_vec.getY() );
			}
		}

	}
	delete[] list;
	return Vector<float>(0,0);
}

Vector<float> RunawayRumba::getReflectedVector(CustomizedRumba rumba) {
	Vector<float> tmp_vec = center_pos - rumba.getCenterPos();
	if( tmp_vec.getMagnitude() < (rumba.getRadius() + radius)) {
		return tmp_vec;
	}
	return Vector<float>(0, 0);
}

Vector<float> RunawayRumba::getReflectedVector(SDL_Rect field) {
	// judge vertical side
	if( ( (field.w - (center_pos.getX() + radius)) < 0 && speed_vec.getX() > 0)
		|| (center_pos.getX() < radius && speed_vec.getX() < 0) ) {
		return Vector<float>( -speed_vec.getX(), speed_vec.getY() );
	}
	// judge horizontal side
	if( ((field.h - (center_pos.getY() + radius)) < 0 && speed_vec.getY() > 0)
		|| (center_pos.getY() < radius && speed_vec.getY() < 0) ) {
		return Vector<float>( speed_vec.getX(), -speed_vec.getY() );
	}
	return Vector<float>(0.0, 0.0);
}

void RunawayRumba::straight() { center_pos = center_pos + speed_vec; }

void RunawayRumba::calcSpeedVector(SDL_Rect field, vector<Equipment> equip_list, vector<CustomizedRumba> rumba_list) {
	Vector<float> tmp_vec = Vector<float>(0.0, 0.0);
	unsigned int i;

	tmp_vec += getReflectedVector(field);
	// reflected by all Equipments
	for(i = 0; i < equip_list.size(); i++) tmp_vec += getReflectedVector( equip_list[i] );
	// reflected by all Customized roombas
	for(i = 0; i < rumba_list.size(); i++) tmp_vec += getReflectedVector( rumba_list[i] );
	// reflected by all field sides

	if(tmp_vec.getMagnitude() < 0.1) return;
	tmp_vec /= tmp_vec.getMagnitude();
	tmp_vec *= ROOMBA_SPEED;
	speed_vec = tmp_vec;
}
bool RunawayRumba::isInEquipment(Equipment equip) {
		Vector<int>* appexes = equip.getAllApexes();
		bool is_in = 
			( appexes[0].getX() < center_pos.getX()
				 && center_pos.getX() < appexes[2].getX() ) &&
			( appexes[0].getY() < center_pos.getY()
				&& center_pos.getY() < appexes[2].getY() );
		return is_in;
}

#endif
