// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
	Name:       Stepper Motor micro.ino
	Created:	2019-07-01 10:05:33 AM
	Author:     DESKTOP-RAHMAN\Rahman
*/

#include <Stepper.h>
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)
Stepper stepper(STEPS, 9, 11, 10, 12);

long rpm = 1;
long mystep = 1;
bool inv = false;
bool newData = false;
bool stop_motor_flag = false;

String All_Data = "";
bool flag_read = false;
//===========================================
int step_number = 0;    // which step the motor is on
int direction = 0;      // motor direction
int last_step_time = 0; // time stamp in us of the last step taken
long number_of_steps = 2038; // total number of steps for this motor
long step_delay = 0;
// Arduino pins for the motor control connection:
#define motor_pin_1		9
#define motor_pin_2		 11
#define motor_pin_3		 10
#define motor_pin_4		 12

#define LED 4

// When there are 4 pins, set the others to 0:
int motor_pin_5 = 0;

// pin_count is used by the stepMotor() method:
int pin_count = 4;

//===========================================

void setup() {
	Serial.begin(115200);
	//Serial.getTimeout(500);
	//Serial.setTimeout(200);

	// setup the pins on the microcontroller:
	/*pinMode(motor_pin_1, OUTPUT);
	pinMode(motor_pin_2, OUTPUT);
	pinMode(motor_pin_3, OUTPUT);
	pinMode(motor_pin_4, OUTPUT);*/

	pinMode(LED, OUTPUT);
	//digitalWrite(LED, HIGH);
	// put your setup code here, to run once:
	//stepper.setSpeed(10); // 1 rpm
	//stepper.step(2038 * 6); // do 2038 steps -- corresponds to one revolution in one minute
}



void loop() {
	digitalWrite(LED, HIGH);
	if (newData)
	{
		if (All_Data.indexOf("@") >= 0)
		{
			String data = All_Data.substring(All_Data.indexOf("@") + 1, All_Data.indexOf("A"));
			rpm = data.toInt();
			//Serial.print("rmp=");
			//Serial.println(rpm);
			data = All_Data.substring(All_Data.indexOf("A") + 1, All_Data.indexOf("B"));
			mystep = data.toInt();
			//Serial.print("step=");
			//Serial.println(mystep);
			String in = (All_Data.substring(All_Data.indexOf("B") + 1, All_Data.indexOf("#")));
			//Serial.print("inv=");
			//Serial.println(in);

			All_Data = "";
			newData = false;
			stepper.setSpeed(rpm);
			if (in == "+")
			{
				stepper.step(mystep);
			}
			else
			{
				stepper.step(0-mystep);
			}

		}
		All_Data = "";
	}

}



void serialEvent() {
	while (Serial.available()) {

		char inChar = (char)Serial.read();
		if (inChar == '!') {
			flag_read = false;
			stop_motor_flag = true;
			newData = false;
			return;
		}

		if (inChar == '@') {
			flag_read = true;
		}

		if (inChar == '#') {
			All_Data += inChar;
			flag_read = false;
			//Serial.print(All_Data);
			newData = true;
			return;
		}

		if (flag_read)	All_Data += inChar;
	}
}


//===============================================================================

//
///*
// * Sets the speed in revs per minute
// */
//void setSpeed(long whatSpeed)
//{
//	step_delay = 60L * 1000L * 1000L / number_of_steps / whatSpeed;
//}
//
///*
// * Moves the motor steps_to_move steps.  If the number is negative,
// * the motor moves in the reverse direction.
// */
//void step(int steps_to_move)
//{
//	int steps_left = abs(steps_to_move);  // how many steps to take
//
//	// determine direction based on whether steps_to_mode is + or -:
//	if (steps_to_move > 0) { direction = 1; }
//	if (steps_to_move < 0) { direction = 0; }
//
//
//	// decrement the number of steps, moving one step each time:
//	while (steps_left > 0)
//	{
//		if (stop_motor_flag) //stop motor command
//		{
//			digitalWrite(motor_pin_1, LOW);
//			digitalWrite(motor_pin_2, LOW);
//			digitalWrite(motor_pin_3, LOW);
//			digitalWrite(motor_pin_4, LOW);
//			stop_motor_flag = false;
//			return;
//		}
//		unsigned long now = micros();
//		// move only if the appropriate delay has passed:
//		if (now - last_step_time >= step_delay)
//		{
//			// get the timeStamp of when you stepped:
//			last_step_time = now;
//			// increment or decrement the step number,
//			// depending on direction:
//			if (direction == 1)
//			{
//				step_number++;
//				if (step_number == number_of_steps) {
//					step_number = 0;
//				}
//			}
//			else
//			{
//				if (step_number == 0) {
//					step_number = number_of_steps;
//				}
//				step_number--;
//			}
//			// decrement the steps left:
//			steps_left--;
//			// step the motor to step number 0, 1, ..., {3 or 10}
//			if (pin_count == 5)
//				stepMotor(step_number % 10);
//			else
//				stepMotor(step_number % 4);
//		}
//	}
//}
//
///*
// * Moves the motor forward or backwards.
// */
//void stepMotor(int thisStep)
//{
//	if (pin_count == 4) {
//		switch (thisStep) {
//		case 0:  // 1010
//			digitalWrite(motor_pin_1, HIGH);
//			digitalWrite(motor_pin_2, LOW);
//			digitalWrite(motor_pin_3, HIGH);
//			digitalWrite(motor_pin_4, LOW);
//			break;
//		case 1:  // 0110
//			digitalWrite(motor_pin_1, LOW);
//			digitalWrite(motor_pin_2, HIGH);
//			digitalWrite(motor_pin_3, HIGH);
//			digitalWrite(motor_pin_4, LOW);
//			break;
//		case 2:  //0101
//			digitalWrite(motor_pin_1, LOW);
//			digitalWrite(motor_pin_2, HIGH);
//			digitalWrite(motor_pin_3, LOW);
//			digitalWrite(motor_pin_4, HIGH);
//			break;
//		case 3:  //1001
//			digitalWrite(motor_pin_1, HIGH);
//			digitalWrite(motor_pin_2, LOW);
//			digitalWrite(motor_pin_3, LOW);
//			digitalWrite(motor_pin_4, HIGH);
//			break;
//		}
//	}
//}
//
///*
//  version() returns the version of the library:
//*/
//int version(void)
//{
//	return 5;
//}
