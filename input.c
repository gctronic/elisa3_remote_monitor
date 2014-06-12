#include "input.h"
#include "terminal.h"
#ifdef _WIN32
    #include "windows.h"
#endif

extern int robotAddress;
extern unsigned int delayCounter;
extern char robLSpeed, robRSpeed;
extern char current_speed;
extern char robRedLed, robGreenLed, robBlueLed;
extern unsigned char robFlagsTx;
extern unsigned char obstacleAvoid, cliffAvoid, irOn, tvOn, sleepOn, smallLedsOn;
extern unsigned char exitProg;

unsigned char HKeyPressed() {
    if(GetKeyState (0x48) < 0) {     // 'h'
        return 1;
    } else {
        return 0;
    }
}

void handleKeyboardInput() {

#ifdef _WIN32
        delayCounter++;
        if(delayCounter>40) {   // wait a little from one command to the other
            delayCounter = 0;

            if (GetKeyState (VK_LEFT) < 0) {
                robRSpeed = current_speed;
                robLSpeed = 0;
            } else if (GetKeyState (VK_RIGHT) < 0) {
                robLSpeed = current_speed;
                robRSpeed = 0;
            } else if (GetKeyState (VK_DOWN) < 0) {
                robLSpeed = -current_speed;
                robRSpeed = -current_speed;
            } else if (GetKeyState (VK_UP) < 0) {
                robLSpeed = current_speed;
                robRSpeed = current_speed;
            } else if (GetKeyState (VK_ADD) < 0) {
                current_speed += 5;
                if(current_speed > 100) {
                    current_speed = 100;
                }
            } else if (GetKeyState (VK_SUBTRACT) < 0) {
                current_speed -= 5;
                if(current_speed < -100) {
                    current_speed = -100;
                }
            } else if (GetKeyState (VK_SPACE) < 0) {
                current_speed = 0;
                robRedLed = 0;
                robGreenLed = 0;
                robBlueLed = 0;
                robFlagsTx = 0;
                turnOffSmallLeds(robotAddress);
                resetFlagTX(robotAddress);
            } else if (GetKeyState (0x41) < 0) {    // 'a'
                robLSpeed = -current_speed;
                robRSpeed = current_speed;
            } else if (GetKeyState (0x53) < 0) {    // 's'
                robLSpeed = current_speed;
                robRSpeed = -current_speed;
            } else if (GetKeyState (0x52) < 0) {    // 'r'
                robRedLed++;
                if(robRedLed > 100) {
                    robRedLed = 100;
                }
            } else if (GetKeyState (0x45) < 0) {    // 'e'
                robRedLed--;
                if(robRedLed < 0) {
                    robRedLed = 0;
                }
            } else if (GetKeyState (0x47) < 0) {    // 'g'
                robGreenLed++;
                if(robGreenLed > 100) {
                    robGreenLed = 100;
                }
            } else if (GetKeyState (0x46) < 0) {    // 'f'
                robGreenLed--;
                if(robGreenLed < 0) {
                    robGreenLed = 0;
                }
            } else if (GetKeyState (0x42) < 0) {    // 'b'
                robBlueLed++;
                if(robBlueLed > 100) {
                    robBlueLed = 100;
                }
            } else if (GetKeyState (0x56) < 0) {    // 'v'
                robBlueLed--;
                if(robBlueLed < 0) {
                    robBlueLed = 0;
                }
            } else if(GetKeyState (0x55) < 0) {     // 'u'
                if(tvOn) {
                    tvOn = 0;
                    disableTVRemote(robotAddress);
                } else {
                    tvOn = 1;
                    enableTVRemote(robotAddress);
                }
            } else if (GetKeyState (0x49) < 0) {    // 'i'
                if(irOn) {
                    irOn = 0;
                    turnOffAllIRs(robotAddress);
                } else {
                    irOn = 1;
                    turnOnAllIRs(robotAddress);
                }
            } else if(GetKeyState (0x4f) < 0) {     // 'o'
                if(obstacleAvoid) {
                    obstacleAvoid = 0;
                    disableObstacleAvoidance(robotAddress);
                } else {
                    obstacleAvoid = 1;
                    enableObstacleAvoidance(robotAddress);
                }
            } else if(GetKeyState (0x50) < 0) {     // 'p'
                if(cliffAvoid) {
                    cliffAvoid = 0;
                    disableCliffAvoidance(robotAddress);
                } else {
                    cliffAvoid = 1;
                    enableCliffAvoidance(robotAddress);
                }
            } else if(GetKeyState (0x4a) < 0) {     // 'j'
                if(sleepOn) {
                    sleepOn = 0;
                    disableSleep(robotAddress);
                } else {
                    sleepOn = 1;
                    enableSleep(robotAddress);
                }
            } else if(GetKeyState (0x43) < 0) {     // 'c'
                if(smallLedsOn) {
                    smallLedsOn = 0;
                    turnOffSmallLeds(robotAddress);
                } else {
                    smallLedsOn = 1;
                    turnOnSmallLeds(robotAddress);
                }
            } else if(GetKeyState (0x4b) < 0) {     // 'k'
                calibrateSensors(robotAddress);
            } else if(GetKeyState (0x4c) < 0) {     // 'l'
                startOdometryCalibration(robotAddress);
            } else if(GetKeyState (0x48) < 0) {     // 'h'
                printHelp();
            } else if(GetKeyState (0x51) < 0) {     // 'q'
                exitProg = 1;
            } else {
                robRSpeed = 0;
                robLSpeed = 0;
            }

        }

#endif

}

