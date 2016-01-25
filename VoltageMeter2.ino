/*

Tutorial 5: Volt Meter
Stuart GitHub Test

*/



#include "Window.h"
// select the analog input pin
int sensorPin = A0;
// variable to store the value coming from the sensor
int sensorValue = 0;   
// variable to store the voltage coming from the sensor
float sensorVoltage = 0; 



void setup() {


	// start serial for output
	Serial.begin(9600);  

}



void loop() {

	// Read the value from the analog input pin 
	int sensorValue = analogRead(sensorPin);



	// Convert sensor value to voltage, a value of 1023 = 5V, a value of 0 = 0V
	float sensorVoltage = sensorValue*(5.0 / 1023.0);



	// print sensor value
	Serial.print("The voltage is ");
	Serial.println(sensorVoltage);



	// delay by 1000 milliseconds:
	delay(1000);

}