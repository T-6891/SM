//подключаем библиотеку Bounce
#include <Bounce.h>
//дефайним значения пинов с кнопкой и со светодиодом
#define BUTTON 2
#define LED 13
//создаем объект класса Bounce. Указываем пин, к которому подключена кнопка, и время дребезга в мс.
Bounce bouncer = Bounce(BUTTON,5); 

//задаем начальное состояние светодиода "выключен"
int ledValue = LOW;



void setup() {
  //определяем режимы работы пинов
  pinMode(BUTTON,INPUT);
  pinMode(LED,OUTPUT);
}



void loop() {
  //если сменилось состояние кнопки
  if ( bouncer.update() ) {
    //если считано значение 1
    if ( bouncer.read() == HIGH) {
     //если свет был выключен, будем его включать
     if ( ledValue == LOW ) {
       ledValue = HIGH;
     //если свет был включен, будем выключать
     } else {
       ledValue = LOW;
     }
     //записываем значение вкл/выкл на пин со светодиодом 
     digitalWrite(LED,ledValue);
    }
  }
}

