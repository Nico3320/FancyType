# **FancyType**

## ANSI-Code Integration

### Mit der Map ANSI[], wurden ANSI-Code sequenzen ganz einfach mit eingebunden. Gib einfach zu ANSI[] einen validen String Parameter (Liste unten), und erhalte den passenden ANSI-Code als string zurück.

<details>
<summary>Valide eingaben für Text Farben änderungen:</summary>

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
<summary>Valide eingaben für Text Hintergrund änderung:</summary>

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
<summary>Valide eingaben für Text Modifikation:</summary>

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
#include "fancytype"

int main() {
    std::cout << ANSI["RED"] << "Roter Text" << ANSI["BOLD"] << "Fetter Roter Text";
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

### ``
