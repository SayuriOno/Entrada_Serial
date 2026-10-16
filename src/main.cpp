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
void aplicarCor();
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
  const int tamanhoMaximo = 50; //? o tamanho do vetor (inclui '/0')
  char frase[tamanhoMaximo];   //! o array tem 50 posicoes a sua disposicao
  int position = 0 ;

   while(Serial.available() > 0 )//! Serial.available() informa quantos bytes estão esperando para serem lidos pela serial.(50)
   { char c = Serial.read(); //! Essa linha lê um byte por vez e armazena o resultado na variável c.
    //! c guarda o caractere recebido, não a posição do array.
    //! ele eh um contador quase ja que vai guardar o caractere lido.
       if ( c == '\r') continue; //! quando o caractere recebido for \r, ignore-o e passe para a próxima repetição do laço.
       //! o comando continue pula o restante do while naquela volta e passa para a leitura do proximo caractere
       //! o \r eh lido e simplesmente descartado, sem entrar no vetor


       if ( c == '\n') //! se C for igual a tecla '\n' 
       {
        frase[position] = '\0'; //! se C for igual a tecla \n, frase armazena o fim(\0) na posicao indicada pelo position.

        if(position > 0) //! se position for maior que 0
        processarfrase(frase); //! execute a funcao processarfrase com a frase recebida
         //! enviamos a informacao frase para essa funcao que chamamos processa-la 
         //! frase indica as posicoes de 0 a 50, e as letras estao nessas posicoes, logo, enviamos letras ao processafrase processar 

        position=0 ; //! e entao ele zera tudo denovo e volta pro comeco 
       }

       else if (position < tamanhoMaximo - 1) //! -1 por causa do /0 no final, logo o position vai de 0 a 48.
       {//! se a position for menor que 48, frase vai armarzenar C na posicao indicada por position.
        frase[position] = c;
        position++; //! e entao position deve somar +1
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
   //* %s indica onde o texto deve ser inserido. Enquanto texto indica a variavel que guarda o texto que deve ser colocado no %s
   char* comando = texto;
   //! o * eh o endereco do texto, a variavel comando sabe onde o texto esta e recebe seu endereco
   //! mas ela nao modifica ele caso tenha const char* texto no void.
   char* parametro = NULL;
   //!null eh o vazio, a ausencia de um valor 
   //! logo o parametro eh o endereco de nada
  
   char* espaco = strchr( texto, ' '); 
   //! a variavel espaco sabe que deve procurar(gracas comando strchr) ' ' no texto ( gracas ao "texto, ' ' " )
   //! sintaxe: strchr (endereco/lugar, o que procurar)

    //! strchr procura o primeiro caractere ' ' dentro de texto.
   //! Se encontrar, retorna o endereço desse espaço.
   //! Se não encontrar, retorna NULL (ou nullptr, conceitualmente).
  
   if (espaco != NULL) //! se ele encontrar um espaco...
   { parametro = espaco + 1; //! parametro passa a indicar o endereco do caractere depois do espaco encontrado
    *espaco = '\0';
    //! o *espaco = substituir o conteudo do endereco do espaco por \0, basta o * ser colocado no inicio do espaco
    //! sendo o final de string em todo o espaco
    
    //! parametro eh nada, agora toda vez que da um espaco ele indica o inicio de uma palavra
   }

   int vermelho = 0;
   int verde = 0;
   int azul = 0;
   int brilho = 0;

   if (strcasecmp( comando, "vermelho")== 0 )//! se no endereco do texto, procura e achar a palavra vermelho
    { //! o ==0 indica quando ambos textos(o que ele procura e o que ele achou) estao iguais, se ele achou vermelho no texto. 
      //! strcasecnp faz o mesmo de strcnp mas nao leva em consideracao letras maiusculas e minusculas

       vermelho = 255;
       verde = 0;
       azul = 0;
       brilho = 100;

    }
    else if (strcasecmp( comando, "verde")==0 )
      {
       vermelho = 0;
       verde =255;
       azul = 0;
       brilho = 100;

      }
    else if (strcasecmp( comando, "azul")==0 )
      { 
       vermelho = 0;
       verde = 0;
       azul = 255;
       brilho = 100;
   
      }
      else if (strcasecmp( comando, "branco")==0 )
      {
       vermelho = 255;
       verde = 255;
       azul = 255;
       brilho = 100;
      }
      else if (strcasecmp( comando, "desliga")==0 )
      {
       vermelho = 0;
       verde = 0;
       azul = 0;
       brilho = 0;
        
      }
      else if (strcasecmp( comando, "RGB")==0 )
      {
        if(parametro=NULL )//! se o parametro volta a nada, ou seja, se eu nao der espaco
        {
          Serial.println( " use o comando: RBG r g b (0 a 255)");
          return;//! return encerra a funcao 
        }

       char* cursor = parametro;

       vermelho = constrain(lerProximoNumero(cursor), 0 , 255);
       verde = constrain(lerProximoNumero(cursor), 0 , 255);
       azul = constrain(lerProximoNumero(cursor), 0 , 255);
        //! limita o valor em uma faixa do minimo ao maximo, logo qualquer valor a cima do maximo 
        //! e abaixo do minimo, eh parado
        //! sintaxe: constrain( valor que quer limitar, minimo, maximo)

      }
       else if (strcasecmp( comando, "brilho")==0 )//! caso contrario, se voce achar a palavra brilho...
      {
       if(parametro=NULL ) //! se nao der espaco:
        {
          Serial.println( " use o comando: BRILHO n (0 a 100)");//! fala isso
          return;//! e encerra a string.
        }
        brilho = constrain(atoi(parametro), 0, 100);//! aqui limita o brilho de 0 a 100
      }
      else
      {
         char buffer[100];//! guarda 100 posicoes
         snprintf( buffer, sizeof(buffer), "comando: [%s] nao existe", comando);
        //! serve para montar um texto e armazená-lo em uma variável de texto
        //! sintaxe: snprintf(destino, tamanho, "texto + %s", o que vai substituir o %s);
         Serial.println(buffer);
         return;
      }
      aplicarCor();//! e entao realiza essa funcao
}
 void aplicaCor()
 {
  int r = vermelho * brilho/100;//! r = vermelho vezes o brilho dividido por 100
  int g = verde * brilho/100;
  int b = azul * brilho/100;

  rgbLedWrite(PIN_RGB_LED, r , g , b);
   //! A função rgbLedWrite() serve para controlar a cor de um LED RGB
   //! sintaxe: rgbLedWrite(pino, vermelho, verde, azul);
   
  char bufferMensagem[80];
  snprintf(bufferMensagem, sizeof(bufferMensagem), "cor: R=%3d G=%3d B=%3d | Brilho: %3d %% | HEX: #%02X%02X%02X ", 
            vermelho, verde, azul, brilho, r, b, g);
            Serial.println(bufferMensagem);
  //! hexadecimal de cor comeca pelo #
 }

int lerProximoNumero(char*& cursor)
{//! char*& cursor = referimos nos ao conteudo do cursor com o *&

int valor = atoi(cursor);
  //! A função atoi() serve para converter um texto que representa um número inteiro em um valor do tipo int.
char* espaco = strchr( cursor, ' ');
cursor = (espaco != NULL ) ? espaco + 1 : NULL;
  //! se espaco for diferente de NULL, soma espaco + 1, caso contrario eh NULL.
return valor; //! entao voce retorna o valor.

}

//!  char endereco = 4
//!  print(endereco) = e                             0123456789
//!  pois a memoria tem 9 espacos com 9 conteudos : [abcdefghij]

//todo=====================================================================================================================================================

void leituraBloqueante()
{
if (Serial.available()>0)//! se ele for maior que 0
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
