#include <SoftwareSerial.h>
#include <Servo.h>

#define ENA 5
#define IN1 6
#define IN2 4
#define ENB 3
#define IN3 8
#define IN4 7
#define TRIG A0
#define ECHO A1
#define SERVO_PIN 9

Servo scanner;
int speedVal = 110;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  scanner.attach(SERVO_PIN);
  scanner.write(90);
  Serial.begin(9600);
}

void loop() {
  int frontDist = getDistance();

  Serial.print("Front: ");
  Serial.println(frontDist);

  if (frontDist > 50) {
    forward();
  }
  else {
    stopRobot();
    delay(300);

    backward();
    delay(800);

    stopRobot();
    delay(300);

    scanner.write(160);
    delay(600);
    int leftDist = getDistance();

    scanner.write(20);
    delay(600);
    int rightDist = getDistance();

    scanner.write(90);
    delay(400);

    if (leftDist > rightDist) {
      turnLeft();
      delay(1000);
    }
    else {
      turnRight();
      delay(1000);
    }

    stopRobot();
    delay(200);
  }
}

int getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  if (distance == 0)
    distance = 300;

  return distance;
}

void forward() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
