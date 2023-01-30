
#include "lib/include.h"

#include "lib/include.h"

extern void Configura_Reg_PWM1(uint16_t freq)
{
    SYSCTL->RCGCPWM |= (1<<0);    
    SYSCTL->RCGCGPIO |= (1<<1); 
    SYSCTL->RCC |=(1<<20);   
    SYSCTL->RCC &= 0xFFF0FFFF; 
    GPIOB->AFSEL |= (1<<4); 
    GPIOB->PCTL |= 0x00040000; 
    GPIOB->DEN |= (1<<4);
    PWM1->_1_CTL &= ~(1<<0);
    PWM1->_1_GENA = 0x008C; 
    PWM1->_1_LOAD = 2500;
    PWM1->_1_CMPB = 2000;
    PWM1->_1_CMPA = 2000; 
    PWM1->_1_CTL |= (1<<0);
    PWM1->ENABLE = (1<<2);
}


extern void Config_PWM_Exp1(uint16_t freq)      //Configuración para el experimento 1
{
    
    SYSCTL->RCGCPWM |= (1<<0); /*Enable reloj de modulo PWM0 pag 354*/
    SYSCTL->RCGCGPIO |= (1<<1); /*Enable reloj de GPIO Puerto B pag 340 pin 5*/
   // GPIOF->AFSEL |= (1<<3)|(1<<2)|(1<<1); /*Control de registros ya sea por GPIO o Otros Pag 672*/
    GPIOF->AFSEL |= 0x30;
    GPIOF->PCTL |= (GPIOF->PCTL&0xFFFF000F) | 0x00006660; /*Combinado con la tabla Pag 1351 y el registro PCTL le digo que es pwm Pag 689*/
    GPIOF->DEN |= 0x30; /* para decirle si es digital o no Pag 682*/
    SYSCTL->RCC |= (1<<20);  /*Enable o Disable Divisor  Pag 1747*/
    PWM0->_0_CTL = (0<<0);
    PWM0->_1_CTL = (0<<0); /*Bloqueo y desbloqueo*/
    PWM0->_1_GENB = 0x0000080C; /*Registro de las acciones del pwm Pag 1285*/
    PWM0->_1_GENA = 0x0000008C; /*Registro de las acciones del pwm Pag 1282*/
    PWM0->_0_GENB = 0x0000008C;//PWM5
    PWM0->_1_LOAD = (int)(20000000/freq); /*cuentas=fclk/fpwm  para 1khz cuentas = (16,000,000/1000)*/
    PWM0->_0_LOAD = (int)(20000000/freq);
    PWM0->_1_CMPB = 15000;
    PWM0->_1_CMPA = 15000;
    PWM0->_0_CMPA = 15000;
    PWM0->_1_CTL = (1<<0);// Se activa el generador 3
    PWM0->_0_CTL = (1<<0);// Se activa el generador 2
    PWM0->ENABLE = (1<<3) | (1<<2) | (1<<1); /*habilitar el bloque pa que pase Pag 1247*/
    
} 