#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void readData(char* , char *[]);
int testForLetter(char letter);
int menue();

int main() {
    int lives, i, finish;
    char wrongLetters[30], rightLetters[30], wordToFind[30], *wordList[] = {"Test", "Secret", "Epic"};
    //readData("/home/nicklas/Schreibtisch/Schule/PGR_VD/Linux/Hangman/data/wordlist.txt", wordList);


    int mode = menue();

    lives = 5;
    finish = 0;

    switch (mode){
        char temp[30];
        case 1:
            printf("Comming Soon...");
            finish = 1;
            break;

        case 2:
            printf("Gib bitte ein Wort ein: ");
            fflush(stdin);
            fgets(temp, 30, stdin);
            //toupper(temp);
            printf("%s", toupper('s'));         <-------------
            finish = 1;
            break;

        default:
            printf("Test");
            break;
    }

/*    do{
 *
 *   }while(!finish && lives);
 */
    return 0;
}


void readData(char *path, char *data[]){
    // TODO:
    FILE *wordList;
    char buffer[40];
    int i = 0;

    wordList = fopen(path, "r");

    if (wordList){
        while (fgets(buffer, 40, wordList)){
            //strcpy(data[i], &buffer);
            i++;
        }
    }else
        printf("Konnte Datei %s nicht finden", path);
    for (int j = 0; j < 6; ++j) {
        printf("%s", data[j]);
    }
}

int testForLetter(char letter) {
    return 1;
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
