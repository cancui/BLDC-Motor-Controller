void set_flash_green()
{
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
	OCR1A   = 1562; // Set CTC compare value to 10Hz at 16MHz AVR clock, with a prescaler of 1024
	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt
	TCCR1B |= ((1 << CS10) | (1 << CS12)); // Start timer at Fcpu/1024
	
	/*
	while(true) {
		//TCNT1 = 0;
		if (TIFR1 & (1 << OCF1A)) {
			TOG_LED_GREEN();
			TIFR1 = (1 << OCF1A); // clear the CTC flag (writing a logic one to the set flag clears it)
		}
	}*/
}

void set_flash_red()
{
	TCCR0A |= (1 << WGM01); // Configure timer 0 for CTC mode
	OCR0A = 255; // delay of ~16 ms
	TIMSK0 |= (1 << OCIE0A);  //Enable CTC interrupt
	TCCR0B |= ((1 << CS02) | (1 << CS00)); // Start timer at Fcpu/1024
}

void set_flash_yellow()
{
	TCCR2A |= (1 << WGM21);
	OCR2A = 255;
	TIMSK2 |= (1 << OCIE2A);
	TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20)); // Start timer at Fcpu/1024
}

ISR(TIMER1_COMPA_vect)
{
	TOG_LED_GREEN();
}

ISR(TIMER0_COMPA_vect)
{
	static uint8_t red_count = 1;
	if(red_count >= 7) {
		TOG_LED_RED();
		red_count = 0;
	}
	red_count++;
}

ISR(TIMER2_COMPA_vect)
{
	static uint8_t yellow_count = 1;
	if(yellow_count >= 7) {
		TOG_LED_YELLOW();
		yellow_count = 0;
	}
	yellow_count++;
}