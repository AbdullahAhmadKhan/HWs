#include "Squadratic.h"

Squadratic::Squadratic(int id, vector<Wall*> walls, Cell* p_c, float length): MicroOrganism(id, walls){
	this -> parent_cell = p_c;
	this -> edge_length = length;
}

Squadratic::Squadratic(int id, float fl): MicroOrganism(id){
	//cout << "hi";
	this -> edge_length = fl; 
}

Squadratic::Squadratic(const Squadratic& rhs): MicroOrganism (rhs.id){
	this -> edge_length = rhs.edge_length;
	this -> parent_cell = rhs.parent_cell;
	for(int i = 0; i < rhs.edges.size(); i++){
		(this -> edges).push_back(rhs.edges[i]);
	}
}

Squadratic::~Squadratic(){

}

void Squadratic::ConnectToCell(Cell* const cell){
	Cell* copy = new Cell(*cell);
	copy -> StrengthenCellWall();

	//cout << (copy -> GetCellWall()[0] == NULL);

	this -> parent_cell = cell;
	if(edges.size() != 0){
		for(int i = 0; i < 4; i++){
			delete (this -> edges[i]);
		}
		edges.clear();
	}
	for(int i = 0; i < 4; i++){
		Wall* temp = new Wall(*(copy -> GetCellWall()[i]));
		(this -> edges).push_back(temp);
	}

	delete copy;
}

bool Squadratic::DoesFitInto(const Cell& cell) const{
	//cout << edges.size() << "NOOOOO";
	//cout << cell << endl;
	Cell* copy = new Cell(cell);
	copy -> StrengthenCellWall();
	int arr[4];
	bool result;
	for(int i = 0; i < 4; i++){
		arr[i] = 0;
	}
	//cout << *copy << endl;
	if(copy -> GetCellWall().size() == 4){
		//cout << "YEs";
		for(int i = 0; i < 4; i++){
			copy -> GetCellWall()[i] -> ComputeLength();
		}
		for(int i = 0; i < 4; i++){
			CurvyWall* temp = dynamic_cast<CurvyWall*> (copy -> GetCellWall()[i]);
			if(temp != NULL){
				//cout << "NO";
				return false;
			}
		}
		bool angle = true;
		//cout << copy -> GetCellWall().size() << endl;
		for(int i = 0; i < 4; i++){
			//cout << i;
			//cout << "Here" << endl;
			//cout << abs(copy -> GetCellWall()[i] -> FindAngleBetween(*copy -> GetCellWall()[i + 1]) * 180 / PI) << endl;
			if(abs(copy -> GetCellWall()[i] -> FindAngleBetween(*copy -> GetCellWall()[i + 1]) * 180 / PI) < (90 + EPSILON) &&
				abs(copy -> GetCellWall()[i] -> FindAngleBetween(*copy -> GetCellWall()[i + 1]) * 180 / PI) > (90 - EPSILON) ||
				abs(copy -> GetCellWall()[i] -> FindAngleBetween(*copy -> GetCellWall()[i + 1]) * 180 / PI) < (270 + EPSILON) &&
				abs(copy -> GetCellWall()[i] -> FindAngleBetween(*copy -> GetCellWall()[i + 1]) * 180 / PI) > (270 - EPSILON)){
				//cout << i << endl;
				continue;
			}
			else{
				//cout << "NOO";
				angle = false;
				break;
			}
		}

		if(angle == false){
			return false;
		}

		for(int i = 3; i >= 0; i--){
			//cout << copy -> GetCellWall()[i] -> GetInitialParticle() << copy -> GetCellWall()[i] -> GetFinalParticle() << endl;
			for(int j = 3; j >= 0; j--){
				//cout << edges.size();
				//cout << edges[i] -> GetLength();
				if(abs(edge_length - copy -> GetCellWall()[j] -> GetLength()) < EPSILON){
					arr[j] += 1;
				}
			}
		}
		bool found = false;
		for(int i = 0; i < 4; i++){
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

void Squadratic::React(){
	vector<Particle*> mid_particles;
	for(int i = 0; i < 4; i++){
		Particle* temp_particle = new Particle((this -> edges[i] -> GetFinalParticle().X() + this -> edges[i] -> GetInitialParticle().X())/2, (this -> edges[i] -> GetFinalParticle().Y() + this -> edges[i] -> GetInitialParticle().Y())/2);
		mid_particles.push_back(temp_particle);
	}
	Particle* center_particle = new Particle((mid_particles[0] -> X() + mid_particles[1] -> X() + mid_particles[2] -> X() + mid_particles[3] -> X()) / 4,
		(mid_particles[0] -> Y() + mid_particles[1] -> Y() + mid_particles[2] -> Y() + mid_particles[3] -> Y()) / 4);
	
	for(int i = 0; i < 4; i++){
		vector<Wall*> temp_walls;
		Wall* temp_wall = new Wall(this -> edges[i] -> GetInitialParticle(), *mid_particles[i]);
		temp_walls.push_back(temp_wall);
		temp_wall = new Wall(*mid_particles[i], *center_particle);
		temp_walls.push_back(temp_wall);
		temp_wall = new Wall(*center_particle, *mid_particles[4 - i]);
		temp_walls.push_back(temp_wall);
		temp_wall = new Wall(*mid_particles[4 - i], this -> edges[i] -> GetInitialParticle());
		temp_walls.push_back(temp_wall);

		Squadratic* new_mo = new Squadratic(this -> id, temp_walls, this -> parent_cell, this -> edge_length / 2);
		this -> children.push_back(new_mo);

		for(int j = 0; j < 4; j++){
			delete temp_walls[j];
		}
		temp_walls.clear();
	} 
	delete center_particle;
	for(int i = 0; i < 4; i++){
		delete mid_particles[i];
	}
	mid_particles.clear();
}

Squadratic& Squadratic::GetChild(float min_x, float max_x, float min_y, float max_y) const{
	for(int i = 0; i < 4; i++){
		int ctr;
		for(int j = 0; j < 4; j++){
			ctr = 0;
			if(this -> children[i] -> edges[j] -> GetInitialParticle().X() - min_x >= EPSILON && max_x - this -> children[i] -> edges[j] -> GetInitialParticle().X() >= EPSILON 
				&& this -> children[i] -> edges[j] -> GetInitialParticle().Y() - min_y >= EPSILON && max_y - this -> children[i] -> edges[j] -> GetInitialParticle().Y() >= EPSILON){
				ctr++;
			}
		}
		if(ctr == 4){
			return *(this -> children[i]);
		}
	}
	throw NotBornChildException();
}