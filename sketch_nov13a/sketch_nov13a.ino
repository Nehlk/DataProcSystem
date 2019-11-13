#include <LiquidCrystal.h>
#define BTN_UP 0
#define BTN_DOWN 1
#define BTN_LEFT 2
#define BTN_RIGHT 3
#define BTN_SELECT 4
#define BTN_NADA 5

int readButton (){
  int value=analogRead(A0);
  
  if(value<70)
    return BTN_RIGHT;
    
   if(value>69 && value<235)
    return BTN_UP;
    
   if(value>235 && value<411)
    return BTN_DOWN;
    
   if(value>411 && value<646)
    return BTN_LEFT;
    
   if(value>646 && value<930)
    return BTN_SELECT;
  
  return BTN_NADA;
}  

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);





 int minuto_B = 0;
 int minuto_A = 0;
 int segundo_B = 0;
 int segundo_A = 0;
 char puntero = '^';

int posicionCursor = 0;
int previousValue = BTN_NADA;
int value = 0;


void moverCositoDerecha(int col, char cosin)
{
   if(col - 1 == 0 || col -1 == 3)
   {
    lcd.setCursor(col-1, 1);
    lcd.print(" ");
   }else if(col-2 == 1)
   {
    lcd.setCursor(col-2, 1);
    lcd.print(" ");
   }
   
   lcd.setCursor(col, 1); 
   lcd.print(puntero);
   delay(100);
}

void moverCositoIzquierda(int col, char cosin)
{
   if(col + 1 == 4 || col + 1 == 1)
   {
    lcd.setCursor(col+1, 1);
    lcd.print(" ");
   }else if(col+2 == 3)
   {
    lcd.setCursor(col+2, 1);
    lcd.print(" ");
   }
   
   lcd.setCursor(col, 1); 
   lcd.print(puntero);
   delay(100);
}


void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);

  lcd.print(minuto_B);
  lcd.print(minuto_A);
  lcd.print(":");
  lcd.print(segundo_B);
  lcd.print(segundo_A);

   lcd.setCursor(0, 1); 
   lcd.print(puntero);
}




double mills = millis();


void loop()
{
 int button = readButton();
 
 Serial.println(mills+= 0.1);


    if(previousValue == BTN_NADA && value != BTN_NADA)
    {
        switch(button)
         {
             case BTN_RIGHT:
               if(posicionCursor == 0 || posicionCursor ==3)
               {
            
                 posicionCursor++;
                 moverCositoDerecha(posicionCursor, puntero);
                }else if(posicionCursor == 1)
                  {
                    posicionCursor += 2;
                    moverCositoDerecha(posicionCursor, puntero);
                  }
          
                  break;

            case BTN_LEFT:
                  if(posicionCursor == 4 || posicionCursor ==1)
                  {
                    posicionCursor--;
                    moverCositoIzquierda(posicionCursor, puntero);
            
                  }
                  else if(posicionCursor == 3)
                  {
                    posicionCursor -= 2;
                    moverCositoIzquierda(posicionCursor, puntero);
                  }
                break;


            case BTN_UP:
                  if(posicionCursor == 0 && minuto_B < 5)
                  {
                    minuto_B ++;
                    lcd.setCursor(posicionCursor, 0); 
                    lcd.print(minuto_B);
                    delay(100);
                        
                  }
                  else if(posicionCursor == 1 && minuto_A < 9)
                  {
                      minuto_A++;
                      lcd.setCursor(posicionCursor, 0); 
                      lcd.print(minuto_A);
                      delay(100);
                        
                  }
                  else if(posicionCursor == 3 && segundo_B < 5)
                   {
                      segundo_B++;
                      lcd.setCursor(posicionCursor, 0); 
                      lcd.print(segundo_B);
                      delay(100);
                        
                    }
                    else if(posicionCursor == 4 && segundo_A < 9)
                    {
                      segundo_A++ ;
                      lcd.setCursor(posicionCursor, 0); 
                      lcd.print(segundo_A);
                      delay(100);
                        
                    }
                    break;

            case BTN_DOWN:
                    if(posicionCursor == 0 && minuto_B > 0)
                    {
                      minuto_B --;
                      lcd.setCursor(posicionCursor, 0); 
                      lcd.print(minuto_B);
                      delay(100);
                        
                    }
                   else if(posicionCursor == 1 && minuto_A> 0)
                    {
                      minuto_A--;
                      lcd.setCursor(posicionCursor, 0); 
                      lcd.print(minuto_A);
                      delay(100);
                        
                    }
                    else if(posicionCursor == 3 && segundo_B > 0)
                    {
                      segundo_B--;
                      lcd.setCursor(posicionCursor, 0); 
                      lcd.print(segundo_B);
                      delay(100);
                        
                    }
                    else if(posicionCursor == 4 && segundo_A > 0)
                    {
                      segundo_A-- ;
                      lcd.setCursor(posicionCursor, 0); 
                      lcd.print(segundo_A);
                      delay(100);
                    }            
            
                    break;  


             case BTN_SELECT:     
                    cuentaRegresiva();
                   break;      
  }



      delay(100);
  
    }
    
}


void cuentaRegresivaSegA()
{
    
    float segA = segundo_A;

   while(segA >= 0)
   {
      if(segA > 0)
      {
        
        segA -= 0.001;
        segundo_A = segA;
        lcd.setCursor(4, 0); 
                    lcd.print(segundo_A);
          
      }
   }
  
}


void cuentaRegresivaSegB()
{
     float segB = segundo_B;

    while(segB >= 0)
   {
      if(segB > 0)
      {
        
        segB -= 0.001;
        segundo_B = segB;
        lcd.setCursor(3, 0); 
                    lcd.print(segundo_B);
          
      }
   }
}


void cuentaRegresiva()
{
 while(segundo_A >= 0){  

    if(segundo_A == 0)
    {
      segundo_B-- ;
      lcd.setCursor(3, 0); 
      lcd.print(segundo_B);

      segundo_A = 9;
      lcd.setCursor(4, 0); 
      lcd.print(segundo_A);
    }

     cuentaRegresivaSegA();
 }
    
}

