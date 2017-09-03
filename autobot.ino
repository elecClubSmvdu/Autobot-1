/* Autobot model 1
 Ravi Prakash , on 27th of aug,2017.. Attempt number 1 
 3 Ultrasonic sensors, 2 ir sensors
 */
#include<SoftwareSerial.h>        // Seial com via BT
#include<Servo.h>                 // Servo operation
#include<math.h>                 // tgm functions
#include<TimerOne.h>              // timer interrupts

int trigPin1=13; //Sensor Trip pin connected to Arduino pin 13
int echoPin1=11;  //Sensor Echo pin connected to Arduino pin 11
float pingTime1;  //time for ping to travel from sensor to target and return
float distance1; //Distance to Target in cm

int trigPin2=12; //Sensor Trip pin connected to Arduino pin 12
int echoPin2=10;  //Sensor Echo pin connected to Arduino pin 10
float pingTime2;  //time for ping to travel from sensor to target and return
float distance2; //Distance to Target in cm

int trigPin3=7; //Sensor Trip pin connected to Arduino pin 7
int echoPin3=8;  //Sensor Echo pin connected to Arduino pin 8
float pingTime3;  //time for ping to travel from sensor to target and return
float distance3; //Distance to Target in cm

const int LeftIR=A0;  // ir sensor on left side
const int RightIR=A1;  // ir sensor on right side

float speedOfSound=34786.7; //Speed of sound in cm/s at 28 degree celcius
int servoControlPin=6; //Servo control  to pin 6

float servoAngle; 
Servo myPointer;  // servo object 

SoftwareSerial Bluetooth(3,2);
String dataInp;


int lm1=3;//left motor pin 1
int lm2=5;//left motor pin 2
int rm1=6;//right motor pin 1
int rm2=9;//right motor pin 2

void setup()
{
  Bluetooth.begin(9600);
  Serial.begin(115200);

pinMode(lm1,OUTPUT);
pinMode(lm2,OUTPUT);
pinMode(rm1,OUTPUT);
pinMode(rm2,OUTPUT);

pinMode(trigPin1,OUTPUT);
pinMode(trigPin2,OUTPUT);
pinMode(trigPin3,OUTPUT);
pinMode(echoPin1,INPUT);
pinMode(echoPin2,INPUT);
pinMode(echoPin3,INPUT);

myPointer.attach(servoControlPin);
}

void loop()                                 // void loop begins
{
while(Bluetooth.available()==0)            // entire operation inside this loop
{
digitalWrite(trigPin1, LOW); //Set trigger pin low
digitalWrite(trigPin2, LOW); //Set trigger pin low
digitalWrite(trigPin3, LOW); //Set trigger pin low
delayMicroseconds(2000); //Let signal settle
digitalWrite(trigPin1, HIGH); //Set trigPin high
digitalWrite(trigPin2, HIGH); //Set trigPin high
digitalWrite(trigPin3, HIGH); //Set trigPin high
delayMicroseconds(15); //Delay in high state
digitalWrite(trigPin1, LOW); //ping has now been sent
digitalWrite(trigPin2, LOW); //ping has now been sent
digitalWrite(trigPin3, LOW); //ping has now been sent
delayMicroseconds(10); //Delay in low state


pingTime1 = pulseIn(echoPin1, HIGH);  //pingTime is presented in microceconds
pingTime2 = pulseIn(echoPin2, HIGH);  //pingTime is presented in microceconds
pingTime3 = pulseIn(echoPin3, HIGH);  //pingTime is presented in microceconds

pingTime1=pingTime1/1000000;
pingTime2=pingTime2/1000000;
pingTime3=pingTime3/1000000;

distance1=speedOfSound*pingTime1;
distance2=speedOfSound*pingTime2;
distance3=speedOfSound*pingTime3;

if(distance2>distance1&&distance2>distance3)
{
  
}
if(distance1>distance2&&distance1>distance3)
{
  
}
if(distance3>distance1&&distance3>distance2)
{
  
}
  
}
// if there's a comand from bt
if(Bluetooth.available()>0)           // control with bluetooth( On/off/other operations)
    {                  
   dataInp=Bluetooth.read();
   BlueMode();                        // calling the function to get bluetooth control
    }

  
}                                    // void loop ends


// bluetooth command mode

void BlueMode()
{                                                 // make my own customised app(Tejabot)

  // speed is minimum 
 if(dataInp=="G1f")      //forward
 {
   analogWrite(lm1,102);
   analogWrite(lm2,0);
   analogWrite(rm1,102);
   analogWrite(rm2,0);
 }

 if(dataInp=="G1b")            //back
 {
   analogWrite(lm1,0);
   analogWrite(lm2,102);
   analogWrite(rm1,0);
   analogWrite(rm2,102);
 }

 if(dataInp=="G1l")          //left
 {
   analogWrite(lm1,0);
   analogWrite(lm2,0);
   analogWrite(rm1,102);
   analogWrite(rm2,0);
 }

 if(dataInp=="G1r")         // right
 {
   analogWrite(lm1,102);
   analogWrite(lm2,0);
   analogWrite(rm1,0);
   analogWrite(rm2,0);
 }

 if(dataInp=="G1dl")       // diag left
 {
   analogWrite(lm1,51);
   analogWrite(lm2,0);
   analogWrite(rm1,102);
   analogWrite(rm2,0);
 }

 if(dataInp=="G1dr")      // diag right
 {
   analogWrite(lm1,102);
   analogWrite(lm2,0);
   analogWrite(rm1,51);
   analogWrite(rm2,0);
 }

 if(dataInp=="G1dlb")    // diag left back
 {
   analogWrite(lm1,0);
   analogWrite(lm2,51);
   analogWrite(rm1,0);
   analogWrite(rm2,102);
 }

 if(dataInp=="G1drb")   // diag  right back
 {
   analogWrite(lm1,0);
   analogWrite(lm2,102);
   analogWrite(rm1,0);
   analogWrite(rm2,51);
 }

 if(dataInp=="G1rot")   //rotate at centre
 {
   analogWrite(lm1,51);
   analogWrite(lm2,0);
   analogWrite(rm1,51);
   analogWrite(rm2,0);
 }

// speed is max

if(dataInp=="G2f")      //forward
 {
   analogWrite(lm1,255);
   analogWrite(lm2,0);
   analogWrite(rm1,255);
   analogWrite(rm2,0);
 }

 if(dataInp=="G1b")            //back
 {
   analogWrite(lm1,0);
   analogWrite(lm2,255);
   analogWrite(rm1,0);
   analogWrite(rm2,255);
 }

 if(dataInp=="G1l")          //left
 {
   analogWrite(lm1,0);
   analogWrite(lm2,0);
   analogWrite(rm1,255);
   analogWrite(rm2,0);
 }

 if(dataInp=="G1r")         // right
 {
   analogWrite(lm1,255);
   analogWrite(lm2,0);
   analogWrite(rm1,0);
   analogWrite(rm2,0);
 }

 if(dataInp=="G1dl")       // diag left
 {
   analogWrite(lm1,102);
   analogWrite(lm2,0);
   analogWrite(rm1,255);
   analogWrite(rm2,0);
 }

 if(dataInp=="G1dr")      // diag right
 {
   analogWrite(lm1,255);
   analogWrite(lm2,0);
   analogWrite(rm1,102);
   analogWrite(rm2,0);
 }

 if(dataInp=="G1dlb")    // diag left back
 {
   analogWrite(lm1,0);
   analogWrite(lm2,102);
   analogWrite(rm1,0);
   analogWrite(rm2,255);
 }

 if(dataInp=="G1drb")   // diag  right back
 {
   analogWrite(lm1,0);
   analogWrite(lm2,255);
   analogWrite(rm1,0);
   analogWrite(rm2,102);
 }

 if(dataInp=="G1rot")   //rotate at centre
 {
   analogWrite(lm1,255);
   analogWrite(lm2,0);
   analogWrite(rm1,0);
   analogWrite(rm2,255);
 }
}

