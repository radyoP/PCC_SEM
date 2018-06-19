#define SEND_FREQ 2500


/* ======= LedController ======= */
/**
   Purely virtual class
*/
class LedController {

  public:
    virtual void ON() = 0;

    virtual void OFF() = 0;

};


/* ======= WhiteLedController ======= */
/**
   Manages LED strips
*/
class WhiteLedController : LedController {
  private:
    const int warmLedPin;
    const int coldLedPin;

  public:
    WhiteLedController() {};
    WhiteLedController(int warmLedPin, int coldLedPin) : warmLedPin(warmLedPin), coldLedPin(coldLedPin)
    { ;
      pinMode(warmLedPin, OUTPUT);
      pinMode(coldLedPin, OUTPUT);
    };

    void ON() override {
      set(128, 128);
    };

    void OFF() override {
      set(0, 0);
    };

    void set(int warm, int cold) {
      analogWrite(warmLedPin, filter(warm));
      analogWrite(coldLedPin, filter(cold));
      Serial.print("warm: ");
      Serial.println(filter(warm));
      Serial.print("\n");
      Serial.print("cold: ");
      Serial.println(filter(cold));
      Serial.print("\n");
    }

  private:
    int filter(int val) {
      if (val > 255) return 255;
      if (val < 0)   return  0;
      return val;
    }
};



/* ======= SensorReader ====== */
/*
   Reads data from sensor
*/
class SensorReader {
  private:
    int sensorPin;

  public:
    SensorReader() {};

    SensorReader(int sensorPin) : sensorPin(sensorPin) {
      pinMode(sensorPin, INPUT);
    };

    int getValue() {
      return analogRead(sensorPin);
    }
};




/* ====== ControllerController ====== */

class ControllerController {
  private:
    WhiteLedController whiteLedController;
    SensorReader lightSensor;
    unsigned long sentTime = millis();
    char buff[20]; 
    int buff_idx = 0;

  public:
    ControllerController() {};
    ControllerController(int warmLedPin, int coldLedPin, int sensorPin) :
      whiteLedController(warmLedPin, coldLedPin),
      lightSensor(sensorPin){
      Serial.begin(9600);
      buff[19] = 0;
    }

    void act() {
      int warm, cold;
      if (getInput(&warm, &cold)) {
        whiteLedController.set(warm, cold);
      }
      if (millis() - sentTime > SEND_FREQ) {
        sentTime = millis();
        sendData();
      }
    }

  private:
    bool getInput(int* warm, int* cold) {
      while(Serial.available()>0) {
        char input = Serial.read();
        if(input == '\n'){
          buff[buff_idx] = '\0';
          bool ret = sscanf(buff, "%d %d", warm, cold) == 2;
          buff_idx = 0;
          serialFlush();
          return ret;   
        }else{
          buff[buff_idx] = input;
          buff_idx++;
          return false;
        }
      }
      return false;
        
    }

    void sendData() {
      Serial.println(lightSensor.getValue());
    }

    void read3(char* buff){
      for(int i = 0; i < 3; i++){
        buff[i] = Serial.read();
      }
      buff[3] = 0;
    }

   void serialFlush(){
    while(Serial.available() > 0) {
    char t = Serial.read();
  }
}  
};

ControllerController* controller;

void setup() {
  controller = new ControllerController(3, 5, A0);
}

void loop() {
  controller->act();
}
