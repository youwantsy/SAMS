#pragma once

struct Position {
    double x;
    double y;
    template<typename Ar> void serialize(Ar& ar, unsigned) { ar& x& y; }
};

struct Message {
    int id;
    int data1;
    Position data2;
    Position data3;
    bool data4;
    double data5;
    Position data6;
    Position data7;
    double data8;
    double data9;

    template<typename Ar> void serialize(Ar& ar, unsigned) { ar& id& data1& data2& data3& data4& data5& data6& data7& data8& data9; }
}; 

class CommunicationManager
{
    
public:
    Message message;
    int getCurrentMissileNum();
    void sendOCS(const Message& message);
    void sendGMS(const Message& message);
    Message receiver();
};