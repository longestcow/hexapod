#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX


 
char c = ' ';
 
void setup() 
{
    Serial.begin(9600);
    BTserial.begin(9600);  
    

}
 
void loop()
{
 
 
    if (Serial.available())
    {
        c =  Serial.read();
        BTserial.write(c);  
    }
 
}


// steps for bluetooth to work https://www.martyncurrey.com/connecting-2-arduinos-by-bluetooth-using-a-hc-05-and-a-hc-06-easy-method-using-cmode/
// CONFIGURATION (hc05) (open btserial at 38400, press down the button for at mode)
// AT+ROLE=1 (master mode)
// AT+CMODE=1 (connect freely)
// AT+UART=9600,0,0 (this means btserial has to be open at 9600 for communication)
//CONFIGURATION (hc06) (open btserial at 9600)
// AT+BAUD4 (9600 baud just to make sure)
// unplug both
// cycle power of hc06 FIRST
// cycle power of hc05 (ensure its with baud rate 9600)
// should connect and then serial comm should work


// wiring for both =>
// vcc - 5v, gnd - gnd
// tx - directly to 2
// rx - voltage divider to 3
