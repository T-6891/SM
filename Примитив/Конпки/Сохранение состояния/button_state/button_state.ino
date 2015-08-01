int flag=0; 

void setup()    
{ 
       
    pinMode(13, OUTPUT);         
      
        
} 

void loop() 

{ 
        
     if(digitalRead(14)==HIGH&&flag==0)//если кнопка нажата    
     // и перемення flag равна 0 , то ... 
     { 
           
       digitalWrite(13,!digitalRead(13)); 
       flag=1; 
        //это нужно для того что бы с каждым нажатием кнопки 
        //происходило только одно действие 
        // плюс защита от "дребезга"  100% 
        
     } 
        
      if(digitalRead(14)==LOW&&flag==1)//если кнопка НЕ нажата 
     //и переменная flag равна - 1 ,то ... 
     { 
           
        flag=0;//обнуляем переменную flag 
     } 
} 


