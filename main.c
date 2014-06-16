#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include "elisa3-lib.h"
#include "terminal.h"
#include "input.h"

// received from robot
int robotAddress;
unsigned int robProx[8] = {0};
unsigned int robProxAmb[8] = {0};
unsigned int robGround[4] = {0};
unsigned int robGroundAmb[4] = {0};
unsigned int robBattLevel = 0;
unsigned int robBattPercent = 0;
signed int robAccX=0, robAccY=0, robAccZ=0;
int robVertAngle = 0;
unsigned char robSelector=0, robTvRemote=0, robFlagsRx=0;
signed long int robLeftMotSteps=0, robRightMotSteps=0;
signed int robTheta=0, robXPos=0, robYPos=0;
double linkQualityToRob=0;

// sent to robot
char robLSpeed=0, robRSpeed=0;
char robRedLed=0, robGreenLed=0, robBlueLed=0;
unsigned char robFlagsTx = 0x00;
unsigned char obstacleAvoid=0, cliffAvoid=0, irOn=0, tvOn=0, sleepOn=0, smallLedsOn=0;

// various
unsigned int delayCounter=0;
char current_speed=0;
unsigned char exitProg=0;

int main(int argc, char *argv[]) {

    printf("\r\nInsert the robot address: ");
    scanf("%d", &robotAddress);

    initTerminal();

    // init the communication with the RF module and thus with the robot
    openRobotComm();

    // set the address of the robot to control; if more robots (max of 4 per packet) need to be controlled
    // the function need to be called more times with different ids (0..3) and addresses
    setRobotAddress(0, robotAddress);

    while(!exitProg) {

        handleKeyboardInput();

        // set new data for the robot (given from the user through the keyboard)
        setLeftSpeed(robotAddress, robLSpeed);
        setRightSpeed(robotAddress, robRSpeed);
        setRed(robotAddress, robRedLed);
        setBlue(robotAddress, robBlueLed);
        setGreen(robotAddress, robGreenLed);

        // update sensors data received from the robot
        robVertAngle = getVerticalAngle(robotAddress);
        getAllProximity(robotAddress, robProx);
        getAllProximityAmbient(robotAddress, robProxAmb);
        getAllGround(robotAddress, robGround);
        getAllGroundAmbient(robotAddress, robGroundAmb);
        robBattLevel = getBatteryAdc(robotAddress);
        robBattPercent = getBatteryPercent(robotAddress);
        robAccX = getAccX(robotAddress);
        robAccY = getAccY(robotAddress);
        robAccZ = getAccZ(robotAddress);
        robFlagsRx = getFlagTX(robotAddress, 0);
        robTvRemote = getTVRemoteCommand(robotAddress);
        robSelector = getSelector(robotAddress);
        robLeftMotSteps = getLeftMotSteps(robotAddress);
        robRightMotSteps = getRightMotSteps(robotAddress);
        robXPos = getOdomXpos(robotAddress);
        robYPos = getOdomXpos(robotAddress);
        robTheta = getOdomTheta(robotAddress);
        linkQualityToRob = getRFQuality(robotAddress);

        printRobotInfo();

    }

    closeRobotComm();
	closeTerminal();

	return 0;

}

