#include <iostream>
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

int main(int argc, char **argv) {

	uint16_t const CID {192};

	std::shared_ptr<cluon::OD4Session> od4;

    od4 = std::make_shared<cluon::OD4Session>(CID, [](cluon::data::Envelope &&envelope) noexcept {});

    float pedalValue{0};
    float steeringValue{0};
    float offSet{0.13};
    unsigned char choice;

    std::cout << "  Group 8 RemoteControl" << std::endl;
    std::cout << "                       " << std::endl;
    std::cout << "      Keys to use      " << std::endl;
    std::cout << "           w           " << std::endl;
    std::cout << "    a             d    " << std::endl;
    std::cout << "           s           " << std::endl;
    std::cout << "                       " << std::endl;

	while (1) {
       
        opendlv::proxy::GroundSteeringReading msgSteering;
        opendlv::proxy::PedalPositionReading msgPedal;

        system("/bin/stty raw");
        choice = getchar();
        system("/bin/stty cooked");

        switch (choice) {
            case 'w':   
                if(pedalValue <= 0){
                    std::cout << "ACCELERATING" << std::endl;
                    pedalValue = 0.10;
                }
                else if(pedalValue <= 0.35){
                    std::cout << "ACCELERATING" << std::endl;
                    pedalValue += 0.02;
                }      
                else{
                    std::cout << "FULL SPEED REACHED" << std::endl;
                }
                msgPedal.percent(pedalValue);
                msgSteering.steeringAngle(steeringValue);
                break;

            case 'a':
                if(steeringValue == offSet){
                    std::cout << "TURNING LEFT" << std::endl;
                    steeringValue = (offSet + 90);
                }
                else if(steeringValue < offSet){
                    std::cout << "GOING STRAIGHT" << std::endl;
                    steeringValue = offSet;
                }
                msgPedal.percent(pedalValue);
                msgSteering.steeringAngle(steeringValue);
                break;

            case 's': 
                if(pedalValue > 0.11){
                    std::cout << "DECELERATING" << std::endl;
                    pedalValue -= 0.02;
                } 
                else{
                    std::cout << "STOPPED" << std::endl;
                    pedalValue = 0;
                }
                msgPedal.percent(pedalValue);
                msgSteering.steeringAngle(steeringValue);
                break;

            case 'd':   
                if(steeringValue == offSet){
                    std::cout << "TURNING RIGHT" << std::endl;
                    steeringValue = (offSet - 75);
                }
                else if(steeringValue > offSet){
                    std::cout << "GOING STRAIGHT" << std::endl;
                    steeringValue = offSet;
                }
                msgPedal.percent(pedalValue);
                msgSteering.steeringAngle(steeringValue);
                break;

            case 'r':
                pedalValue = (-0.50);
                msgPedal.percent(0);
                od4->send(msgPedal);
                msgPedal.percent(pedalValue);
                msgSteering.steeringAngle(steeringValue);
                break;

            case 'x': 
                pedalValue = 0;
                steeringValue = offSet;
                msgPedal.percent(pedalValue);
                msgSteering.steeringAngle(steeringValue);
                od4->send(msgPedal);
                od4->send(msgSteering);
                exit(0);
                break;

            default:    
                pedalValue = 0;
                steeringValue = offSet;
                msgPedal.percent(pedalValue);
                msgSteering.steeringAngle(steeringValue);
            }

        std::cout << "SteeringAngle: " << msgSteering.steeringAngle() << " PedalPosition: " << msgPedal.percent() << std::endl;

        od4->send(msgPedal);
        od4->send(msgSteering);
    }
    return 0;
}
