int enL = 6;           // Enable: Digital Pin 6 for Left Motor
int enR = 11;          // Enable: Digital Pin 11 for Right Motor

int inL1 = 7;          // Left Motor, Side 1: Digital Pin 7
int inL2 = 8;          // Left Motor, Side 2: Digital Pin 8
int inR1 = 12;         // Right Motor, Side 1: Digital Pin 12
int inR2 = 13;         // Right Motor, Side 2: Digital Pin 13

// Ultrasonic Sensor
int trigPin = 1;
int echoPin = 0;

int minimumRange = 0;
int maximumRange = 100;

// Line Tracker Sensor
int lineSensor = 2;

// Global variables
double duration, distance, totalDistance;

void setup() {
  Serial.begin(9600);   // Allow for Serial monitor printing. Used for debugging.
  pinMode(enL, OUTPUT);
  pinMode(enR, OUTPUT);
  pinMode(inL1, OUTPUT);
  pinMode(inL2, OUTPUT);
  pinMode(inR1, OUTPUT);
  pinMode(inR2, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(lineSensor, INPUT);

  delay(3000);
}

void moveForward(int lWheel) 
{
  
  analogWrite(enL, lWheel);
  digitalWrite(inL1, HIGH);
  digitalWrite(inL2, LOW);

  analogWrite(enR, lWheel);
  digitalWrite(inR1, HIGH);
  digitalWrite(inR2, LOW);
}


void moveBackward(int rWheel) 
{
  analogWrite(enL, rWheel);
  digitalWrite(inL1, LOW);
  digitalWrite(inL2, HIGH);

  analogWrite(enR, rWheel);
  digitalWrite(inR1, LOW);
  digitalWrite(inR2, HIGH);
}

void moveStop() {
  analogWrite(enL, 0);
  digitalWrite(inL1, LOW);
  digitalWrite(inL2, LOW);

  analogWrite(enR, 0);
  digitalWrite(inR1, LOW);
  digitalWrite(inR2, LOW);  
}

void turnAround(int speed) {
  analogWrite(enL, speed);
  digitalWrite(inL1, LOW);
  digitalWrite(inL2, HIGH);

  analogWrite(enR, speed);
  digitalWrite(inR1, HIGH);
  digitalWrite(inR2, LOW);  
}

double ultrasonicSensor() {
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);

 Serial.println(duration/58.2);
 return duration/58.2; // in cm
}

void loop() {
  ultrasonicSensor();
 
  Serial.println(digitalRead(lineSensor)); // Black is 0 and White is 1
  while(digitalRead(lineSensor) == 0) {
    if(ultrasonicSensor() > 20) {
      turnAround(255);
    } else {
      moveForward(255);      
    }
  }
  while(digitalRead(lineSensor) == 1) {
    turnAround(255);
    delay(3000);
    moveForward(255);
    delay(500);
    break;
  }

}
