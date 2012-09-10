// Arduino Buildup
// Arduino Commander

// Board Description
// 4,5,6 tied to gnd through resistor

// Globals
int led = 6;

void setup() {
  // Initialize Output Pins
  for (int i=4;i<=6;i++) {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
}

void loop() {
 // Loop through each LED, on, delay, off.
 if (++led>6) led=4;
 digitalWrite(led,HIGH);
 delay(1000);
 digitalWrite(led,LOW);
}  
 
