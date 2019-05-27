#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int readData(char* , char*[]);
int testForLetter(char, char*, int);
int menue();
void update(int, char*, char*, int);

int main() {
    int lives, i, finish;
    char wrongLetters[27], rightLetters[27], wordToFind[30], *wordList[100], input;

    printf("Loading words...\n\n\n");
    int words = readData("wordlist.txt", wordList);
    int mode = menue();
    int lettersOfWord = 0;

    lives = 11;
    finish = 0;



	do{
		system("cls");
		// ALLES RESETEN
		for(i = 0; i < 30; i++){
			wrongLetters[i] = '\0';
			rightLetters[i] = '\0';
			wordToFind[i] = '\0';
		}
		// Modus wählen
	    switch (mode){
	        char temp[30];
	        case 1:
	        	srand(time(NULL));
	        	int index = rand() % words;
	        	strcpy(wordToFind, wordList[index]);
	        	
	        	for(i = 0; wordToFind[i] != '\0' && wordToFind[i] != '\n'; i++){
	            	wordToFind[i] = toupper(wordToFind[i]);
	            	rightLetters[i] = '_';
				}
	        	
	        	lettersOfWord = 0;
	        	
	        	while(wordToFind[lettersOfWord] >= 'A' && wordToFind[lettersOfWord] <= 'Z' ){
	        		lettersOfWord++;
				}
	            break;
	
	        case 2:
	            do{
	            	printf("Please insert a word: ");
		            fflush(stdin);
		            fgets(temp, 30, stdin);
		            
		            for(i = 0; temp[i] != '\0' && temp[i] != '\n'; i++){
		            	temp[i] = toupper(temp[i]);
		            	rightLetters[i] = '_';
					}
					finish = 1;
					for(i = 0; temp[i] != '\n' && temp[i] != '\0'; i++){
		            	if(temp[i] < 'A' || temp[i] > 'Z') finish = 0;
					}
				}while(!finish);
				finish = 0;
				
				rightLetters[i] = '\n';
				strcpy(wordToFind, temp);
				lettersOfWord = i;
	            break;
	
	        default:
	            break;
	    }
	    
	    // Das eigentliche Spiel...
	    
	    do{
	    	update(lives, wrongLetters, rightLetters, lettersOfWord);
	    	do{
	    		printf("Please insert a char: ");
	    		fflush(stdin);
	    		scanf("%c", &input);
	    		input = toupper(input);
	    		if(testForLetter(input, wrongLetters, 27)) input = '0';
	    		if(testForLetter(input, rightLetters, 27)) input = '0';
	    		
			}while(input < 'A' || input > 'Z');
			
			if(!testForLetter(input, wordToFind, 27)){ // add letter to wrong letters
				for(i = 0; wrongLetters[i]; i++){}
				wrongLetters[i] = input;
				lives--;
			}else{
				for(i = 0; wordToFind[i]; i++){
					if(wordToFind[i] == input){
						rightLetters[i] = input;
					}
				}
			}
			if(!testForLetter('_', rightLetters, 30)) finish = 1; // Teste ob Word gefunden ist.
			
		}while(!finish && lives);
		system("cls");
		if(finish){
	   		printf("\t\tGLUECKWUNSCH!\n\tDu hast das Wort gefunden!!!");
		}else {
			printf("\t\tVERLOREN!\n\tDu hast leider keine Leben mehr!");
		}
		printf("\n\nMoechtest du nochmal spielen? [Y|N]");
	}while(toupper(getchar()) == 'Y');
	
	
    // Freigeben des Spiechers
    for(i = 0; i < words; i++){
    	free(wordList[i]);
	}
    return 0;
}


int readData(char *path, char *data[]){
    FILE *wordList;
    char buffer[40];
    int i, j;
    int words;

    wordList = fopen(path, "r");

    if (wordList){
        while (fgets(buffer, 40, wordList)){
        	data[i] = (char *) malloc(40*sizeof(char));
        	
        	for(j = 0; buffer[j]; j++){
        		buffer[j] = toupper(buffer[j]);
			}
        	
        	strcpy(data[i], buffer);
            i++;
        }
    }else
        printf("Konnte Datei %s nicht finden", path);
        
	return i;
}

int testForLetter(char letter, char *sequenze, int length) {
	int contains = 0;
	int i = 0;
	
	while (sequenze[i] && !contains){
		if(tolower(sequenze[i]) == tolower(letter)) contains = 1;
		i++;
	}
    return contains;
}

int menue(){
    char input[3];
    int x;
    do{
        printf("Willkommen bei Hangman!\n");
        printf("Bitte waehle eine der folgenden Optionen:\n");
        printf("1 - Bekomme ein zufaelliges Wort aus einer Datei\n");
        printf("2 - Gib ein Wort ein, und lass deine Freunde raten!\n\n\n");
        printf("Waehle bitte deine Option: ");

        fflush(stdin);
        fgets(input, 3, stdin);
        x = atoi(input);
    }while (x < 1 || x > 2);
    return x;
}

void update(int lives, char *wrongLetters, char *rightLetters, int wordSize){
	int i;
	
	system("cls");
	printf("\t\tFIND THE WORD!\n\n\n");
	for(i = 0; i < wordSize; i++){
		printf("%c ", rightLetters[i]);
	}
	printf("%70s: %i\n\n","lives", lives);
	printf("Wrong Letters: ");
	for(i = 0; wrongLetters[i]; i++){
		printf("%c |", wrongLetters[i]);
	}
	printf("\n\n");
}
