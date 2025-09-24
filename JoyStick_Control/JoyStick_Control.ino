int xPin = A0; 
int yPin = A1; 
int buttonPin = 5; 

void setup() { 
  pinMode(buttonPin, INPUT_PULLUP); 
  Serial.begin(9600); 
} 

void loop() { 
  int xVal = analogRead(xPin); 
  int yVal = analogRead(yPin); 
  int buttonVal = digitalRead(buttonPin); 
  
  Serial.print("X = "); 
  Serial.print(xVal); 
  Serial.print("   Y = "); 
  Serial.print(yVal); 
  Serial.print("   Button = "); 
  Serial.println(buttonVal); 
  
  delay(100); 
}   