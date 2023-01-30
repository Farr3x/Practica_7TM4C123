#include "lib/include.h"

extern void Configurar_UART3(void)
{
    SYSCTL->RCGCUART  = (1<<3);   //Paso 1 (RCGCUART) pag.344 UARTEnable/modulo0 0->Disable 1->Enable
    SYSCTL->RCGCGPIO |= (1<<2);     //Paso 2 (RCGCGPIO) pag.340  clock port D
    //(GPIOAFSEL) pag.671 Enable alternate function

    GPIOC->AFSEL = (1<<6) | (1<<7);     //Rx | Tx
    //GPIO Port Control (GPIOPCTL) PA0-> U0Rx PA1-> U0Tx pag.688
    GPIOC->PCTL = (GPIOC->PCTL&0x00FFFFFF) | 0x11000000;// (1<<0) | (1<<4);//0x00000011
    // GPIO Digital Enable (GPIOCEN) pag.682
    GPIOC->DEN = (1<<6) | (1<<7);//PD6 Rx PD7 Tx
    //UART3 UART Control (UARTCTL) pag.918 DISABLE!!
    UART3->CTL = (0<<9) | (0<<8) | (0<<0) | (0<<4) ;

    /* 
    UART Integer Baud-Rate Divisor (UARTIBRD) pag.914
    BRD = 40,000,000 / (16*115200) = 21.7013
    UARTFBRD[DIVFRAC] = integer(.7013 * 64 + 0.5) = 45.3832
    */

    UART3->IBRD = 21;
    // UART Fractional Baud-Rate Divisor (UARTFBRD) pag.915
    UART3->FBRD = 45;
    //  UART Line Control (UARTLCRH) pag.916
    UART3->LCRH = (0x3<<5)|(1<<4);
    //  UART Clock Configuration(UARTCC) pag.939
    UART3->CC =(0<<0);
    //Disable UART0 UART Control (UARTCTL) pag.918
    UART3->CTL = (1<<0)| (1<<8) | (1<<9)| (1<<4);
}

extern char readChar(void)
{
    //UART FR flag pag 911
    //UART DR data 906
    int v;
    char c;
    while((UART3->FR & (1<<4)) != 0 );
    v = UART3->DR & 0xFF;
    c = v;
    return c;
}

extern void printChar(char c)
{
    while((UART3->FR & (1<<5)) != 0 );
    UART3->DR = c;
}

extern void printString(char *string)
{
    while(*string)
    {
        printChar(*(string++));
    }
}

extern int readString(char delimitador, char *string, char rc)
{
    int i = 0;
    while(rc != delimitador)
    {
        *(string+i) = rc;
        i++;
        rc = readChar();
    }
    return i;
}

extern int invString(int dim, char *string, char *inv)
{
    int i = 0;
    while(dim > 0)
    {
        *(inv+i) = *(string+dim-1);
        i++;
        dim--;
    }
    return i;
}

extern int numString(int dim, char *string, char *numst)
{
    //int i = dim*2 + 1;
    int i = 0, j = 0, k;
    short unsigned int par = 1;
    while(dim > j)
    {
        //if(i%2 != 1)
        if(par != 0)
        {
            *(numst+i) = *(string+j);
            i++;
            par = 0;
        }
        else
        {
            j++;
            //*(numst+i) = j;
            k = NumToChar(j, numst+i);
            /*if(k%2 != 1)
            {
                k++;
            }*/
            i = i + k;
            par = 1;
        }
    }
    return i;
}

extern int NumToChar(int g, char *pstring)
{
    int i = 1, k = 0, h = g;
    while(h/10 > 0)
    {
        i++;
        h = h/10;
    }
    for(int j = i; j > 0; j--)
    { 
        int u = pow(10,(j-1));
        *(pstring+k) = (g / u) + 48;
        k++;
        g = g - u*(g/u);
    }
    return k;
}

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
       if(i%10==0)
       {
           string = realloc(string,(i+10)*sizeof(char));
       }
       c = readChar();
   }
   return string;
}
*/

//Experimento 2

//El envio es su nombre  (rave) 

// invertirlo y regresarlo con numeros consecutivos
// entre letras (e1v2a3r) 