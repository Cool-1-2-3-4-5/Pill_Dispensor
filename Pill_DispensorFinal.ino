#include <LiquidCrystal.h>
#include <Servo.h>
// Button and pin variables
int resetContButton = 7;
int leftButton = 6;
int rightButton = 5;
int autoButton = 4;
// Pill variables
int redPills = 5;
int whitePills = 5;
int redCnt;
int whiteCnt;
int autoRedCnt = 1;
int autoWhiteCnt = 1;
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
void run(int r_pills, int w_pills){
  for(int i = 1; i <= r_pills; i++){
    pos_left = pos_left + 30;
    left.write(pos_left);
    delay(1000);
  }
  for(int j = 1; j <= w_pills; j++){
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
  if(redPills <= 0 || whitePills <= 0){ // Check to see if there are pills
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
    redPills = 5;
    whitePills = 5;
    delay(1000);
  }
  else{
    if(digitalRead(7)){ // Manual
      lcd_1.clear();
      delay(400);
      redCnt = 0;
      whiteCnt = 0;
      lcd_1.print("What would like?"); // Display the number of pills
      lcd_1.setCursor(0, 1);
      lcd_1.print("RP: " + String(redPills) + " WP: " + String(whitePills));
      delay(1500);
      lcd_1.clear();
      lcd_1.print("Select Red Pills");
      lcd_1.setCursor(0, 1);
      lcd_1.print("0-"+ String(redPills) + " available");
      delay(1000);
      lcd_1.clear();
      delay(300);
      while((!digitalRead(resetContButton)) || !(redCnt <= redPills && redCnt >= 0)){ // Set desired Red Pills with correct range
        lcd_1.print("Red Pills: " + String(redCnt));
        delay(200);
        if(digitalRead(leftButton)){ // increase
          redCnt = redCnt + 1;
          delay(200);
        }
        else if(digitalRead(rightButton)){ // decrease
          redCnt = redCnt - 1;
          delay(200);
        }
        lcd_1.clear();
      }
      delay(200);
      lcd_1.clear();
      lcd_1.print("Select White Pills"); // Display the number of pills
      lcd_1.setCursor(0, 1);
      lcd_1.print("0-"+ String(whitePills) + " available");
      delay(1000);
      lcd_1.clear();
      delay(300);
      while((!digitalRead(resetContButton)) || !(whiteCnt <= whitePills && whiteCnt >= 0)){ // Set desired White Pills with correct range
        lcd_1.print("White Pills: " + String(whiteCnt));
        delay(200);
        if(digitalRead(leftButton)){ // Increase
          whiteCnt = whiteCnt + 1;
          delay(200);
        }
        else if(digitalRead(rightButton)){ // Decrease
          whiteCnt = whiteCnt - 1;
          delay(200);
        }
        lcd_1.clear();
      }
      delay(200);
      run(redCnt,whiteCnt);
      delay(1000);
      lcd_1.print("Success!");
      lcd_1.setCursor(0,1);
      lcd_1.print("RP: " + String(redCnt) + "   WP: " + String(whiteCnt));
      redPills = redPills - redCnt; // Update pill counters
      whitePills = whitePills - whiteCnt;
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
      while((!digitalRead(resetContButton)) && autoRedCnt <= redPills && autoWhiteCnt <= whitePills){ // Wait till button is presssed and pill set is in range
        if(digitalRead(4)){ // Change pill set
          delay(2000);
          while(!digitalRead(4) || !(autoRedCnt <= redPills && autoRedCnt >= 0)){ // Change number of red pills
            lcd_1.print("Change Red Set");
            lcd_1.setCursor(0,1);
            lcd_1.print("RP: " + String(autoRedCnt) + "  WP: " + String(autoWhiteCnt));
            delay(200);
            if(digitalRead(leftButton)){ // Increase
              autoRedCnt = autoRedCnt + 1;
              delay(200);
            }
            else if(digitalRead(rightButton)){ // Decrease
              autoRedCnt = autoRedCnt - 1;
              delay(200);
            }
            lcd_1.clear();
          }
          delay(2000);
          while(!digitalRead(4) || !(autoWhiteCnt <= redPills && autoWhiteCnt >= 0)){ // Change number of white pills
            lcd_1.print("Change White Set");
            lcd_1.setCursor(0,1);
            lcd_1.print("RP: " + String(autoRedCnt) + "  WP: " + String(autoWhiteCnt));
            delay(200);
            if(digitalRead(leftButton)){ // Increase
              autoWhiteCnt = autoWhiteCnt + 1;
              delay(200);
            }
            else if(digitalRead(rightButton)){ // Decrease
              autoWhiteCnt = autoWhiteCnt - 1;
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
          lcd_1.print("RP: " + String(autoRedCnt) + "  WP: " + String(autoWhiteCnt));
          delay(500);
          lcd_1.clear();
          delay(100);
        }
      }
      delay(100);
      run(autoRedCnt,autoWhiteCnt);
      delay(2000);
      lcd_1.setCursor(0,0);
      lcd_1.print("Auto Successful!");
      delay(1000);
      redPills = redPills - autoRedCnt; // Update pill counters
      whitePills = whitePills - autoWhiteCnt;
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