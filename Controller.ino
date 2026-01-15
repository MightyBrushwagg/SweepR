#include "ADXL362.h"
#include <SPI.h>
#include <Wire.h>
#include <L3G.h>
#include <math.h>
#include <WiFiS3.h>
#include <WiFiUdp.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <SPI.h>
#include <math.h>

// Define custom SPI pins for Arduino R4 (ESP32-S3)
#define SPI_MISO 13
#define SPI_MOSI 11
#define SPI_SCK 12
#define SPI_CS 10  // Chip Select (CS), change if needed

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
// Define screen properties
#define TEXT_HEIGHT 16
#define BOT_FIXED_AREA 0
#define TOP_FIXED_AREA 16
#define YMAX 320

#define BUTTON_PIN 4
#define DEBOUNCE_TIME 25

// Scrolling region
uint16_t yStart = TOP_FIXED_AREA;
uint16_t yArea = YMAX - TOP_FIXED_AREA - BOT_FIXED_AREA;
uint16_t yDraw = YMAX - BOT_FIXED_AREA - TEXT_HEIGHT;

uint16_t xPos = 0;  // X position tracker
byte data = 0;      // Serial byte input

int blank[19] = { 0 };  // Pre-allocate memory
int loopCount = 0;      // Counter to display something different every loop

// Accelerometer object
ADXL362 acc(SPI_CS);

// Gyroscope object
L3G gyro;

// Global variables for accelerometer readings
MeasurementInMg xyzlow;
MeasurementInMg xyz;
float temp;

// Global variables for gyroscope readings
float gyroX, gyroY, gyroZ;
float theta_g = 0;
float phi_g = 0;
float psi_g = 0;

// Replace with your network credentials
const char ssid[] = "eduino";
const char password[] = "password";

// body is 20, controller is 22
// IP address of the receiver Arduino
const IPAddress peerIP(192, 168, 243, 20);  // Update with the actual IP address
const unsigned int sendPort = 2000;         // Port to send data to

// Local port to listen on
const unsigned int listenPort = 3000;

WiFiUDP Udp;
char incomingPacket[50];  // Buffer for incoming data

int mode = 0;

void setup() {
  Serial.begin(115200);

  // Initialise accelerometer
  check(acc.init());
  acc.printRegisters();
  Serial.print(F("\r\nCHIP REVISION : "));
  Serial.println(acc.getRevisionId());
  check(acc.activateMeasure());
  acc.printRegisters();

  // Initialise gyroscope
  Wire.begin();
  if (!gyro.init()) {
    Serial.println("Failed to autodetect gyro type!");
    while (1)
      ;
  }
  gyro.enableDefault();

  // is below necessary
  // while (!Serial) { ; }  // Wait for Serial Monitor

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Start UDP
  Udp.begin(listenPort);
  Serial.print("Listening on port ");
  Serial.println(listenPort);

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  // Print initial message
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  setupScrollArea(TOP_FIXED_AREA, BOT_FIXED_AREA);

  // button code

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

int last_steady_state = LOW;       // the previous steady state from the input pin
int last_flickerable_state = LOW;  // the previous flickerable state from the input pin
int current_state;                 // the current reading from the input pin

unsigned long last_debounce_time = 0;  // the last time the output pin was toggled

float x = 0;
float y = 0;

void loop() {
  unsigned long timer = millis();  // Get current time

  // Read accelerometer values
  xyzlow = acc.getXYZLowPower(ad_range_2G);
  xyz = acc.getXYZ(ad_range_2G);
  temp = acc.getTemperature();

  // Read gyroscope values
  gyro.read();
  gyroX = gyro.g.x * 8.75 / 1000.0;  // Convert raw values to dps
  gyroY = gyro.g.y * 8.75 / 1000.0;
  gyroZ = gyro.g.z * 8.75 / 1000.0;

  // Example variables

  // Create the message
  int* controls = get_control(&mode);

  char message[50];
  snprintf(message, sizeof(message), "v1=%d, v2=%d, mode=%d", controls[0], controls[1], mode);

  // Send the message via UDP
  Udp.beginPacket(peerIP, sendPort);
  Udp.write(message);
  Udp.endPacket();

  Serial.print("Sent message: ");
  Serial.println(message);
  int xa, ya;
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);

    // Read the packet into the buffer
    int len = Udp.read(incomingPacket, sizeof(incomingPacket) - 1);
    if (len > 0) {
      incomingPacket[len] = '\0'; // Null-terminate the string
    }

    Serial.print("Received message: ");
    Serial.println(incomingPacket);

    // Parse the received data
    
    if (sscanf(incomingPacket, "x=%d, y=%d", &xa, &ya) == 2) {
      Serial.print("Parsed values - x: ");
      Serial.print(xa);
      Serial.print(", y: ");
      Serial.print(ya);
    } else {
      Serial.println("Failed to parse message.");
    }
  } else{
    Serial.println("No message :(");
  }

  // two delays? - delay(10); // Wait for a second before sending the next packet

  // Ensure loop runs at a stable rate
  // delay(100 - (millis() - timer)); // uncomment if needed, comes from docs


  // read the state of the switch/button:
  current_state = digitalRead(BUTTON_PIN);

  // If the switch/button changed, due to noise or pressing:
  if (current_state != last_flickerable_state) {
    // reset the debouncing timer
    last_debounce_time = millis();
    // save the the last flickerable state
    last_flickerable_state = current_state;
  }

  if ((millis() - last_debounce_time) > DEBOUNCE_TIME) {
    // if the button state has changed:
    if (last_steady_state == HIGH && current_state == LOW) {
      // Serial.println("The button is pressed");
      loopCount++;
    } else if (last_steady_state == LOW && current_state == HIGH) {
      // Serial.println("The button is released");

    
    }
    // save the the last steady state
    last_steady_state = current_state;
  }

  // Store the last drawn position
  static float prev_x = 0;
  static float prev_y = 0;

  // Clear the previous position before drawing a new "x"
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.drawCentreString("x", round(prev_x), round(prev_y), 2);

  // Draw the new "x"
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawCentreString("x", round(x), round(y), 2);

  // Update previous position
  prev_x = x;
  prev_y = y;

  // Move to next position
  x = 100 + xa;
  y = 150 + ya;

  // Handle serial input
  if (Serial.available()) {
    data = Serial.read();

    // Scroll when necessary
    if (data == '\r' || xPos > 231) {
      xPos = 0;
      yDraw = scroll_line();
    }

    if (data > 31 && data < 128) {
      xPos += tft.drawChar(data, xPos, yDraw, 2);
      blank[(18 + (yStart - TOP_FIXED_AREA) / TEXT_HEIGHT) % 19] = xPos;
    }
  }
  delay(10); // 10 ms
}

void check(short code) {
  if (code <= 0) {
    Serial.print(F("\r\n**** ERROR: "));
    Serial.print(code);
    Serial.println(F(" ****"));
    if (code == -110)
      Serial.println(F("Device not connected? Check wiring or noisy power supply."));
    else if (code >= -104 && code <= -102)
      Serial.println(F("Check power supply stability."));
    delay(3000);
  } else {
    Serial.println(F("----------------------------------------"));
  }
}

// Scroll display
int scroll_line() {
  int yTemp = yStart;
  tft.fillRect(0, yStart, blank[(yStart - TOP_FIXED_AREA) / TEXT_HEIGHT], TEXT_HEIGHT, TFT_BLACK);

  yStart += TEXT_HEIGHT;
  if (yStart >= YMAX - BOT_FIXED_AREA)
    yStart = TOP_FIXED_AREA + (yStart - YMAX + BOT_FIXED_AREA);

  scrollAddress(yStart);
  return yTemp;
}

// Set scrolling area
void setupScrollArea(uint16_t tfa, uint16_t bfa) {
  tft.writecommand(ILI9341_VSCRDEF);
  tft.writedata(tfa >> 8);
  tft.writedata(tfa);
  tft.writedata((YMAX - tfa - bfa) >> 8);
  tft.writedata(YMAX - tfa - bfa);
  tft.writedata(bfa >> 8);
  tft.writedata(bfa);
}

// Update scroll pointer
void scrollAddress(uint16_t vsp) {
  tft.writecommand(ILI9341_VSCRSADD);
  tft.writedata(vsp >> 8);
  tft.writedata(vsp);
}

int* get_control(int* mode_a) {
  static int array[2];

  MeasurementInMg a_p_low = acc.getXYZLowPower(ad_range_2G);
  MeasurementInMg a_p = acc.getXYZ(ad_range_2G);

  double mag_a_p = sqrt((a_p.x / 1000) * (a_p.x / 1000) + (a_p.y / 1000) * (a_p.y / 1000) + (a_p.z / 1000) * (a_p.z / 1000));
  double* angles = RP_calculate(a_p);

  if (mag_a_p > (1.5 * 9.81)) {
    if (*mode_a == 1) {
      *mode_a = 0;
    } else {
      *mode_a = 1;
    }
    //buzzer logic
  }

  float theta_g_vel, phi_g_vel, psi_g_vel;
  gyro.read();
  theta_g_vel = gyro.g.x * 8.75 / 1000.0;  // Convert raw values to dps
  phi_g_vel = gyro.g.y * 8.75 / 1000.0;
  psi_g_vel = gyro.g.z * 8.75 / 1000.0;


  float time_gap = 0.01;
  float threshold_difference = 5;
  float threshold = 20;


  if (theta_g_vel < 0.8 and theta_g_vel > -0.58) {
    theta_g_vel = 0;
  }

  theta_g += theta_g_vel * time_gap;
  phi_g += phi_g_vel * time_gap;
  psi_g += psi_g_vel * time_gap;

 // !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think
  // !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think
    // !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think
      // !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think
        // !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think
          // !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think
        // !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think
      // !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think
    // !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think
  // !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think
// !!! angles is an array of length 2, how is angles[2] being accessed? it should be angles[0] and angles[1] I think

  if (fabs(theta_g - angles[0]) > threshold_difference && fabs(phi_g - angles[1]) > threshold_difference) {
    if (fabs(angles[0]) > threshold) {
      if (angles[0] > 0) {
        array[0] = 500;
        array[1] = 1000;
      } else {
        array[0] = 1000;
        array[1] = 500;
      }
    } else if (fabs(angles[1]) > threshold) {
      if (angles[1] > 0) {
        array[0] = 1000;
        array[1] = 1000;
      } else {
        array[0] = -1000;
        array[1] = -1000;
      }
    }
  } else {
    array[0] = 0;
    array[1] = 0;
  }

  //   // Display accelerometer values
  // Serial.print(F("ACC (8-bit) x: "));
  // Serial.print(a_p_low.x / 1000.0);
  // Serial.print(F(" y: "));
  // Serial.print(a_p_low.y / 1000.0);
  // Serial.print(F(" z: "));
  // Serial.print(a_p_low.z / 1000.0);
  // Serial.println("");

  // Display gyroscope values
  // Serial.print("GYRO theta: ");
  // Serial.print(theta_g);
  // Serial.print(" phi: ");
  // Serial.print(phi_g);

  // Serial.print(" ACC Theta: ");
  // Serial.print(angles[0]);
  // Serial.print(" phi: ");
  // Serial.print(angles[1]);
  // Serial.println(" ");

  // Serial.print("motor speed left: ");
  // Serial.print(array[0]);
  // Serial.print(", motor speed right: ");
  // Serial.print(array[1]);

  return array;
}


// calculate the Roll&Pitch
double* RP_calculate(MeasurementInMg acc) {
  static double angles[2];
  double x_Buff = float(acc.x);
  double y_Buff = float(acc.y);
  double z_Buff = float(acc.z);

  double roll = atan2(y_Buff, z_Buff) * 57.3;
  double pitch = atan2((-x_Buff), sqrt(y_Buff * y_Buff + z_Buff * z_Buff)) * 57.3;

  angles[0] = roll;
  angles[1] = pitch;

  return angles;
}
