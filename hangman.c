#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int readData(char* , char*[]);
int testForLetter(char, char*, int);
int menue();

int main() {
    int lives, i, finish;
    char wrongLetters[30], rightLetters[30], wordToFind[30], *wordList[100];

    int mode = menue();
    printf("Loading words...\n\n");
    int words = readData("wordlist.txt", wordList);

    lives = 5;
    finish = 0;

	// Modus wählen
    switch (mode){
        char temp[30];
        case 1:
        	srand(time(NULL));
        	rand()%
            break;

        case 2:
            printf("Gib bitte ein Wort ein: ");
            fflush(stdin);
            fgets(temp, 30, stdin);
            for(i = 0; temp[i]; i++){
            	temp[i] = toupper(temp[i]);
			}
			strcpy(wordToFind, temp);
			printf("%s", wordToFind);
            break;

        default:
            break;
    }
    
    // Das eigentliche Spiel...
    
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
        
    words = i;
        
    for(i--; i >= 0; i--){
		printf("%s", data[i]);
	}
	return words;
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
