/*
 Name:		FrequencyMeter.ino
 Created:	3/12/2025 7:08:24 AM
 Author:	Alexandr
*/

const int g_time_value = 3035; //Preload timer value (3035 for 1 seconds with 256 prescaller)
                               //https://deepbluembedded.com/arduino-timer-calculator-code-generator/

volatile bool g_bLedFlag = false;
volatile bool g_bActionFlag = false;



// процедура обработки прерывания переполнения счетчика
ISR(TIMER1_OVF_vect)
{
	cli();                   //запрещаем прерывания	

	TCNT1 = g_time_value;    // set preload timer
	g_bLedFlag = !g_bLedFlag;
	g_bActionFlag = true;

	sei();                   //разрешаем прерывания
}

ISR(TIMER2_OVF_vect)
{
	cli();                  //запрещаем прерывания	


	sei();                   //разрешаем прерывания
}


void setTimer_1_Interrupt() {

	cli();                    //запрещаем прерывания	
	TCCR1A = 0;
	TCCR1B = 0;

	TCNT1 = g_time_value;     // set preload timer

	//TIMER1 PRESCALLER
	// --------------------------------------
	// CS12  |  CS11  |  CS10   |  DESCRIPTION
	//   0   |    0   |    0    |  Timer/Counter Disabled
	//   0   |    0   |    1    |  No prescalling
	//   0   |    1   |    0    |  Clock / 8
	//   0   |    1   |    1    |  Clock / 64
	//   1   |    0   |    0    |  Clock / 256
	//   1   |    0   |    1    |  Clock / 1024

	//TCCR1B |= (1 << CS10);
	//TCCR1B |= (1 << CS11);
	TCCR1B |= (1 << CS12);    // 256 prescaler (коэффициент деления предделителя)
	TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt ISR (разрешаем вызов процедуры обработки прерывания переполнения счетчика)
	sei();                    // разрешаем прерывания
}

void setTimer_2_Interrupt() {

	//TIMER1 PRESCALLER
	// --------------------------------------
	// CS22  |  CS21  |  CS20   |  DESCRIPTION
	//   0   |    0   |    0    |  Timer/Counter2 Disabled
	//   0   |    0   |    1    |  No prescalling
	//   0   |    1   |    0    |  Clock / 8
	//   0   |    1   |    1    |  Clock / 32
	//   1   |    0   |    0    |  Clock / 64
	//   1   |    0   |    1    |  Clock / 128
	//   1   |    1   |    0    |  Clock / 256
	//   1   |    1   |    0    |  Clock / 1024


	cli();                    //запрещаем прерывания	
	TCCR2A = 0;
	TCCR2B = 0;	

	//Timer prescaller disabled
	//TCCR2B |= (1 << CS20);    // 1 prescaler (no prescalling)
	
	TIMSK2 |= (1 << TOIE2);   // enable timer overflow interrupt ISR (разрешаем вызов процедуры обработки прерывания переполнения счетчика)
	TCNT2 = 0;

	sei();                    // разрешаем прерывания
}




// the setup function runs once when you press reset or power the board
void setup() {

}

// the loop function runs over and over again until power down or reset
void loop() {
  
	// SLEEP instruction 
	sleep_enable();
	sleep_mode();
}
