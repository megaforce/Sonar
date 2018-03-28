
#include <Servo.h>

  Servo myservo;
  const int trigPin = 9;
  const int echoPin = 10;
  int pos = 0;  
  
  float duration, distance;

void setup() {
  myservo.attach(8);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  for (pos = 0; pos <= 180; pos += 5) {    
    myservo.write(pos);   
    digitalWrite(trigPin, LOW);  
    digitalWrite(trigPin, HIGH);  
    digitalWrite(trigPin, LOW);  
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    Serial.println(distance);
    delay(100);
    delay(15);                       
  }
  for (pos = 180; pos >= 0; pos -= 5) { 
    myservo.write(pos); 
    digitalWrite(trigPin, LOW);  
    digitalWrite(trigPin, HIGH);  
    digitalWrite(trigPin, LOW);  
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    Serial.println(distance);
    delay(100);
    delay(15);                      
  }


}
