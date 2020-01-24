/*
		EDUCATIONAL INSTITUTION: INSTITUTO FEDERAL DE EDUCAÇÃO, CIÊNCIA E TECNOLOGIA DE SÃO PAULO (IFSP)
		
		       GROUP MEMBERS: MURILO DE PAULA ARAUJO   PROMPTUARY: 1540211
							  OLDAIR FRANSISCO                     1540025
							  SAMUEL ENVANGELISTA                  1541633
							  TIAGO SANTOS                         1541226
							  ZACARIAS SANTANA                     1541439                      
		
		TEACHER MSc. ADVISOR: LUIZ EDUARDO MIRANDA  J. RODRIGUES  
 
				END OF COURSE WORK: PROJECT OF AUTOMATIC COCKTAIL SHAKER
*/

#include <Servo.h>                             // Including the Servo Motor function library 
#include <Stepper.h>                           // Including the Stepper Motor function library

// Declaring servo type variables, using 6 servo motors in the project
Servo Servo_1;                                  
Servo Servo_2;                                 
Servo Servo_3;                                 
Servo Servo_4;                                 
Servo Servo_5;                                 
Servo Servo_6;                                 


const int Engine_Laps = 200;                  // Number of steps per lap
Stepper myStepper(Engine_Laps, 8, 9, 10, 11); // Starts the myStepper variable using ports 8, 9, 10 and 11

// Declaration of the buttons used in the project, and respectively, the "entrance doors" of Arduino                                 
const int Button_5 = 2;                                       
const int Button_6 = 3;                                       
const int Button_1 = 4;                                       
const int Button_2 = 5;                                       
const int Button_3 = 6;  
const int Button_Start = 13;                                     
const int Button_4 = 30;  

// Declaration of the levers used in the project, and respectively, the "entrance doors" of Arduino
const int Hand_Lever = 7;
const int Automatic_Lever = 12; 

// Declaration of the Led's used in the project, and respectively, the "exit doors" of Arduino
const int Led_1 = 19;                                           
const int Led_2 = 20;                                           
const int Led_3 = 21;                                           
const int Led_4 = 16;                                           
const int Led_5 = 17;                                           
const int Led_6 = 18;                                           

// Declaration of the variables that store the states of the buttons, levers and selection
int Button_State_4 = LOW;                                         
int Button_State_5 = LOW;                                         
int Button_State_6 = LOW;                                         
int Button_State_1 = LOW;                                         
int Button_State_2 = LOW;                                         
int Button_State_3 = LOW;                                         
int Button_State_Start = LOW;                                     

int Hand_Lever_State = LOW;  
int Automatic_Lever_State = LOW;    

int Selection = 0;
int Selection_1 = 0;
int Selection_2 = 0;

// Function responsible for turning off the button's Led's, the stepper motor and the 6 servo motors
void Shutting_Down_Components ();

void setup() {
	
	Serial.begin(9600);                                         
	myStepper.setSpeed(3); // Motor speed set to 300

	// Indicating which pin will receive the signal from the respective Servo Motor
	Servo_1.attach(23);                                             
	Servo_2.attach(24);                                             
	Servo_3.attach(25);                                             
	Servo_4.attach(26);	
	Servo_5.attach(27);  
	Servo_6.attach(28);  

	// Indicating the Arduino ports of the buttons as input
	pinMode(Button_1, INPUT); 
	pinMode(Button_2, INPUT); 
	pinMode(Button_3, INPUT);   
	pinMode(Button_4, INPUT);   
	pinMode(Button_5, INPUT);   
	pinMode(Button_6, INPUT);   

	// Indicating the lever Arduino ports as input
	pinMode(Hand_Lever, INPUT);
	pinMode(Automatic_Lever, INPUT);  

	// Indicating the Arduino ports of the led's as input
	pinMode(Led_1, OUTPUT);                                         
	pinMode(Led_4, OUTPUT);                                         
	pinMode(Led_6, OUTPUT);                                         
	pinMode(Led_5, OUTPUT);                                         
	pinMode(Led_2, OUTPUT);                                         
	pinMode(Led_3, OUTPUT);  
}

void loop() 
{    
	// Defining the starting position of each Servo Motor
	Servo_1.write(0); 
	Servo_2.write(0); 
	Servo_3.write(0); 
	Servo_4.write(0); 
	Servo_5.write(0); 
	Servo_6.write(0); 

	// Function responsible for turning off the button's Led's, the stepper motor and the 6 servo motors
	Shutting_Down_Components();

	// Check the status of each button and store in its respective variable to assist that state
	Button_State_1 = digitalRead (Button_1);                      
	Button_State_2 = digitalRead (Button_2);                             
	Button_State_3 = digitalRead (Button_3);                             
	Button_State_4 = digitalRead (Button_4);                            
	Button_State_5 = digitalRead (Button_5);                            
	Button_State_6 = digitalRead (Button_6);                             
	Button_State_Start = digitalRead (Button_Start);

	// Check the status of each lever and store in its respective variable to assist that state
	Hand_Lever_State = digitalRead (Hand_Lever);             
	Automatic_Lever_State = digitalRead (Automatic_Lever);                 

	// If the Lever State that enables the machine in the manual function is selected
	if (Hand_Lever_State == HIGH) {
		
		if (Button_State_1 == HIGH)
			Selection = 1; 

		if (Selection == 1)
			digitalWrite (Led_1, HIGH); // Turn on a Led, indicating that the manual option has been selected
		
		// I check if besides the manual option it is chosen, if the Start button is also
		if (Selection == 1 && Button_State_Start == HIGH) { 
			
			Shutting_Down_Components();
			
			// Indicate the position that the stepper motor should be positioned in
			myStepper.step(-17); 
	  
			delay (2000);      // 2 second delay
			Servo_1.write(0);   // Indicate the position of the servo motor 1

			delay(2000);       // 2 second delay
			Servo_1.write(120); // Ideal position to raise the glass to a height that activates the "Drink Dispenser"

			delay(7000);       // 7 second delay, an ideal time to drop a drink into the glass
			Servo_1.write(0);   // The servo motor returns to the starting position

			delay(2000);       // 2 second delay

			myStepper.step (17); // Return of the stepper motor in the initial position

			Selection = 0; // Indicates that I already do what the customer wanted, to do it again only if the customer presses the Start button again

			Shutting_Down_Components();
		}

		if (Button_State_2 == HIGH)
		Selection = 2;

		if (Selection == 2)
		digitalWrite (Led_2, HIGH);

		if (Selection == 2 && Button_State_Start == HIGH) {
			
			Shutting_Down_Components();
		   
			myStepper.step(-49); 
		  
			delay (2000);
			Servo_2.write(0);

			delay(2000);
			Servo_2.write(180);

			delay(7000);
			Servo_2.write(0);
			
			delay(2000);
			
			myStepper.step (49);
			
			Selection = 0;
			
			Shutting_Down_Components();
		}
		
		if (Button_State_3 == HIGH)
			Selection = 3;

		if (Selection == 3)
		digitalWrite (Led_3, HIGH);
	
		if (Selection == 3 && Button_State_Start == HIGH) {
			
			Shutting_Down_Components();
			     
			myStepper.step(-83); 
	  
			delay (2000);
			Servo_3.write(0);
	  
			delay(2000);
			Servo_3.write(90);
	  
			delay(7000);
			Servo_3.write(0);
	  
			delay(2000);
			digitalWrite(23, LOW);

			myStepper.step (83);
	  
			Selection = 0;
			
			Shutting_Down_Components();
		}

		if (Button_State_4 == HIGH)
		Selection = 4;

		if (Selection == 4)
		digitalWrite (Led_4, HIGH);
	
		if (Selection == 4 && Button_State_Start == HIGH) {
	  
			Shutting_Down_Components();
			     
			myStepper.step(83); 
			  
			delay (2000);
			Servo_4.write(0);
			
			delay(2000);
			Servo_4.write(90);
			
			delay(7000);
			Servo_4.write(0);
			
			delay(2000);

			myStepper.step (-83);
			
			Selection = 0;
			
			Shutting_Down_Components();
		}
	
		if (Button_State_5 == HIGH)
		Selection = 5;

		if (Selection == 5)
		digitalWrite (Led_5, HIGH);
	
		if (Selection == 5 && Button_State_Start == HIGH) {
			
			Shutting_Down_Components();

			myStepper.step(50); 
	  
			delay (2000);
			Servo_5.write(0);
	  
			delay(2000);
			Servo_5.write(120);
			
			delay(7000);
			Servo_5.write(0);
			
			delay(2000);
			
			myStepper.step (-50);
			
			Selection = 0;
			
			Shutting_Down_Components();
		}
		
		if (Button_State_6 == HIGH)
		Selection = 6;

		if (Selection == 6)
		digitalWrite (Led_6, HIGH);
	
		if (Selection == 6 && Button_State_Start == HIGH) {
		
		Shutting_Down_Components();

		myStepper.step(17); 
	  
		delay (2000);
		Servo_6.write(0);
	  
		delay(2000);
		Servo_6.write(120);
	  
		delay(7000);
		Servo_6.write(0);
	  
		delay(2000);

		myStepper.step (-17);
		
		Selection = 0;
		
		Shutting_Down_Components();
		}
	}
	
	if (Automatic_Lever_State == HIGH) {
	
		if (Button_State_1 == HIGH)
		Selection = 1;
	
		if (Selection == 1)
		digitalWrite (Led_1, HIGH);
	
		if (Button_State_3 == HIGH)
		Selection_1 = 1;
	
		if (Selection_1 == 1)
		digitalWrite (Led_3, HIGH);
	
		if (Button_State_5 == HIGH)
		Selection_2 = 1;
	
		if (Selection_2 == 1)
		digitalWrite (Led_5, HIGH);
	
		if (Selection == 1 && Selection_1 == 1 && Selection_2 == 1 && Button_State_Start == HIGH)	{

			Shutting_Down_Components();

			myStepper.step(-17); 
		  
			delay (2000);
			Servo_1.write(0);
		  
			delay(2000);
			Servo_1.write(120);
		  
			delay(7000);
			Servo_1.write(0);
		  
			delay(2000);

			myStepper.step (-68);
		 
			delay (2000);
			Servo_3.write(0);
			
			delay(2000);
			Servo_3.write(120);
		  
			delay(7000);
			Servo_3.write(0);
		  
			delay(2000);
		  
			myStepper.step (-66);
		  
			delay (2000);
			Servo_5.write(0);
			
			delay(2000);
			Servo_5.write(120);
		  
			delay(7000);
			Servo_5.write(0);
		  
			delay(2000);
		  
			myStepper.step (-51);
		
			Shutting_Down_Components();
		
			Selection = 0;
			Selection_1 = 0;
			Selection_2= 0;
		}
	}
}

// Function responsible for turning off the button's Led's, the stepper motor and the 6 servo motors
void Shutting_Down_Components() {
	
	// Turning off the 6 Led's of the buttons
	digitalWrite(Led_1, LOW);
	digitalWrite(Led_2, LOW);
	digitalWrite(Led_3, LOW);
	digitalWrite(Led_4, LOW);
	digitalWrite(Led_5, LOW);
	digitalWrite(Led_6, LOW);
			
	// Turning off the stepper motor, setting it in the original position
	digitalWrite(8, LOW);
	digitalWrite(9, LOW);
	digitalWrite(10, LOW);
	digitalWrite(11, LOW);
		
	// Turning off the 6 servo motors
	digitalWrite(23, LOW);
	digitalWrite(24, LOW);
	digitalWrite(25, LOW);
	digitalWrite(26, LOW);
	digitalWrite(27, LOW);
	digitalWrite(28, LOW);
}
	
