#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include "elisa3-lib.h"
#include "terminal.h"
#include "input.h"
#ifdef _WIN32
	#include <windows.h>
#endif

// received from robot
int robAddress[1];
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
signed int rTheta=0, rXPos=0, rYPos=0;
double linkQualityToRob=0;
double robGyroZ=0;
signed int robHeading=0;

// sent to robot
char robLSpeed=0, robRSpeed=0;
char robRedLed=0, robGreenLed=0, robBlueLed=0;
unsigned char robFlagsTx = 0x00;
unsigned char obstacleAvoid=0, cliffAvoid=0, irOn=0, tvOn=0, sleepOn=0, smallLedsOn=0;

// various
unsigned int delayCounter=0;
char current_speed=0;
unsigned char exitProg=0;

//FILE *fptr;

int main(int argc, char *argv[]) {

    //fptr = fopen("data.csv", "w");

    printf("\r\nInsert the robot address: ");
    scanf("%d", &robAddress[0]);

    initTerminal();

    // init the communication with the robots; set the addresses and number of the robots to control
    startCommunication(robAddress, 1);

    while(!exitProg) {

        handleKeyboardInput();

        // set new data for the robot (given from the user through the keyboard)
        setLeftSpeed(robAddress[0], robLSpeed);
        setRightSpeed(robAddress[0], robRSpeed);
        setRed(robAddress[0], robRedLed);
        setBlue(robAddress[0], robBlueLed);
        setGreen(robAddress[0], robGreenLed);

        // update sensors data received from the robot
        robVertAngle = getVerticalAngle(robAddress[0]);
        getAllProximity(robAddress[0], robProx);
        getAllProximityAmbient(robAddress[0], robProxAmb);
        getAllGround(robAddress[0], robGround);
        getAllGroundAmbient(robAddress[0], robGroundAmb);
        robBattLevel = getBatteryAdc(robAddress[0]);
        robBattPercent = getBatteryPercent(robAddress[0]);
        robAccX = getAccX(robAddress[0]);
        robAccY = getAccY(robAddress[0]);
        robAccZ = getAccZ(robAddress[0]);
        robFlagsRx = getFlagTX(robAddress[0], 0);
        robTvRemote = getTVRemoteCommand(robAddress[0]);
        robSelector = getSelector(robAddress[0]);
        robLeftMotSteps = getLeftMotSteps(robAddress[0]);
        robRightMotSteps = getRightMotSteps(robAddress[0]);
        rXPos = getOdomXpos(robAddress[0]);
        rYPos = getOdomYpos(robAddress[0]);
        rTheta = getOdomTheta(robAddress[0]);
        linkQualityToRob = getRFQuality(robAddress[0]);
        robGyroZ = getGyroZ(robAddress[0]);
        robHeading = getHeading(robAddress[0]);

        printRobotInfo();

        //fprintf(fptr, "%d,%d,%d\n", getAccX(robAddress[0]), getAccY(robAddress[0]), getAccZ(robAddress[0]));

    }

    stopCommunication();
	closeTerminal();

	//fclose(fptr);

	return 0;

}

