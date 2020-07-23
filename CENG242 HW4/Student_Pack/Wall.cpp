#include "Wall.h"

using namespace std;

Wall::Wall(float f){
	this -> length = f;
	this -> start_point = NULL;
	this -> end_point = NULL;
	this -> center_point = NULL;
	
}

Wall::Wall(const Particle& s_p, const Particle& e_p){
	this -> start_point = new Particle(s_p);
	this -> end_point = new Particle(e_p);
	//cout << "Hiiii";
	ComputeLength();
	this -> center_point = NULL;
}

Wall::Wall(const Wall& rhs){
	this -> length = rhs.length;
	if(rhs.start_point != NULL){
		this -> start_point = new Particle(*(rhs.start_point));
	}
	else{
		this -> start_point = NULL;
	}
	if(rhs.end_point != NULL){
		this -> end_point = new Particle(*(rhs.end_point));
	}
	else{
		this -> end_point = NULL;
	}
	this -> center_point = NULL;
}

const Particle& Wall::GetInitialParticle() const{
	return *start_point;
}

const Particle& Wall::GetFinalParticle() const{
	return *end_point;
}

float Wall::FindAngleBetween(const Wall& rhs) const{
	float tan1, tan2;
	if(abs(end_point -> Y() - start_point -> Y()) < EPSILON){
		//cout << *end_point << " " << *start_point << " ";
		//cout << rhs.GetFinalParticle() << " " << rhs.GetInitialParticle() << (abs(rhs.GetFinalParticle().Y() - rhs.GetInitialParticle().Y()) < EPSILON) << endl;
		if(abs(rhs.GetFinalParticle().Y() - rhs.GetInitialParticle().Y()) < EPSILON){
			//cout << "Hi";
			return 0;
		}
		else{
			if(abs(rhs.GetFinalParticle().X() - rhs.GetInitialParticle().X()) < EPSILON){
				return 3.14159265 / 2;
			}
			else{
				tan2 = (rhs.GetFinalParticle().Y() - rhs.GetInitialParticle().Y()) / (rhs.GetFinalParticle().X() - rhs.GetInitialParticle().X());
				return atan(tan2);
			}
		}
	}
	else{
		if(abs(end_point -> X() - start_point -> X()) < EPSILON){
			if(abs(rhs.GetFinalParticle().Y() - rhs.GetInitialParticle().Y()) < EPSILON){
				return 3.14159265 / 2;
			}
			else{
				if(abs(rhs.GetFinalParticle().X() - rhs.GetInitialParticle().X()) < EPSILON){
					return 0;
				}
				else{
					tan2 = (rhs.GetFinalParticle().Y() - rhs.GetInitialParticle().Y()) / (rhs.GetFinalParticle().X() - rhs.GetInitialParticle().X());
					return 3.14159265 / 2 - atan(tan2);
				}
			}
		}
		else{
			if(abs(rhs.GetFinalParticle().Y() - (rhs.GetInitialParticle().Y())) < EPSILON){
				tan1 = (end_point -> Y() - start_point -> Y()) / (end_point -> X() - start_point -> X());
				return 3.14159265 - atan(tan1);
			}
			else{
				if(abs(rhs.GetFinalParticle().X() - rhs.GetInitialParticle().X()) < EPSILON){
					tan1 = (end_point -> Y() - start_point -> Y()) / (end_point -> X() - start_point -> X());
					return 3.14159265 / 2 - atan(tan1);
				}
				else{
					tan1 = (end_point -> Y() - start_point -> Y()) / (end_point -> X() - start_point -> X());
					tan2 = (rhs.GetFinalParticle().Y() - rhs.GetInitialParticle().Y()) / (rhs.GetFinalParticle().X() - rhs.GetInitialParticle().X());
					return atan(tan1) - atan(tan2);
				}
			}		
		}
	}
	/*tan1 = (end_point -> Y() - start_point -> Y()) / (end_point -> X() - start_point -> X());
	tan2 = (rhs.GetFinalParticle().Y() - rhs.GetInitialParticle().Y()) / (rhs.GetFinalParticle().X() - rhs.GetInitialParticle().X());
	return atan(tan1) - atan(tan2);*/
}

float Wall::GetLength() const{
	return length;
}

void Wall::ComputeLength(){
	if(start_point != NULL && end_point != NULL){ 
		this -> length = start_point -> FindDistance(*end_point);
	}
}

Wall* Wall::Clone() const{
	Wall* copy = new Wall(*this);
	return copy;
}

bool Wall::IsContinuousLinear(const Wall& rhs) const{
	bool is_cont = false;
	bool is_linear = false;

	float computed_length_rhs = rhs.GetLength();
	float actual_length_rhs = rhs.GetInitialParticle().FindDistance(rhs.GetFinalParticle());

	float computed_length = this -> length;
	float actual_length = (this -> start_point) -> FindDistance(*(this -> end_point));

	if(computed_length_rhs != actual_length_rhs || computed_length != actual_length){
		return false;
	}
	if(abs(this -> FindAngleBetween(rhs)) < EPSILON){
		is_linear = true;
	}

	if(this -> GetInitialParticle() == rhs.GetFinalParticle() || this -> GetFinalParticle() == rhs.GetInitialParticle()){
		is_cont = true;
	}
	//cout << this -> GetInitialParticle() << this -> GetFinalParticle() << " " << rhs.GetInitialParticle() << rhs.GetFinalParticle() << is_linear << " " << is_cont << endl;

	return is_cont && is_linear;
}

const Wall& Wall::operator+(const Wall& rhs) const{
	if(this -> IsContinuousLinear(rhs)){
		if(abs(this -> GetInitialParticle().X() - rhs.GetFinalParticle().X()) < EPSILON && abs(this -> GetInitialParticle().Y() - rhs.GetFinalParticle().Y()) < EPSILON){
			Wall* result = new Wall(rhs.GetInitialParticle(), *(this -> end_point));
			return *result;
		}
		else if(abs(this -> GetFinalParticle().X() - rhs.GetInitialParticle().X()) < EPSILON && abs(this -> GetFinalParticle().Y() - rhs.GetInitialParticle().Y()) < EPSILON){
			Wall* result = new Wall(*(this -> start_point), rhs.GetFinalParticle());
			return *result;
		}
		else{
			throw ApplePearException();
		}
	}
	else{
		throw ApplePearException();
	}
}

Wall::~Wall(){
	if(this -> start_point != NULL){
		delete this -> start_point;
	}
	if(this -> end_point != NULL){
		delete this -> end_point;
	}
	if(this -> center_point != NULL){
		delete this -> center_point;
	}
}