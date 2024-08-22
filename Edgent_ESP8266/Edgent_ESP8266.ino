/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME "NodeMCU"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG
#define APP_DEBUG

//define the variable 
int soilMoist; //for soil moisture
float Temperature; //for temperature sensor
float Humidity; //for humidity sensor
// int waterPump = 0; //for water pump


//define input port 
#define WATER_PUMP 3 //water pump
#define SENSOR_SOIL 4 //soil sensor pin
#define TEMPERATURE_SENSOR 5 //temperature sensor
#define HUMIDITY_SENSOR //Humidity sensor
 
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"

//pin v0 for water pump
BLYNK_WRITE(V0) {
    if( param.asINT() == 1 ) {
      digitalWrite(WATER_PUMP, HIGH);
    }
    else {
      digitalWrite(WATER_PUMP, LOW);
    }
}

BLYNK_CONNECTED() {
    Blynk.syncVirtual(V0); 
}

//function send soil moisture data to blynk
void sendSoilMoisture() {
  soilMoist = analogRead(SENSOR_SOIL); //reading data from sensor soil (v1)
  Blynk.virtualWrite(v1, soilMoist); //send data into blynk
}

//function send soil 
void sendTemperature() {
  Temperature = analogRead(TEMPERATURE_SENSOR);
  Blynk.virtualWrite(V2, Temperature);
}

void sendHumidity() {
  Humidity = analogRead(HUMIDITY_SENSOR);
  Blynk.virtualwrite(V4, Humidity);
}

void setup()
{
  Serial.begin(115200);
  delay(100);

  //define the tools
  pinMode(SENSOR_SOIL, INPUT); //sensor soil
  pinMode(WATER_PUMP, OUTPUT); //water pump
  pinMode(TEMPERATURE_SENSOR, INPUT); //temperature sensor
  pinmode(HUMIDITY_SENSOR, INPUT);

  //water pump is off
  digitalWrite(WATER_PUMP, LOW);

  BlynkEdgent.begin();
}

void loop() {
  BlynkEdgent.run();
}

