 #define encoder0PinA 2

#define encoder0PinB 3
int a;
int b;
int c;

volatile unsigned int encoder0Pos = 0;
float poslinkis;

void setup() {
  Serial.begin (9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,ILINKIS"); 

  pinMode(encoder0PinA, INPUT); 
  pinMode(encoder0PinB, INPUT); 

// encoder pin on interrupt 0 (pin 2)

  attachInterrupt(0, doEncoderA, CHANGE);

// encoder pin on interrupt 1 (pin 3)

  attachInterrupt(1, doEncoderB, CHANGE);  

  

}

void loop(){ //Do stuff here 
poslinkis=encoder0Pos/55.88;
if (a == 1) {
  c = 2;
}
if ((a == 2) && (c == 2)) {
//Serial.print (encoder0Pos, DEC);
Serial.print("DATA,TIME,");
//Serial.print ( ',' ); 
Serial.println (poslinkis); 
//Serial.println (a);
//Serial.println (b);
//Serial.println (c);
c = 1;
}
}
void doEncoderA(){

  // look for a low-to-high on channel A
  if (digitalRead(encoder0PinA) == HIGH) { 

    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == LOW) {  
      encoder0Pos = encoder0Pos + 1;         // CW
      a = 1;
    } 
    else {
      encoder0Pos = encoder0Pos - 1;      // CCW
      a = 2;
    }
  }

  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinB) == HIGH) {   
      encoder0Pos = encoder0Pos + 1;          // CW
      a = 1;
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
      a = 2;
    }
  }
          
  // use for debugging - remember to comment out

}

void doEncoderB(){

  // look for a low-to-high on channel B
  if (digitalRead(encoder0PinB) == HIGH) {   

   // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == HIGH) {  
      encoder0Pos = encoder0Pos + 1;         // CW
      a  = 1;
    } 
    else {
      encoder0Pos = encoder0Pos - 1;         // CCW
      a = 2;
    }
  }

  // Look for a high-to-low on channel B

  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinA) == LOW) {   
      encoder0Pos = encoder0Pos + 1;          // CW
      a = 1;
    } 
    else {
      encoder0Pos = encoder0Pos - 1;          // CCW
      a = 2;
    }
  }

} 
