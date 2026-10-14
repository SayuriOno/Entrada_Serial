#include <Arduino.h>


void setup() {
Serial.begin(9600);
Serial.setTimeout(2000);
//* readStringUntil esperar no maximo esse tempo (ms) pelo '\n'
//* o padrao eh 1000ms
Serial.print( );
Serial.println("digite o seu nome e pressione ENTER: ");

}

void loop() {
//* available() diz quantos bytes ja chegaram e estao esperando leitura 
if (Serial.available()>0)
{
string texto = Serial.readStringUntil('\n')
Serial.printf("Seu nome eh %s", texto.c_str());
}
}


