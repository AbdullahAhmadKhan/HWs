#include "Triangular.h"

Triangular::Triangular(int id, const vector<Wall*>& edges, const NucleoBase& nucleobase): MicroOrganism(id, edges){
	this -> RNA = new NucleoBase(nucleobase);
}

Triangular::~Triangular(){
	delete RNA;
}

void Triangular::ConnectToCell(Cell* const cell){
	Cell* copy = new Cell(*cell);
	copy -> StrengthenCellWall();

	this -> parent_cell = cell;
	if(this -> edges.size() != 0){ 
		for(int i = 0; i < 3; i++){
			delete (this -> edges[i]);
		}
		edges.clear();
	}

	for(int i = 0; i < 3; i++){
		Wall* temp = new Wall(*(copy -> GetCellWall()[i]));
		(this -> edges).push_back(temp);
	}

	delete copy;
}

bool Triangular::DoesFitInto(const Cell& cell) const{
	Cell* copy = new Cell(cell);
	copy -> StrengthenCellWall();
	int arr[3];
	bool result;
	
	for(int i = 0; i < 3; i++){
		arr[i] = 0;
	}
	//cout << *copy << endl; 
	if(copy -> GetCellWall().size() == 3){
		for(int i = 0; i < 3; i++){
			copy -> GetCellWall()[i] -> ComputeLength(); 
		}
		for(int i = 0; i < 3; i++){
			CurvyWall* temp = dynamic_cast<CurvyWall*> (copy -> GetCellWall()[i]);
			if(temp != NULL){
				//cout << "No";
				return false;
			}
		}

		for(int i = 2; i >= 0; i--){
			//cout << copy -> GetCellWall()[i] -> GetInitialParticle() << copy -> GetCellWall()[i] -> GetFinalParticle() << endl;
			for(int j = 2; j >= 0; j--){
				if(abs(edges[i] -> GetLength() - copy -> GetCellWall()[j] -> GetLength()) < EPSILON){
					//cout << "Yes";
					arr[j] += 1;
				}
			}
		}
		bool found = false;
		for(int i = 0; i < 3; i++){
			//cout << arr[i] << " ";
			if(arr[i] == 0){
				found = true;
			}
		}
		if(found){
			result = false;
		}
		else{
			result = true;
		}
	}
	else{
		result = false;
	}
	delete copy;
	return result;
}

void Triangular::React(){
	this -> parent_cell -> GetTissue() -> RemoveCell(*parent_cell);
	delete this -> parent_cell;										//TODO: Make the tissue notice that the cell was killed

}

const NucleoBase& Triangular::GetRNA() const{
	NucleoBase* current = this -> RNA;

	while(current -> prev != NULL){
		current = current -> prev;
	}

	return *current;
}

void Triangular::Mutate(Triangular& rhs){
	int i = 0, j = 0;
	string new_this, new_that;

	while(i < (this -> RNA) -> chain.length() && j < rhs.RNA -> chain.length()){
		if(this -> RNA -> chain[i] == rhs.RNA -> chain[j]){
			new_this.push_back(this -> RNA -> chain[i]);
			new_that.push_back(rhs.RNA -> chain[j]);
			i++;
			j++;
			continue;
		}
		else if(this -> RNA -> chain[i] == 'G' && rhs.RNA -> chain[j] == 'S'){
			new_this.push_back('S');
			new_that.push_back('G');
			i++;
			j++;
		}
		else if(this -> RNA -> chain[i] == 'S' && rhs.RNA -> chain[j] == 'G'){
			new_this.push_back('G');
			new_that.push_back('S');
			i++;
			j++;
		}
		else if(this -> RNA -> chain[i] == 'A' && rhs.RNA -> chain[j] == 'U'){
			new_this.push_back('U');
			new_that.push_back('A');
			i++;
			j++;
		}
		else if(this -> RNA -> chain[i] == 'U' && rhs.RNA -> chain[j] == 'A'){
			new_this.push_back('A');
			new_that.push_back('U');
			i++;
			j++;
		}
		else{
			i++;
			j++;
		}
	}
	swap((this -> RNA) -> chain, new_this);
	swap(rhs.RNA -> chain, new_that);
}