int audio_read_head = 0;
int audio_write_head = 0;

int cnt = 0;
int des = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome");
  // put your setup code here, to run once:
  TCCR2A = (1<<COM2A0) | (1<<WGM21) | (1<<WGM20); //Setup pwm, toggle oc2a when compare match
  TCCR2B = (1<<CS00) | (1<<WGM22); //Waveform generation and no prescaling
  OCR2A = 1;
  DDRB |= (1<<PB3);

  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0;

  OCR0A = 1;

  TCCR0A |= (1 << WGM01); //CTC Mode
  TCCR0B |= (1 << CS00 | 1 << CS01); //Prescaler 1
  
  TIMSK0 |= (1 << OCIE0A); //Enable interrupt
  sei();
}

void loop() {
    if(Serial.available() > 0)
    {
      des = Serial.parseInt();
      Serial.println("OK");
    }
}

ISR(TIMER0_COMPA_vect){
   cnt++;
   if(cnt > des)
   {
    OCR2A ^= 1;
    cnt = 0;
   }
   
}
