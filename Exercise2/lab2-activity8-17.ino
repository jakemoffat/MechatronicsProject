/**
 * @file PWM-motor-control.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to drive wheel motors through a motor controller.
 * @version 1.0
 * @date 2021-07-04
 *
 * @copyright Copyright (c) 2021
 *
 */

int E1 = 6; // Left wheel PWM pin (must be a PWM pin)
int M1 = 7; // Left wheel direction digital pin
int E2 = 5; // Right wheel PWM pin (must be a PWM pin)
int M2 = 4; // Right wheel direction digital pin
int times = 0;

void setup()
{
    pinMode(M1, OUTPUT); // Configure pin M1 for output
    pinMode(M2, OUTPUT); // Configure pin M2 for output
}

void loop()
{
    int u = 255; // A variable for the motor PWM command [0-255]

    // Play with this code to write open loop commands to the wheel motors
    // Tell the motor driver board what to do
    digitalWrite(M1, LOW);  // Drive forward (left wheels)
    digitalWrite(M2, HIGH); // Drive forward (right wheels)
        
    analogWrite(E1, u);     // PWM speed command (left wheels)
    analogWrite(E2, u);     // PWM speed command (right wheels)
    delay(2000);

    // Brief delay (perhaps not necessary)

    digitalWrite(M1, HIGH);  // Drive forward (left wheels)
    digitalWrite(M2, LOW); // Drive forward (right wheels)
        
    analogWrite(E1, u);     // PWM speed command (left wheels)
    analogWrite(E2, u);     // PWM speed command (right wheels)
    delay(2000);

    digitalWrite(M1, LOW);  // Drive forward (left wheels)
    digitalWrite(M2, LOW); // Drive forward (right wheels)
    delay(2000);

    digitalWrite(M1, HIGH);  // Drive forward (left wheels)
    digitalWrite(M2, HIGH); // Drive forward (right wheels)
    delay(2000);


    //now FASTER
    u = 255; // A variable for the motor PWM command [0-255]

    // Play with this code to write open loop commands to the wheel motors
    // Tell the motor driver board what to do
    digitalWrite(M1, LOW);  // Drive forward (left wheels)
    digitalWrite(M2, HIGH); // Drive forward (right wheels)
        
    analogWrite(E1, u);     // PWM speed command (left wheels)
    analogWrite(E2, u);     // PWM speed command (right wheels)
    delay(2000);

    // Brief delay (perhaps not necessary)

    digitalWrite(M1, HIGH);  // Drive forward (left wheels)
    digitalWrite(M2, LOW); // Drive forward (right wheels)
        
    analogWrite(E1, u);     // PWM speed command (left wheels)
    analogWrite(E2, u);     // PWM speed command (right wheels)
    delay(2000);

    digitalWrite(M1, HIGH);  // Drive forward (left wheels)
    digitalWrite(M2, HIGH); // Drive forward (right wheels)
    delay(2000);

    digitalWrite(M1, LOW);  // Drive forward (left wheels)
    digitalWrite(M2, LOW); // Drive forward (right wheels)
    delay(2000);
    }
    
