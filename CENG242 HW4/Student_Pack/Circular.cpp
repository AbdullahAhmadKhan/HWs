#include "Circular.h"

Circular::Circular(int id, float rad): MicroOrganism(id, rad){
	micro_radius = rad;

}

Circular::~Circular(){

}

void Circular::ConnectToCell(Cell* const cell){
	Cell* copy = new Cell(*cell);
	copy -> StrengthenCellWall();

	this -> parent_cell = cell;
	if(this -> edges.size() != 0){
		delete (this -> edges[0]);
		edges.clear();
	}
	Wall* temp = new Wall(*(copy -> GetCellWall()[0]));
	(this -> edges).push_back(temp);

	delete copy;
}

bool Circular::DoesFitInto(const Cell& cell) const{

	//cout << cell << endl;
	Cell* copy = new Cell(cell);
	copy -> StrengthenCellWall();
	int arr = 0;
	bool result;
	//cout << cell << endl;

	//cout << "Here";
	//CurvyWall* temp = dynamic_cast<CurvyWall*>(copy -> GetCellWall()[0]);// sil bunu
	//cout << temp -> GetRadius() << endl;

	//cout << *copy << endl;	
	if(copy -> GetCellWall().size() == 1){
		copy -> GetCellWall()[0] -> ComputeLength(); 
		//cout << copy -> GetCellWall()[0] -> GetInitialParticle().Y() << endl;
		//cout << copy -> GetCellWall()[0] -> GetFinalParticle().Y() << endl;
		//cout << edges[0] -> GetInitialParticle() << endl;
		//cout << edges[0] -> GetFinalParticle().Y() << endl;
		//cout << copy -> GetCellWall()[0] -> GetLength() << endl;
		//this -> edges[0] -> ComputeLength();
		//cout << edges[0] -> GetLength() << endl;// << " " << copy -> GetCellWall()[0] -> GetLength() << endl;
		
		CurvyWall* temp = dynamic_cast<CurvyWall*> (copy -> GetCellWall()[0]);
		if(temp == NULL){
			//cout << "No";
			return false;
		}
		if(abs(edges[0] -> GetLength() - copy -> GetCellWall()[0] -> GetLength()) < EPSILON){
			//cout << "Noo";
			arr += 1;
		}
		//cout << arr << endl
			;
		if(arr == 1){
			result = true;
		}
		else if(arr == 0){
			//cout << "Hi?";
			result = false;
			//cout << result;
		}
	}
	else{
		result = false;
	}
	//cout << result << endl;
	delete copy;
	//cout << cell << endl;
	return result;
}

void Circular::React(){
	micro_radius *= 2;
	CurvyWall* temp = dynamic_cast<CurvyWall*> (this -> parent_cell -> GetCellWall()[0]);
	vector<Wall*> new_walls;
	Particle* new_start = new Particle(temp -> GetCenter().X() + micro_radius, temp -> GetCenter().Y()); 
	Particle* new_end = new Particle(temp -> GetCenter().X() + micro_radius, temp -> GetCenter().Y());
	Wall* new_wall = new CurvyWall(*new_start, *new_end, temp -> GetCenter());
	new_walls.push_back(new_wall);

	Cell* temp2 = parent_cell;
	parent_cell = new Cell(parent_cell -> GetCellID(), new_walls, parent_cell -> GetTissue());
	
	delete temp2;
	delete new_start;
	delete new_end;
}

bool Circular::DoesContain(const Particle& part) const{
	CurvyWall* temp = dynamic_cast<CurvyWall*> (parent_cell -> GetCellWall()[0]);
	if(pow(pow(part.X() - temp -> GetCenter().X(), 2) + pow(part.Y() - temp -> GetCenter().Y(), 2), 0.5) - this -> micro_radius < EPSILON){
		return true;
	}
	else{
		return false;
	}

}