#include "Cell.h"

Cell::Cell(int id, const vector<Wall*>& v, Tissue* tissue){
	this -> id = id;
	for(int i = 0; i < v.size(); i++){
		Wall* temp = (*v[i]).Clone();
		this -> walls.push_back(temp);
	}
	this -> parent_tissue = tissue;
}

Cell::Cell(const Cell& rhs){
	this -> id = rhs.id;
	for(int i = 0; i < rhs.walls.size(); i++){
		Wall* temp = (*rhs.walls[i]).Clone();
		this -> walls.push_back(temp);
	}
	this -> parent_tissue = rhs.parent_tissue;
}

int Cell::GetCellID() const{
	return id;
}

Tissue* Cell::GetTissue() const{
	return parent_tissue;
}

const vector<Wall*>& Cell::GetCellWall() const{
	return walls;
}

void Cell::RenewCellWall(vector<Wall*>& new_walls){
	for(int i = 0; i < (this -> walls).size(); i++){
		delete (this -> walls)[i];
	}
	walls.clear();
	for(int i = 0; i < new_walls.size(); i++){
		(this -> walls).push_back(new_walls[i]);
	}
}

void Cell::StrengthenCellWall(){
	//cout << "Hi";
	vector<Wall*> new_walls;
	if((this -> walls).size() == 0){
		return;
	}
	Wall* sum;
	sum = ((this -> walls)[0]) -> Clone();
	//cout << "yes";
	for(int i = 0; i < (this -> walls).size(); i++){
		int next;
		if(i == (this -> walls).size() - 1){
			next = 0;
			try{
				if(sum != NULL){
					if(new_walls.size() != 0){
						const Wall* temp = &(*sum + *(new_walls[next]));
						delete sum;
						sum = const_cast<Wall*>(temp);
					}
					else{
						/*const Wall* temp = &(*sum + *(walls[next]));
						delete sum;
						sum = const_cast<Wall*>(temp);
						cout << sum -> GetInitialParticle().Y()<< endl;
						cout << sum -> GetFinalParticle().Y() << endl;*/
					}
				}
				else{
					sum = new Wall(*sum + *(new_walls[next]));
				}
				if(new_walls.size() == 0){
					new_walls.push_back(sum);
				}
				else{
					delete new_walls[0];
					new_walls[0] = sum;
				}
			}
			catch(ApplePearException error){
				if(sum != NULL){
					new_walls.push_back(sum);
				}
			}
			break;
		}
		next = i + 1;
		if(next < (this -> walls).size()){
			try{
				if(sum != NULL){
					const Wall* temp = &(*sum + *((this -> walls)[next]));
					delete sum;
					sum = const_cast<Wall*>(temp);
					//cout << sum -> GetInitialParticle().Y()<< endl;
					//cout << sum -> GetFinalParticle().Y() << endl;
				}
				else{
					sum = new Wall(*sum + *((this -> walls)[next]));
				}
			}
			catch(ApplePearException error){
				if(sum != NULL){
					new_walls.push_back(sum);
				}
				sum = ((this -> walls)[next]) -> Clone();
			}
		}
		else{
			new_walls.push_back((this -> walls)[i]);
			break;
		}
	}
	RenewCellWall(new_walls);
	/*for(int i = 0; i < new_walls.size(); i++){
		delete new_walls[i];
	}*/
	new_walls.clear();
}

Cell::~Cell(){
	for(int i = 0; i < (this -> walls).size(); i++){
		delete (this -> walls)[i];
	}
	(this -> walls).clear();
	parent_tissue = NULL;
}

ostream& operator<<(ostream& os, const Cell& cell){
	for(int i = 0; i < cell.walls.size(); i++){
		if(i == cell.walls.size() - 1){
			os << "(" << cell.walls[i] -> GetInitialParticle().X() << "," << cell.walls[i] -> GetInitialParticle().Y() << ")";
			break;
		}
		os << "(" << cell.walls[i] -> GetInitialParticle().X() << "," << cell.walls[i] -> GetInitialParticle().Y() << ")" << " - ";
	}
	return os;
}