// Left Motor
const int ENA = 9;  
const int IN1 = 8;
const int IN2 = 7;

// Right Motor
const int ENB = 10; 
const int IN3 = 12;
const int IN4 = 11;

// Joystick
const int VRx = A0;
const int VRy = A1;

// Rectangle dimensions
float length = 0;  
float width  = 0;  

// Motor speed + PWM
const float wheel_speed = 20;   // cm/s, tune experimentally
const int PWM_SPEED = 200;      

// Correction factors (tune if one motor drifts)
const float leftCorrection = 0.95;
const float rightCorrection = 1.0;

// Base turn timing
const int baseTurnDelay = 300; // ms for ~90° pivot
const int forwardDelayBuffer = 150; // ms settle time after moving forward

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);

  stopMotors();

  Serial.begin(9600);
  delay(500);
  Serial.println("Enter rectangle length (cm):");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); 
    input.trim();

    if (length == 0) {
      length = input.toFloat();
      Serial.print("Length set to: ");
      Serial.println(length);
      Serial.println("Now enter rectangle width (cm):");
    } 
    else if (width == 0) {
      width = input.toFloat();
      Serial.print("Width set to: ");
      Serial.println(width);
      Serial.println("Stored! Push joystick UP to draw a rectangle.");
    }
  }

  int yValue = analogRead(VRy);
  if (yValue < 200 && length > 0 && width > 0) {
    Serial.println("Joystick UP detected -> Drawing rectangle");
    RectanglePath();
    while (analogRead(VRy) < 200) delay(50);
    delay(500); 
  }
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0); 
}

void ForwardMotor(float distance_cm) {
  int duration = (distance_cm / wheel_speed) * 1000;

  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);  // left forward
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);  // right forward

  analogWrite(ENA, PWM_SPEED * leftCorrection);
  analogWrite(ENB, PWM_SPEED * rightCorrection);

  delay(duration);
  stopMotors();
  delay(forwardDelayBuffer); // let caster settle
}

// Turn left with adaptive timing
void TurnMotorLeft(int turnCount) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   // left backward
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);  // right forward

  int turnDuration = baseTurnDelay;

  // Compensate for caster lag on later turns
  if (turnCount >= 2) {
    turnDuration += 50;  // add ~50 ms for turn 3 and 4
  }

  // Slightly slower PWM during turns to reduce slip
  analogWrite(ENA, PWM_SPEED * 0.8);
  analogWrite(ENB, PWM_SPEED * 0.8);

  delay(turnDuration);
  stopMotors();
  delay(200); // stabilization pause
}

void RectanglePath() {
  for (int i = 0; i < 4; i++) {
    if (i % 2 == 0) {
      ForwardMotor(length);
      delay(1000);
    } else {
      ForwardMotor(width);
      delay(1000);
    }
    TurnMotorLeft(i);
  }
}
