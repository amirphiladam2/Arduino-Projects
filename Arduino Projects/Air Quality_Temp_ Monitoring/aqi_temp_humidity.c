
#include<Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>  

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI SDA
#define OLED_CLK SCL
#define OLED_DC 8
#define OLED_RESET 3
#define OLED_CS 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define sensor A0 
#define DHTPIN 2  // Rename from DHT11PIN to DHTPIN to match library conventions
#define DHTTYPE DHT11  // Define the type of DHT sensor you're using

DHT dht(DHTPIN, DHTTYPE);  // Create an instance of the DHT sensor

int gasLevel  = 0;
String quality = "";

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setFont();
  display.setCursor(0, 43);
  display.println("Temp  :");
  display.setCursor(80, 43);
  display.println(t);
  display.setCursor(114, 43);
  display.println("C");
  display.setCursor(0,  56);
  display.println("RH    :");
  display.setCursor(80, 56);
  display.println(h);
  display.setCursor(114, 56);
  display.println("%");
}

void air_sensor()
{
  gasLevel = analogRead(sensor);

  if(gasLevel < 60) {
    quality = "  GOOD!";
  }
  else if (gasLevel > 60 && gasLevel < 90) { 
    quality =  "  Poor!";
  }
  else if (gasLevel > 101 && gasLevel < 150) {
    quality = "Very bad!";
  }
  else if (gasLevel > 300 && gasLevel < 500) {
    quality = "Toxic!";
  }
  else {
    quality = " Toxic";   
  }
  
  display.setTextColor(WHITE);
  display.setTextSize(1);  
  display.setCursor(1,5);
  display.setFont();
  display.println("Air Quality:");
  display.setTextSize(1);
  display.setCursor(5,23);
  display.println(gasLevel);
  
  display.setCursor(20,23);
  display.println(quality);  
}

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  dht.begin();  // Initialize the DHT sensor
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  display.setTextSize(2);
  display.setCursor(50, 0);
  display.println("Air");
  display.setTextSize(1);
  display.setCursor(23, 20);
  display.println("Quality monitor");
  display.display();
  delay(1200);
  display.clearDisplay();
  
  display.setTextSize(1.5);
  display.setCursor(20, 20);
  display.println("BY Circuit");
  display.setCursor(20, 40);
  display.println("Digest");
  display.display();
  delay(1000);
  display.clearDisplay();    
}

void loop() {
  display.clearDisplay();
  air_sensor();
  sendSensor();
  display.display();  
}
