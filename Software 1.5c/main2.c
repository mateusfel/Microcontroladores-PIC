#include <main.h>

#include <2416mascarenhas.C>
#define use_portb_kbd TRUE
#include <kbd4x4.C>

#define LCD_ENABLE_PIN  PIN_C2                                    ////
#define LCD_RS_PIN      PIN_C0                                    ////
#define LCD_RW_PIN      PIN_C1                                    ////
#define LCD_DATA4       PIN_A0                                    ////
#define LCD_DATA5       PIN_A1                                    ////
#define LCD_DATA6       PIN_A2                                    ////
#define LCD_DATA7       PIN_A3                                    ////
#include <LCD.C>

//int tela = 0;
int tecla = 0;

char id[10] = {0,0,0,0,0,0,0,0,0,0};
int  iddigito = 0;

char pin[10] = {0,0,0,0,0,0,0,0,0,0};
int  pindigito = 0;

char usuario[20];

const int idcorreto[10] = {'1','2','3','4',0,0,0,0,0,0};
const int pincorreto[10] = {'1','2','3','4',0,0,0,0,0,0};

char lastchar(void);
void verificalogin();

void main()
{
   kbd_init();
   port_b_pullups(TRUE);
   lcd_init();
   init_ext_eeprom();
   
   //GRAVANDO A ID DO ADM NA MEMÓRIA PARA TESTES
   write_ext_eeprom(0, '1');
   write_ext_eeprom(1, '2');
   write_ext_eeprom(2, '3');
   write_ext_eeprom(3, '4');
   write_ext_eeprom(4, 0);
   write_ext_eeprom(5, 0);
   write_ext_eeprom(6, 0);
   write_ext_eeprom(7, 0);
   write_ext_eeprom(8, 0);
   write_ext_eeprom(9, 0);
   //GRAVANDO O PIN DO ADM NA MEMÓRIA PARA TESTES
   write_ext_eeprom(10, '1');  //PELO AMOR DE DEUS REMOVER ISSO NA PRÁTICA SENÃO VAI GASTAR O CICLO DE VIDA DA EEPROM
   write_ext_eeprom(11, '2');
   write_ext_eeprom(12, '3');
   write_ext_eeprom(13, '4');
   write_ext_eeprom(14, 0);
   write_ext_eeprom(15, 0);
   write_ext_eeprom(16, 0);
   write_ext_eeprom(17, 0);
   write_ext_eeprom(18, 0);
   write_ext_eeprom(19, 0);
   //GRAVANDO A ID DO USER2 NA MEMÓRIA PARA TESTES
   write_ext_eeprom(20, '4');
   write_ext_eeprom(21, '3');
   write_ext_eeprom(22, '2');
   write_ext_eeprom(23, '1');
   write_ext_eeprom(24, 0);
   write_ext_eeprom(25, 0);
   write_ext_eeprom(26, 0);
   write_ext_eeprom(27, 0);
   write_ext_eeprom(28, 0);
   write_ext_eeprom(29, 0);
   //GRAVANDO O PIN DO USER2 NA MEMÓRIA PARA TESTES
   write_ext_eeprom(30, '4');  //PELO AMOR DE DEUS REMOVER ISSO NA PRÁTICA SENÃO VAI GASTAR O CICLO DE VIDA DA EEPROM
   write_ext_eeprom(31, '3');
   write_ext_eeprom(32, '2');
   write_ext_eeprom(33, '1');
   write_ext_eeprom(34, 0);
   write_ext_eeprom(35, 0);
   write_ext_eeprom(36, 0);
   write_ext_eeprom(37, 0);
   write_ext_eeprom(38, 0);
   write_ext_eeprom(39, 0);
   
   //GRAVANDO O FIM DO CADASTRO DOS USUÁRIOS
   write_ext_eeprom(40, 'x');
   
   goto telaID;
   
   ////////////////////////// TELA ID
   telaID: //"ponteiro"
   printf(lcd_putc,"\fID:");
   while(TRUE){ //Loop para capturar o ID ou mudar de tela
      tecla = lastchar();
      switch(tecla){
         case 'A':
            goto telaPIN;
         break;
         case 'B':
            //Nada acontece
         break;
         case 'C':
            //Nada acontece
         break;
         case 'D':
            //Nada acontece
         break;
         case '*':   //Esse caso apaga o vetor pin, apaga os asteriscos digitado na tela e retorna ao dígito 0 do pin
              printf(lcd_putc,"\fID:");
              iddigito = 0;
              for(int i; i < 10; i++){
                  id[i] = 0;
              }
         break;
         case '#':
            //Nada acontece
         break;
         default: //Esse caso DEFAULT grava o número digitado no vetor pin
            if(iddigito < 10){  //limita a quantidade de dígitos do pin em 10 [vai de 0 à 9]
               printf(lcd_putc,"%c",tecla);
               id[iddigito] = tecla; //O atual dígito do pin recebe o número digitado
               iddigito++; //avança o dígito do pin
            }
         break;
      }
      
   }
   ////////////////////// FIM TELA ID
   
   ////////////////////// TELA DO PIN
   telaPIN: //"ponteiro"
   printf(lcd_putc,"\fPIN:");
   while(TRUE){ //Loop para capturar o PIN ou mudar de tela
      tecla = lastchar();
      switch(tecla){
         case 'A':
            goto verifica;
         break;
         case 'B':
            //Nada acontece
         break;
         case 'C':
            //Nada acontece
         break;
         case 'D':
            //Nada acontece
         break;
         case '*':   //Esse caso apaga o vetor pin, apaga os asteriscos digitado na tela e retorna ao dígito 0 do pin
              printf(lcd_putc,"\fPIN:");
              pindigito = 0;
              for(int i; i < 10; i++){
                  pin[i] = 0;
              }
         break;
         case '#':
            //Nada acontece
         break;
         default: //Esse caso DEFAULT grava o número digitado no vetor pin
            if(pindigito < 10){  //limita a quantidade de dígitos do pin em 10 [vai de 0 à 9]
               printf(lcd_putc,"*");
               pin[pindigito] = tecla; //O atual dígito do pin recebe o número digitado
               pindigito++; //avança o dígito do pin
            }
         break;
      }
      
   }   
   ////////////////////// FIM TELA DO PIN
   
   ///////////////////// VERIFICA LOGIN
   while(TRUE){
      verifica:
      for(int i = 0; i < 10; i++){ //passa os valores de id para o início de usuario
         usuario[i] = id[i];
      }
      for(int j = 10; j < 20; j++){ //passa os valores de pin para o fim de usuario
         usuario[j] = pin[j-10];
      }
      
      int posicao_na_memoria = 0; //Inidica em qual posicao de usuário está na memória EEPROM
      int usuario_match = TRUE;  //Indica se algum usuário combinou
      int continua_a_busca = TRUE; //inidica se a busca deve continuar
      
      while(continua_a_busca){   //Começa a procurar na EEPROM um usuário com esse ID e PIN registrados
         if(read_ext_eeprom(posicao_na_memoria*20) != 'x'){
            for(int g = 0; g < 20; g++){
               if(usuario[g] != read_ext_eeprom(g+posicao_na_memoria*20)){
                  usuario_match = FALSE;
               } //Fim if
                 //Senao o usuario_mach continua TRUE :)
            } //Fim for
            if(usuario_match){ //Se depois de todas as comparações continuou TRUE então desabilita a flag de continuar a busca
               continua_a_busca = FALSE;
            }
            else{             //Senao continua incrementando posições na memória
               posicao_na_memoria++; //incrementa a posição na memória EEPROM (Multiplica um fator de 20 que avança os 20 bytes necessários)
               usuario_match = TRUE; //Volta para TRUE para que possa fazer a verificação no próximo endereço de memória
            }
         } //Fim if de verificação do fim da memória
         else{
            continua_a_busca = FALSE;
            usuario_match = FALSE;
         } //Fim else de verificação da memória (desabilita a flag continua_a_busca porque cehgou ao fim da memória EEPROM)
      } // fim while de busca
      
      if(usuario_match && (posicao_na_memoria == 0)){ //Mensagem para o ADM que está sempre na primeira posição da memória (posição 0)
         printf(lcd_putc,"\f[ADM] Acesso\nAutorizado");
         /////Chamar função Ativa a Lâmpada
         for(int h = 0; h < 10000; h++){ /////////Fica esperando para ver se o ADM vai apertar a tecla para acessar o Menu
            if(kbd_getc() == 'A'){
            goto telaMenu; ///Vai pra tela de menu começando por cadastrar se o usuário apertar A
            }
         }
         goto telaID; ///// Se o ADM não apertar a tecla para o Menu, volta para o começo do programa
      }
      else if(usuario_match && (posicao_na_memoria > 0) ){ //Mensagem para outros usuários
         printf(lcd_putc,"\fAcesso\nAutorizado");
         /////Chamar função Ativa a Lâmpada
         delay_ms(1000);
         goto telaID;
      }
      else{    //Mensagem para o bandido hehehe
         printf(lcd_putc,"\fAcesso\nNegado");
      }
   }
   ///////////// FIM VERIFICA LOGIN
   
   ///////////// TELA MENU
   telaMenu:
   printf(lcd_putc,"\fAcessando\no menu");
   delay_ms(1000);
   goto opcaoCadastrar;
   //////////// FIM TELA MENU
   
   /////////// OPCAO CADASTRAR
   opcaoCadastrar:
   tecla = lastchar();
   switch(tecla){
      case 4:
         //goto 
      break;
      case 5:
         //goto
      break;
      case 6:
         goto opcaoRemover;
      break;
      default:
         goto opcaoCadastrar;
      break;
   }
   ////////// FIM OPCAO CADASTRAR
   
   /////////// OPCAO REMOVER
   opcaoRemover:
   tecla = lastchar();
   switch(tecla){
      case 4:
         //goto 
      break;
      case 5:
         //goto
      break;
      case 6:
         //goto
      break;
      default:
         goto opcaoRemover;
      break;
   }
   ////////// FIM OPCAO CADASTRAR
}

////////////////////// FUNÇÃO LASTCHAR
char lastchar(){
   char caractere = 0; //Inicia o char com 0 para que ele entre no loop
   while(caractere == 0){ //Fica verificando o caractere até que ele deixe de ser NULL
      caractere = kbd_getc();
   }
   return caractere; //Retorna o caractere quando ele não é NULL e o programa continua;
}
////////////////////// FIM FUNÇÃO LASTCHAR

