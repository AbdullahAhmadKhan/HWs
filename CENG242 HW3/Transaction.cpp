#include "Transaction.h"

Transaction::Transaction(){
	this -> _amount = -1;
	this -> _date = -1; 
}

Transaction::Transaction(double amount, time_t date){
	this -> _amount = amount;
	this -> _date = date;
}

Transaction::Transaction(const Transaction& rhs){
	this -> _amount = rhs._amount;
	this -> _date = rhs._date;
}

bool Transaction::operator<(const Transaction& rhs) const{
	if(this -> _date < rhs._date){
		return true;
	}
	return false;
}

bool Transaction::operator>(const Transaction& rhs) const{
	if(this -> _date > rhs._date){
		return true;
	}
	return false;
}

bool Transaction::operator<(const time_t date) const{

	if(this -> _date < date){
		return true;
	}
	return false;
}

bool Transaction::operator>(const time_t date) const{
	if(this -> _date > date){
		return true;
	}
	return false;
}

double Transaction::operator+(const Transaction& rhs){
	double result = (this -> _amount) + rhs._amount;
	return result;
}

double Transaction::operator+(const double add){
	double result = (this -> _amount) + add;
	return result;
}

Transaction& Transaction::operator=(const Transaction& rhs){
	this -> _amount = rhs._amount;
	this -> _date = rhs._date;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Transaction& transaction){
	tm *output = localtime(&(transaction._date));
	os << transaction._amount << "\t" << "-" << "\t" << output -> tm_hour << ":" << output -> tm_min << ":" << output -> tm_sec << "-" << output -> tm_mday << "/" << output -> tm_mon + 1 << "/" << 1900 + output -> tm_year << std::endl;
	return os;
}