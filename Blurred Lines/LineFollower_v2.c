#pragma config(Sensor, S3,     lightSensor,    sensorLightActive)

#define TURN_UNIT 50

#define LIGHT_WHITE 40

#define LEFT 0
#define RIGHT 1

#define STOP 0
#define HIGH 20
#define REV -19

int turnTime = 0;
int lastTurnDir = LEFT;

void turnLeft() {
	motor[motorB] = HIGH;
	motor[motorC] = REV;
}

void turnRight() {
	motor[motorB] = REV;
	motor[motorC] = HIGH;
}

void standStill() {
	motor[motorB] = STOP;
	motor[motorC] = STOP;
}

void advance() {
	motor[motorB] = HIGH;
	motor[motorC] = HIGH;
}

void initiateTurning() {
	turnTime = 4;

	while(true) {
		turnTime += turnTime/2;

		// turn to selected direction
		if (lastTurnDir == LEFT)
			turnLeft();
		else
			turnRight();

		for (int time = 0; time < turnTime; time++) {
			if (SensorValue[lightSensor] < LIGHT_WHITE) {
				standStill();
				return;
			}
			wait1Msec(TURN_UNIT);
		}
		standStill();

		// since black was not found on the direction for the current time units, change direction
		if (lastTurnDir == LEFT)
			lastTurnDir = RIGHT;
		else
			lastTurnDir = LEFT;
	}
}

task main()
{
	// wait 50 msec to initialize light sensor
	wait1Msec(50);

	while(true)
	{
		// starts on black; go ahead while black line is detected
		advance();
		while (SensorValue[lightSensor] < LIGHT_WHITE){};

		// when the line is lost, start turning until line is found again
		initiateTurning();
	}
}
