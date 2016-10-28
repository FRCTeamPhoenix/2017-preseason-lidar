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
#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x04          // Value to initiate ranging.
#define RegisterHighLowB 0x8f // Register to get both High and Low bytes in 1 call.

#include <cstdint>
#include "WPILib.h"

class Lidar
{
    int m_mode;

    double m_distance;

    double m_fastAverage;
    double m_slowAverage;

    I2C *m_I2C;

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
