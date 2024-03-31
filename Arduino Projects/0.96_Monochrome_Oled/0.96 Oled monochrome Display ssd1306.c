/CODE BY AMIR PHILIP ADAM
/THIS CODE IS FOR 0.96 MONOCHROME DISPLAY SSD1306

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64   // OLED display height, in pixels

// Map your pins to the library's pin definitions:
#define OLED_MOSI SDA        //  used for I2C (some boards A4)
#define OLED_CLK SCL         //  used for I2C (some boards A5)
#define OLED_DC 8           // Data/Command pin (mapped to D8 based on your original information)
#define OLED_RESET 3       // Reset pin (mapped to D3 based on your original information)
#define OLED_CS 9          // Chip select pin (unused)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  // Uncomment if you want to use serial communication for debugging
  // Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V or 5V (depending on board)
  // You can also use a separate battery or external voltage supply
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1); // Halt execution if initialization fails
  }

  display.clearDisplay();  // Clear the display buffer
}

void loop() {
  display.setTextSize(2);      // Set the text size (1 = normal, 2 = double size)
  display.setTextColor(WHITE); // Set the text color to white (other options: BLACK)
  display.setCursor(0, 10);    // Set the cursor position (x, y)

  // Example: Displaying text
  display.println("Bravo\nAmir!");
  display.print("Finally\nWorked");
  display.println("Proud Moment.");

  display.display();  // Send the updated display buffer to the OLED
  delay(2000);        // Delay for 2 seconds between updates
}
