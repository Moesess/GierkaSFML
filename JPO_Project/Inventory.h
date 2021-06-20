#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"

class Inventory{
private:
	Item** items;
	unsigned nr_of_items;
	unsigned capacity;

	// Methods
	void init();
	void null(const unsigned from = 0);
	void free_memory();

public:
	Inventory(unsigned capacity);
	virtual ~Inventory();

	// Methods
	void clear();
	const bool empty() const;
	const bool add(Item* item);
	const bool remove(unsigned i);

	const bool save_to_file(const std::string file_name);
	const bool load_from_file(const std::string file_name);

	// Getters
	const unsigned& size() const;
	const unsigned& max_size() const;

	// Setters

};

#endif