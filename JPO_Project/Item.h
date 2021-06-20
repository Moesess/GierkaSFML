#ifndef ITEM_H
#define ITEM_H

enum ItemTypes{WEAPON_DEFAULT = 0, MELEEWEAPON};

class Item{
private:
	void variables_init();

protected:
	// Vars
	short unsigned type;
	unsigned value;

public:
	Item(unsigned value);
	virtual ~Item();

	// Methods
	virtual Item* clone() = 0;
};

#endif