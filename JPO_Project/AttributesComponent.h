#ifndef ATTRIBUTESCOMPONENT_H
#define ATTRIBUTESCOMPONENT_H

class AttributesComponent{
private:

public:
	// Levels
	int level;
	int exp;
	int exp_next;
	int level_points;

	// Attributes
	int strength;
	int vitality;
	int dexterity;
	int agility;
	int intelligence;

	// Stats
	int hp;
	int hp_max;
	int damage_min;
	int damage_max;
	int accuracy;
	int defence;
	int luck;

	// ======
	AttributesComponent(int level);
	virtual ~AttributesComponent();

	// Setters

	// Getters

	// Methods
	std::string print() const;

	void loose_hp(const int hp);
	void gain_hp(const int hp);
	void loose_exp(const int exp);
	void gain_exp(const int exp);

	const bool is_dead() const;

	void update_level();
	void update_stats(const bool reset = false);
	void update();
};

#endif