#include <iostream>
#include "cluon/UDPSender.hpp"
#include <string>
using namespace std;

int main(int /*argc*/, char** /*argv*/){

	while(1){
	string mystr;
	cout << "Enter a number: ";
	getline (cin, mystr);

    cluon::UDPSender sender{"127.0.0.1", 1234};
    sender.send(std::move(mystr));

	}

    return 0;
}