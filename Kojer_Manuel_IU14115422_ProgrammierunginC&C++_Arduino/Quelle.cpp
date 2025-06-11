#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 32

void processExpression(char *expr);

int main() 
{
    char inputBuffer[BUFFER_SIZE];
    
    printf("Einfacher Taschenrechner (Eingabe z. B.: 3 + 5)\n");
    printf("Zum Beenden: Strg+C oder leere Eingabe\n");

    while (1) 
    {
        printf("\nGib einen Ausdruck ein: ");
        
        // Lese Zeile von der Konsole ein
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
            break;  // EOF oder Fehler
        }

        // Zeilenumbruch entfernen, falls vorhanden
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        // Leere Eingabe = Programmende
        if (strlen(inputBuffer) == 0) {
            break;
        }

        processExpression(inputBuffer);
    }

    return 0;
}

void processExpression(char *expr) 
{
    int num1 = 0, num2 = 0;
    char op = 0;

    // Ausdruck parsen
    if (sscanf(expr, "%d %c %d", &num1, &op, &num2) == 3) 
    {
        long result = 0;
        int validExpression = 1;

        switch (op) 
        {
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
            case '/':
                if (num2 != 0) 
                {
                    result = num1 / num2;
                } else {
                    validExpression = 0;
                    printf("Fehler: Division durch Null ist nicht moeglich.\n");
                }
                break;
            default:
                validExpression = 0;
                printf("Fehler: Unbekannter Operator '%c'.\n", op);
                break;
        }

        if (validExpression) {
            printf("Ergebnis: %ld\n", result);
        }
    } else {
        printf("Fehler: Ungueltiger Ausdruck. Bitte Eingabe im Format 'Zahl Operator Zahl'.\n");
    }
}
