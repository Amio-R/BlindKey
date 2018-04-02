#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <ugpio/ugpio.h>
#include <stdio.h>
#include <sstream>

using namespace std;
//created a class that will store the input button and corresponding letters
//Initializing functions
void readingPins(int *preadValues, int *pGPIO);
void resetValues(int *preadValues, int *pGPIO);
int loggingFile(string s);
class BrailleConverter

	{
		// here is where we initilaze all the  variable, we will use an array to story the 
		//possibe input combinations and have a corresponding array for the letters 

		public:
				BrailleConverter(int input[]);
			    	static void convertBinaryInput();
			   	static void printBinaryInput();
				static void printBraille();
				static int binaryInputs[7];
				static char letter;
				static char fileName[];
				static int brailleValues[27][7];
				static char letters[27];
				~BrailleConverter();

	};
	// initialize the  values of the array
	// values are static because they wont change , stay the same for every instaintiation of the class
	char  BrailleConverter::letter = '0';
	char BrailleConverter::fileName[]= "text.txt";
	char BrailleConverter::letters[27] ={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
	 												 'R','S','T','U','V','W','X','Y','Z',' '};	
	int BrailleConverter::binaryInputs[7] = {1,0,0,0,0,0,0};
	int BrailleConverter::brailleValues[27][7]= {  {1,0,0,0,0,0,0},
	 					 						   {1,0,1,0,0,0,0},
	 					 						   {1,1,0,0,0,0,0},
	 					 						   {1,1,0,1,0,0,0},
	 					 						   {1,0,0,0,0,0,0},
							 					   {1,1,1,0,0,0,0},
							 					   {1,1,1,1,0,0,0},
							 					   {1,0,1,1,0,0,0},
							 					   {0,1,1,0,0,0,0},
							 					   {0,1,1,1,0,0,0},
							 					   {1,0,0,0,1,0,0},
							 					   {1,0,1,0,1,0,0},
							 					   {1,1,0,0,1,0,0},
							 					   {1,1,0,1,1,0,0},
							 					   {1,0,0,1,1,0,0},
							 					   {1,1,1,0,1,0,0},
							 					   {1,1,1,1,1,0,0},
							 					   {1,0,1,1,1,1,0},
							 					   {0,1,1,0,1,0,0},
							 					   {0,1,1,1,1,1,0},
							 					   {1,0,0,0,0,0,0},
							 					   {1,0,1,0,1,1,0},
							 					   {0,1,1,1,0,1,1},
							 					   {1,1,0,0,0,1,0},
							 					   {1,1,0,1,1,1,0},
							 					   {1,0,0,1,1,1,0},
							 					   {0,0,0,0,0,0,1}
	 											 };
	 	//loggingFile("initialialized Static members of object");
	 						

     
	 //constructor will set the input values to the binary inputs array(memmber of the class)
	 BrailleConverter::BrailleConverter(int input[])
	 {
	 	for(int i=0; i<7; i++)
	 	{
	 		binaryInputs[i]= input[i];
	 	}
	 	
	 	loggingFile("Function: BrailleConverter::BrailleConverter || Constructor sets argument as member in object");
	 	
	}
	//destructor will close the file
	BrailleConverter::~BrailleConverter()
	{
		std::fstream outfile; 
		outfile.close();
		loggingFile("Function: BrailleConverter::~BrailleConverter || Destructor Closes Outfile");
	 

	}
	// this will go through every element in the brailleValues array and check if it corresponds to a values
	// if it does correspond to a value, that leter will be stored in the letter char
	// if a corresponding value cannot be found an error message will show
	void BrailleConverter::convertBinaryInput()
	 {
	 	int value=0;
	 	int index=0;
	 	bool same = true;
	 	bool match =false;
	 	int counter=0;
	 	bool skip=false;
	 	int i=0;
	 	int j=0;
	 	int k=0;
		letter = '0';
		bool reached= false;
		loggingFile("Function: BrailleConverter::convertBinaryInput ||  User input Values are used and checked aganist 2D of possible letters");
	 
	 	while(same)
	 	{
	 	
	 		if (binaryInputs[k] == brailleValues[i][j])
	 		{	
	 			value++;
	 			match=true;
	 			if(value==7 && match==true)
	 			{
	 				letter= letters[i];
					reached = true;
					loggingFile("Function: BrailleConverter::convertBinaryInput ||  Corresponding letter was found, saved in data member 'letter'");
	 				same= false;
	 			}
	 			else{
	 				j++;
	 				k++;
	 			}
	 		}
	 		else
	 		{	match=false;
	 			value=0;
	 			i++;
				if(i==27)
				{
					same=false;
					reached==false;
				}
	 			j=0;
	 			k=0;
	 		}


	 	}	

		if(reached == false  || letter == '0')
		{
			loggingFile("Function: BrailleConverter::convertBinaryInput ||  Corresponding letter was not found, error message");
			cout<<"You have inputted the wrong combination. Please try again."<<endl;
		}
	 	
	 }


	 void BrailleConverter::printBinaryInput()
	 {
	 	std::fstream outfile; 
	 	outfile.open(fileName, ios::out | ios ::app);
		if (!outfile.is_open())
		{
			loggingFile("Function: BrailleConverter::printBinaryInput || textfile cannot be opened, file error is printed on to a screen");
			cout<<"Error opening file"<<endl;
			return ;
		}
		else{
		loggingFile("Function: BrailleConverter::printBinaryInput || textfile was opened successfully, corresponding letter is printed on to a screen");
		outfile << letter;
		
		}
	 }
		

int loggingFile(string input)
{
	char fileName[]= "logging.txt";
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    std::fstream outfile; 
    outfile.open(fileName, ios::out | ios ::app);
	if (!outfile.is_open())
	{
		cout<<"Error opening file"<<endl;
		return -1;
	}
		

	outfile<< __DATE__<<" "<<__TIME__<<" "<<input<<endl;

	return 0;
}
void readingPins(int *preadValues, int *pGPIO)
{
	int test, index, value;
	int pinDirection;
	for(int i=0; i<7; i++)
			{

				if((test = gpio_is_requested(pGPIO[i])) < 0)
				{
					cerr << "This GPIO pin is in use" << endl;
					return ;
				}
				else
				{
					std::ostringstream oss;
					oss<<"Function: readingPins || gpio pin for button "<< i+1<<"was read successfully. Starting read";
					std::string in = oss.str();
					loggingFile(in);
					cout << "Starting GPIO pin" << endl;
					if((pinDirection = gpio_request(pGPIO[i], NULL)) < 0)
					{
						cerr << "There was an error setting the pin value" << endl;
						return ;
					}
				}
				pinDirection = gpio_direction_input(pGPIO[i]);
				cout << "Starting read button " << i+1 << endl;

				for(int index = 0; index < 3; index++)
				{
					value = gpio_get_value(pGPIO[i]);
					if(value==1)
					{
						preadValues[i]=1;
						std::ostringstream oss;
						oss<<"Function: readingPins || Button "<<i+1<<" was pressed, value stored in array";
						std::string in = oss.str();
						loggingFile(in);
						
						cout << "Button "<< i+1<<" was pressed"<< endl;
					}
		
					value=0;
					sleep(1);
				}
			}

}
void resetValues(int *preadValues, int *pGPIO)
{
	loggingFile("Function:resetValues || GPIO pins are freed and values are set back to zero for next read");
		for(int i=0; i<7; i++)
		{
			*(preadValues + i)=0;
			gpio_free(pGPIO[i]);

		}
}

int main(){


	 	
		int gpioPin[7]={0};
		int readvalues[7]= {0,0,0,0,0,0,0};
		gpioPin[0]= 1;
		gpioPin[1]= 2;
		gpioPin[2]= 9;
		gpioPin[3]= 3;
		gpioPin[4]= 0;
		gpioPin[5]= 8;
		gpioPin[6]= 18;
		int *preadValues; 
		preadValues= readvalues;
		int *pGPIO= gpioPin;
		loggingFile("Function: main || arrays and pointer variables are declared");
		while(1)
		{
			loggingFile("Function:main || calling readingPins() function");
			readingPins(preadValues, pGPIO);

			
		
			loggingFile("Function:main || creating new BrailleConverter object passing readvalues array");
			BrailleConverter* test= new BrailleConverter(readvalues);
			loggingFile("Function:main || calling convertBinaryInput() in object to find corresponding letters");
			test->convertBinaryInput();
			
		
			char value= test->letter;
			char printValues[8]= {'0','0','0','0','0','0','0','\0'};
			for(int i=0; i<7;i++)
			{
				printValues[i]=(char) ('0' +readvalues[i]);
			}
			
			if(test->letter != '0')
			{
				loggingFile("Function:main || read was sucessful printing corresponding letter on to an array");
				cout<<"The binary inputs are: "<< printValues<<endl;
				cout<<"And the corresponding letter is "<<test->letter<<endl;
				test->printBinaryInput();
			}
			loggingFile("Function:main || calling resetValue() function");
			resetValues(preadValues, pGPIO);
	
			

			loggingFile("Function:main || read was sucessful asking user if the want to continue");
			cout<<"Enter 'y' if you wish to continue or 'n' if you dont"<<endl;
			char input;
			cin>>input;
	
			
			if(input=='n')
			{
				loggingFile("Function:main || user does not want to continue, ending program");
				cout<<"Ending program"<<endl;
				delete preadValues;
				delete pGPIO;
				return 0 ;
			}


		}

	 	return 0;


	 }
