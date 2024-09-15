#define STEPPER_PIN_1 7
#define STEPPER_PIN_2 8
#define STEPPER_PIN_3 12
#define STEPPER_PIN_4 13
int step_number = 0;
int passDig = 0;
bool firstup = true;
bool firstdown = true;
bool firstleft = true;
bool firstright = true;
bool open = false;
String CorrectPassword[6] = {"up", "up", "down", "down", "left", "right"};
String EnteredPassword[6] = {"", "", "", "", "", ""};
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

 pinMode(STEPPER_PIN_1, OUTPUT);
 pinMode(STEPPER_PIN_2, OUTPUT);
 pinMode(STEPPER_PIN_3, OUTPUT);
 pinMode(STEPPER_PIN_4, OUTPUT);

 pinMode(2, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValuex = analogRead(A0)-510;
  int sensorValuey = analogRead(A1)-500;
  int sensorvaluebut = digitalRead(2);
  int brightnessy = sensorValuey/4;
  int brightnessx = sensorValuex/4;
  int yellow, blue, green, red;

  
 
  if(sensorvaluebut == 0){
       if(PasswordCheck(CorrectPassword, EnteredPassword) == true){
        open = true;
        
        
       }
    passDig = 0;
    Serial.println(passDig);
  }
Serial.println(sensorvaluebut);
  if(open == true){
    for(int i = 0; i < 1000; i++){
      OneStep(true);
       delay(2);
    }
    open = false;
  }

  //Serial.println(sensorvaluebut);

  if(passDig > 5){
    passDig = 0;
  }

  //yellow = brightnessy;
  if(brightnessy >= 0)
  {
    analogWrite(10, brightnessy);
    analogWrite(9, 0);
    if(brightnessy > 120 && firstleft == true){
      EnteredPassword[passDig] = "left";
      passDig++;
      firstleft = false;
    }

    if(brightnessy <20){
      firstleft = true;
    }
  }
  else
  {
    analogWrite(9, -brightnessy);
        if(-brightnessy > 120 && firstright == true){
      EnteredPassword[passDig] = "right";
      passDig++;
      firstright = false;
    }

    if(brightnessy > -100){
      firstright = true;
    }
  }
  if(brightnessx >= 0)
  {
    analogWrite(11, brightnessx);
    analogWrite(3, 0);
    if(brightnessx > 120 && firstdown == true){
      EnteredPassword[passDig] = "down";
      passDig++;
      firstdown = false;
    }

    if(brightnessx <20){
      firstdown = true;
    }
  }
  else
  {       
      if(-brightnessx > 120 && firstup == true){
      EnteredPassword[passDig] = "up";
      passDig++;
      firstup = false;
    }

    if(brightnessx > -100){
      firstup = true;
    }
        
    analogWrite(3, -brightnessx);
    //Serial.println(brightnessx);
  }
  // Serial.print("X: ");
  // Serial.print(sensorValuex);
  // Serial.print("Y: ");

// for (int i = 6 - 1; i >= 0; i--) 
    
//     Serial.println(EnteredPassword[i]);

      
   
  // }

 
}

void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
 
  
} 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}

bool PasswordCheck(String pass[], String cor[])
{
  for (int i = 0; i < 6; i++) 
  {
    if (CorrectPassword[i] != EnteredPassword[i]) 
    {
      Serial.println("WORKSWOO");
        return false;
    }
        
  }
  return true;
}
