#include <Keypad.h>
#include <LiquidCrystal.h>

#define LINHAS 4
#define COLUNAS 4

char mapaDeTeclas[LINHAS][COLUNAS] = {
  {'2','1','3','A'},
  {'5','4','6','B'},
  {'8','7','9','C'},
  {'0','*','#','D'}
};

byte pinosLinhas[LINHAS] = {8, 9, 10, 11};
byte pinosColunas[COLUNAS] = {A0, A1, A2, A3};

Keypad teclado = Keypad(makeKeymap(mapaDeTeclas),
                        pinosLinhas,
                        pinosColunas,
                        LINHAS,
                        COLUNAS);

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

char vetorSenha[5] = "____";
char senhaCorreta[5] = "AB77";
int posicao = 0;

bool verificarSenha() {
  for (int i = 0; i < 4; i++) {
    if (vetorSenha[i] != senhaCorreta[i]) {
      return false;
    }
  }
  return true;
}

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("DIGITE A SENHA");
  lcd.setCursor(6, 1);
  lcd.print(vetorSenha);
  Serial.begin(9600);
}

void incorrectPassword(){
  lcd.setCursor(2,0);
  lcd.write("ACESSO NEGADO");
  lcd.setCursor(0,1);
  lcd.write("SENHA INCORRETA!");
  delay(1000);
  lcd.noDisplay();
  delay(400);
  lcd.display();
  delay(400);
  lcd.noDisplay();
  delay(400);
  lcd.display();
  delay(400);
  restartDisplay();
}

void correctPassword(){
  lcd.setCursor(1, 0);
  lcd.print("ACESSO LIBERADO");
  lcd.setCursor(1, 1);
  lcd.print("SENHA CORRETA!");
  delay(1000);
  lcd.noDisplay();
  delay(400);
  lcd.display();
  delay(400);
  lcd.noDisplay();
  delay(400);
  lcd.display();
  delay(400);
  restartDisplay();
}

void restartDisplay(){
  for(int i=0; i< 4; i++){
  	vetorSenha[i] = '_';
  }
  posicao = 0;
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("DIGITE A SENHA");
  lcd.setCursor(6, 1);
  lcd.print(vetorSenha);
}

void loop() {
  char tecla = teclado.getKey();

  if (tecla && posicao < 4) {
    vetorSenha[posicao] = tecla;
    posicao++;

    lcd.setCursor(6, 1);
    lcd.print(vetorSenha);
  }

  if (posicao == 4) {
    lcd.clear();
    if (verificarSenha()) {
	 correctPassword();
    } else {
	 incorrectPassword();
    }
   delay(2000);
  }
}