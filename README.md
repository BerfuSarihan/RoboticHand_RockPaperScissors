# Robotic Hand: Rock-Paper-Scissors

An interactive robotic hand that mimics human gestures and plays Rock-Paper-Scissors in real time.

## Features
- 5 servo motors to control each finger individually
- 2 flex sensors on the index and ring fingers to detect user gestures
- Ultrasonic sensor starts the game when a hand is detected (~20 cm)
- Two modes:
  - **Hand Mimic Mode**: Robot copies your hand gestures
  - **Game Mode**: Robot plays Rock-Paper-Scissors with the user
- Serial Monitor displays both moves and the winner of each round

## Hardware Requirements
- Arduino board (Uno or compatible clone)
- 5x Servo motors
- 2x Flex sensors
- 1x Ultrasonic sensor (HC-SR04)
- Jumper wires, breadboard, and power supply

## Wiring / Schematics

- Flex sensors: index → A0, ring → A1
- Servo pins: thumb → 2, index → 3, middle → 4, ring → 5, pinky → 6
- Ultrasonic sensor: trig → 7, echo → 8

## Usage
1. Open `filename` in Arduino IDE
2. Connect your Arduino and upload the code
3. Place your hand ~20 cm above the ultrasonic sensor to start the game
4. Observe moves and results on the Serial Monitor

## Important Notes
- **Flex Sensor Calibration**: Adjust `flexThreshold` depending on your sensors. Use the Serial Monitor to read raw values. Bent fingers should read above the threshold, straight fingers below.
- **Servo Position Adjustment**: Adjust `open` and `closed` angles for smooth and complete finger movements. Test each finger individually to find the optimal positions.


