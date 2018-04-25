#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "cluon/UDPReceiver.hpp"
#include "messages.hpp"
#define MAX 11

using namespace std::chrono;

int main(int /*argc*/, char** /*argv*/) {
std::shared_ptr<cluon::OD4Session> incom, excom;
    uint16_t const In_CID = 191;
    uint16_t const Ex_CID = 192;
    const float FREQ {2.0f};
    uint16_t sensor_dist[MAX];
    uint8_t iterator {0};
    const float dist_average;



   auto last = std::chrono::high_resolution_clock::now();
    
    incom = std::make_shared<cluon::OD4Session>(In_CID,[](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
            opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            std::cout << "Sent a message for ground steering to " << receivedMsg.steeringAngle() << "." << std::endl;
        }
        else if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
            opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            std::cout << "Sent a message for pedal position to " << receivedMsg.percent() << "." << std::endl;
        }
        else if (envelope.dataType() == opendlv::proxy::DistanceReading::ID()) {
          opendlv::proxy::DistanceReading sonic = cluon::extractMessage<opendlv::proxy::DistanceReading>(std::move(envelope));
            // Ultrasonic reading
            std::cout << "Distance from USonic reading " << sonic.distance() << "." << std::endl;
        }
    });

    excom = std::make_shared<cluon::OD4Session>(Ex_CID,[&last,&incom](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
            opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            std::cout << "Recieved a message for ground steering to " << receivedMsg.steeringAngle() << "." << std::endl;
            
            opendlv::proxy::GroundSteeringReading msgSteering;
            msgSteering.steeringAngle(receivedMsg.steeringAngle());
            last = std::chrono::high_resolution_clock::now();
            incom->send(msgSteering);

        }
        else if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
            opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            std::cout << "Recieved a message for pedal position to " << receivedMsg.percent() << "." << std::endl;
            
            opendlv::proxy::PedalPositionReading msgPedal;
            msgPedal.percent(receivedMsg.percent());
            last = std::chrono::high_resolution_clock::now();
            incom->send(msgPedal);

        }else if (envelope.dataType() == opendlv::proxy::DistanceReading::ID()) {
          opendlv::proxy::DistanceReading sonic = cluon::extractMessage<opendlv::proxy::DistanceReading>(std::move(envelope));
            // Ultrasonic reading
            sensor_dist[iterator] {sonic.distance()};
            iterator++;
            if (iterator == MAX) iterator = 0;
            dist_average {0};
            for (int i {0}; i < 11; i++){
                dist_average += sensor_dist[i];
                dist_average /= MAX;
                std::cout << dist_average << std::endl;
            }

            if (dist_average <= 25){
            opendlv::proxy::GroundSteeringReading msgSteering;
            opendlv::proxy::PedalPositionReading msgPedal;
        
                msgPedal.percent(0);
                msgSteering.steeringAngle(0);
                sonic.distance(dist_average);
                incom->send(msgSteering);
                incom->send(msgPedal);
                income->send(sonic);
                
            }
        }    
    });
        auto safetyTimer{[&incom, &last]() -> bool {
            opendlv::proxy::GroundSteeringReading msgSteering;
            opendlv::proxy::PedalPositionReading msgPedal;
            auto dur = std::chrono::high_resolution_clock::now() - last;
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
            if (ms >= 2000) {
                msgPedal.percent(0);
                msgSteering.steeringAngle(0);
                incom->send(msgSteering);
                incom->send(msgPedal);
                last = std::chrono::high_resolution_clock::now();
            }
            return true;
        }};
        incom->timeTrigger(FREQ, safetyTimer);
    
    return 0;
}
