#include <LiquidCrystal.h>
#include <Servo.h>
// Button and pin variables
int resetContButton = 7;
int leftButton = 6;
int rightButton = 5;
int autoButton = 4;
// Pill variables
int rightPills = 5;
int leftPills = 5;
int rightCnt;
int leftCnt;
int autoRightCnt = 1;
int autoLeftCnt = 1;
int seconds = 0;
// Servo and LCD variables
LiquidCrystal lcd_1(12, 11, 10, 9, 3, 2);
Servo left;
Servo right;
int pos_left = 0; // position variables
int pos_right = 0;

void setup(){
  pinMode(resetContButton,INPUT);
  pinMode(leftButton,INPUT);
  pinMode(rightButton,INPUT);
  pinMode(autoButton,INPUT);
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  left.attach(13);
  right.attach(8);
  left.write(0);
  right.write(0);
}
void run(int r_pills, int l_pills){
  for(int i = 1; i <= r_pills; i++){
    pos_left = pos_left + 30;
    left.write(pos_left);
    delay(1000);
  }
  for(int j = 1; j <= l_pills; j++){
    pos_right = pos_right + 30;
    right.write(pos_right);
    delay(1000);
  }
}
void run_reset(){
  left.write(0);
  right.write(0);
}

void loop(){
  if(rightPills <= 0 || leftPills <= 0){ // Check to see if there are pills
    while(!digitalRead(resetContButton)){
      lcd_1.setCursor(0, 0);
      lcd_1.print("Reset! Remove");
      lcd_1.setCursor(0,1);
      lcd_1.print("Pills. Cont:1");
      delay(200);
      lcd_1.clear();
    }
    lcd_1.clear();
    run_reset();
    delay(4000);
    while(!digitalRead(resetContButton)){
      lcd_1.setCursor(0, 0);
      lcd_1.print("Add new pills");
      lcd_1.setCursor(0,1);
      lcd_1.print("Cont:1");
      delay(200);
      lcd_1.clear();
    }
    lcd_1.print("Successfully");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Reset!");
    rightPills = 5;
    leftPills = 5;
    delay(1000);
  }
  else{
    if(digitalRead(7)){ // Manual
      lcd_1.clear();
      delay(400);
      rightCnt = 0;
      leftCnt = 0;
      lcd_1.print("What would like?"); // Display the number of pills
      lcd_1.setCursor(0, 1);
      lcd_1.print("RP: " + String(rightPills) + " LP: " + String(leftPills));
      delay(1500);
      lcd_1.clear();
      lcd_1.print("Select Right Pills");
      lcd_1.setCursor(0, 1);
      lcd_1.print("0-"+ String(rightPills) + " available");
      delay(1000);
      lcd_1.clear();
      delay(300);
      while((!digitalRead(resetContButton)) || !(rightCnt <= rightPills && rightCnt >= 0)){ // Set desired Right Pills with correct range
        lcd_1.print("Right Pills: " + String(rightCnt));
        delay(200);
        if(digitalRead(leftButton)){ // increase
          rightCnt = rightCnt + 1;
          delay(200);
        }
        else if(digitalRead(rightButton)){ // decrease
          rightCnt = rightCnt - 1;
          delay(200);
        }
        lcd_1.clear();
      }
      delay(200);
      lcd_1.clear();
      lcd_1.print("Select Left Pills"); // Display the number of pills
      lcd_1.setCursor(0, 1);
      lcd_1.print("0-"+ String(leftPills) + " available");
      delay(1000);
      lcd_1.clear();
      delay(300);
      while((!digitalRead(resetContButton)) || !(leftCnt <= leftPills && leftCnt >= 0)){ // Set desired Left Pills with correct range
        lcd_1.print("Left Pills: " + String(leftCnt));
        delay(200);
        if(digitalRead(leftButton)){ // Increase
          leftCnt = leftCnt + 1;
          delay(200);
        }
        else if(digitalRead(rightButton)){ // Decrease
          leftCnt = leftCnt - 1;
          delay(200);
        }
        lcd_1.clear();
      }
      delay(200);
      run(rightCnt,leftCnt);
      delay(1000);
      lcd_1.print("Success!");
      lcd_1.setCursor(0,1);
      lcd_1.print("RP: " + String(rightCnt) + "   LP: " + String(leftCnt));
      rightPills = rightPills - rightCnt; // Update pill counters
      leftPills = leftPills - leftCnt;
      delay(1500);
      lcd_1.clear();
      delay(300);
    }
    else if(digitalRead(4)){ // Auto
      lcd_1.setCursor(0,0);
      lcd_1.print("Following is");
      lcd_1.setCursor(0,1);
      lcd_1.print("Pill Set");
      delay(1000);
      lcd_1.clear();
      while((!digitalRead(resetContButton)) && autoRightCnt <= rightPills && autoLeftCnt <= leftPills){ // Wait till button is presssed and pill set is in range
        if(digitalRead(4)){ // Change pill set
          delay(2000);
          while(!digitalRead(4) || !(autoRightCnt <= rightPills && autoRightCnt >= 0)){ // Change number of Right pills
            lcd_1.print("Change Right Set");
            lcd_1.setCursor(0,1);
            lcd_1.print("RP: " + String(autoRightCnt) + "  LP: " + String(autoLeftCnt));
            delay(200);
            if(digitalRead(leftButton)){ // Increase
              autoRightCnt = autoRightCnt + 1;
              delay(200);
            }
            else if(digitalRead(rightButton)){ // Decrease
              autoRightCnt = autoRightCnt - 1;
              delay(200);
            }
            lcd_1.clear();
          }
          delay(2000);
          while(!digitalRead(4) || !(autoLeftCnt <= rightPills && autoLeftCnt >= 0)){ // Change number of Left pills
            lcd_1.print("Change Left Set");
            lcd_1.setCursor(0,1);
            lcd_1.print("RP: " + String(autoRightCnt) + "  LP: " + String(autoLeftCnt));
            delay(200);
            if(digitalRead(leftButton)){ // Increase
              autoLeftCnt = autoLeftCnt + 1;
              delay(200);
            }
            else if(digitalRead(rightButton)){ // Decrease
              autoLeftCnt = autoLeftCnt - 1;
              delay(200);
            }
            lcd_1.clear();
          }
          delay(2000);
          lcd_1.clear();
          lcd_1.setCursor(0,0);
          lcd_1.print("Pill set");
          lcd_1.setCursor(0,1);
          lcd_1.print("selected");
          delay(500);
          lcd_1.clear();
        }
        else{
          lcd_1.setCursor(0,0);
          lcd_1.print("Pills Set");
          lcd_1.setCursor(0,1);
          lcd_1.print("RP: " + String(autoRightCnt) + "  LP: " + String(autoLeftCnt));
          delay(500);
          lcd_1.clear();
          delay(100);
        }
      }
      delay(100);
      run(autoRightCnt,autoLeftCnt);
      delay(2000);
      lcd_1.setCursor(0,0);
      lcd_1.print("Auto Successful!");
      delay(1000);
      rightPills = rightPills - autoRightCnt; // Update pill counters
      leftPills = leftPills - autoLeftCnt;
      lcd_1.clear();
    } 
    else{ // Wait till user picks mode
      lcd_1.setCursor(0, 0);
      lcd_1.print("Pick Mode");
      lcd_1.setCursor(0, 1);
      lcd_1.print("Manual:1  Auto:4");
      delay(200);
      lcd_1.clear();
    }
  }
}