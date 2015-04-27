#pragma config(Sensor, S1,     touchSensor,    sensorTouch)
#pragma config(Sensor, S2,     sonarSensor,    sensorSonar)

task main()
{
	// wait 50 msec to initialize light sensor
	wait1Msec(50);

	int somethingClose = 20;
	int highSpeed = -80;
	int noSpeed = 0;
	int reverseSpeed = 80;
	int turnTime = 1500;

	while(true)
	{
		// run ahead to slam against something
		while(SensorValue[touchSensor] == 0)
		{
			motor[motorB] = highSpeed;
			motor[motorC] = highSpeed;
		}

		// stop
		motor[motorB] = noSpeed;
		motor[motorC] = noSpeed;
		wait1Msec(250);

		// turn right
		motor[motorC] = reverseSpeed;
		wait1Msec(turnTime);
		motor[motorC] = noSpeed;

		// ahead full while the obstacle is near
		motor[motorB] = highSpeed;
		motor[motorC] = highSpeed;
		while (SensorValue[sonarSensor] < somethingClose);

		// when the obstacle is cleared, turn
		motor[motorB] = noSpeed;
		wait1Msec(turnTime);

		// when the turn ends, continue
		motor[motorB] = highSpeed;
	}
}
