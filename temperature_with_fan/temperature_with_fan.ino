#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN A3     // Pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

#define MOTOR_PIN 7   // Pin connected to the DC motor, changed to pin 7

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor
LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize LCD

void setup() {
  Serial.begin(9600);
  Serial.println("Temperature Sensor Test");

  dht.begin();
  lcd.init();
  lcd.backlight();
  
  pinMode(MOTOR_PIN, OUTPUT); // Set the motor pin as an output
}

void loop() {
  float temperature = dht.readTemperature(); // Read temperature

  if (isnan(temperature)) { // Check if reading is valid
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.print(" C");

  if (temperature > 25) {
    digitalWrite(MOTOR_PIN, HIGH); // Turn on the motor if temperature is above 25°C
  } else {
    digitalWrite(MOTOR_PIN, LOW); // Turn off the motor if temperature is not above 25°C
  }

  delay(1000);
}
