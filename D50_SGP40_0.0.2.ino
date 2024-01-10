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

/*
~65
65~220
220~660
660~2200
2200~


colorWipe(strip.Color(255, 0, 0), 10);  //빨강
colorWipe(strip.Color(255, 255, 0), 10);//노랑
colorWipe(strip.Color(0, 255, 0), 10);//초록
colorWipe(strip.Color(0, 255, 255), 10);//아쿠아
colorWipe(strip.Color(0, 0, 255), 10);//파랑

*/

#define FANSPEED4 250
#define FANSPEED3 200
#define FANSPEED2 150
#define FANSPEED1 150

#define SENSORRANGE4 2200
#define SENSORRANGE3 660
#define SENSORRANGE2 220
#define SENSORRANGE1 65

int speed = 0;
int cnt = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

DFRobot_SGP40 mySgp40;

void setup() {
  pinMode(FANPIN, OUTPUT);
  analogWrite(FANPIN, FANSPEED1);
  Serial.begin(115200);
  Serial.println("sgp40 is starting, the reading can be taken after 10 seconds...");
  strip.begin();
  strip.show();

  for (int i = 0; i < 4; i++) {
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
  uint16_t index = mySgp40.getVoclndex();
  uint16_t index2 = mySgp40.readRawData();
  int status=0;
  if (index >= SENSORRANGE4) {
    colorWipe(strip.Color(255, 0, 0), 10);
    analogWrite(FANPIN, FANSPEED4);
  } else if (index >= SENSORRANGE3 && index < SENSORRANGE4) {
    colorWipe(strip.Color(255, 0, 0), 10);
    analogWrite(FANPIN, FANSPEED4);
  } else if (index >= SENSORRANGE2 && index < SENSORRANGE3) {
    analogWrite(FANPIN, FANSPEED2);
    colorWipe(strip.Color(255, 255, 0), 10);
  } else if (index >= SENSORRANGE1 && index < SENSORRANGE2) {
    colorWipe(strip.Color(0, 255, 255), 10);
    analogWrite(FANPIN, FANSPEED1);
  } else {
    colorWipe(strip.Color(0, 255, 255), 10);
    analogWrite(FANPIN, FANSPEED1);
  }
  Serial.print("vocIndex = ");
  Serial.print(index);
  Serial.print("  ");
  Serial.print(index2);
  delay(1000);
  
  cnt++;
  Serial.print("        ");
  Serial.println(cnt);
  /*
  if (cnt >= 60) {
    Serial.println("VocReset");
    mySgp40.softReset(); // 센서 리셋
    cnt = 0;
  }
  */
  if (cnt >= 60) {
    Serial.println("MeaseureTest");
    mySgp40.sgp40MeasureTest();
    cnt = 0;
  }
  Serial.println(mySgp40.sgp40MeasureTest());

  
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
