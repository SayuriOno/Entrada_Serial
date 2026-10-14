#include <Arduino.h>

//todo 
//?
//*
//!

void leituraNaoBLoqueante();
void leituraBloqueante();
void processarfrase();
void setup() {

Serial.begin(115200);
Serial.setTimeout(2000);

//* setTimeout = limite do tempo 
//* readStringUntil esperar no maximo esse tempo (ms) pelo '\n'
//* o padrao eh 1000ms

Serial.println( );
Serial.println("digite o seu nome e pressione ENTER: ");

}

void loop() {
}

void leituraNaoBLoqueante()
{
  const int tamanhoMaximo = 50; //*o tamanho do vetor (inclui '/0')
  char frase[tamanhoMaximo];
  int position = 0 

   while(serial.available() > 0 )
   { char c = Serial.read();
       if ( c == '\r') continue;
       //! o comando continue pula o restante do while naquela volta e passa para a leitura do proximo caractere
       //! o \r eh lido e simplesmente descartado, sem entrar no vetor

       if ( c== '\n')
       {
        frase[position] = '\0';
        position = 0 ;
        processarfrase(frase);
       }

       else if (position < tamanhoMaximo - 1) //! -1 por causa do /0 no final, logo o position vai de 0 a 48.
       {
        frase[position] = c;
        position++;
       }
}
}

void processarfrase(const char* texto)
{
   Serial.printf("recebido: [%s]\n\r", texto);
}

void leituraBloqueante()
{
if (Serial.available()>0)
//* available() diz quantos bytes ja chegaram e estao esperando leitura  
{
string texto = Serial.readStringUntil('\n')
//! readStringUntil eh perigoso por ser algo bloqueiante 
texto.trim();
//* o trim remove caracteres nao imprimiveis e eh a primeira coisa que fazemos ao colocar um string texto
//* o trim() remove espacos, /r , \t , \n 
//! aqui voce cria o texto e depois apaga os caracteres desnecessarios  



if ( texto.length() == 0 ) return 

Serial.printf("Seu nome eh %s\n\r", texto.c_str());
//! mandou imprimir o nome
Serial.printf("quantidade de caracteres: %u\n\r ", texto.length() );
//! aqui voce mandou imprimir a quantidade de caracteres do nome

Serial.printf("primeira letra: %c\n\r", texto.charAt(0));
Serial.printf("ultima letra: %c\n\r", texto[ texto.length() - 1 ] );
//! e entao manda imprimir a ultima e primeira letra

string maiusculo = texto;
maiusculo.toUpperCase();
Serial.print("em maiusculas: %s\n\r", maiusculo.c_str());

if (maiusculo == "thiago" );
  Serial.println("este eh seu nome correto");
//! se for thiago imprime que esta certo
}}
