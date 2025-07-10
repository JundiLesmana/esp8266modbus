/*------ modbus tcp -----*/
#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else //ESP32
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>
/*------------------------*/

const char* ssid = "your wifi";
const char* passphrase = "password wifi"; 

int ModbusTCP_port = 502;

//PIN DEFINE 
#define LED_BI D2 //LEDBUILT-IN
/*
#define LED_1 14 //LED 1
#define LED_2  12 //LED 2
#define LED_3 13 //LED 3
#define LED_4 15 //LED 4
*/

//MODBUS REGISTER MAP
const int Reg1 = 0; //40001

/*
const int Dig1 = 0; //00001---Tambahan
const int Dig2 = 1; //00002
const int Dig3 = 2; //00003
const int Dig4 = 3; //00004
*/

//ModbusIP object
ModbusIP mb;

long ts;
int Random1, Random2, Random3, Random4;

void setup() {
 // put your setup code here, to run once:
 Serial.begin(115200);

 pinMode(LED_BI,OUTPUT);
 /*
 pinMode(LED_1,OUTPUT);
 pinMode(LED_2,OUTPUT);
 pinMode(LED_3,OUTPUT);
 pinMode(LED_4,OUTPUT);
 */
 
 //==================================
 //==================================
 delay(3000);
 //==================================
 Serial.println();
 Serial.println("Disconnecting current wifi connection");
 WiFi.disconnect();
 delay(10);
 
 ts = millis();
 
 Serial.println();
 Serial.println();
 Serial.println("Startup");
  
 digitalWrite(LED_BI,HIGH);
 delay(100);
 digitalWrite(LED_BI,LOW);
 delay(1000); 

 //----------------------------------------------------------- 
 IPAddress IP(192,168,0,23); //-------
 IPAddress NETMASK(255,255,255,0);
 IPAddress NETWORK(192,168,0,1); //--------
 IPAddress DNS(8,8,8,8);
 WiFi.config(IP, NETWORK, NETMASK, DNS);  

 WiFi.mode(WIFI_STA);
 //====================================
 WiFi.begin(ssid, passphrase );
 Serial.println();
 Serial.println("Waiting.");
  
 while ((WiFi.status() != WL_CONNECTED))
 {     
    Serial.print("."); //cetak . dilayar SerialMonitor
    delay(250);
 }
 //-----------------  

 Serial.println("Connected ");
 Serial.println("ESP8266 Slave Modbus TCP/IP ");
 Serial.print("IP Address: ");
 Serial.print(WiFi.localIP());
 Serial.print(":");
 Serial.println(String(ModbusTCP_port));
 Serial.print("MAC Address: ");
 Serial.println(WiFi.macAddress());
 Serial.println("Modbus TCP/IP Online");
 Serial.println(" ");
 delay(100);
 
 //---------Connecting to router, ----------------
 mb.server();
 mb.addHreg(Reg1);//40001
 mb.addHreg(Reg2);//40002
 mb.addHreg(Reg3);//40003
 mb.addHreg(Reg4);//40004
 /* 
 mb.addCoil(Dig1);//00001
 mb.addCoil(Dig2);//00002
 mb.addCoil(Dig3);//00003
 mb.addCoil(Dig4);//00004
*/

  
}

void loop() {
 // put your main code here, to run repeatedly:
 mb.task();
        ts = millis();
        /*-------------------BLINK---------------*/
        //digitalWrite(LED_BI,!digitalRead(LED_BI));
        /*-------------------BLINK---------------*/
         if (Reg1 == 1){
          digitalWrite(LED_BI,HIGH);
          }
          if (Reg1 == 0){
          digitalWrite(LED_BI,LOW);
          }
        /*
        mb.Hreg(Reg1, random(0,99));
        mb.Hreg(Reg2, random(100,199));
        mb.Hreg(Reg3, random(200,299));
        mb.Hreg(Reg4, random(300,399));
        //Tambahan
        digitalWrite(LED_1, mb.Coil(Dig1));
        digitalWrite(LED_2, mb.Coil(Dig2));
        digitalWrite(LED_3, mb.Coil(Dig3));
        digitalWrite(LED_4, mb.Coil(Dig4));
       */
       
        Serial.print(mb.Hreg(Reg1));
        Serial.print(", ");
        Serial.print(mb.Hreg(Reg2));
        Serial.print(", ");
        Serial.print(mb.Hreg(Reg3));
        Serial.print(", ");
        Serial.println(mb.Hreg(Reg4));
        

}
