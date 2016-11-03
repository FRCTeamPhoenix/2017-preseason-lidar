/*
 * Lidar.cpp
 *
 *  Created on: Oct 24, 2016
 *      Author: cooli
 */

#include <Lidar.h>

Lidar::Lidar(uint32_t lidarPort, int mode):
    m_mode(mode),
    m_distance(0),
    m_fastAverage(0),
    m_slowAverage(0)
{
    // TODO Auto-generated constructor stub
    m_I2C = new I2C(I2C::kOnboard, LIDARLite_ADDRESS);
}

void Lidar::run() {
    byte nackack = 100;
    while (nackack != 0) {
        nackack = m_I2C -> Write(RegisterMeasure, MeasureValue);
        Wait(0.001);
    }
    byte distanceArray[2];
    nackack = 100;
    while (nackack != 0) {
        nackack = m_I2C -> Read(RegisterHighLowB, 2, distanceArray);
        Wait(0.001);
    }
    std::ostringstream ss;
    int distance = (distanceArray[0] << 8) + distanceArray[1];
    ss << distance;
    SmartDashboard::PutString("DB/String 1",ss.str());
}

Lidar::~Lidar()
{
    delete m_I2C;
}

