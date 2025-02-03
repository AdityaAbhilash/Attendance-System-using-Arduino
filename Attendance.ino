#include <SPI.h>
#include <MFRC522.h>
#include <TimeLib.h>  // Include this for time functions
 #include <Wire.h>   
 #include <LiquidCrystal_I2C.h>  

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER 2 //buzzer pin 
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int readsuccess;
byte readcard[4];
char str[32] = "";
String StrUID;
unsigned long lastScanTime = 0; // Store the last scan time
unsigned long elapsedTime = 0;   // Store elapsed time

void setup() {
  Serial.begin(9600);         // Initialize serial communications with the PC
  SPI.begin();                // Init SPI bus
  mfrc522.PCD_Init();         // Init MFRC522 card

  Serial.println("CLEARDATA");
  Serial.println("LABEL,Date,Time Elapsed,UID,Name,Branch,Roll Number");
  delay(1000);
  
  Serial.println("Scan PICC to see UID...");
  Serial.println("");

  lcd.init();   // lcd.init();
  lcd.backlight(); // Turn on the blacklight and print a message.   

  // Set the time manually
  setTime(0, 0, 0, 28, 11, 2024); // Set to 2:30 PM, 4th Nov 2024

  pinMode(BUZZER, OUTPUT);  
  noTone(BUZZER);
}

void loop() {
  RTC();
  readsuccess = getid();
 
  if (readsuccess) {
    String name, branch, rollNumber;
    elapsedTime = millis() - lastScanTime; // Calculate elapsed time since last scan
    lastScanTime = millis(); // Update last scan time

    if (identifyCard(StrUID, name, branch, rollNumber)) {
      // Get current date and time
      String currentDate = String(day()) + "/" + String(month()) + "/" + String(year());
      String currentTime = String(hour()) + ":" + String(minute()) + ":" + String(second());

      // Print elapsed time to serial
      Serial.print("Elapsed Time: ");
      Serial.print((elapsedTime / 3600000)); // hours
      Serial.print("h ");
      Serial.print((elapsedTime / 60000) % 60); // minutes
      Serial.print("m ");
      Serial.print((elapsedTime / 1000) % 60); // seconds
      Serial.println("s");

      // Print data in CSV format for Excel
      Serial.print("DATA,");
      Serial.print(currentDate);  // Date from internal clock
      Serial.print(",");
      Serial.print("\""); // Start quoting the time string
      Serial.print(currentTime);   // Time from internal clock
      Serial.print("\""); // End quoting the time string
      Serial.print(",");
      Serial.print(StrUID);        // UID of the scanned card
      Serial.print(",");
      Serial.print(name);          // Name from identification
      Serial.print(",");
      Serial.print(branch);        // Branch from identification
      Serial.print(",");
      Serial.println(rollNumber);  // Roll number from identification
    }
  }
}

// --------------------------------------------------------------------
int getid() {  
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }
 
  Serial.println("THE UID OF THE SCANNED CARD IS:");
  
  for (int i = 0; i < 4; i++) {
    readcard[i] = mfrc522.uid.uidByte[i];  // Store the UID of the tag in readcard
  }
  
  array_to_string(readcard, 4, str);
  StrUID = str;
  
  mfrc522.PICC_HaltA();  // Halt PICC
  return 1;
}

// --------------------------------------------------------------------
void array_to_string(byte array[], unsigned int len, char buffer[]) {
    for (unsigned int i = 0; i < len; i++) {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i * 2 + 0] = nib1 < 0xA ? '0' + nib1 : 'A' + nib1 - 0xA;
        buffer[i * 2 + 1] = nib2 < 0xA ? '0' + nib2 : 'A' + nib2 - 0xA;
    }
    buffer[len * 2] = '\0';
}

// --------------------------------------------------------------------
// Function to identify card and return associated details
bool identifyCard(String uid, String &name, String &branch, String &rollNumber) {
    if (uid == "E73FE54D") {   // Example UID - replace with actual UID
        tone(BUZZER, 500);  
        delay(500);  
        noTone(BUZZER);
        lcd.clear();
        lcd.setCursor(7, 0);
        lcd.print("Aditya    ");
        lcd.setCursor(7, 1);
        lcd.print("22EC01059");
        info();  
        name = "Aditya Abhilash";
        branch = "ECE";
        rollNumber = "22EC01059";
        return true;

    }
    else if (uid == "B90FA26E") {  // Another example UID
        tone(BUZZER, 500);  
        delay(500);  
        noTone(BUZZER);  
        lcd.clear();
        lcd.setCursor(7, 0);
        lcd.print("Atharva    ");
        lcd.setCursor(7, 1);
        lcd.print("22EC01003");
        info();  
        name = "Atharva Tol";
        branch = "ECE";
        rollNumber = "22EC01003";
        return true;
    }
    // Add more cards as needed
    else {
        tone(BUZZER, 500);  
        delay(500);  
        noTone(BUZZER);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ID : ");
        lcd.print("Unknown");
        lcd.setCursor(0, 1);
        lcd.print("Access denied");
        delay(1000);
        lcd.clear();  
        Serial.println("Unknown Card");
        return false;
    }
}

void RTC()
{
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014
  
  lcd.setCursor(0, 0);
  lcd.print("Put Your Card to" );
  lcd.setCursor(0, 1);
  lcd.print("the Reader  ");
  /* delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    lcd.print(rtc.getTimeStr());
    lcd.setCursor(0, 1);
    lcd.print("Date: ");
    lcd.print(rtc.getDateStr());
    delay(500);
    lcd.clear(); */
}

void info()
{
  lcd.setCursor(0, 0);
  lcd.print("Name : ");
  lcd.setCursor(0, 1);
  lcd.print("ID   : ");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Authorized Access");
  delay(1000);
  lcd.clear();
}
