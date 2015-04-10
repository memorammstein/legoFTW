#pragma config(Sensor, S3, lightSensor, sensorLightActive, sonarSensor, S1, sonarSensorActive)

task main()
{
	int crashDistance= 5;
	int darkness = 50;
	int maxSpeed = 60;
	int minSpeed = 20;

	while(true)
	{
		if(SensorValue[lightSensor] > darkness)
		{
			//turn to find space
			while(SensorValue[sonarSensor] <= crashDistance)
			{
				motor[motorB] = minSpeed;
				motor[motorC] = maxSpeed;
			}

			//run while is light and space
			while(SensorValue[lightSensor] > darkness 
			&& SensorValue[sonarSensor] > crashDistance)
			{
				motor[motorB] = maxSpeed;
				motor[motorC] = maxSpeed;
			}
			
			//stop
			motor[motorB] = 0;
			motor[motorC] = 0;
			
		}
	}
  
  
}
