//Criando constantes e variáveis globais
#define esteira1 6
#define esteira2 9
#define esteira3 10
#define esteira4 11
#define botaoAzul 8
#define botaoVerde 12
#define ledVermelho 3
#define ledAzul 4
#define ledVerde 5
#define pir 2
#define leitorQr A0 //0-1023
#define velocidade A1//0-1023
int qntEsteira2 = 0;
int qntEsteira3 = 0;
int qntEsteira4 = 0;
int flag = 0;

//configurando as portas do arduino e o Serial
void setup()
{
 pinMode(esteira1, OUTPUT); 
 pinMode(esteira2, OUTPUT);
 pinMode(esteira3, OUTPUT);
 pinMode(esteira4, OUTPUT);
 pinMode(ledVermelho, OUTPUT);
 pinMode(ledAzul, OUTPUT);
 pinMode(ledVerde, OUTPUT);
 pinMode(botaoVerde, INPUT_PULLUP);
 pinMode(botaoAzul, INPUT_PULLUP);
 pinMode(pir, INPUT);
 Serial.begin(9600);
 Serial.println("Bem-vindo ao controle de estoque!");
 Serial.println("Aperte o botao LARANJA para INICIAR");
 Serial.println("OU aperte o botao VERDE para checar as quantidades");
}
//Criando o programa das esteiras
void loop()
{
  //Criando a rotina do botão verde
  if(digitalRead(botaoVerde)==LOW && flag==0){
  	Serial.print("Produto X:");
    Serial.println(qntEsteira2);
    Serial.print("Produto Y:");
    Serial.println(qntEsteira3);
    Serial.print("Produto Z:");
    Serial.println(qntEsteira4);
    flag = 1;
  }
  //Criando a rotina do botão azul
  if(digitalRead(botaoAzul)==LOW){
    boolean valida= true; 
    //Inicia o enquanto para velocidade das esteiras
    while(valida==true){    
      int velocidadeEsteira = analogRead(velocidade);
      Serial.print("Velocidade de entrada:");
      Serial.println(velocidadeEsteira);
      velocidadeEsteira = map(velocidadeEsteira, 0,1023,0,255);
      Serial.print("Velocidade de saida(PWM):");
      Serial.println(velocidadeEsteira);
      digitalWrite(ledVerde, HIGH);
      analogWrite(esteira1,velocidadeEsteira);
      //Se o sensor de presença detectar algo, ele faz
      if(digitalRead(pir)==HIGH){
        Serial.println("Produto detectado:");
        Serial.print("Codigo:");
        Serial.println(analogRead(leitorQr));
        digitalWrite(ledVerde, LOW);
        delay(50);
        digitalWrite(ledVermelho, HIGH);
        analogWrite(esteira1, 0);
        delay(3000);
        /*Seleciona uma das três esteiras, baseado no valor
        do sensor ldr*/
        if(analogRead(leitorQr) <= 568){
          	Serial.println(" Esteira 2");
            digitalWrite(ledVermelho, LOW);
            delay(50);
            digitalWrite(ledAzul, HIGH);
            analogWrite(esteira1, velocidadeEsteira);
          	delay(1000);
          	analogWrite(esteira1, 0);
            analogWrite(esteira2, velocidadeEsteira);
            delay(5000);
            analogWrite(esteira2, 0);
          	valida = false;
          	qntEsteira2++;
          	Serial.println("Produto entregue!");
          	Serial.print("Quantidade de produtos X:");
          	Serial.println(qntEsteira2);
          	Serial.println("Adicione o proximo produto!");
        }else if(analogRead(leitorQr) > 568 && analogRead(leitorQr) <= 912){
            Serial.println(" Esteira 3");
          	digitalWrite(ledVermelho, LOW);
            delay(50);
            digitalWrite(ledAzul, HIGH);
            analogWrite(esteira1, velocidadeEsteira);
          	delay(1000);
          	analogWrite(esteira1, 0);
            analogWrite(esteira3, velocidadeEsteira);
            delay(5000);
            analogWrite(esteira3, 0);
          	valida = false;
          	qntEsteira3++;
          	Serial.println("Produto entregue!");
          	Serial.print("Quantidade de produtos Y:");
          	Serial.println(qntEsteira3);
          	Serial.println("Adicione o proximo produto!");
        }else{
          	Serial.println(" Esteira 4");
            digitalWrite(ledVermelho, LOW);
            delay(50);
            digitalWrite(ledAzul, HIGH);
            analogWrite(esteira1, velocidadeEsteira);
          	delay(1000);
          	analogWrite(esteira1, 0);
            analogWrite(esteira4, velocidadeEsteira);
            delay(5000);
            analogWrite(esteira4, 0);
          	valida = false;
          	qntEsteira4++;
          	Serial.println("Produto entregue!");
          	Serial.print("Quantidade de produtos Z:");
          	Serial.println(qntEsteira4);
          	Serial.println("Adicione o proximo produto!");
        }
        //Finalizando o programa e resetando o FLAG
        delay(500);
        digitalWrite(ledAzul, LOW);
        flag=0;
      }
    }  
  }
}