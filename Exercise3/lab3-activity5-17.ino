/**
 * @file sharp-sensor.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to read proximity data from a Sharp GP2Y0A21YK.
 * @version 1.0
 * @date 2021-11-16
 *
 * @copyright Copyright (c) 2021
 *
 */

// Arduino analog input pin to which the Sharp sensor is connected
const byte SHARP_PIN = 2;
//const byte SHARP_PIN1 = 1;
//const byte SHARP_PIN2 = 0;

// Motor driver PWM pin
const byte E1 = 6;

// Motor driver direction pin
const byte M1 = 7;

// Motor driver PWM pin
const byte E2 = 4;

// Motor driver direction pin
const byte M2 = 5;

// Left wheel encoder digital pins
const byte SIGNAL_A = 2;
const byte SIGNAL_B = 3;

//Right wheel encoder digital pins
const byte SIGNAL_C = 8;
const byte SIGNAL_D = 9;

// Variable to store the proximity measurement
int sharp_val = 0;
//int sharp_val1 = 0;
//int sharp_val2 = 0;

int distanceCM;
//int distanceCM1;
//int distanceCM2;

void setup()
{
    // Open the serial port at 9600 bps
    Serial.begin(9600);
    pinMode(M1, OUTPUT); // Configure pin M1 for output
    pinMode(M2, OUTPUT); // Configure pin M2 for output
}

void loop()
{
    // Read the sensor output (0-1023, or 10 bits)
    sharp_val = analogRead(SHARP_PIN);
    //sharp_val1 = analogRead(SHARP_PIN1);
    //sharp_val2 = analogRead(SHARP_PIN2);

    distanceCM = 28908*pow(sharp_val, -1.272);
    //distanceCM1 = 28908*pow(sharp_val1, -1.272);
    //distanceCM2 = 28908*pow(sharp_val2, -1.272);

    // Print the value to the Serial Monitor
    Serial.print(sharp_val);
    Serial.print("\t");
    //Serial.print(sharp_val1);
    //Serial.print("\t");
    //Serial.print(sharp_val2);
    //Serial.print("\n");

    // Print the value to the Serial Monitor
    Serial.print("Distance 1: ");
    Serial.print(distanceCM);
    //Serial.print("\t");
    //Serial.print("DIstance 2: ");
    //Serial.print(distanceCM1);
    //Serial.print("\t");
    //Serial.print("DIstance 3: ");
    //Serial.print(distanceCM2);
    Serial.print("\n");

             
            if (distanceCM < 25){
              digitalWrite(M1, LOW);  // Drive forward (left wheels)
              digitalWrite(M2, HIGH);
              analogWrite(E1, 0);     // PWM speed command (left wheels)
              analogWrite(E2, 0); 
              delay(3000);
              digitalWrite(M1, LOW);  // Drive forward (left wheels)
              digitalWrite(M2, LOW);
              analogWrite(E1, 220);     // PWM speed command (left wheels)
              analogWrite(E2, 220); 
              delay(200);
              } else {
               digitalWrite(M1, LOW);  // Drive forward (left wheels)
              digitalWrite(M2, HIGH);
              analogWrite(E1, 200);     // PWM speed command (left wheels)
              analogWrite(E2, 200); 
                } 


    // Delay for a bit before reading the sensor again
    delay(500);
}
