#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <DFRobot_SGP40.h>

#define PIN 2
#define NUMPIXELS 3
#define BRIGHTNESS 255

#define FANPIN 6

/*
#define FANHIGH 200
#define FANMID 150
#define FANLOW 100
*/

#define FANHIGH 250
#define FANMID 200
#define FANLOW 150

#define SENSORHIGH  250
#define SENSORMID 150 
#define SENSORLOW 100


int speed = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

DFRobot_SGP40 mySgp40;

void setup() {
  pinMode(FANPIN, OUTPUT);
  analogWrite(FANPIN, FANLOW);
  Serial.begin(115200);
  Serial.println("sgp40 is starting, the reading can be taken after 10 seconds...");
  /*
   * 传感器预热时间为10s。
   * duration:初始化等待时间。单位：毫秒。建议duration>=10000ms
   */
  strip.begin();
  strip.show();
  //colorWipe(strip.Color(0, 255, 0), 10);

  //colorWipe(strip.Color(0, 255, 0), 10);

  for(int i=0;i<4;i++){
    colorWipe(strip.Color(0, 255, 255), 10);
    delay(1000);
    colorWipe(strip.Color(255, 255, 0), 10);
    delay(1000);
    colorWipe(strip.Color(255, 0, 0), 10);
    delay(1000);
  }
    colorWipe(strip.Color(0, 255, 255), 10);
  

  while (mySgp40.begin(/*duration = */ 10000) != true) {
    Serial.println("failed to init chip, please check if the chip connection is fine");
    delay(10000);
  }
  //colorWipe(strip.Color(255, 255, 255), 10);
  Serial.println("----------------------------------------------");
  Serial.println("sgp40 initialized successfully!");
  Serial.println("----------------------------------------------");
}

void loop() {
  //strip.begin();
  /*
  strip.setPixelColor(0, 255, 0, 0);
  strip.setPixelColor(1, 255, 100, 0);
  strip.setPixelColor(2, 255, 200, 0);
  //strip.setPixelColor(3+  , 255, 255, 255);
  */
  //strip.show();
  /*
  colorWipe(strip.Color(255,255,0),10);
  delay(5000);
  colorWipe(strip.Color(0,255,0),10);
  delay(5000);
  colorWipe(strip.Color(0,0,255),10);
  delay(5000);
  */

  uint16_t index = mySgp40.getVoclndex();
  if (index >= SENSORHIGH) {
    colorWipe(strip.Color(255, 0, 0), 10);
      analogWrite(FANPIN, FANHIGH);
  } else if (index >= SENSORMID && index < SENSORHIGH) {
    colorWipe(strip.Color(255, 255, 0), 10);
    analogWrite(FANPIN, FANMID);
  } else {
    colorWipe(strip.Color(0, 255, 255), 10);
    analogWrite(FANPIN, FANLOW);
  }
  Serial.print("vocIndex = ");
  Serial.println(index);
  delay(1000);
  /*
  colorWipe(strip.Color(255,255,255),10);
  delay(2000);
  */
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
