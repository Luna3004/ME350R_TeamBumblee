// Left Motor 
const int ENA = 9;  
const int IN1 = 8;
const int IN2 = 7;

// Right Motor
const int ENB = 10; 
const int IN3 = 12;
const int IN4 = 11;

// Away from Wall: 14.5 in 
// Back of Wheel Away from Barricade: 4.5 in 

// Joystick 
const int VRx = A0; 
const int VRy = A1;

const float wheel_speed = 54.5;  // cm/sec approx
const int wheel_radius = 65; 

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);

  Serial.begin(9600);
  stopMotors();

  delay(2000);
}

void loop() {
    int yValue = analogRead(VRy);
    if (yValue < 200) {
      Serial.println("Starting Parallel Parking maneuver...");
      ParallelPark();
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

void ForwardMotor(int duration_ms) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  delay(duration_ms);
  stopMotors();
}

void ReverseMotor(int duration_ms) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  delay(duration_ms);
  stopMotors();
}

// Pivot turn right (in place)
void TurnRight(int duration_ms) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  delay(duration_ms);
  stopMotors();
}

// Pivot turn left (in place)
void TurnLeft(int duration_ms) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  delay(duration_ms);
  stopMotors();
}

void ParallelPark() {
  // Step 1: Move forward slightly
  ForwardMotor(500);  // adjust timing
  delay(500);
  
  // Step 2: Turn wheels right + reverse
  TurnRight(200);  
  ReverseMotor(400);  
  delay(500);

  // Step 3: Turn wheels left + reverse
  TurnLeft(200);
  delay(500);
  
  stopMotors();
  Serial.println("Parallel parking complete!");
}
