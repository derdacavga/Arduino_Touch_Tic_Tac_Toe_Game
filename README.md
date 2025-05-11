# Touch Tic Tac Toe Game Developed Using TFT_eSPI Library with ESP32-S3

This project is a classic Tic Tac Toe (XOX) game developed using the ESP32-S3 microcontroller and an ILI9341 TFT screen (with an XPT2046 touch controller). 
The game is written with the popular TFT_eSPI library and features automatic touchscreen calibration upon initial startup.

🎮 Features
Classic 3x3 Tic Tac Toe game logic.
Colorful graphical interface with game board, X and O symbols.
Making moves via touch input using the XPT2046 touch controller.
Informative messages indicating the current player, winner, or a draw.
Ability to restart the game by touching the screen when the game ends.
Automatic Touch Calibration:
Automatically starts touchscreen calibration on the first run or if the calibration file is not found.
Saves the calibration data to the ESP32-S3's SPIFFS memory and skips the calibration step on subsequent startups by using this data.
🛠️ Hardware Requirements
Microcontroller: ESP32-S3 (Any ESP32-S3 development board will work)
Display: ILI9341-based TFT LCD Screen (240x320 resolution recommended)
Touch Controller: XPT2046 touch controller integrated with the screen
Jumper wires for connections
⚙️ Software and Library Requirements
Arduino IDE: Latest version or a version with ESP32-S3 support.
ESP32 Board Support: ESP32 board package must be installed in the Arduino IDE via the ESP32 board manager URL.
Libraries:
TFT_eSPI by Bodmer: Can be installed via the Arduino IDE Library Manager.
🔧 Setup and Configuration
Library Installation: Install the TFT_eSPI library mentioned above through your Arduino IDE's Library Manager.
TFT_eSPI Configuration (VERY IMPORTANT!):
For the TFT_eSPI library to work correctly, pin configurations and driver settings must be made. These settings are located in the User_Setup.h file (or a file created by copying from User_Setup_Select.h) within the TFT_eSPI folder in your Arduino libraries directory.
Make sure to adjust the following settings according to your hardware:
Enable the correct driver: #define ILI9341_DRIVER
Define the SPI pins your ESP32-S3 uses for the TFT display: TFT_MOSI, TFT_SCLK, TFT_CS, TFT_DC, TFT_RST.
Enable the touch screen and define its pins:
#define XPT2046_TOUCH
#define TOUCH_CS your_touch_cs_pin (e.g., 5)
The touch controller usually uses the same SPI pins as the TFT.
Define the path where the calibration file will be saved (this must be the same as SKETCH_CALIBRATION_FILE in this project): #define TFT_CALIBRATION_FILE "/TouchCalDataFile"
Adjust SPI_FREQUENCY and TOUCH_SPI_FREQUENCY settings if necessary.
For detailed information and examples, examine the comments in the User_Setup.h file in the TFT_eSPI library.
SPIFFS (File System):
This project uses SPIFFS to save touch calibration data. You may need to create a SPIFFS image for ESP32 using the "ESP32 Sketch Data Upload" tool from the Arduino IDE (it's usually formatted automatically on first use or if the file system is empty).
Uploading the Code:
In the Arduino IDE, select the correct ESP32-S3 board and port.
Upload the code to your ESP32-S3.
🚀 How to Play?
After uploading the code to the ESP32-S3, power up the device.
Calibration:
If calibration has not been done before or the calibration file is not found, the screen will ask you to touch specific points. Follow the on-screen instructions to complete the calibration.
After successful calibration, the data will be saved, and the game will start.
Gameplay:
The game board will appear on the screen. The current player (X or O) is indicated in the message area.
To make a move, touch an empty cell on the game board.
The game continues until a player lines up three of their symbols horizontally, vertically, or diagonally, or until there are no empty cells left on the board (draw).
Game End:
The winning player or a draw is indicated on the screen.
To start a new game, simply touch anywhere on the screen.
💡 Potential Improvements
More advanced graphics and animations can be added.
Sound effects can be added (e.g., when a move is made or the game ends).
An AI opponent with different difficulty levels can be added.
A score board can be kept.
Different theme options can be offered.
