const int xPin = A0;     // X-axis
const int yPin = A1;     // Y-axis 
const int buttonPin = 5; 

// Left Motor 
const int ENA = 9;  
const int IN1 = 8;
const int IN2 = 7;

// Right Motor
const int ENB = 10; 
const int IN3 = 12;
const int IN4 = 11;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  stopMotors();
}

void loop() {
  int xVal = analogRead(xPin);
  int yVal = analogRead(yPin);


  int xPos = xVal - 512;
  int yPos = yVal - 512;

  if (abs(xPos) < 100) xPos = 0;
  if (abs(yPos) < 100) yPos = 0;

  if (yPos > 0) {
    // Forward
    setMotor(ENA, IN1, IN2, 200);
    setMotor(ENB, IN3, IN4, 200);
  } 
  else if (yPos < 0) {
    // Backward
    setMotor(ENA, IN1, IN2, -200);
    setMotor(ENB, IN3, IN4, -200);
  }
  else if (xPos > 0) {
    setMotor(ENA, IN1, IN2, 200);
    setMotor(ENB, IN3, IN4, 0);
  }
  else if (xPos < 0) {
    setMotor(ENA, IN1, IN2, 0);
    setMotor(ENB, IN3, IN4, 200);
  }
  else {
    stopMotors();
  }

  delay(100);
}

void setMotor(int EN, int INa, int INb, int speed) {
  if (speed > 0) {            // forward
    digitalWrite(INa, HIGH);
    digitalWrite(INb, LOW);
    analogWrite(EN, speed);
  } else if (speed < 0) {     // backward
    digitalWrite(INa, LOW);
    digitalWrite(INb, HIGH);
    analogWrite(EN, -speed);
  } else {                    // stop
    digitalWrite(INa, LOW);
    digitalWrite(INb, LOW);
    analogWrite(EN, 0);
  }
}

void stopMotors() {
  setMotor(ENA, IN1, IN2, 0);
  setMotor(ENB, IN3, IN4, 0);
}
