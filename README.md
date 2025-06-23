# Sisteme cu Microprocesoare (SMP) - Montaj de tip interfon

Acest proiect este reprezentat de un sistem de interfon bazat pe un microcontroller Arduino, care permite autentificarea unui utilizator printr-o tastatură matriceală și un sistem RFID (Radio Frequency Identification).

---

## Funcționalități

- **Autentificare prin RFID:** Utilizatorii pot deschide sistemul printr-o cartelă de acces sau un tag.
- **Tastatură de Securitate:** O tastatură matriceală permite introducerea unui cod de acces, iar un buzzer semnalează validitatea acestuia.
- **Feedback Vizual și Auditiv:** LED-urile semnalează statusul sistemului (verde pentru permis și albastru pentru respins), iar buzzer-ul emite un semnal sonor corespunzător.
- **Monitorizare prin PIR:** Senzorul PIR detectează mișcarea în apropierea interfonului, activând sau dezactivând sistemul.

---

## Tehnologii și Componente Hardware

- **Arduino Plusivo:** Microcontroller-ul central, controlează toate componentele.
- **Tastatură Matriceală 4×4:** Permite introducerea codului numeric.
- **Modul RFID RC522:** Cititor de taguri RFID (13.56 MHz).
- **Buzzer:** Emite sunete pentru feedback.
- **LED-uri (Verde și Albastru):** Indică acces permis sau respins.
- **Rezistențe de 220Ω:** Protejează LED-urile.
- **Senzor PIR HW416:** Detectează mișcare în fața interfonului.
- **Breadboard:** Asamblare temporară a circuitului.

---

## Schema Electrică

Conexiuni esențiale:

- **Tastatură → Arduino:** 8 pini digitali
- **RFID RC522 → Arduino:**
  - SDA → D10
  - SCK → D13
  - MOSI → D11
  - MISO → D12
  - RST → D9
- **LED-uri + Rezistențe → Arduino:** D3 (verde), D4 (albastru)
- **Buzzer → Arduino:** D5
- **PIR → Arduino:** Un pin digital

**Alimentare:** Prin portul USB al Arduino-ului.

---

## Instalare și Rulare

### Cerințe:

- Arduino IDE instalat
- Bibliotecile:
  - `MFRC522`
  - `Keypad`
  - `Adafruit BusIO`
  - `Adafruit LiquidCrystal`
  - `LiquidCrystal I2C`
  - `Adafruit MCP23017`
