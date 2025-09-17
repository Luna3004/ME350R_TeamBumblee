// Pin connections for motor driver
#define ENA 9     // Enable/speed pin for left motor (PWM)
#define IN1 8     // Left motor forward
#define IN2 7     // Left motor backward

#define ENB 10    // Enable/speed pin for right motor (PWM)
#define IN3 6     // Right motor forward
#define IN4 5     // Right motor backward

// Joystick pins
#define JOY_X A0  // Left-right axis
#define JOY_Y A1  // Forward-back axis

int xValue, yValue;
int motorSpeedLeft, motorSpeedRight;

void setup() {
  // Motor pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize motors OFF
  stopMotors();

  Serial.begin(9600);
}

void loop() {
  // Read joystick values (0–1023)
  xValue = analogRead(JOY_X);
  yValue = analogRead(JOY_Y);

  // Center joystick around 0 (-512 to +512)
  int xAxis = xValue - 512;
  int yAxis = yValue - 512;

  // Deadzone (to prevent drift)
  int deadzone = 50;
  if (abs(xAxis) < deadzone) xAxis = 0;
  if (abs(yAxis) < deadzone) yAxis = 0;

  // Mix joystick values into motor speeds
  motorSpeedLeft  = yAxis + xAxis;
  motorSpeedRight = yAxis - xAxis;

  // Map motor speed to PWM (0–255)
  motorSpeedLeft  = map(motorSpeedLeft,  -512, 512, -255, 255);
  motorSpeedRight = map(motorSpeedRight, -512, 512, -255, 255);

  // Run motors
  setMotor(ENA, IN1, IN2, motorSpeedLeft);
  setMotor(ENB, IN3, IN4, motorSpeedRight);

  delay(20);
}

// Function to control a motor
void setMotor(int EN, int INa, int INb, int speed) {
  if (speed > 0) {
    digitalWrite(INa, HIGH);
    digitalWrite(INb, LOW);
    analogWrite(EN, speed);
  } else if (speed < 0) {
    digitalWrite(INa, LOW);
    digitalWrite(INb, HIGH);
    analogWrite(EN, -speed);
  } else {
    digitalWrite(INa, LOW);
    digitalWrite(INb, LOW);
    analogWrite(EN, 0);
  }
}

// Stop all motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
