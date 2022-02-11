//Title:   Windchill Assessing Program
//Name:    Adam Pena
//Date:    9/26/21

#include <stdio.h>
#include <math.h>
#include <string.h>

#define fahrlow -10.0                         //lower limit of fahrenheit as macro
#define fahrhigh 45.0                         //upper limit of fahrenheit as macro
#define celslow ((-10.0-32.0)*(5.0/9.0))    //lower limit of celsius as macro (~-23.33)
#define celshigh ((45.0-32.0)*(5.0/9.0))    //upper limit of celsius as macro (~7.22)

char name[254];         // Space created for a name as a string
char unitString[254];   // Space created to handle string input when expecting char
char unit;              // Char parsed from user input for unit type
char tempStr[254];      // Temp number entered by user as string (input mismatch handling, used with strToNum function)
double temp;            // Parsed temp string converted to double and stored here
char windSpeedStr[254]; // Wind speed entered by user as string (input mismatch handling)
double windSpeed;       // Parsed windspeed string converted to double and stored here
double windChill;       // Calculated wind chill
char goAgainStr[254];   // Initirally a string for input mismatch handling
char goAgain;           // A character to store yes/no response to continue program, pulled from goAgainStr
int goAgainNum = 1;     // A "boolean" based on character entered for goAgain. Controls loop of whole program in main

//Relevant Functions
int toCelsConverter(double fahrenNumCC)    //To convert celsius to fahrenheit
{
  double celsNumCC = ((fahrenNumCC - 32)*(5/9));
  return celsNumCC;
}

int toFahrenConverter(double celsNumFC)    //To convert fahrenheit to celsius
{
  double fahrenNumFC = (1.8*celsNumFC) + 32;
  return fahrenNumFC;
}

void trimExcess(char * str) // Function to remove trailing from name and attach a null character for nice formatting
{
  int index = -1;
  int i = 0;

  while(str[i] != '\0') //parse the string index by index looking for a large gap leading up to a null-terminated character. Places a null terminating character before that, shortening the string for printf format
  {
      if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
      {
        index= i;
      }
      i++;
  }
  str[index + 1] = '\0';
}

double strToNum(char *getStr){ // Function to parse a string and return a number (double). Used to handle scans where a number is expected but user could enter chars.
  char numStr[254];            // Str used to store numbers
  double digitCount = 0;       // Keep track of num of ints in string
  int strParseIndex = 0;       // Used to append nums sequentially onto numStr
  int numParseIndex = 0;       // Used to go through numStr sequentially
  double returnNum = 0;            // Num to be returned
  int digitCountDeci = 0;      // Counts number of digits after decimal
  int isNegative = 0;          // "boolean" int to keep track of whether num can be called negative
  int hasDecimal = 0;          // "boolean" int to keep track of whether num has a decimal
  int funkyInput = 0;          // "boolean" keeping track of whether chars were entered

  for(int i=0; i < strlen(getStr); i++){

    if(funkyInput == 0){ // If a letter or non-number-oriented character is in the string, it is funky
      if(getStr[i] != '0' && getStr[i] != '1' && getStr[i] != '2' && getStr[i] != '3' && getStr[i] != '4' && getStr[i] != '5' && getStr[i] != '6' && getStr[i] != '7' && getStr[i] != '8' && getStr[i] != '9' && getStr[i] != '.' && getStr[i] != '-' && getStr[i] != '\0' && getStr[i] != ' ' && getStr[i] != '\n'){
        funkyInput = 1;
      }
    }

    if(getStr[i] == '-' && digitCount == 0 && hasDecimal == 0){ // If a hyphen is detected before any number or decimal, it will be negative
      isNegative = 1;
    }

    if(hasDecimal == 0){    // Handle thusly if no decimal
      if(getStr[i] == '.'){ // If decimal hasDecimal == 1
          hasDecimal = 1;
          }

      if(getStr[i] == '0' || getStr[i] == '1' || getStr[i] == '2' || getStr[i] == '3' || getStr[i] == '4' ||getStr[i] == '5' || getStr[i] == '6' || getStr[i] == '7' || getStr[i] == '8' || getStr[i] == '9'){
        digitCount++;     // Num found, increment count
        numStr[strParseIndex] = getStr[i]; // Append num at i to numStr
        strParseIndex++;  // Go to next index of numStr
      }
    }

    if(hasDecimal == 1){  //Handle thusly after decimal found
      if(getStr[i] == '0' || getStr[i] == '1' || getStr[i] == '2' || getStr[i] == '3' || getStr[i] == '4' ||getStr[i] == '5' || getStr[i] == '6' || getStr[i] == '7' || getStr[i] == '8' || getStr[i] == '9'){
        digitCount++; 
        digitCountDeci++; // Keep track of nums after decimal
        numStr[strParseIndex] = getStr[i];
        strParseIndex++;
      }
    }
  }

  if((int) digitCount == 0 && funkyInput == 1){ //If its all weird chars and no numbers
    returnNum = 0;
    printf("Your input had many unexpected characters, defaulted input to 0.\n");
    return returnNum;
  }

  digitCount--; // Offset count of numbers for exponentiating

  for(int j = digitCount; j >= 0; j--){
      returnNum += (numStr[numParseIndex]-48)*pow(10.0, digitCount); // Think scientific notation: (num * 10^3) + (nextNum * 10^2) +... etc
      numParseIndex++;
      digitCount--; // Keep going until num* 10^0
    }

  if(hasDecimal == 1){ // If it has a decimal, scoot decimal in and over by amount of digits after decimal. Again, scientific notation: 14,562 * 10^(-3) = 14.562)
        returnNum *= pow(10.0, ((digitCountDeci) * -1));
      }

  if(isNegative){ //Make negative if its negative
    returnNum *= (-1);
  }

  if(digitCount != 0 && funkyInput == 1){ // If there are numbers but also characters, let the user know what happened
    printf("Your input had some unexpected characters, but your input was parsed for numbers and relevant symbols. It was translated to approximately %.2lf.\n", returnNum);

    return returnNum;
  }

  if(digitCount != 0 && funkyInput == 1){ // If there are numbers but also characters, let the user know what happened
    printf("Your input had some unexpected characters, but your input was parsed for numbers and relevant symbols. It was translated to approximately %.2lf.\n", returnNum);
    
    return returnNum;
  }
  
  return returnNum;
}

void getName(){  //get the name and trim excess                             
  fgets(name, sizeof(name), stdin); 
  trimExcess(name);
}

//Get valid unit 
void getUnit(){   
    while(1){
    
    char firstLetter;                             //char variable called first letter. going to store first letter of unitString

    fgets(unitString, sizeof(unitString), stdin); //reads unit as a string in case user puts in a string of characters rather than just c or f

    strncpy(&firstLetter, unitString, 1);         //creates a copy of the first letter of unitString into firstLetter

    if(strlen(unitString) > 2){                   //if unitString is just a char & null-terminating char (length 2)
      if(firstLetter == 'c' || firstLetter == 'C' || firstLetter == 'f' || firstLetter == 'F'){  //Check if unit is invalid, loop if not
        if(firstLetter == 'c' || firstLetter == 'C'){ //if first letter of input string is c, unit = celsius
          printf("I'm assuming you meant 'C' for celsius!\n");
          unit = 'c';
        }

        if(firstLetter == 'f' || firstLetter == 'F'){ //if first letter of input string is f, unit = fahrenheit
          printf("I'm assuming you meant 'F' for fahrenheit!\n");
          unit = 'f';
        }
        break;
      }
    }
    if(firstLetter == 'c' || firstLetter == 'C' || firstLetter == 'f' || firstLetter == 'F'){  //If unit is inputted as proper char, unit = f or c respectively
        if(firstLetter == 'c' || firstLetter == 'C'){
              unit = 'c';
        }

        if(firstLetter == 'f' || firstLetter == 'F'){
          unit = 'f';
        }
        break;
      }
    else{ //if the user inputs a char or string of chars not starting with f or c, loop and reprompt for input
      printf("That is an invalid entry for unit, f for fahrenheit c for celsius:\n");
      continue;
    }
  }
}

// getTemp
void getTemp(){
while(1){
    fgets(tempStr, sizeof(tempStr), stdin);     // Scan the temperature as a string (to handle input mismatch)
    temp = strToNum(tempStr);                   // Parse the string for numbers

      if(unit == 'f' || unit == 'F'){           //Check bounds for fahrenheit if unit = f
        if(temp < fahrlow || temp > fahrhigh){
          printf("Temperature out of range, try again (-10 to 45):\n");
        }
        
        else{
          break;
        }
      }

      if(unit == 'c' || unit == 'C'){          //Check bounds for celsius if unit = c
        if(temp < celslow || temp > celshigh){
          printf("Temperature out of range, try again (approx. -23.3 to 7.2):\n");
        }

        else{
          break;
        }
      }
    }
}

// getWindSpeed, basically identical logic to getTemp
void getWindSpeed(){
    while(1){
      fflush(stdin);
      fgets(windSpeedStr, sizeof(windSpeedStr), stdin);
      windSpeed = strToNum(windSpeedStr);

      if(windSpeed >= 0 && windSpeed <= 25){
        break;
      }
        
      else{
        printf("Invalid wind speed, please try again:\n");
        continue;
      }
    }
  }
    // Calculate the wind chill:
void calcWindChill(){

  windChill = 13.12 + (0.6215*(toCelsConverter(temp)))-((11.37) * (pow(windSpeed, 0.16))); 

  if(unit == 'f' || unit == 'F'){  //use converter if fahrenheit (formula in pdf given with c val)
    windChill = toFahrenConverter(windChill);
    }
    
}

// Display message according to windChill and unit. 
void displayPrompt(){
    //Windchill if fahrenheit..
    if(unit == 'f' || unit == 'F'){
      if(windChill > 32){
        printf("Well %s, the temperature considering windchill factor is %0.2f F, get out and do something!\n", name, windChill);
      }

      else if(windChill > 10 && windChill < 32){
        printf("%s, the temperature considering windchill factor is about %0.2lf F, consider layering up.\n", name, windChill);
      }

      else if(windChill < 10){
        printf("%s, the windchill factor is %0.2lf F. Are you curious about cryogenic freezing?\n", name, windChill);
      }
    }
    
    //Windchill if celsius..
    else if(unit == 'c' || unit == 'C'){
      if(windChill > toCelsConverter(32.0)){
        printf("Well %s, the temperature considering windchill factor is %0.2lf C, get out and do something!\n", name, windChill);
      }

      else if(windChill > toCelsConverter(10.0) && windChill < toCelsConverter(32.0)){
        printf("%s, the temperature considering windchill factor is about %0.2lf, consider layering up.\n", name, windChill);
      }

      else if(windChill < toCelsConverter(10.0)){
        printf("%s, the windchill factor is %0.2lf C. Are you curious about cryogenic freezing?\n", name, windChill);
      }
    }
  }

void getContinueAns(){    //Ask the user if they want to continue
  while(1){
    char firstLetter;                             //char variable called first letter. going to store first letter of goAgainStr

    fgets(goAgainStr, sizeof(goAgainStr), stdin); //reads unit as a string in case user puts in a string of characters rather than just c or f

    strncpy(&firstLetter, goAgainStr, 1);         //creates a copy of the first letter of unitString into firstLetter


    if(strlen(goAgainStr) > 2){                   //if goAgainStr String is just a char & null-terminating char (length 2)
      if(firstLetter == 'y' || firstLetter == 'Y' || firstLetter == 'n' || firstLetter == 'N'){  //Check if entry is invalid, loop if not
        if(firstLetter == 'y' || firstLetter == 'Y'){ //if first letter of input string is y, goAgain = yes
          printf("I'm assuming you meant 'Y' for yes!\n");
          goAgain = 'y';
        }

        if(firstLetter == 'n' || firstLetter == 'N'){ //if first letter of input string is n, goAgain = no
          printf("I'm assuming you meant 'n' for no!\n");
          goAgain = 'n';
        }
        break;
      }
    }
    
    if(firstLetter == 'y' || firstLetter == 'Y' || firstLetter == 'n' || firstLetter == 'N'){  //If goAGain is inputted as proper char, goAgain = y or n respectively
        if(firstLetter == 'y' || firstLetter == 'Y'){
              goAgain = 'y';
        }

        if(firstLetter == 'n' || firstLetter == 'N'){
          goAgain = 'n';
        }
        break;
      }

    if(goAgain == 'n' || goAgain == 'N'){
      goAgainNum = 0;                   // Cut program if no
      printf("Enjoy the weather!\n");   // Bye!
      break;
    }

    else{ //if the user inputs a char or string of chars not starting with f or c, loop and reprompt for input
      printf("That is an invalid entry, try again. 'Y' for yes or 'N' for no:\n"); // Re-prompt invalid input
      continue;
    }
  }
}  


int main(void) {
  while(goAgainNum){    // Code nested in a while loop, to repeat program if user wants to. goAgainNum

    //Get username:
    printf("What is your name?\n");  
    getName();
        
    //Get the unit type:
    printf("Enter a unit, F for fahrenheit or C for celsius (will go off the first letter of any entry): \n");  
    getUnit();
      
    //Get valid temperature 
    printf("Enter the temperature in your unit (Will parse for numbers)\n");
    getTemp();
      
    //Get the wind speed: 
    printf("Enter your wind speed in m/s (A letter will default to 0): \n");    
    getWindSpeed();
    
    //Calculate Wind Chill 
    calcWindChill();

    //Show temperature dependent prompt
    displayPrompt();
      
    //Ask the user if they'd like to go again
    printf("Do you want to calculate another windchill? (y or n, will parse first letter of input for relevant answer)");
    getContinueAns();

    if(goAgain == 'N' || goAgain == 'n'){
      goAgainNum = 0; // Because goAgainNum == 0, main while loop will stop now return 0, and end program
      printf("See you later!");
    }

    else{
      continue;
    }
  } 
  return 0;
}
