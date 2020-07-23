#include "Particle.h"

using namespace std;

Particle::Particle(float f1, float f2){
	this -> x_coor = f1;
	this -> y_coor = f2;
}

Particle::Particle(const Particle& rhs){
	this -> x_coor = rhs.x_coor; 
	this -> y_coor = rhs.y_coor;
}

float Particle::X() const{
	return this-> x_coor;
}

float Particle::Y() const{
	return this-> y_coor;
}

float Particle::FindDistance(const Particle& rhs) const{
	if(abs(this -> x_coor - rhs.x_coor) >= EPSILON && abs(this -> y_coor - rhs.y_coor) >= EPSILON){
		return pow(pow((this -> x_coor - rhs.x_coor), 2) + pow((this -> y_coor - rhs.y_coor), 2), 0.5);
	}
	else if(abs(this -> x_coor - rhs.x_coor) <= EPSILON && abs(this -> y_coor - rhs.y_coor) >= EPSILON){
		return abs(this -> y_coor - rhs.y_coor);
	}
	else if(abs(this -> x_coor - rhs.x_coor) >= EPSILON && abs(this -> y_coor - rhs.y_coor) <= EPSILON){
		return abs(rhs.x_coor - this -> x_coor);
	}
	else if(abs(this -> x_coor - rhs.x_coor) <= EPSILON && abs(this -> y_coor - rhs.y_coor) <= EPSILON){
		return 0;	
	}
}

bool Particle::operator== (const Particle& rhs) const{
	if(abs(this -> x_coor - rhs.x_coor) < EPSILON && abs(this -> y_coor - rhs.y_coor) < EPSILON){
		return true;
	}
	else{
		return false;
	}
}

ostream& operator<<(ostream& os, const Particle& particle){
	os << "(" << particle.X() << "," << particle.Y() << ")";
	return os;
}