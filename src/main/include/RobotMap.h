//From BaseBot, questionable but probably useful
#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 * Use static constants whenever possible to reduce memory useage
 */

struct RobotMap {
    //Change motor type in BoomMax.h to brushed or brushless
    static const int FrontLeftSparkMaxID = 4;
    static const int FrontRightSparkMaxID = 1;
    static const int BackLeftSparkMaxID = 3;
    static const int BackRightSparkMaxID = 2;
    static const int XBoxControllerDrivePort = 0;
    static constexpr double MaxSpeed = 2.25; //Lower is higher
    static constexpr double TimeToGoOneFoot = .52;
    //static const int XBoxControllerOperatorPort = 1;
};

#endif // _ROBOTMAP_HG_