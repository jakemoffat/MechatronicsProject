/**
 * @file servomotor.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to command the Hitec HS422 servomotor.
 * @version 1.0
 * @date 2021-12-15
 *
 * @copyright Copyright (c) 2021
 *
 * Based on the example code by BARRAGAN <http://barraganstudio.com>, modified
 * 2013-11-08 by Scott Fitzgerald http://www.arduino.cc/en/Tutorial/Sweep.
 * Uses the Servo library https://www.arduino.cc/reference/en/libraries/servo/.
 * 
 * Modifications and final code done by: Jake Moffat and Bertan Dogancay
 *
 */

// Use this library to command servomotors
#include <Servo.h>

//Motor driver PWM pin
const byte E1 = 6;

//Motor driver direction pin
const byte M1 = 7;

//Motor driver PWM pin
const byte E2 = 5;

//Motor driver direction pin
const byte M2 = 4;

// Create servo objects
Servo hs422servo;
Servo hs421servo;
Servo hs420servo;

// Variable to store the servo position [degrees]
int angle = 0;

void setup()
{
  // Open the serial port at 9600 bps
  Serial.begin(9600);
  pinMode(M1, OUTPUT); // Configure pin M1 for output
  pinMode(M2, OUTPUT); // Configure pin M2 for output
  // Attach the servo on pin ## to the Servo object
  hs422servo.attach(12); // horizontal motion servo from activity 1
  hs421servo.attach(11); // vertical motion servo 
  hs420servo.attach(10); // gripper motion servo from activity 2
}

void loop()
{

  /* This part is seperated into 4 parts
   *  STEP 1: Get the gripper in the right position and start approaching the target/flag
   *  STEP 2: Grab the flag, close the grip and lift the flag 
   *  STEP 3: Rover drives backwards back to the square with the flag still raised
   *  STEP 4: Rover stops moving and places the flag down in the square and open the grip 
   */

  //STEP 1
  int u = 150; // chosen speed of rover
  // our hardware wheels would move at the same speed together, so had to go slower than wanted to get correct motion
  // for example u = 160 would make our rover turn more left and not in a straight line

  hs422servo.write(90);  // starts grip in forward facing position
  hs421servo.write(90);  // starts grip in horizontal position
  hs420servo.write(10);  // opens the grip - easier to grab the flag in the claws if already opened
  delay(5000);

  digitalWrite(M1, LOW); // Drive forward (left wheels)
  digitalWrite(M2, HIGH);  // Drive forward (right wheels)
  analogWrite(E1, u);     // PWM speed command (left wheels)
  analogWrite(E2, u);     // PWM speed command (right wheels)
  delay(5800);  // drive forward for calculated distance - because the flag could be placed between a 5500 and 6000 and the grip would still be able to reach of the target was "6000" away


  u = 0;  // stop the rover
  analogWrite(E1, u);     // PWM speed command (left wheels)
  analogWrite(E2, u);     // PWM speed command (right wheels)
  delay(2000); // this delay was put to show us when it would stop so we could visually see when step 2 would begin

  //STEP 2:
    
  // closes the grip
  for (angle = 0; angle <= 180; angle += 1)
  {
    // Tell the grip servo to go to position "angle"
    hs420servo.write(angle);

    // Wait a specified time [ms]
    delay(10); // we made this value much larger when testing just to visualize
  }
  delay(5000); // same delay from activity 2

  // lift the flag
  for (angle = 90; angle <= 180; angle += 1)
  {
    // Tell servo that adjusts the lifting of the grip to go to position "angle"
    hs421servo.write(angle);

    // Wait a specified time [ms]
    delay(10); // also played around with this value when testing
  }
  delay(5000); // again, same delay from activity 2 - also shows the start of step 3

  //STEP 3:

  u = 150;  // chosen speed of rover - same as moving forward
  digitalWrite(M1, HIGH);  // Drive backward (left wheels)
  digitalWrite(M2, LOW); // Drive backward (right wheels)
  analogWrite(E1, u);     // PWM speed command (left wheels)
  analogWrite(E2, u);     // PWM speed command (right wheels)

  delay(6200); // drive backward more distance because we needed to account for the size of the rover so the flag and rover would both be in the square

  u = 0;  // stop the rover
  analogWrite(E1, u);     // PWM speed command (left wheels)
  analogWrite(E2, u);     // PWM speed command (right wheels)
  delay(2000); // another delay to show us when step 4 would begin 

  //STEP 4:

  // lower the flag
  for (angle = 180; angle >= 90; angle -= 1)
  {
    // Tell servo that adjusts the lifting of the grip to go to position "angle"
    hs421servo.write(angle);

    // Wait a specified time [ms]
    delay(10);
  }

  // open the grip
  for (angle = 180; angle >= 0; angle -= 1)
  {
    // Tell the grip servo to go to position "angle"
    hs420servo.write(angle);

    // Wait a specified time [ms]
    delay(10); // this delay was larger to show us the end of the process
  }

  //break;
}
