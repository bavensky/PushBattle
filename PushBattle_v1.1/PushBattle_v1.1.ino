#include <Adafruit_NeoPixel.h>

#define stepPin 9
#define dirPin 8 

#define red 3
#define green 2

#define limit_red A1
#define limit_green A0

#define led 5
#define DELAY_UP 30
#define DEBOUSE 200

int mode = 0;
int work = 0;
int state = 1;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, led, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  
  pinMode(red, INPUT_PULLUP);
  pinMode(green, INPUT_PULLUP);
  pinMode(limit_red, INPUT);
  pinMode(limit_green, INPUT);

  strip.begin();
  strip.show();
  
  attachInterrupt(0, red_up, FALLING);
  attachInterrupt(1, green_up, FALLING);
}

void loop() {
  if(state == 1)  {
    rainbow(5);
  }
  if(digitalRead(limit_red) == 0)  {
    delay(DEBOUSE);
        state=2;
      }
  if(digitalRead(limit_green) == 0)  {
    delay(DEBOUSE);
        state=3;
      }
      
  if(state == 2)  {
    for(int l=0; l<17; l++) {
        strip.setPixelColor(l, strip.Color(0,127,0));
        strip.show();
      }
      for(int c=0; c<=15000; c++) {
        digitalWrite(dirPin,  LOW);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(50);
        digitalWrite(stepPin, LOW);
      }
      delay(3000);
      state = 0;
  }
  if(state == 3)  {
    for(int l=0; l<17; l++) {
        strip.setPixelColor(l, strip.Color(127,0,0));
        strip.show();
      }
        
      for(int c=0; c<=15000; c++) {
        digitalWrite(dirPin,  HIGH);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(50);
        digitalWrite(stepPin, LOW);
       }
       delay(3000);
       state = 0; 
  }
  


} // END LOOP

void red_up() {
  state=0;
    for(int l=0; l<=7; l++) {
        strip.setPixelColor(l, strip.Color(0,127,0));
        strip.show();
    }
    for(int l=8; l<=17; l++) {
        strip.setPixelColor(l, strip.Color(127,0,0));
        strip.show();
    }
    
    for(int i=0; i<500; i++)  {
    digitalWrite(dirPin,HIGH);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(DELAY_UP);
    digitalWrite(stepPin, LOW);
    }
    
     if(digitalRead(limit_red) == 0)  {
      delay(DEBOUSE);
        state=2;
      }
}

void green_up() {
  state=0;
  for(int l=0; l<=7; l++) {
        strip.setPixelColor(l, strip.Color(0,127,0));
        strip.show();
    }
    for(int l=8; l<=17; l++) {
        strip.setPixelColor(l, strip.Color(127,0,0));
        strip.show();
    }
    
    for(int i=0; i<500; i++)  {
    digitalWrite(dirPin,LOW);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(DELAY_UP);
    digitalWrite(stepPin, LOW);
    }

    if(digitalRead(limit_green) == 0)  {
      delay(DEBOUSE);
        state=3;
      }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
