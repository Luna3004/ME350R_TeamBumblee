// Left Motor 
const int ENA = 9;  
const int IN1 = 8;
const int IN2 = 7;

// Right Motor
const int ENB = 10; 
const int IN3 = 12;
const int IN4 = 11;

float length = 0; 
float width = 0;  
const float wheel_speed = 54.5;
const int wheel_radius = 65; 

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  stopMotors();

  while (!Serial) {
    ;
  }
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

      RectanglePath();  
    }
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

  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  delay(duration);
  stopMotors();
}

void TurnMotorLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  delay(800); // adjust
  stopMotors();
}


void RectanglePath() {
  ForwardMotor(length);
  TurnMotorLeft();
  delay(500);

  ForwardMotor(width);
  TurnMotorLeft();
  delay(500);

  ForwardMotor(length);
  TurnMotorLeft();
  delay(500);

  ForwardMotor(width);
  TurnMotorLeft();
  delay(500);

}
