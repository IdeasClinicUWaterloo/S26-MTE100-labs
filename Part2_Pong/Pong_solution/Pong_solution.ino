#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Defining screen
//##############################################################
// fill in screen variables using connect_to_screen_module 

// Screen Variables
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Score tracking
int scoreP1 = 0;
int scoreP2 = 0;

const int PADDLE_WIDTH = 2;
const int PADDLE_HEIGHT = 12;

// Position tracking for player 1 paddle
int P1_X = 0;
int P1_Y = 32;
// Position tracking for player 2 paddle
int P2_X = 128-PADDLE_WIDTH;
int P2_Y = 32;
// Position tracking for ball
int ballX = 64;
int ballY = 32;

// Button pins - keep out 
const int BTN_P1 = 4;
const int BTN_P2 = 3;
const int BTN_RES = 2;

bool lastBtnP1 = HIGH;
bool lastBtnP2 = HIGH;
bool lastBtnRES= HIGH;

int p1Dir = 0;
int p2Dir = 0;

unsigned long  gameTime = 0;
unsigned long  startTime = 0;

enum GameState {
  // These are the different game states. In your code, think about what should happen in each state and when to switch between states
  PLAYING,
  GAME_OVER
};

// Starting state
GameState state = PLAYING;

void setup() {
  //############################################################## 
  // - Configure screen using connect_to_screen module
  // - Init Button 1 and 2 as I/O using pinMode();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  pinMode(BTN_P1, INPUT_PULLUP);
  pinMode(BTN_P2, INPUT_PULLUP);
  pinMode(BTN_RES, INPUT_PULLUP);

  startTime = millis();
}


void loop() {
  // Button polls
  bool btnP1 = digitalRead(BTN_P1);
  bool btnP2 = digitalRead(BTN_P2);
  bool btnRES = digitalRead(BTN_RES);

  if (lastBtnP1 == HIGH && btnP1 == LOW){
    if (p1Dir == 0) {
      p1Dir = (P1_Y <= 0) ? 2 : -1;

    } else { // If direction is not 0, flip p1Dir
      p1Dir *= -1;
    }
  }

  if (lastBtnP2 == HIGH && btnP2 == LOW){
    if (p2Dir == 0) {
      p2Dir = (P2_Y <= 0) ? 2 : -1;

    } else { // If direction is not 0, flip p1Dir
      p2Dir *= -1;
    }
  }

  P1_Y += p1Dir;
  P2_Y += p2Dir;

  if (P1_Y <= 0 || P1_Y >= SCREEN_HEIGHT - PADDLE_HEIGHT) {
    // constrain prevents the paddle from extending beond the screen

    // P1_Y = constrain(P1_Y, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
    // p1Dir = 0;

    if (P1_Y <= 0) P1_Y = 0; 
    else P1_Y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    p1Dir = 0;
  }
  if (P2_Y <= 0 || P2_Y >= SCREEN_HEIGHT - PADDLE_HEIGHT) {
    // constrain prevents the paddle from extending beond the screen

    P2_Y = constrain(P2_Y, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
    p2Dir = 0;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(50, 55);

  //timer challenge
  gameTime = millis() - startTime;
  int min = gameTime/60000;
  int sec = (gameTime/1000)%60;

  if (lastBtnRES == HIGH && btnRES == LOW){
    resetGame();
  }
  
  if (min<10) display.print("0");
  display.print(min);
  display.print(":");
  if(sec<10) display.print("0");
  display.print(sec);

  // Sets up text for the player scores
  display.setCursor(40, 0);
  display.print("P1:");
  display.print(scoreP1);
  display.print("  P2:");
  display.print(scoreP2);
  display.setCursor(40,10);

  // Set up paddles
  display.fillRect(P1_X, P1_Y, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_WHITE);
  display.fillRect(P2_X, P2_Y, PADDLE_WIDTH, PADDLE_HEIGHT, SSD1306_WHITE);
  // Set up ball
  display.fillRect(ballX, ballY, 2, 2, SSD1306_WHITE);
  display.display();
  // Displays everything
  delay(15);

  // Store button state for edge detection
  lastBtnP1 = btnP1;
  lastBtnP2 = btnP2;
  lastBtnRES = btnRES;
}

void resetGame(){
  ballX = 64;
  ballY = 32;

  P1_Y = 32;
  P2_Y = 32;
  
  p1Dir = 0;
  p2Dir = 0;

  // Sets up text for the player scores
  display.setTextSize(1);
  scoreP1 = 0;
  scoreP2 = 0;

  startTime = millis();
  gameTime = 0;
}

