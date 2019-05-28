#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define WORD_SIZE 10

// Deklarieren von Funktionen
int readData(char* , char*[]); // Einlesen der "wordlist.txt"
int testForLetter(char, char*, int); // Testet ob ein Buchstabe in einem String vorhanden ist
int menue(); // Das Menue des Spieles (Auswahl von Single und Mulitplayer)
void update(int, char*, char*, int); // Die ausgabe des Aktuellen Spielfeldes
void selectionsort(int, char[]); // Sortieren 

int main() {
	// Deklarierne von Variablen
    int words, lives, i, finish, lettersOfWord, mode;
    char wrongLetters[27], rightLetters[27], wordToFind[WORD_SIZE], *wordList[100], temp[WORD_SIZE], input;

    lettersOfWord = 0;
    words = readData("wordlist.txt", wordList); // Lese Wörter aus Datei ein
	if(!words) return words;
	do{
		system("cls");
    	lives = 11;
		finish = 0;
		
		// ALLES RESETEN
		for(i = 0; i < WORD_SIZE; i++){
			wordToFind[i] = '\0';
			temp[i] = '\0';
		}
		for(i = 0; i < 27; i++){			
			wrongLetters[i] = '\0';
			rightLetters[i] = '\0';
		}
		// Modus wählen
		mode = menue();
	    switch (mode){
	        case 1: // Zufalls-Wort aus "wordlist.txt" (Singleplayer)
	        	// Ein Zufällieges Wort in "wordToFind" Speichern.
	        	srand(time(NULL));
	        	int index = rand() % words;
	        	strcpy(wordToFind, wordList[index]);
	        	
	        	// Für jeden Buchstaben einen "_"
	        	// Wortlänge herrausfinden und speichern
	        	for(lettersOfWord = 0; wordToFind[lettersOfWord] != '\0' && wordToFind[lettersOfWord] != '\n'; lettersOfWord++){
	            	wordToFind[lettersOfWord] = toupper(wordToFind[lettersOfWord]);
	            	rightLetters[lettersOfWord] = '_';
				}
	            break;
	
	        case 2: // Benutzereingabe einen Wortes (Multiplayer)
	            do{
	            	// Wort einlesen
					finish = 1;
	            	printf("Bitte gib ein Wort ein: ");
		            fflush(stdin);
		            fgets(temp, WORD_SIZE, stdin);
		            // Testen ob Wort zugelassene unzugelassen Buchstaben hat (Zugelassene Buchstaben [A-Z])
					for(i = 0; temp[i] != '\n' && temp[i] != '\0'; i++){
						temp[i] = toupper(temp[i]);
		            	if(temp[i] < 'A' || temp[i] > 'Z'){
		            		finish = 0;	
		            		printf("%c\n", temp[i]);
						} 
					}
				}while(!finish); // Wiederhole solange, bis Wort zugelassen ist
				
		        // Für Buchstabe in Wort ein "_"
		        for(i = 0; temp[i] != '\0' && temp[i] != '\n'; i++){
		           	rightLetters[i] = '_';
				}
				rightLetters[i] = '\0'; // Den String sicherheitshalber noch mal Manuell beenden
				strcpy(wordToFind, temp); // Speichern des Wortes in "wordToFind"
				lettersOfWord = i; // Länge des Wortes Speichern
	            break;
	            
	        default:break;
	    }
	    
	    // Das eigentliche Spiel...
	    finish = 0;
	    do{
	    	// Gebe das aktuelle Spielfeld aus
	    	update(lives, wrongLetters, rightLetters, lettersOfWord);
	    	
	    	do{
	    		// Lese Buchstaben von User ein
	    		printf("Bitte gib einen Buchstaben ein: ");
	    		fflush(stdin);
	    		scanf("%c", &input);
	    		input = toupper(input); // Formatiere eingabe zu Großbuchstabe
	    		if(testForLetter(input, wrongLetters, 27)) input = '0'; // Teste ob der Buchstabe schon mal vorgekommen ist
	    		if(testForLetter(input, rightLetters, 27)) input = '0'; // Teste ob der Buchstabe schon mal vorgekommen ist
			}while(input < 'A' || input > 'Z'); // Wiederhohle solange die eingabe unzulässig ist (Eingabe außerhalb von [A-Z])
			
			// Teste ob Buchstabe gesucht wird oder nicht
			if(!testForLetter(input, wordToFind, 27)){
				// Aktuallisiere die Falschbuchstabenliste
				/*
				Zählen bis jetzt Falscher Eingaben und füge die neue dann hinzu
				*/
				for(i = 0; wrongLetters[i]; i++){}
				wrongLetters[i] = input;
				selectionsort(i+1, wrongLetters); // Sortieren der Buchstaben
				lives--; // Ziehe ein Leben ab
			}else{
				for(i = 0; wordToFind[i]; i++){ // Ersetze die "_" mit dem richtiegen Buchstaben
					if(wordToFind[i] == input){
						rightLetters[i] = input;
					}
				}
			}
			if(!testForLetter('_', rightLetters, WORD_SIZE)) finish = 1; // Teste ob Wort gefunden ist.
			
		}while(!finish && lives); // Wiederhohle solange nicht fertig oder keine Leben mehr
		system("cls");
		if(finish){ // Wenn keine Leben mehr vorhanden sind -> Verloren
	   		printf("\t\tGLUECKWUNSCH!\n\tDu hast das Wort gefunden!!!");
		}else { // Sonst -> Gewonnen
			printf("\t\tVERLOREN!\n\tDu hast leider keine Leben mehr!");
		}
		printf("\n\nMoechtest du nochmal spielen? [Y|N]");
		fflush(stdin);
	}while(toupper(getchar()) == 'Y'); // Wiederhohle solange user noch spielen möchte
	
	
    // Freigeben des Spiechers
    for(i = 0; i < words; i++){
    	free(wordList[i]);
	}
    return 0;
}


int readData(char *path, char *data[]){ 
	// Deklarieren
    FILE *wordList;
    char buffer[40];
    int i = 0, j = 0;
    int words;
	// Öffnen der Datei im lese modus
    wordList = fopen(path, "r");
    if (wordList){ // Prüfe auf existends der Datie
        while (fgets(buffer, 40, wordList)){ // Einlesen eine Zeile
        	data[i] = (char *) malloc(40*sizeof(char)); // Reservieren des Speichers für die Wörter
        	
        	for(j = 0; buffer[j] && buffer[j] != '\n'; j++){ // Bearbeitung der Buchstaben
        		buffer[j] = toupper(buffer[j]);
        		if(buffer[j] < 'A' || buffer[j] > 'Z'){  // Überprüfe auf unerlaubte Zeichen
        			system("cls");
        			printf("ERROR: Ein unerwartetes Zeichen wurde in \"wordlist.txt\" gefunden. (Zeile %i > '%c')\n", i+1, buffer[j]);
        			printf("\tPruefe ob alle eingaben korrekt sind.\n");
        			printf("\tEs sind nur Buchstaben des Englischen Alphabetes erlaubt [A-Z]!");
        			return 0;
				}
			}
        	strcpy(data[i], buffer); // Kopiere bearbeitete eingabe in "data[i]"
            i++;
        }
    }else
        printf("Konnte Datei %s nicht finden", path);
        
	return i;
}

int testForLetter(char letter, char *sequenze, int length) {
	int i = 0;
	while (sequenze[i]){ // Gehe jeden einzelnen Buchstaben im String durch
		if(tolower(sequenze[i]) == tolower(letter)) return 1; // Wenn vorhanden -> gebe 1 zurück
		i++;
	}
    return 0; // Wenn buchstabe nicht vorhanden -> Gebe 0 zurück
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
        fgets(input, 3, stdin); // Lese eingabe ein ( Als Buchstaben ) 
        x = atoi(input); // Wandle eingabe in Zahl um
        
    }while (x < 1 || x > 2); // Wiederhohle solange eingabe nicht gültig
    return x;
}

void update(int lives, char *wrongLetters, char *rightLetters, int wordSize){
	int i;
	
	system("cls");
	printf("\t\tFinde das Wort!\n\n\n");
	for(i = 0; i < wordSize; i++){ // Gebe Wort aus (Mit "_" und den Buchstaben) Bsp.: "W _ R T"
		printf("%c ", rightLetters[i]);
	}
	printf("%70s: %i\n\n","Leben", lives); // Gebe aktuelle Leben aus
	printf("Falsche Buchstaben: ");
	for(i = 0; wrongLetters[i]; i++){ // Gebe alle Buchstaben die Falsch eingegeben wurden aus
		printf("%c | ", wrongLetters[i]);
	}
	printf("\n\n");
}

void selectionsort(int anzahl, char daten[]){
    int i, k, t, min;

    for( i = 0; i < anzahl-1; i++){
        min = i;
        for( k = i+1; k < anzahl; k++){
            if( daten[k] < daten[min])
                min = k;
        }

        t = daten[min];
        daten[min] = daten[i];
        daten[i] = t;
    }
}
