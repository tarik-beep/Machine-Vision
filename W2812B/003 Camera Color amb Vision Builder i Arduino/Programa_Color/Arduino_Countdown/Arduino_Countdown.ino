#include <FastLED.h>

#define LED_PIN     3   // Pin on està conectat el DIN de la matriu
#define MATRIX_WIDTH  16 // LED's d'amplada de la matriu
#define MATRIX_HEIGHT 16 // LED's d'altura de la matriu
#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT) // Numero total de LED's
#define BRIGHTNESS 100 // Brillantor de la matriu 

CRGB leds[NUM_LEDS];//Crea un array on cada element és un LED RGB que pots controlar el color de cada LED

// Mapeig de la matriu (dependrà de la connexió)
#define XY(x, y) ((y) * MATRIX_WIDTH + (x)) // Passa de coordenades x,y a posició de l'array

// Definim els colors bàsics
// Colors:
#define BLACK CRGB(0, 0, 0)
#define WHITE CRGB(255, 255, 255)
#define RED CRGB(255, 0, 0)
#define GREEN CRGB(0, 128, 0)
#define BLUE CRGB(0, 0, 255)
#define YELLOW CRGB(255, 255, 0)
#define ORANGE CRGB(255, 165, 0)
#define PURPLE CRGB(128, 0, 128)
#define PINK CRGB(255, 192, 203)
#define BROWN CRGB(165, 42, 42)
#define GRAY CRGB(128, 128, 128)


// Definim el numero1 en una matriu de 16x16
const CRGB numero1[16][16] = {
{ BLACK, BLACK, BLACK, BLACK, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK},
{ BLACK, BLACK, BLACK, YELLOW, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, YELLOW, BLACK, BLACK, BLACK},
{ BLACK, BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK, BLACK},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, WHITE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ BLACK, BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK, BLACK},
{ BLACK, BLACK, BLACK, YELLOW, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, YELLOW, BLACK, BLACK, BLACK},
{ BLACK, BLACK, BLACK, BLACK, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK}
};

// Definim el numero2 en una matriu de 16x16
const CRGB numero2[16][16] = {
{ BLACK, BLACK, BLACK, BLACK, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK},
{ BLACK, BLACK, BLACK, YELLOW, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, YELLOW, BLACK, BLACK, BLACK},
{ BLACK, BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK, BLACK},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, WHITE, PURPLE, PURPLE, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, WHITE, PURPLE, PURPLE, PURPLE, WHITE, WHITE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, WHITE, WHITE, WHITE, PURPLE, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, WHITE, WHITE, WHITE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, PURPLE, WHITE, WHITE, WHITE, WHITE, PURPLE, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ BLACK, BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK, BLACK},
{ BLACK, BLACK, BLACK, YELLOW, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, YELLOW, BLACK, BLACK, BLACK},
{ BLACK, BLACK, BLACK, BLACK, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK}
};

// Definim el numero3 en una matriu de 16x16
const CRGB numero3[16][16] = {
{ BLACK, BLACK, BLACK, BLACK, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK},
{ BLACK, BLACK, BLACK, YELLOW, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, YELLOW, BLACK, BLACK, BLACK},
{ BLACK, BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK, BLACK},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ YELLOW, PURPLE, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, WHITE, PURPLE, PURPLE, PURPLE, PURPLE, WHITE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, PURPLE, PURPLE, YELLOW},
{ YELLOW, PURPLE, PURPLE, PURPLE, WHITE, WHITE, WHITE, PURPLE, PURPLE, WHITE, WHITE, WHITE, PURPLE, PURPLE, PURPLE, YELLOW},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK},
{ BLACK, BLACK, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, BLACK, BLACK},
{ BLACK, BLACK, BLACK, YELLOW, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, YELLOW, YELLOW, BLACK, BLACK, BLACK},
{ BLACK, BLACK, BLACK, BLACK, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK}
};


const byte numChars = 255;                                 // Aqui li indiquem quantes dades te que rebre
char receivedChars[numChars];                              // array on guarda totes aquestes dades

boolean newData = false;                                   // Iniciem la variable newData com a false



void setup() {
    Serial.begin(9600);          
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); // Iniciar comunicació amb la pantalla
    FastLED.setBrightness( BRIGHTNESS );                   // Assignar al brillantor de la pantalla
    drawEmoji();                                           // Funció que carrega la pantalla en blanc a l'array leds 
    FastLED.show();                                        // Funció que mostra a la pantalla l'array leds
    pinMode(8,INPUT_PULLUP);                               // Definim el pin 8 com a entrada (Polsador)
}

void loop() {
  if(digitalRead(8)==LOW){                                 // Quan es prem el botó
     countdown();                                          // Funció compte enrere
     drawBlack();                                          // Funció pantalla negre
     delay(500);                                           // Delay de mig segon
     Serial.write('S');                                    // Envia per la comunicació serial una ('s')
     delay(500);                                           // Delay de mig segon
  }
  recvNoEndMarker();                                     // Funció que rep les dades per el port serial 
  if (newData == true){                                    // Mirem si rebem noves dades
    FastLED.show();                                        // Les enviem a la pantalla
    newData = false;                                       // Resetejem la variable
  }   
}

// ********************* Funcions

void drawEmoji() {                                         // Funció Per pintar la pantalla de blanc
    for (int y = 0; y < MATRIX_HEIGHT; y++) {              // Aqui li indiquem totes les columnes verticals
        for (int x = 0; x < MATRIX_WIDTH; x++) {           // Aqui li indiquem totes les columnes horitzontals
            leds[XY(x, y)] = WHITE;                        // Aqui li diem el color que volem pintar
        }
    }
}

void drawBlack() {                                         // Funció Per pintar la pantalla de negre
    for (int y = 0; y < MATRIX_HEIGHT; y++) {              // Aqui li indiquem totes les columnes verticals
        for (int x = 0; x < MATRIX_WIDTH; x++) {           // Aqui li indiquem totes les columnes horitzontals
            leds[XY(x, y)] = BLACK;                        // Aqui li diem el color que volem pintar
        }
    }
}

void countdown() {                                         
  const CRGB* countdown[3] = { &numero3[0][0], &numero2[0][0], &numero1[0][0] }; // & = dóna’m la seva adreça de memòria

  for (int i = 0; i < 3; i++) {                                   // Variable i per recórrer els elements dins de l'array
    for (int y = 0; y < MATRIX_HEIGHT; y++) {                     // Recorre les files
      for (int x = 0; x < MATRIX_WIDTH; x++) {                    // Recorre les columnes
        leds[XY(x, y)] = countdown[i][XY(x, y)];                  // Carrega el dibuix a l'array leds
      }
    }
    FastLED.show();                                               // Mostra l'array leds a la pantalla
    delay(1000);                                                  // Temps d'espera entra cada segon(pantalla)
  }
}

void recvNoEndMarker() {                                 // Funció de dades rebudes
  static int pixelIndex = 0;                               // Definim una variable estàtica
  static byte rgb[3];                                      // Definim un array de 3 elements
  static byte colorPos = 0;                                // Variable que guardarà index d'array
  char rc;                                                 // Variable per llegir dades que arriben per el serial

  while (Serial.available() > 0) {                         // Preguntem si hi han dades per llegir, que segueixi llegint
    rc = Serial.read();                                    // guardem a la variable rc les dades que arriben des de el port
    rgb[colorPos] = (byte)rc;                              // guardem el valor de rc a l'array rgb
    colorPos++;                                            // Aqui li indiquem al colorPos que vaigui incrementant

    if (colorPos == 3) {                                   // Si colorPos és igual a 3
      if (pixelIndex < NUM_LEDS) {                         // Quan pixelIndex és menor a 256
        leds[pixelIndex] = CRGB(rgb[0], rgb[1], rgb[2]);   // li indiquem a l'array de leds el numero de led que té que engegar amb els valors rgb
        pixelIndex++;                                      // Incrementem la variable per pintar tots els pixels
      }
      colorPos = 0;                                        // Reiniciem colorPos a 0 per tal de que vaigui al següent i torni a fer l'ordre RGB.

      
      FastLED.show();                                      
    }

    
    if (pixelIndex >= NUM_LEDS) {                          // Preguntem si la variabla pixelIndex és igual o més gran que 256
      pixelIndex = 0;                                      // Reiniciem aquesta variable per utilitzar una altre cop el programa
    }
  }
}

void buttonPres(){                            // Funció que mira si el polsador verd s'ha premut
  if(digitalRead(8)==LOW){                    // Mirem si el pin 8 definit com a entrada és igual a 0
     Serial.write('S');                       // Enviem una 'S' per el port serial
     delay(500);                              // Delay de 500ms
  }
}


