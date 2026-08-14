#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Defining screen
//##############################################################
// fill in screen variables using connect_to_screen_module 



// Button pins - keep out 
const int BTN_P1 = 3;
const int BTN_P2 = 4;

bool lastBtnP1 = HIGH;
bool lastBtnP2 = HIGH;

int p1Dir = 0;
int p2Dir = 0;

unsigned long  gameTime = 0;
unsigned long  startTime = 0;

enum GameState {
  // Don't worry about game states for now! 
  // In your own time, how and why you would trigger a new state. Come to the ideasclinic workshop to learn!! 
  PLAYING,
  GAME_OVER
};

// Starting state
GameState state = PLAYING;

void setup() {
  //############################################################## 
  // - Configure screen using connect_to_screen module
  // - Init Button 1 and 2 as I/O using pinMode();

  startTime = millis();
}


void loop() {
  // Button polls
  bool btnP1 = digitalRead(BTN_P1);
  bool btnP2 = digitalRead(BTN_P2);

  //############################################################## 
  // - input button functionality from the instructions
  // CHALLENGE: add constraints to the paddles so they don't leave the screen


  //############################################################## 
  // - add your code from the timer module challenge


  //############################################################## 
  // - draw the paddles using code from connect_to_screen 


  // Store button state for button detection
  lastBtnP1 = btnP1;
  lastBtnP2 = btnP2;
}

void resetGame(){
  //CHALLENGE
  // - reset the game! 

}
