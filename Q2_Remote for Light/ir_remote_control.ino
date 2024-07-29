#include <IRremote.hpp>

// Define pins
#define IR_RECEIVE_PIN 6  // IR sensor connected to pin 6
#define BULB_PIN 11       // Bulb connected to pin 11


// Global variable to store the bulb state
bool bulbOn = false;

void setup() {
  Serial.begin(9600);
  Serial.println("IR Remote Control Setup"); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); 
  pinMode(BULB_PIN, OUTPUT); 
  digitalWrite(BULB_PIN, LOW); 
  Serial.println("Setup complete."); 
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Received IR code: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); 
    Serial.print("IR Data: ");
    IrReceiver.printIRResultShort(&Serial); 
    Serial.print("IR Send Code: ");
    IrReceiver.printIRSendUsage(&Serial);   

    // Check for specific IR commands
    switch (IrReceiver.decodedIRData.decodedRawData) {
      case 0xFD00FF: // Power (Assuming this is your power button code)
        bulbOn = !bulbOn; 
        digitalWrite(BULB_PIN, bulbOn ? HIGH : LOW); 
        Serial.print("Bulb is now ");
        Serial.println(bulbOn ? "ON" : "OFF"); 
        break;
      case 0xFF00BF00: // Power button code (NEC protocol, Address: 0xBF00, Command: 0x00)
        bulbOn = !bulbOn; // Toggle the bulb state
        digitalWrite(BULB_PIN, bulbOn ? HIGH : LOW); // Turn on/off the bulb
        Serial.print("Bulb is now ");
        Serial.println(bulbOn ? "ON" : "OFF"); // Print the bulb state
        break;
      // Add more cases for other remote commands if needed
    }

    IrReceiver.resume(); 
  }
}