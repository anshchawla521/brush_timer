#define tim 20 // in seconds
#define led_pin 13
#define button_pin 2 // only 2 or 3
#define minpulsetime 30
#define maxpulsetime 1500

bool is_running = false;
unsigned long start_time = 0;
unsigned long last_blink = 0;
int time_left = 0;


void isr() {
  if (!is_running) {
    // not running
    start_time = millis();
    is_running = true;
    //Serial.println("i got called");
  }
}

void setup() {
  pinMode(led_pin , OUTPUT);
  pinMode(button_pin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_pin), isr, CHANGE);
  Serial.begin(9600);
}

void loop() {
  if (is_running) {
    if (millis() - start_time > tim*100) { // overflow automatically taken care of
      // time up 
      is_running = false;
    }else{
      // running and time not over 
      time_left = int(float(minpulsetime) +float(maxpulsetime-minpulsetime)*(float(start_time + tim*100 - millis()))/float(tim*100) ) ;
      //Serial.print("Time left ");
      //Serial.println(time_left);
      if(millis() -  last_blink >time_left){
        // time to change state
        last_blink = millis();
        //Serial.println("toggled led");
        digitalWrite(led_pin, !digitalRead(led_pin));//toggle
      }
      

      
    }
    
  }else{
    digitalWrite(led_pin , LOW);
    //goto sleep
    //Serial.println("i am sleeping");
    //delay(1000);
    
    }

}
