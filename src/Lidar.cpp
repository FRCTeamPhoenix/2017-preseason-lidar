/*
 * Lidar.cpp
 *
 *  Created on: Oct 24, 2016
 *      Author: cooli
 */

#include <Lidar.h>

Lidar::Lidar(uint32_t lidarPort, Relay * onSwitch, int mode):
m_counter(lidarPort),
m_mode(mode),
m_distance(0),
m_fastAverage(0),
m_slowAverage(0)
{
    // TODO Auto-generated constructor stub
    m_I2C = new I2C(I2C::kOnboard, LIDARLite_ADDRESS);
    m_counter.SetSemiPeriodMode(true);
}

double Lidar::getFastAverage() {
   return m_fastAverage;
}

double Lidar::getSlowAverage() {
   return m_slowAverage;
}

void Lidar::run() {
    if (m_mode == 0) {
        byte nackack = 100;
        while (nackack != 0) {
            nackack = m_I2C -> Write(RegisterMeasure, MeasureValue);
            Wait(0.01);
        }
        byte distanceArray[2];
        nackack = 100;
        while (nackack != 0) {
            nackack = m_I2C -> Read(RegisterHighLowB, 2, distanceArray);
            Wait(0.01);
        }
        std::ostringstream ss;
        int distance = (distanceArray[0] << 8) + distanceArray[1];
        ss << distance;
        SmartDashboard::PutString("DB/String 1",ss.str());
    }

    if (m_mode == 1) {
        m_distance = m_counter.GetPeriod() * 39370.0787;
        double fast = 5.0;
        m_fastAverage = (fast * m_fastAverage + m_distance) / (fast + 1.0);
        double slow = 25.0;
        m_slowAverage = (slow * m_slowAverage + m_distance) / (slow + 1.0);
    }
}

Lidar::~Lidar()
{
    delete m_I2C;
}

