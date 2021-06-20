#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent(){
	this->skills.push_back(Skill(SKILLS::HEALTH));
	this->skills.push_back(Skill(SKILLS::ACCURACY));
	this->skills.push_back(Skill(SKILLS::ATTACK));
	this->skills.push_back(Skill(SKILLS::ENDURANCE));
}

SkillComponent::~SkillComponent(){

}

const int SkillComponent::get_skill(const int skill) const{

	if (skills.empty() or skill < 0 or this->skills.size() <= static_cast<unsigned>(skill)) {
		throw("ERROR: SKILLCOMPONENT GETSKILL SKILL DOESNT EXIST" + skill);
	}
	else 
	return this->skills[skill].get_level();
}

const void SkillComponent::gain_exp(const int skill, const int exp){

	if (skills.empty() or skill < 0 or this->skills.size() <= static_cast<unsigned>(skill)) {
		throw("ERROR: SKILLCOMPONENT GAINEXP SKILL DOESNT EXIST" + skill);
	}
	else {
		this->skills[skill].gain_exp(exp);
	}

	return void();
}
