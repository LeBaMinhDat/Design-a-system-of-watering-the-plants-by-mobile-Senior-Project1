/*
#################################################################
 #  SENIOR PROJECT 2                                           #
 #  TOPIC : DESIGN A SYSTEM OF WATERING THE PLANTS BY MOBILE   #
 #                                                             #
 #       Advisor: Assoc. Prof. TRUONG NGOC SON                 #
 #       Student:                                              #
 #        LE THI KIEU GIANG   ID Student: 19119001             #
 #        NGUYEN HUNG THINH   ID Student: 19119056             #
#################################################################
*/
#define RAIN_PIN_LED 12
#define RED_PIN 11
#define YELLOW_PIN 10
#define GREEN_PIN 9
#define PIN_Waterlevel_notification 6
#define PIN_Rain_notification 5
void setup() {
  Serial.begin(115200);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(RED_PIN,OUTPUT);
  pinMode(YELLOW_PIN,OUTPUT);
  pinMode(GREEN_PIN,OUTPUT);
  pinMode(RAIN_PIN_LED, OUTPUT);
  digitalWrite(RED_PIN,LOW);
  digitalWrite(RAIN_PIN_LED,LOW);
  digitalWrite(YELLOW_PIN,LOW);
  digitalWrite(GREEN_PIN,LOW);
  pinMode(PIN_Rain_notification,OUTPUT);
  pinMode(PIN_Waterlevel_notification,OUTPUT);
  Serial.println("Connect success");
}

void loop() {
  int Rain_value = analogRead(A0);
  int Waterlevel_value = analogRead(A1);
//  Serial.println(Rain_value);
 Serial.println(Waterlevel_value);
  if (Rain_value >= 700)
  {
//    Serial.println("SUNNY");
    digitalWrite(PIN_Rain_notification,LOW);
    digitalWrite(RAIN_PIN_LED,LOW);
    delay(50);  
  } else
  {
//    Serial.println("RAIN");
    digitalWrite(PIN_Rain_notification,HIGH);
    digitalWrite(RAIN_PIN_LED,HIGH);
    delay(50); 
    digitalWrite(RAIN_PIN_LED,LOW);
    delay(50);
    digitalWrite(RAIN_PIN_LED,HIGH);
    delay(50); 
  }
if (Waterlevel_value <= 150){
    digitalWrite(RED_PIN,HIGH);
    digitalWrite(YELLOW_PIN,LOW);
    digitalWrite(GREEN_PIN,LOW);
    digitalWrite(PIN_Waterlevel_notification,LOW);
    delay(50); 
   } 
   else if(Waterlevel_value <= 300)
   {
    digitalWrite(YELLOW_PIN,HIGH);
    digitalWrite(RED_PIN,LOW);
    digitalWrite(GREEN_PIN,LOW);
    digitalWrite(PIN_Waterlevel_notification,LOW);
    delay(50); 
   }
    else if(Waterlevel_value > 450)
   {
    digitalWrite(GREEN_PIN,HIGH);
    digitalWrite(YELLOW_PIN,LOW);
    digitalWrite(RED_PIN,LOW);
    digitalWrite(PIN_Waterlevel_notification,HIGH);
    delay(50); 
   } 
}
