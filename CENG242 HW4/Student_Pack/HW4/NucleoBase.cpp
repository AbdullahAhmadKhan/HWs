#include "NucleoBase.h"

NucleoBase::NucleoBase(string str, NucleoBase* nucleobase){
	this -> chain = str;
	this -> prev = nucleobase;
	this -> next = NULL;
	this -> SetPrevNext();
}

NucleoBase::NucleoBase(const NucleoBase& rhs){
	this -> chain = rhs.chain;
	if(rhs.prev != NULL){
		this -> prev = new NucleoBase(*rhs.prev);
	}
	else{
		this -> prev = NULL;
	}
	if(rhs.next != NULL){
		this -> next = new NucleoBase(*rhs.next);
	}
	else{
		this -> next = NULL;
	}
}

NucleoBase::~NucleoBase(){
	this -> prev = NULL;
	this -> next = NULL;
}

void NucleoBase::SetPrevNext(){
	if(this -> prev != NULL){
		this -> prev -> next = this;
	}
}

NucleoBase* NucleoBase::GetLast(){
	NucleoBase* curr = this;
	while(curr -> next != NULL){
		curr = curr -> next;
	}
	return curr;
}

ostream& operator<<(ostream& os, const NucleoBase& nucleobase){
	NucleoBase* curr = const_cast<NucleoBase*>(&nucleobase);
	while(curr -> prev != NULL){
		curr = curr -> prev;
	}

	while(curr != NULL){
		os << curr -> chain;
	}
	return os;
}