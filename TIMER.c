#include "lib/include.h"
void (*PeriodicTask)(void);
extern void Configurar_Timer0A(void(*task)(void), unsigned long int periodo)
{
    SYSCTL->RCGCTIMER |= (1<<0) | (1<<0); //Encender el Periferico Timer 0 y 1  pag 380
    PeriodicTask = task; // asignar la direccion de memoria de la tarea a temporizar
    TIMER0->CTL = (0<<0);  // desabilitar el temporizador a usar antes de hacer cambios
    TIMER1->CTL = (0<<0);  
    TIMER0->CFG = 0x00000000; // modo de operacion 16 o 32 bits 
    TIMER1->CFG = 0x00000000;  
  
    // seleciona 32 bits con 0x0
    TIMER0->TAMR = (0x2<<0); //modo periodico pag 732
    TIMER1->TAMR = (0x2<<0); 

    TIMER0->TAILR = periodo - 1;   
    TIMER1->TAILR = periodo - 1;
    TIMER0->ICR = 1<<0; //se limpia el timer 
    TIMER1->ICR = 1<<0;  
    TIMER0->IMR = 1<<0; //habilitación de la mascara de la interrupción 
    TIMER1->IMR = 1<<0;
  
    NVIC->IP[4] = (NVIC->IP[4]&0x00FFFFFF) | 0x20000000;
    NVIC->ISER[0] = (1UL << 19); //pag 147
    // numero de interrupcion TIMER0A = 19 
    // n=19 ----> [4n+3] [4n+2] [4n+1] [4n] ---> [4n+3]

    TIMER0->CTL = (1<<0);
    TIMER1->CTL = (1<<1);


}

extern void Timer0A_Handler(void)
{
  TIMER0->ICR = 1<<0;// acknowledge TIMER0A timeout
  (*PeriodicTask)(); 
  TIMER1->ICR = 1<<0;// acknowledge TIMER0A timeout
  (*PeriodicTask)(); 
            
}