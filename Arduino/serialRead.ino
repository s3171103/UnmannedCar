/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int a;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600);  
}

// the loop routine runs over and over again forever:
void loop() {
  String s="";
  while(Serial.available()){
    char a = Serial.read();
    if(a!='\n'){
      s += a;
    }
    delay(1);
  }
  
  if(s!=""){
    Serial.println(s);
  }
//  while(Serial.available()){
//    Serial.println(Serial.readString());
//  }
}
