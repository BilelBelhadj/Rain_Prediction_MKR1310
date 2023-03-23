#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define PIN_LED 6     // Control signal, connect to DI of the LED
#define NUM_LED 1     // Number of LEDs in a strip


Adafruit_NeoPixel RGB_Strip = Adafruit_NeoPixel(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int hum = 0, temp = 0, sun = 0, RedLight = 0, GreenLight = 0, BlueLight = 0;
double ProbablityRain = 0;

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint16_t wait) {
  for (uint16_t i = 0; i < RGB_Strip.numPixels(); i++) {
    RGB_Strip.setPixelColor(i, c);
    RGB_Strip.show();
    delay(wait);
  }
}



void setup() {
  Serial.begin(9600);

  RGB_Strip.begin();
  RGB_Strip.show();
  RGB_Strip.setBrightness(200);    // Set brightness, 0-255 (darkest - brightest)

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
    }
  
    display.clearDisplay();
    display.setTextColor(WHITE);
}

void loop() {
  //gerer les valeur aleatoirement
  hum  = rand() % 20 + 65;
  temp = rand() % 5 + 23;
  sun  = rand() % 401 + 800;
 
  //Formule trouvée par modélisation
  ProbablityRain= 0.03743225*hum - 2.21389335*temp - 0.09773871*sun + 198.85713381876218;

  if(ProbablityRain < 40){
    colorWipe(RGB_Strip.Color(0,255,0), 1000);
  }else if(ProbablityRain < 75){
    colorWipe(RGB_Strip.Color(255,165,0), 1000);
  }else{
    colorWipe(RGB_Strip.Color(255,0,0), 1000);
  }
   
  for (int i = 0; i < 120; i++) {
    display.clearDisplay();
    //display temperature
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Temp:");
    display.setTextSize(2);
    display.setCursor(0,10);
    display.print(String(temp));
    
    //display humidity
    display.setTextSize(1);
    display.setCursor(40, 0);
    display.print("Hum: ");
    display.setTextSize(2);
    display.setCursor(40, 10);
    display.print(String(hum));

    //display SUN
    display.setTextSize(1);
    display.setCursor(80, 0);
    display.print("SUN: ");
    display.setTextSize(2);
    display.setCursor(80, 10);
    display.print(String(sun));

    //display Rain probability
    display.setTextSize(1);
    display.setCursor(0, 40);
    display.print("PROB RAIN: ");
    display.setTextSize(2);
    display.setCursor(i, 50);
    display.print(String(ProbablityRain));
    display.display(); 
    delay(30);
    }
}