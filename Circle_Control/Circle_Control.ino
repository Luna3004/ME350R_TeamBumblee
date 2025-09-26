// Left Motor 
const int ENA = 9;  
const int IN1 = 8;
const int IN2 = 7;

// Right Motor
const int ENB = 10; 
const int IN3 = 12;
const int IN4 = 11;

float radius = 0; // cm
const float wheelbase = 15.3; // cm

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  stopMotors();

  while (!Serial) { ; }
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
      CirclePath(radius);  
    }
  }
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0); 
}

// Circle motion
void CirclePath(float R) {

  int speed_PWM = 200;  

  float leftRatio  = (R - (wheelbase / 2)) / R;
  float rightRatio = (R + (wheelbase / 2)) / R;

  int leftspeed  = constrain(speed_PWM * leftRatio, 0, 255);
  int rightspeed = constrain(speed_PWM * rightRatio, 0, 255);

  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);

  analogWrite(ENA, leftspeed);
  analogWrite(ENB, rightspeed);

  float circumference = 2 * 3.1416 * R; // cm
  float speed = 54.5; // cm/s
  int duration = (circumference / speed) * 1000; // ms

  delay(duration);

  stopMotors();
}
