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

float radius = 0; 
const float wheelbase = 15.3; 
const int PWM_BASE = 150; //150   

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

  delay(500);
  Serial.println("Enter circle radius (cm):");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); 
    input.trim();
    radius = input.toFloat();

    if (radius > 0) {
      Serial.print("Radius set to: ");
      Serial.println(radius);
      Serial.println("Push joystick UP to draw a circle.");
    }
  }

  int yValue = analogRead(VRy);
  if (yValue < 200 && radius > 0) {
    Serial.println("Joystick UP detected -> Drawing circle");
    CirclePath(radius);

    while (analogRead(VRy) < 200) {
      delay(50);
    }
    delay(500); 
  } 
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0); 
}

void CirclePath(float R) {
  const float L = wheelbase;   // distance between wheels (15.3 cm)
  const float MIN_PWM = 45;    // prevents TT motors from stalling
  const float outerCorrection = 0.80; // slows down outer wheel slightly

  // Compute wheel ratios
  float ratio_L = (R - L/2) / R; // inner wheel
  float ratio_R = (R + L/2) / R; // outer wheel

  // Compute PWM values
  int leftPWM  = constrain(PWM_BASE * ratio_L * outerCorrection, MIN_PWM, 255);
  int rightPWM = constrain(PWM_BASE * ratio_R, MIN_PWM, 255);

  // Set motor directions
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   // left forward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);   // right forward

  // Apply PWM
  analogWrite(ENA, leftPWM);
  analogWrite(ENB, rightPWM);

  // Compute time to complete circle
  float circumference = 2 * 3.1416 * R;  // cm
  float speed = 30;                       // cm/s (tune if needed)
  int duration = (circumference / speed) * 1000;

  delay(duration);
  stopMotors();
}

