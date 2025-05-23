#include <FastLED.h>

#define LED_PIN     3   // Pin on està conectat el DIN de la matriu
#define MATRIX_WIDTH  16 // LED's d'amplada de la matriu
#define MATRIX_HEIGHT 16 // LED's d'altura de la matriu
#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT) // Numero total de LED's
#define BRIGHTNESS 64 // Briantor de la matriu

CRGB leds[NUM_LEDS]; //Crea un array on cada element és un LED RGB que pots controlar.

// Mapeig de la matriu (dependrà de la connexió)
#define XY(x, y) ((y) * MATRIX_WIDTH + (x))// Passa de coordenades x,y a posició de l'array

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

CRGB savedImage[NUM_LEDS];         // Guarda la imatge rebuda

void loop() {
  buttonPres();
  recvNoEndMarker();
  
  if (newData == true) {
    memcpy(savedImage, leds, sizeof(leds));  // Guardem la imatge rebuda
    countdown();                             // Mostrem 3, 2, 1
    memcpy(leds, savedImage, sizeof(leds));  // Recuperem la imatge original
    FastLED.show();                          
    newData = false;
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

void recvNoEndMarker() {                                 // Funció de dades rebudes
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

void countdown() {                                         
  const CRGB* countdown[3] = { &numero3[0][0], &numero2[0][0], &numero1[0][0] }; // & = dóna’m la seva adreça de memòria

  for (int i = 0; i < 3; i++) {                                   // Variable i per recórrer els elements dins de l'array
    for (int y = 0; y < MATRIX_HEIGHT; y++) {                     // Recorre les files
      for (int x = 0; x < MATRIX_WIDTH; x++) {                    // Recorre les columnes
        leds[XY(x, y)] = countdown[i][y * MATRIX_WIDTH + x];      // Calcula l'índex lineal per accedir al LED correcte del número i l'assigna al LED corresponent de la pantalla
      }
    }
    FastLED.show();                                               // Mostra el numero a la pantalla
    delay(1000);                                                  // Temps d'espera entra cada segon(pantalla)
  }
}


void buttonPres(){                     // Funció que mira si el polsador verd s'ha premut
  if(digitalRead(8)==LOW){             // Mirem si el pin 8 definit com a entrada és igual a 0
     Serial.write('S');                // Enviem una 's' per el port serial
     delay(500);                       // Delay de 500ms
  }
}


