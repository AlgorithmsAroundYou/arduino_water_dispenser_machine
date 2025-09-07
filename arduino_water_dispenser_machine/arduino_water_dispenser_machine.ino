// Pin Definitions
const int IR_PIN = 2;     // Digital pin connected to the IR sensor module's output
const int RELAY_PIN = 12; // Digital pin connected to the relay module's input

// Variables
bool objectDetected = false; // To track the state of the object detection

void setup() {
  // Initialize the IR sensor pin as an input
  pinMode(IR_PIN, INPUT);

  // Initialize the relay pin as an output
  pinMode(RELAY_PIN, OUTPUT);
  // Initially turn off the relay (HIGH for most relay modules means off)
  digitalWrite(RELAY_PIN, HIGH);

  // Optional: Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the state of the IR sensor
  // A HIGH signal often indicates an object is detected (depending on the IR module)
  if (digitalRead(IR_PIN) == HIGH) {
    // If an object is detected and it's the first time (not already marked as detected)
    if (!objectDetected) {
      objectDetected = true; // Mark as detected
      Serial.println("Object Detected! Dispensing...");
      activateDispenser();  // Call the function to activate the dispenser
    }
  } else {
    // If the object is no longer detected
    if (objectDetected) {
      objectDetected = false; // Reset the detection flag
      Serial.println("Object removed.");
      // You might want to add a timer here to turn off the pump after some time
    }
  }
}

void activateDispenser() {
  // Turn on the relay to power the motor/pump
  digitalWrite(RELAY_PIN, LOW); // LOW usually turns ON the relay module
  Serial.println("Dispensing in progress...");

  // Keep the dispenser on for a specific duration (e.g., 2 seconds)
  delay(2000); // Adjust this delay as needed

  // Turn off the relay to stop the motor/pump
  digitalWrite(RELAY_PIN, HIGH); // Turn off the relay
  Serial.println("Dispensing complete.");
}