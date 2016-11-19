/*
 * Lidar.cpp
 *
 *  Created on: Oct 24, 2016
 *      Author: cooli
 */

#include <Lidar.h>

Lidar::Lidar(uint32_t triggerPin, uint32_t monitorPin, int mode):
m_monitorPin(monitorPin),
m_mode(mode),
m_distance(0),
m_fastAverage(0),
m_slowAverage(0),
m_triggerPin(triggerPin)
{
    // TODO Auto-generated constructor stub
    m_I2C = new I2C(I2C::kMXP, LIDARLite_ADDRESS);
    m_monitorPin.SetSemiPeriodMode(true);
    m_triggerPin.Set(0);
    m_counter = 0;
    m_status = 0;
}

double Lidar::getFastAverage() {
   return m_fastAverage;
}

double Lidar::getSlowAverage() {
   return m_slowAverage;
}

//void Lidar::run() {
//    m_counter++;
//    if (m_mode == 0) {
//        byte nackack = 1;
//        while (nackack != 0) {
//            nackack = m_I2C -> Write(RegisterMeasure, MeasureValue);
//            Wait(0.01);
//        }
//        byte highByte;
//        byte lowByte;
//        nackack = 1;
//        while (nackack != 0) {
//            nackack = m_I2C -> Read(HighByte, 1, &highByte);
//            Wait(0.01);
//        }
//        nackack = 1;
//        while (nackack != 0) {
//            nackack = m_I2C -> Read(LowByte, 1, &lowByte);
//            Wait(0.01);
//        }
//        int distance = lowByte;
//        //int distance = (highByte << 8) + lowByte;
//        m_distance = distance;
//    }
//
//    if (m_mode == 1) {
//        m_distance = m_monitorPin.GetPeriod() * 39370.0787;
//    }
//    double fast = 5.0;
//    m_fastAverage = m_distance;
//    //m_fastAverage = (fast * m_fastAverage + m_distance) / (fast + 1.0);
//    double slow = 25.0;
//    m_slowAverage = (slow * m_slowAverage + m_distance) / (slow + 1.0);
//}

void Lidar::run() {
    m_counter++;
    byte distanceArray[2];
    while (m_I2C->Write(0x00, 0x04));
    byte distanceRegister_1st[1];
    distanceRegister_1st[0] = 0x8f;
    m_I2C->WriteBulk(distanceRegister_1st, 0x01);
    m_I2C->ReadOnly(2, distanceArray);
    m_distance = (distanceArray[0] << 8) + distanceArray[1];
    m_fastAverage = m_distance;
    m_slowAverage = m_distance;
    Wait(0.004);
}

//void Lidar::run() {
//    m_counter++;
//    while (m_I2C->Read(0x01, 1, &m_status));
//
//    while (m_I2C->Write(0x00, 0x04));
//
//    byte result = 1;
//
//    do {
//        m_I2C->Read(0x01, 1, &result);
//    } while (result & 1);
//
////    Wait(0.1);
//    byte distanceArray[2];
//
//    while (m_I2C->Read(0x10, 1, distanceArray));
//
//    m_distance = (distanceArray[0] << 8) + distanceArray[1];
//    m_distance = ((int)distanceArray[0]);
//    m_fastAverage = m_distance;
//    m_slowAverage = m_distance;
//
//    Wait(1);
//}

Lidar::~Lidar()
{
    delete m_I2C;
}
