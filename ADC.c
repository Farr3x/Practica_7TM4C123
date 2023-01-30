#include "lib/include.h"

extern void Configura_Reg_ADC0(void)
{
    /*
    Habilitar el modulo 0 del ADC con 6 canales analogicos 
    en el puerto E y D a una velocidad de conversion de 1Msps
    dandole la mayor prioridad al secuenciador 2 con evento
    de procesador 
    */
     //Pag 352 para inicializar el modulo de reloj del adc RCGCADC
    SYSCTL->RCGCADC = (1<<0); 
    //Pag 340 (RGCGPIO) Puertos base habilitación del reloj
    //                     F     E      D       C      B     A
    SYSCTL->RCGCGPIO |= (1<<5)|(1<<4)|(1<<3)|(0<<2)|(0<<1)|(0<<0);
    //Pag 663 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida
    GPIOE->DIR = (0<<2) | (0<<1) | (0<<4)| (0<<5); //PE2(AIN1), PE1(AIN2), PE4(AIN9), PE5(AIN8)
    GPIOD->DIR = (0<<3) | (0<<2); //PD3(AIN4), PD2(AIN5)
    //(GPIOAFSEL) pag.770 Enable alternate función para que el modulo analógico tenga control de esos pines
    GPIOE->AFSEL =  (1<<2) | (1<<1)| (1<<4)| (1<<5);
    GPIOD->AFSEL =  (1<<2) | (1<<3);
    //(GPIODEN) pag.781 desabilita el modo digital
    GPIOE->DEN = (0<<2) | (0<<1) | (0<<4) | (0<<5 );
    GPIOD->DEN = (0<<3) | (0<<2);;
    //Pag 787 GPIOPCTL registro combinado con el GPIOAFSEL y la tabla pag 1808
    GPIOE->PCTL = GPIOE->PCTL & (0xFF00F00F);
    GPIOD->PCTL = GPIOD->PCTL & (0xFFFFF00F);
    //(GPIOAMSEL) pag.687 habilitar analogico
    GPIOE->AMSEL =  (1<<2) | (1<<1)| (1<<4)| (1<<5);
    GPIOD->AMSEL =  (1<<2) | (1<<3);

    //Pag 891 El registro (ADCPC) establece la velocidad de conversión por segundo
    ADC0->PC = 0x3;//250ksps
    //Pag 841 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores
    ADC0->SSPRI = 0x3021;
    //Pag 821 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS  = (0<<3) | (0<<2) | (0<<1) | (0<<0);
    //Pag 833 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
    ADC0->EMUX  = (0x0FF0);
    //Pag 867 Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado
    ADC0->SSMUX2 = 0x0421;  //AIN4, AIN2, AIN1
    ADC0->SSMUX1 = 0x0985;  //AIN9, AIN8, AIN5
    //pag 868 Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción
    ADC0->SSCTL1 = (1<<10) | (1<<9) | (1<<6) | (1<<5) | (1<<2) | (1<<1) ;
    ADC0->SSCTL2 = (1<<10) | (1<<9) | (1<<6) | (1<<5) | (1<<2) | (1<<1) ;
    /* Enable ADC Interrupt */
    ADC0->IM |= (1<<1) | (1<<2); /* Unmask ADC0 sequence 1 and 2 interrupt pag 825*/
    //NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFFFF00) | 0x00000020;
    //NVIC_EN0_R = 0x00010000;
    //Pag 821 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS = (1<<3) | (1<<2) | (1<<1) | (1<<0);
    ADC0->PSSI |= (1<<2) | (1<<1);      //Iniciar el muestreo en el seq 1 y 2. Pag. 841
}

extern void ADC0_InSeq2(uint16_t *Lect)
{
    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC0->PSSI = (1<<2);
       while((ADC0->RIS&0x04)==0){}; // espera al convertidor
       Lect[2] = ADC0->SSFIFO2&0xFFF;
       Lect[1] = ADC0->SSFIFO2&0xFFF; //  Leer  el resultado almacenado en la pila2
       Lect[0] = ADC0->SSFIFO2&0xFFF;
       //printChar('A');
       ADC0->ISC = 0x0004;  //Conversion finalizada
}

extern void ADC0_InSeq1(uint16_t *Lect)
{
    //ADC Processor Sample Sequence Initiate (ADCPSSI)
       ADC0->PSSI = (1<<1);
       while((ADC0->RIS&0x02)==0){}; // espera al convertidor
       Lect[5] = ADC0->SSFIFO2&0xFFF;
       Lect[4] = ADC0->SSFIFO2&0xFFF; //  Leer  el resultado almacenado en la pila2
       Lect[3] = ADC0->SSFIFO2&0xFFF;
       //printChar('A');
       ADC0->ISC = 0x0002;  //Conversion finalizada
}