/*
  Advanced Weather Station
  Author: Atsunyo Gordon Dzidzor Koku
  Created: Monday, March 24, 2025, 10:23:08 AM
*/

#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <SD.h>

// I2C LCD Setup
LiquidCrystal_I2C lcd(0x27, 20, 4);

// DHT22 Setup
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// RTC Setup
RTC_DS1307 rtc;

// Buzzer Pins
const int buzzer1 = 30;
const int buzzer2 = 32;
const int buzzer3 = 34;

// Potentiometer Pin (Air Pressure)
const int pressurePin = A0;

// Keypad Setup
const byte ROWS = 4;
const byte COLS = 4;

// Temperature, humidity and pressure thresholds
const float HIGH_TEMP_THRESHOLD = 30.0;
const float HIGH_HUM_THRESHOLD = 70.0;
const float HIGH_PRES_THRESHOLD = 1050;  //added threshold
const float LOW_TEMP_THRESHOLD = 20.0;
const float LOW_HUM_THRESHOLD = 35.0;
const float LOW_PRES_THRESHOLD = 950;  //added threshold

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 38, 40, 42, 44 };
byte colPins[COLS] = { 39, 41, 43, 45 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// SD Card Setup
const int chipSelect = 53;
File dataFile;

float temperature, humidity, pressure;
int dayData[7][2];
String dayOfWeek[7] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
int currentDay = 0;
bool showData = false;
bool isAlertActive = false;
int selectedDay = 0;

volatile char pressedKey = NO_KEY;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  dht.begin();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  lcd.print("Ms. Nadia");
  delay(2000);
  lcd.clear();

  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzer3, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    lcd.print("SD Card Error");
    while (1)
      ;
  }

  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(rowPins[i]), keypadInterrupt, FALLING);
  }
}

void loop() {
  readSensors();
  handleKeypadInterrupt();
  handleTimeEvents();
  displayMainData();  // Update time every loop.

  if (showData) {
    displayDayData();
  } else {
    checkAlerts();
  }
  delay(100);
}

void readSensors() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  pressure = map(analogRead(pressurePin), 0, 1023, 900, 1100);
}

void handleKeypadInterrupt() {
  if (pressedKey != NO_KEY) {  // Check if a key was pressed
    char key = pressedKey;
    pressedKey = NO_KEY;

    if (key == 'A') {
      showData = !showData;
      lcd.clear();
      if (showData == false) {
        currentDay = 0;
      }
    } else if (key >= '1' && key <= '7' && showData) {
      selectedDay = key - '1';
    }
  }
}

void keypadInterrupt() {
  char key = keypad.getKey();
  if (key) {
    pressedKey = key;
  }
}

// void handleKeypad() {
//   char key = keypad.getKey();  //this line reads the character of the pressed key (if any) and stores it in the key variable.
//   checkKeypadStatus(key);
// }

// void checkKeypadStatus(char key) {
//   if (key) {
//     if (key == 'A') {
//       showData = !showData;
//       lcd.clear();
//       if (showData == false) {
//         currentDay = 0;
//       }
//     } else if (key >= '1' && key <= '7' && showData) {
//       selectedDay = key - '1';
//     }
//   }
// }

void displayMainData() {
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  lcd.print(now.toString("YYYY-MM-DD"));
  lcd.print("  ");
  lcd.print(now.toString("hh:mm:ss"));
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 2);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(0, 3);
  lcd.print("P: ");
  lcd.print(pressure);
  lcd.print("mbar");
}

void displayDayData() {
  lcd.setCursor(0, 0);
  lcd.print("Day ");
  lcd.print(selectedDay + 1);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(dayData[selectedDay][0]);
  lcd.print("C");
  lcd.setCursor(0, 2);
  lcd.print("Hum: ");
  lcd.print(dayData[selectedDay][1]);
  lcd.print("%");
  lcd.setCursor(0, 3);
  lcd.print("Press A to return");
}

void displayWeekData() {
  lcd.setCursor(0, 0);
  lcd.print("Day ");
  lcd.print(selectedDay + 1);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(dayData[selectedDay][0]);
  lcd.print("C");
  lcd.setCursor(0, 2);
  lcd.print("Hum: ");
  lcd.print(dayData[selectedDay][1]);
  lcd.print("%");
  lcd.setCursor(0, 3);
  lcd.print("Press A to return");
}

void checkAlerts() {
  if (temperature > HIGH_TEMP_THRESHOLD) {
    triggerAlert("High Temp!");
  }
  if (humidity > HIGH_HUM_THRESHOLD) {
    triggerAlert("High Humidity!");
  }
  if (pressure < LOW_PRES_THRESHOLD || pressure > HIGH_PRES_THRESHOLD) {
    triggerAlert("Pressure Alert!");
  }
}

void triggerAlert(String message) {
  isAlertActive = true;
  while (isAlertActive) {
    ringTone();
    lcd.clear();
    lcd.print("Alert: ");
    lcd.print(message);
    delay(1500);
    displayMainData();  //display main data during alert.
    delay(2000);
  }
}

void stopAllAlerts() {
  noTone(buzzer1);
  noTone(buzzer2);
  noTone(buzzer3);
  isAlertActive = false;
}

void logData() {
  if (currentDay < 7) {
    dayData[currentDay][0] = temperature;  // Store average temperature
    dayData[currentDay][1] = humidity;     // Store average humidity
    currentDay++;
  } else {
    // Shift data to overwrite oldest day
    for (int i = 0; i < 6; i++) {
      dayData[i][0] = dayData[i + 1][0];
      dayData[i][1] = dayData[i + 1][1];
    }

    dayData[6][0] = temperature;
    dayData[6][1] = humidity;
  }

  // Write data to SD card
  dataFile = SD.open("data.txt", FILE_WRITE);  //Opens (or creates) a file named "data.txt" on the SD card for writing.

  if (dataFile) {  // Checks if the file was successfully opened.
    for (int i = 0; i < 7; i++) {
      dataFile.print(dayOfWeek[i]);
      dataFile.print(i + 1);
      dataFile.print(": Temp=");
      dataFile.print(dayData[i][0]);
      dataFile.print("C, Hum=");
      dataFile.print(dayData[i][1]);
      dataFile.println("%");
    }
    dataFile.close();
  } else {
    Serial.println("Error writing to data.txt");
    lcd.clear();
    lcd.print("SD Write Error!");
    delay(2000);
  }
}

// Function to calculate daily averages (call this once per day)
void calculateDailyAverage() {
  // This function would normally calculate the average
  // temperature and humidity for the day. For simplicity,
  // we'll just use the current readings.
  logData();
}

// Function to simulate a new day (replace with actual time-based trigger)
void simulateNewDay() {
  // Call calculateDailyAverage once per day
  calculateDailyAverage();
}

// Function to handle time-based events (using RTC)
void handleTimeEvents() {
  DateTime now = rtc.now();

  // Simulating a new day at midnight (replace with actual logic)
  if (now.hour() == 0 && now.minute() == 0 && now.second() == 0) {
    simulateNewDay();
    delay(1000);  // To prevent multiple calls in the same second
  }
}

void ringTone() {
  playTone(BUZZER1, 523, 300); // C5
  playTone(BUZZER2, 523, 300); // C5
  playTone(BUZZER1, 523, 300); // C5
  playTone(BUZZER3, 415, 1000); // G#4
  delay(500);

  playTone(BUZZER1, 523, 300); // C5
  playTone(BUZZER2, 523, 300); // C5
  playTone(BUZZER1, 523, 300); // C5
  playTone(BUZZER3, 392, 1000); // G4
  delay(1000);
}

void playTone(int buzzerPin, int frequency, int duration) {
  tone(buzzerPin, frequency, duration);
  delay(duration);
  noTone(buzzerPin);
}