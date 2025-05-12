# Touch Tic Tac Toe Game Developed Using TFT_eSPI Library with ESP32-S3

# 🎮 Tic Tac Toe (XOX) on ESP32-S3 with ILI9341 Touchscreen

A classic Tic Tac Toe (XOX) game developed using the **ESP32-S3** microcontroller and an **ILI9341 TFT screen** with **XPT2046 touch controller**. Built with the powerful **TFT_eSPI** library, this project offers a fun graphical game experience, including automatic touchscreen calibration on first startup.

---

## ✨ Features

- 🟦 Classic 3x3 Tic Tac Toe game logic  
- 🎨 Colorful graphical interface (game board, X/O symbols)  
- 👉 Touch-based gameplay using the XPT2046 controller  
- ℹ️ On-screen messages for current turn, winner, or draw  
- 🔄 Restart the game by touching the screen after it ends  
- 🛠️ **Automatic Touch Calibration**  
  - On first run or missing calibration file  
  - Saves data to **SPIFFS** for future use  

---

## 🧰 Hardware Requirements

- **Microcontroller:** ESP32-S3 (any dev board)  
- **Display:** ILI9341-based TFT LCD (240x320 recommended)  
- **Touch Controller:** XPT2046 (usually integrated with the screen)  
- **Connections:** Jumper wires  

---

## ⚙️ Software & Library Setup

### Arduino IDE

- Ensure you're using the latest **Arduino IDE** with **ESP32-S3** board support.  
- Add the ESP32 boards URL in the **Boards Manager**:


### Required Libraries

- ✅ [`TFT_eSPI`](https://github.com/Bodmer/TFT_eSPI) by Bodmer  
(Install from Arduino Library Manager)

---

## 🔧 TFT_eSPI Configuration (Very Important!)

Open `User_Setup.h` in the TFT_eSPI library folder and set the following:

- **Enable the correct driver:**

#define ILI9341_DRIVER

Touch calibration data is saved using SPIFFS. If necessary, use the "ESP32 Sketch Data Upload" tool to prepare the SPIFFS filesystem. (Often automatically formatted on first run.)

🚀 How to Play?
Upload the code using the correct board and port in the Arduino IDE.

Power up the ESP32-S3.

First Run:

Calibration screen will prompt you to touch specific points.

Calibration data will be saved in SPIFFS.

Game Starts!

Current player (X or O) is shown.

Touch an empty cell to place your move.

The game ends when someone wins or there's a draw.

Touch the screen anywhere to restart the game.

💡 Potential Improvements
🎞️ Add animations and richer graphics

🔊 Add sound effects (e.g., move, win, draw)

🤖 Add AI opponent with difficulty levels

📊 Implement a scoreboard

🎨 Provide theme customization options

