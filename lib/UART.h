#ifndef UART_UART_H_
#define UART_UART_H_

extern void Configurar_UART3(void);
extern char readChar(void);
extern void printChar(char c);
extern void printString(char *string);
extern int readString(char delimitador, char *string, char rc);
extern int invString(int dim, char *string, char *inv);
extern int numString(int dim, char *string, char *numst);
extern int NumToChar(int g, char *string);

#endif /* UART_UART_H_ */