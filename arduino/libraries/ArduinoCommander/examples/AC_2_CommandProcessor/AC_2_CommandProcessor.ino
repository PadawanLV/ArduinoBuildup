// Arduino Buildup
// Arduino Commander

// Board Description
// 4,5,6 tied to gnd through resistor

// Defines
#define MAXCMD 50            // Max Command Length

// Includes
#include <string.h>

// Globals
char b;                     // Input buffer
char cmd[MAXCMD+1] = {""};  // Command buffer

void setup() {
  // Initialize Output Pins
  for (int i=4;i<=6;i++) {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
  // Start up Serial
  Serial.begin(9600);
  Serial.println("Arduino Commander v1.2");
  Ready();
}

void loop() {
 
  // Read Serial Port, build command
  if (Serial.available()) {
    b = Serial.read();
    // If /, then process command
    if (b=='/') {
      ProcessCommand();
      return;
    }
    int i = strlen(cmd);
    if (i < MAXCMD) {
      cmd[i] = b;
      cmd[i+1]= 0;
      return; 
    }
  }
}  
 
// Command Processor
void ProcessCommand(){
  Serial.println();
  Serial.println(cmd);

  // Command
  b = cmd[0] - '0';
  if (b>=4 && b<=6) {
    // valid Port Number
    Serial.println("");
    Serial.print("Port ");
    Serial.print(b,DEC);
    Serial.print(" set ");
    if (strcasestr(cmd,"ON")) {
      digitalWrite(b,HIGH);
      Serial.println("ON");
    }
    else {
      digitalWrite(b,LOW);
      Serial.println("OFF");
    }
    Ready();
    return;
  }

  // Syntax Error
  Serial.println("Syntax Error!");
  Ready();
}
  
// Ready Prompt
void Ready() {
  Serial.println("");
  Serial.print("Ready >");
  ClearCMD();
}

void ClearCMD(){
 for (int i=0;i<MAXCMD;i++) cmd[i]=0;
}
