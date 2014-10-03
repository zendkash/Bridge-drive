#include "ControlAlgorithm.h"
#include "../Drives/Drive.h"
#include "../Sensors/Sensor.h"

class SwerveControlAlgorithm: public ControlAlgorithm
{
private:
    int count;
    bool swerve;
public:
    SwerveControlAlgorithm(Sensor* sens, Drive* drv);
    void process();
};