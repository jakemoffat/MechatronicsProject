/**
 * @file motor-angular-rate.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to estimate motor speed from encoder.
 * @version 1.0
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

// Motor driver PWM pin
const byte E1 = 6;

// Motor driver direction pin
const byte M1 = 7;

// Motor driver PWM pin
const byte E2 = 4;

// Motor driver direction pin
const byte M2 = 5;

// Motor PWM command variable [0-255]
byte u = 0;

// Left wheel encoder digital pins
const byte SIGNAL_A = 2;
const byte SIGNAL_B = 3;

//Right wheel encoder digital pins
const byte SIGNAL_C = 8;
const byte SIGNAL_D = 9;

// Encoder ticks per (motor) revolution (TPR)
const int TPR = 3000;

// Wheel radius [m]
const double RHO_LEFT = 0.0625;
const double RHO_RIGHT = 0.0625;

// Counter to keep track of encoder ticks [integer]
volatile long encoder_ticks_left = 0;
volatile long encoder_ticks_right = 0;

// Variable to store estimated angular rate of left wheel [rad/s]
double omega_L_LEFT = 0.0;
double omega_L_RIGHT = 0.0;

// Sampling interval for measurements in milliseconds
//const int T = 1000; to change to 5Hz f = 1/T
//Therefore, the new T = 200
const int T = 200;

// Counters for milliseconds during interval
long t_now = 0;
long t_last = 0;

//Variable for Linear Speed
double v_L_LEFT = 0;
double v_L_RIGHT = 0;

// This function is called when SIGNAL_A goes HIGH
void decodeEncoderLeftTicks()
{
    if (digitalRead(SIGNAL_B) == LOW)
    {
        // SIGNAL_A leads SIGNAL_B, so count one way
        encoder_ticks_left--;
    }
    else
    {
        // SIGNAL_B leads SIGNAL_A, so count the other way
        encoder_ticks_left++;
    }
}

void decodeEncoderRightTicks()
{
    if (digitalRead(SIGNAL_D) == LOW)
    {
        // SIGNAL_C leads SIGNAL_D, so count one way
        encoder_ticks_right++;
    }
    else
    {
        // SIGNAL_D leads SIGNAL_C, so count the other way
        encoder_ticks_right--;
    }
}

void setup()
{
    // Open the serial port at 9600 bps
    Serial.begin(9600);

    // Set the pin modes for the motor driver
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);

    // Set the pin modes for the encoders
    pinMode(SIGNAL_A, INPUT); //left wheel
    pinMode(SIGNAL_B, INPUT); //left wheel
    pinMode(SIGNAL_C, INPUT); //right wheel
    pinMode(SIGNAL_D, INPUT); //right wheel

    // Every time the pin goes high, this is a pulse
    attachInterrupt(digitalPinToInterrupt(SIGNAL_A), decodeEncoderLeftTicks, RISING);
    attachInterrupt(digitalPinToInterrupt(SIGNAL_C), decodeEncoderRightTicks, RISING);


    // Print a message
    Serial.print("Program initialized.");
    Serial.print("\n");
}

void loop()
{
    // Get the elapsed time [ms]
    t_now = millis();

    if (t_now - t_last >= T)
    {
        // Estimate the rotational speed [rad/s]
        omega_L_LEFT = 2.0 * PI * ((double)encoder_ticks_left / (double)TPR) * 1000.0 / (double)(t_now - t_last);
        omega_L_RIGHT = 2.0 * PI * ((double)encoder_ticks_right / (double)TPR) * 1000.0 / (double)(t_now - t_last);


        v_L_LEFT = RHO_LEFT * omega_L_LEFT;
        v_L_RIGHT = RHO_RIGHT * omega_L_RIGHT;

        // Print some stuff to the serial monitor
        Serial.print("Left Encoder ticks: ");
        Serial.print(encoder_ticks_left);
        Serial.print("\t");
        Serial.print("Right Encoder ticks: ");
        Serial.print(encoder_ticks_right);
        Serial.print("\t");
        //Serial.print("Estimated left wheel (angular) speed: ");
        //Serial.print(omega_L);
        //Serial.print(" rad/s");
        //Serial.print("\n");

        Serial.print("Estimated LEFT wheel (linear) speed: ");
        Serial.print(v_L_LEFT);
        Serial.print(" m/s");
        Serial.print("\t");

        Serial.print("Estimated RIGHT wheel (linear) speed: ");
        Serial.print(v_L_RIGHT);
        Serial.print(" m/s");
        Serial.print("\n");

        // Record the current time [ms]
        t_last = t_now;

        // Reset the encoder ticks counter
        encoder_ticks_left = 0;
        encoder_ticks_right = 0;
    }

    // Set the wheel motor PWM command [0-255]
    u = 128;

    // Write to the output pins
    digitalWrite(M1, LOW); // Drive forward (left wheels)
    analogWrite(E1, u);    // Write left motors command

    digitalWrite(M2, HIGH); // Drive forward (left wheels)
    analogWrite(E2, u);    // Write left motors command
}
