#include "Tissue.h"

Tissue::Tissue(){
	this -> min_x = 0;
	this -> max_x = 0;
	this -> min_y = 0;
	this -> max_y = 0;
}

Tissue::Tissue(float f1, float f2, float f3, float f4){
	this -> min_x = f1;
	this -> max_x = f2;
	this -> min_y = f3;
	this -> max_y = f4;
}

Tissue::Tissue(const Tissue& rhs){
	this -> min_x = rhs.min_x;
	this -> max_x = rhs.max_x;
	this -> min_y = rhs.min_y;
	this -> max_y = rhs.max_y;

	for(int i = 0; i < rhs.cells.size(); i++){
		Cell* temp = new Cell(*rhs.cells[i]);
		this -> cells.push_back(temp);
	}
}

Tissue::~Tissue(){
	for(int i = 0; i < cells.size(); i++){
		delete this -> cells[i];
	}
	cells.clear();
}

float* Tissue::GetCoordinates(){
	float* arr;
	arr = new float [4];
	arr[0] = this -> min_x;
	arr[1] = this -> max_x;
	arr[2] = this -> min_y;
	arr[3] = this -> max_y;
	return arr;
}

void Tissue::AddCell(Cell& cell){
	Cell* temp = &cell;
	cells.push_back(temp);
}
		
void Tissue::RemoveCell(Cell& cell){
	for(int i = 0; i < cells.size(); i++){
		if(cells[i] -> GetCellID() == cell.GetCellID()){
			cells.erase(cells.begin() + i);
		}
	}
}

const Cell& Tissue::GetCell(int id) const{
	for(int i = 0; i < cells.size(); i++){
		if(cells[i] -> GetCellID() == id){
			return *cells[i];
		}
	}
	throw DeadCellException();	
}

void Tissue::Interact(const vector<MicroOrganism*>& mo){
	for(int i = 0; i < mo.size(); i++){
		for(int j = 0; j < cells.size(); j++){
			//cout << mo[i] -> DoesFitInto(*cells[j]);
			if(mo[i] -> DoesFitInto(*cells[j])){
				mo[i] -> ConnectToCell(cells[j]);
			}
		}
	}
	//cout << *cells[0] << endl;
	//cout << *cells[1] << endl;
	//cout << *cells[2] << endl;
	/*cout << *cells[3] << endl;
	cout << *cells[4] << endl;
	cout << *cells[5] << endl;
	cout << *cells[6] << endl;*/
	/*cout << mo[5] -> DoesFitInto(*cells[1]) << endl;
	cout << mo[5] -> DoesFitInto(*cells[2]) << endl;
	cout << mo[5] -> DoesFitInto(*cells[3]) << endl;
	cout << mo[5] -> DoesFitInto(*cells[4]) << endl;
	cout << mo[5] -> DoesFitInto(*cells[5]) << endl;
	cout << mo[5] -> DoesFitInto(*cells[6]) << endl;*/
	
}	
