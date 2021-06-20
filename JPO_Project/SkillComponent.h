#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H

enum SKILLS {HEALTH = 0, ATTACK, ACCURACY, ENDURANCE};

class SkillComponent{

private:
	class Skill {
	private:
		int type;
		int level;
		int level_cap;
		int exp;
		int exp_next;

	public:
		Skill(int type) {
			this->type = type;
			this->level = 1;
			this->level_cap = 99;
			this->exp = 0;
			this->exp_next = 100;
		}

		~Skill() {}

		// Getters
		inline const int& get_level() const { return this->level; }
		inline const int& get_type() const { return this->type; }
		inline const int& get_exp() const { return this->exp; }
		inline const int& get_exp_next() const { return this->exp_next; }

		// Setters
		inline void set_level(const int level) { this->level = level; }
		inline void set_level_cap(const int level_cap) { this->level_cap = level_cap; }

		// Methods
		inline void gain_exp(const int exp) { this->exp += exp; this->update_level(); }
		inline void loose_exp(const int exp) { this->exp -= exp; }

		void update_level(const bool up = true) {

			if (up) {
				if (this->level < this->level_cap) {

					while (this->exp >= this->exp_next) {

						if (this->level < this->level_cap) {

							this->level++;
							this->exp_next = static_cast<int>(std::pow(this->level, 2) + this->level * 10 + this->level * 2);
						}
					}
				}
			}

			else {
				if (this->level > 0){

					while (this->exp < 0) {

						if (this->level > 0) {

							this->level--;
							this->exp_next = static_cast<int>(std::pow(this->level, 2) + this->level * 10 + this->level * 2);
						}
					}
				}
			}
		}

		void update(){
			
		}
	};

	std::vector<Skill> skills;

public:
	SkillComponent();
	virtual ~SkillComponent();

	// Getters
	const int get_skill(const int skill) const;

	// Methods
	const void gain_exp(const int skill, const int exp);
};

#endif