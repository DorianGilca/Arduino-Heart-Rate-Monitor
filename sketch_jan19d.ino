#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MAX30100_PulseOximeter.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
PulseOximeter pox;

#define REPORTING_PERIOD_MS 1000
uint32_t lastReportTime = 0;

void onBeatDetected() {
    Serial.println("Beat detected!");
}

void setup() {
    Serial.begin(115200);
    Serial.println("Test MAX30100...");

    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Init Puls...");

    if (!pox.begin()) {
        Serial.println("Eroare MAX30100! Verifica conexiunile.");
        lcd.setCursor(0, 1);
        lcd.print("Eroare senzor!");
        while (1); 
    } else {
        Serial.println("MAX30100 OK!");
    }

    pox.setOnBeatDetectedCallback(onBeatDetected);
    pox.setIRLedCurrent(MAX30100_LED_CURR_24MA); 

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Puls: -- BPM");
}

void loop() {
    pox.update();

    if (millis() - lastReportTime > REPORTING_PERIOD_MS) {
        float bpm = pox.getHeartRate();

        lcd.setCursor(0, 0);
        lcd.print("Puls: ");
        lcd.setCursor(6, 0);
        
        if (bpm > 0) {
            lcd.print("     "); 
            lcd.setCursor(6, 0);
            lcd.print(bpm);
            
            Serial.print("Puls: "); 
            Serial.print(bpm); 
            Serial.println(" BPM");
        } else {
            lcd.print("--");
            Serial.println("Nu s-a detectat puls.");
        }

        lastReportTime = millis();
    }
}