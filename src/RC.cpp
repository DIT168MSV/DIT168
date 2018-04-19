#include <iostream>
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

int main(int argc, char **argv) {

    cluon::OD4Session od4(192, [](cluon::data::Envelope &&envelope) noexcept {});

    float value{0};
    unsigned char choice;

    std::cout << "  Group 8 RemoteControl " << std::endl;
    std::cout << "                       " << std::endl;
    std::cout << "    Keys to use        " << std::endl;
    std::cout << "           w           " << std::endl;
    std::cout << "    a             d    " << std::endl;
    std::cout << "           s           " << std::endl;
    std::cout << "                       " << std::endl;


    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        opendlv::proxy::GroundSteeringReading msgSteering;
        opendlv::proxy::PedalPositionReading msgPedal;


        std::cin >> choice;

        switch (choice) {
            case 'w':   std::cout << "case W" << std::endl;
                msgSteering.steeringAngle(0.0);
                if (value < 0){
                    value = 0.05;
                }
                    else if (value <= 0.4) {
                    value += 0.05;
                    }   else {
                    std::cout << "full speed reached" << std::endl;
                }
                    msgPedal.percent(value);
                    break;

            case 'a':   std::cout << "case a" << std::endl;
                if (value >= 0.25) {
                        value = 0.15;
                    }
                    msgPedal.percent(value);
                    msgSteering.steeringAngle(45);
                    break;

            case 's': std::cout << "case s" << std::endl;
                if (value >= 0.05) {
                    value -= 0.05;
                } else {
                    std::cout << "full stop reached" << std::endl;
                }
                msgPedal.percent(value);
                msgSteering.steeringAngle(0);
                break;

            case 'd':   std::cout << "case d" << std::endl;
                if (value >= 0.25) {
                    value = 0.15;
                    }
                    msgPedal.percent(value);
                    msgSteering.steeringAngle(-45);
                    break;
            case 'r':   if (value == 0){value =-1;}
                        msgPedal.percent(value);
                        msgSteering.steeringAngle(0.0);
                        break;

            default:    value = 0;
                    msgPedal.percent(value);
                    msgSteering.steeringAngle(0);
            }
            if(value > 0 && value < 0.05){
                std::cout << "Sending pedalPosition : 0%." << std::endl;
        }
                else if (value < 0 ){std::cout << "Reverse : -1%." << std::endl;}
        else{
        std::cout << "Sending pedalPosition :" << value * 100 << "%." << std::endl;
            }
        od4.send(msgPedal);
        std::cout << "Sending steeringAngle: " << msgSteering.steeringAngle() << std::endl;
        od4.send(msgSteering);
    }

    return 0;
}
