#include <LiquidCrystal.h>
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define  UP   'U'
#define RIGHT 'R'  
#define DOWN  'D'
#define LEFT  'L'

#define ENTER "Enter"
#define PASSWORD "Password"
#define CONFIG	"Config"
#define MODE 	"Mode"

int adc_key_in  = 0;
LiquidCrystal lcd(4,5,6,7,8,9);

int read_LCD_buttons()  
{ 
 adc_key_in = analogRead(A0);
 if (adc_key_in > 900) return btnNONE;
 if (adc_key_in < 50)   return btnRIGHT; 
 if (adc_key_in < 250)  return btnUP;
 if (adc_key_in < 450)  return btnDOWN;
 if (adc_key_in < 650)  return btnLEFT;
 if (adc_key_in < 850)  return btnSELECT; 
 return btnNONE;
} 

/************ variables ************/

 int posCol  = 10;
 int posFila = 1;
 int cRegresiva = 10;


char puntero = '^';



int password_Digits = 0;
char default_FirstDigit = 'L';
char default_SecondDigit = 'L';
char default_ThirdDigit = 'R';
char default_FourthDigit = 'R';


char first_Digit;
char second_Digit;
char third_Digit;
char fourth_Digit;

bool clearScreen = false;
bool menuStatus  = true;
bool configStatus = false;

/*************************************/



/**
 * @brief dibuja un puntero en la columna y fila dada por parametro
 * @param col: columna entre 0 y 15
 * @param fila: fila   entre 0 o 1
 * @return void.
 * 
 */
void printPuntero(int col, int fila)
{
   lcd.setCursor(col, fila);
   lcd.print(puntero);
}


/**
 * @brief borra el puntero en la columna y fila dada por parametro
 * @param col: columna entre 0 y 15
 * @param fila: fila   entre 0 o 1
 * @return void.
 * 
 */
void borrarPuntero(int col, int fila)
{
   lcd.setCursor(col, fila);
   lcd.print(" ");
}


/**
 * @brief Mueve el puntero borrando el anterior, incrementando en 1
 *        la posicion de la columna y dibujando en la nueva columna
 * @return void.
 * 
 */
void moveRight()
{
  if(posCol < 9)
  {	
    borrarPuntero(posCol, posFila);
    posCol++;
    printPuntero(posCol, posFila);
  }
}


/**
 * @brief Mueve el puntero borrando el anterior, decrementando en 1
 *        la posicion de la columna y dibujando en la nueva columna
 *        siempre que sea mayor a 6 la posicion de la columna.
 * @return void.
 * 
 */
void moveLeft()
 {
  if(posCol > 6)
  {	
    borrarPuntero(posCol, posFila);
    posCol--;
    printPuntero(posCol, posFila);
  }
}


/**
 * @brief Dibuja un caracter 
 * @param key: caracter a dibujar
 * @return void.
 * 
 */
void printDigit(char key)
{
 	lcd.setCursor(posCol, 0);
  	lcd.print(key);
}



/**
 * @brief Asigna a cada variable un caracter, siendo este el orden de una password
 * @param key: caracter a almacenar
 * @param passDigit: hace referencia a la posicion del puntero 
 *                   en orden para almacenar la password
 * @return void.
 */
void assign_digitPassword(int passDigit, char key)
{
	
	switch(passDigit)
    {
      	case 0:  first_Digit  = key; 	break;
      	case 1:  second_Digit = key; 	break;
      	case 2:  third_Digit  = key;	break;
      	case 3:  fourth_Digit = key;	break;
    }
}






/**
 * @brief Escribe la password 
 * @param key: caracter a escribir
 * 
 * @return void.
 */
void write_Password_Digit(char key)
{
  	if(password_Digits < 4)
    {      
       	printDigit(key);
      	assign_digitPassword(password_Digits, key);  
      	
      	borrarPuntero(posCol, posFila);
      	posCol++;
      	printPuntero(posCol, posFila); 
      
	    	password_Digits++;
    }
}



/**
 * @brief Resetea la password
 * @return void.
 * 
 */
void resetPassword()
{
  first_Digit  = '0';
  second_Digit = '0';
  third_Digit  = '0';
  fourth_Digit = '0';
}




/**
 * @brief Checkea que la password introducida coincida con la seteada
 *        si Coincide limpia la pantalla y prende el LED
 * @return returnAux: 1 si hubo error
 *                    0 si todo ok.
 * 
 */
int checkPassword()
{
  int returnAux = 1;
  
  	if( default_FirstDigit == first_Digit &&
        default_SecondDigit == second_Digit &&
        default_ThirdDigit == third_Digit &&
       	default_FourthDigit == fourth_Digit &&
       	password_Digits == 4)
    {
      menuStatus = false;
      clearScreen = true;
      cleanScreen();
      digitalWrite(10, HIGH);
      returnAux = 0;
    }
   return returnAux;   
}




/**
 * @brief Setea una nueva contraseña dentro del config Menu
 * @param passDigit: digito que representa la posicion del puntero
 * @param key: caracter a almacenar en la posicion (1-4) del password
 * @return void
 */
void setNewPassword(int passDigit, char key)
{
  if(configStatus == true)
  {
    switch(passDigit)
    {
      	case 0:  default_FirstDigit  = key; 	break;
      	case 1:  default_SecondDigit = key; 	break;
      	case 2:  default_ThirdDigit  = key; 	break;
      	case 3:  default_FourthDigit = key; 	break;
    }
  }
}





/**
 * @brief lee la nueva password introducida y vuelve al menu principal
 * @param key: caracter leido
 * @return void
 *
 */
void take_New_Password(char key)
{
	
      if(password_Digits < 4)
  	  {
      
      	printDigit(key);
      	setNewPassword(password_Digits, key);  
      	
      	borrarPuntero(posCol, posFila);
      	posCol++;
      	printPuntero(posCol, posFila); 
      
	    	password_Digits++;
   	  }
      if(password_Digits == 4)
      {
        password_Digits -= 4;
        configStatus = false;
        menuStatus = true;
        clearScreen = true;
        cleanScreen();
      }
      
}





/**
 * @brief Limpia la pantalla solo si clearScreen es true, entra limpia y la setea en false
 *        para que no limpie indefinidamente dentro del LOOP
 *        
 * @return void
 */
void cleanScreen()
{
  if(clearScreen == true)
  {
    lcd.clear();
    clearScreen = false;
  }
  
}




/**
 * @brief Imprime un numero (usado para cuenta Regresiva)
 * @param num: numero a mostrar por pantalla
 * @param columna: numero de la columna a mostrar numero
 *         
 * @return void
 */
void printNum(int num, int columna)
{
  lcd.setCursor(columna, 0);
  lcd.print(num);
}






/**
 * @brief Contador decreciente de 10 segundos 9-0, cuando llega a 0 el led se apaga
 *        
 * @return void
 */
void cuentaRegresiva()
{	
  	borrarPuntero(posCol, posFila);
  	

  	if(cRegresiva == 0)
    {
        digitalWrite(10, LOW);
        clearScreen = true;
        resetPassword();
        menuStatus = true;
      
    }
  	else
    {
        cRegresiva -= 1;
        printNum(cRegresiva, 8);
  	    delay(1000);	
    }
 	
}
  




/**
 * @brief Menu principal de la aplicacion
 *        
 * @return void
 */
void Menu()
{
	if(menuStatus == true)
    {
    	lcd.setCursor(0,0);
  		lcd.print(ENTER);
  		lcd.setCursor(0,1);
    	lcd.print(PASSWORD);
  	
  	 	if(posCol == 14)
   		{	
          	 borrarPuntero(posCol, posFila);
      		   posCol -= 4;
   	 	}
  	
  		printPuntero(posCol, posFila);
      	if(password_Digits == 4)
        {
          password_Digits -= 4;
        }
    }
}






/**
 * @brief Menu de configuracion de la aplicacion, permite setear una nueva password
 *        
 * @return void
 */
void configMenu()
{
   menuStatus   = false;
   configStatus = true;
   
   cleanScreen();
   if(configStatus == true)
   {
  	  lcd.setCursor(0,0);
	    lcd.print(CONFIG);
  	  lcd.setCursor(0,1);
  	  lcd.print(MODE);      
   }  
}









void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  
  Menu(); 
}



void loop()
{
   lcd.setCursor(0,0);
   cleanScreen();
  
  switch(read_LCD_buttons()){
    
      case btnRIGHT:
      if(menuStatus == true){ write_Password_Digit(RIGHT); }
      if(configStatus == true) { take_New_Password(RIGHT); }
      break;
    
      case btnLEFT:
      if(menuStatus == true){ write_Password_Digit(LEFT); }
      if(configStatus == true) { take_New_Password(LEFT); }
      break;
    
      case btnUP:
     	if(menuStatus == true){ write_Password_Digit(UP); }
      if(configStatus == true) { take_New_Password(UP); }
      break;
    
      case btnDOWN:
      if(menuStatus == true){ write_Password_Digit(DOWN); }
      if(configStatus == true) { take_New_Password(DOWN); }
      break;
    
      case btnSELECT:
      clearScreen = true;
      configMenu();
      break;
    
      case btnNONE:
      printPuntero(posCol, posFila);
      if(menuStatus == true){ Menu(); }
      if(configStatus == true) { configMenu(); }
      break;
    
  }
  
  
  
  
  
  if(checkPassword() == 0)
  {
    cuentaRegresiva();
  }else if(cRegresiva == 0){
    cRegresiva += 10;
  }
  delay(100);
}