#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

const int SW = 2; // SW
const int X = 0;  // VRx
const int Y = 1;  // VRy

#define TFT_CS   10
#define TFT_RST  9
#define TFT_DC   8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

const int playerWidth = 10;
const int playerHeight = 10;
const int obstacleWidth = 10;
const int obstacleHeight = 20;
const int obstacleSpeed = 2;

int playerX, playerY;        // Player position
int obstacleX, obstacleY;    // Obstacle position
int score;

void setup() {
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);

  playerX = tft.width() / 2 - playerWidth / 2; // Initial player position at the center of the screen
  playerY = tft.height() - playerHeight - 5;

  obstacleX = random(tft.width() - obstacleWidth); // Initial obstacle position
  obstacleY = -obstacleHeight;

  score = 0;

  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
}

void loop() {
  // Clear the screen
  tft.fillScreen(ST7735_BLACK);

  // Move the obstacle downwards
  obstacleY += obstacleSpeed;

  // Check if the player collided with the obstacle
  if (checkCollision()) {
    gameOver();
    return;
  }

  // Check if the obstacle passed the player
  if (obstacleY > playerY + playerHeight) {
    score++;
    resetObstacle();
  }

  // Draw the player character
  tft.fillRect(playerX, playerY, playerWidth, playerHeight, ST7735_WHITE);

  // Draw the obstacle
  tft.fillRect(obstacleX, obstacleY, obstacleWidth, obstacleHeight, ST7735_RED);

  // Display the score
  tft.setCursor(0, 0);
  tft.print("Score: ");
  tft.print(score);

  // Read the joystick values
  int joyX = analogRead(X);
  int joyY = analogRead(Y);
  int buttonState = digitalRead(SW);

  // Move the player based on joystick input
  movePlayer(joyX, joyY);

  delay(10);
}

bool checkCollision() {
  // Check if the player and obstacle rectangles overlap
  return playerX < obstacleX + obstacleWidth &&
         playerX + playerWidth > obstacleX &&
         playerY < obstacleY + obstacleHeight &&
         playerY + playerHeight > obstacleY;
}

void resetObstacle() {
  obstacleX = random(tft.width() - obstacleWidth);
  obstacleY = -obstacleHeight;
}

void gameOver() {
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);

  // Calculate the center position for the text
  int centerX = (tft.width() - 9 * 6) / 2; // 9 characters, assuming 6 pixels width for each character

  // Print "Game Over" text
  tft.setCursor(centerX, tft.height() / 2 - 10);
  tft.print("Game Over");

  // Print the score
  tft.setCursor(centerX, tft.height() / 2 + 10);
  tft.print("Score: ");
  tft.print(score);

  // Print instructions
  tft.setCursor(centerX - 6, tft.height() / 2 + 30);
  tft.print("Move left to play again");

  bool playAgain = false;

  while (true) {
    int joystickX = analogRead(X);

    if (joystickX < 100) {
      playAgain = true;
      break;
    }
  }

  if (playAgain) {
    // Reset game and play again
    loop();
  } else {
    while (true) {} // Wait indefinitely
  }
}


void movePlayer(int joyX, int joyY) {
  // Adjust player position based on joystick input
  playerX += map(joyX, 0, 1023, -2, 2);
  playerY += map(joyY, 0, 1023, -2, 2);

  // Ensure the player stays within the screen bounds
  if (playerX < 0) {
    playerX = 0;
  }
  if (playerX + playerWidth > tft.width()) {
    playerX = tft.width() - playerWidth;
  }
  if (playerY < 0) {
    playerY = 0;
  }
  if (playerY + playerHeight > tft.height()) {
    playerY = tft.height() - playerHeight;
  }
}

void enableAutomaticPlayers() {
  // Define positions and velocities for automatic players
  int automaticPlayer1X = 10;
  int automaticPlayer1Y = 20;
  int automaticPlayer1Velocity = 2;

  int automaticPlayer2X = 50;
  int automaticPlayer2Y = 40;
  int automaticPlayer2Velocity = 3;

  int automaticPlayer3X = 80;
  int automaticPlayer3Y = 10;
  int automaticPlayer3Velocity = 1;

  while (true) {
    // Clear the screen
    tft.fillScreen(ST7735_BLACK);

    // Move and draw automatic player 1
    automaticPlayer1X += automaticPlayer1Velocity;
    if (automaticPlayer1X < 0 || automaticPlayer1X + playerWidth > tft.width()) {
      automaticPlayer1Velocity *= -1;
    }
    tft.fillRect(automaticPlayer1X, automaticPlayer1Y, playerWidth, playerHeight, ST7735_GREEN);

    // Move and draw automatic player 2
    automaticPlayer2X += automaticPlayer2Velocity;
    if (automaticPlayer2X < 0 || automaticPlayer2X + playerWidth > tft.width()) {
      automaticPlayer2Velocity *= -1;
    }
    tft.fillRect(automaticPlayer2X, automaticPlayer2Y, playerWidth, playerHeight, ST7735_GREEN);

    // Move and draw automatic player 3
    automaticPlayer3Y += automaticPlayer3Velocity;
    if (automaticPlayer3Y < 0 || automaticPlayer3Y + playerHeight > tft.height()) {
      automaticPlayer3Velocity *= -1;
    }
    tft.fillRect(automaticPlayer3X, automaticPlayer3Y, playerWidth, playerHeight, ST7735_GREEN);

    // Draw the player character
    tft.fillRect(playerX, playerY, playerWidth, playerHeight, ST7735_WHITE);

    // Check if the player collided with any automatic player
    if (checkCollisionWithAutomaticPlayer(automaticPlayer1X, automaticPlayer1Y) ||
        checkCollisionWithAutomaticPlayer(automaticPlayer2X, automaticPlayer2Y) ||
        checkCollisionWithAutomaticPlayer(automaticPlayer3X, automaticPlayer3Y)) {
      gameOver();
      return;
    }

    delay(10);
  }
}

bool checkCollisionWithAutomaticPlayer(int automaticPlayerX, int automaticPlayerY) {
  // Check if the player and automatic player rectangles overlap
  return playerX < automaticPlayerX + playerWidth &&
         playerX + playerWidth > automaticPlayerX &&
         playerY < automaticPlayerY + playerHeight &&
         playerY + playerHeight > automaticPlayerY;
}
