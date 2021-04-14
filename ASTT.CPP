#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
#include<fstream.h>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip.h>
long generateBookingID();
struct myCities
{
	char cities[20][30];
	int mpos;
	int cost[20];
}cityData;
int pos;
char tempCities[20][30] = {"Amritsar\0", "Agra\0", "Varanasi\0", "Haridwar\0", "Rishikesh\0",
			"Nainital\0", "Shimla\0", "Lucknow\0", "Chandigarh\0", "SriNagar\0"
		"empty\0","empty\0","empty\0","empty\0","empty\0","empty\0","empty\0","empty\0","empty\0","empty\0"};
int today = 0;                       //variable that holds  the current date
int t_TotalTickets = 0;
struct seatsAvailable
{
    int seatsOnRoute[20];
    int dayOJ;
};
typedef struct seatsAvailable availSeats;
availSeats seats[4];
class ToursTravels                     //class declaration
{
    public:
    void bookTicket();
    void cancelTicket();
    void viewTicket();
    void welcomeScreen();
    void firstMenu(int screen);
    void userScreen();
    void viewCities();
    void AddCityToArray();
    void RemoveCityFromArray();
    void DisplayStats();
    void editCities();
};
class Ticket                           //class declaration
{
  private:
	  char name[30];
	  char fromCity[30];
	  char toCity[30];
	  int NoOfPass;
  public:
	  char* getName();
	  void setName(char tname[30]);
	  int getNoOfPass();
	  void setNoOfPass(int tNoOfPass);
	  char* getToCity();
	  void setToCity(char cityName[30]);
	  char* getFromCity();
	  void setFromCity(char cityName[30]);
	  int month;
	  int day;
	  int year;
	  char phoneNumber[15];
	  void displayData();
	  long  bookingID;
	  int cost;
};
void Ticket::displayData()           //function to display the ticket after
{                                    //it's confirmed/view ticket
    cout << "Booking ID : " << bookingID << endl;
    cout << "Name : " << name << endl;
    cout << "From City : " <<fromCity << endl;
    cout << "To City : " << toCity << endl;
    cout << "Date Of Journey :" << day << ":" << month << ":" << year << endl;
    cout << "Number of Passengers :" << NoOfPass << endl;
    cout << "Phone Number : " << phoneNumber << endl;
    cout << "Ticket Amount : " << cost << endl;
}
char* Ticket::getToCity()
{
    return toCity;
}
void Ticket::setToCity(char cityName[30])
{
    strcpy(toCity, cityName);
}
char* Ticket::getFromCity()
{
    return fromCity;
}
void Ticket::setFromCity(char cityName[30])
{
    strcpy(fromCity, cityName);
}
int Ticket::getNoOfPass()
{
    return NoOfPass;
}
void Ticket::setNoOfPass(int tNoOfPass)
{
    NoOfPass=tNoOfPass;
}
char* Ticket::getName()
{
    return name;
}
void Ticket::setName(char tname[30])
{
    strcpy(name,tname);
}

				 //function to know the date
int dateMenu(int &selectedDay, int &selectedMon, int &selectedYear)
{
  struct date d;
  getdate(&d);
  int day = d.da_day;
  int month = d.da_mon;
  int year = d.da_year;
  int choice;
  for(int i=0; i<4; i++)
   {
    cout<<i+1<<". "<<"\"" << day+2+i<<":"<<month<<":"<<year<< "\"" << endl;
   }
    cin >> choice;
    if (choice < 1 || choice > 4)
    {
	cout << endl;
	cout << "Please choose between the given dates: " << endl;
	cin >> choice;
    }
   selectedDay = day+choice+1;
   selectedMon = month;
   selectedYear = year;
   return choice;
}
void ToursTravels::bookTicket()       //bookTicket func. defination
{
    Ticket myTicket;
    int toCityChoice;
    int fromCityChoice;
    clrscr();
    welcomeScreen();
    cout<< "****************************************************************" << endl;
    cout << "Go ahead, book your ticket" << endl;
    cout<< "****************************************************************" << endl;
    myTicket.setFromCity("Delhi");
    cout << "Please select the city you want to travel from Delhi: " << endl;
    cout<< "****************************************************************" << endl;
    int validationCheck = 0;
    for (int j=0;j < 20; j++)//display cities
    {
      if (strcmp(cityData.cities[j], "") != 0)
      {
	  cout<< j+1 << ". "<<cityData.cities[j] <<endl;
      }
      validationCheck = j;
    }
    cout<< "****************************************************************" << endl;
    cout<<"Please select your destination -> "<<endl;
    cin>>toCityChoice;
    if (toCityChoice > validationCheck)
    {
	cout << "Please enter correct city code : " << endl;
	cin >> toCityChoice;
    }
    myTicket.setToCity(cityData.cities[toCityChoice-1]);
    clrscr();
    cout << "From City : " << myTicket.getFromCity() << "\t" << "To City : " << myTicket.getToCity() << endl;
    cout << "Choose date of journey -> " << endl;
    int choice = 0;
    int dayOJ = 0, monthOJ = 0, yearOJ = 0;
    choice = dateMenu(dayOJ, monthOJ, yearOJ);
    cout << "Selected date of journey : " << dayOJ << ":" << monthOJ << ":" << yearOJ << endl;
    myTicket.day=dayOJ;
    myTicket.month=monthOJ;
    myTicket.year=yearOJ;
    clrscr();
    cout << "From City : " << myTicket.getFromCity() << "\t" << "To City : " << myTicket.getToCity() << endl;
    cout << "Date of Journey : " << myTicket.day <<":"<<myTicket.month<<":"<<myTicket.year<<endl;
    cout << "Enter Number of Passengers -> " << endl;
    int passNumber;
    cin >> passNumber;
    myTicket.setNoOfPass(passNumber);


    //manage seats for this route
    int diff = dayOJ - today; //agar 2 hain to 0, 3 -> 1, 4->2, 5->3
    switch(diff)
    {
	case 2:
	{
	  if (myTicket.getNoOfPass() > seats[0].seatsOnRoute[toCityChoice])
	  {
	     cout << "Error : Seats Not Available" << endl;
	     cout <<"\n\n\n\n"<<endl;
	     cout <<"Press any Key to Continue....."<<endl;
	     getch();
	     firstMenu(2);
	  }
	  seats[0].seatsOnRoute[toCityChoice] = seats[0].seatsOnRoute[toCityChoice] - myTicket.getNoOfPass();

	}
	break;
	case 3:
	{
	  if (myTicket.getNoOfPass() > seats[1].seatsOnRoute[toCityChoice])
	  {
	     cout << "Error : Seats Not Available" << endl;
	     cout << "\n\n\n\n"<<endl;
	     cout << "Press any key to Continue....."<<endl;
	     getch();
	     firstMenu(2);
	  }
	  seats[1].seatsOnRoute[toCityChoice] = seats[1].seatsOnRoute[toCityChoice] - myTicket.getNoOfPass();

	}
	break;
	case 4:
	{
	  if (myTicket.getNoOfPass() > seats[2].seatsOnRoute[toCityChoice])
	  {
	     cout << "Error : Seats Not Available" << endl;
	     return;
	  }
	  seats[2].seatsOnRoute[toCityChoice] = seats[2].seatsOnRoute[toCityChoice] - myTicket.getNoOfPass();

	}
	break;
	case 5:
	{
	  if (myTicket.getNoOfPass() > seats[3].seatsOnRoute[toCityChoice])
	  {
	     cout << "Error : Seats Not Available" << endl;
	     return;
	  }
	  seats[3].seatsOnRoute[toCityChoice] = seats[3].seatsOnRoute[toCityChoice] - myTicket.getNoOfPass();

	}
	break;
	default:
		cout << "Sorry, Seats not available" << endl;
	break;
    }
    cout << endl;
    char t_name[30];
    cout << "Enter Name : " << endl;
    cin >> t_name;
    myTicket.setName(t_name);
    cout << endl;
    cout << "Enter Phone Number : " << endl;
    char phNumber[10];
    gets(phNumber);
    if (strlen(phNumber)>10)
    {
	cout<<"wrong no.";
	strcpy(myTicket.phoneNumber, "NULL");//NULL is copied when no is wrong
    }
    else
    {
	strcpy(myTicket.phoneNumber, phNumber);
    }
    int booking_id = 0;
    booking_id = rand() % 10000;
    myTicket.bookingID = generateBookingID();
			  //getting the cost of the ticket
    char* tempToCity = myTicket.getToCity();
			 //go to the loop in cityData and check toCity and get cost
    int index = 0;
    for (int i = 0; i < cityData.mpos; i++)
    {
	if (stricmp(tempToCity, cityData.cities[i]) == 0)
	{
	    index = i;
	}
    }
    int cost = cityData.cost[index];

    myTicket.cost = (myTicket.getNoOfPass() * cost);

    clrscr();
    cout << "Ticket initiary details" << endl;
    myTicket.displayData();
    cout << "##### ticket confirmed #####" << endl;
    t_TotalTickets++;
    ofstream fo("stu.dat", ios::app|ios::binary);

    fo.write((char*)&myTicket, sizeof(myTicket));
    fo.close();
    cout << "Press any key to go to Main Menu" << endl;
    getch();
    clrscr();
    welcomeScreen();
    firstMenu(2);
}
long generateBookingID()
{
    struct time t;
    gettime(&t);
    int hour = t.ti_hour;
    int min = t.ti_min;
    int sec = t.ti_sec;
    struct date d;
    getdate(&d);
    int day = d.da_day;
    int mon = d.da_mon;
    int year = d.da_year;
    long bID = 100*day+10*mon+year+hour+min+sec;
    return bID;
}
void ToursTravels::viewTicket()
{
    clrscr();
    welcomeScreen();
    cout << "###############################" << endl;
    cout << "Enter your booking ID : " << endl;
    int bookingID;
    cin >> bookingID;
    char found = 'n';
    Ticket temp;
    ifstream fi("stu.dat", ios::in|ios::binary);
    if (!fi.good())
    {
	 cout << "Error in database or there is no booking, please try again later" << endl;
	 getch();
	 clrscr();
	 welcomeScreen();
	 firstMenu(2);
	 return;
    }
    while (!fi.eof())
    {
	fi.read((char*)&temp, sizeof(temp));
	if (temp.bookingID == bookingID)
	{
	    temp.displayData();
	    found = 'y';
	    break;
	}
    }
    if (found == 'n')
    {
	 cout << "No Record Found, please enter correct number" << endl;
    }
    fi.close();
    cout << "Press Any Key to go to Main Menu" << endl;
    getch();
    clrscr();
    welcomeScreen();
    firstMenu(2);
}
void ToursTravels::cancelTicket()
{
    clrscr();
    char cnfrm;
    welcomeScreen();
    cout << "###############################" << endl;
    cout << "Enter your booking ID : " << endl;
    int bookingID;
    cin >> bookingID;
    char found = 'n';
    Ticket temp;
    ifstream fi("stu.dat", ios::in|ios::binary);
    if (!fi.good())
    {
	cout << "Error in database, or no ticket..." << endl;
	getch();
	welcomeScreen();
	firstMenu(2);
	return;
    }
    ofstream tfile("temp.dat",ios::out|ios::binary);
    while (!fi.eof())
    {
	fi.read((char*)&temp, sizeof(temp));
	if (temp.bookingID == bookingID)
	{
	    cout<<"Your Ticket : "<<endl;
	    temp.displayData();
	    found = 'y';
	    cout<<endl<<endl;
	    cout<<"Do You want to Cancel this Ticket (Y/N)"<<endl;
	    cin>>cnfrm;
	     if(cnfrm == 'n'|| cnfrm == 'N')
	      {

	       tfile.write((char*)&temp, sizeof(temp));
	       cout<<"Don't Worry!! Your Ticket is with Us!!";

	      }
	      else
		      {
		  cout << "Your ticket is deleted" << endl;
	      }
	      fi.close();
	      tfile.close();
	      break;
	}
	else
	{
	    tfile.write((char*)&temp, sizeof(temp));
	}
	fi.close();
	tfile.close();
    }
    if (found == 'n')
    {
	 cout << "No Record Found, please enter correct bookingID" << endl;
	 remove("temp.dat");
    }
    else
    {
	remove("stu.dat");
	if (rename("temp.dat", "stu.dat") == 0)
	{

	    t_TotalTickets--;
	}
	else
	{
	    cout << "database is having some error" << endl;
	}
    }
    cout << "Press Any Key to go to Main Menu" << endl;
    getch();
    clrscr();
    welcomeScreen();
    firstMenu(2);
}
void ToursTravels::welcomeScreen()     //welcomeScreen func. defination
{
  //Welcome Screen Banner
  cout << "         **************************************************************  " <<endl;
  cout << "         *          #                     ######                      *  " <<endl;
  cout << "         *        #   #                   #			      *  " << endl;
  cout << "         *        #####                   ######                      *  " << endl;
  cout << "         *        #   #  ##                    #   ##                 *  " << endl;
  cout << "         *        #   #  ##               ######   ##                 *  " << endl;
  cout << "         *                                                            *  " << endl;
  cout << "         *                TOURS & TRAVELS                             *  " << endl;
  cout << "         **************************************************************" << endl;
  cout<<"\t\t\t Welcome To A.S Tours & Travels \n\n" << endl;
}
void ToursTravels::userScreen()
{
    clrscr();
    welcomeScreen();
    int choice = 0;
    cout << "**************************************************************" << endl;
    cout << "1. Login as ADMIN" << endl;
    cout << "2. Login as Traveler" << endl;
    cout << "3. Exit Application "<< endl;
    cout << "**************************************************************" << endl;
    cin >> choice;
    char password[10];
    if (choice == 1)
    {
	cout << "\n\n " << endl;
	char *password;
	password = getpass("Enter admin password:");
	if (strcmp(password, "admin123") == 0)
	{
	    firstMenu(1);
	}
	else
	{
	    cout << "Password is wrong,press any key to go to Login menu." << endl;
	    getch();
	    userScreen();
	}
    }
    else if (choice == 2)
    {
	firstMenu(2);
    }
    else if (choice == 3)
    {
	exit(0);
    }
    else
    {
	cout << "Please enter write choice, press any key to continue again" << endl;
	getch();
	userScreen();
    }
}
void ToursTravels::viewCities()
 {
    cout<<"The cities that we offer services, in, are : "<<endl;

    for (int j=0;j < cityData.mpos; j++)
    {
	  cout<< j+1 << ". "<<cityData.cities[j] <<endl;
    }
   cout<<"\n\n\n\n\n"<<endl;
   cout<<"Press any key to continue...."<<endl;
   getch();
   firstMenu(1);
 }
void ToursTravels::AddCityToArray()
{
    cout<<"The Cities where we already offer services in, are: "<<endl;
   for (int k=0;k < cityData.mpos; k++)
    {
	  cout<< k+1 << ". "<<cityData.cities[k] <<endl;
    }
   if (cityData.mpos == 20)
   {
       cout << "You can not add more cities... " << endl;
       getch();
       firstMenu(1);
   }
   else
   {
	char cityName[50];
	   cout << "Enter City Name : " << endl;
	   cin >> cityName;
	   int isExist = 0;
	   for (int i = 0; i < cityData.mpos; i++)
	   {
		if (stricmp(cityName, cityData.cities[i]) == 0)
		{
		   isExist = 1;
		   break;
		 }
	   }
	   if (isExist == 1)
	   {
		cout << "City already exists... press enter to continue...." << endl;
		getch();
		firstMenu(1);
	 }
	 else
	   {
		strcpy(cityData.cities[cityData.mpos],cityName);
		cout<<"City added successfully.....press enter to continue...."<<endl;
		cityData.cost[cityData.mpos] = (300+(cityData.mpos)*2);
	       cityData.mpos++;
		remove("cities.dat");
		ofstream ACTF("cities.dat", ios::out|ios::binary);
		if(ACTF.good())
		{
		   ACTF.write((char*)&cityData,sizeof(cityData));
		}
		 ACTF.close();

		 getch();
		 firstMenu(1);
	    }
	}

}
void ToursTravels::RemoveCityFromArray()
{
    cout<<"The cities that we offer services, in, are : "<<endl;
    for (int j=0;j < cityData.mpos; j++)
    {
	  cout<< j+1 << ". "<<cityData.cities[j] <<endl;
    }
    char temparr[20][20];
    int tempcost[20];
    char cityName[50];
    cout << "Enter City Name : " << endl;
    cin >> cityName;
    j = 0;

	int cityFound = 0;
    for (int i = 0; i < cityData.mpos;i++)
    {
	if ((stricmp(cityData.cities[i], cityName) == 0))
	{

	    cityFound = 1;
	    continue;
	}
	else
	{
	    strcpy(temparr[j], cityData.cities[i]);
	    tempcost[j] = cityData.cost[i];
	    j++;

	}
    }
    if (cityFound != 1)
    {
	cout << "City Not Found... press any key to continue" << endl;
	getch();
	firstMenu(1);
    }

    cityData.mpos = j;

    for(i=0; i<cityData.mpos; i++)
    {
      strcpy(cityData.cities[i],temparr[i]);
      cityData.cost[i], tempcost[i];
    }
    cout<<"City removed successfully....press Enter to continue...."<<endl;
      remove("cities.dat");
      ofstream RCTF("cities.dat", ios::out|ios::binary);
       if(RCTF.good())
	{
	    RCTF.write((char*)&cityData,sizeof(cityData));
	}
       RCTF.close();
    getch();
    firstMenu(1);
}
void ToursTravels::editCities()
{
 char cityName[50];
 int cityNo;
    cout<<"The Cities where we already offer services in, are: "<<endl;
   for (int k=0;k < cityData.mpos; k++)
    {
	  cout<< k+1 << ". "<<cityData.cities[k] <<endl;
    }
    cout<<"\n\n"<<endl;
    cout << "Enter City (number) : " << endl;
    cin>>cityNo;
    cout<<"\n\n"<<endl;
    cout<<"Enter New Name for "<<cityData.cities[cityNo-1]<<endl;
    cin>>cityName;
    if (stricmp(cityData.cities[cityNo-1], cityName) == 0)
	{

	    cout << "City's name is already the same...." << endl;
	}
    else if (stricmp(cityData.cities[cityNo-1], cityName)!=0)
	{
	   strcpy(cityData.cities[cityNo-1], cityName);
	   cout<< "City's Name has been successfully changed...."<<endl;
	   cout<<"\n\n\n\n"<<endl;
	   cout<<"Press any key to continue...."<<endl;
	   getch();
	   firstMenu(1);
	}
	else
	{
	    cout << "City Not Found...press any key to continue" << endl;
	}

    getch();
    firstMenu(1);
}
void ToursTravels::DisplayStats()
{
    clrscr();
    //welcomeScreen();


    cout<<
	 setw(13) << "[Booking ID]" << setw(10) << "[Name]" << setw(10) << "[Contact]" << setw(10) << "[To City]" << setw(14) << "[#Passengers]" << setw(10) << "[Cost]" << endl;
    int totalTickets = 0;
    ifstream dsf("stu.dat", ios::out|ios::binary);
    if (dsf.good())
    {
	while (1)
	{
	    Ticket temp;
	    dsf.read((char*)&temp, sizeof(temp));
	    if (dsf.eof())
	    {
		break;
	    }
	    cout <<
		 setw(10) << temp.bookingID << setw(10) << temp.getName() << setw(10) << temp.phoneNumber << setw(10) << temp.getToCity() << setw(14) <<  temp.getNoOfPass() << setw(10) << temp.cost << endl;
	    totalTickets++;
	}
    }
    dsf.close();
    cout << endl;
    cout << "Total Booked Tickets = " << totalTickets << endl;
    cout << "Press Any Key to go to Main Menu" << endl;
    getch();
    clrscr();
    welcomeScreen();
    userScreen();
}
void ToursTravels::firstMenu(int screen)            //firstMenu func. defination
{
     clrscr();
     welcomeScreen();
     if (screen == 1)
     {
       cout<< "****************************************************************************************************************************************************************" << endl;
       cout << "1. List of Cities" <<endl;
       cout << "2. Add new City" << endl;
       cout << "3. Remove City" << endl;
       cout << "4. Edit City" <<endl;
       cout << "5. Booking Statistics" << endl;
       cout << "6. LogOut" << endl;
       cout<< "****************************************************************************************************************************************************************" << endl;
       int choice = 0;
       cin >> choice;
       switch(choice)
       {
	   case 1:
	   {
	      clrscr();
	      viewCities();
	   }
	   break;
	   case 2:
	   {
	       AddCityToArray();
	   }
	   break;
	   case 3:
	   {
	       RemoveCityFromArray();
	   }
	   break;
	   case 4:
	   {
	    editCities();
	   }
	   break;
	   case 5:
	   {
	       DisplayStats();
	   }
	   break;
	   case 6:
	   {
	       userScreen();
	   }
	   break;
	   default:
	   {
	       cout << "Please enter right choice" << endl;
	   }
	   break;
       }
     }
     else
     {
       int choice = 0;
       cout<< "****************************************************************************************************************************************************************" << endl;
       cout<<"1. Plan your Journey"<<endl;
       cout<<"2. View your Journey"<<endl;
       cout<<"3. Cancel your Journey"<<endl;
       cout<<"4. Go to the login Screen"<<endl;
       cout<< "****************************************************************************************************************************************************************" << endl;
       cout << "Please select your desired option : " ;
       cin>>choice;
       switch (choice)       //beginning of switch case
       {
	 case 1:
	 {
	    bookTicket();
	 }
	 break;
	 case 2:
	 {
	    viewTicket();
	 }
	 break;
	 case 3:
	 {
	   cancelTicket();
	 }
	 break;
	 case 4:
	 {
	     clrscr();
	     userScreen();
	 }
	 break;
	 default:
	 {
	     cout << "Please enter correct choice" << endl;
	 }
       }
      }
}
void init()
{
    //initialize seats on different routes
    struct date d;
    getdate(&d);
    int day = d.da_day;
    today = day;
    for (int i = 0; i < 4; i++)
    {
	seats[i].dayOJ = (day+2+i);
	for(int j = 0; j < 20; j++)
	{
	    seats[i].seatsOnRoute[j] = 50;
	}
    }
    int checkFile = 0;
    ifstream ifs("cities.dat", ios::in|ios::binary);
    if (!ifs)
    {

	checkFile = 0;
	ifs.close();
    }
    else
    {
	checkFile = 1;
	ifs.close();
    }
    if (checkFile == 0)
    {
	cout << "checkFile == 0" << endl;
	struct myCities cityList;
	for (i = 0; i < 10; i++)
	{
	    cout << "tempcities[" << i+1 << "] = "<< tempCities[i] << endl;
	    strcpy(cityList.cities[i],  tempCities[i]);
	    cityList.cost[i] = (300+i*2);
	}
	cityList.mpos = 10;
	ofstream cityFile("cities.dat", ios::out|ios::binary);
	if (cityFile.good())
	{
	    cityFile.write((char*)&cityList, sizeof(cityList));
	}
	cityFile.close();
    }
    cout << "Reading from file cities" << endl;
    ifstream ifst("cities.dat", ios::in|ios::binary);
    if (ifst.good())
    {
	struct myCities temp1;

	ifst.read((char*)&temp1, sizeof(temp1));
	cout << "mpos = " << temp1.mpos << endl;
	for (int i = 0; i < temp1.mpos; i++)
	{
	  cout << "city[" << i+1 << "] = " << temp1.cities[i] << endl;
	  strcpy(cityData.cities[i],temp1.cities[i]);
	  cityData.cost[i] = temp1.cost[i];
	}
	cout << "mpos = " << temp1.mpos << endl;
	cityData.mpos = temp1.mpos;
	ifst.close();
    }
}

int main()
{
    clrscr();
    init();
    ToursTravels myTravel;
    myTravel.welcomeScreen();
    myTravel.userScreen();
    getch();
    return 0;
}
