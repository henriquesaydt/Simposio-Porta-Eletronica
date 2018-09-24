#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Servo.h>
 
#define SS_PIN 53
#define RST_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
Servo motor;
LiquidCrystal lcd(6, 7, 9, 4, 3, 2); 

 
char st[20];
char senhaCorreta[7] = "666666";
char senha[7];
int j,i,anl1;
 
void setup() 
{
  Serial.begin(9600);
  SPI.begin();// Inicia  SPI bus
  //Botões do Tecladinho
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  
  
  motor.attach(8);
  motor.write(0);
  mfrc522.PCD_Init(); // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  lcd.begin(16, 2); 
  mensageminicial();
}
 
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    if(digitalRead(22) == LOW){
      Serial.println("Digite a senha");
      lcd.clear();
      lcd.print("Digite a senha");
      delay(1000);
      
      for (j=0;j<6;j++){
        for(;;){
          if(digitalRead(23) == LOW){
            Serial.println("Botão 0 \n indice:");
            Serial.print(j);
            senha[j] = '0';
            break;
          }
          else if(digitalRead(24) == LOW){
            Serial.println("Botão 1 \n indice:");
            Serial.print(j);
            senha[j] = '1';
            break;
          }
          else if(digitalRead(25) == LOW){
            Serial.println("Botão 2 \n indice:");
            Serial.print(j);
            senha[j] = '2';
            break;
          }
          else if(digitalRead(26) == LOW){
            Serial.println("Botão 3 \n indice:");
            Serial.print(j);
            senha[j] = '3';
            break;
          }
          else if(digitalRead(27) == LOW){
            Serial.println("Botão 4 \n indice:");
            Serial.print(j);
            senha[j] = '4';
            break;
          }
          else if(digitalRead(28) == LOW){
            Serial.println("Botão 5 \n indice:");
            Serial.print(j);
            senha[j] = '5';
            break;
          }
          else if(digitalRead(29) == LOW){
            Serial.println("Botão 6 \n indice:");
            Serial.print(j);
            senha[j] = '6';
            break;
          }
          else if(digitalRead(30) == LOW){
            Serial.println("Botão 7 \n indice:");
            Serial.print(j);
            senha[j] = '7';
            break;
          }
          else if(digitalRead(31) == LOW){
            Serial.println("Botão 8 \n indice:");
            Serial.print(j);
            senha[j] = '8';
            break;
          }
          else if(digitalRead(32) == LOW){
            Serial.println("Botão 9 \n indice:");
            Serial.print(j);
            senha[j] = '9';
            break;
          }
          else{
            continue;
          }
        }
        Serial.println("Você digitou: ");
        lcd.setCursor(j,1);
        lcd.print(senha[j]);
        
        Serial.println(j);
        delay(700);
      }
      Serial.println(senha);
      Serial.println(senhaCorreta);
      verificaSenha();
    }
    if (analogRead(A0) <= 800)
    {
      delay(1000);
      motor.write(0);
      mensageminicial();
    }
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }


  // Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();

  
  if (conteudo.substring(1) == "50 ED C1 A3")
  {
    Serial.println("Acesso permitido!");
    lcd.clear();
    lcd.print("Acesso permitido!");
    motor.write(180);
    delay(2000);
    lcd.clear();
    lcd.print("Porta aberta!");
  }
  else 
  {
    Serial.println("Acesso Negado!");
    lcd.clear();
    lcd.print("Acesso Negado!");
    delay(3000);
    mensageminicial();
  }

} 

void mensageminicial()
{
  lcd.clear();
  lcd.print("Aproxime o seu");  
  lcd.setCursor(0,1);
  lcd.print("cartao do leitor");  
}

void verificaSenha()
{
  if (strcmp(senhaCorreta, senha) == 0)
  {
    Serial.println("Acesso permitido!");
    lcd.clear();
    lcd.print("Acesso permitido!");
    motor.write(180);
    delay(2000);
    lcd.clear();
    lcd.print("Porta aberta!");
  }
  else 
  {
    Serial.println("Acesso Negado!");
    lcd.clear();
    lcd.print("Acesso Negado!");
    delay(3000);
    mensageminicial();
  }
}

int lerTeclado(){
  int v, res;
  res = 0;
  for (v=0; v<100; v++){
    res = res + analogRead(A1);
  }
  res = (res/100);
  if (res < 0){
    res = res*(-1);
  }
  return res;
}

