#include <LiquidCrystal.h>

// Initialize the LiquidCrystal library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Adjust pins as needed

// Pin assignments
int buzzerPin = 10;      // Buzzer pin
int tempPin = A0;        // TMP36 temperature sensor pin
int gasPin = A1;         // Analog gas sensor pin (connected to A1)

// RGB LED pins
int redPin = 6;          // Red LED pin
int greenPin = 5;        // Green LED pin
int bluePin = 9;         // Blue LED pin

// Threshold values
float tempThreshold = 50.0;  // Celsius threshold for fire detection
int gasThreshold = 300;       // Adjust this value based on your testing

// Setup function
void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);  // Set up the LCD's number of columns and rows
  lcd.print("Initializing..."); // Initial message

  // Set RGB LED pins as OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Set buzzer pin as OUTPUT
  pinMode(buzzerPin, OUTPUT);
  
  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Reading temperature from TMP36
  float tempValue = analogRead(tempPin); 
  tempValue = (tempValue * (5.0 / 1023.0) - 0.5) * 100.0; // Convert to Celsius

  // Reading gas level from MQ-6 gas sensor
  int gasValue = analogRead(gasPin); // Read the analog value from the gas sensor

  // Display readings on LCD
  lcd.clear(); // Clear the LCD for fresh output
  lcd.setCursor(0, 0); // Set cursor to the first line
  lcd.print("Temp: ");
  lcd.print(tempValue);
  lcd.print(" C");

  lcd.setCursor(0, 1); // Set cursor to the second line
  lcd.print("Gas: ");
  lcd.print(gasValue);  // Display gas sensor value

  // Print sensor readings to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(tempValue);
  Serial.print(" °C, Gas Level: ");
  Serial.println(gasValue);

  // Check if temperature exceeds threshold
  if (tempValue > tempThreshold || gasValue < 630) {
    // Activate alarm (buzzer and RGB LED)
    digitalWrite(buzzerPin, HIGH);
    
    // Turn on RGB LED to red
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    
    // Print alarm status on Serial Monitor
    Serial.println("ALERT! FIRE or GAS DETECTED!");
    lcd.setCursor(0, 1); // Set cursor to the second line
    lcd.print("ALERT! FIRE/GAS!");
  } else {
    // Turn off alarm
    digitalWrite(buzzerPin, LOW);
    
    // Turn off RGB LED
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    
    // Clear alert message
    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear line
  }
  
  delay(1000);  // Update every second
}