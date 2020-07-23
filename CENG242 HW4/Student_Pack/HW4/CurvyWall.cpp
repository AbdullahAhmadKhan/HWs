#include "CurvyWall.h"

CurvyWall::CurvyWall(float f1, float f2): Wall(f1) {
	this -> length = f1;
	this -> radius = f2;
	center_point = NULL;
	start_point = NULL;
	end_point = NULL;
}

CurvyWall::CurvyWall(const Particle& s_p, const Particle& e_p, const Particle& c_p): Wall(s_p, e_p){
	this -> center_point = new Particle(c_p);
	this -> radius = c_p.FindDistance(s_p);
	this -> ComputeLength();
}

CurvyWall::CurvyWall(const CurvyWall& rhs): Wall(*(rhs.start_point), *(rhs.end_point)){
	if(rhs.center_point != NULL){
		this -> center_point = new Particle(*(rhs.center_point));
	}
	else{
		this -> center_point = NULL;
	}
	this -> radius = rhs.radius;	
	this -> length = rhs.length;	
}

float CurvyWall::GetRadius() const{
	return radius;
}

const Particle& CurvyWall::GetCenter() const{
	return *center_point;
}

void CurvyWall::ComputeLength(){
//	cout << "hi";
//	cout << this -> start_point -> Y() << endl;
//	cout << this -> end_point -> Y() << endl;
	if(abs(this -> start_point -> X() - this -> end_point -> X()) < EPSILON && abs(this -> start_point -> Y() - this -> end_point -> Y()) < EPSILON){
		//cout << "YES";
		//cout << radius;
		this -> length = 2 * PI * (this -> radius) + 0.004;
		//cout << length << endl;
		return;
	}
	//cout << "Hey";
	//cout << *this -> start_point << *this -> end_point << endl;

	float radian1 = atan2(start_point -> Y() - center_point -> Y(), start_point -> X() - center_point -> X());
	float radian2 = atan2(end_point -> Y() - center_point -> Y(), end_point -> X() - center_point -> X());
	/*float angle1 = radian1 * 180.0 / PI + 180;
	float angle2 = radian2 * 180.0 / PI + 180;*//*
	float a = start_point -> FindDistance(*center_point);
	float b = start_point -> FindDistance(*end_point); 				Bu sehvdir
	float c = end_point -> FindDistance(*center_point);
	float theta = acos((a * a + c * c - b * b) / 2 * a * c) * 180.0 / PI;*/
	float theta;
	theta = abs(radian2 - radian1);
	this -> length = (this -> radius) * theta;
}

Wall* CurvyWall::Clone() const{
	CurvyWall* clone = new CurvyWall(*this);
	return clone;
}

bool CurvyWall::IsContinuousLinear(const Wall&) const{
	return false;
}

const Wall& CurvyWall::operator+(const Wall& rhs) const{
	if(rhs.GetLength() != rhs.GetInitialParticle().FindDistance(rhs.GetFinalParticle()) && *(rhs.center_point) == *(this -> center_point)){
		if(this -> GetInitialParticle() == rhs.GetFinalParticle()){
			Wall* result = this -> Clone();
			delete result -> start_point;
			delete result -> end_point;
			result -> start_point = new Particle(rhs.GetInitialParticle());
			result -> end_point = new Particle(*(this -> end_point));
			return *result;
		}
		else if(this -> GetFinalParticle() == rhs.GetInitialParticle()){
			Wall* result = this -> Clone();
			delete result -> start_point;
			delete result -> end_point;
			result -> start_point = new Particle(*(this -> start_point));
			result -> end_point = new Particle(rhs.GetFinalParticle());
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

CurvyWall::~CurvyWall(){
	
}