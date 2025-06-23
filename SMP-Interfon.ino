#include <Keypad.h>    // Include biblioteca Keypad pentru interacțiunea cu tastatura matricială
#include <SPI.h>       // Include biblioteca SPI pentru comunicarea cu modulul RFID
#include <MFRC522.h>   // Include biblioteca MFRC522 pentru modulul RFID

// Configurare pini RFID
#define RST_PIN 7      // Pin de reset
#define SS_PIN 10      // Pin de selecție (SDA)

MFRC522 mfrc522(SS_PIN, RST_PIN); // Instanță RFID

// Configurare tastatură matricială
const byte ROWS = 4;   // Numărul de rânduri
const byte COLS = 4;   // Numărul de coloane

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {14, 15, 16, 17}; // Rânduri pe pinii A0-A3
byte colPins[COLS] = {2, 6, 8, 7};    // Coloane pe pinii D2, D6, D8, D7

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Configurare LED-uri și buzzer
const int greenLed = 3;  // LED verde (Acces permis)
const int blueLed = 4;   // LED albastru (Acces respins)
const int buzzerPin = 5; // Buzzer

// Cod presetat pentru tastatură
const String correctCode = "1234";
String enteredCode = ""; // Cod introdus de utilizator

// Carduri autorizate (UID-uri)
byte authorizedCard1[] = {0x03, 0x9F, 0x94, 0x9A}; // Exemplu UID card autorizat

void setup() {
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

    // Inițializare RFID
    SPI.begin();
    mfrc522.PCD_Init();

    // Inițializare Serial Monitor
    Serial.begin(9600);
    Serial.println("Sistem de acces activat! Așteaptă card sau cod...");
}

void loop() {
    // Citire card RFID
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        tone(buzzerPin, 1000, 200); // Sunet scurt la detectarea unui card

        Serial.print("Card detectat: ");
        for (byte i = 0; i < mfrc522.uid.size; i++) {
            Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
            Serial.print(mfrc522.uid.uidByte[i], HEX);
        }
        Serial.println();

        // Verifică dacă cardul este autorizat
        if (isAuthorizedCard(mfrc522.uid.uidByte, authorizedCard1)) {
            Serial.println("Card autorizat! Acces permis.");
            digitalWrite(greenLed, HIGH); // Aprinde LED verde
            delay(3000); // Menține LED-ul aprins 3 secunde
            digitalWrite(greenLed, LOW);
        } else {
            Serial.println("Card neautorizat! Acces respins.");
            digitalWrite(blueLed, HIGH); // Aprinde LED albastru
            delay(3000); // Menține LED-ul aprins 3 secunde
            digitalWrite(blueLed, LOW);
        }

        // Termină comunicarea cu cardul
        mfrc522.PICC_HaltA();
    }

    // Citire tastatură
    char key = keypad.getKey(); // Citește tasta apăsată

    if (key) {
        tone(buzzerPin, 1000, 200); // Sunet scurt la apăsare
        Serial.print("Tasta apăsată: ");
        Serial.println(key);

        if (key == '#') { // Verifică codul introdus când se apasă '#'
            Serial.print("Cod introdus: ");
            Serial.println(enteredCode);

            if (enteredCode == correctCode) {
                Serial.println("Cod corect! Acces permis.");
                digitalWrite(greenLed, HIGH); // Aprinde LED verde
                delay(3000); // Menține LED-ul aprins 3 secunde
                digitalWrite(greenLed, LOW);
            } else {
                Serial.println("Cod greșit! Acces respins.");
                digitalWrite(blueLed, HIGH); // Aprinde LED albastru
                delay(3000); // Menține LED-ul aprins 3 secunde
                digitalWrite(blueLed, LOW);
            }
            enteredCode = ""; // Resetează codul introdus
        } else if (key == '*') {
            Serial.println("Cod resetat.");
            enteredCode = "";
        } else {
            enteredCode += key; // Adaugă tasta apăsată la codul introdus
        }
    }
}

// Funcție pentru verificarea UID-ului cardului
bool isAuthorizedCard(byte *uid, byte *authorizedCard) {
    for (byte i = 0; i < 4; i++) { // Compară fiecare octet din UID
        if (uid[i] != authorizedCard[i]) {
            return false; // Dacă un octet nu se potrivește, cardul nu este autorizat
        }
    }
    return true; // Toți octeții se potrivesc -> card autorizat
}