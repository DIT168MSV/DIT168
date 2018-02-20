#include <chrono>
#include <iostream>
#include "oddEvenChecker.hpp"
#include "cluon/UDPReceiver.hpp"

int main(int /*argc*/, char** /*argv*/){
    std::cout<< "Waiting for input" << std::endl;

    cluon::UDPReceiver receiver("127.0.0.1", 1234,
    	[](std::string &&data, std::string &&/*from*/,
    	std::chrono::system_clock::time_point &&/*timepoint*/) noexcept {

        OddEvenChecker n;
        if(n.isEven(std::stoi(data))){
            std::cout<< "The number " <<data<< " is even" << std::endl;
        }
        else{
            std::cout<< "The number " <<data<<" is odd" << std::endl;
        }

	});

	using namespace std::literals::chrono_literals;
	while(receiver.isRunning()) {
		std::this_thread::sleep_for(1s);
	}

    return 0;
}