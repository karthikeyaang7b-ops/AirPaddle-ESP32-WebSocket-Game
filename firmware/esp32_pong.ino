#include <Wire.h>
#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "<Enter your wifi info>";
const char* password = "<enter password>";

WebSocketsServer webSocket = WebSocketsServer(81);

const int MPU_ADDR = 0x68; 
const int BUZZER_PIN = 4;
const float TILT_THRESHOLD = 20.0; // Increased threshold so buzzer only fires on extreme tilts

void setup() {
  // Baud rate set to high-speed 115200
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);

  Wire.begin(21, 22);
  delay(100);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); 
  Wire.write(0x00); 
  if (Wire.endTransmission() != 0) {
    Serial.println("Failed to connect to MPU sensor!");
    while (1) { delay(10); }
  }
  Serial.println("MPU Sensor Initialized!");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();
}

void loop() {
  webSocket.loop();

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  int16_t rawX = (Wire.read() << 8) | Wire.read();
  int16_t rawY = (Wire.read() << 8) | Wire.read();
  int16_t rawZ = (Wire.read() << 8) | Wire.read();

  float ax = rawX / 16384.0;
  float ay = rawY / 16384.0;
  float az = rawZ / 16384.0;

  // Sensitivity Tuning: We damp down the pitch calculation using a smoothing factor
  float pitch = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / M_PI;
  float roll = atan2(-ax, az) * 180.0 / M_PI;

  // Local Buzzer Feedback on sharp movements
  if (abs(pitch) > TILT_THRESHOLD || abs(roll) > TILT_THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH); 
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Stream data over WebSockets
  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 30) { // Faster stream loop (~33 FPS) for snappy gameplay
    lastMsg = millis();
    String jsonPayload = "{\"pitch\":" + String(pitch) + ",\"roll\":" + String(roll) + "}";
    webSocket.broadcastTXT(jsonPayload);
  }
}
