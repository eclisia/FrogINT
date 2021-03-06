/**
 * Simple Write. 
 * 
 * Check if the mouse is over a rectangle and writes the status to the serial port. 
 * This example works with the Wiring / Arduino program that follows below.
 */


import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port
int i ;
String inString;  // Input string from serial port
int lf = 10;      // ASCII linefeed 


void setup() 
{
  size(600, 600);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600,'N',8,2.0);
  myPort.bufferUntil(lf); 
  
}





void draw() {
  background(255);
  text("Start: " + inString, 10,10);
  
  if (mouseOverRect() == true) {  // If mouse is over square,
    fill(255,0,0);                    // change color and
    myPort.write('h');              // send an H to indicate mouse is over square
  } 
  else {                        // If mouse is not over square,
    fill(0,255,0);                      // change color and
    myPort.write('o');              // send an L otherwise
  }
  rect(50, 50, 100, 100);         // Draw a square
  text("received: " + inString, 10,200);
}

boolean mouseOverRect() { // Test if mouse is over square
  return ((mouseX >= 50) && (mouseX <= 150) && (mouseY >= 50) && (mouseY <= 150));
}


void serialEvent(Serial myPort) {
  // read a byte from the serial port:
  
  inString = myPort.readString(); 
   //<>//
 
  
}


/*
  // Wiring/Arduino code:
 // Read data from the serial and turn ON or OFF a light depending on the value
 
 char val; // Data received from the serial port
 int ledPin = 4; // Set the pin to digital I/O 4
 
 void setup() {
 pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
 Serial.begin(9600); // Start serial communication at 9600 bps
 }
 
 void loop() {
 while (Serial.available()) { // If data is available to read,
 val = Serial.read(); // read it and store it in val
 }
 if (val == 'H') { // If H was received
 digitalWrite(ledPin, HIGH); // turn the LED on
 } else {
 digitalWrite(ledPin, LOW); // Otherwise turn it OFF
 }
 delay(100); // Wait 100 milliseconds for next reading
 }
 
 */
