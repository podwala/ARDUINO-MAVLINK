/*
  Arduino MAVLink Mode LED Indicator
  ----------------------------------
  Author: Your Name
  Purpose: Reads MAVLink serial data and changes RGB LED color based on flight mode.

  Hardware:
  - Arduino Uno
  - MAVLink Flight Controller (TELEM TX → Arduino RX)
  - Common Cathode RGB LEDs on pins 9, 10, 11
*/

#define R_PIN 9
#define G_PIN 10
#define B_PIN 11

void setColor(int r, int g, int b) {
  analogWrite(R_PIN, r);
  analogWrite(G_PIN, g);
  analogWrite(B_PIN, b);
}

enum State { WAIT_HEADER, READ_FRAME };
State state = WAIT_HEADER;

uint8_t buf[40];
int idx = 0;
int expected_len = 0;

void setup() {
  Serial.begin(57600);

  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);

  setColor(80, 0, 80);  // Startup indicator (purple)
}

void loop() {

  while (Serial.available()) {

    uint8_t c = Serial.read();

    if (state == WAIT_HEADER) {
      if (c == 0xFE) {   // MAVLink v1 header
        buf[0] = c;
        idx = 1;
        state = READ_FRAME;
      }
    }

    else if (state == READ_FRAME) {

      buf[idx++] = c;

      if (idx == 2) {
        // Payload length byte
        uint8_t len = buf[1];
        expected_len = len + 8;  
        // Header(6) + Payload + CRC(2)
      }

      if (idx >= expected_len) {
        parseFrame(buf);
        state = WAIT_HEADER;
        idx = 0;
      }
    }
  }
}

void parseFrame(uint8_t *f) {

  // Flight mode byte (custom_mode low byte for most FCs)
  uint8_t mode = f[6];

  switch (mode) {

    case 0x00:   // Stabilize
      setColor(0, 255, 0);     // Green
      break;

    case 0x02:   // AltHold
      setColor(0, 0, 255);     // Blue
      break;

    case 0x06:   // Loiter / GPS Hold
      setColor(0, 255, 255);   // Cyan
      break;

    default:
      setColor(255, 255, 255); // Unknown mode → White
      break;
  }
}
