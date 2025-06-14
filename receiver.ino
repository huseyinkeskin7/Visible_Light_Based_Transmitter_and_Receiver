#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize a LiquidCrystal object with the address 0x27 and size 16x2

const int ldrPin = 2; // Define the pin number for the LDR (Light Dependent Resistor)
volatile unsigned long lastChangeTime = 0; // Keep track of the last change in time
volatile bool ldrState = LOW; // Store the state of the LDR
volatile int bitCount = 0; // Counter for the received bits
unsigned long bitPeriod = 0; // Duration of a received bit
unsigned long eskizaman = 0; // Variable to store previous time
bool startread = 0; // Flag to indicate the start of reading data
bool periodsetted = 0; // Flag to indicate if the period has been set
char matrix[8]; // Array to hold received bits temporarily
int satir = 0; // Counter for LCD row position

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  pinMode(ldrPin, INPUT); // Set LDR pin as input
  attachInterrupt(digitalPinToInterrupt(ldrPin), ldrInterrupt, CHANGE); // Attach interrupt to the LDR pin change
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the LCD backlight
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0); // Set the cursor to the first position
  lcd.print("MESSAGE WAITING"); // Display "MESSAGE WAITING" on the LCD
}

char displayContent[16] = "                  ";

void loop() {
  if (periodsetted) {
    unsigned long zaman = millis(); // Get the current time in milliseconds
    
    if (digitalRead(ldrPin) == LOW) {
      if (zaman - eskizaman > 3000) {
        lcd.clear(); // Clear the LCD screen after 3 seconds of low signal from LDR
        satir = 0; // Reset the row counter for LCD
      }
      startread = !startread; // Toggle the startread flag
      eskizaman = zaman; // Update the previous time
    }

    while (startread) {
      byte karakter = 0;

      delay(bitPeriod); // Wait for the duration of a bit

      for (int i = 0; i <= 7; i++) {
        bool value = digitalRead(ldrPin); // Read the LDR pin value
        matrix[i] = value; // Store the received bit in the matrix array
        delay(bitPeriod - 12); // Wait for the remaining time of the bit period

        karakter = (karakter << 1) | matrix[i]; // Construct the character from received bits
      }

      Serial.print(char(karakter)); // Print the received character to Serial Monitor
      
      char newkarakter = char(karakter); // Store the received character in a new variable
      
      lcd.setCursor(satir, 1); // Set the cursor position on the LCD
      lcd.print(newkarakter); // Print the received character on the LCD
      lcd.setCursor(0, 0); // Set the cursor to the first position
      lcd.print("RECEIVED DATA"); // Display "RECEIVED DATA" on the LCD
      satir++; // Increment the row counter

      if (satir > 16) {
        lcd.scrollDisplayLeft(); // Scroll the LCD display to the left if the row exceeds 16
      }

      startread = !startread; // Toggle the startread flag to exit the while loop
    }
  }
}

void ldrInterrupt() {
  unsigned long currentTime = millis(); // Get the current time in milliseconds

  ldrState = digitalRead(ldrPin); // Read the state of the LDR pin

  if (ldrState == HIGH) {
    lastChangeTime = currentTime; // Update the time if LDR state is HIGH
  } else {
    bitCount++; // Increment the bit count for each LOW state

    if (bitCount == 4) {
      bitPeriod = (currentTime - lastChangeTime) / 1; // Calculate the duration of the received bit
      detachInterrupt(digitalPinToInterrupt(ldrPin)); // Detach the interrupt for LDR pin
      periodsetted = 1; // Set the flag to indicate the period has been set
      Serial.print("First 8 Bit Period : "); // Print message to Serial Monitor
      Serial.print(bitPeriod); // Print the duration of the received bit
      Serial.println(" ms"); // Print units to Serial Monitor
      bitCount = 0; // Reset the bit count
      delay(bitPeriod); // Wait for the duration of the received bit
    }
  }
}
