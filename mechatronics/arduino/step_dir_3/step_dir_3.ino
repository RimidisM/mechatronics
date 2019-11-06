#define F_CPU 16000000
#define StepPinA 2
#define encoderB 5
#define encoderA 3
volatile long Step = 0;


double PV, Output, Setpoint;
double kp, ki, kd;
volatile unsigned long lastTime;
volatile double errSum, lastErr;
volatile long encoder0Pos = 0;
int Dir = 12;
int motor1 =10;
int motor2 =8;
int MotorPWM=6;

void setup() {
  
  pinMode(StepPinA, INPUT); 
  pinMode(Dir, INPUT);
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(MotorPWM, OUTPUT);
  // put your setup code here, to run once:
attachInterrupt(1, doEncoder, CHANGE);
attachInterrupt(0, doStep, RISING);

// Parametrai:
kp = 2;
ki = 0;
kd = 1;
Serial.begin (115200);
Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,Setpoint,PV,Output");;
}

void loop(){
  Setpoint =(double)Step;
  PV = (double)encoder0Pos;
  compute();
  Serial.print("DATA,TIME,"); 
  Serial.print(Setpoint);
   Serial.print(",");
Serial.print(PV);
Serial.print(",");
Serial.println(Output);

  if(Output > 0) {
analogWrite(MotorPWM, Output);
CC();
}
else if(Output < -0){
analogWrite(MotorPWM, -Output);
CCW();
}
else{
STOP();
}
// display setpoint and measured value

}
void CC(){
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);

}
void CCW(){
digitalWrite(motor1,LOW);
digitalWrite(motor2,HIGH);
}
void STOP(){
digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
}
void compute()
{
/*How long since we last calculated*/
unsigned long now = millis();
double dT = (double)(now - lastTime); //Our Sampling time
/*Compute all the working error variables*/
double error = Setpoint - PV;
errSum = (error * dT);
double dErr = (error - lastErr) / dT;
/*Compute PID Output*/
Output = kp * error + ki * errSum + kd * dErr;
/*Remember some variables for next time*/
/*Max 100, Min -100*/
if(Output>255){Output = 255;}
else if(Output <-255){Output = -255;}
else{}
lastErr = error;
lastTime = now;
}
void doEncoder(){
if ((digitalRead(encoderA)== HIGH)&&(digitalRead(encoderB) == LOW)) {   // found a low-to-high on channel A
     // check channel B to see which way
                                             // encoder is turning
      encoder0Pos = encoder0Pos - 1;         // CCW
    } 
 if ((digitalRead(encoderA)== HIGH)&&(digitalRead(encoderB) == HIGH)) {
      encoder0Pos = encoder0Pos + 1;         // CW
    }
 
  }
void doStep(){
  int Direction = digitalRead(Dir);
  if (digitalRead(Dir) == LOW) {
    Step= Step+1;}
if (digitalRead(Dir) == HIGH) {
    Step= Step-1;}
}

