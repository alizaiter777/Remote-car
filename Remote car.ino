#include <IRremote.h>

const int RemotePin = 12;
IRrecv irrecv(RemotePin);
decode_results results;

int in1 = 3;
int in2 = 4;
int in3 = 7;
int in4 = 9;

double cm = 0, inches = 0;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT); 
  pinMode(13, INPUT); 
 
}

void loop() {
  // ENA pin 
  analogWrite(10, 200);
  analogWrite(5, 200);

  cm = readUltrasonicDistance(8, 13); 
  Serial.print(cm);
  Serial.println("cm, ");

  if (cm <= 10) {
    if (irrecv.decode(&results)) {
      if (results.value == 0xE785F8D4 || results.value == 0x395C59A0) {
        backward();
        Serial.println("Obstacle detected! Moving backward.");
        
      } else {
        stop();
        Serial.println("Obstacle detected! Only backward movement allowed.");
        
      }
      irrecv.resume();
    } else {
      stop();
      Serial.println("Obstacle detected! Only backward movement allowed.");
    }
  } else {
    if (irrecv.decode(&results)) {
      if (results.value == 0xEB150A80 || results.value == 0xE2F4C194) {
        forward();
      } else if (results.value == 0xE785F8D4 || results.value == 0x395C59A0) {
        backward();
      } else if (results.value == 0xE3F4C327 || results.value == 0xEC150C13) {
        left();
      } else if (results.value == 0x8F73BFF || results.value == 0x111784EB) {
        right();
      } else if (results.value == 0xB4C0B9DB || results.value == 0x62EA590F) {
        stop();
      }
      irrecv.resume();
    }
  }
}

int readUltrasonicDistance(int triggerPin, int echoPin) {
  int distance;
  digitalWrite(triggerPin, LOW);
  delay(30);
  digitalWrite(triggerPin, HIGH);
  delay(30);
  digitalWrite(triggerPin, LOW);
  distance = pulseIn(echoPin, HIGH) / 2 / 29;
  return distance;
}


void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
