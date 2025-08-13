#include <Servo.h>


// Servo Motor Definitions

Servo thumb, index, middle, ring, pinky;

// Pins for each servo

const int thumbPin = 2;
const int indexPin = 3;
const int middlePin = 4;
const int ringPin = 5;
const int pinkyPin = 6;


// Flex Sensors for Hand Detection

const int flexIndexPin = A0;  // Index finger
const int flexRingPin = A1;   // Ring finger

// Threshold to detect bent vs straight
const int flexThreshold = 500;


// Ultrasonic Sensor Pins

const int trigPin = 7;
const int echoPin = 8;


// Servo Positions

const int closed = 0;   // Finger fully closed
const int open = 90;    // Finger fully open


// Variables

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  // Attach servo motors

  thumb.attach(thumbPin);
  index.attach(indexPin);
  middle.attach(middlePin);
  ring.attach(ringPin);
  pinky.attach(pinkyPin);

  // Ultrasonic pins

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start with all fingers open

  openAllFingers();

  Serial.println("Robotic Hand: Rock-Paper-Scissors ready!");
  Serial.println("Place your hand ~20 cm above the ultrasonic sensor to start the game.");
}

void loop() {
  // Measure distance to start the game
  distance = getDistance();

  if(distance > 0 && distance <= 20) { // Start game when hand is detected
    Serial.println("\n--- Game Started ---");

    // Read User Hand
    int indexValue = analogRead(flexIndexPin);
    int ringValue = analogRead(flexRingPin);
    
    int userMove = 0; // 1-Rock, 2-Paper, 3-Scissors
    
    if(indexValue < flexThreshold && ringValue < flexThreshold) userMove = 1; // Rock
    else if(indexValue > flexThreshold && ringValue > flexThreshold) userMove = 2; // Paper
    else if(indexValue > flexThreshold && ringValue < flexThreshold) userMove = 3; // Scissors

    // Robot Random Move
    int robotMove = random(1, 4); // 1-Rock, 2-Paper, 3-Scissors

    // Countdown before showing moves

    Serial.println("\nGet ready!");
    for(int i = 3; i > 0; i--){
      Serial.println(i);
      delay(1000); // 1 second per number
    }
    Serial.println("Go!\n");

    // Show robot move

    switch(robotMove){
      case 1: playRock(); Serial.println("Robot: Rock"); break;
      case 2: playPaper(); Serial.println("Robot: Paper"); break;
      case 3: playScissors(); Serial.println("Robot: Scissors"); break;
    }

    // Show user move

    switch(userMove){
      case 1: Serial.println("You: Rock"); break;
      case 2: Serial.println("You: Paper"); break;
      case 3: Serial.println("You: Scissors"); break;
      default: Serial.println("You: Move not detected!"); break;
    }

    // Determine Winner

    if(userMove == 0){
      Serial.println("Result: Invalid move!");
    }
    else if(userMove == robotMove){
      Serial.println("Result: Draw!");
    }
    else if((userMove == 1 && robotMove == 3) || 
            (userMove == 2 && robotMove == 1) || 
            (userMove == 3 && robotMove == 2)){
      Serial.println("Result: You Win!");
    }
    else{
      Serial.println("Result: Robot Wins!");
    }

    // Wait for hand removal and re-detection
    openAllFingers();
    Serial.println("\nPlease remove your hand...");
    // Wait until hand is removed (distance > 25 cm)
    while(getDistance() <= 25) {
      delay(50); // Small delay to avoid flooding Serial Monitor
    }

    Serial.println("Hand removed. Place hand again to start next game.");
    // Wait until hand is detected again (distance <= 20 cm)
    while(getDistance() > 20) {
      delay(50);
    }
  }

  delay(50);
}

// Function: Get Distance from Ultrasonic Sensor
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int dist = duration * 0.034 / 2; // cm
  return dist;
}

// Function: Open All Fingers
void openAllFingers() {
  thumb.write(open);
  index.write(open);
  middle.write(open);
  ring.write(open);
  pinky.write(open);
}

// Function: Rock Gesture
void playRock() {
  thumb.write(closed);
  index.write(closed);
  middle.write(closed);
  ring.write(closed);
  pinky.write(closed);
}

// Function: Paper Gesture
void playPaper() {
  openAllFingers();
}

// Function: Scissors Gesture
void playScissors() {
  index.write(open);
  middle.write(open);
  thumb.write(closed);
  ring.write(closed);
  pinky.write(closed);
}
