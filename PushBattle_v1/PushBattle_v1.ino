#include <Adafruit_NeoPixel.h>

#define stepPin 9
#define dirPin 8 

#define red A1
#define green A0


#define limit_red 2
#define limit_green 3

#define led 5

int mode = 0;
int work = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, led, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  
  pinMode(red, INPUT);
  pinMode(green, INPUT);
  pinMode(limit_red, INPUT_PULLUP);
  pinMode(limit_green, INPUT_PULLUP);
    
  strip.begin();
  strip.show();


}

void loop() {
  
rainbow(5);
Serial.println(" OUT ");

if(digitalRead(red) == 0 && digitalRead(green) == 0)  {
  for(int l=0; l<20; l++) {
  strip.setPixelColor(l, strip.Color(0,0,0));
  strip.show();
  }
  mode = 1;
  work = 1;
}

if(mode==1)  {
  for(int l=0; l<10; l++) {
  strip.setPixelColor(l, strip.Color(127,0,0));
  strip.show();
  }
  for(int l=10; l<20; l++) {
  strip.setPixelColor(l, strip.Color(0,127,0));
  strip.show();
  }
  
  while(work == 1)  {
    if(digitalRead(red) == 0) {
    digitalWrite(dirPin,HIGH);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(30);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(30);
    }

  if(digitalRead(green) == 0) {
    digitalWrite(dirPin,LOW);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(30);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(30);
    }
    
   if(digitalRead(limit_red) == 0) {
      for(int l=0; l<20; l++) {
        strip.setPixelColor(l, strip.Color(0,127,0));
        strip.show();
      }
      for(int c=0; c<13700; c++) {
        digitalWrite(dirPin,  HIGH);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(50);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(50);
      }

     work = 0;
     mode = 0;
   }
   if(digitalRead(limit_green) == 0) {
      for(int l=0; l<20; l++) {
        strip.setPixelColor(l, strip.Color(127,0,0));
        strip.show();
      }
      
      for(int c=0; c<17000; c++) {
        digitalWrite(dirPin,  LOW);
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(50);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(50);
      }

      work = 0;
      mode = 0;
    }     
  }
  }
  
} // END LOOP

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
