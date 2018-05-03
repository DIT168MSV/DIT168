#include <iostream>
#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

int main(int argc, char **argv) {
    int retCode{0};
    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
    if (0 == commandlineArguments.count("right") || 0 == commandlineArguments.count("left")) {
        std::cerr << argv[0] << " The RC for the manual steering " << std::endl;
        std::cerr << "Usage:   " << argv[0]
                  << " --right=<the amount of right steering value> --left=<the amount of left steering value>" << std::endl;
        std::cerr << "Example: " << argv[0] << " --right=0.65 --left=0.6" << std::endl;
        retCode = 1;
    } else {

        const float RIGHT = std::stof(commandlineArguments["right"]);
        const float LEFT = std::stof(commandlineArguments["left"]);

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
/**
* We use "stty" to get the raw input so we don't need to press enter every time
* we want to give the car a new command. after we do cooked to not mess up
* the terminal output.
**/
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
                    steeringValue = (offSet + LEFT);
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
                    steeringValue = (offSet - RIGHT);
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
}
