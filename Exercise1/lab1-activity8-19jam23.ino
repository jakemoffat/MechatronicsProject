/**
2 * @file lab1-activity8-19jam23.ino
3 * @author Jake Moffat (19jam23@queensu.ca)
4 * @brief Brief description of this sketch.
5 * @version 3.1
6 * @date 2022-02-17
7 *
8 */

// initalize pins
#define TRIG 6
#define ECHO 4
#define ledPIN 11

// define needed variables
long dur;
int range;
int range2;

int ledSTATE = LOW;
const long interval = 500;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

int SENSOR = 4;
int sensorPIN = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(ledPIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  dur = pulseIn(ECHO, HIGH);
  range = dur/58;

  if (range < range2) {
    currentMillis = millis();
  }
  if (currentMillis - previousMillis >= interval) {
    digitalWrite(ledPIN, !digitalRead(ledPIN));
    previousMillis = currentMillis;
  }

  if (ledSTATE == LOW) {
    ledSTATE = HIGH;
  }
  else {
    ledSTATE = LOW;
  }

  digitalWrite(ledPIN, ledSTATE);

  range2 = range;
  Serial.print("Your object is: ");
  Serial.print(range);
  Serial.println(" cm away");

  delay(100);

}
