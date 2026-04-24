void setup() {
  // Buttons (traced from schematic)
#define BTN1 0 // SW 1 MCU pin 1 GPIO0
#define BTH2 1 // SW2 MCU Pin 2 GPIO1
#define BTN3 2 // SW3 → MCU Pin 3 → GPIO2

// I2C OLED (traced from schematic)
#define SDA_PIN 22  // OLED SDA → MCU Pin 5 → GPIO22
#define SCL_PIN 23  // OLED SCL → MCU Pin 6 → GPIO23

//LED lights (traced from schematic)
#define LED1 //led 1 GPIO21
#define LED2 //led 2 GPIO16
#define LED3 //led 3 GPIO17

//display and pin constants
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BTN_LEFT   D0
#define BTN_MIDDLE D1
#define BTN_RIGHT  D2

//coding the pet
struct Pet{
  int hunger;       // 0 to 100 (0 = starving, 100 = full)
  int happiness;    // 0 to 100 (0 = miserable, 100 = ecstatic)
  int energy;       // 0 to 100 (0 = exhausted, 100 = fully rested)
  unsigned long age; // total seconds the pet has been alive
};

// pet global 
Pet pet;

//state machine
enum Screen {
  SCREEN_MAIN,
  SCREEN_FEED,
  SCREEN_PLAY,
  SCREEN_SLEEP
};

Screen currentScreen = SCREEN_MAIN;

//setup for when board powers or resets
void setup() {
   pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_MIDDLE, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Tamagotchi Init...");
  display.display();
  delay(1000);

  pet.hunger = 80;
  pet.happiness = 80;
  pet.energy = 80;
  pet.age = 0;

  //game update logic
  unsigned long lastUpdate = 0;

void updatePet() {
  if (millis() - lastUpdate > 5000) {  // every 5 seconds
    pet.hunger--;
    pet.happiness--;
    pet.energy--;

    if (pet.hunger < 0) pet.hunger = 0;
    if (pet.happiness < 0) pet.happiness = 0;
    if (pet.energy < 0) pet.energy = 0;

    pet.age += 5;
    lastUpdate = millis();
  }
  
}

}

void loop() {
  // put your main code here, to run repeatedly:

}
