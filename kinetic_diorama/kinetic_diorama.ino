#include <WiFi.h>
#include <ESP32Servo.h>
#include <HTTPClient.h>
//stepper
int outPorts[] = {14, 27, 26, 25};
//servo
Servo myservo;  // create servo object to control a servo
int posVal = 0;    // variable to store the servo position
int servoPin = 12; // Servo motor pin
//button
#define pin_button1 34
boolean fire = false;
boolean ignore = false;
//wifi
const char *ssid_Router     = "asdfasdfa";//change this to your router name
const char *password_Router = "asdfasdf";//change this to your router password
String address= "http://165.227.76.232:3000/bnh2128/running"; // the url

void setup() {
  Serial.begin(9600);//115200
  //stepper
  for (int i = 0; i < 4; i++) {
    pinMode(outPorts[i], OUTPUT);
  }
  //servo
  myservo.setPeriodHertz(50);           // standard 50 hz servo
  myservo.attach(servoPin, 500, 2500);  // attaches the servo on servoPin to the servo object
  //button
  pinMode(pin_button1,INPUT);

  moveServo(0,0);
  //wifi
  WiFi.begin(ssid_Router, password_Router);
  Serial.println(String("Connecting to ")+ssid_Router);
  while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
  }
  Serial.println("\nConnected, IP address: ");
  Serial.println(WiFi.localIP());

}
void moveServo(int _start, int _end){
    for (int posVal =  _start = 0; posVal <= _end; posVal += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(posVal);       // tell servo to go to position in variable 'pos'
    delay(15);                   // waits 15ms for the servo to reach the position
  }
}
//stepper
void moveSteps(bool dir, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    moveOneStep(dir); // Rotate a step
    delay(constrain(ms,3,20));        // Control the speed
  }
}

void moveOneStep(bool dir) {
  // Define a variable, use four low bit to indicate the state of port
  static byte out = 0x01;
  // Decide the shift direction according to the rotation direction
  if (dir) {  // ring shift left
    out != 0x08 ? out = out << 1 : out = 0x01;
  }
  else {      // ring shift right
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }
  // Output singal to each port
  for (int i = 0; i < 4; i++) {
    digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
  }
}

void moveAround(bool dir, int turns, byte ms){
  for(int i=0;i<turns;i++)
    moveSteps(dir,32*64,ms);
}
//
void loop() {
  //wifi stuff
  if(!ignore && (WiFi.status() == WL_CONNECTED)) {
      HTTPClient http;
      http.begin(address);
    int httpCode = http.GET(); // start connection and send HTTP header
    if (httpCode == HTTP_CODE_OK) { 
        String response = http.getString();
        if (response.equals("false")){
            //off
            if (fire){
              moveServo(22,0);
              ignore = false;
              fire = false;  
            }
            moveSteps(true, 32 * 64, 3);
        }else if(response.equals("true")){
             // Shoot
             if (!fire){//if already not firing,move servo
              moveServo(0,22);
              fire = true;
              ignore = true;
            }
        }
    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    delay(500); //delay
  }
  if(digitalRead(pin_button1)==LOW){
    //pressed, activate firing mech
    if (!fire){//if already not firing,move servo
      moveServo(0,22);
      fire = true;
    }
    
  }else{
    if (fire){
      moveServo(22,0);
      fire = false;  
    }
    moveSteps(true, 32 * 64, 3);
  }

}
