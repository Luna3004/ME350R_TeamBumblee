// Left 
const int ENA = 9;   
const int IN1 = 8;
const int IN2 = 7;

// Right
const int ENB = 10;  
const int IN3 = 12;
const int IN4 = 11;

void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("L298N Driver Start.");
  stopMotors();
  delay(500);
}

void loop() {
 
  Serial.println("Left Motor Forward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(ENA, HIGH); 
  delay(2000);

  Serial.println("Left Motor Backward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(ENA, HIGH);
  delay(2000);

  stopMotors();
  delay(1000);

  Serial.println("Right Motor Forward");
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(ENB, HIGH);
  delay(2000);

  Serial.println("Right Motor Backward");
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(ENB, HIGH);
  delay(2000);

  stopMotors();
  delay(1000);

 // PWM Increase Test 
  Serial.println("PWM ramp forward both motors");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);

  for (int s = 0; s <= 255; s += 25) {
    analogWrite(ENA, s);
    analogWrite(ENB, s);
    Serial.print("PWM = "); Serial.println(s);
    delay(250);
  }

  stopMotors();
  Serial.println("Stop");

  while (1) { delay(1000); } 
}

// Stop Function
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}
