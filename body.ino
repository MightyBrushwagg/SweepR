#include <Wire.h>
#include <Motoron.h>
#include <math.h>
#include <WiFiS3.h>
#include <WiFiUdp.h>
#include <tracks.h>

// ADXL345 Accelerometer
#define DEVICE (0x53)
#define TO_READ (6)
char str[512];

// Buzzer and LED pins
#define BLUE_PIN 7 // Probably useless
#define GREEN_PIN 8 // PWM
#define BUZZER_PIN 9
#define RED_PIN 10 // PWM

// State Detection Thresholds
#define ACCEL_THRESHOLD 5000   // Adjust based on sensitivity
#define TILT_THRESHOLD 30.0    // Max tilt angle before state = 0 (degrees)
#define UPSIDE_DOWN_THRESHOLD -9.81 // Approx -1g, indicating inversion
int state = 1; // Default to normal operation

// Motor Encoder Definitions
const int encoder_ticks_per_rev = 292.7 / 2;
const float wheel_radius = 63.0 / 2.0;
const float wheel_circumference = 2.0 * M_PI * wheel_radius;
const float wheel_body_separation = 300.0;
const int motor_speed = 2000;
volatile int motor_speed_l = 1000;
volatile int motor_speed_r = 1000;

#define encoder_a_l 2
#define encoder_a_r 3
#define encoder_b_l 4
#define encoder_b_r 5

MotoronI2C mc;

volatile int voltage_sign_l = -1;
volatile int voltage_sign_r = 1;

volatile long encoder_ticks_l = 0;
volatile long encoder_ticks_r = 0;
long prev_ticks_l = 0, prev_ticks_r = 0;

float x = 0.0, y = 0.0, theta = 0.0, v = 0.0, w = 0.0;
unsigned long prev_time = 0;

// Accelerometer Variables
byte buff[TO_READ];
int regAddress = 0x32;
int x_a, y_a, z_a;
double roll = 0.00, pitch = 0.00;

// Music Variables
int *melodies[] = {melody1, melody2, melody3, melody4, melody5, melody6};
int *durations[] = {durations1, durations2, durations3, durations4, durations5, durations6};
int noteCounts[] = {
    sizeof(durations1) / sizeof(int),
    sizeof(durations2) / sizeof(int),
    sizeof(durations3) / sizeof(int),
    sizeof(durations4) / sizeof(int),
    sizeof(durations5) / sizeof(int),
    sizeof(durations6) / sizeof(int)};

int noteIndex = 0;
int trackIndex = 0;
unsigned long previousNoteTime = 0;
bool isPlaying = false;
const int totalTracks = 6;

// Replace with your network credentials
const char ssid[] = "eduino";
const char password[] = "password";

// body is 20, controller is 22
// IP address of the receiver Arduino
const IPAddress peerIP(192, 168, 243, 22);  // Update with the actual IP address
const unsigned int sendPort = 3000;         // Port to send data to

// Local port to listen on
const unsigned int listenPort = 2000;

WiFiUDP Udp;
char incomingPacket[50]; // Buffer for incoming data

void handleEncoderA_L()
{
  if (motor_speed_l > 0)
    encoder_ticks_l++;
  else
    encoder_ticks_l--;
}

void handleEncoderA_R()
{
  if (motor_speed_r > 0)
    encoder_ticks_r++;
  else
    encoder_ticks_r--;
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  // Motoron Initialisation
  mc.reinitialize();
  mc.disableCrc();
  mc.clearResetFlag();
  mc.setMaxAcceleration(1, 140);
  mc.setMaxDeceleration(1, 300);
  mc.setMaxAcceleration(3, 140);
  mc.setMaxDeceleration(3, 300);

  // Encoder Interrupts
  pinMode(encoder_a_l, INPUT);
  pinMode(encoder_b_l, INPUT);
  pinMode(encoder_a_r, INPUT);
  pinMode(encoder_b_r, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder_a_l), handleEncoderA_L, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder_a_r), handleEncoderA_R, RISING);

  // LED & Buzzer Setup
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Accelerometer Initialisation
  writeTo(DEVICE, 0x2D, 0);
  writeTo(DEVICE, 0x2D, 16);
  writeTo(DEVICE, 0x2D, 8);

  prev_time = millis();

  // WiFi Setup
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Start UDP
  Udp.begin(listenPort);
  Serial.print("Listening on port ");
  Serial.println(listenPort);

}

void loop() {
  // mc.setSpeed(1, 2000);
  // mc.setSpeed(3, -2000);

  updateAccelerometer();
  checkRobotState();
  updateOdometry();
  playMusicNonBlocking();
  handleWiFi(x, y);

  // Serial.print("The acceleration info of x, y, z are:");
  sprintf(str, "%d %d %d", x_a, y_a, z_a);
  // Serial.print(str);
  Serial.write(10);
  //Roll & Pitch calculate
  RP_calculate();
  // Serial.print("Roll:"); Serial.println( roll );
  // Serial.print("Pitch:"); Serial.println( pitch );
  // Serial.println("");

  delay(10); // delay 10 ms
}

// Odometry Update
void updateOdometry()
{
  unsigned long current_time = millis();
  float dt = (current_time - prev_time) / 1000.0;

  long current_ticks_l = encoder_ticks_l;
  long current_ticks_r = encoder_ticks_r;

  float dL = ((current_ticks_l - prev_ticks_l) * wheel_circumference) / encoder_ticks_per_rev;
  float dR = ((current_ticks_r - prev_ticks_r) * wheel_circumference) / encoder_ticks_per_rev;

  prev_ticks_l = current_ticks_l;
  prev_ticks_r = current_ticks_r;

  float dTheta = (dR - dL) / (2.0 * wheel_body_separation);
  float D = (dR + dL) / 2.0;

  theta += dTheta;
  x += D * cos(theta);
  y += D * sin(theta);

  float vL = dL / dt, vR = dR / dt;
  v = (vL + vR) / 2.0;
  w = wheel_radius * (vR - vL) / (2.0 * wheel_body_separation);

  prev_time = current_time;

  // Serial Output
  // Serial.print("X:");
  // Serial.print(x);
  // Serial.print("\tY:");
  // Serial.print(y);
  // Serial.print("\tZero:");
  // Serial.println(0);

  // Motor Control
  mc.setSpeed(1, -motor_speed_l);
  mc.setSpeed(3, motor_speed_r);
  // mc.setSpeed(1, 2000);
  // mc.setSpeed(3, -2000);
}

// Accelerometer Update
void updateAccelerometer()
{
  readFrom(DEVICE, regAddress, TO_READ, buff);
  x_a = (int16_t)((buff[1] << 8) | buff[0]);  
  y_a = (int16_t)((buff[3] << 8) | buff[2]);  
  z_a = (int16_t)((buff[5] << 8) | buff[4]);

  RP_calculate();
}

// Roll & Pitch Calculation
void RP_calculate()
{
  roll = atan2(y_a, z_a) * 57.3;
  pitch = atan2(-x_a, sqrt(y_a * y_a + z_a * z_a)) * 57.3;
}

// Finding the robot's state from accelerometer values
void checkRobotState() {
    // Convert raw accelerometer data to meaningful acceleration values
    double ax = x_a * 0.0039; // Assuming ADXL345 scale (LSB to g conversion)
    double ay = y_a * 0.0039;
    double az = z_a * 0.0039 * 9.81; // Convert to m/s^2

    // Check for Bumping (Short small spikes in acceleration)
    if (abs(ax) > ACCEL_THRESHOLD || abs(ay) > ACCEL_THRESHOLD || abs(az) > ACCEL_THRESHOLD) {
        state = 0;
    }
    // Check for Jumping (Free fall: az approaches 0 or becomes negative)
    else if (az < 1.0) {  
        state = 0;
    }
    // Check for Tilting (Roll or Pitch exceeding threshold)
    else if (abs(roll) > TILT_THRESHOLD || abs(pitch) > TILT_THRESHOLD) {
        state = 0;
    }
    // Check for Landing Upside Down (Large impact + az near -1g)
    else if (az < UPSIDE_DOWN_THRESHOLD) {
        state = 0;
    }
    else {
        state = 1;
    }

    updateIndicators();
}

void updateIndicators() {
    if (state == 1) {
        setColour(0, 255, 0);
        isPlaying = false; // Allow normal song playback
    } else {
        setColour(255, 0, 0);
        tone(BUZZER_PIN, 200); // High-pitched beep for error
        isPlaying = true; // Stop music
    }
}

// RGB LED Control
void setColour(int R, int G, int B)
{
  analogWrite(RED_PIN, R);
  analogWrite(GREEN_PIN, G);
  analogWrite(BLUE_PIN, B);
}

// Non-blocking Music Playback
void playMusicNonBlocking()
{
  unsigned long currentMillis = millis();
  int *melody = melodies[trackIndex];
  int *trackDuration = durations[trackIndex];
  int numNotes = noteCounts[trackIndex];

  // If the state is 0, override music with an alarm sound
  if (state == 0)
  {
    tone(BUZZER_PIN, 2000); // High-pitched alarm
    return; // Exit the function to prevent normal music from playing
  }
  else
  {
    noTone(BUZZER_PIN); // Stop beeping when state is not 0
  }

  // If enough time has passed, move to the next note
  if (!isPlaying || (currentMillis - previousNoteTime > (1000 / trackDuration[noteIndex]) * 1.3))
  {
    noTone(BUZZER_PIN); // Stop previous note

    int duration = 1000 / trackDuration[noteIndex];
    tone(BUZZER_PIN, melody[noteIndex], duration);

    previousNoteTime = currentMillis;
    isPlaying = true;

    // Move to the next note
    noteIndex++;

    // If the song finishes, cycle to the next track
    if (noteIndex >= numNotes)
    {
      noteIndex = 0;
      trackIndex = (trackIndex + 1) % totalTracks;
    }
  }
}

void handleWiFi(float x, float y)
{
  // Send
  char message[50];
  snprintf(message, sizeof(message), "x=%d, y=%d", (int)x, (int)y);  // Cast to int if needed

  // Send the message via UDP
  Udp.beginPacket(peerIP, sendPort);
  Udp.write(message);
  Udp.endPacket();

  Serial.print("Sent message: ");
  Serial.println(message);

  // Receive
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    int len = Udp.read(incomingPacket, sizeof(incomingPacket) - 1);
    if (len > 0)
      incomingPacket[len] = '\0';

    Serial.print("Received message: ");
    Serial.println(incomingPacket);

    int v1, v2, mode;
    if (sscanf(incomingPacket, "v1=%d, v2=%d, mode=%d", &motor_speed_l, &motor_speed_r, &mode) == 3)
    {
      Serial.print("Parsed v1: "); Serial.print(motor_speed_l);
      Serial.print(" v2: "); Serial.print(motor_speed_r);
      Serial.print(" mode: "); Serial.println(mode);
      
      // Optional: You can use v1, v2, mode to change behaviour
    }
  }
  else
  {
    Serial.print("sad :(");
  }
}

// I2C Communication
void writeTo(int device, byte address, byte val)
{
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.write(val);
  Wire.endTransmission();
}

void readFrom(int device, byte address, int num, byte buff[])
{
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(device, num);
  for (int i = 0; Wire.available(); i++)
    buff[i] = Wire.read();
}
