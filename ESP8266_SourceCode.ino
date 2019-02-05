#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TRIGGERPIN D1
#define ECHOPIN    D2
#define LEDMOTOR   D5

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] ="";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "My";
char pass[] = "admin123";

WidgetLCD lcd(V1);
WidgetLED led1(V4);



void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(LEDMOTOR, OUTPUT);
 
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  lcd.clear(); //Use it to clear the LCD Widget
  //lcd.print(0, 0, "Distance to water surface in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  // Please use timed events when LCD printintg in void loop to avoid sending too many commands
  // It will cause a FLOOD Error, and connection will be dropped
 
}

void loop()
{
  lcd.clear();
  //lcd.print(0, 0, "WaterLevl in %"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  long duration, distance;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println("cm");

    Distance(distance);
  

  
 
 
  Blynk.run();

  delay(1000);

}

void Distance(long dist){

     //Precentage Calculation

      long distance;

       distance=100-((dist/50.0)*100.0);
       
        Serial.print(distance);
        Serial.println(" % precentage");
        
    if(distance<101){ 
        
        //level widget
        Blynk.virtualWrite(V2, distance);
  
         //  Graph
        Blynk.virtualWrite(V5, distance);
        Blynk.virtualWrite(V5, distance);
 
        if(distance >90){
          
        lcd.clear();
        lcd.print(0, 1, "Full Capacity");
        led1.off();
        digitalWrite(LEDMOTOR, LOW);
     
        }else if(distance <10){

         lcd.clear();
         lcd.print(0, 0, "Water Pump ON");
         led1.on();
         digitalWrite(LEDMOTOR, HIGH);
      
       }else{
         lcd.clear();
         lcd.print(7, 1, distance);
         led1.on();
         digitalWrite(LEDMOTOR, HIGH);
       }

   }else{
           lcd.clear();
           lcd.print(0, 1, "Calibration Err");
           led1.off();
           digitalWrite(LEDMOTOR, LOW);
          }

  
  }
