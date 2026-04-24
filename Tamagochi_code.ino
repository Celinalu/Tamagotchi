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
  //read button input
  unsigned long lastButtonPress = 0;

void checkButtons() {
  if (millis() - lastButtonPress < 200) return;  // debounce: ignore presses within 200ms

  if (digitalRead(BTN_LEFT) == LOW) {
    currentScreen = SCREEN_FEED;
    tone(BUZZER_PIN, 1000, 50);
    lastButtonPress = millis();
  }
  else if (digitalRead(BTN_MIDDLE) == LOW) {
    currentScreen = SCREEN_PLAY;
    tone(BUZZER_PIN, 1200, 50);
    lastButtonPress = millis();
  }
  else if (digitalRead(BTN_RIGHT) == LOW) {
    currentScreen = SCREEN_SLEEP;
    tone(BUZZER_PIN, 800, 50);
    lastButtonPress = millis();
  }
  
  //Screen logic 
  void handleScreenLogic() {
  switch(currentScreen) {

    case SCREEN_FEED:
      pet.hunger += 10;
      if (pet.hunger > 100) pet.hunger = 100;
      currentScreen = SCREEN_MAIN;
      break;

    case SCREEN_PLAY:
      pet.happiness += 10;
      pet.energy -= 5;
      if (pet.happiness > 100) pet.happiness = 100;
      if (pet.energy < 0) pet.energy = 0;
      currentScreen = SCREEN_MAIN;
      break;

    case SCREEN_SLEEP:
      pet.energy += 15;
      if (pet.energy > 100) pet.energy = 100;
      currentScreen = SCREEN_MAIN;
      break;

    case SCREEN_MAIN:
      break;  // do nothing, just display stats
  }
  //pet display faces
  // Example: Happy face (all stats above 50)
  const unsigned char PROGMEM petHappy[] = {
  0b00000000, 0b00000000,
  0b00000011, 0b11000000,
  0b00000100, 0b00100000,
  0b00001000, 0b00010000,
  0b00010010, 0b01001000,
  0b00010000, 0b00001000,
  0b00010111, 0b11101000,
  0b00010011, 0b11001000,
  0b00010001, 0b10001000,
  0b00010000, 0b00001000,
  0b00001000, 0b00001000,
  0b00000100, 0b00010000,
  0b00001111, 0b11100000,
  0b00011101, 0b10000000,
  0b00000011, 0b10000000,
  0b00000000, 0b00000000
};
// Example: Sad face (any stat below 30)
const unsigned char PROGMEM petSad[] = {
  0b00000000, 0b00000000,
  0b00000011, 0b11000000,
  0b00000100, 0b00100000,
  0b00001000, 0b00010000,
  0b00010010, 0b01001000,
  0b00010000, 0b00001000,
  0b00010001, 0b10001000,
  0b00010011, 0b11001000,
  0b00010111, 0b11101000,
  0b00010000, 0b00001000,
  0b00001000, 0b00001000,
  0b00000100, 0b00010000,
  0b00001111, 0b11100000,
  0b00011101, 0b10000000,
  0b00000011, 0b10000000,
  0b00000000, 0b00000000
};
// Example: Neutral face (everything else)
const unsigned char PROGMEM petNeutral[] = {
  0b00000000, 0b00000000,
  0b00000011, 0b11000000,
  0b00000100, 0b00100000,
  0b00001000, 0b00010000,
  0b00010010, 0b01001000,
  0b00010000, 0b00001000,
  0b00010011, 0b11001000,
  0b00010111, 0b11101000,
  0b00010001, 0b10001000,
  0b00010000, 0b00001000,
  0b00001000, 0b00001000,
  0b00000100, 0b00010000,
  0b00001111, 0b11100000,
  0b00011101, 0b10000000,
  0b00000011, 0b10000000,
  0b00000000, 0b00000000
};
// Example: Sleeping face (closed eyes)
const unsigned char PROGMEM petSleep[] = {
  0b00000000, 0b00000000,
  0b00000011, 0b11000000,
  0b00000100, 0b00100000,
  0b00001000, 0b00010000,
  0b00011110, 0b01111000,
  0b00010100, 0b00101000,
  0b00010011, 0b11001000,
  0b00010111, 0b11101000,
  0b00010001, 0b10001000,
  0b00010000, 0b00001000,
  0b00001000, 0b00001000,
  0b00000100, 0b00010000,
  0b00001111, 0b11100000,
  0b00011101, 0b10000000,
  0b00000011, 0b10000000,
  0b00000000, 0b00000000
};

}
void render() {
  display.clearDisplay();

  // Choose the right sprite based on pet stats
  const unsigned char* sprite;
  if (pet.hunger < 30 || pet.happiness < 30 || pet.energy < 30) {
    sprite = petSad;
  } else if (pet.hunger > 50 && pet.happiness > 50 && pet.energy > 50) {
    sprite = petHappy;
  } else {
    sprite = petNeutral;
  }

  // Draw the pet sprite (centered horizontally, near the top)
  display.drawBitmap(56, 2, sprite, 16, 16, SSD1306_WHITE);

  // Draw stat bars below the pet
  display.setTextSize(1);

  display.setCursor(0, 24);
  display.print("HUN ");
  drawBar(24, 24, pet.hunger);

  display.setCursor(0, 34);
  display.print("HAP ");
  drawBar(24, 34, pet.happiness);

  display.setCursor(0, 44);
  display.print("ENG ");
  drawBar(24, 44, pet.energy);

  // Button labels at the bottom
  display.setCursor(0, 56);
  display.println("[Feed] [Play] [Sleep]");

  display.display();
}

// Draws a stat bar: empty rectangle with a filled portion based on value (0 to 100)
void drawBar(int x, int y, int value) {
  int barWidth = 100;
  int barHeight = 6;
  int fillWidth = map(value, 0, 100, 0, barWidth);

  display.drawRect(x, y, barWidth, barHeight, SSD1306_WHITE);       // outline
  display.fillRect(x, y, fillWidth, barHeight, SSD1306_WHITE);      // filled portion
}
}

void loop() {
 checkButtons();       // 1. Read input
  updatePet();          // 2. Update state over time
  handleScreenLogic();  // 3. Process actions
  render();             // 4. Display results
  delay(100);           // 5. Short pause

}
