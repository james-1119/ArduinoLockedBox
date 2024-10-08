//Initializing the variables 
#define STEPPER_PIN_1 4
#define STEPPER_PIN_2 5
#define STEPPER_PIN_3 6
#define STEPPER_PIN_4 7

#define GREEN 10
#define RED 9
#define BLUE 11
#define YELLOW 3

int step_number = 0;
int passDig = 0;
bool firstup = true;
bool firstdown = true;
bool firstleft = true;
bool firstright = true;
bool firstbut = true;
bool open = false;
bool OC = true;

//Creates a string array for the correct password as well as the user input
String CorrectPassword[6] = {"up", "up", "down", "down", "left", "right"};
String EnteredPassword[6] = {"", "", "", "", "", ""};
void setup() {

 Serial.begin(9600);

//Sets pins to output
 pinMode(STEPPER_PIN_1, OUTPUT);
 pinMode(STEPPER_PIN_2, OUTPUT);
 pinMode(STEPPER_PIN_3, OUTPUT);
 pinMode(STEPPER_PIN_4, OUTPUT);

 pinMode(12, OUTPUT);     
 digitalWrite(12, HIGH);   

//Sets the pin 2 (where the joystick button goes) as input
 pinMode(2, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValuex = analogRead(A0)-510;    //Creates variable for the analog input of the y component of the joystick
  int sensorValuey = analogRead(A1)-500;    //Creates variable for the analog input of the x component of the joystick
  int sensorvaluebut = digitalRead(2);      //Creates variable for the digital input of the joystick button


  int brightnessy = sensorValuey/4;    //Divides the analog input in x and y by 4 to get a value that is able to be outputted
  int brightnessx = sensorValuex/4; 

  int yellow, blue, green, red;     //Creates integer variables for the different colored lightes that show user input


 
  if(sensorvaluebut == 0 && firstbut == true){      //Checks for when the joystick button is pressed
       if(PasswordCheck(CorrectPassword, EnteredPassword) == true){  //Using the PasswordCheck function, checks if the two arrays are equal
          open = true; //Sets open to true
       }

    passDig = 0; //Sets the current password digit back to the start
    firstbut = false;
  }

  if(sensorvaluebut == 1){
    firstbut = true;
  }

  if(open == true && OC == true){ //Checks for if the open variable is true

    for(int i = 0; i < 1032; i++){  //For loop that runs the stepper motor 

      OneStep(true);  //Calls the OneStep function which activates the stepper motor
      delay(3);       //Delays 2 ms to make sure the stepper motor functions properly

    }

    open = false; //Sets open to false
    OC = false;
  }
  else if (open == true && OC == false)
  {
     for(int i = 0; i < 1032; i++){  //For loop that runs the stepper motor 

      OneStep(false);  //Calls the OneStep function which activates the stepper motor
      delay(3);       //Delays 2 ms to make sure the stepper motor functions properly

    }

    open = false;
    OC = true;
  }


  if(passDig > 5){    //Whenever the password digit goes past the number of elements in the password array, set it back to the first digit
    passDig = 0;
  }

  if(brightnessy >= 0)  //if the brightnessy is in the positive direction execute 
  {
    analogWrite(GREEN, brightnessy);  //Set the left light (green) to equal brightness y
    analogWrite(RED, 0);    //Sets the right light (red) to have 0 brightness

    if(brightnessy > 80 && firstleft == true){   //When the brightness level of the light reaches its max, and its the first time its greater than 120

      EnteredPassword[passDig] = "left";  //Inputs "left" into the EnteredPassword array in element passDig
      passDig++;  //Increases the array element by one
      firstleft = false;  //Sets firstleft to false (to prevent holding in a derection from repeatedly inputing in that direction)
    }

    if(brightnessy <20){  //When the joystick returns to the middle sets firstleft to true
      firstleft = true;
    }
  }
  else  //When brightness y is in the negative direction execute:
  {
    analogWrite(RED, -brightnessy);
        if(-brightnessy > 80 && firstright == true){
      EnteredPassword[passDig] = "right";
      passDig++;
      firstright = false;
    }

    if(brightnessy > -60){
      firstright = true;
    }
  }
  if(brightnessx >= 0)
  {
    analogWrite(BLUE, brightnessx);
    analogWrite(YELLOW, 0);
    if(brightnessx > 80 && firstdown == true){
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
      if(-brightnessx > 80 && firstup == true){
      EnteredPassword[passDig] = "up";
      passDig++;
      firstup = false;      
    }

    if(brightnessx > -60){
      firstup = true;
    }
        
    analogWrite(YELLOW, -brightnessx);
  }

}

void OneStep(bool dir){ //OneStep function that runs the stepper motor moving it forward by one step every time it is called
    if(dir){  //If statement determining the direction of the rotation (positive = clockwise)
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
  }else{  //If false then rotates counterclockwise
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
step_number++;   //Increments the different magnetic fields being activated to keep stepping the motor
  if(step_number > 3){
    step_number = 0;
  }
}

bool PasswordCheck(String pass[], String cor[])   //Function for checking the if the CorrectPassword array and the EnteredPassword array are equal
{
  for (int i = 0; i < 6; i++) 
  {
    if (CorrectPassword[i] != EnteredPassword[i]) 
    {
        return false; //If any element is not equal to the other, return false
    }
        
  }
  return true; //If all elements are equal, the arays are equal return true
}
