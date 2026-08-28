#include <DHT.h>
#include <DHT_U.h>

#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

#include <DHT.h>
#include <DHT_U.h>

#include "DHT.h"
#include <WiFi.h>
#include <WiFiClient.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


#define DHTPIN 5     // what digital pin we're connected to 

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "project"; // Your ssid

const char* password = "project1234"; // Your Password

 

char status;

double T,P,p0,a;

WiFiServer server(80);

void setup() {

Serial.begin(9600);
pinMode(18, INPUT);
pinMode(19, INPUT);
pinMode(15, INPUT);
pinMode(23, OUTPUT);

delay(100);

dht.begin();
lcd.init(); // initialize the lcd
lcd.backlight();
Serial.print("Connecting to ");

Serial.println(ssid);

WiFi.begin(ssid, password);

//lcd.begin(16, 2);
 
while (WiFi.status() != WL_CONNECTED) {

delay(500);

Serial.print(".");
lcd.setCursor(0,0);            
  lcd.print("   IoT based  ");
  lcd.setCursor(0,1);            
  lcd.print("Forest Protection");
  delay(3000);
  lcd.clear();
}

 

Serial.println("");

Serial.println("WiFi is connected");

server.begin();

Serial.println("Server started");

 

 

Serial.println(WiFi.localIP());

lcd.clear();
lcd.print("Server started");
lcd.setCursor(0,1);
lcd.print(WiFi.localIP());
delay(3000);
lcd.clear();

  /*if (pressure.begin())

    Serial.println("BMP180 init success");

  else

  {

    Serial.println("BMP180 init fail\n\n");

    while(1); // Pause forever.

  }*/

  delay(1000);

}

 

void loop() {


float h = dht.readHumidity();

// Read temperature as Celsius (the default)

float t = dht.readTemperature();

// Read temperature as Fahrenheit (isFahrenheit = true)

float f = dht.readTemperature(true);

 int sound=analogRead(34); 

lcd.setCursor(0,0);            
  lcd.print("Temp:");
  lcd.print(t);
  lcd.print(char(223));
  lcd.print("C");
 

  lcd.setCursor(8,0);
  lcd.print("Hum:");
  lcd.print(h);
  lcd.print("%");
  //Serial.print("Humidity:");
 
  delay(1500); 

  lcd.setCursor(0,1);            
  lcd.print("Sound:");
  lcd.print(sound);
    lcd.print(" ");
WiFiClient client = server.available();

client.println("HTTP/1.1 200 OK");

client.println("Content-Type: text/html");

client.println("Connection: close");  // the connection will be closed after completion of the response

client.println("Refresh: 10");  // update the page after 10 sec

client.println();

client.println("<!DOCTYPE HTML>");

client.println("<html>");

client.println("<style>html { font-family: Cairo; display: block; margin: 0px auto; text-align: center;color: #FFFFFF; background-color: #0066FF;}");

client.println("body{margin-top: 50px;}");

client.println("h1 {margin: 50px auto 30px; font-size: 50px; text-align: center;}");

client.println(".side_adjust{display: inline-block;vertical-align: middle;position: relative;}");

client.println(".text1{font-weight: 180; padding-left: 15px; font-size: 50px; width: 170px; text-align: left; color: #FFFFFF;}");

client.println(".data1{font-weight: 180; padding-left: 80px; font-size: 50px;color: #FFFFFF;}");

client.println(".text2{font-weight: 180; font-size: 50px; width: 170px; text-align: left; color: #FFFFFF;}");

client.println(".data2{font-weight: 180; padding-left: 150px; font-size: 50px;color: #FFFFFF;}");

client.println(".text3{font-weight: 180; font-size: 50px; width: 170px; text-align: left; color: #FFFFFF;}");

client.println(".data3{font-weight: 180; padding-left: 150px; font-size: 50px;color: #FFFFFF;}");

client.println(".text4{font-weight: 180; font-size: 50px; width: 170px; text-align: left; color: #FFFFFF;}");

client.println(".data4{font-weight: 180; padding-left: 150px; font-size: 50px;color: #FFFFFF;}");

client.println(".text5{font-weight: 180; font-size: 50px; width: 170px; text-align: left; color: #FFFFFF;}");

client.println(".data5{font-weight: 180; padding-left: 150px; font-size: 50px;color: #FFFFFF;}");

client.println(".text6{font-weight: 180; font-size: 50px; width: 170px; text-align: left; color: #FFFFFF;}");

client.println(".data6{font-weight: 180; padding-left: 150px; font-size: 50px;color: #FFFFFF;}");

client.println(".text7{font-weight: 180; font-size: 50px; width: 170px; text-align: left; color: #FFFFFF;}");

client.println(".data7{font-weight: 180; padding-left: 150px; font-size: 50px;color: #FFFFFF;}");

client.println(".data{padding: 10px;}");

client.println("</style>");

client.println("</head>");

client.println("<body>");

client.println("<div id=\"webpage\">");   

client.println("<h1>IoT based Forest Protection System</h1>");

client.println("<div class=\"data\">");

client.println("<div class=\"side_adjust text1\">Sound:</div>");

client.println("<div class=\"side_adjust data1\">");

client.print(sound);

client.println("</div>");  

client.println("<div class=\"data\">");

client.println("<div class=\"side_adjust text2\">Humidity:</div>");

client.println("<div class=\"side_adjust data2\">");

client.print(h);

client.println("<div class=\"side_adjust text2\">%</div>");

client.println("</div>");

client.println("<div class=\"data\">");

client.println("<div class=\"side_adjust text3\">Temperature:</div>");

client.println("<div class=\"side_adjust data3\">");

client.print(t);

client.println("<div class=\"side_adjust text3\">*C</div>");

client.print(f);

client.println("<div class=\"side_adjust text3\">F</div>");

client.println("</div>");

client.println("<div class=\"data\">");

//client.println("<div class=\"side_adjust text4\">Pressure:</div>");

//client.println("<div class=\"side_adjust data4\">");

//client.print(p0,2);

//client.println("<div class=\"side_adjust text4\">mb</div>");

//client.println("</div>");

//client.println("<div class=\"data\">");


if(digitalRead(18)==LOW)
{
lcd.setCursor(0,1);            
  lcd.print("Fire detected... ");
client.println("<div class=\"side_adjust text5\">Fire_detected</div>");

client.println("</div>");
digitalWrite(23, HIGH);
Serial.println("AT+CMGF=1");    //To send SMS in Text Mode
          delay(1000);
          Serial.println("AT+CMGS=\"+918121413341\"\r"); // change to the phone number you using  17.254760, 78.307664


          delay(1000);
          Serial.print("Fire detected at https://www.google.co.in/search?client=opera&q=17.254760%2C78.307664123");//the content of the message
          delay(200);
          Serial.println((char)26);//the stopping character
          delay(1000);
          Serial.println((char)26);//the message stopping character
          delay(1000);
digitalWrite(23, LOW);
lcd.setCursor(0,1);            
  lcd.print("                   ");

}
if(sound<390 && digitalRead(15)==LOW)
{
  lcd.setCursor(0,1);            
  lcd.print("Cutting alert!...     ");
client.println("<div class=\"side_adjust text6\">Cutting_alert</div>");

client.println("</div>");
digitalWrite(23, HIGH);
Serial.println("AT+CMGF=1");    //To send SMS in Text Mode
          delay(1000);
          Serial.println("AT+CMGS=\"+918121413341\"\r"); // change to the phone number you using  17.254760, 78.307664


          delay(1000);
          Serial.print("Cutting sound detected at https://www.google.co.in/search?client=opera&q=17.254760%2C78.307664123");//the content of the message
          delay(200);
          Serial.println((char)26);//the stopping character
          delay(1000);
          Serial.println((char)26);//the message stopping character
          delay(1000);
digitalWrite(23, LOW);
lcd.setCursor(0,1);            
  lcd.print("                   ");
}
if(sound>390)
{
  
client.println("<div class=\"side_adjust text6\">No_cutting</div>");

client.println("</div>");
}
if(digitalRead(18)!=LOW)
{
client.println("<div class=\"side_adjust text5\">No_Fire</div>");

client.println("</div>");

}

if(digitalRead(19)==HIGH)
{
lcd.setCursor(0,1);            
  lcd.print("Somebody passing... ");
client.println("<div class=\"side_adjust text7\">Somebody_passing</div>");

client.println("</div>");
digitalWrite(23, HIGH);
Serial.println("AT+CMGF=1");    //To send SMS in Text Mode
          delay(1000);
          Serial.println("AT+CMGS=\"+918121413341\"\r"); // change to the phone number you using  17.254760, 78.307664


          delay(1000);
          Serial.print("Somebody passing at https://www.google.co.in/search?client=opera&q=17.254760%2C78.307664123");//the content of the message
          delay(200);
          Serial.println((char)26);//the stopping character
          delay(1000);
          Serial.println((char)26);//the message stopping character
          delay(1000);digitalWrite(23, LOW);
lcd.setCursor(0,1);            
  lcd.print("                   ");
}
if(digitalRead(19)!=HIGH)
{
client.println("<div class=\"side_adjust text7\">No_person</div>");

client.println("</div>");

}

client.println("<div class=\"data\">");

client.println("</body>");

client.println("</html>");

 delay(4000);

}