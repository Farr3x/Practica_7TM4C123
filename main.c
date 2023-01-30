#include "lib/include.h"

int main(void)
{
    uint16_t Result[6];
    Configurar_PLL(_40MHZ);  //Confiuracion de velocidad de reloj
    Configurar_UART3();//Yo FCLK 40MHZ Baudrate 115200
    Configurar_GPIO();
    Configura_Reg_ADC0();
    Configura_Reg_PWM1(50);
    ADC0_InSeq1(Result);
    ADC0_InSeq2(Result);
    while(1)
    {
        ADC0_InSeq1(Result);
        ADC0_InSeq2(Result);
    }
}