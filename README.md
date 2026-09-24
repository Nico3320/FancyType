# **FancyType**

## ANSI-Code Integration

Basic ANSI-codes sind in der Map ANSI gespeichert. Mögliche String-Inputs unten. 

<details>
<summary>Text Farben ändern:</summary>

* BLACK
* RED
* GREEN
* YELLOW
* BLUE
* MAGENTA
* CYAN
* WHITE

* BRIGHT_BLACK
* BRIGHT_RED
* BRIGHT_GREEN
* BRIGHT_YELLOW
* BRIGHT_BLUE
* BRIGHT_MAGENTA
* BRIGHT_CYAN
* BRIGHT_WHITE

</details>

<details>
<summary>Text Hintergrund ändern:</summary>

* BG_BLACK
* BG_RED
* BG_GREEN
* BG_YELLOW
* BG_BLUE
* BG_MAGENTA
* BG_CYAN
* BG_WHITE

* BG_BRIGHT_BLACK
* BG_BRIGHT_RED
* BG_BRIGHT_GREEN
* BG_BRIGHT_YELLOW
* BG_BRIGHT_BLUE
* BG_BRIGHT_MAGENTA
* BG_BRIGHT_CYAN
* BG_BRIGHT_WHITE

</details>

<details>
<summary>Text Modifizieren:</summary>

* BOLD
* DIM
* ITALIC
* UNDERLINE
* BLINK
* REVERSE
* HIDDEN
* STRIKETHROUGH

* RESET

</details>

*Anwendungs Beispiel*

```
#include <iostream>
#include "fancytype.cpp"

int main() {
    std::cout << ANSI["RED"] << "Roter Text" << ANSI["BOLD"] << "Fetter Roter Text" << ANSI["RESET"] << "Normaler Text";
}
```

## Klassen

### COLOR
Die COLOR Klasse nimmt und hält eine Farbe, aufgeteilt in ihre RGB-Dezimal Werte.
Objekte der Klasse enthalten 3 Attribute, jeweils einen pro Farbwert:

```
int r = 255;
int g = 255;
int b = 255;
```

Ein COLOR-Objekt kann in verschiedenen FancyType Funktionen eingefügt werden, aber auch einfach in das cout.

*Anwendungs Beispiel*

```
#include <iostream>
#include "fancytype.cpp"

int main() {
    COLOR color1(255,0,255);
    std::cout << color1 << "Farbiger Text!";
}
```

Um die Farbe anzupassen ganz einfach die Attribute ändern, oder mit `color1.set_color(int r, int g, int b)`

### BORDER
Die BORDER Klasse ist an sich nur sinnvoll in eigener Benutzung, oder in Benutzung mit der "bordered_text()" Funktion.

Sie hält in eigenen Attributen die Eigenschaften eines Rahmens.
- char (Standart '%')
- - top    -> Die obere Leiste eines Rahmens
- - bottom -> Die untere Leiste eines Rahmens
- - left   -> Die Linke Seite eines Rahmens
- - right  -> Die Rechte Seite eines Rahmens
- - corner -> Die Ecken eines Rahmens
- bool (Standart true)
- - strike -> Entscheidet ob der Rahmen Durchgestrichen ist
- - bold   -> Entscheidet ob der Rahmen Dick ist
- COLOR (Standart Weiß)
- - color  -> Setzt die Farbe vom Rahmen

## Funktionen

### `std::string color_code(int r, int g, int b`
Nimmt Parameter im Wert von 0-255 und bildet daraus eine Farbe in form von ANSI-Code und gibt sie als String zurück

*Anwendungs Beispiel*

```
#include <iostream>
#include "fancytype.cpp"

int main() {
    std::cout << color_code(255, 255, 0) << "Dein Farbiger Text hier";
}
```

### `mod(std::vector<std::string> mods)`
Nimmt ein Feld von Konsolen Modifikationen und gibt sie sofort zur Konsole aus.

*Anwendungs Beispiel*

```
#include <iostream>
#include "fancytype.cpp"

int main() {
    mod({"RED", "BOLD"});
    std::cout << "Fetter Roter Text!";

    mod({"RESET"});
    std::cout << "Normaler Text";
}
```

### `line(int size, COLOR color, std::string pieces)`
Druckt eine linie in die Konsole.
- size für die Länge
- color(optional) für die Farbe der Line
- pieces für das Linien Stück

*Anwendungs Beispiel*

´´´
#include <iostream>
#include "fancytype.cpp"

int main() {
    line(5, COLOR(255,255,255), "="); // -> "====="
    line(5, "=");                     // -> "=====" genau gleich
    line(5, "!=");                    // -> "!=!=!=!=!="
}
´´´

### `headLine(COLOR color, char piece)`
(COLOR Optional)
Schreibt eine Linie, die sich auf die Ganze Konsolen-Breite anpasst, bestehend aus einem char.

*Anwendungs Beispiel*
```
#include <iostream>
#include "fancytype.cpp"

int main() {
    headLine('=');
    // -> ...=========...
    headLine('+');
    // -> ...+++++++++...
    
    headLine(COLOR(0,255,0), '=');
    // -> ...=========... (Aber in Grün)
}
```

### `void header(std::string text, COLOR color, char piece, int margin)`
(COLOR Optional)
Schreibt zuerst eine anzahl an "piece" in der Menge von "margin"
Danach kommt "text", unsere Überschrift
Und der Rest Wird aufgefüllt mit "piece"

*Anwendungs Beispiel*
```
#include <iostream>
#include "fancytype.cpp"

int main() {
    header("Topic", '=', 5);
    // -> =====Topic================...

    header("Topic", COLOR(255,0,0), '=', 5);
    // -> =====Topic================... (Aber in Rot)
}
```

### `process(std::string str)`
Produziert einen funktionellen String aus einem Normal-lesbaren String

- '%' Um eine Modifikation hinzuzufügen
- - Nimmt als Modifikation genau das was nach dem %, und vor dem nächsten ' ' steht.
- - Muss eine Valide Modifikation aus den Oberen Listen sein

- '$' Um einen Farb-Code hinzuzufügen
- - Nimmt als Farb Code das was durch ein nicht-zahl-zeichen getrennt ist. <br> Kann so aussehen: $255 255 0 aber auch so $255,255,0 oder auch so $255q255q0

*Anwendungs Beispiel*
```
#include <iostream>
#include "fancytype.cpp"

int main() {
    std::string text1 = process("Blanker Text, %RED Roter Text %BOLD Fetter Roter Text");
    // text1 -> "Blanker Text, \033[31mRoter Text \033[1mFetter Roter Text"

    std::string text2 = process("$255,0,255 Pinker Text");
    // text2 -> "\033[38;2;255;0;255mPinker Text"

    std::cout << text1 << " " << text2;
    // -> "Blanker Text, Roter Text Fetter Roter Text Pinker Text"
}
```

### `print(std::string str)`
Druckt den String und lässt gleichzeitig auch "process()" davor laufen sodass auch Modifikationen möglich sind.

### `println(std::string str)`
Gleich wie "print()" nur mit Zeilenumbruch

### `bordered_text(std::string text, BORDER border, int paddingVertical, int paddingHorizontal)`
Druckt Text innerhalb eines Rahmens.
- text ist der gedruckte text
- border ist ein Objekt der Klasse BORDER, der das border-design hält
- paddingVertical ist der Vertikale abstand zwischen Text und Rahmen
- paddingHorizontal ist der Horizontale abstand zwischen Text und Rahmen

*Anwendungs Beispiel*
```
#include <iostream>
#include "fancytype.cpp"

int main() {
    bordered_text("Mein Text!", BORDER(), 1, 1);
    //   %%%%%%%%%%%%%%
    //   %            %
    //   % Mein Text! %
    //   %            %
    //   %%%%%%%%%%%%%%
}
```
