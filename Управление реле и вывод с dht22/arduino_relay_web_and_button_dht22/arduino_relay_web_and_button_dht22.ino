#include <SPI.h>
#include <Ethernet.h>
#include <Bounce.h>
#include <DHT.h>

#define BUTTON 2                                       // создаем объект класса Bounce. Указываем пин, к которому подключена кнопка.
Bounce bouncer = Bounce(BUTTON,10);                     // время дребезга контактов в мс
#define DHTPIN 3
#define DHTTYPE DHT22


int relay = 4;                                         // пин подключения реле
int relayValue = LOW;                                  // состояние реле при включении (выключено)
byte mac[] = { 0xDE, 0xAD, 0xDE, 0xEF, 0xF2, 0xED };   // MAC адрес
byte ip[] = { 192, 168, 88, 170 };                     // IP адрес
byte gateway[] = { 192, 168, 88, 1 };                  // шлюз
byte subnet[] = { 255, 255, 255, 0 };                  // маска сети
EthernetServer server(80);                             // порт веб сервера     
String readString;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
   while (!Serial) {
    ;
  }
  pinMode(relay, OUTPUT);
  pinMode(BUTTON,INPUT);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {

// Упраление кнопками
  if ( bouncer.update() ) {
    if ( bouncer.read() == HIGH) {
     if ( relayValue == LOW ) {
       relayValue = HIGH;
     } else {
       relayValue = LOW;
     }
     digitalWrite(relay,relayValue);
    }
  }

// Ethernet сервер
  EthernetClient client = server.available();
          if (client) {
            boolean currentLineIsBlank = true;
          while (client.connected()) {   
          if (client.available()) {
          char c = client.read();
     
          if (readString.length() < 100) {
            readString += c;
           }

// Вывод на com порт отладочной информации
           if (c == '\n') {          
           Serial.println(readString); 
           if (c == '\n' && currentLineIsBlank) 

// Генерация веб страницы     
           client.println("HTTP/1.1 200 OK");
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");

          // get data from DHT22 sensor
          float h = dht.readHumidity();
          float t = dht.readTemperature();
          Serial.println(t);
          Serial.println(h);
           
           client.println("<HEAD>");
           client.println("<meta charset='UTF-8' />");
           client.println("<TITLE>Панель управления</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>Панель управления</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Arduino with Ethernet Shield</H2>");
           client.println("<br />");  
           client.println("<a href=\"/?button1on\"\">Включить</a>");
           client.println("<a href=\"/?button1off\"\">Выключить</a><br />");   
           client.println("<br />");
           client.println("<p>Temperature - ");
           client.print(t);
           client.print(" degrees Celsius</p>");
           client.print("<p>Humidity - ");
           client.print(h);
           client.print(" percent</p>");     
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           client.stop();

// Обработка http запросов
           if (readString.indexOf("?button1on") >0){
               digitalWrite(relay, HIGH);
           }
           if (readString.indexOf("?button1off") >0){
               digitalWrite(relay, LOW);
           }
           
            readString="";  
          if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        } 
         }
                      
       }
    }
}
}

