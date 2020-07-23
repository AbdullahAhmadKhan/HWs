#include "SoftCopy.h"
/* YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. DO NOT MODIFY THE HEADER FILE AS IT WILL BE
REPLACED BY THE ORIGINAL HEADER DURING TESTING. THE REQUIRED
HEADER FILE IS ALREADY INCLUDED FOR YOU ABOVE THIS COMMENT BLOCK.
THE CONSTRUCTOR and DESTRUCTOR ARE ALREADY IMPLEMENTED.
START YOUR IMPLEMENTATIONS BELOW THOSE. */


// DONE
SoftCopy::SoftCopy(int ISBN, double price, int startPage, int endPage) : Book(ISBN, price) {
	this->startPage = startPage;
	this->endPage = endPage;
	this->numberOfPages = (endPage - startPage) + 1;
	this->firstHalf = NULL;
	this->secondHalf = NULL;
	this->pageContent = "";
}

// DONE
SoftCopy::~SoftCopy() {
	if (firstHalf != NULL)
		delete firstHalf;
	if (secondHalf != NULL)
		delete secondHalf;
}

SoftCopy* SoftCopyHelper(SoftCopy* arg){
	if(arg == NULL){
		return NULL;
	}
	SoftCopy* result = new SoftCopy(*arg);
	return result;
}

SoftCopy::SoftCopy(const SoftCopy& rhs){
	this -> startPage = rhs.startPage;
	this -> endPage = rhs.endPage;
	this -> numberOfPages = rhs.numberOfPages;
	this -> firstHalf = SoftCopyHelper(rhs.firstHalf);
	this -> secondHalf = SoftCopyHelper(rhs.secondHalf);
	this -> pageContent = rhs.pageContent;

	this -> ISBN = rhs.ISBN;
	this -> next = rhs.next;
	this -> price = rhs.price;
}

SoftCopy& SoftCopy::operator=(const SoftCopy& rhs){
	if(this -> firstHalf != NULL){
		delete this -> firstHalf;
	}
	if(this -> secondHalf != NULL){
		delete this -> secondHalf;
	}


	this -> startPage = rhs.startPage;
	this -> endPage = rhs.endPage;
	this -> numberOfPages = rhs.numberOfPages;
	this -> firstHalf = SoftCopyHelper(rhs.firstHalf);
	this -> secondHalf = SoftCopyHelper(rhs.secondHalf);
	this -> pageContent = rhs.pageContent;

	this -> ISBN = rhs.ISBN;
	this -> next = rhs.next;
	this -> price = rhs.price;

	return *this;
}

SoftCopy& SoftCopy::operator+(const SoftCopy& rhs) const{
	if(rhs.firstHalf == NULL && rhs.secondHalf == NULL && rhs.startPage == rhs.endPage){
	    SoftCopy* result = new SoftCopy(*this);
	    result -> UploadPage(rhs.pageContent, rhs.startPage);
	    return *result;
	}
	else{
	    if(rhs.firstHalf == NULL){
	        return *this + *(rhs.secondHalf);
	    }
	    else if(rhs.secondHalf == NULL){
	        return *this + *(rhs.firstHalf);
	    }
	    else{
	        SoftCopy* result_l = const_cast<SoftCopy*>(&(*this + *(rhs.firstHalf)));
    	    SoftCopy* result = const_cast<SoftCopy*>(&(*result_l + *(rhs.secondHalf)));
    	    delete result_l;
    	    return *result;
	    }
	}
}

Book* SoftCopy::Clone() const{
	return NULL;
}

void SoftCopy::Discount(){
    this -> price = (this -> price) * 0.75;
}

void SoftCopy::UploadPage(string s, int num){
    if(this -> startPage == num && this -> endPage == num){
		pageContent = s;
	}
	
	else{
	    if(num <= (((this -> endPage) + (this -> startPage)) / 2) && num >=  (this -> startPage)){
    	    if(this -> firstHalf != NULL){
    	        firstHalf -> UploadPage(s, num);
    	    }
    	    else{
    	        this -> firstHalf = new SoftCopy(ISBN, price, this -> startPage, ((this -> endPage) + (this -> startPage)) / 2);
    		    firstHalf -> UploadPage(s, num);
    		}
    	}
    	
    	else if(num > (((this -> endPage) + (this -> startPage)) / 2) && num <= (this -> endPage)){
            if(this -> secondHalf != NULL){
    	        secondHalf -> UploadPage(s, num);
    	    }
    	    else{
    	        this -> secondHalf = new SoftCopy(ISBN, price, ((this -> endPage) + (this -> startPage)) / 2 + 1, this -> endPage);
    		    secondHalf -> UploadPage(s, num);
    		}
    	}
    	else{
    	    return;
    	}
	}
}

string SoftCopy::Display(int from, int to) const{
    string result = "";
    int temp = 0, deleted = 0;
    
    /*if(this -> firstHalf == NULL){
        if(startPage == (startPage + endPage) / 2 && startPage != endPage){
            if(startPage == to || endPage == to){
                deleted += 1;
                result += "\b";
            }
        }
    }*/
    
    if(this -> firstHalf != NULL){
        if(result.length() != 0 && ((this -> firstHalf) -> Display(from, to)).length() != 0){
            result += "\n";
        }
        result += (this -> firstHalf) -> Display(from, to);
    }
    else{
        if(this -> secondHalf == NULL){
            temp += 1;
            if(this -> startPage >= from && this -> endPage <= to && startPage == endPage){
                result += this -> pageContent;
                /*if(this -> endPage < to){
                    result += "\n";
                }*/
            }
        }
    }
    
    /*if(deleted == 0){
        if(this -> secondHalf == NULL){
            if(startPage == (startPage + endPage) / 2 && startPage != endPage){
                if(startPage == to || endPage == to){
                    result += "\b";
                }
            }
        }
    }*/
    
    if(this -> secondHalf != NULL){
        if(result.length() != 0 && ((this -> secondHalf) -> Display(from, to)).length() != 0){
            result += "\n";
        }
        result += (this -> secondHalf) -> Display(from, to);
    }
    else{
        if(this -> firstHalf == NULL){
            if(temp == 0){
                if(this -> startPage >= from && this -> endPage <= to && startPage == endPage){
                    result += this -> pageContent;
                    /*if(this -> endPage < to){
                        result += "\n";
                    }*/
                }
            }
        }
    }
    
    
    return result;
}