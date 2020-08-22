#include <Adafruit_GFX.h>      // Include core graphics library for the display
#include <Adafruit_SSD1306.h>  // Include Adafruit_SSD1306 library to drive the display

#define sensor A0
#define trigger 4
#define echo 5

Adafruit_SSD1306 display(128, 64);

void setup()  // Start of setup
{                
  Serial.begin(9600);
  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  
  delay(100);  // This delay is needed to let the display to initialize

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C
 
  display.clearDisplay();  // Clear the buffer

  display.setTextColor(WHITE);  // Set color of the text

  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3

  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                               // To override this behavior (so text will run off the right side of the display - useful for
                               // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                               // with setTextWrap(true).

  display.dim(0);  //Set brightness (0 is maximun and 1 is a little dim)

  delay(1000);

}

void loop()
{
  display.clearDisplay();

  int angle = getAngle();
  displayValue("ANGLE: ", 0, 10, 2);
  displayValue(angle, 70, 10, 2);

  float distance = getDistance(trigger, echo);
  displayValue("DISTANCE: ", 0, 30, 2);
  if(distance <= 30)
  {
    displayValue(distance, 0, 50, 2);
  }
  displayValue("CM", 100, 50, 2);
  
  display.display();  // Print everything we set previously

}

int getAngle()
{
  int value = analogRead(A0);
  long angle = 0;
  if(value <= 523)
    angle = map(value, 523, 305, 0, 55);
  else
    angle = map(value, 524, 742, -1, -55);
  return angle;
}

float getDistance(int Trigger, int Echo)
{
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(Trigger, LOW);
  float duration = pulseIn(Echo, HIGH);

  //Calculate distance (in cm) based on the speed of sound
  return duration / 58.2;
}

template <class T> void displayValue(T text, int x, int y, int fontSize)
{
  display.setTextSize(fontSize);
  display.setCursor(x, y);
  display.println(text);
}

