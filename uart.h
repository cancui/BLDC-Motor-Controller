#ifndef UART_H
#define UART_H

#include "queue.h"

#include <stdbool.h>
#include <stdint.h>

#define FOSC_UART 16000000UL // Clock Speed
#define BAUD_UART 9600
#define UBRR_UART (FOSC_UART/16/BAUD_UART-1)

#define UART_QUEUE_MAX_LENGTH 30

//Possible messages to receive and send
typedef enum {
	MESSAGE_1 = 0,
	MESSAGE_2
} UART_commands;

Queue *rx_queue; 
Queue *tx_queue;
uint8_t rx_queue_length;
uint8_t tx_queue_length;

volatile bool rx_overflow_flag;

void init_UART(unsigned ubrr);

bool UART_enqueue(char entry_);
bool UART_enqueue_urgent(char to_write);
bool UART_enqueue_string(char* str);
bool UART_write();
bool UART_write_flush();

char UART_read();
void UART_interpret(); //For ISR
void UART_receive(); //For ISR (doing the work in the actual ISR seems better)

void UART_test_return_chars();

#endif