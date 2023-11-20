#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 10
#define LED_COUNT 3


// LED configuration
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GBR + NEO_KHZ800);
uint32_t backlightColor = strip.Color(0, 15, 0);
uint32_t onColor = strip.Color(0, 255, 0);

// Button configuration
int buttonPins[] = {2, 3, 4};
int buttonStates[] = {1, 1, 1};

void setup() {
  // Make rx/tx leds inaccessible for libraries
  pinMode(LED_BUILTIN_TX, INPUT);
  pinMode(LED_BUILTIN_RX, INPUT);

  // Set everything up
  strip.begin();
  strip.setBrightness(255);
  for(int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    strip.setPixelColor(i, backlightColor);
  }
  strip.show();
  Keyboard.begin();
}

void loop() {
  // Check all buttons
  for(int i = 0; i < 3; i++) {
    int state = digitalRead(buttonPins[i]);
    if(state != buttonStates[i]) {
      if(state) {
        // Button released
        strip.setPixelColor(2 - i, backlightColor);
        strip.show();
        if(i == 0) {
          keyOneAction();
        } else if(i == 1) {
          keyTwoAction();
        } else if(i == 2) {
          keyThreeAction();
        }
      } else {
        // Button pressed
        strip.setPixelColor(2 - i, onColor);
        strip.show();
      }
      buttonStates[i] = state;
    }
  }

  // Delay before checking again
  delay(10);
}

void keyOneAction() {
  // Action for left key
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  delay(10);
  Keyboard.releaseAll();
  delay(200);
  Keyboard.println("cmd");
}

void keyTwoAction() {
  // Action for middle key
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('c');
  delay(10);
  Keyboard.releaseAll();
}

void keyThreeAction() {
  // Action for right key
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('v');
  delay(10);
  Keyboard.releaseAll();
}
