// Voltage sensor variables
int adc_max1 = 2700;               // Adjusted maximum ADC value for ESP32
int adc_min1 = 1500;               // Adjusted minimum ADC value for ESP32
float volt_multi = 231;            // Nominal AC RMS voltage for scaling
float volt_multi_p;                // Positive peak voltage multiplier
float volt_multi_n;                // Negative peak voltage multiplier
float volt_rms1 = 0;
int Voltage_Sensor_1 = 35;         // Use GPIO 35 on ESP32 for voltage sensor

// Current sensor variables
int Current_Sensor_Pin = 34;       // Use GPIO 34 on ESP32 for current sensor
float current = 0;

// LED setup
int LED_Pin = 2;                   // Use GPIO 2 for LED output (change if needed)
float voltage_threshold = 240.0;   // Voltage threshold in VAC
float current_threshold = 6.0;     // Current threshold in Amps

void setup() {
  Serial.begin(115200);
  
  // Voltage sensor setup
  pinMode(Voltage_Sensor_1, INPUT);       // Set voltage sensor pin as input
  volt_multi_p = volt_multi * 1.4142;     // Calculate positive peak multiplier
  volt_multi_n = -volt_multi_p;           // Calculate negative peak multiplier

  // Current sensor setup
  pinMode(Current_Sensor_Pin, INPUT);     // Set current sensor pin as input
  
  // LED setup
  pinMode(LED_Pin, OUTPUT);               // Set LED pin as output
  digitalWrite(LED_Pin, LOW);             // Start with LED off
}

void loop() {
  // Read and calculate RMS voltage
  volt_rms1 = get_voltage(Voltage_Sensor_1, adc_min1, adc_max1);
  Serial.print("Vrms: ");
  Serial.print(volt_rms1 - 253);          // Adjust for nominal value
  Serial.println(" VAC");

  // Read and calculate current from ACS712 sensor
  current = get_current(Current_Sensor_Pin);
  Serial.print("Current: ");
  Serial.print(current + 16, 3);          // Adjusted for offset
  Serial.println(" A");

  // Check if voltage or current threshold is crossed
  if ((volt_rms1 >= voltage_threshold) || (current >= current_threshold)) {
    digitalWrite(LED_Pin, HIGH);          // Turn on LED
  } else {
    digitalWrite(LED_Pin, LOW);           // Turn off LED
  }

  delay(300);  // Delay for stability
}

// Function to calculate RMS voltage
float get_voltage(int pin, int adc_min, int adc_max) {
  float adc_sample;
  float volt_inst = 0;
  float sum = 0;
  float volt;
  long init_time = millis();
  int N = 0;

  while ((millis() - init_time) < 100) {   
    adc_sample = analogRead(pin);           
    // Map ADC value from adc_min to adc_max to volt_multi_n and volt_multi_p range
    volt_inst = map(adc_sample, adc_min, adc_max, volt_multi_n * 100, volt_multi_p * 100) / 100.0; 
    sum += sq(volt_inst);                   
    N++;
    delay(1);
  }
  volt = sqrt(sum / N); // Calculate RMS voltage
  return volt;
}

// Function to calculate current based on ACS712 sensor
float get_current(int pin) {
  int adc = analogRead(pin);               // Read analog value from current sensor
  float voltage = adc * (3.3 / 4095.0);    // Convert ADC value to voltage (ESP32 uses 3.3V reference)

  // Calculate current (assuming 2.5V zero current and 0.1V per amp sensitivity for ACS712-20A model)
  float current = (voltage - 2.5) / 0.1;

  // Apply threshold to ignore small noise
  if (abs(current) < 0.16) {
    current = 0;
  }
  return current;
}
