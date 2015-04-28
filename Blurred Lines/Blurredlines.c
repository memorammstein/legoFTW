#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)

#define SPEED_HIGH 75
#define SPEED_LOW 5
#define SPEED_REV -10
#define SPEED_STOP 0

#define LIGHT_WHITE 35

#define TURN_RIGHT 0
#define TURN_LEFT 1

#define TURN_TIME 500

int turn;

void fullStop()
{
	motor[motorC] = SPEED_STOP;
	motor[motorB] = SPEED_STOP;
	wait1Msec(50);
}

void aheadFull()
{
	motor[motorC] = SPEED_HIGH;
	motor[motorB] = SPEED_HIGH;
}

void turnRight()
{
	motor[motorC] = SPEED_HIGH;
	motor[motorB] = SPEED_REV;
}

void hardRight()
{
	motor[motorC] = SPEED_HIGH;
	motor[motorB] = SPEED_REV;
}

void turnLeft()
{
	motor[motorC] = SPEED_REV;
	motor[motorB] = SPEED_HIGH;
}

void hardLeft()
{
	motor[motorC] = SPEED_REV;
	motor[motorB] = SPEED_HIGH;
}

task main()
{
	// wait 50 msec to initialize light sensor
	wait1Msec(50);

	turn = 0;

	while(true)
	{
		// while the sensor is on track, go ahead full speed
		if (SensorValue[lightSensor] < LIGHT_WHITE)
		{
			aheadFull();
			//wait1Msec(10);
		}
		else
		{
			// if the robot lost the line, spin to the current selected side
			if (turn == TURN_RIGHT)
			{
				int count = 0;
				while (count < TURN_TIME && SensorValue[lightSensor] > LIGHT_WHITE)
				{
					turnRight();
					count++;
					wait1Msec(1);
					if (SensorValue[lightSensor] < LIGHT_WHITE)
						break;
				}
				// if the turn ends and the whiteline was not found,
				// a wrong turn was selected; an emergency counterturn is made until
				// the line is found again
				if (SensorValue[lightSensor] > LIGHT_WHITE + 10)
				{
				motor[motorC] = SPEED_REV;
				motor[motorB] = SPEED_REV;
				wait1Msec(20);
				motor[motorC] = SPEED_STOP;
				motor[motorB] = SPEED_STOP;

					turn = TURN_LEFT;
					hardLeft();
					wait1Msec(20);
					while (SensorValue[lightSensor] > LIGHT_WHITE);
				}
			}
			else if (turn == TURN_LEFT)
			{
				int count = 0;
				while (count < TURN_TIME && SensorValue[lightSensor] > LIGHT_WHITE)
				{
					turnLeft();
					count++;
					wait1Msec(1);
					if (SensorValue[lightSensor] < LIGHT_WHITE)
						break;
				}
				// if the turn ends and the whiteline was not found,
				// a wrong turn was selected; an emergency counterturn is made until
				// the line is found again
				if (SensorValue[lightSensor] > LIGHT_WHITE + 10)
				{
					turn = TURN_RIGHT;
					while (SensorValue[lightSensor] > LIGHT_WHITE)
					{
						hardRight();
					}
				}
			}
		}
	}
}
