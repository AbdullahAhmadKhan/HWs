#include "MicroOrganism.h"

MicroOrganism::MicroOrganism(int id){
	this -> id = id;
	this -> parent_cell = NULL;
	
}

MicroOrganism::MicroOrganism(int id, float rad){
	this -> id = id;
	Wall *temp = new CurvyWall(2*PI*rad, rad);
	(this -> edges).push_back(temp);
	this -> parent_cell = NULL;
}

MicroOrganism::MicroOrganism(int id, const vector<Wall*>& new_edges){
	this -> id = id;
	for(int i = 0; i < new_edges.size(); i++){
		Wall* temp = new_edges[i] -> Clone();
		(this -> edges).push_back(temp);
	}
	//cout << new_edges.size();
	this -> parent_cell = NULL;
}

ostream& operator<<(ostream& os, const MicroOrganism& microorganism){
	if(microorganism.parent_cell != NULL){
		os << "The microorganism " << microorganism.id << " was successfully placed into the cell " << microorganism.parent_cell -> GetCellID() << "."; 
	}
	else{
		os << "The microorganism " << microorganism.id << " could not be placed into any cell!";
	}
	return os;
}

bool MicroOrganism::DoesFitInto(const Cell& cell) const{
	return false;
}

void MicroOrganism::ConnectToCell(Cell* const cell){
	return;
}

void MicroOrganism::React(){
	return;
}

MicroOrganism::~MicroOrganism(){
	for(int i = 0; i < edges.size(); i++){
		delete this -> edges[i];
	}
	edges.clear();
	this -> parent_cell = NULL;
}