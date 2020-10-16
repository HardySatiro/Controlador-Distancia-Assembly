
#pragma config FOSC = HS 
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON 
#pragma config LVP = OFF 
#pragma config CPD = OFF 
#pragma config WRT = OFF 
#pragma config CP = OFF

#define _XTAL_FREQ 4000000
#define ESQUERDA 1
#define DIREITA 0
#include <xc.h>
#include <pic16f877a.h>
#include "lcd.h"

unsigned char unidade = 0;
unsigned char b[] = "HARDY";
int cont = 0;
char di, es; // variaveis para printar no LCD
int linha1[] = {0,0,1,1};
int linha2[] = {0,1,1,0};
int linha3[] = {1,1,0,0};
int linha4[] = {1,0,0,1};

float esq, dir; //variavaeis para calculo de angulo
int esa, dia; //variaveis para armazenar distancia


void atualizaDisplay(){  
    Set_Cursor(1, 1);
    LCD_writelcd("DESENVOLVIDO BY");
    __delay_ms(500);
    
}

void atualizaDisplay2(){
    
    Set_Cursor(2, 6);
    LCD_writelcd(b);
    __delay_ms(500);
    
}

void inicializacao(){
    OPTION_REGbits.nRBPU=0;
    
    TRISA = 0b00111000;
    TRISB = 0xFF; 
    TRISD = 0x00;
    TRISC = 0x00;// LCD Pins as Output 
    PORTC = 0x00;
    LCD_init();
    LCD_limpa();
    
    atualizaDisplay();
    atualizaDisplay2(); 
    __delay_ms(3000);
    LCD_limpa();
    T1CON = 0x00;
    
}

void passos(int direcao, int n){
    
    
    if(direcao == DIREITA){
        for(int j = 0; j <= n; j++){
            for(int i = 0; i < 5; i++){
                __delay_ms(3);
                RC4 = linha1[i];
                RC5 = linha2[i];
                RC6 = linha3[i];
                RC7 = linha4[i];
            }
            
        }
    }else if(direcao == ESQUERDA){
        for(int j = 0; j <= n; j++){
            for(int i = 4; i > -1; i--){
                __delay_ms(3);
                RC0 = linha1[i];
                RC1 = linha2[i];
                RC2 = linha3[i];
                RC3 = linha4[i];
            }
            
        }
    }
 
}

void sensord(){
    
   
    TMR1H = 0;                //Sets the Initial Value of Timer
    TMR1L = 0;                //Sets the Initial Value of Timer

    RA0 = 1;                  //TRIGGER HIGH
    __delay_us(10);           //10uS Delay 
    RA0 = 0;       //TRIGGER LOW

    while(!RA3);              //Waiting for Echo
    TMR1ON = 1;               //Timer Starts
    while(RA3);               //Waiting for Echo goes LOW
    TMR1ON = 0;               //Timer Stops

    dia = (TMR1L | (TMR1H<<8)); //Reads Timer Value
    dia = dia/58.82;              //Converts Time to Distance
   // a = a + 1;             //Distance Calibration
    if(dia>=2 && dia<=400){ 
        LCD_limpa();
          Set_Cursor(1,5);
          LCD_writelcd("Distance");

          Set_Cursor(2,14);
          di = (dia%10 + 48);
          LCD_escreve(di);

          dia = dia /10;
          Set_Cursor(2,13);
          di = (dia%10 + 48);
          LCD_escreve(di);

          dia = dia / 10;
          Set_Cursor(2,12);
          di = (dia%10 + 48);
          LCD_escreve(di);

          Set_Cursor(2,15);
          LCD_writelcd("cm");   
    } else {
        LCD_limpa();
        Set_Cursor(1,1);
        LCD_writelcd("Out of Range");
    } 

__delay_ms(400);

    
}

void sensore(){
    
    
    Set_Cursor(2,1);
    LCD_writelcd("asdlasdk");
       
    TMR1H = 0;                //Sets the Initial Value of Timer
    TMR1L = 0;                //Sets the Initial Value of Timer

    RA1 = 1;                  //TRIGGER HIGH
    __delay_us(10);           //10uS Delay 
    RA1= 0;       //TRIGGER LOW

    while(!RA4);              //Waiting for Echo
    TMR1ON = 1;               //Timer Starts
    while(RA4);               //Waiting for Echo goes LOW
    TMR1ON = 0;               //Timer Stops
    Set_Cursor(2,1);

    esa = (TMR1L | (TMR1H<<8)); //Reads Timer Value
    esa = esa/58.82;              //Converts Time to Distance
   // a = a + 1;             //Distance Calibration
    if(esa>=2 && esa<=400){ 
        LCD_limpa();
          Set_Cursor(1,5);
          LCD_writelcd("Distance");

          Set_Cursor(2,14);
          es = (esa%10 + 48);
          LCD_escreve(es);

          esa = esa /10;
          Set_Cursor(2,13);
          es = (esa%10 + 48);
          LCD_escreve(es);

          esa = esa / 10;
          Set_Cursor(2,12);
          es = (esa%10 + 48);
          LCD_escreve(es);

          Set_Cursor(2,15);
          LCD_writelcd("cm");   
    } else {
        LCD_limpa();
        Set_Cursor(1,1);
        LCD_writelcd("Out of Range");
    } 



}

void print(){
    
    Set_Cursor(1,1);
    LCD_writelcd("DIR:");
    
    
    
    
}

void main(){
    inicializacao();
    int n = 13;
    while(1){
        Set_Cursor(1,1);
        LCD_writelcd("Aperte um botão");
        if(RB0==0){
            passos(DIREITA, n); // mover motor direita
        }else if(RB1==0){
            passos(ESQUERDA, n); // mover motor esquerda
        }else if(RB2==0){
            sensord(); // calcular distancia sensor da direita
        }else if(RB3==0){   
            sensore(); // calcular distancia sensor da esquerda
        }
        
        
    }
}