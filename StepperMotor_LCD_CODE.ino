/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/


#include <Stepper.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Steps your motor take to complete 360 degree rotation. In your case it 28BYJ-48 it takes 2038 steps per revolution
const int stepsPerRevolution = 2038;

// initialize the stepper library on pins 8 through 11:
Stepper stepper_m(stepsPerRevolution, 6, 8, 7, 9);



//This function takes 3 paramenters as input:

//1. steps : you can define how many steps you want your motor to take 
// (IMP: If you input 0 steps function will automatically override to revolution function)

//2. revolution: You can define here how many full rotations (360) you want your motor to do 
// (IMP: In order to activate this function steps should be given as 0) 

//3. direction: if set true motor rotates clockise and vice versa.


void move_stepper(int steps, int revolution, bool direction){

  if(steps == 0){
    if(revolution != 0){
      steps = round(revolution * stepsPerRevolution);
    }
    else{
      Serial.println("No Steps or revolution given");
      return;
    }
  }
  Serial.println("Moving Stepper Motor");

  if(direction){
    lcd.clear();
    //Moving LCD cursor to first column and row
    lcd.setCursor(0,0);
    lcd.print("Motor Direction"); //Letters must be less than and equal to 16 otherwise it will be not printed correctly
    //Moving LCD cursor to 2nd row and 1st column
    lcd.setCursor(0, 1);
    lcd.print("Anti-Clockwise"); //Letters must be less than and equal to 16 otherwise it will be not printed correctly

    //Printing update on computer's serial monitor
    Serial.println("Moving Counter-Clockwise");

    //Moving Stepper motor
    stepper_m.step(steps);
  }else{
    lcd.clear();
    //Moving LCD cursor to first column and row
    lcd.setCursor(0,0);
    lcd.print("Motor Direction"); //Letters must be less than and equal to 16 otherwise it will be not printed correctly
    //Moving LCD cursor to 2nd row and 1st column
    lcd.setCursor(0, 1);
    lcd.print("Clockwise"); //Letters must be less than and equal to 16 otherwise it will be not printed correctly

    //Printing update on computer's serial monitor
    Serial.println("Moving Clockwise");

    //Moving stepper motor
    stepper_m.step(-steps);
  }
  Serial.println("Stepper motor moved successfully!");
}

//In this function you can set stepper motor speed. You should set speed between 10 - 100 for smooth performance

void set_motor_speed(int speed) { //Max 100% for smooth control
  Serial.print("Motor Speed set to: ");
  Serial.println(speed);
   speed = speed / 10;
  stepper_m.setSpeed(speed);
}



void setup() {

//Starting Serial monitor at 1115200 baud rate
  Serial.begin(115200);

//Initailzing LCD display
  lcd.begin(16, 2);

//Clear all contents from LCD
  lcd.clear();

//Setting motor speed to maximum on startup
  set_motor_speed(100);

}

void loop() {
  //This function will rotate motor 3 times complete revolution in clockwise direction.
  move_stepper(0, 3, true);

  //This function will rotate motor 1 time complete revolution in anti-clockwise direction.
  move_stepper(0, 1, false);

}
