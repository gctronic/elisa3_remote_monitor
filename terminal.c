#include "terminal.h"
#include "input.h"
#include <stdio.h>
#ifdef _WIN32
    #include "windows.h"
#endif
#if defined(__linux__) || defined(__APPLE__)
	#include <ncurses.h>
#endif

extern unsigned int robProx[8];
extern unsigned int robProxAmb[8];
extern unsigned int robGround[4];
extern unsigned int robGroundAmb[4];
extern signed int robAccX, robAccY, robAccZ;
extern unsigned int robBattLevel;
extern unsigned int robBattPercent;
extern int robVertAngle;
extern unsigned char robSelector, robTvRemote, robFlagsRx;
extern signed long int robLeftMotSteps, robRightMotSteps;
extern signed int robTheta, robXPos, robYPos;
extern char current_speed;
extern char robLSpeed, robRSpeed;
extern char robRedLed, robGreenLed, robBlueLed;
extern unsigned char robFlagsTx;
extern double linkQualityToRob;

#ifdef _WIN32
void curPos(int x, int y) {
  HANDLE hStdout;
  CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
  hStdout=GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
  csbiInfo.dwCursorPosition.X=x;
  csbiInfo.dwCursorPosition.Y=y;
  SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
}
#endif

void printHelp() {

#ifdef _WIN32
    system( "cls" );
#endif

#if defined(__linux__) || defined(__APPLE__)
	clear();
#endif

    while(1) {

#ifdef _WIN32
        curPos(0,0);
#endif

#if defined(__linux__) || defined(__APPLE__)
		refresh();
#endif

        printf("************\n\r");
        printf("*** HELP ***\n\r");
        printf("************\n\r");
        printf("\n\rMOVEMENT: when no key is pressed the speed sent to robot is 0\n\r");
        printf("+: increase speed used to control the robot\n\r");
        printf("-: decrease speed used to control the robot\n\r");
        printf("Arrow up: both motors forward\n\r");
        printf("Arrow down: both motors backward\n\r");
        printf("Arrow left: motor right forward\n\r");
        printf("Arrow right: motor left forward\n\r");
        printf("a: pivot counterclockwise (motor right forward, motor left backward)\n\r");
        printf("s: pivot clockwise (motor right backward, motor left forward)\n\r");
        printf("\n\rRGB COLOR:\n\r");
        printf("r: red power increase (max 100)\n\r");
        printf("e: red power decrease (min 0)\n\r");
        printf("g: green power increase (max 100)\n\r");
        printf("f: green power decrease (min 0)\n\r");
        printf("b: blue power increase (max 100)\n\r");
        printf("v: blue power decrease (min 0)\n\r");
        printf("\n\rGREEN LEDS:\n\r");
        printf("c: turn all small green leds on/off (toggle)\n\r");
        printf("\n\rFLAGS:\n\r");
        printf("u: enable/disable tv remote receiver (toggle)\n\r");
        printf("i: turn all IR emitters on/off (toggle)\n\r");
        printf("o: enable/disable obstacle avoidance (toggle)\n\r");
        printf("p: enable/disable cliff avoidance (toggle)\n\r");
        printf("j: goto sleep (the robot sleep for 1 minute)\n\r");
        printf("k: calibrate all sensors (proximity, ground, accelerometer)\n\r");
        printf("l: start odometry calibration\n\r");
        printf("\n\rOTHERS:\n\r");
        printf("spacebar: reset\n\r");
        printf("h: enter/exit help\n\r");
        printf("q: quit\n\r");
        printf("\n\rFLAGS received:\n\r");
        printf("bit0: 0 = robot not in charge; 1 = robot in charge\n\r");
        printf("bit1: 0 = button pressed; 1 = button not pressed\n\r");
        printf("bit2: 0 = robot not charged; 1 = robot charged completely\n\r");
        printf("the remainig bits are not used\n\r");

        if(HKeyPressed()) {
            break;
        }

    }

#ifdef _WIN32
    system( "cls" );
#endif

#if defined(__linux__) || defined(__APPLE__)
		refresh();
#endif

}

void initTerminal() {
#ifdef _WIN32
    system("mode 75, 60");
#endif

#if defined(__linux__) || defined(__APPLE__)
    initscr();
	keypad(stdscr,1);
    cbreak();
    noecho();
    timeout(100); // non-blocking getch()
#endif

}

void closeTerminal() {
#if defined(__linux__) || defined(__APPLE__)
	endwin();
#endif
}

void printRobotInfo() {

#ifdef _WIN32
        curPos(0,0);
#endif

#if defined(__linux__) || defined(__APPLE__)
		refresh();
#endif

        printf("*****************************\n\r");
        printf("*** RECEPTION robot -> pc ***\t\tPress h for help\n\r");
        printf("*****************************\n\r");
        printf("PROXIMITY\r\n");
        printf("Prox0\t Prox1\t Prox2\t Prox3\t Prox4\t Prox5\t Prox6\t Prox7\r\n");
        printf("%4d\t %4d\t %4d\t %4d\t %4d\t %4d\t %4d\t %4d\t\n\r", robProx[0], robProx[1], robProx[2], robProx[3], robProx[4], robProx[5], robProx[6], robProx[7]);
        printf("PROXIMITY AMBIENT\r\n");
        printf("Prox0\t Prox1\t Prox2\t Prox3\t Prox4\t Prox5\t Prox6\t Prox7\r\n");
        printf("%4d\t %4d\t %4d\t %4d\t %4d\t %4d\t %4d\t %4d\t\n\r", robProxAmb[0], robProxAmb[1], robProxAmb[2], robProxAmb[3], robProxAmb[4], robProxAmb[5], robProxAmb[6], robProxAmb[7]);
        printf("GROUND\r\n");
        printf("ground0\t ground1\t ground2\t ground3\r\n");
        printf("%4d\t %4d\t\t %4d\t\t %4d\t\n\r", robGround[0], robGround[1], robGround[2], robGround[3]);
        printf("GROUND AMBIENT\r\n");
        printf("ground0\t ground1\t ground2\t ground3\r\n");
        printf("%4d\t %4d\t\t %4d\t\t %4d\t\n\r", robGroundAmb[0], robGroundAmb[1], robGroundAmb[2], robGroundAmb[3]);
        printf("ACCELEROMETER\r\n");
        printf("X:%4d\t Y:%4d\t Z:%4d\t\r\n", robAccX, robAccY, robAccZ);
        printf("angle: %3d degrees (on vertical wall)\n\r", robVertAngle);
        printf("BATTERY\r\n");
        printf("adc: %4d (~%3d%%)\n\r", robBattLevel, robBattPercent);
        printf("FLAGS\r\n");
        if(robFlagsRx==0) {
            printf("0x00\n\r");
        } else {
            printf("%#.2x\n\r", robFlagsRx);
        }
        printf("TV REMOTE\r\n");
        printf("%.2d\n\r", robTvRemote);
        printf("SELECTOR\r\n");
        printf("%.2d\n\r", robSelector);
        printf("MOTORS ENCODERS\r\n");
        printf("l: %+.10ld r: %+.10ld\n\r", robLeftMotSteps, robRightMotSteps);
        printf("ODOMETRY\r\n");
        printf("X:%4d\t Y:%4d\t theta:%4d\t\r\n", robXPos, robYPos, robTheta);
        printf("****************************\n\r");
        printf("*** TRANSFER robot <- pc ***\n\r");
        printf("****************************\n\r");
		printf("SPEED\r\n");
		printf("speed to send: %+3d\t\r\n", current_speed);
		printf("left: %+3d\t right: %+3d\t\n\r", robLSpeed, robRSpeed);
		printf("RGB LEDS\r\n");
		printf("r: %3d\t g: %3d\t b: %3d\t\n\r", robRedLed, robGreenLed, robBlueLed);
        printf("FLAGS\r\n");
        if(robFlagsTx==0) {
            printf("0x00\n\r");
        } else {
            printf("%#.2x\n\r", robFlagsTx);
        }
        printf("\nRF LINK QUALITY\r\n");
        printf("%6.2f %%\r\n", linkQualityToRob);

}

