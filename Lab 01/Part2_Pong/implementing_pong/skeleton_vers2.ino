#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Defining screen
//##############################################################
// FILL IN SCREEN VARIABLES FROM CONNECT_TO_SCREEN TUTORIAL



// Button pins
const int BTN_P1 = 4;
const int BTN_P2 = 3;

int p1Dir = 0;
int p2Dir = 0;
// Ball starting velocity
int ballVX = -1;
int ballVY = 1;

// State tracking
bool lastBtnP1 = HIGH;
bool lastBtnP2 = HIGH;

int pressCountP1 = 0;
int pressCountP2 = 0;

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
  // - Configure screen 
  // - Configure Button 2 

  // Declare our buttons
  pinMode(BTN_P1, INPUT_PULLUP);

  startTime = millis();
}


void loop() {
  // Button polls
  bool btnP1 = digitalRead(BTN_P1);
  bool btnP2 = digitalRead(BTN_P2);

  // Initial Phase
  // Game Loop 
  if (state == PLAYING) {
    if (lastBtnP1 == HIGH && btnP1 == LOW) { // Button presses to toggle paddle direction
      //FILL IN 
    }
    if (lastBtnP2 == HIGH && btnP2 == LOW) {
      // FILL IN
    }

    // Paddle movement update
    P1_Y += p1Dir;
    P2_Y += p2Dir;

    //##############################################################
    // FILL IN PADDLE CONSTRAINTS FROM INSTRUCTIONS



    // Ball movement
    // This is acheived by adding the X and Y velocity to the respective X and Y positions.
    // if ball collides with top or bottom screen, what happens?
    //##############################################################
    // FILL IN BALL MOVEMENTS FROM INSTRUCTIONS



    //##############################################################
    //CHALLENGE 1 - BALL CONSTRAINTS
    if (ballY <= 0 || ballY >= SCREEN_HEIGHT - 2) {
      // This is the bounds of top and bottom the screen. What happens when the ball hits the bounds?
    }

    //##############################################################
    //CHALLENGE 2 - SCORING
    if (ballX < 0) {
      // FILL IN
    }
    if (ballX > SCREEN_WIDTH) {
      // FILL IN
    }

    //##############################################################
    // FILL IN FROM PREVIOUS TUTORIALS
    // - Update screen graphics using connect_to_screen 
    // - Display timer 
    // - Update the states of lastBtnP1 and lastBtnP2 from button_polling

  }

  // Game Over
  else if (state == GAME_OVER) {
    display.clearDisplay();
    display.setCursor(25, 20);
    display.setTextSize(1);
    if (scoreP1 == 3) {
      display.println("Player 1 Wins!");
    } else {
      display.println("Player 2 Wins!");
    }

    display.setCursor(10, 40);
    display.println("Press any button...");
    display.display();

    // Wait for any button press to restart
    if ((lastBtnP1 == HIGH && btnP1 == LOW) || (lastBtnP2 == HIGH && btnP2 == LOW)) {
      state = PLAYING;
      resetGame();
    }
  }

  // Store button state for edge detection
  lastBtnP1 = btnP1;
  lastBtnP2 = btnP2;
}

// Resets the round after a point is scored
void resetRound() {
  //##################################################################
  // CHALLENGE 3 
  // - Set the starting positions and directions of the ball and paddles
  // - Update screen 

  ballVX *= -1;
  // Picks a random direction
  ballVY = (random(0, 2) == 0) ? -1 : 1;
}


// resets the game after game over
void resetGame() {
  resetRound();
  pressCountP1 = 0;
  pressCountP2 = 0;
  scoreP1 = 0;
  scoreP2 = 0;

  startTime = millis();
  gameTime = 0;
}