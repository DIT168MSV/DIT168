#include <iostream>
#include "oddEvenChecker.hpp"

int main(){
    	OddEvenChecker n;
	int num = 6;
if(n.isEven(num))
    	std::cout<< num << " is even"<< std::endl;
else
	std::cout<< num << " is odd"<< std::endl;
    return 0;
}
