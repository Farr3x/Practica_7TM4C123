#include "lib/include.h"

int main(void)
{
    uint16_t Result[6];
    Configurar_PLL(_40MHZ);  //Confiuracion de velocidad de reloj
    Configurar_UART3();//Yo FCLK 40MHZ Baudrate 115200
    Configurar_GPIO();
    Configura_Reg_ADC0();
    ADC0_InSeq1(*Result);
    ADC0_InSeq2(*Result);
    while(1)
    {
        ADC0_InSeq1(*Result);
        ADC0_InSeq2(*Result);
        unsigned long int Valor[6];
        Valor[0] = Result[0];
        Valor[1] = Result[1];
        Valor[2] = Result[2];
        Valor[3] = Result[3];
        Valor[4] = Result[4];
        Valor[5] = Result[5];
    }
}