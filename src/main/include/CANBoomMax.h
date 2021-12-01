#include <rev/CANSparkMax.h>

class BoomMax : public rev::CANSparkMax{
    public:
    BoomMax(int deviceID, bool backward)
        : CANSparkMax(deviceID, rev::CANSparkMax::MotorType::kBrushed){
            SetClosedLoopRampRate(.5);
            SetOpenLoopRampRate(.5);
            SetInverted(backward);
            SetCANTimeout(0);
            SetControlFramePeriodMs(95);
        }
};