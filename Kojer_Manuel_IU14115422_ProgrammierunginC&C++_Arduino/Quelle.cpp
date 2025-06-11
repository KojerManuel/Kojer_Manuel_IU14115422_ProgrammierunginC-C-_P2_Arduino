void setup()
 {
  // Starte die serielle Kommunikation mit einer Baudrate von 9600
  Serial.begin(9600);
}

void loop() 
{
  static char inputBuffer[32];  // Puffer zum Speichern der eingegebenen Zeichen
  static byte charIndex = 0;    // Zeiger auf das nächste Zeichen im Puffer

  // Prüfen, ob neue Daten vorhanden sind
  while (Serial.available()) 
{
    char incomingChar = Serial.read();  // Ein einzelnes Zeichen auslesen

    // Wenn ein Zeilenumbruch empfangen wird, haben wir die komplette Eingabe
    if (incomingChar == '\n') 
{
      inputBuffer[charIndex] = '\0';  // Abschließen des Strings
      processExpression(inputBuffer);  // Den Ausdruck analysieren und berechnen
      charIndex = 0;  // Zurücksetzen des Indexes für die nächste Eingabe
    } else if (charIndex < sizeof(inputBuffer) - 1) 
{
      inputBuffer[charIndex++] = incomingChar;  // Zeichen im Puffer speichern
    }
  }
}

void processExpression(char *expr) 
{
  int num1 = 0, num2 = 0;
  char op = 0;

  // Der Ausdruck wird in Operanden und Operator zerlegt
  if (sscanf(expr, "%d %c %d", &num1, &op, &num2) == 3) 
{
    long result = 0;  // Ergebnis der Berechnung
    bool validExpression = true;  // Flag für die Gültigkeit des Ausdrucks

    // Berechnung je nach Operator
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
          validExpression = false;  // Verhindern der Division durch Null
        }
        break;
      default:
        validExpression = false;  // Ungültiger Operator
    }

    // Ergebnis oder Fehlermeldung ausgeben
    if (validExpression) 
{
      Serial.print("Ergebnis: ");
      Serial.println(result);
    } else {
      if (op == '/' && num2 == 0) 
{
        Serial.println("Fehler: Division durch Null ist nicht moeglich.");
      } else 
{
        Serial.println("Fehler: Unbekannter Operator.");
      }
    }
  } else 
{
    // Fehler bei der Formatierung des Ausdrucks
    Serial.println("Fehler: Ungueltiger Ausdruck. Bitte überpruefe deine Eingabe.");
  }
}
