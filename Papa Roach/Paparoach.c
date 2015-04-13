#pragma config(Sensor, S1,     touchSensor,    sensorTouch)
#pragma config(Sensor, S3,     lightSensor,    sensorLightActive)

task main()
{
	// wait 50 msec to initialize light sensor
	wait1Msec(50);

	int darkness = 25;
	int highSpeed = -80;
	int noSpeed = 0;
	int reverseSpeed = 80;

	while(true)
	{
		if(SensorValue[lightSensor] > darkness)
		{
			// run ahead to find shadow
			while(SensorValue[touchSensor] == 0 &&
				SensorValue[lightSensor] > darkness)
			{
				motor[motorB] = highSpeed;
				motor[motorC] = highSpeed;
			}

			// when he encounters an obstacle, stop, spin and continue
			if (SensorValue[lightSensor] > darkness)
			{
				motor[motorB] = noSpeed;
				motor[motorC] = noSpeed;
				wait1Msec(250);
				motor[motorC] = reverseSpeed;
				wait1Msec(600);
			}

			// stop after the turn.
			// if light is still on, it will advance again.
			// also, if light was found, this stops the robot
			motor[motorB] = noSpeed;
			motor[motorC] = noSpeed;
		}
	}
}
