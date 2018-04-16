#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "cluon/UDPReceiver.hpp"
#include "messages.hpp"

int main(int /*argc*/, char** /*argv*/) {

    uint16_t const In_CID = 191;
    uint16_t const Ex_CID = 192;

    std::shared_ptr<cluon::OD4Session> incom, excom;

    incom = std::make_shared<cluon::OD4Session>(In_CID,[](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
            opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            std::cout << "Sent a message for ground steering to " << receivedMsg.steeringAngle() << "." << std::endl;
        }
        else if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
            opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            std::cout << "Sent a message for pedal position to " << receivedMsg.percent() << "." << std::endl;
        }
    });

    excom = std::make_shared<cluon::OD4Session>(Ex_CID,[&](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
            opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            std::cout << "Recieved a message for ground steering to " << receivedMsg.steeringAngle() << "." << std::endl;
            
            opendlv::proxy::GroundSteeringReading msgSteering;
            msgSteering.steeringAngle(receivedMsg.steeringAngle());
            incom->send(msgSteering);

        }
        else if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
            opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            std::cout << "Recieved a message for pedal position to " << receivedMsg.percent() << "." << std::endl;
            
            opendlv::proxy::PedalPositionReading msgPedal;
            msgPedal.percent(receivedMsg.percent());
            incom->send(msgPedal);

        }
    });
    while(1){
        /*
        HAHAH
        */
    }
    return 0;
}
