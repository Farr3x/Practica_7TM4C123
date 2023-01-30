#include "lib/include.h"

uint16_t Result[6], duty[2];
void Hilo_1(void)
{
    /*
 //llamada a la conversion por procesador
    PWM0->_1_CMPB = duty[0];
    PWM0->_1_CMPA = duty[1];
    PWM0->_0_CMPA = 1500;    
    */
    GPIOB->DATA = (1<<0);
    ADC0_InSeq2(Result,duty);
    GPIOB->DATA = (0<<0);
    

}

int main(void)
{

    Configurar_PLL(_40MHZ);  //Confiuracion de velocidad de reloj
    Configurar_UART3();//Yo FCLK 40MHZ Baudrate 115200
    Configurar_GPIO();
    Configura_Reg_ADC0();
    Configura_Reg_PWM1(50);
    Configurar_Timer0A(&Hilo_1,10000);
    ADC0_InSeq1(Result, duty);
    ADC0_InSeq2(Result, duty);
    while(1)
    {
        ADC0_InSeq1(Result, duty);
        ADC0_InSeq2(Result, duty);
    }
}