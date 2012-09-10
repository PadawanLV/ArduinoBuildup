// Arduino Buildup
// Arduino Commander

// Board Description
// 4,5,6 LED tied to gnd through resistor
// 7,8,9 input switchs, N/O, through resistor to grnd

// Defines
#define MAXCMD 50            // Max Command Length

// Includes
#include <string.h>

// Globals
char b;                     // Input buffer
char cmd[MAXCMD+1] = {""};  // Command buffer

// Input buttons
int btn[3]={1,1,1};         // Button Status Register

void setup() {
  // Initialize Output Pins
  for (int i=4;i<=6;i++) {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
    pinMode(i+3,INPUT_PULLUP);
  }
  // Start up Serial
  Serial.begin(9600);
  Serial.println("Arduino Commander v1.2");
  Ready();
}

void loop() {
 
  //: Read Serial Port, build command
  if (Serial.available()) {
    b = Serial.read();
    //: If /, then process command
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
 
  // Input Polling
  int dirty = 0;
  for (int i=7;i<=9;i++) {
    b=digitalRead(i);
    if (b!=btn[i-7]) {
      btn[i-7]=b;
      dirty = 1;
    }
  }
  if (dirty) {
    Serial.println("");
    Serial.print("Input Value = ");
    Serial.println(btn[0] + btn[1]*2 + btn[2]*4);
  }
  
}  
 
// Command Processor
void ProcessCommand(){
  
  Serial.println();
  Serial.println(cmd);
 
  // HELP
  if (strcasestr(cmd,"HELP")) {
    Syntax();
    return;
  }
  
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
  Syntax();
}

void Syntax() {
  Serial.println("");
  Serial.println("SYNTAX: COMMAND/");
  Serial.println("PORT(4-6) ACTION(ON/OFF) ie: 4 ON/");
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
