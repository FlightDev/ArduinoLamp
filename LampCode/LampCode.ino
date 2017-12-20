const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

const int outputA = 2; //the clk attach to pin 2
const int outputB = 3; //the dt pin attach to pin 3
const int clicker = 4;//the sw pin attach to pin 4 - this is the "clicker"

int counter = 0;
int currentMode = 0;
int aState;
int aLastState;
int whiteCounter = 255;
int speed = 5;

void setup() {
  // Start off with the LED off.
  setColorRgb(0,0,0);

//set clkPin,dePin,swPin as INPUT
pinMode(outputA, INPUT);
pinMode(outputB, INPUT);
pinMode(clicker, INPUT);
digitalWrite(clicker, HIGH);
Serial.begin(9600); // initialize serial communications at 9600 bps
aLastState = digitalRead(outputA);

}

void loop() {
  unsigned int rgbColor[3];
  while (true) {
    if (currentMode % 4 == 0){
      setColorRgb(0, 0, 0);
      if (buttonPressed()){
        currentMode += 1;
        delay(500);
        break;
      }
    }
    if (currentMode % 4 == 1){
      rgbColor[0] = 255;
      rgbColor[1] = 0;
      rgbColor[2] = 0;  
    
      // Choose the colors to increment and decrement.
      for (int decColor = 0; decColor < 3; decColor += 1) {
        int incColor = decColor == 2 ? 0 : decColor + 1;
        
        // cross-fade the two colors.
        for(int i = 0; i < 255; i += 1) {
          rgbColor[decColor] -= 1;
          rgbColor[incColor] += 1;
          setColorRgb(rgbColor[0], rgbColor[1], rgbColor[2]);
          aState = digitalRead(outputA);
              if (aState != aLastState) {
                if (digitalRead(outputB) != aState){
                  if (speed >= 150){
                    speed = 150;
                  }
                  else {
                    speed += 1;
                  }
                }
                else {
                  if (speed <= 1){
                    speed = 1;
                  }
                  else {
                    speed -= 1;
                  }
                }
                }
          delay(speed);
          if (buttonPressed()){
            currentMode += 1;
            delay(500);
            break;
          }
        }
      }
    }
    if (currentMode % 4 == 2){
      // Start off with red.
      rgbColor[0] = 255;
      rgbColor[1] = 255;
      rgbColor[2] = 255;  
      setColorRgb(255, 255, 255);
      while (true){
        aState = digitalRead(outputA);
            if (aState != aLastState) {
              if (digitalRead(outputB) != aState){
                if (counter > 1530){
                  counter = 0;
                }
                else {
                  counter += 15;
                }
              }
              else {
                
                if (counter <= 0){
                  counter = 1530;
                }
                else {
                  counter -= 15;
                }
              }
          if (counter > 0 && counter <= 510){
            if (counter < 256){
            rgbColor[0] = 255;
            rgbColor[1] = counter;
            }
            else {
            rgbColor[0] = 510 - counter;
            rgbColor[1] = 255;
            }
            rgbColor[2] = 0;
          }
          if (counter > 511 && counter <= 1020){
            if (counter < 766){
            rgbColor[1] = 255;
            rgbColor[2] = counter - 511;
            }
            else {
            rgbColor[1] = 1020 - counter;
            rgbColor[2] = 255;
            }
            rgbColor[0] = 0;
          }
          if (counter > 1020 && counter <= 1530){
            if (counter < 1275){
            rgbColor[2] = 255;
            rgbColor[0] = counter - 1020;
            }
            else {
            rgbColor[2] = 1530 - counter;
            rgbColor[0] = 255;
            }
            rgbColor[1] = 0;
          }
          setColorRgb(rgbColor[0], rgbColor[1], rgbColor[2]);
          delay(5); 
            }
          aLastState = aState;
      if (buttonPressed()){
        currentMode += 1;
        delay(500);
        break;
      }
      }
    }
    if (currentMode % 4 == 3){
      setColorRgb(0, 0, 0);
      for (int i = 0; i < 256; i++){
        setColorRgb(i, i, i);
        delay(5);
      }
      int brightness = 255;
       while (currentMode % 4 == 3){
        aState = digitalRead(outputA);
              if (aState != aLastState) {
                if (digitalRead(outputB) != aState){
                  if (brightness >= 255){
                    brightness = 255;
                  }
                  else {
                    brightness += 5;
                  }
                }
                else {
                  if (brightness <= 10){
                    brightness = 10;
                  }
                  else {
                    brightness -= 5;
                  }
                }
            setColorRgb(brightness, brightness, brightness);
            delay(5);
            }
        if (buttonPressed()){
          currentMode += 1;
          delay(500);
          break;
        }
      }
    }
  }
}

boolean buttonPressed(){
  int button_pressed = !digitalRead(clicker);
  return button_pressed;  
}

void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }
