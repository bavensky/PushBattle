#include <Adafruit_NeoPixel.h>

#define stepPin 9
#define dirPin 8 
#define red A0
#define green A1

#define led 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, led, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(red, INPUT);
  pinMode(green, INPUT);

  strip.begin();
  strip.show();
}

void loop() {
//  Serial.print(digitalRead(red));
//  Serial.print("  ");
//  Serial.println(digitalRead(green));
//  
//  rainbow(30);  
//  strip.setPixelColor(1, strip.Color(0,150,0));
//  strip.show();
  
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
