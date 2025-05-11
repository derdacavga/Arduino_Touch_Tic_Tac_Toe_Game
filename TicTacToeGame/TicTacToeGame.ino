#include <SPI.h>
#include <TFT_eSPI.h>
#include <FS.h>
#include "SPIFFS.h"

TFT_eSPI tft = TFT_eSPI();

#define SKETCH_CALIBRATION_FILE "/TouchCalDataFile"

#define FIXED_SCREEN_WIDTH 240
#define FIXED_SCREEN_HEIGHT 320

#define GRID_SIZE 240
#define CELL_SIZE (GRID_SIZE / 3)

#define GRID_X_OFFSET ((FIXED_SCREEN_WIDTH - GRID_SIZE) / 2)
#define GRID_Y_OFFSET 0

#define LINE_COLOR TFT_BLACK
#define BG_COLOR TFT_GREEN
#define X_COLOR TFT_RED
#define O_COLOR TFT_BLUE
#define TEXT_COLOR TFT_BLACK
#define WINNER_BG_COLOR TFT_GREEN
#define CAL_TEXT_COLOR TFT_BLACK
#define CAL_BG_COLOR TFT_GREEN

#define PLAYER_NONE 0
#define PLAYER_X 1
#define PLAYER_O 2

int board[3][3];
int currentPlayer;
bool gameOver;
int winner;

unsigned long lastTouchTime = 0;
const unsigned long touchDebounceDelay = 300;

uint16_t screenWidth, screenHeight;

void ensureTouchCalibration();
void setupGame();
void drawBoard();
void drawX(int centerX, int centerY);
void drawO(int centerX, int centerY);
void handleTouchInput();
bool checkWin();
bool checkDraw();
void displayMessage(String msg1, String msg2 = "", uint16_t bgColor = BG_COLOR);
void updateTurnMessage();

void setup() {

  tft.init();
  tft.setRotation(2);
  logo();
  delay(1000);
  screenWidth = tft.width();
  screenHeight = tft.height();

  SPIFFS.begin();
  ensureTouchCalibration();
  setupGame();
}

void ensureTouchCalibration() {

  bool calFileExists = SPIFFS.exists(SKETCH_CALIBRATION_FILE);

  if (!calFileExists) {
    tft.fillScreen(CAL_BG_COLOR);
    tft.setCursor(0, 50);
    tft.setTextSize(1);
    tft.setFreeFont(&FreeSansBold9pt7b);
    tft.setTextColor(CAL_TEXT_COLOR);
    tft.println("Touch Calibration Required");
    tft.println("Follow on-screen instructions.");
    delay(1000);

    tft.calibrateTouch(nullptr, TFT_MAGENTA, CAL_BG_COLOR, 15);

    if (SPIFFS.exists(SKETCH_CALIBRATION_FILE)) {
    } else {
    }
  } else {
  }
}

void loop() {
  handleTouchInput();
}

void handleTouchInput() {
  if (millis() - lastTouchTime < touchDebounceDelay) {
    uint16_t t_x, t_y;
    if (!tft.getTouch(&t_x, &t_y, 10)) {
      lastTouchTime = 0;
    }
    return;
  }

  uint16_t touchX, touchY;

  if (tft.getTouch(&touchX, &touchY)) {
    lastTouchTime = millis();

    if (gameOver) {
      setupGame();
    } else {

      if (touchX >= GRID_X_OFFSET && touchX < GRID_X_OFFSET + GRID_SIZE && touchY >= GRID_Y_OFFSET && touchY < GRID_Y_OFFSET + GRID_SIZE) {

        int col = (touchX - GRID_X_OFFSET) / CELL_SIZE;
        int row = (touchY - GRID_Y_OFFSET) / CELL_SIZE;

        if (col >= 0 && col < 3 && row >= 0 && row < 3) {
          if (board[row][col] == PLAYER_NONE) {
            board[row][col] = currentPlayer;

            int centerX = GRID_X_OFFSET + col * CELL_SIZE + CELL_SIZE / 2;
            int centerY = GRID_Y_OFFSET + row * CELL_SIZE + CELL_SIZE / 2;
            if (currentPlayer == PLAYER_X) {
              drawX(centerX, centerY);
            } else {
              drawO(centerX, centerY);
            }

            if (checkWin()) {
              gameOver = true;
              winner = currentPlayer;
              String winMsg = "Player ";
              winMsg += (winner == PLAYER_X ? "X" : "O");
              winMsg += " Wins!";
              displayMessage(winMsg, "Tap to play again", WINNER_BG_COLOR);
            } else if (checkDraw()) {
              gameOver = true;
              winner = PLAYER_NONE;
              displayMessage("It's a Draw!", "Tap to play again", TFT_DARKGREY);
            } else {
              currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
              updateTurnMessage();
            }
          }
        }
      }
    }
  }
}

void setupGame() {

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      board[r][c] = PLAYER_NONE;
    }
  }
  currentPlayer = PLAYER_X;
  gameOver = false;
  winner = PLAYER_NONE;

  tft.fillScreen(BG_COLOR);
  drawBoard();
  updateTurnMessage();
}

void drawBoard() {

  for (int i = 1; i < 3; i++) {
    tft.drawLine(GRID_X_OFFSET + i * CELL_SIZE, GRID_Y_OFFSET,
                 GRID_X_OFFSET + i * CELL_SIZE, GRID_Y_OFFSET + GRID_SIZE,
                 LINE_COLOR);
    tft.drawLine(GRID_X_OFFSET, GRID_Y_OFFSET + i * CELL_SIZE,
                 GRID_X_OFFSET + GRID_SIZE, GRID_Y_OFFSET + i * CELL_SIZE,
                 LINE_COLOR);
  }

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      int centerX = GRID_X_OFFSET + c * CELL_SIZE + CELL_SIZE / 2;
      int centerY = GRID_Y_OFFSET + r * CELL_SIZE + CELL_SIZE / 2;
      if (board[r][c] == PLAYER_X) {
        drawX(centerX, centerY);
      } else if (board[r][c] == PLAYER_O) {
        drawO(centerX, centerY);
      }
    }
  }
}

void drawX(int centerX, int centerY) {
  int armLength = CELL_SIZE / 3;
  tft.drawLine(centerX - armLength, centerY - armLength,
               centerX + armLength, centerY + armLength, X_COLOR);
  tft.drawLine(centerX - armLength + 1, centerY - armLength,
               centerX + armLength + 1, centerY + armLength, X_COLOR);
  tft.drawLine(centerX - armLength, centerY - armLength + 1,
               centerX + armLength, centerY + armLength + 1, X_COLOR);

  tft.drawLine(centerX - armLength, centerY + armLength,
               centerX + armLength, centerY - armLength, X_COLOR);
  tft.drawLine(centerX - armLength + 1, centerY + armLength,
               centerX + armLength + 1, centerY - armLength, X_COLOR);
  tft.drawLine(centerX - armLength, centerY + armLength - 1,
               centerX + armLength, centerY - armLength - 1, X_COLOR);
}

void drawO(int centerX, int centerY) {
  int radius = CELL_SIZE / 3;
  tft.drawCircle(centerX, centerY, radius, O_COLOR);
  tft.drawCircle(centerX, centerY, radius - 1, O_COLOR);
}

bool checkWin() {

  for (int r = 0; r < 3; r++) {
    if (board[r][0] == currentPlayer && board[r][1] == currentPlayer && board[r][2] == currentPlayer) return true;
  }
  for (int c = 0; c < 3; c++) {
    if (board[0][c] == currentPlayer && board[1][c] == currentPlayer && board[2][c] == currentPlayer) return true;
  }
  if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) return true;
  if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) return true;

  return false;
}

bool checkDraw() {
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      if (board[r][c] == PLAYER_NONE) return false;
    }
  }

  return true;
}

void displayMessage(String msg1, String msg2, uint16_t bgColor) {
  int msgAreaY = GRID_Y_OFFSET + GRID_SIZE;

  if (msgAreaY >= screenHeight) msgAreaY = screenHeight - 60;
  if (msgAreaY < 0) msgAreaY = 0;

  int msgAreaHeight = screenHeight - msgAreaY;
  if (msgAreaHeight <= 20) msgAreaHeight = 60;

  tft.fillRect(0, msgAreaY, screenWidth, msgAreaHeight, bgColor);

  tft.setTextColor(TEXT_COLOR, bgColor);
  tft.setTextWrap(true);
  tft.setTextDatum(MC_DATUM);

  int messageFont = 2;

  int yPos1 = msgAreaY + msgAreaHeight / 2;
  if (msg2 != "") {
    yPos1 = msgAreaY + msgAreaHeight / 3;
  }
  tft.drawString(msg1, screenWidth / 2, yPos1, messageFont);

  if (msg2 != "") {
    int yPos2 = msgAreaY + (msgAreaHeight * 2) / 3;
    tft.drawString(msg2, screenWidth / 2, yPos2, messageFont);
  }
}

void updateTurnMessage() {
  if (gameOver) return;
  String turnMsg = "Player ";
  turnMsg += (currentPlayer == PLAYER_X ? "X" : "O");
  turnMsg += "'s Turn";
  displayMessage(turnMsg, "", BG_COLOR);
}

void logo() {
  tft.fillScreen(TFT_GREEN);
  int centerX = 120;
  int centerY = 160;
  int radius = 70;
  int thickness = 7;

  tft.fillCircle(centerX, centerY, radius, TFT_RED);
  for (int r = radius - thickness / 2; r <= radius + thickness / 2; r++) {
    tft.drawCircle(centerX, centerY, r, TFT_BLACK);
  }

  tft.setTextColor(TFT_BLACK, TFT_RED);
  tft.setTextDatum(MC_DATUM);
  tft.setFreeFont(&FreeSansBold24pt7b);
  tft.drawString("DSN", centerX, centerY);
  tft.setTextColor(TFT_BLACK, TFT_GREEN);
  tft.setFreeFont(&FreeSansBold9pt7b);
  tft.drawString("Tic Tac Toe Game", centerX, 300);
}