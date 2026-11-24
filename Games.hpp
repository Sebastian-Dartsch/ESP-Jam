#pragma once

#include <Fonts/FreeSansOblique9pt7b.h>
#include "Fonts/Picopixel.h"

int drawCard() {
  return random(1, 13);
}

void exitGame() {
  Game = false;
  Game2 = false;
  Game4 = false;
  Game5 = false;
  Spam = false;
  Menu = true;
  display.clearDisplay();
  drawMenu();
  display.display();
}

int getCardValue(int card) {
  if (card > 10) return 10;
  if (card == 1) return 11;
  return card;
}

int getScore(int hand[], int count) {
  int score = 0, aces = 0;
  for (int i = 0; i < count; i++) {
    int val = getCardValue(hand[i]);
    score += val;
    if (val == 11) aces++;
  }
  while (score > 21 && aces > 0) {
    score -= 10;
    aces--;
  }
  return score;
}


float playerX2 = 60;
float playerY2 = 40;
float velocityY2 = 0;
const float gravity2 = 0.30;       
const float jumpStrength2 = -4.2;  
int score3 = 0;
bool gameOver3 = false;
int facingDir2 = 1;   

bool jetpackActive = false;
int jetpackTimer = 0;
const int JETPACK_DURATION = 50;  

#define NUM_PLATFORMS 5
struct Platform { 
  int x; 
  float y; 
  int width; 
  bool hasJetpack; 
};
Platform plats[NUM_PLATFORMS];

#define MAX_PARTICLES 8
struct Particle { float x, y, vx, vy; int life; };
Particle particles[MAX_PARTICLES];

void spawnParticle(float x, float y, float vy_modifier) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].life <= 0) {
      particles[i].x = x;
      particles[i].y = y;
      particles[i].vx = random(-10, 11) / 10.0;
      particles[i].vy = (random(10, 30) / 10.0) + vy_modifier;
      particles[i].life = random(5, 12);
      break;
    }
  }
}

void drawCardGraphic(int x, int y, int card, bool isHidden) {
  if (x > 114) return;
  display.fillRoundRect(x, y, 14, 24, 3, SSD1306_BLACK);
  display.drawRoundRect(x, y, 14, 24, 3, SSD1306_WHITE);
  display.setCursor(x + 4, y + 8);
  if (isHidden) {
    display.print("#");
  } else {
    if (card == 1) display.print("A");
    else if (card == 10) display.print("J");
    else if (card == 11) display.print("Q");
    else if (card == 12) display.print("K");
    else display.print(card);
  }
}

void render() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(2, 2);
  display.print("Dealer:");
  display.setCursor(15, 12);
  if (!gameOver) {
    display.print("##");
  } else {
    display.print(getScore(dealerHand, dCount));
  }

  for (int i = 0; i < dCount; i++) {
    bool hidden = (!gameOver && i == 1);
    drawCardGraphic(55 + (i * 16), 2, dealerHand[i], hidden);
  }

  display.setCursor(2, 30);
  display.print("You:");
  display.setCursor(15, 40);
  display.print(getScore(playerHand, pCount));
  for (int i = 0; i < pCount; i++) {
    drawCardGraphic(55 + (i * 16), 28, playerHand[i], false);
  }

  display.drawRect(0, 54, 128, 10, SSD1306_WHITE);

  if (!gameOver) {
    const char* opts[] = { "HIT", "STAY", "DBL" };
    int xPos[] = { 12, 54, 95 };
    for (int i = 0; i < 3; i++) {
      if (selectedOption == i) {
        display.fillRect(xPos[i] - 2, 55, 30, 8, SSD1306_WHITE);
        display.setTextColor(SSD1306_BLACK);
      } else {
        display.setTextColor(SSD1306_WHITE);
      }
      display.setCursor(xPos[i], 56);
      display.print(opts[i]);
    }
  } else {
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(5, 56);
    display.print(statusMsg);
  }
  display.display();
}

void startNewGame() {
  pCount = 0;
  dCount = 0;
  playerHand[pCount++] = drawCard();
  playerHand[pCount++] = drawCard();
  dealerHand[dCount++] = drawCard();
  dealerHand[dCount++] = drawCard();
  gameOver = false;
  selectedOption = 0;
  render();
}

void finishGame() {
  while (getScore(dealerHand, dCount) < 17) { dealerHand[dCount++] = drawCard(); }
  int p = getScore(playerHand, pCount);
  int d = getScore(dealerHand, dCount);
  if (p > 21) {
    statusMsg = "BUST!";
    tone(BUZZER_PIN, 260, 25);
    delay(50);
    noTone(BUZZER_PIN);
    delay(25);
    tone(BUZZER_PIN, 210, 25);
    delay(25);
    noTone(BUZZER_PIN);
  } else if (d > 21 || p > d) {
    statusMsg = "YOU WIN!";
    tone(BUZZER_PIN, 210, 25);
    delay(50);
    noTone(BUZZER_PIN);
    delay(25);
    tone(BUZZER_PIN, 260, 25);
    delay(25);
    noTone(BUZZER_PIN);
  } else if (p < d) {
    statusMsg = "LOST!";
    tone(BUZZER_PIN, 260, 25);
    delay(50);
    noTone(BUZZER_PIN);
    delay(25);
    tone(BUZZER_PIN, 210, 25);
    delay(25);
    noTone(BUZZER_PIN);
  } else {
    statusMsg = "PUSH!";
    tone(BUZZER_PIN, 260, 25);
    delay(50);
    noTone(BUZZER_PIN);
    delay(25);
    tone(BUZZER_PIN, 210, 25);
    delay(25);
    noTone(BUZZER_PIN);
  }
  gameOver = true;
  render();
}

void playBlackJack() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextWrap(false);
  randomSeed(esp_random());

  static const unsigned char PROGMEM image_cards_clubs_bits[] = { 0x03, 0x80, 0x07, 0xc0, 0x0f, 0xe0, 0x0f, 0xe0, 0x0f, 0xe0, 0x07, 0xc0, 0x3b, 0xb8, 0x7f, 0xfc, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xfe, 0xfe, 0x7d, 0x7c, 0x39, 0x38, 0x03, 0x80, 0x07, 0xc0 };
  static const unsigned char PROGMEM image_cards_diamonds_bits[] = { 0x01, 0x00, 0x03, 0x80, 0x03, 0x80, 0x07, 0xc0, 0x0f, 0xe0, 0x0f, 0xe0, 0x1f, 0xf0, 0x3f, 0xf8, 0x7f, 0xfc, 0x3f, 0xf8, 0x1f, 0xf0, 0x0f, 0xe0, 0x0f, 0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01, 0x00 };
  static const unsigned char PROGMEM image_cards_hearts_bits[] = { 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x7c, 0x7c, 0xfe, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0x7f, 0xfc, 0x3f, 0xf8, 0x1f, 0xf0, 0x0f, 0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01, 0x00, 0x00, 0x00 };
  static const unsigned char PROGMEM image_cards_spades_bits[] = { 0x01, 0x00, 0x03, 0x80, 0x07, 0xc0, 0x0f, 0xe0, 0x1f, 0xf0, 0x3f, 0xf8, 0x7f, 0xfc, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xfd, 0x7e, 0x7b, 0xbc, 0x33, 0x98, 0x07, 0xc0, 0x0f, 0xe0, 0x1f, 0xf0 };

  const char* Layer_1_text = "PLAY";
  display.clearDisplay();
  display.setTextColor(1);
  display.setTextWrap(false);
  display.setFont(&Picopixel);
  display.setCursor(0, 4);
  display.print("BALANCE:");
  display.setCursor(31, 4);
  display.print("1000");
  display.drawLine(0, 6, 127, 6, 1);
  display.drawBitmap(48, 14, image_cards_clubs_bits, 15, 16, 1);
  display.drawBitmap(81, 15, image_cards_diamonds_bits, 15, 16, 1);
  display.drawBitmap(65, 14, image_cards_spades_bits, 15, 16, 1);
  display.drawBitmap(31, 14, image_cards_hearts_bits, 15, 16, 1);
  display.setFont(&FreeSansOblique9pt7b);
  display.setCursor(7, 48);
  display.print("BLACK JACK");
  display.fillRoundRect(55, 55, 19, 9, 1, 1);
  display.setTextColor(0);
  display.setFont(&Picopixel);
  display.setCursor(57, 61);
  display.print(Layer_1_text);
  display.display();

  delay(1000);
  display.setFont();
  display.clearDisplay();

  Menu = false;
  Game = true;
  startr = true;
  startNewGame();
  render();
}

void handleBlackJack() {
  if (startr) {
    render();
    startr = false;
  }
  if (gameOver) {
    delay(2000);
    startNewGame();
    return;
  }

  int buttonState = digitalRead(DownbuttonPin);
  if (buttonState == LOW) {
    if (!isPressing) {
      isPressing = true;
      buttonPressedTime = millis();
      longPressExecuted = false;
    }
    if (!longPressExecuted && (millis() - buttonPressedTime >= longPressTime)) {
      exitGame();
      longPressExecuted = true;
    }
  } else {
    if (isPressing) { isPressing = false; }
  }

  if (digitalRead(LeftbuttonPin) == LOW) {
    selectedOption = (selectedOption - 1 + 3) % 3;
    render();
    delay(200);
  }
  if (digitalRead(RightbuttonPin) == LOW) {
    selectedOption = (selectedOption + 1) % 3;
    render();
    delay(200);
  }
  if (digitalRead(SubmitbuttonPin) == LOW) {
    delay(200);
    if (selectedOption == 0) {
      playerHand[pCount++] = drawCard();
      if (getScore(playerHand, pCount) > 21) { finishGame(); }
    } else if (selectedOption == 1) {
      finishGame();
    } else if (selectedOption == 2) {
      playerHand[pCount++] = drawCard();
      finishGame();
    }
    render();
  }
}

void playerPaddleTone() {
  tone(BUZZER_PIN, 250, 25);
  delay(25);
  noTone(BUZZER_PIN);
}
void mcuPaddleTone() {
  tone(BUZZER_PIN, 225, 25);
  delay(25);
  noTone(BUZZER_PIN);
}
void wallTone() {
  tone(BUZZER_PIN, 200, 25);
  delay(25);
  noTone(BUZZER_PIN);
}
void player_scoreTone() {
  tone(BUZZER_PIN, 200, 25);
  delay(50);
  noTone(BUZZER_PIN);
  delay(25);
  tone(BUZZER_PIN, 250, 25);
  delay(25);
  noTone(BUZZER_PIN);
}
void mcu_scoreTone() {
  tone(BUZZER_PIN, 250, 25);
  delay(25);
  noTone(BUZZER_PIN);
  delay(25);
  tone(BUZZER_PIN, 200, 25);
  delay(25);
  noTone(BUZZER_PIN);
}
void drawCourt() {
  display.drawRect(0, 0, 128, 54, SSD1306_WHITE);
}

void playPingPong() {
  Game2 = true;
  Menu = false;
  display.display();
  display.clearDisplay();
  drawCourt();
  display.display();
  ball_update = millis();
  paddle_update = ball_update;
  starter = true;
}

void handlePingPong() {
  int buttonState = digitalRead(LeftbuttonPin);
  if (buttonState == LOW) {
    if (!isPressing) {
      isPressing = true;
      buttonPressedTime = millis();
      longPressExecuted = false;
    }
    if (!longPressExecuted && (millis() - buttonPressedTime >= longPressTime)) {
      exitGame();
      longPressExecuted = true;
      return;
    }
  } else {
    isPressing = false;
  }

  bool update_needed = false;
  unsigned long time = millis();
  static bool up_state = false;
  static bool down_state = false;

  up_state |= (digitalRead(UpbuttonPin) == LOW);
  down_state |= (digitalRead(DownbuttonPin) == LOW);
  if (starter) {
    display.clearDisplay();
    ball_x = 53;
    ball_y = 26;
    ball_dir_x = 1;
    ball_dir_y = 1;
    mcu_y = 16;
    player_y = 16;
    mcu_score = 0;
    player_score = 0;
    game_over = false;
    starter = false;
    drawCourt();
  }

  if (time > ball_update) {
    uint8_t new_x = ball_x + ball_dir_x;
    uint8_t new_y = ball_y + ball_dir_y;
    if (new_x == 0 || new_x == 127) {
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
      if (new_x < 64) {
        player_scoreTone();
        player_score++;
      } else {
        mcu_scoreTone();
        mcu_score++;
      }
      if (player_score == SCORE_LIMIT || mcu_score == SCORE_LIMIT) {
        win = player_score > mcu_score;
        game_over = true;
      }
    }
    if (new_y == 0 || new_y == 53) {
      wallTone();
      ball_dir_y = -ball_dir_y;
      new_y += ball_dir_y + ball_dir_y;
    }
    if (new_x == MCU_X && new_y >= mcu_y && new_y <= mcu_y + PADDLE_HEIGHT) {
      mcuPaddleTone();
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
    }
    if (new_x == PLAYER_X && new_y >= player_y && new_y <= player_y + PADDLE_HEIGHT) {
      playerPaddleTone();
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
    }

    display.drawPixel(ball_x, ball_y, SSD1306_BLACK);
    display.drawPixel(new_x, new_y, SSD1306_WHITE);
    ball_x = new_x;
    ball_y = new_y;
    ball_update += BALL_RATE;
    update_needed = true;
  }

  if (time > paddle_update) {
    paddle_update += PADDLE_RATE;
    display.drawFastVLine(MCU_X, mcu_y, PADDLE_HEIGHT, SSD1306_BLACK);
    const uint8_t half_paddle = PADDLE_HEIGHT >> 1;
    if (mcu_y + half_paddle > ball_y) {
      int8_t dir = ball_x > MCU_X ? -1 : 1;
      mcu_y += dir;
    }
    if (mcu_y + half_paddle < ball_y) {
      int8_t dir = ball_x > MCU_X ? 1 : -1;
      mcu_y += dir;
    }
    if (mcu_y < 1) mcu_y = 1;
    if (mcu_y + PADDLE_HEIGHT > 53) mcu_y = 53 - PADDLE_HEIGHT;
    display.drawFastVLine(MCU_X, mcu_y, PADDLE_HEIGHT, SSD1306_WHITE);
    display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, SSD1306_BLACK);
    if (up_state) player_y -= 1;
    if (down_state) player_y += 1;
    up_state = down_state = false;
    if (player_y < 1) player_y = 1;
    if (player_y + PADDLE_HEIGHT > 53) player_y = 53 - PADDLE_HEIGHT;
    display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, SSD1306_WHITE);
    update_needed = true;
  }

  if (update_needed) {
    if (game_over) {
      const char* text = win ? "YOU WIN!!" : "YOU LOSE!";
      display.clearDisplay();
      display.setCursor(40, 28);
      display.print(text);
      display.display();
      delay(3000);
      exitGame();
    }
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    display.setCursor(0, 56);
    display.print(mcu_score);
    display.setCursor(122, 56);
    display.print(player_score);
    display.display();
  }
}

void resetGame() {
  playerX = 10;
  playerY = 35;
  lives = 3;
  score2 = 0;
  difficulty = 1;
  bossActive = false;
  nextBossAt = 1000;
  for (int i = 0; i < MAX_STARS; i++) {
    stars[i].x = random(0, 128);
    stars[i].y = random(12, 63);
    stars[i].speed = random(5, 15) / 10.0;
  }
  for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = false;
  for (int i = 0; i < MAX_BOSS_BULLETS; i++) bossBullets[i].active = false;
  for (int i = 0; i < MAX_ENEMIES; i++) enemies[i].active = false;
  gameOver2 = false;
}

void resetGame2() {
  playerX2 = 64;
  playerY2 = 40;
  velocityY2 = jumpStrength2;
  score3 = 0;
  gameOver3 = false;
  jetpackActive = false;
  jetpackTimer = 0;
  
  for (int i = 0; i < MAX_PARTICLES; i++) particles[i].life = 0;

  plats[0].x = 52; 
  plats[0].y = 55; 
  plats[0].width = 24;
  plats[0].hasJetpack = false;
  
  for (int i = 1; i < NUM_PLATFORMS; i++) {
    plats[i].x = random(5, 100);
    plats[i].y = plats[i-1].y - random(13, 17); 
    plats[i].width = random(16, 24);
    plats[i].hasJetpack = (random(0, 100) > 95);
  }
}

void playDoodleJump() {
  Game5 = true;
  Menu = false;
  randomSeed(analogRead(34));
  resetGame2();
  display.clearDisplay();
  display.display();
}

void Raumschiff() {
  Game4 = true;
  Menu = false;
  randomSeed(esp_random());
}

void fireBullet() {
  if (millis() - lastShotTime < 180) return;
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (!bullets[i].active) {
      bullets[i].active = true;
      bullets[i].x = playerX + 6;
      bullets[i].y = nextShotLeft ? (playerY - 5) : (playerY + 5);
      nextShotLeft = !nextShotLeft;
      lastShotTime = millis();
      break;
    }
  }
}

void spawnEnemy() {
  if (bossActive || random(100) > (4 + difficulty)) return;
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active) {
      enemies[i].active = true;
      enemies[i].x = 128;
      enemies[i].y = random(15, 60);
      enemies[i].type = random(0, 2);
      enemies[i].speed = (random(10, 50) / 7.0) + (difficulty * 2);
      enemies[i].rot = random(0, 4);
      enemies[i].hp = (enemies[i].type == 0) ? 2 : 1;
      break;
    }
  }
}

void updateGame() {
  if (!bossActive && score2 >= nextBossAt) {
    bossActive = true;
    bossHP = 100 + (difficulty * 10);
    bossY = 32;
  }

  for (int i = 0; i < MAX_STARS; i++) {
    stars[i].x -= stars[i].speed;
    if (stars[i].x < 0) {
      stars[i].x = 128;
      stars[i].y = random(12, 63);
    }
  }

  if (digitalRead(UpbuttonPin) == LOW && playerY > 16) playerY -= 2;
  if (digitalRead(DownbuttonPin) == LOW && playerY < 60) playerY += 2;
  if (digitalRead(LeftbuttonPin) == LOW && playerX > 5) playerX -= 2;
  if (digitalRead(RightbuttonPin) == LOW && playerX < 60) playerX += 2;

  fireBullet();

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].active) {
      bullets[i].x += 6;
      if (bullets[i].x > 128) bullets[i].active = false;

      if (bossActive && bullets[i].active && bullets[i].x > 60 && abs(bullets[i].y - bossY) < 25) {
        bullets[i].active = false;
        bossHP--;
        if (bossHP <= 0) {
          bossActive = false;
          score2 += 250;
          nextBossAt += 1000;
          difficulty++;
          for (int j = 0; j < MAX_BOSS_BULLETS; j++) bossBullets[j].active = false;
        }
      }
    }
  }

  if (bossActive) {
    if (bossDirDown) bossY++;
    else bossY--;
    if (bossY > 45 || bossY < 25) bossDirDown = !bossDirDown;

    if (abs(80 - playerX) < 20 && abs(bossY - playerY) < 20) {
      lives = 0;
      gameOver2 = true;
    }

    if (millis() - lastBossShotTime > (unsigned long)(800 - (difficulty * 50))) {
      for (int i = 0; i < MAX_BOSS_BULLETS; i++) {
        if (!bossBullets[i].active) {
          bossBullets[i].active = true;
          bossBullets[i].x = 75;
          bossBullets[i].y = bossY;
          lastBossShotTime = millis();
          break;
        }
      }
    }
  } else {
    for (int i = 0; i < MAX_ENEMIES; i++) {
      if (enemies[i].active) {
        enemies[i].x -= enemies[i].speed;
        if (abs((int)enemies[i].x - playerX) < 8 && abs(enemies[i].y - playerY) < 6) {
          enemies[i].active = false;
          lives--;
          if (lives <= 0) gameOver2 = true;
        }
        if (enemies[i].x < -10) enemies[i].active = false;
      }
    }
  }

  for (int i = 0; i < MAX_BOSS_BULLETS; i++) {
    if (bossBullets[i].active) {
      bossBullets[i].x -= 4;
      if (bossBullets[i].x < 0) bossBullets[i].active = false;

      if (abs((int)bossBullets[i].x - playerX) < 6 && abs(bossBullets[i].y - playerY) < 6) {
        bossBullets[i].active = false;
        lives--;
        if (lives <= 0) gameOver2 = true;
      }
    }
  }

  for (int b = 0; b < MAX_BULLETS; b++) {
    if (!bullets[b].active) continue;
    for (int e = 0; e < MAX_ENEMIES; e++) {
      if (enemies[e].active && abs(bullets[b].x - (int)enemies[e].x) < 7 && abs(bullets[b].y - enemies[e].y) < 6) {
        bullets[b].active = false;
        enemies[e].hp--;

        if (enemies[e].hp <= 0) {
          enemies[e].active = false;
          score2 += (enemies[e].type == 1) ? 25 : 15;
        }
      }
    }
  }
  spawnEnemy();
}

void drawAsteroid(int x, int y, int rot) {
  display.drawPixel(x - 3, y, WHITE);
  display.drawPixel(x + 3, y, WHITE);
  display.drawPixel(x, y - 3, WHITE);
  display.drawPixel(x, y + 3, WHITE);
  display.drawLine(x - 2, y - 2, x + 2, y - 2, WHITE);
  display.drawLine(x - 2, y + 2, x + 2, y + 2, WHITE);
  if (rot == 0) display.drawPixel(x - 1, y - 1, WHITE);
  else if (rot == 1) display.drawPixel(x + 1, y - 1, WHITE);
  else if (rot == 2) display.drawPixel(x + 1, y + 1, WHITE);
  else display.drawPixel(x - 1, y + 1, WHITE);
}

void drawNewBoss(int x, int y) {
  int dx = x - 65;
  int dy = y - 30;

  display.drawBitmap(55 + dx, 5 + dy, image_paint_2_copy_1_bits, 64, 13, 1);
  display.drawBitmap(83 + dx, 18 + dy, image_paint_29_bits, 8, 1, 1);
  display.drawBitmap(55 + dx, 46 + dy, image_paint_2_2_bits, 64, 13, 1);
  display.drawBitmap(80 + dx, 23 + dy, image_paint_26_bits, 1, 1, 1);
  display.fillRect(57 + dx, 26 + dy, 59, 12, 1);
  display.drawBitmap(61 + dx, 26 + dy, image_paint_10_bits, 1, 12, 1);
  display.drawBitmap(116 + dx, 27 + dy, image_paint_33_bits, 1, 8, 1);
  display.drawBitmap(57 + dx, 26 + dy, image_paint_5_bits, 5, 12, 0);
  display.drawLine(59 + dx, 36 + dy, 56 + dx, 36 + dy, 1);
  display.drawLine(56 + dx, 33 + dy, 53 + dx, 33 + dy, 1);
  display.drawLine(56 + dx, 30 + dy, 53 + dx, 30 + dy, 1);
  display.drawLine(59 + dx, 27 + dy, 56 + dx, 27 + dy, 1);
  display.drawLine(82 + dx, 45 + dy, 60 + dx, 45 + dy, 1);
  display.drawLine(82 + dx, 45 + dy, 60 + dx, 45 + dy, 1);
  display.drawLine(82 + dx, 18 + dy, 60 + dx, 18 + dy, 1);
  display.drawLine(113 + dx, 45 + dy, 91 + dx, 45 + dy, 1);
  display.drawLine(113 + dx, 18 + dy, 91 + dx, 18 + dy, 1);
  display.drawBitmap(111 + dx, 26 + dy, image_paint_16_bits, 5, 12, 0);
  display.drawBitmap(111 + dx, 26 + dy, image_paint_17_bits, 9, 12, 1);
  display.drawBitmap(88 + dx, 34 + dy, image_paint_19_bits, 30, 4, 0);
  display.drawBitmap(88 + dx, 24 + dy, image_paint_19_copy_1_bits, 30, 4, 0);
  display.drawBitmap(113 + dx, 28 + dy, image_paint_21_bits, 7, 6, 0);
  display.drawBitmap(104 + dx, 35 + dy, image_paint_25_copy_1_bits, 13, 5, 1);
  display.drawBitmap(111 + dx, 27 + dy, image_paint_24_bits, 2, 8, 0);
  display.drawBitmap(104 + dx, 22 + dy, image_paint_25_1_bits, 13, 5, 1);
  display.drawBitmap(56 + dx, 25 + dy, image_paint_25_2_bits, 61, 12, 1);
  display.drawLine(81 + dx, 24 + dy, 76 + dx, 24 + dy, 1);
  display.drawLine(82 + dx, 21 + dy, 77 + dx, 21 + dy, 1);
  display.drawBitmap(76 + dx, 6 + dy, image_paint_28_bits, 16, 53, 1);
  display.drawBitmap(81 + dx, 20 + dy, image_paint_28_1_bits, 2, 3, 1);
  display.drawBitmap(83 + dx, 5 + dy, image_paint_30_bits, 34, 54, 0);
  display.drawBitmap(57 + dx, 35 + dy, image_paint_26_bits, 1, 1, 0);
}

void drawGame() {
  display.clearDisplay();
  for (int i = 0; i < MAX_STARS; i++) display.drawPixel((int)stars[i].x, stars[i].y, WHITE);
  display.drawFastHLine(0, 10, 128, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 1);
  display.print("HP:");
  for (int i = 0; i < lives; i++) display.print("I");
  display.setCursor(60, 1);
  display.print("S:");
  display.print(score2);

  if (gameOver2) {
    display.setCursor(35, 25);
    display.setTextSize(2);
    display.print("OVER");
    display.setTextSize(1);
    display.setCursor(30, 45);
    display.print("Press Submit");
    display.display();
    return;
  }

  display.fillTriangle(playerX - 5, playerY - 7, playerX - 5, playerY + 7, playerX + 3, playerY, SSD1306_WHITE);
  display.fillRect(playerX - 6, playerY - 1, 10, 3, SSD1306_WHITE);
  display.drawLine(playerX + 3, playerY, playerX + 7, playerY, SSD1306_WHITE);
  display.drawLine(playerX - 8, playerY - 5, playerX - 5, playerY - 2, SSD1306_WHITE);
  display.drawLine(playerX - 8, playerY + 5, playerX - 5, playerY + 2, SSD1306_WHITE);
  display.drawPixel(playerX - 8, playerY - 1, SSD1306_WHITE);
  display.drawPixel(playerX - 8, playerY + 1, SSD1306_WHITE);

  if (bossActive) {
    drawNewBoss(80, bossY);
    display.drawRect(105, 1, 22, 5, WHITE);
    display.fillRect(105, 1, map(bossHP, 0, 100 + (difficulty - 1) * 10, 0, 22), 5, WHITE);
  }

  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].active) display.drawFastHLine(bullets[i].x, bullets[i].y, 4, WHITE);
  }

  for (int i = 0; i < MAX_BOSS_BULLETS; i++) {
    if (bossBullets[i].active) {
      display.drawFastHLine(bossBullets[i].x, bossBullets[i].y, 6, WHITE);
    }
  }

  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].active) {
      if (enemies[i].type == 0) drawAsteroid((int)enemies[i].x, enemies[i].y, enemies[i].rot);
      else display.fillTriangle(enemies[i].x + 5, enemies[i].y, enemies[i].x - 3, enemies[i].y - 5, enemies[i].x - 3, enemies[i].y + 5, WHITE);
    }
  }
  display.display();
}

void handleRaumschiff() {
  int buttonState = digitalRead(SubmitbuttonPin);
  if (buttonState == LOW) {
    if (!isPressing) {
      isPressing = true;
      buttonPressedTime = millis();
      longPressExecuted = false;
    }
    if (!longPressExecuted && (millis() - buttonPressedTime >= longPressTime)) {
      exitGame();
      longPressExecuted = true;
      return;
    }
  } else {
    isPressing = false;
  }
  if (gameOver2) {
    drawGame();
    if (digitalRead(SubmitbuttonPin) == LOW) {
      resetGame();
      delay(300);
    }
  } else {
    updateGame();
    drawGame();
    delay(20);
  }
}

void handleDoodle() {
  if (digitalRead(UpbuttonPin) == LOW) {
    if (!isPressing) {
      isPressing = true;
      buttonPressedTime = millis();
      longPressExecuted = false;
    }
    if (!longPressExecuted && (millis() - buttonPressedTime >= longPressTime)) {
      exitGame();
      longPressExecuted = true;
      return;
    }
  } else {
    isPressing = false;
  }

  if (gameOver3) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(12, 15);  display.print("GAME OVER");
    display.setTextSize(1);
    display.setCursor(38, 40); display.print("Score: "); display.print(score3);
    display.setCursor(22, 53); display.print("[Submit] Restart");
    display.display();
    
    if (digitalRead(SubmitbuttonPin) == LOW) { resetGame2(); delay(300); }
    return;
  }

  if (digitalRead(LeftbuttonPin) == LOW) { playerX2 -= 2.2; facingDir2 = -1; }
  if (digitalRead(RightbuttonPin) == LOW) { playerX2 += 2.2; facingDir2 = 1; }

  if (playerX2 < -8) playerX2 = 128;
  if (playerX2 > 128) playerX2 = -8;

  if (jetpackActive) {
    velocityY2 = -5.0; 
    jetpackTimer--;
    if (random(0, 2) == 0) spawnParticle(playerX2 + 4, playerY2 + 8, 2.0);
    if (jetpackTimer <= 0) jetpackActive = false;
  } else {
    velocityY2 += gravity2;
  }
  playerY2 += velocityY2;

  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].life > 0) {
      particles[i].x += particles[i].vx;
      particles[i].y += particles[i].vy;
      particles[i].life--;
    }
  }

  if (velocityY2 > 0 && !jetpackActive) {
    for (int i = 0; i < NUM_PLATFORMS; i++) {
      if (playerX2 + 7 > plats[i].x && playerX2 < plats[i].x + plats[i].width &&
          playerY2 + 8 >= plats[i].y && playerY2 + 8 <= plats[i].y + 3) {
        
        velocityY2 = jumpStrength2; 
        for(int p=0; p<3; p++) spawnParticle(playerX2 + 4, playerY2 + 8, 0.5);
        break; 
      }
    }
  }

  for (int i = 0; i < NUM_PLATFORMS; i++) {
    if (plats[i].hasJetpack && abs(playerX2 + 4 - (plats[i].x + plats[i].width/2)) < 8 && abs(playerY2 + 4 - (plats[i].y - 4)) < 8) {
      plats[i].hasJetpack = false;
      jetpackActive = true;
      jetpackTimer = JETPACK_DURATION;
    }
  }

  if (playerY2 < 25) { 
    float diff = 25 - playerY2;
    playerY2 = 25;
    score3 += (int)diff;
    
    for (int i = 0; i < MAX_PARTICLES; i++) { if (particles[i].life > 0) particles[i].y += diff; }

    for (int i = 0; i < NUM_PLATFORMS; i++) {
      plats[i].y += diff;
      
      if (plats[i].y > 64) {
        float highestY = 64;
        for (int j = 0; j < NUM_PLATFORMS; j++) { if (plats[j].y < highestY) highestY = plats[j].y; }
        
        plats[i].y = highestY - random(13, 17);
        plats[i].x = random(5, 105);
        plats[i].width = random(16, 24);
        plats[i].hasJetpack = (random(0, 100) > 95);
      }
    }
  }

  if (playerY2 > 64) gameOver3 = true;

  display.clearDisplay();
  
  display.setTextSize(1); display.setTextColor(SSD1306_WHITE);
  display.setCursor(4, 1); display.print("SCORE: "); display.print(score3);
  if(jetpackActive) { display.setCursor(85, 1); display.print("BOOST!"); }
  display.drawFastHLine(0, 10, 128, SSD1306_WHITE);

  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].life > 0) display.drawPixel((int)particles[i].x, (int)particles[i].y, SSD1306_WHITE);
  }

  for (int i = 0; i < NUM_PLATFORMS; i++) {
    int py = (int)plats[i].y;
    display.drawFastHLine(plats[i].x, py, plats[i].width, SSD1306_WHITE);
    for(int gx = plats[i].x; gx < plats[i].x + plats[i].width; gx += 2) {
      display.drawPixel(gx, py + 1, SSD1306_WHITE);
    }
    
    if (plats[i].hasJetpack) {
      int jx = plats[i].x + (plats[i].width / 2) - 2;
      display.fillRect(jx, py - 4, 4, 4, SSD1306_WHITE);
      display.drawFastVLine(jx + 1, py - 6, 2, SSD1306_WHITE); 
      display.drawPixel(jx + 2, py - 2, SSD1306_BLACK);       
    }
  }

  int px = (int)playerX2;
  int py = (int)playerY2;
  display.fillRect(px, py, 8, 8, SSD1306_WHITE);
  display.drawPixel(px + 2, py + 2, SSD1306_BLACK);
  display.drawPixel(px + 5, py + 2, SSD1306_BLACK);

  if (jetpackActive) {
    if (facingDir2 == 1) display.fillRect(px - 2, py + 3, 2, 4, SSD1306_WHITE);
    else display.fillRect(px + 8, py + 3, 2, 4, SSD1306_WHITE);
  }

  display.display();
  delay(18);
}
