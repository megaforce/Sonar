#include <Servo.h>

  Servo myservo;
  const int trigPin = 9;
  const int echoPin = 10;
  int pos = 0; 
  float duration;
  int distance;
  String data;
  
void setup() {
  myservo.attach(8);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(4800);
  
}

void loop() {

  for (pos = 0; pos <= 180; pos += 5) {    
    myservo.write(pos); 
    delay(15);   
    digitalWrite(trigPin, LOW);  
    digitalWrite(trigPin, HIGH);  
    digitalWrite(trigPin, LOW);  
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    data += pos;
    data += "|||";
    if (distance < 25){
    data += distance;
    }
    if (data.length() < 4 && data.length() > 11)
    data = "";  
    else
    Serial.print(data);
    delay(325);
    data = "";          
  }
  for (pos = 180; pos >= 0; pos -= 5) { 
    myservo.write(pos); 
    delay(15); 
    digitalWrite(trigPin , LOW);  
    digitalWrite(trigPin, HIGH);  
    digitalWrite(trigPin, LOW);  
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;    
    data += pos;
    data += "|||";
    if (distance < 25 ){
    data += distance;
    }
    if (data.length() < 4 && data.length() > 11)
    data = "";  
    else
    Serial.print(data);
    delay(325);
    data = "";                      
  }


}
