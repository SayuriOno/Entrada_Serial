#include <Arduino.h>
// C++ code
//
//PROJETO: entrada serial
//DESCRIÇÃO:
//NOME: Sayuri Ono
//DATA: 15/10/2026
//Versão 1.5

//! anotacoes importantes 
//? anotacoes menos importantes

void leituraNaoBLoqueante();
void leituraBloqueante();
void processarfrase(char* texto);
int lerProximoNumero(char*& cursor);

//todo===================================================================================================================================================================
void setup() {

Serial.begin(115200);
Serial.setTimeout(2000);

//! setTimeout = limite do tempo 
//! readStringUntil esperar no maximo esse tempo (ms) pelo '\n'
//! o padrao eh 1000ms

Serial.println( );
Serial.println("digite o seu nome e pressione ENTER: ");

}

//todo===========================================================================================================================================

void loop()
{
leituraNaoBLoqueante ();
}

//todo===========================================================================================================================================

void leituraNaoBLoqueante()
{
  const int tamanhoMaximo = 50; //*o tamanho do vetor (inclui '/0')
  char frase[tamanhoMaximo];
  int position = 0 ;

   while(Serial.available() > 0 )
   { char c = Serial.read();
       if ( c == '\r') continue;
       //! o comando continue pula o restante do while naquela volta e passa para a leitura do proximo caractere
       //! o \r eh lido e simplesmente descartado, sem entrar no vetor


       if ( c== '\n')
       {
        frase[position] = '\0';

        if(position > 0)
        processarfrase(frase);

        position=0 ;
       }

       else if (position < tamanhoMaximo - 1) //! -1 por causa do /0 no final, logo o position vai de 0 a 48.
       {
        frase[position] = c;
        position++;
       }
} }

//todo=====================================================================================================================================================

//? vermelho, verde, azul.
//? branco e desliga.
//? RGB r g b (ex: RGB 200 125 98) (0 a 255)
//? brilho n ( de 0 a 100%)

void processarfrase(char* texto)
{
   Serial.printf("recebido: [%s]\n\r", texto);
   
   char* comando = texto;
   //! o * eh o endereco do texto, a variavel comando sabe onde o texto esta e recebe seu endereco
   //! mas ela nao modifica ele caso tenha const char* texto no void.
   char* parametro = NULL;
   //!null eh o \0

   char* espaco = strchr( texto, ' '); 
   //! o espaco sabe que deve procurar( comando strchr) o espaco no texto ( gracas ao "texto, ' ' " )
   //! que indica (endereco/lugar, o que procurar)

   if (espaco != NULL) //! se ele encontrar um espaco...
   { parametro = parametro + 1;
    *espaco = ' \0 ';
    //! o *espaco = substituir o conteudo do espaco por \0, so o * adiciona 
   }

   int vermelho = 0;
   int verde = 0;
   int azul = 0;
   int brilho = 0;

   if (strcasecnp( comando, "vermelho")==0 )
    {  //! strcasecnp faz o mesmo de strcnp mas nao leva em consideracao letras maiusculas e minusculas

       vermelho = 255;
       verde = 0;
       azul = 0;

    }
    else if (strcasecnp( comando, "verde")==0 )
      {
       vermelho = 0;
       verde =255;
       azul = 0;

      }
    else if (strcasecnp( comando, "azul")==0 )
      { 
       vermelho = 0;
       verde = 0;
       azul = 255;
   
      }
      else if (strcasecnp( comando, "branco")==0 )
      {
       vermelho = 255;
       verde = 255;
       azul = 255;
      }
      else if (strcasecnp( comando, "desliga")==0 )
      {
       vermelho = 0;
       verde = 0;
       azul = 0;
        
      }
      else if (strcasecnp( comando, "RGB")==0 )
      {
        if(parametro=NULL )
        {
          Serial.println( " use o comando: RBG r g b (0 a 255)");
          return;
        }

       char* cursor = parametro;

       vermelho = constrain(lerProximoNumero(cursor), 0 , 255);
       verde = constrain(lerProximoNumero(cursor), 0 , 255);
       azul = constrain(lerProximoNumero(cursor), 0 , 255);
       //! limita o valor em uma faixa do minimo ao maximo
       //! constraind( valor que esta constando, minimo, maximo)

      }
       else if (strcasecnp( comando, "brilho")==0 )
      {
       if(parametro=NULL )
        {
          Serial.println( " use o comando: BRILHO n (0 a 100)");
          return;
        }
        brilho = constrain(atoi(parametro), 0, 100);
      }
      else
      {
         char buffer[100];
         snprintf( buffer, sizeof(buffer), "comando: [%s] nao existe", comando);
         Serial.println(buffer);
         return;
      }

}
 void aplicaCor()
 {
  int r = vermelho * brilho/100;
  int g = verde * brilho/100;
  int b = azul * brilho/100;

  rgbLedWrite(PIN_RGB_LED, r , g , b);

  char bufferMensagem[80];
  snprintf(bufferMensagem, sizeof(bufferMensagem), "cor: R=%3d G=%3d B=%3d | Brilho: %3d %% | HEX: #%02X%02X%02X ", 
            vermelho, verde, azul, brilho, r, b, g);
            Serial.println(bufferMensagem);
  //! hexadecimal de cor comeca pelo #
 }

int lerProximoNumero(char*& cursor)
{//! char*& cursor = referimos nos ao conteudo do cursor com o *&

int valor = atoi(cursor);
char* espaco = strchr( cursor, ' ');
cursor = (espaco != NULL ) ? espaco + 1 : NULL;
return valor; 

}

//!  char endereco = 4
//!  print(endereco) = e                             0123456789
//!  pois a memoria tem 9 espacos com 9 conteudos : [abcdefghij]

//todo=====================================================================================================================================================

void leituraBloqueante()
{
if (Serial.available()>0)
//! available() diz quantos bytes ja chegaram e estao esperando leitura  
{
String texto = Serial.readStringUntil('\n');
//! readStringUntil eh perigoso por ser algo bloqueante 

texto.trim();
//! o trim remove caracteres nao imprimiveis e eh a primeira coisa que fazemos ao colocar um string texto
//! o trim() remove espacos, /r , \t , \n 
//? aqui voce cria o texto e depois apaga os caracteres desnecessarios  


if ( texto.length() == 0 ) return 
//! diferente do continue, o return sai da funcao.

Serial.printf("Seu nome eh %s\n\r", texto.c_str());
//? mandou imprimir o nome
Serial.printf("quantidade de caracteres: %u\n\r ", texto.length() );
//? aqui voce mandou imprimir a quantidade de caracteres do nome

Serial.printf("primeira letra: %c\n\r", texto.charAt(0));
Serial.printf("ultima letra: %c\n\r", texto[ texto.length() - 1 ] );
//? e entao manda imprimir a ultima e primeira letra

String maiusculo = texto;
maiusculo.toUpperCase();
Serial.print("em maiusculas: %s\n\r", maiusculo.c_str());

if (maiusculo == "thiago" );
  Serial.println("este eh seu nome correto");
//? se for thiago imprime que esta certo


//!A função Serial.printf() permite enviar dados formatados para a porta serial usando especificadores de estilo C 
//! (como %d, %s, %f), funcionando como uma alternativa mais compacta a múltiplos comandos Serial.print()

//!Sintaxe básica: Serial.printf("formato"(o texto), valor1(referente a onde), valor2, ...);

//? nosso /0 ocupa 2 caracteres enquanto la ocupa apenas um
}
}