// Pin Definitions
#define PIR_PIN 4
#define BUZZER_PIN 3
#define BULB_PIN 2
#define GAS_SENSOR A1
#define THERMISTOR_PIN A0
#define ULTRA_PIN 6 
#define MOTOR_PIN 5

// Constants
#define GAS_THRESHOLD 400
#define TEMP_THRESHOLD 35.0 // Celsius
#define WATER_LEVEL_THRESHOLD 15 // cm

// Thermistor constants
const float SERIES_RESISTOR = 10000;
const float THERMISTOR_NOMINAL = 10000;
const float TEMPERATURE_NOMINAL = 25;
const float B_COEFFICIENT = 3950;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BULB_PIN, OUTPUT);
  pinMode(ULTRA_PIN, OUTPUT); // will switch to INPUT for reading
  pinMode(MOTOR_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(BULB_PIN, LOW);
  digitalWrite(MOTOR_PIN, LOW);

  Serial.begin(9600);
}

void loop() {
  // --- Motion Detection ---
  if (digitalRead(PIR_PIN) == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(BULB_PIN, HIGH);
    delay(1000);
  } else {
    digitalWrite(BULB_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // --- Gas Detection ---
  int gasValue = analogRead(GAS_SENSOR);
  Serial.print("Gas Level: ");
  Serial.println(gasValue);
  if (gasValue > GAS_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);
  }

  // --- Temperature Detection (Thermistor) ---
  int analogValue = analogRead(THERMISTOR_PIN);
  float resistance = SERIES_RESISTOR / ((1023.0 / analogValue) - 1);
  float steinhart = resistance / THERMISTOR_NOMINAL;
  steinhart = log(steinhart);
  steinhart /= B_COEFFICIENT;
  steinhart += 1.0 / (TEMPERATURE_NOMINAL + 273.15);
  steinhart = 1.0 / steinhart;
  float tempC = steinhart - 273.15;
  Serial.print("Temperature: ");
  Serial.println(tempC);

  if (tempC > TEMP_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);
  }

  // --- Water Level Detection using 3-pin Ultrasonic ---
  float distance = getUltrasonicDistance();
  Serial.print("Water Level (cm): ");
  Serial.println(distance);

  if (distance > WATER_LEVEL_THRESHOLD) {
    digitalWrite(MOTOR_PIN, HIGH); // Low level: turn on motor
  } else {
    digitalWrite(MOTOR_PIN, LOW);  // Enough water: motor off
  }

  delay(1000);
}

// --- Function to read from 3-pin ultrasonic sensor ---
float getUltrasonicDistance() {
  pinMode(ULTRA_PIN, OUTPUT);
  digitalWrite(ULTRA_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_PIN, LOW);

  pinMode(ULTRA_PIN, INPUT);
  long duration = pulseIn(ULTRA_PIN, HIGH, 30000); // Timeout after 30ms

  float distance = duration * 0.034 / 2;
  return distance;
}