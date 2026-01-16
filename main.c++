#include <Keypad.h>
#include <LiquidCrystal.h>
#define LINHAS 4
#define COLUNAS 4
int posicao = 0;

char mapaDeTeclas[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte  pinosLinhas[LINHAS] = {8,9,10,11};
byte  pinosColunas[COLUNAS] = {A0,A1,A2,A3};
char vetorSenha[4] = {'_','_','_','_'};

Keypad teclado = Keypad(makeKeymap(mapaDeTeclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
   lcd.begin(16,2);
   lcd.clear();
   lcd.setCursor(1,0);
   lcd.print("DIGITE A SENHA");
   lcd.setCursor(5,1);
   lcd.print(vetorSenha);
}

void loop() {
    char tecla = teclado.getKey();

    if (tecla && posicao < 4) {
      vetorSenha[posicao] = tecla;
      posicao++;

      lcd.setCursor(5,1);
      lcd.print(vetorSenha);
  	}
 }
