#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include "elisa3-lib.h"
#include "terminal.h"
#include "input.h"
#include <windows.h>

// received from robot
int robotAddress[1];
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
    scanf("%d", &robotAddress[0]);

    initTerminal();

    // init the communication with the robots; set the addresses and number of the robots to control
    startCommunication(robotAddress, 1);

    while(!exitProg) {

        handleKeyboardInput();

        // set new data for the robot (given from the user through the keyboard)
        setLeftSpeed(robotAddress[0], robLSpeed);
        setRightSpeed(robotAddress[0], robRSpeed);
        setRed(robotAddress[0], robRedLed);
        setBlue(robotAddress[0], robBlueLed);
        setGreen(robotAddress[0], robGreenLed);

        // update sensors data received from the robot
        robVertAngle = getVerticalAngle(robotAddress[0]);
        getAllProximity(robotAddress[0], robProx);
        getAllProximityAmbient(robotAddress[0], robProxAmb);
        getAllGround(robotAddress[0], robGround);
        getAllGroundAmbient(robotAddress[0], robGroundAmb);
        robBattLevel = getBatteryAdc(robotAddress[0]);
        robBattPercent = getBatteryPercent(robotAddress[0]);
        robAccX = getAccX(robotAddress[0]);
        robAccY = getAccY(robotAddress[0]);
        robAccZ = getAccZ(robotAddress[0]);
        robFlagsRx = getFlagTX(robotAddress[0], 0);
        robTvRemote = getTVRemoteCommand(robotAddress[0]);
        robSelector = getSelector(robotAddress[0]);
        robLeftMotSteps = getLeftMotSteps(robotAddress[0]);
        robRightMotSteps = getRightMotSteps(robotAddress[0]);
        robXPos = getOdomXpos(robotAddress[0]);
        robYPos = getOdomXpos(robotAddress[0]);
        robTheta = getOdomTheta(robotAddress[0]);
        linkQualityToRob = getRFQuality(robotAddress[0]);

        printRobotInfo();

    }

    stopCommunication();
	closeTerminal();

	return 0;

}

