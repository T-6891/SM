#include <SPI.h>
#include <Ethernet.h>
#include <Bounce.h>

#define BUTTON 2
//создаем объект класса Bounce. Указываем пин, к которому подключена кнопка, и время дребезга в мс.
Bounce bouncer = Bounce(BUTTON,5); 

int led = 4;
int ledValue = LOW;
byte mac[] = { 0xDE, 0xAD, 0xDE, 0xEF, 0xF2, 0xED };   //physical mac address
byte ip[] = { 192, 168, 88, 170 };                      // ip in lan (that's what you need to use in your browser. ("192.168.1.178")
byte gateway[] = { 192, 168, 88, 1 };                   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
String readString;

void setup() {
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(led, OUTPUT);
  pinMode(BUTTON,INPUT);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {

  if ( bouncer.update() ) {
    if ( bouncer.read() == HIGH) {
     if ( ledValue == LOW ) {
       ledValue = HIGH;
     } else {
       ledValue = LOW;
     }
     digitalWrite(led,ledValue);
    }
  }
  // Create a client connection
  EthernetClient client = server.available();
          if (client) {
          while (client.connected()) {   
          if (client.available()) {
          char c = client.read();
     
          //read char by char HTTP request
          if (readString.length() < 100) {
            //store characters to string
            readString += c;
            //Serial.print(c);
           }

           //if HTTP request has ended
           if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
     
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta charset='UTF-8' />");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>Web panel</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>Web panel</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Arduino with Ethernet Shield</H2>");
           client.println("<br />");  
           client.println("<a href=\"/?button1on\"\">Включить</a>");
           client.println("<a href=\"/?button1off\"\">Выключить</a><br />");   
           client.println("<br />");     
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           client.stop();
           if (readString.indexOf("?button1on") >0){
               digitalWrite(led, HIGH);
           }
           if (readString.indexOf("?button1off") >0){
               digitalWrite(led, LOW);
           }
           
            readString="";  
           
         }
                      
       }
    }
}
}

