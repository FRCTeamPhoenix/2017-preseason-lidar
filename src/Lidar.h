/*
 * Lidar.h
 *
 *  Created on: Oct 24, 2016
 *      Author: cooli
 */

#ifndef SRC_LIDAR_H_
#define SRC_LIDAR_H_

#define MODE_I2C 0
#define MODE_PWM 1

#include <cstdint>

class Lidar
{
    int m_mode;

    double m_distance;

    double m_fastAverage;
    double m_slowAverage;

    public:
        // Make sure to pass in 0 to mode
        Lidar(uint32_t lidarPort, int mode);
        void run();
        double getDistance();
        double getFastAverage();
        double getSlowAverage();
        virtual ~Lidar();
};

#endif /* SRC_LIDAR_H_ */
