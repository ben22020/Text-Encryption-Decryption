#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int TEXT_SIZE = 256;
const int ROTOR_SIZE = 10;
const char ROTOR_VALUES[10] = {7,3,0,1,9,5,2,6,4,8};
const char LETTERS[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                          'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};
int rotor_one, rotor_two, rotor_three;
/*  mod:  Implements a true modulus function
 *  INPUT: original number (a) and dividor (b)
 *  OUTPUT: remainder*/
int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r+ b : r;
}

// incrementRotors: Advances rotor positions by one
void incrementRotors()
{
	rotor_one++;
	if (rotor_one == ROTOR_SIZE){
		rotor_one = 0;
		rotor_two++;
	}
	if (rotor_two == ROTOR_SIZE){
		rotor_two = 0;
		rotor_three++;
	}
	if (rotor_three == ROTOR_SIZE)
		rotor_three = 0;
}

//findCharIndex returns the index of the character provided in the argument, by searching an array until a value is equal to the argument character

int findCharIndex(char letter){
    
    for(int i = 0; i < 27; i++){
        if(letter == LETTERS[i]){
            return i;
        }    
    }
}

//getKey() adds the values of the rotors at the positions given by the variables rotor_one, rotor_two, and rotor_three
int getKey(){
    
    return ROTOR_VALUES[rotor_one] + ROTOR_VALUES[rotor_two] + ROTOR_VALUES[rotor_three];

}

//if the findCharIndex() + the key is less than the size of the LETTERS array, simply return the character at the index findCharIndex() + key.
// else, return the difference between the value of the sum and 27.

char encrypt(char a, int key){
  
  if(findCharIndex(a) + key < 27){
      
      a = LETTERS[findCharIndex(a) + key];
       
    }
    else{
        a = LETTERS[(findCharIndex(a) + key) - 27];
    }
    
    return a;
    
}

// if the value of findCharIndex() - key is greater than 0, return that value. else, return mod((findCharIndex(a) - key), 27)

char decrypt(char a, int key){
    
    if(findCharIndex(a) - key >= 0){
         a = LETTERS[findCharIndex(a) - key];
    }
    else{
         a = LETTERS[mod((findCharIndex(a) - key), 27)];
    }

    return a;
}

int main(int argc, char *argv[])
{
    
    if(argc < 5)
    {
        printf("You tryna play me?!\n");
        return -1;
    }
  
  rotor_one = atoi(argv[1]);
  rotor_two = atoi(argv[2]);
  rotor_three = atoi(argv[3]);
  char inputText[TEXT_SIZE];
  char outputText[TEXT_SIZE];
  
  printf("Rotor #1 position is set to %d \n", rotor_one);
  printf("Rotor #2 position is set to %d \n", rotor_two);
  printf("Rotor #3 position is set to %d \n", rotor_three);
  
  
  
  int i;
  
  if(argv[4][0] == 'e'){//if user enters encryption argument
      
    printf("Please enter text to encrypt\n");
    fgets(inputText, TEXT_SIZE, stdin);
    printf("Text supplied: %s \n", inputText);
     
          for(i = 0; i < strlen(inputText) - 1; i ++){//encrypts the characters one by one for the entire length of the text input by user, then increments the rotor
         
              outputText[i] = encrypt(inputText[i], getKey());
              incrementRotors();
          }
   
   outputText[i+1] = '\0';
   printf("Encrypted message: %s \n", outputText);
  
   }else if(argv[4][0] == 'd'){
      
    printf("Please enter text to decrypt\n");
    fgets(inputText, TEXT_SIZE, stdin);
    printf("Text supplied: %s \n", inputText);   
      
        for(i = 0; i < strlen(inputText) - 1; i ++){//decrypts the characters one by one for the entire length of the text input by user, then increments the rotor
         
            outputText[i] = decrypt(inputText[i], getKey());
            incrementRotors();
      }
        outputText[i + 1] = '\0';
        printf("Decrypted message: %s \n", outputText);
      
    }else{
     
      printf("Invalid encryption/decryption instruction");
    }


    return EXIT_SUCCESS;
}