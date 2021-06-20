#include "stdafx.h"
#include "EditorMode.h"

EditorMode::EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data):state_data(state_data), tile_map(tile_map), editor_state_data(editor_state_data){
	this->texture_res = 32.f;
}

EditorMode::~EditorMode(){

}

const bool EditorMode::get_keytime(){
	if (*this->editor_state_data->keytime >= *this->editor_state_data->keytime_max) {

		*this->editor_state_data->keytime = 0.f;
		return true;
	}
	return false;
}
