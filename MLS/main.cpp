#include <iostream>
#include "CommunicationManager.h"
#include "StatusManager.h"
#include "MissileLauncher.h"
#include <thread>

int main() {
    CommunicationManager communicationManager;
    MissileLauncher missileLauncher;
    StatusManager statusManager;

    Message message;
    message.id = 4;
    message.data1 = 0xF0;
    message.data2 = { 2, 2 };
    message.data3 = { 3, 3 };
    message.data4 = 0;
    message.data5 = 5;
    message.data6 = { 6, 6 };
    message.data7 = { 2, 2 };
    message.data8 = 8;
    message.data9 = 9;

    std::thread receiverScenario([&communicationManager]() {
        while (true) {
            communicationManager.message = communicationManager.receiver();
           
            std::cout << "Received Message.id:" << communicationManager.message.id << std::endl;
            std::cout << "Received Message.data1" << communicationManager.message.data1 << std::endl;
            std::cout << "Received Message.data2.x" << communicationManager.message.data2.x << std::endl;
            std::cout << "Received Message.data3.x" << communicationManager.message.data3.x << std::endl;
            std::cout << "Received Message.data4" << communicationManager.message.data4 << std::endl;
            std::cout << "Received Message.data5" << communicationManager.message.data5 << std::endl;
            std::cout << "Received Message.data6.x" << communicationManager.message.data6.x << std::endl;
            std::cout << "Received Message.data7.x" << communicationManager.message.data7.x << std::endl;
            std::cout << "Received Message.data8" << communicationManager.message.data8 << std::endl;
            std::cout << "Received Message.data9" << communicationManager.message.data9 << std::endl;
        }});

    receiverScenario.detach();
    
    while (true) {
        statusManager.getMessage(communicationManager.message);


        communicationManager.sendGMS(message);
        communicationManager.sendOCS(message);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    return 0;
}