#include <iostream>
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

int main(int argc, char** argv) {

    cluon::OD4Session od4(112, [](cluon::data::Envelope &&envelope) noexcept {});

      while (1) {
        opendlv::proxy::GroundSteeringReading msgSteering;
        opendlv::proxy::PedalPositionReading msgPedal;

        std::string choice;
        std::getline(std::cin, choice);
        
            switch (choice.at(0)) {
                case 'w':   msgPedal.percent(0.5);
                            msgSteering.steeringAngle(0);   
                            break;
                case 'a':   msgPedal.percent(0.25);
                            msgSteering.steeringAngle(45);  
                            break;
                case 's':   msgPedal.percent(0);
                            msgSteering.steeringAngle(0);  
                            break;
                case 'd':   msgPedal.percent(0.25);
                            msgSteering.steeringAngle(-45);
                            break;
                default:    msgPedal.percent(0);
                            msgSteering.steeringAngle(0);
            }

            std::cout << "Sending pedalPosition: " << msgPedal.percent() << std::endl;
            od4.send(msgPedal);

            std::cout << "Sending steeringAngle: " <<msgSteering.steeringAngle() << std::endl;
            od4.send(msgSteering);
        }

       return 0;
    }