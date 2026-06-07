#include <LiquidCrystal.h>

// LCD: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define SENSOR_PIN     A0
#define MAINS_VOLTAGE  220.0
#define SENSITIVITY    0.185
#define VREF           5.0
#define ADC_RESOLUTION 1023.0
#define SAMPLES        500

float currentRMS = 0.0;
float powerWatts = 0.0;
float energyWh   = 0.0;
unsigned long lastTime = 0;

float readCurrentRMS() {
  float sumSquares = 0.0;
  float midpoint   = 512.0;

  for (int i = 0; i < SAMPLES; i++) {
    int raw = analogRead(SENSOR_PIN);
    float voltage = (raw - midpoint) * (VREF / ADC_RESOLUTION);
    float current = voltage / SENSITIVITY;
    sumSquares += current * current;
    delayMicroseconds(200);
  }
  return sqrt(sumSquares / SAMPLES);
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Energy Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Initialising...");
  delay(1500);
  lcd.clear();

  lastTime = millis();

  Serial.println("Time(s) | Current(A) | Power(W) | Energy(Wh)");
  Serial.println("--------|------------|----------|----------");
}

void loop() {
  currentRMS = readCurrentRMS();
  powerWatts = currentRMS * MAINS_VOLTAGE;

  unsigned long now = millis();
  float hoursElapsed = (now - lastTime) / 3600000.0;
  energyWh += powerWatts * hoursElapsed;
  lastTime = now;

  lcd.setCursor(0, 0);
  lcd.print("I:");
  lcd.print(currentRMS, 2);
  lcd.print("A P:");
  lcd.print(powerWatts, 1);
  lcd.print("W  ");

  lcd.setCursor(0, 1);
  lcd.print("Energy:");
  lcd.print(energyWh, 4);
  lcd.print("Wh  ");

  Serial.print(now / 1000);
  Serial.print("s\t| ");
  Serial.print(currentRMS, 3);
  Serial.print(" A\t| ");
  Serial.print(powerWatts, 2);
  Serial.print(" W\t| ");
  Serial.print(energyWh, 5);
  Serial.println(" Wh");

  delay(1000);
}
