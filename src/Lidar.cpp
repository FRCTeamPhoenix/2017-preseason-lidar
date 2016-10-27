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

}

Lidar::~Lidar()
{
    // TODO Auto-generated destructor stub
}

