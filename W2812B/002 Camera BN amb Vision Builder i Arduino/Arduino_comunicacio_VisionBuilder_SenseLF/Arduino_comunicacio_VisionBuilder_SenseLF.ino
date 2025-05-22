#include <FastLED.h>

#define LED_PIN     3   // Pin on està conectat el DIN de la matriu
#define MATRIX_WIDTH  16 // LED's d'amplada de la matriu
#define MATRIX_HEIGHT 16 // LED's d'altura de la matriu
#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT) // Numero total de LED's
#define BRIGHTNESS 64 // Briantor de la matriu

CRGB leds[NUM_LEDS]; //Crea un array on cada element és un LED RGB que pots controlar.

// Mapeig de la matriu (dependrà de la connexió)
#define XY(x, y) ((y) * MATRIX_WIDTH + (x))

// Definim els colors bàsics
#define YELLOW  CRGB(255, 200, 0)
#define BLUE    CRGB(0, 0, 255)
#define WHITE   CRGB(255, 255, 255)
#define BLACK   CRGB(0, 0, 0)



// Definim el emoji en una matriu de 16x16
const CRGB emoji1[16][16] = {
  {WHITE, WHITE, WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE, WHITE, WHITE, WHITE},
  {WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE, WHITE},
  {WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE},
  {WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE},
  {WHITE, YELLOW, YELLOW, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, YELLOW, YELLOW, WHITE},
  {YELLOW, YELLOW, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, YELLOW, YELLOW},
  {YELLOW, BLACK, YELLOW, BLACK, BLACK, BLACK, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, YELLOW, BLACK, YELLOW},
  {YELLOW, YELLOW, YELLOW, BLUE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLUE, YELLOW, YELLOW, YELLOW},
  {YELLOW, YELLOW, BLUE, BLUE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLUE, BLUE, YELLOW, YELLOW},
  {YELLOW, BLUE, BLUE, BLUE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, BLUE, BLUE, BLUE, YELLOW},
  {BLUE, BLUE, BLUE, BLUE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLUE, BLUE, BLUE, BLUE},
  {BLUE, BLUE, BLUE, BLUE, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLUE, BLUE, BLUE, BLUE},
  {WHITE, BLUE, BLUE, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, YELLOW, YELLOW, BLUE, BLUE, WHITE},
  {WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE, WHITE},
  {WHITE, WHITE, WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE, WHITE, WHITE, WHITE},
  {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, YELLOW, YELLOW, YELLOW, YELLOW, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE}
};
const CRGB emojiblank[16][16];
// Arduino server for Color LEGO_Arduino.vbai 

const byte numChars = 255;                                 // Aqui li indiquem quantes dades te que rebre
char receivedChars[numChars];                              // array on guarda totes aquestes dades

boolean newData = false;                                   // Iniciem la variable newData com a false
void setup() {
    Serial.begin(9600);
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); // Iniciar comunicació amb la pantalla
    FastLED.setBrightness( BRIGHTNESS );                   // Assignar al brillantor de la pantalla
    drawEmoji();                                           // Funció que pinta la pantalla en blanc quan resetejem
    FastLED.show();                                        // Eina de la llibreria que mostra a la pantalla
    pinMode(8,INPUT_PULLUP);                               // Definim el pin 8 com a entrada (Polsador)
}

void loop() {
  buttonPres();                                            // Mirem si s'ha premut algun polsador
  recvWithEndMarker();                                     // Comença a llegir dades del port serial
  if (newData == true){                                    // Mirem si ha llegit totes les dades
    FastLED.show();                                        // Pinta a la pantalla la imatge completa
    newData = false;                                       // Resetejem la variable newData per provar alguna altre imatge
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

void recvWithEndMarker() {                                 // Funció de dades rebudes
  static byte nbit = 0;                                    // Variable estatica que guarda 8 bis
  static byte nbyte = 0;                                   // Variable estatica que guarda 1 byte
  char endMarker = '\n';                                   // Funció que decideix quan parar de llegir 
  char rc;                                                 // Variable per llegir dades que arriben per el serial
   
  while (Serial.available() > 0 && newData == false) {     // Preguntem si hi han dades per llegir, que segueixi llegint sempre i quan newData sigui false
    rc = Serial.read();                                    // Preparem la variable rc perquè llegeixi les dades que arriben des de el port
    if (nbyte !=32)                                        // Mirem si nbyte és diferent a 32
    {
      for (int i = 0; i<=7 ; i++)                          // Es crea la variable i per mirar els 8 valors binaris
      {
        int bitValue = (rc >> i) & 1;                      // Es crea la variable bitValue que mira si els 8 bits són 1 o 0 mirannt-los de un en un
        if (bitValue == 1)                                 // Aqui mirem si llegeix un 1
        {
          leds[nbit+(8*nbyte)] = CRGB::WHITE;              // Si llegeix un 1 pintarà a la pantalla el LED corresponent amb blanc
        }
        else
        {
          leds[nbit+(8*nbyte)] = CRGB::BLACK;             // Si llegeix un 0 pintarà a la pantalla el LED corresponent amb negre
        }
        nbit++;                                           // Aqui li diem a la variable nbit que vaigui incrementant 
      }
      nbit = 0;                                           // Aqui modifiquem la variable nbit per igualar-la a 0 
      nbyte++;                                            // Li diem que vaigui cambiant al següent paquet de 8 bits.
    }
    if (nbyte == 32) {                                    // Mirem si nbyte és igual a 32
      nbyte = 0;                                          // Si és així reiniciem aquesta variable
      newData = true;                                     // Tornem a actualitzar la variable newData a true
    }
  }
}

void buttonPres(){                     // Funció que mira si el polsador verd s'ha premut
  if(digitalRead(8)==LOW){             // Mirem si el pin 8 definit com a entrada és igual a 0
     Serial.write('S');                // Enviem una 's' per el port serial
     delay(500);                       // Delay de 500ms
  }
}


