#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                           - Line Tracker -                                             *|
|*                                            ROBOTC on NXT                                               *|
|*                                                                                                        *|
|*  This program allows your taskbot to follow a line in reverse.                                         *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:                                                                                              *|
|*    1)  The Light Sensor is attached to the back of the robot.                                          *|
|*    2)  Be sure to take readings of your Light Sensor over the light and dark areas.  Once you have     *|
|*        the values, add them and divide by 2 to find your threshold.  Then, use your threshold as a     *|
|*        comparison in your program.                                                                     *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port B                  motorB              NXT                 Right motor                         *|
|*    Port C                  motorC              NXT                 Left motor                          *|
|*    Port 1                  lightSensor         Light Sensor        Back mounted                        *|
\*---------------------------------------------------------------------------------------------------4246-*/

void findLine360();
void goStraight();

task main()
{
   wait1Msec(50);                        // The program waits 50 milliseconds to initialize the light sensor.
   while(true)                           // Infinite loop
   {
     if(go == STRAIGHT)
       {
         if(SensorValue[lightSensor] > 50)
         {
           findLine360();
				 }
         while(SensorValue[lightSensor] < 50)
         {
           motor[motorB] = 25;                  // Motor B is run at a 60 power level.
					 motor[motorC] = 25;
				 }
				 go = LEFT;
       }
     if(go == LEFT)
       {
         motor[motorB] = 25;                  // Motor B is run at a 60 power level.
				 motor[motorC] = 10;
				 wait1Msec(500);
				 if(SensorValue[lightSensor] < 50)
				 {
				   go = STRAIGHT;
				 }
				 else
				 {
				   if(buf == 0)
				   {
				     ++buf;
				   }
				   else
				   {
				     buf = 0;
				     go = RIGHT;
				   }
				 }
       }
     if(go == RIGHT)
       {
         motor[motorB] = 10;                  // Motor B is run at a 60 power level.
				 motor[motorC] = 25;
				 if(SensorValue[lightSensor] < 50)
				 {
				   go = STRAIGHT;
				 }
				 else
				 {
				   if(buf == 0)
				   {
				     ++buf;
				   }
				   else
				   {
				     buf = 0;
				     go = RIGHT_AGAIN;
				   }
				 }
       }
     if(go == RIGHT_AGAIN)
       {
         motor[motorB] = 10;                  // Motor B is run at a 60 power level.
				 motor[motorC] = 25;
				 if(SensorValue[lightSensor] < 50)
				 {
				   go = STRAIGHT;
				 }
				 else
				 {
				   if(buf == 0)
				   {
				     ++buf;
				   }
				   else
				   {
				     buf = 0;
				     go = RIGHT_AGAIN;
				   }
				 }
       }
   }
}