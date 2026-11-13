// CCNY Phys 371 - Lab 5: Low-Pass Filter Data Acquisition

// Hardware Pins
const int PWM_TONE_PIN = 7;     // Digital PWM pin (~ Pin 3) connected to resistor
const int ANALOG_IN_PIN = A2;   // Analog pin A0 reading capacitor voltage

// Frequency Setting (Hz)
// Change this value for each trial (e.g., 10, 20, 40, 60, 80, 100, 200, 500 Hz)
const unsigned int TEST_FREQUENCY = 60; 

// Sampling Interval (1000 microseconds = 1 ms sampling rate)
const unsigned long SAMPLE_INTERVAL_US = 1000;
unsigned long lastSampleTime = 0;

void setup() {
  Serial.begin(115200);
  
  // Print CSV header for Python / Colab dataframe import
  Serial.println("Time_ms,ADC_Reading,Voltage_V");
  
  // Start square wave generation on Pin 3
  tone(PWM_TONE_PIN, TEST_FREQUENCY);
}

void loop() {
  unsigned long currentMicros = micros();
  
  // Enforce precise 1 ms sampling rate
  if (currentMicros - lastSampleTime >= SAMPLE_INTERVAL_US) {
    lastSampleTime += SAMPLE_INTERVAL_US;
    
    int rawADC = analogRead(ANALOG_IN_PIN);
    float voltage = rawADC * (5.0 / 1023.0);
    float timeMs = currentMicros / 1000.0;
    
    // Print formatted 3-column CSV row
    Serial.print(timeMs, 2);
    Serial.print(",");
    Serial.print(rawADC);
    Serial.print(",");
    Serial.println(voltage, 3);
  }
}