#include <iostream>
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

int main(int argc, char **argv) {

	uint16_t const CID {192};
	const float FREQ {2.0f};
	std::shared_ptr<cluon::OD4Session> od4;


    od4 = std::make_shared<cluon::OD4Session>(CID, [](cluon::data::Envelope &&envelope) noexcept {});

    float pedalValue{0};
    unsigned char choice;

    std::cout << "  Group 8 RemoteControl " << std::endl;
    std::cout << "                       " << std::endl;
    std::cout << "    Keys to use        " << std::endl;
    std::cout << "           w           " << std::endl;
    std::cout << "    a             d    " << std::endl;
    std::cout << "           s           " << std::endl;
    std::cout << "                       " << std::endl;

	while (1) {
       
        opendlv::proxy::GroundSteeringReading msgSteering;
        opendlv::proxy::PedalPositionReading msgPedal;


        std::cin >> choice;

        switch (choice) {
            case 'w':   msgSteering.steeringAngle(0.0);
                if (pedalValue <= 0){
                    pedalValue = 0.10;
                     std::cout << " YOU ARE NOW ACCELERATING..." << std::endl;
                }
                    else if (pedalValue <= 0.35) {
                    pedalValue += 0.02;
                    std::cout << "YOU ARE NOW ACCELERATING..." << std::endl;
                    }   else {
                    std::cout << "full speed reached" << std::endl;
                }
                    msgPedal.percent(pedalValue);
                    break;

            case 'a':   std::cout << "YOU JUST TURN LEFT..." << std::endl;
                if (pedalValue >= 0.15) {
                        pedalValue = 0.15;
                    }
                    msgPedal.percent(pedalValue);
                    msgSteering.steeringAngle(45);
                    break;

            case 's': if (pedalValue > 0.11) {
                    pedalValue -= 0.02;
                    std::cout << "YOU ARE NOW DECELERATING..." << std::endl;
                } else {
                    pedalValue = 0;
                    std::cout << "FULL STOP REACHED" << std::endl;
                }
                msgPedal.percent(pedalValue);
                msgSteering.steeringAngle(0);
                break;

            case 'd':   std::cout << "YOU JUST TURNED RIGHT..." << std::endl;
                if (pedalValue >= 0.15) {
                    pedalValue = 0.15;
                    }
                    msgPedal.percent(pedalValue);
                    msgSteering.steeringAngle(-45);
                    break;

            case 'x': pedalValue = 0;
                    msgPedal.percent(pedalValue);
                    od4->send(msgPedal);
                     exit(0);
                     break;

            default:    pedalValue = 0;
                    msgPedal.percent(pedalValue);
                    msgSteering.steeringAngle(0);
            }
            if(pedalValue > 0 && pedalValue < 0.02){
                std::cout << "with pedalPosition : 0 %." << std::endl;
        }
                else if (pedalValue < 0 ){std::cout << "Reverse : -1%." << std::endl;}
        else{
        std::cout << "with pedalPosition : " << pedalValue * 100 << "%." << std::endl;
            }
        od4->send(msgPedal);
        std::cout << "with steeringAngle: " << msgSteering.steeringAngle() << std::endl;
        od4->send(msgSteering);
    }
    return 0;
}
