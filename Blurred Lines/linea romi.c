#pragma config(Sensor, S3,     lightSensor,         sensorLightActive)

#define SPEED_HIGH 7
#define SPEED_LOW 5
#define SPEED_REV -10

#define LIGHT_WHITE 35

#define TURN_RIGHT 1
#define TURN_LEFT -1

#define TURN_INIT_TIME 500
#define CENTER_TIME 500

void goLow()
{
	motor[motorC] = SPEED_LOW;
	motor[motorB] = SPEED_LOW;
}

void goFast()
{
	motor[motorC] = SPEED_HIGH;
	motor[motorB] = SPEED_HIGH;
}

void turn(int dir)
{
	if(dir==TURN_LEFT)
	{
		motor[motorC] = SPEED_REV;
		motor[motorB] = SPEED_HIGH;
	}
	else
	{
		motor[motorB] = SPEED_REV;
		motor[motorC] = SPEED_HIGH;
	}
}

void goBackards()
{
	motor[motorC] = SPEED_REV;
	motor[motorB] = SPEED_REV;
}

void goStop()
{
	motor[motorC] = 0;
	motor[motorB] = 0;
}

bool stopWhenBlackOrTimeout(int t)
{
	int delay=0;
	while(SensorValue[lightSensor] >= LIGHT_WHITE)
	{
		wait1Msec(10);
		delay+=10;
		if( delay>= t)
		{
			goStop();
			return false;
		}
	}

	goStop();
	return true;
}

task main()
{
	int t;
	int direction= TURN_RIGHT;

	while(true)
	{
		//estado = camino
		goFast();
		while(SensorValue[lightSensor] < LIGHT_WHITE);
		goStop();

		//estado = correccion optimista
		//giro 1
		t= TURN_INIT_TIME;
		turn(direction);
		if(stopWhenBlackOrTimeout(t))
			continue;

		//giro 2
		turn*= -1;
		turn(direction);
		if(stopWhenBlackOrTimeout(t*2))
			continue;

		//estado = correccion pesimista
		//deshace giro
		direction*= -1;
		turn(direction);
		wait1Msec(t);
		goStop();

		//regresa
		goBackwards();
		while(SensorValue[lightSensor] >= LIGHT_WHITE);
		goStop();

		//find other wall
		while(SensorValue[lightSensor] < LIGHT_WHITE)
		{
			turn(direction);
			wait1Msec(t);
			goStop();

			t+=20;
			direction*=-1;
		}

		//center in path
		turn(-direction);
		wait1Msec(CENTER_TIME);
		goStop();


	}
}
