#include "lib/include.h"

extern void Configurar_UART2(void)
{
    SYSCTL->RCGCUART  = (1<<2);   //Paso 1 (RCGCUART) pag.344 UARTEnable/modulo0 0->Disable 1->Enable
    SYSCTL->RCGCGPIO |= (1<<3);     //Paso 2 (RCGCGPIO) pag.340  clock port D
    //(GPIOAFSEL) pag.671 Enable alternate function
    GPIOA->AFSEL = (1<<1) | (1<<0);
    //GPIO Port Control (GPIOPCTL) PA0-> U0Rx PA1-> U0Tx pag.688
    GPIOA->PCTL = (GPIOA->PCTL&0xFFFFFF00) | 0x00000011;// (1<<0) | (1<<4);//0x00000011
    // GPIO Digital Enable (GPIODEN) pag.682
    GPIOA->DEN = (1<<0) | (1<<1);//PA1 PA0
    //UART2 UART Control (UARTCTL) pag.918 DISABLE!!
    UART2->CTL = (0<<9) | (0<<8) | (0<<0);

    // UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    /*
    BRD = 40,000,000 / (16*115200) = 21.7013
    UARTFBRD[DIVFRAC] = integer(.7013 * 64 + 0.5) = 45.3832
    */
    UART2->IBRD = 27;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART2->FBRD = 46;
    //  UART Line Control (UARTLCRH) pag.916
    UART2->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
    UART2->CC =(0<<0);
    //Disable UART0 UART Control (UARTCTL) pag.918
    UART2->CTL = (1<<0) | (1<<8) | (1<<9);



}

extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART2->FR & (1<<4)) != 0 );
    v = UART2->DR & 0xFF;
    c = v;
    return c;
}
extern void printChar(char c)
{
    while((UART2->FR & (1<<5)) != 0 );
    UART2->DR = c;
}
extern void printString(char* string)
{
    while(*string)
    {
        printChar(*(string++));
    }
}

extern char * readString(char delimitador)
{
   int i=0;
   char *string = (char *)calloc(10,sizeof(char));
   char c = readChar();
   while(c != delimitador)
   {
       *(string+i) = c;
       i++;
       if(i%10==0)
       {
           string = realloc(string,(i+10)*sizeof(char));
       }
       c = readChar();
   }

   return string;

}
//Experimento 2

//El envio es su nombre  (rave) 

// invertirlo y regresarlo con numeros consecutivos
// entre letras (e1v2a3r) 

/*
extern char * readString(char delimitador)
{
   int i=0;
   char *string = (char *)calloc(10,sizeof(char));
   char c = readChar();
   while(c != delimitador)
   {
       *(string+i) = c;
       i++;
       c = readChar();
   }
    int j = 0;
   while(i != 0)
   {
       *(string+i) = c;
       i--;
       if(i%10==0)
       {
           string = realloc(string,(i+10)*sizeof(char));
       }
       c = readChar();
       j++;
   }
   return string;
}


extern int readString(char delimitador, char *string)
{
   int i = 0;
   char c = readChar();

   while(c != delimitador)
   { 
            string[i] = c;
            i++;
            c = readChar(); 
   }

   return i;
}
*/