#include "uart.h"
#include "queue.h"

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void init_UART(unsigned ubrr)
{
	rx_queue = queue_new();
	tx_queue = queue_new();
	rx_queue_length = 0;
	tx_queue_length = 0;

	rx_overflow_flag = false;
	
	//Set baud rate
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;

	//Enable receiver and transmitter
	//TODO: double check no |= is OK
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	//Set frame format: 8 data, 1 stop bit 
	//TODO: double check no |= is OK
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); //for 2 stop bit: (1<<USBS0)|(3<<UCSZ00);

	UCSR0B |= (1 << RXCIE0); //Enable receive complete interrupt
}

bool UART_enqueue(unsigned char entry_)
{
	if(tx_queue_length >= UART_QUEUE_MAX_LENGTH) {
		return false;
	}

	unsigned char *entry = (unsigned char *)malloc(sizeof(unsigned char));

	if(!entry){
		return false;
	}

	*entry = entry_;
	queue_push_head(tx_queue, entry);

	tx_queue_length++;
	return true;
}

bool UART_enqueue_string(unsigned char* str)
{
	if(strlen(str) + 1 > UART_QUEUE_MAX_LENGTH - tx_queue_length){
		return false;
	}

	while(*str != '\0'){
		
		unsigned char *entry = (unsigned char *)malloc(sizeof(unsigned char));

		if(!entry){
			return false;
		}

		*entry = *str;
		queue_push_head(tx_queue, entry);

		tx_queue_length++;
		str++;
	}

	unsigned char *entry_termination = (unsigned char *)malloc(sizeof(unsigned char));

	if(!entry_termination){
		return false;
	}

	*entry_termination = '\0';
	queue_push_head(tx_queue, entry_termination);

	tx_queue_length++;	

	return true;
}

bool UART_write()
{
	if(tx_queue_length < 1 || !(UCSR0A & (1 << UDRE0))){
		return false;
	}

	unsigned char *to_write = (unsigned char *)queue_pop_tail(tx_queue);

	UDR0 = *to_write;

	free(to_write);

	tx_queue_length--;
	return true;
}

bool UART_enqueue_urgent(unsigned char to_write)
{
	unsigned char *entry = (unsigned char *)malloc(sizeof(unsigned char));

	if(!entry){
		return false;
	}

	*entry = to_write;
	queue_push_tail(tx_queue, entry);

	tx_queue_length++;
	return true;
}

bool UART_write_flush()
{
	if(tx_queue_length < 1 || !(UCSR0A & (1 << UDRE0))){
		return false;
	}

	while(tx_queue_length > 0){
		while ((UCSR0A & (1 << UDRE0)) == 0) {};
		UART_write();
	}

	return true;
}
/*
void UART_write(unsigned char to_write)
{
	while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
	UDR0 = to_write; // Echo back the received byte back to the computer
}*/

//TODO: Receive triggers interrupt, queues the new character, main() dequeues
//TODO: Check if it works with the thermal interrupt contantly called
//TODO: Check for error flags
//TODO: System for re-requesting information if errored
//TODO: Funtion for interpreting commands
unsigned char UART_read()
{
	if(rx_queue_length < 1){
		return '\0';
	}

	unsigned char *just_read_ = (unsigned char *)queue_pop_tail(rx_queue);

	unsigned char just_read = *just_read_;

	free(just_read_);

	rx_queue_length--;
	return just_read;

	/*
	unsigned char received;
	while ((UCSR0A & (1 << RXC0)) == 0) {}; // Do nothing until data have been received and is ready to be read from UDR
	received = UDR0; // Fetch the received byte value into the variable "ByteReceived"
	return received;
	*/

}

ISR(USART_RX_vect)
{
	if(rx_queue_length >= UART_QUEUE_MAX_LENGTH){
		rx_overflow_flag = true;
		return;
	}

	unsigned char *entry = (unsigned char *)malloc(sizeof(unsigned char));

	if(!entry){
		rx_overflow_flag = true;
		return;
	}

	*entry = UDR0;
	queue_push_head(rx_queue, entry);

	rx_queue_length++;
	return;
}