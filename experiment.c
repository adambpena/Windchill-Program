#include <stdio.h>
#include <math.h>
#include <string.h>

// char theString[1024];
// char numParseStr[1024]; 
// double digitCount = 0 ;
// double digitCountDeci = 0;
// double theNum;
// int theIndex = 0;
// int isNegative = 0;
// int hasDecimal = 0;

// int main(){
// fgets(theString, sizeof(theString), stdin);

//   for(int i = 0; i < sizeof(theString); i++)
//   {
//     if(theString[i] == '-' && digitCount == 0){
//       isNegative = 1;
//     }

//     if(hasDecimal == 0){
//         if(theString[i] == '.'){
//         hasDecimal = 1;
//         }
//         if(theString[i] == '0' || theString[i] == '1' || theString[i] == '2' || theString[i] == '3' || theString[i] == '4' ||theString[i] == '5' || theString[i] == '6' || theString[i] == '7' || theString[i] == '8' || theString[i] == '9'){
//           digitCount++;
//           numParseStr[theIndex] = theString[i];
//           theIndex++;
//           continue;
//         }
//     }

//     if(hasDecimal == 1){
//       if(theString[i] == '0' || theString[i] == '1' || theString[i] == '2' || theString[i] == '3' || theString[i] == '4' ||theString[i] == '5' || theString[i] == '6' || theString[i] == '7' || theString[i] == '8' || theString[i] == '9'){
//         digitCount++;
//         digitCountDeci++;
//         numParseStr[theIndex] = theString[i];
//         theIndex++;
//         continue;
//       }
//     }
    
//   }

//   int theIndex2 = 0; 
//   digitCount--;

//   if(hasDecimal == 0){
//     for(int j = digitCount; j >= 0; j--){
//       {
//         theNum += ((numParseStr[theIndex2]- 48)*pow(10.0, (digitCount)));

//         theIndex2++;
//         digitCount--;
//       }
//     }
//   }

//   if(hasDecimal == 1){
//     for(int j = digitCount; j >= 0; j--){
//       theNum += ((numParseStr[theIndex2]- 48)*pow(10.0, (digitCount)));

//       theIndex2++;
//       digitCount--;
//     }

//     theNum *= pow(10.0, ((digitCountDeci) * -1));
//   }

//   if(isNegative == 1){
//     theNum *= -1;
//   }

//   printf("%lf\n", theNum);

//   return 0;
// }

//--------------------------------------------

// #include <stdio.h>
// #include <math.h>
// #include <string.h>

// char aString[1024];
// char numParseStr[1024]; 
// double digitCount = 0 ;
// double digitCountDeci = 0;
// double theNum;
// int theIndex = 0;
// int isNegative = 0;
// int hasDecimal = 0;

// A selection of code that converts a string to an integer, unused but a fun experiment

// double stringToInt(char *theString){
//   for(int i = 0; i < sizeof(theString); i++)
//   {
//     if(theString[i] == '-' && digitCount == 0){
//       isNegative = 1;
//     }

//     if(hasDecimal == 0){
//         if(theString[i] == '.'){
//         hasDecimal = 1;
//         }
//         if(theString[i] == '0' || theString[i] == '1' || theString[i] == '2' || theString[i] == '3' || theString[i] == '4' ||theString[i] == '5' || theString[i] == '6' || theString[i] == '7' || theString[i] == '8' || theString[i] == '9'){
//           digitCount++;
//           numParseStr[theIndex] = theString[i];
//           theIndex++;
//         }
//     }

//     if(hasDecimal == 1){
//       if(theString[i] == '0' || theString[i] == '1' || theString[i] == '2' || theString[i] == '3' || theString[i] == '4' ||theString[i] == '5' || theString[i] == '6' || theString[i] == '7' || theString[i] == '8' || theString[i] == '9'){
//         digitCount++;
//         digitCountDeci++;
//         numParseStr[theIndex] = theString[i];
//         theIndex++;
//       }
//     }
    
//   }

//   int theIndex2 = 0; 
//   digitCount--;

//   if(hasDecimal == 0){
//     for(int j = digitCount; j >= 0; j--){
//       {
//         theNum += ((numParseStr[theIndex2]- 48)*pow(10.0, (digitCount)));

//         theIndex2++;
//         digitCount--;
//       }
//     }
//   }

//   if(hasDecimal == 1){
//     for(int j = digitCount; j >= 0; j--){
//       theNum += ((numParseStr[theIndex2]- 48)*pow(10.0, (digitCount)));

//       theIndex2++;
//       digitCount--;
//     }

//     theNum *= pow(10.0, ((digitCountDeci) * -1));
//   }

//   if(isNegative == 1){
//     theNum *= -1;
//   }

//   printf("%lf\n", theNum);
//   return theNum;
// }

//---------------------------------------------------------

char aString[1024];
char numStr[254];
  double digitCount;
  int strParseIndex = 0;
  int numParseIndex = 0;
  double returnNum;
  int digitCountDeci = 0;
  int isNegative = 0;
  int hasDecimal = 0;


double strToNum(char *getStr){
  

  for(int i=0; i < sizeof(getStr); i++){
    if(getStr[i] == '-' && digitCount == 0){
      isNegative = 1;
    }

    if(hasDecimal == 0){
      if(getStr[i] == '.'){
          hasDecimal = 1;
          }

      if(getStr[i] == '0' || getStr[i] == '1' || getStr[i] == '2' || getStr[i] == '3' || getStr[i] == '4' || getStr[i] == '5' || getStr[i] == '6' || getStr[i] == '7' || getStr[i] == '8' || getStr[i] == '9'){
        digitCount++;
        numStr[strParseIndex] = getStr[i];
        strParseIndex++; 
      }
    }

    if(hasDecimal == 1){
      if(getStr[i] == '0' || getStr[i] == '1' || getStr[i] == '2' || getStr[i] == '3' || getStr[i] == '4' ||getStr[i] == '5' || getStr[i] == '6' || getStr[i] == '7' || getStr[i] == '8' || getStr[i] == '9'){
        digitCount++;
        digitCountDeci++;
        numStr[strParseIndex] = getStr[i];
        strParseIndex++;
      }
    }
   
  }

  if(digitCount == 0){
    returnNum = 0;
    return returnNum;
  }

  digitCount--;  

  for(int j=digitCount; j>=0; j--){
      returnNum += (numStr[numParseIndex]-48)*pow(10.0, digitCount);
      numParseIndex++;
      digitCount--;

      if(hasDecimal == 1){
        returnNum *= pow(10.0, ((digitCountDeci) * -1));
      }
    }

  return returnNum;
}

int main(){
  fgets(aString, sizeof(aString), stdin);

  double theNumber = strToNum(aString);

  printf("%lf\n", theNumber);

  return 0;
}
