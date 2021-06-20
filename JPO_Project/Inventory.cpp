#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory(unsigned capacity) {
	this->capacity = capacity;
	this->init();
}

Inventory::~Inventory() {
	this->free_memory();
}

// Private Methods
void Inventory::init(){
	this->capacity = 8;
	this->nr_of_items = 0;

	this->items = new Item*[this->capacity];

	this->null();
}

void Inventory::null(const unsigned from){
	for (size_t i = from; i < this->capacity; i++)
	{
		this->items[i] = nullptr;
	}
}

void Inventory::free_memory(){
	for (size_t i = 0; i < this->nr_of_items; i++)
	{
		delete this->items[i];
	}

	delete[] this->items;
}

// Public Methods
void Inventory::clear(){
	
	for (size_t i = 0; i < this->nr_of_items; i++){
		delete this->items[i];
	}

	this->nr_of_items = 0;

	this->null();
}

const bool Inventory::empty() const{
	return this->nr_of_items == 0;
}

const bool Inventory::add(Item * item){
	// Dodajemy kopiê istniej¹cego przedmiotu do ekwipunku

	if (this->nr_of_items < this->capacity) {

		this->items[this->nr_of_items++] = item->clone();

		return true;
	}
	return false;
}

const bool Inventory::remove(unsigned i){
	if (this->nr_of_items > 0) {

		if (i < this->capacity and i >= 0) {
			delete this->items[i];
			this->items[i] = nullptr;
			
			--this->nr_of_items;

			return true;
		}
		else return false;
	}
	return false;
}

const bool Inventory::save_to_file(const std::string file_name){

	return false;
}

const bool Inventory::load_from_file(const std::string file_name){

	return false;
}

// Getters
const unsigned & Inventory::size() const {
	return this->nr_of_items;
}

const unsigned & Inventory::max_size() const {

	return this->capacity;
}
