#include "stdafx.h"
#include "Item.h"

void Item::variables_init(){

}

Item::Item(unsigned value){
	this->variables_init();

	this->value = value;
	this->type = ItemTypes::WEAPON_DEFAULT;
}

Item::~Item(){

}
