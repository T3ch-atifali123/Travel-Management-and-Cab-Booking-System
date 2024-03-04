#include<iostream>
#include<thread>
#include<string>
#include<ctime>
#include<conio.h>
#include<fstream>
#include<iomanip>
using namespace std;
using namespace std::chrono_literals;

						/* CLASSES AND THEIR DEFINITIONS*/
class User;
class driver;
class Van;
class passenger;
class admin;
class ride;
class promo;

						/* CONSTANT GLOBAL VARIABLES */

const string QUE[5]={"What is the name of town you were born in?", "What was your Mother's Full name?", "What was your first car?" , "What was your school name?", "What was the name of your fist pet?"};
const string LOCS[6] = { "North Nazimabad","Water Pump","Gulshan Iqbal","Johar","Malir Cantt","Lyari Exp" };
const string pref[3] = { "AC","Non-AC","Any" };

class User
{		
//		THESE ARE BASIC DATA/CREDENTIALS OF EVERY USER WHETHER IT BE ADMIN, DRIVER OR PASSENGER
	protected:
		string full_name, cnic, phone_num;
		string id, password, queAns;
		int age, queNum;
	public:
		User():full_name("N/A"),age(0),cnic("N/A"),phone_num("N/A"),id("N/A"),password("N/A"),queNum(0)
		{
		}		
		void set_queNum(int queNum){this->queNum = queNum;}
		int get_queNum(){return queNum;}
		
		void set_queAns(string queAns){this->queAns = queAns;}
		string get_queAns(){return queAns;}

		void set_full_name(string full_name){this->full_name = full_name;}
		string get_full_name(){return full_name;}
		
		void set_cnic(string cnic){this->cnic = cnic;}
		string get_cnic(){return cnic;}
		
		void set_phone_num(string phone_num){this->phone_num = phone_num;}
		string get_phone_num(){return phone_num;}
		
		void set_id(string id){this->id = id;}
		string get_id(){return id;}
		
		void set_password(string password){this->password = password;}
		string get_password(){return password;}	
		
		void set_age(int age){this->age = age;}
		int get_age(){return age;}	
		
		//THESE ARE PURE VIRTUAL FUNCTIONS FOR CHILD OBJECTS TO COMPLETE DEFINITION
		virtual void update()=0;
		virtual void extract(ifstream&)=0;
};

class Van	//INNER CLASS OF THE CLASS 'DRIVER'
{
	string ride_type, ride_name, ride_color, ride_regNumber;
	int numOfSeats, numOfPassengers;

	public:
		void set_details(string str1,string str2,string str3,string str4, int num1, int num2)
		{
			ride_type = str1;
			ride_name = str2;
			ride_color = str3;
			ride_regNumber = str4;
			numOfSeats = num1;
			numOfPassengers = num2;
		}
		
		void set_ride_type(string ride_type){this->ride_type = ride_type;}
		string get_ride_type(){return ride_type;}
		
		void set_ride_name(string ride_name){this->ride_name = ride_name;}
		string get_ride_name(){return ride_name;}
		
		void set_ride_color(string ride_color){this->ride_color = ride_color;}
		string get_ride_color(){return ride_color;}
		
		void set_ride_regNumber(string ride_regNumber){this->ride_regNumber = ride_regNumber;}
		string get_ride_regNumber(){return ride_regNumber;}
		
		void set_numOfSeats(int numOfSeats){this->numOfSeats = numOfSeats;}
		int get_numOfSeats(){return numOfSeats;}
		
		void set_numOfPassengers(int numOfPassengers){this->numOfPassengers = numOfPassengers;}
		int get_numOfPassengers(){return numOfPassengers;}

		friend ostream& operator<<(ostream&, driver);
};

class driver : public User
{
	private:
		string starting_route, current_location;
		//Variables for Time
		tm starting_time, ending_time;
		float balance=0, rating=0;
		int points=0, total_rides=0;
		Van V;
	public:	
		static int driverCount;		//THIS STORES TOTAL COUNT OF DRIVERS
		
		//THIS FUNCTION SETS VALUES FOR EACH ATTRIBUTE; FUNCTION USED IN SIGNUP OR REGISTRATION
		void set_details(string userID, string pass,string str3,string str4,string str5,string str6,string vstr1,int num5,float num1,float num2,int num3,int num4, string vstr2,string vstr3,string vstr4, int var1, int var2,tm ST, tm ET)	
		{		
			id =userID;
			password = pass;
			full_name = str3;
			cnic = str4;
			starting_route = str5;
			current_location=starting_route;
			phone_num = str6;
			balance = num1;
			rating = num2;
			points = num3;
			total_rides = num4;
			age = num5;
			queAns = starting_route;
			starting_time = ST;
			ending_time = ET;
			queAns = starting_route;
			V.set_details(vstr1,vstr2,vstr3,vstr4,var1,var2);
		}
		
		//FUNCTION USED TO CALL PUBLIC FUNCTION OF PRIVATE DATA MEMBER; USED IN EDIT DRIVER BIO FUNCTION
		void set_van_details(string str1,string str2,string str3,string str4, int num1, int num2)
		{
			V.set_details(str1,str2,str3,str4,num1,num2);
		}
		
		//EXTRACT FUNCTION USED TO EXTRACT DATA FROM RESPECTIVE DATA FILES
		void extract(ifstream &input)
		{
			string vstr1,vstr2,vstr3,vstr4;
			int var1,var2;
			getline(input,id);
			getline(input,password);
			getline(input,full_name);
			getline(input,cnic);
			getline(input,starting_route);
			getline(input,phone_num);
			getline(input,queAns);
			getline(input,vstr1);
			input >> age >> queNum >> balance >> rating >> points >> total_rides;
			input >> starting_time.tm_hour >> starting_time.tm_min >> starting_time.tm_sec;
			input >> ending_time.tm_hour >> ending_time.tm_min >> ending_time.tm_sec;
			input.ignore(256,'\n');
			getline(input,vstr2);
			getline(input,vstr3);
			getline(input,vstr4);
			input >> var1 >> var2;
			input.ignore(256,'\n');
			V.set_details(vstr1,vstr2,vstr3,vstr4,var1,var2);
		}
		
		//UPDATE FUNCTION USED TO UPDATE THE TEXT FILES FO RCHANGES
		void update()
		{
			ofstream output("driver.txt",ios::app);
			output << "\n" << id;
			output << "\n" << password;
			output << "\n" << full_name;
			output << "\n" << cnic;
			output << "\n" << starting_route;
			output << "\n" << phone_num;
			output << "\n" << queAns;
			output << "\n" << V.get_ride_type();  
			output << "\n" << age;
			output << "\n" << queNum;
			output << "\n" << balance;
			output << "\n" << rating;
			output << "\n" << points;
			output << "\n" << total_rides;
			output << "\n" << starting_time.tm_hour << " " << starting_time.tm_min << " " << starting_time.tm_sec;
			output << "\n" << ending_time.tm_hour << " " << ending_time.tm_min << " " << ending_time.tm_sec;
			output << "\n" << V.get_ride_name();
			output << "\n" << V.get_ride_color();
			output << "\n" << V.get_ride_regNumber();
			output << "\n" << V.get_numOfSeats();
			output << "\n" << V.get_numOfPassengers();
			output.close();
		}
		
			//SETTER GETTER FUNCTIONS
		void set_balance(float balance){this->balance = balance;}
		float get_balance(){return balance;}
		
		void set_rating(float rating){this->rating = rating;}
		float get_rating(){return rating;}
		
		void set_points(int points){this->points = points;}
		int get_points(){return points;}
	
		void set_starting_route(string starting_route){this->starting_route = starting_route;}
		string get_starting_route(){return starting_route;}
		
		void set_current_location(string current_location){this->current_location = current_location;}
		string get_current_location(){return current_location;}
		
		void set_total_rides(int total_rides){this->total_rides = total_rides;}
		int get_total_rides(){return total_rides;}
		
		void set_starting_time(tm starting_time){this->starting_time = starting_time;}
		tm get_starting_time(){return starting_time;}
		
		void set_ending_time(tm ending_time){this->ending_time = ending_time;}
		tm get_ending_time(){return ending_time;}
	
		string get_ride_type(){return V.get_ride_type();}
		
		string get_ride_name(){return V.get_ride_name();}
		
		string get_ride_color(){return V.get_ride_color();}
		
		string get_ride_regNumber(){return V.get_ride_regNumber();}
		
		int get_numOfSeats(){return V.get_numOfSeats();}
		
		void set_numOfPassengers(int num){ V.set_numOfPassengers(num); }
		int get_numOfPassengers(){return V.get_numOfPassengers();}
		
		//STATIC FUNCTION TO DISPLAY ITS COUNT
		static void displayDriverCount()
		{
			string str = "There are ";
			string str2 = " registered drivers so far...\n";
			int i=0;
			
			while(str[i]!='\0')
			{
				std::this_thread::sleep_for(50ms);
				cout << str[i];
				i++;
			}
			i=0;
			std::this_thread::sleep_for(50ms);
			cout << driverCount;
			while(str2[i]!='\n')
			{
				std::this_thread::sleep_for(50ms);
				cout << str2[i];
				i++;
			}
			cout << endl;
		}
		
		friend ostream& operator<<(ostream&, driver);
};
int driver::driverCount=0;

class admin : public User
{
	private:
		string area;		//EACH ADMIN HAS HIS OWN AREA OF CONTROL
	public:
		static int adminCount;
		
		admin():area("N/A")
		{
		}
		void set_details(string adminID, string pass, string str3,string str4,string str5,string str6,int num)
		{
			id = adminID;
			password = pass;
			full_name = str3;
			cnic = str4;
			phone_num = str5;
			area = str6;
			age = num;
		}
		
		void set_area(string area){this->area = area;}
		string get_area(){return area;}
		
		void update()
		{
			ofstream output("admin.txt");
			output << "\n" << id;
			output << "\n" << password;
			output << "\n" << full_name;
			output << "\n" << cnic;
			output << "\n" << phone_num;
			output << "\n" << area;
			output << "\n" << age;
			output.close();
		}
		
		void extract (ifstream &input)
		{
			getline(input,id);
			getline(input,password);
			getline(input,full_name);
			getline(input,cnic);
			getline(input,phone_num);
			getline(input,queAns);
			getline(input,area);
			input >> age >> queNum;
			input.ignore(256,'\n');
		}
		static void displayAdminCount()
		{
			string str = "There are ";
			string str2 = " registered admins so far...\n";
			int i=0;
			
			while(str[i]!='\0')
			{
				std::this_thread::sleep_for(50ms);
				cout << str[i];
				i++;
			}
			i=0;
			std::this_thread::sleep_for(50ms);
			cout << adminCount;
			while(str2[i]!='\n')
			{
				std::this_thread::sleep_for(50ms);
				cout << str2[i];
				i++;
			}
			cout << endl;
		}
};
int admin::adminCount=0;

class passenger : public User
{
	private:
		string area,preferences;
		float balance, rating;
		int points, total_rides;
		bool in_ride;
	public:
		static int passengerCount;
		//DEFAULT CONSTRUCTOR TO SET DEFAULT VALUES
		passenger():area("N/A"),preferences("N/A"),balance(10000),rating(0.0),points(0),total_rides(0)
		{
		}
		//OVERLOADED FUNCTION
		void set_details(string userID, string pass,string str3,string str4,string str5,string str6,string str7,string str8, float num1,float num2,int num3,int num4,int num5,bool in_ride)
		{
			id =userID;
			password = pass;
			full_name = str3;
			cnic = str4;
			area = str5;
			phone_num = str6;
			queAns = str8;
			preferences = str7;
			balance = num1;
			rating = num2;
			points = num3;
			total_rides = num4;
			age = num5;
			this->in_ride = in_ride;
		}
		void set_details(string str1, string str2,string str3,string str4,string str5,string str6,string str7,string str8,int num, int num2)
		{
			full_name = str1;
			cnic = str2;
			area = str3;
			phone_num = str4;
			preferences = str5;
			id = str6;
			password = str7;
			queAns = str8;
			age = num;
			queNum=num2;
			balance = 0;
			rating = 0;
			points = 0;
			total_rides=0;
		}
		void update()
		{
			ofstream output("user.txt",ios::app);
			output << "\n" << get_id();
			output << "\n" << password;
			output << "\n" << full_name;
			output << "\n" << cnic;
			output << "\n" << area;
			output << "\n" << phone_num;
			output << "\n" << queAns;
			output << "\n" << preferences;
			output << "\n" << age; 
			output << "\n" << queNum; 
			output << "\n" << balance;
			output << "\n" << rating;
			output << "\n" << points;
			output << "\n" << total_rides;
			output << "\n" << in_ride;
			output.close();
		}
		
		void extract(ifstream &input)
		{
			getline(input,id);
			getline(input,password);
			getline(input,full_name);
			getline(input,cnic);
			getline(input,area);
			getline(input,phone_num);
			getline(input,queAns);
			getline(input,preferences);
			input >> age >> queNum >> balance >> rating >> points >> total_rides >> in_ride;
			input.ignore(256, '\n');
		}
		
		void set_in_ride(bool in_ride){this->in_ride = in_ride;}
		bool get_in_ride(){return in_ride;}
		
		void set_area(string area){this->area = area;}
		string get_area(){return area;}
		
		void set_preferences(string preferences){this->preferences = preferences;}
		string get_preferences(){return preferences;}
		
		void set_balance(float balance){this->balance = balance;}
		float get_balance(){return balance;}
		
		void set_rating(float rating){this->rating = rating;}
		float get_rating(){return rating;}
		
		void set_points(int points){this->points = points;}
		int get_points(){return points;}
		
		void set_total_rides(int total_rides){this->total_rides = total_rides;}
		int get_total_rides(){return total_rides;}		
		
		static void displayUserCount()
		{
			string str = "There are ";
			string str2 = " registered passengers so far...\n";
			int i=0;
			
			while(str[i]!='\0')
			{
				std::this_thread::sleep_for(50ms);
				cout << str[i];
				i++;
			}
			i=0;
			std::this_thread::sleep_for(50ms);
			cout << passengerCount;
			while(str2[i]!='\n')
			{
				std::this_thread::sleep_for(50ms);
				cout << str2[i];
				i++;
			}
			cout << endl;
		}
		
		friend ostream& operator<<(ostream&, passenger); 
};
int passenger::passengerCount=0;

class ride
{
	private:
		string RideID;
		string PassengerID, DriverID;
		string pickup_location, dropoff_location;
		string ride_status;
		string user_feedback;
		tm *start_time, *end_time, *booking_time;	//START TIME INDICATES PICKUP TIME, END FOR DROPOFF, BOOKING FOR TIME OF BOOKING
		int user_rating;
		float fare,discount;
	public:
		static int rideCount;
		ride():RideID("N/A"),PassengerID("N/A"),DriverID("N/A"),pickup_location("N/A"),dropoff_location("N/A"),ride_status("N/A"),user_feedback("N/A"),user_rating(0),fare(0),discount(0)
		{
			start_time = new tm;
			end_time = new tm;
			booking_time = new tm;
		}
		ride(string arr[6],int rating, float fare, float discount):RideID(arr[0]),PassengerID(arr[1]),DriverID(arr[2]),pickup_location(arr[3]),dropoff_location(arr[4]),user_feedback(arr[5]),user_rating(rating),fare(fare),discount(discount)
		{
		}
		
		void set_RideID(string RideID){this->RideID = RideID;}
		string get_RideID(){return RideID;}
		
		void set_PassengerID(string PassengerID){this->PassengerID = PassengerID;}
		string get_PassengerID(){return PassengerID;}
		
		void set_DriverID(string DriverID){this->DriverID = DriverID;}
		string get_DriverID(){return DriverID;}
		
		void set_pickup_location(string pickup_location){this->pickup_location = pickup_location;}
		string get_pickup_location(){return pickup_location;}
		
		void set_dropoff_location(string dropoff_location){this->dropoff_location = dropoff_location;}
		string get_dropoff_location(){return dropoff_location;}
		
		void set_user_feedback(string user_feedback){this->user_feedback = user_feedback;}
		string get_user_feedback(){return user_feedback;}
		
		void set_ride_status(string ride_status){this->ride_status = ride_status;}
		string get_ride_status(){return ride_status;}
		
		void set_user_rating(int user_rating){this->user_rating = user_rating;}
		int get_user_rating(){return user_rating;}
		
		void set_fare(float fare){this->fare = fare;}
		float get_fare(){return fare;}
		
		void set_discount(float discount){this->discount = discount;}
		float get_discount(){return discount;}
		
		void set_start_time(int var)	//VAR IS TIME IN SECONDS, WHICH IS CALCULATED WHEN BOOKING RIDE. 										
		{								//IT ADDS 'VAR' NUMBER OF SECONDS AFTER BOOKING TIME AND SETS PICKUP TIME
			start_time = new tm;
			tm *temp;
			booking_time = new tm;
			time_t curr_time;
			time(&curr_time);
			temp = localtime(&curr_time);
			*start_time = *temp;
			start_time->tm_year=2022;
			start_time->tm_mon++;
			*booking_time = *start_time;
			start_time->tm_sec = start_time->tm_sec + var%60;	
			start_time->tm_min = start_time->tm_min + (var/60)%60 + start_time->tm_sec/60;
			start_time->tm_hour = start_time->tm_hour + var/3600 + start_time->tm_min/60;
			start_time->tm_sec %= 60;
			start_time->tm_min %= 60;
		}
		
		tm get_start_time(){ return *start_time; }
		
		void set_end_time(int var)		//Var is total ride time in seconds
		{
			end_time = new tm;
			*end_time = *start_time;
			end_time->tm_sec = start_time->tm_sec + var%60;	
			end_time->tm_min = start_time->tm_min + (var/60)%60 + end_time->tm_sec/60;
			end_time->tm_hour = start_time->tm_hour + var/3600 + end_time->tm_min/60;
			end_time->tm_sec %= 60;
			end_time->tm_min %= 60;
		}
		
		tm get_end_time(){ return *end_time; }
		tm get_booking_time(){ return *booking_time;}
		
		void set_details(string arr[7],int rating, float fare, float discount,tm ST,tm ET,tm BT)
		{
			start_time = new tm;
			end_time = new tm;
			booking_time = new tm;
			RideID=arr[0];
			PassengerID=arr[1];
			DriverID=arr[2];
			pickup_location=arr[3];
			dropoff_location=arr[4];
			user_feedback=arr[5];
			ride_status = arr[6];
			user_rating=rating;
			this->fare=fare;
			this->discount=discount;
			*start_time = ST;
			*end_time = ET;
			*booking_time = BT;
		}
		void set_details(string arr[7],int rating, float fare, float discount)
		{
			RideID=arr[0];
			PassengerID=arr[1];
			DriverID=arr[2];
			pickup_location=arr[3];
			dropoff_location=arr[4];
			user_feedback=arr[5];
			ride_status = arr[6];
			user_rating=rating;
			this->fare=fare;
			this->discount=discount;
		}
		
		void update()
		{
			ofstream output("ride.txt",ios::app);
			output << "\n" << RideID;
			output << "\n" << PassengerID;
			output << "\n" << DriverID;
			output << "\n" << pickup_location;
			output << "\n" << dropoff_location;
			output << "\n" << user_feedback;
			output << "\n" << ride_status;
			output << "\n" << user_rating;
			output << "\n" << fare;
			output << "\n" << discount;
			output << "\n" << start_time->tm_mday << " " << start_time->tm_mon << " " << start_time->tm_year;
			output << "\n" << start_time->tm_hour << " " << start_time->tm_min << " " << start_time->tm_sec;			
			output << "\n" << booking_time->tm_hour << " " << booking_time->tm_min << " " << booking_time->tm_sec;
			output << "\n" << end_time->tm_hour << " " << end_time->tm_min << " " << end_time->tm_sec;
			output.close();
		}
		
		void extract(ifstream &input)
		{
			getline(input,RideID);
			getline(input,PassengerID);
			getline(input,DriverID);
			getline(input,pickup_location);
			getline(input,dropoff_location);
			getline(input,user_feedback);
			getline(input,ride_status);
			input >> user_rating >> fare >> discount >> start_time->tm_mday >>start_time->tm_mon>>start_time->tm_year;
			input >> start_time->tm_hour >> start_time->tm_min >> start_time->tm_sec;
			input >> booking_time->tm_hour >> booking_time->tm_min >> booking_time->tm_sec;
			input >> end_time->tm_hour >> end_time->tm_min >> end_time->tm_sec;
			input.ignore(256,'\n');
		}
		static void displayRideCount()
		{
			string str = "There are ";
			string str2 = " completed rides so far...\n";
			int i=0;
			
			while(str[i]!='\0')
			{
				std::this_thread::sleep_for(50ms);
				cout << str[i];
				i++;
			}
			i=0;
			std::this_thread::sleep_for(50ms);
			cout << rideCount;
			while(str2[i]!='\n')
			{
				std::this_thread::sleep_for(50ms);
				cout << str2[i];
				i++;
			}
			cout << endl;
		}
		
		friend ostream& operator<<(ostream&, ride);
};
int ride::rideCount=0;

class promo
{	
	string code;
	int discount, discount_limit;
	tm *start_time;
	tm *expiry_date;	
	public:
		promo():code("N/A"),discount(0)
		{
			start_time = new tm;
			expiry_date = new tm;
		}
		
		void set_details(string str,int discount, int limit, tm ET)
		{
			code=str;
			this->discount=discount;
			discount_limit = limit;
			set_start_time();
			set_expiry_date(ET.tm_mday, ET.tm_mon);
		}
		void set_details(string str,float discount,float limit,tm ST,tm ET)
		{
			code=str;
			this->discount=discount;
			discount_limit = limit;
			*start_time = ST;
			*expiry_date = ET;
		}
		
		void set_code(string code){this->code=code;}
		string get_code(){return code;}
		
		void set_discount_limit(int discount_limit){this->discount_limit = discount_limit;}
		int get_discount_limit(){return discount_limit;}

		void set_discount(int discount){this->discount=discount;}
		int get_discount(){return discount;}
		
		void set_start_time()
		{
			tm *tempTM;
			time_t curr_time;
			time(&curr_time);
			tempTM = localtime(&curr_time);
			*start_time = *tempTM;
			start_time->tm_mon ++;
			start_time->tm_year = 2022;
//			delete(tempTM);
		}
		void set_expiry_date(int day, int month)
		{	
			expiry_date->tm_mon = month;
			expiry_date->tm_mday = day;
			expiry_date->tm_year = 2022;
		}	
		tm get_expiry_date(){return *expiry_date;}
		
		void extract(ifstream &input)
		{
			getline(input,code);
			input >> discount >> discount_limit;
			input >> start_time->tm_mday >> start_time->tm_mon >> start_time->tm_year;
			input >> expiry_date->tm_mday >> expiry_date->tm_mon >> expiry_date->tm_year;
			input.ignore();			
		}
		
		void update()
		{
			ofstream output("promo.txt",ios::app);
			output << "\n" << code;
			output << "\n" << discount;
			output << "\n" << discount_limit;
			output << "\n" << start_time->tm_mday << " " << start_time->tm_mon << " " << start_time->tm_year;
			output << "\n" << expiry_date->tm_mday << " " << expiry_date->tm_mon << " " << expiry_date->tm_year;	
			output.close();		
		}
		
		friend ostream& operator<<(ostream&, promo);
};

								/* OPERATOR OVERLOADED FUNCTIONS */
ostream& operator<<(ostream& o, const passenger UOB)
{
	o << "Full Name: " << UOB.full_name << endl;
	o << "CNIC: " << UOB.cnic << endl;
	o << "Age: " << UOB.age << endl;
	o << "Area: " << UOB.area << endl;
	o << "Phone Number: " << UOB.phone_num << endl;
	o << "Preferences: " << UOB.preferences << endl;
	o << "User ID: " << UOB.id << endl;
	o << "Balance: " << UOB.balance << endl;
	o << "Rating: " << UOB.rating << endl;
	o << "Points: " << UOB.points << endl;
	o << "Total Rides: " << UOB.total_rides << endl;
	return o;
}

ostream& operator<<(ostream& o, const driver DOB)
{
	o << "\tDRIVER'S DETAIL:" << endl << endl;
	o << "Full Name: " << DOB.full_name << endl;
	o << "CNIC: " << DOB.cnic << endl;
	o << "Phone Number " << DOB.phone_num << endl;
	o << "ID:  " << DOB.id << endl;
	o << "Balance: " << DOB.balance << endl;
	o << "Rating : " << DOB.rating << endl;
	o << "Points: " << DOB.points << endl;
	o << "Total Rides: " << DOB.total_rides << endl << endl;
	o << "Starting Time: " << DOB.starting_time.tm_hour << " : " << DOB.starting_time.tm_min << " : " << DOB.starting_time.tm_sec << endl;
	o << "Ending Time: " << DOB.ending_time.tm_hour << " : " << DOB.ending_time.tm_min << " : " << DOB.ending_time.tm_sec << endl;
	o << "\tVAN DETAILS: " << endl << endl;
	o << "Ride Type: " << DOB.V.ride_type << endl;
	o << "Ride Name: " << DOB.V.ride_name << endl;
	o << "Ride Colour: " << DOB.V.ride_color << endl;
	o << "Ride Registration Number: " << DOB.V.ride_regNumber << endl;
	o << "Number Of Seats: " << DOB.V.numOfSeats << endl;
	o << "Number Of Passengers: " << DOB.V.numOfPassengers << endl;
	return o;
}

ostream& operator<<(ostream& o, const ride ROB)
{
	o << "Ride ID: " << ROB.RideID << endl;
	o << "Passenger ID: " << ROB.PassengerID << endl;
	o << "Driver ID: " << ROB.DriverID << endl;
	o << "Pickup Location: " << ROB.pickup_location << endl;
	o << "Drop-off Location: " << ROB.dropoff_location << endl;
	o << "Ride Rating by User: " << ROB.user_rating << endl;
	o << "Ride Status: " << ROB.ride_status << endl;
	o << "Ride Fare: " << ROB.fare << endl;
	o << "Ride Discount: " << ROB.discount << endl;
	o << "Date: " << ROB.start_time->tm_mday << " / " << ROB.start_time->tm_mon << " / " << ROB.start_time->tm_year << endl;
	o << "Pickup Time: " << ROB.start_time->tm_hour << ":" << ROB.start_time->tm_min << ":" << ROB.start_time->tm_sec <<endl;
	o << "Booking Time: " << ROB.booking_time->tm_hour << ":" << ROB.booking_time->tm_min << ":" << ROB.booking_time->tm_sec << endl;
	o << "Dropoff Time: " << ROB.end_time->tm_hour << ":" << ROB.end_time->tm_min << ":" << ROB.end_time->tm_sec << endl;
	return o;
}

ostream& operator<<(ostream& o, const promo PPOB)
{
	o << "Promo Code: " << PPOB.code << endl;
	o << "Promo Discount %: " << PPOB.discount << endl;
	o << "Promo Discount Limit: " << PPOB.discount_limit << endl;
	o << "Starting Date: " << PPOB.start_time->tm_mday << "/" << PPOB.start_time->tm_mon << "/" << PPOB.start_time->tm_year << endl;
	o << "Expiry Date: " << PPOB.expiry_date->tm_mday << "/" << PPOB.expiry_date->tm_mon << "/" << PPOB.expiry_date->tm_year << endl;
	return o;
}

					/* VERIFICATIONAL FUNCTIONS */

void checkIntInput(istream &i, int &num)	//TAKES THE ISTREAM OBJECT AS PARAMETER WHERE VARIABLE WAS SUPPOSED TO BE STORED THROUGH
{											//WE CHECK WHETHER THE OBJ SUCCESFULLY TOOK INPUT OR NOT, OTHERWISE IT WILL TAKE INPUT AGAIN.
	while(1)								//AVOIDS THE PROGRAM TO RUN IN A NEVER-ENDING LOOP
	{
		if(i.fail())
		{
			i.clear();
			i.ignore(numeric_limits<streamsize>::max(),'\n');
			cout<<"You have entered wrong input!"<<endl;
			i>>num;
		}
		if(!i.fail())
			break;
	}
}
bool vcheckChar(string str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i]>'9')
		{
			return 0;
		}
	}
	return 1;
}

bool vcheckNum(string str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			return 0;
		}
	}
	return 1;
}

					/* LOGICAL FUNCTIONS */

bool compareDateTime(tm start_time, tm curr_date)
{
	if (start_time.tm_mon == curr_date.tm_mon)
	{
		if(start_time.tm_mday < curr_date.tm_mday)
			return 0;
		else
			return 1;	
	}
	else if (start_time.tm_mon < curr_date.tm_mon)
		return 0;
	else
		return 1;
}

double calculateDistance(int p1, int p2)
{
	int i;
	double distance[6] = { 11.5, 21.4, 5, 13.5, 29.5, 9.3 };
	double x = 0;
	if (p2 > p1)
	{
		for (i = p1 - 1; i < p2 - 1; i++)
		{
			x += distance[i];
		}
	}
	else if (p2 <= p1)
	{
		for (i = p1 - 1; i < 6; i++)
		{
			x += distance[i];
		}
		for (i = 0; i < p2 - 1; i++)
		{
			x += distance[i];
		}
	}
	return x;
}

int calculateTimeDiff(tm curr_tm, tm end_tm)
{
	int num1, num2;
	num1 = curr_tm.tm_sec + curr_tm.tm_min*60 +curr_tm.tm_hour*3600;
	num2 = end_tm.tm_sec + end_tm.tm_min*60 + end_tm.tm_hour*3600;
	return num2-num1;
}

					/* ID GENERATION CODES */
					
string generateID(ride R[100])
{
	string str="R0000";
	char ch;
	int flag=1;
	srand(time(NULL));
	while (flag != 0)
	{
		flag = 0;
		for (int j = 1; j < 5; j++)
		{
			ch = rand() % 10 + 48;
			str[j] = ch;
		}
		for (int i = 0; i < 5; i++)
		{
			if (str == R[i].get_RideID())
			{
				flag = 1;
			}
		}
	}
	return str;
}

string generateID(driver D[10])
{
	string str;
	str = "D0000";
	char ch;
	int flag = 1;
	srand(time(NULL));
	while (flag != 0)
	{
		flag = 0;
		for (int j = 1; j < 5; j++)
		{
			ch = rand() % 10 + 48;
			str[j] = ch;
		}
		for (int i = 0; i < 5; i++)
		{
			if (str == D[i].get_id())
			{
				flag = 1;
			}
		}
	}
	return str;
}

string generateID(passenger P[10])
{
	string str;
	str = "U0000";
	char ch;
	int flag = 1;
	srand(time(NULL));
	while (flag != 0)
	{
		flag = 0;
		for (int j = 1; j < 5; j++)
		{
			ch = rand() % 10 + 48;
			str[j] = ch;
		}
		for (int i = 0; i < 5; i++)
		{
			if (str == P[i].get_id())
			{
				flag = 1;
			}
		}
	}
	return str;
}

					/* ADMIN MENU FUNCTIONS */
void refresh_curr_locations(driver*);
					
void displayAllRides(string admin_area, passenger P[50], driver D[20], ride R[100])
{
	refresh_curr_locations(D);
	for (int i=0; R[i].get_RideID()!="N/A"; i++)
	{
		for(int j=0; P[j].get_id()!="N/A";j++)
		{
			if (R[i].get_PassengerID() == P[j].get_id() && R[i].get_ride_status()=="Booked")
			{
				time_t curr_time;
				tm * curr_tm;
				time(&curr_time);
				curr_tm = localtime(&curr_time);
				if (calculateTimeDiff(*curr_tm,R[i].get_start_time())<0)
				{
					P[j].set_in_ride(1);
					R[i].set_ride_status("In Progress");
				}
			}
			else if (R[i].get_PassengerID()==P[j].get_id() && R[i].get_ride_status()=="In Progress")
			{
				time_t curr_time;
				tm * curr_tm;
				time(&curr_time);
				curr_tm = localtime(&curr_time);
				if (calculateTimeDiff(*curr_tm,R[i].get_end_time())<0)
				{
					P[j].set_in_ride(0);
					R[i].set_ride_status("Incomplete");
				}
			}
		}
	}
	
	ride temp[50];
	int ans=0,j=0,k=0,flag=0,flagB=0,flagIP=0,flagInc=0,flagComp=0,flagCanc=0;
	for (int i=0; R[i].get_RideID()!="N/A"; i++)
	{
		if (admin_area == R[i].get_pickup_location() && R[i].get_ride_status() == "Booked")
		{
			flag = 1;
			temp[j]=R[i];
			j++;
		}
	}
	for (int i=0; R[i].get_RideID()!="N/A"; i++)
	{
		if (admin_area == R[i].get_pickup_location() && R[i].get_ride_status() == "In Progress")
		{
			flag = 1;
			temp[j]=R[i];
			j++;
		}
	}
	for (int i=0; R[i].get_RideID()!="N/A"; i++)
	{
		if (admin_area == R[i].get_pickup_location() && R[i].get_ride_status() == "Incomplete")
		{
			flag = 1;
			temp[j]=R[i];
			j++;
		}
	}
	for (int i=0; R[i].get_RideID()!="N/A"; i++)
	{
		if (admin_area == R[i].get_pickup_location() && R[i].get_ride_status() == "Complete")
		{
			flag = 1;
			temp[j]=R[i];
			j++;
		}
	}
	for (int i=0; R[i].get_RideID()!="N/A"; i++)
	{
		if (admin_area == R[i].get_pickup_location() && R[i].get_ride_status() == "Cancelled")
		{
			flag = 1;
			temp[j]=R[i];
			j++;
		}
	}
	if (flag == 0)
	{
		cout << "There haven't been any rides registered in your area yet.";
	}
	else
	{
		for(int i=0; i<j;i++)
		{
			if(temp[i].get_ride_status()=="Booked")
			{
				flagB=1;
			}
			else if(temp[i].get_ride_status()=="In Progress")
			{
				flagIP=1;
			}
			else if(temp[i].get_ride_status()=="Incomplete")
			{
				flagInc=1;
			}
			else if(temp[i].get_ride_status()=="Complete")
			{
				flagComp=1;
			}
			else if(temp[i].get_ride_status()=="Cancelled")
			{
				flagCanc=1;
			}
		}
		if (flagB==1)
		{
			tm T;
			cout << "\t\t\tBOOKED RIDES\n";
			cout << "\t\t\t------------\n\n";
//			cout << "  Ride ID\tDriver ID  Pickup Location Dropoff Location Fare\tDate" << endl;
			cout << "  Ride ID\tDriver ID\t"<< setw(20) << left << "Pickup Location" << setw(20) << left << "Dropoff Location" << setw(6) << left << "Fare\tDate" << endl;			
			for (int i=0; temp[i].get_RideID()!="N/A"; i++)
			{
				if(temp[i].get_ride_status()=="Booked")
				{
					T=temp[i].get_start_time();
//					cout << k+1 << ". "<< temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t" << temp[i].get_pickup_location() << "\t" << temp[i].get_dropoff_location() << " " << temp[i].get_fare() << "\t" << T.tm_mday << "/" << T.tm_mon<< "/" << T.tm_year << endl;
					cout << k+1 << ". "<< temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t\t" << setw(20) << left << temp[i].get_pickup_location() << setw(20) << left << temp[i].get_dropoff_location() << setw(6) << left << temp[i].get_fare() << "\t" << T.tm_mday << "/" << T.tm_mon<< "/" << T.tm_year << endl;
					k++;
				}
			}
		}
		if (flagIP==1)
		{
			tm T;
			cout << "\n\n\t\t\tRIDES IN PROGRESS\n";
			cout << "\t\t\t-----------------\n\n";
			cout << "  Ride ID\tDriver ID\t"<< setw(20) << left << "Pickup Location" << setw(20) << left << "Dropoff Location" << setw(6) << left << "Fare\tDate" << endl;			
//			cout << "  Ride ID\tDriver ID  Pickup Location Dropoff Location Fare\tDate" << endl;
			for (int i=0; temp[i].get_RideID()!="N/A"; i++)
			{
				if(temp[i].get_ride_status()=="In Progress")
				{
					T=temp[i].get_start_time();
//					cout << k+1 << ". "<< temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t" << temp[i].get_pickup_location() << "\t" << temp[i].get_dropoff_location() << " " << temp[i].get_fare() << "\t" << T.tm_mday << "/" << T.tm_mon<< "/" << T.tm_year << endl;
					cout << k+1 << ". "<< temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t" << setw(20) << left << temp[i].get_pickup_location() << setw(20) << left << temp[i].get_dropoff_location() << "\t" << setw(6) << left << temp[i].get_fare() << "\t" << setw(20) << left << T.tm_mday << "/" << T.tm_mon<< "/" << T.tm_year << endl;
					k++;
				}
			}
		}
		if (flagInc==1)
		{
			tm T;
			cout << "\n\n\t\t\tINCOMPLETE RIDES\n";
			cout << "\t\t\t ----------------\n\n";
//			cout << "  Ride ID\tDriver ID  Pickup Location Dropoff Location Fare\tDate" << endl;
			cout << "  Ride ID\tDriver ID\t"<< setw(20) << left << "Pickup Location" << setw(20) << left << "Dropoff Location" << setw(6) << left << "Fare\tDate" << endl;			
			for (int i=0; temp[i].get_RideID()!="N/A"; i++)
			{
				if(temp[i].get_ride_status()=="Incomplete")
				{
					T=temp[i].get_start_time();
//					cout << k+1 << ". "<< temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t" << temp[i].get_pickup_location() << "\t" << temp[i].get_dropoff_location() << " " << temp[i].get_fare() << "\t" << T.tm_mday << "/" << T.tm_mon<< "/" << T.tm_year << endl;
					cout << k+1 << ". "<< temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t\t" << setw(20) << left << temp[i].get_pickup_location() << setw(20) << left << temp[i].get_dropoff_location() << setw(6) << left << temp[i].get_fare() << "\t" << T.tm_mday << "/" << T.tm_mon<< "/" << T.tm_year << endl;
					k++;
				}
			}
		}
		if (flagComp==1)
		{
			tm T;
			cout << "\n\n\t\t\tCOMPLETED RIDES\n";
			cout << "\t\t\t---------------\n\n";
//			cout << "  Ride ID\tDriver ID  Pickup Location Dropoff Location Fare\tDate" << endl;
			cout << "  Ride ID\tDriver ID\t"<< setw(20) << left << "Pickup Location" << setw(20) << left << "Dropoff Location" << setw(6) << left << "Fare\tDate" << endl;			
			for (int i=0; temp[i].get_RideID()!="N/A"; i++)
			{
				if(temp[i].get_ride_status()=="Complete")
				{
					T=temp[i].get_start_time();
//					cout << k+1 << ". "<< temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t" << temp[i].get_pickup_location() << "\t" << temp[i].get_dropoff_location() << " " << temp[i].get_fare() << "\t" << T.tm_mday << "/" << T.tm_mon<< "/" << T.tm_year << endl;
					cout << k+1 << ". "<< temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t\t" << setw(20) << left << temp[i].get_pickup_location() << setw(20) << left << temp[i].get_dropoff_location() << setw(6) << left << temp[i].get_fare() << "\t" << T.tm_mday << "/" << T.tm_mon<< "/" << T.tm_year << endl;
					k++;
				}
			}
		}
		if (flagCanc==1)
		{
			tm T;
			cout << "\n\n\t\t\tCANCELLED RIDES\n";
			cout << "\t\t\t---------------\n\n";
			cout << "  Ride ID\tDriver ID\t"<< setw(20) << left << "Pickup Location" << setw(20) << left << "Dropoff Location" << setw(6) << left << "Fare\tDate" << endl;			
			for (int i=0; temp[i].get_RideID()!="N/A"; i++)
			{
				if(temp[i].get_ride_status()=="Cancelled")
				{
					T=temp[i].get_start_time();
					cout << k+1 << ". "<< temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t\t" << setw(20) << left << temp[i].get_pickup_location() << setw(20) << left << temp[i].get_dropoff_location() << setw(6) << left << temp[i].get_fare() << "\t" << T.tm_mday << "/" << T.tm_mon<< "/" << T.tm_year << endl;
					k++;
				}
			}
		}
		while(ans<1 || ans>k)
		{
			cout << "\n\n\t\tEnter Selection: ";
			cin >> ans;
			checkIntInput(cin,ans);
		}
		system("cls");
		cout << endl << temp[ans-1];
		getch();
//		delete(temp);
	}
//	delete(temp);
}

				
void displayUsers(string str, passenger POB[15]) 
{
	while(1)
	{
		system("cls");
		driver D[10];
		admin A[10];
		passenger temp[15];
		int ans,j=0;
		for (int i=0; POB[i].get_id()!="N/A";i++)
		{
			if (POB[i].get_area()==str)
			{
				temp[j] = POB[i];
				j++;
			}
		}
		cout << "   Name\t\tID\tAge\tArea\tPoints\tRating" << endl;
		for (int i=0; i<j; i++)
		{
			cout << i+1 << ". " << temp[i].get_full_name() << "\t" << temp[i].get_id() << "\t" << temp[i].get_age() << "\t" << temp[i].get_area() << "\t" << temp[i].get_points() << "\t" << temp[i].get_rating() << endl;
		}
		cout << endl<< "Who do you want to search? ";
		cin >> ans;
		checkIntInput(cin,ans);
		if (ans < 1 || ans >j)
		{
			cout << "WRONG SELECTION!";
			getch();
			continue;
		}
		system("cls");
		cout << temp[ans-1];
		cout << endl;
		system("pause");
		break;
	}
}

void removeDriver(string adminArea, driver DOB[20])
{
	driver temp[10];
	int ans,j=0;
	for (int i=0; DOB[i].get_id()!="N/A";i++)
	{
		if(DOB[i].get_starting_route()==adminArea)
		{
			temp[j] = DOB[i];
			j++;
		}
	}
	cout << "   Name\t\t\tID  \tAge  \tPoints\tRating" << endl;
	for (int i = 0; temp[i].get_id()!="N/A"; i++)
	{
		cout << i + 1 << ". " << temp[i].get_full_name() << "\t " << temp[i].get_id() << "\t " << temp[i].get_age() << "\t " << temp[i].get_points() << "\t " << temp[i].get_rating() << endl;
	}
	cout << endl << "Who do you want to remove? ";
	cin >> ans;
	checkIntInput(cin,ans);
	while(1)
	{
		if (ans < 1 || ans >j)
		{
			cout << "WRONG SELECTION!";
			continue;
		}
		else
		{
			system("cls");
			cout << temp[ans - 1];
			driver::driverCount--;
			cout << "\n\n\tThe driver will now be removed from the database." << endl;
			for(int i=0; DOB[i].get_id()!="N/A"; i++)
			{
				if (DOB[i].get_id() == temp[ans - 1].get_id())
				{
					for (int k=i; DOB[k-1].get_id() != "N/A";k++)
					{
						DOB[k]=DOB[k+1];
					}
				}
			}
			system("pause");
			break;
		}
	}
}

void registerDriver(driver D[15]) 
{	
	system("cls");
	cout << "Driver Credentials" << endl;
	bool x;
	int num=0,ans=0,ans2=0,num1=0,flag=0;
	string str1,str2,str3,str4,str5,str6,ID,pass;
	tm ST,ET;
	ET.tm_hour=0;
	while(!x)
	{
		cin.ignore();
		cout << "Enter Driver's full name: ";
		getline(cin,str1);
		x = vcheckNum(str1);
	}
	while(num<5 || num>100)
	{
		cout << "Enter Driver Age: ";
		cin >> num;
		checkIntInput(cin,num);
	}
	x=0;
	while(!x || str2.size()!=13 || flag!=0)
	{
		flag=0;
		cout << "Enter Driver CNIC: ";
		cin >> str2;
		x=vcheckChar(str2);
		for(int i=0; D[i].get_id()!="N/A"; i++)
		{
			if(D[i].get_cnic()==str2)
			{
				flag=1;
				cout << "DRIVER ALREADY REGISTERED WITH THIS CNIC!" << endl;
				break;
			}
		}
	}	
	x=0;
	while(ans <1 || ans > 6)
	{
		cout << "1. North Nazimabad  2. Water Pump" << endl;
		cout << "3. Gulshan Iqbal    4. Johar" << endl;
		cout << "5. Malir Cantt.     6. Lyari Express" << endl;
		cout << "Enter Driver address: ";
		cin >> ans;
		checkIntInput(cin,ans);
	}
	x=0;
	while(!x || str3.size()!=11 || flag!=0)
	{
		flag=0;
		cout << "Enter Driver phone number: ";
		cin >> str3;
		x = vcheckChar(str3);
		for(int i=0; D[i].get_id()!="N/A"; i++)
		{
			if(D[i].get_phone_num()==str2)
			{
				flag=1;
				cout << "DRIVER ALREADY REGISTERED WITH THIS PHONE NUMBER!" << endl;
				break;
			}
		}
	}
	while(1)
	{
		int anst1,anst2;
		cout << "1. 08 : 00 : 00 AM" << endl;
		cout << "2. 12 : 00 : 00 PM" << endl;
		cout << "3. 04 : 00 : 00 PM" << endl;
		cout << "Enter Starting Time: ";
		cin >> anst1;
		checkIntInput(cin,anst1);
		if (anst1 == 1)
		{
			ST.tm_hour = 8;
			ST.tm_min = 0;
			ST.tm_sec = 0;
		}
		else if (anst1 == 2)
		{
			ST.tm_hour = 12;
			ST.tm_min = 0;
			ST.tm_sec = 0;
		}
		else if (anst1 == 3)
		{
			ST.tm_hour = 16;
			ST.tm_min = 0;
			ST.tm_sec = 0;
		}
		else
			continue;

		cout << "1. 12 : 00 : 00 PM" << endl;
		cout << "2. 04 : 00 : 00 PM" << endl;
		cout << "3. 08 : 00 : 00 PM" << endl;
		cout << "Enter Ending Time: ";
		cin >> anst2;
		checkIntInput(cin,anst2);
		if (anst2 == 1)
		{
			ET.tm_hour = 12;
			ET.tm_min = 0;
			ET.tm_sec = 0;
		}
		else if (anst2 == 2)
		{
			ET.tm_hour = 16;
			ET.tm_min = 0;
			ET.tm_sec = 0;
		}
		else if (anst2 == 3)
		{
			ET.tm_hour = 20;
			ET.tm_min = 0;
			ET.tm_sec = 0;
		}
		if (ET.tm_hour <= ST.tm_hour)
		{
			cout << "\tINVALID TIMINGS!" << endl;
			continue;	
		}
		break;	
	}
	cout << "\tDriver's Vehicle Credentials" << endl << endl;
	while(ans2<1 || ans2 >2)
	{
		cout << "1. AC\t2. Non-AC" << endl;
		cout << "Enter Driver Van Type: ";
		cin >> ans2;
		checkIntInput(cin,ans2);
	}
	x=0;
	while(!x)
	{
		cin.ignore();
		cout << "Enter Name Of Vehicle: " << endl;
		getline(cin, str4);
		x = vcheckNum(str4);
	}
	while(str5.size()!=7 || str5[3]!='-' || flag!=0)
	{
		flag=0;
		cout << "Enter Vehicle Registration Number (XXX-000) :" << endl;
		getline(cin, str5);
		for(int i=0; D[i].get_id()!="N/A";i++)
		{
			if (str5 == D[i].get_ride_regNumber())
			{
				flag = 1;
				cout << "\nDRIVER ALREADY REGISTERED WITH THIS VAN";
				break;
			}
		}
	}
	x=0;
	while(!x)
	{
		cout << "Enter Vehicle Colour:" << endl;
		getline(cin, str6);
		x = vcheckNum(str6);
	}
	while(num1 < 1 || num1 >30)
	{
		cout << "Enter Vehicle seats: ";
		cin >> num1;
		checkIntInput(cin,num1);
	}
	ID = generateID(D);
	pass = "ABC123";
	cout << "Driver ID is: " << ID << endl;
	cout << "The password is: " << pass << endl;
	cout << "The Security Question will be about the town he was born in by default, which driver can change by himself later." << endl;
	cout << "The answer would be his starting route by default.." << endl;
	driver::driverCount++;
	cout << "Driver Registered! Sending the details to via number to Mr. " << str1;
	for (int i=0; i<10; i++)
	{
		if (D[i].get_id() == "N/A")
		{
			D[i].set_details(ID,pass,str1,str2,LOCS[ans-1],str3,pref[ans2-1],num,0,0,0,0,str4,str5,str6,num1,0,ST,ET);
			
			D[i].update();
			break;
		}
	}
	getch();
}

void displayDrivers(string str, driver DOB[15]) 
{
	driver temp[10];
	int ans,j=0;
	for (int i=0; DOB[i].get_id()!="N/A";i++)
	{
		if(DOB[i].get_starting_route()==str)
		{
			temp[j] = DOB[i];
			j++;
		}
	}
	while (1)
	{
		system("cls");
		cout << "   Name\t\t\tID  \tAge  \tPoints\tRating" << endl;
		for (int i = 0; temp[i].get_id()!="N/A"; i++)
		{
			cout << i + 1 << ". " << temp[i].get_full_name() << "\t " << temp[i].get_id() << "\t " << temp[i].get_age() << "\t " << temp[i].get_points() << "\t " << temp[i].get_rating() << endl;
		}
		cout << endl << "Who do you want to search? ";
		cin >> ans;
		checkIntInput(cin,ans);
		if (ans < 1 || ans >j)
		{
			cout << "WRONG SELECTION!";
			continue;
		}
		else
		{
			system("cls");
			cout << temp[ans - 1];
	//		getch();
			system("pause");
			break;
	//		exit(1);
		}
	}
}

void addPromo(promo P[20])
{	
	tm *tempTM, TMVar;			
	time_t curr_time;
	time(&curr_time);
	tempTM = localtime(&curr_time);
	TMVar = *tempTM;
	TMVar.tm_mon++;
	string str1;
	int f1,f2;
	int num,i;
	tm ET;
	system("cls");
	cout<<"Enter the name of the promo : "<<endl;
	cin.ignore();
	getline(cin,str1);		
	cout<<"Enter the discount percentage: "<<endl;
	cin>>f1;
	checkIntInput(cin,f1);
	cout << "Enter the discount limit: " << endl;
	cin >> f2;
	checkIntInput(cin,f2);
	bool x=0;
	while(!x || ET.tm_mon > 12 || ET.tm_mday > 31)
	{
		cout<<"Enter the expiry month: "<<endl;
		cin>>ET.tm_mon;
		checkIntInput(cin,ET.tm_mon);
		cout<<"Enter the day: "<<endl;
		cin>>ET.tm_mday;
		checkIntInput(cin,ET.tm_mday);
		x = compareDateTime(ET, TMVar);
	}
	delete(tempTM);
	for (i=0;i<20; i++)
	{
		if (P[i].get_code() == "N/A")
		{
			P[i].set_details(str1,f1,f2,ET);
			break;
		}
	}
	cout << "\tPROMO ADDED TO SYSTEM!" << endl;
	cout << P[i];
}

			/* EXTRACT AND UPDATE FUNCTIONS WHICH CALLS ALL EXTRACT/UPDATE FUNCTIONS OF ALL CLASSES */

void extract(passenger U[15], admin A[15], driver D[15], ride R[100], promo PR[20])
{
	ifstream input("admin.txt");
	for(int i=0;!input.eof();i++)
	{
		A[i].extract(input);
	}
	input.close();
	input.open("user.txt");
	input.ignore(256,'\n');
	for (int i=0; !input.eof();i++)
	{
		U[i].extract(input);
	}
	input.close();
	input.open("driver.txt");
	input.ignore(256,'\n');
	for(int i=0; !input.eof();i++)
	{
		D[i].extract(input);
	}
	input.close();
	input.open("ride.txt");
	input.ignore(256,'\n');
	for(int i=0; !input.eof();i++)
	{
		R[i].extract(input);
	}
	input.close();
	input.open("promo.txt");
	input.ignore(256,'\n');
	for(int i=0; !input.eof();i++)
	{
		PR[i].extract(input);
	}
	input.close();
	input.open("About Us.txt");
	input >> passenger::passengerCount >> driver::driverCount >> admin::adminCount >> ride::rideCount;
	input.close();
}

void update(passenger P[15], admin A[15], driver D[15],ride R[100], promo PR[20])
{
	ofstream out("user.txt",ios::trunc);
	for(int i=0; P[i].get_id()!="N/A";i++)
	{
		P[i].update();
	}
	out.close();
	out.open("ride.txt",ios::trunc);
	for(int i=0; R[i].get_RideID()!="N/A";i++)
	{
		R[i].update();
	}
	out.close();
	out.open("driver.txt",ios::trunc);
	for (int i=0; D[i].get_id()!="N/A";i++)
	{
		D[i].update();
	}
	out.close();
	out.open("promo.txt",ios::trunc);
	for(int i=0;PR[i].get_code()!="N/A"; i++)
	{
		PR[i].update();
	}
	out.close();
	out.open("About Us.txt", ios::trunc);
	out << passenger::passengerCount << endl << driver::driverCount << endl << admin::adminCount << endl << ride::rideCount;
	out.close();
}

					/* USER MENU FUNCTIONS */
					
void refresh_curr_locations(driver D[20])
{
	int i,count=0,y;
	double x,var;
	double distance[6] = { 11.5, 21.4, 5, 13.5, 29.5, 9.3 };
	tm ST, *ET;
	time_t curr_time;
	time(&curr_time);
	for (count =0; D[count].get_id()!="N/A"; count++)
	{
		ST = D[count].get_starting_time();
		ET = localtime(&curr_time);
		x = 45.0*(calculateTimeDiff(ST,*ET))/3600.0;
		x=x/90.2; 		//This was to Calculate how many times the driver has completed his rounds.
		y = x;
		var = x-y;
	//	cout << x-y << endl;		This was to find out how muhc more distance he covered after passing his starting location.
		var*=90.2;
		for (i=0; i<6; i++)
		{
			if(LOCS[i]==D[count].get_starting_route())
			{
				break;
			}
		}
		for (;;i++)
		{
			if(distance[i]>var)
			{
				D[count].set_current_location(LOCS[i]);
				break;	
			}
			i%=6;
			var-=distance[i];
		}
	}
}

void refresh_user_menu(passenger &P, driver D[20], ride R[100])
{
	for (int i=0; R[i].get_RideID()!="N/A"; i++)
	{
		if (R[i].get_PassengerID() == P.get_id() && R[i].get_ride_status()=="Booked")
		{
			time_t curr_time;
			tm * curr_tm;
			time(&curr_time);
			curr_tm = localtime(&curr_time);
			if (calculateTimeDiff(*curr_tm,R[i].get_start_time())<0)
			{
				P.set_in_ride(1);
				R[i].set_ride_status("In Progress");
			}
		}
		else if (R[i].get_PassengerID()==P.get_id() && R[i].get_ride_status()=="In Progress")
		{
			time_t curr_time;
			tm * curr_tm;
			time(&curr_time);
			curr_tm = localtime(&curr_time);
			if (calculateTimeDiff(*curr_tm,R[i].get_end_time())<0)
			{
				P.set_in_ride(0);
				R[i].set_ride_status("Incomplete");
			}
		}
		if (R[i].get_PassengerID()==P.get_id() && R[i].get_ride_status()=="Incomplete")
		{
			string str;
			int num;
			system("cls");
			cout << "Dear " << P.get_full_name() << endl;
			cout << "The feedback and ride rating for your last ride are missing.\nPlease provide the feedback and rating for the following ride: ";
			cout << R[i];
			cin.ignore();
			cout << endl << "Provide Feedback: ";
			getline(cin,str);
			while(1)
			{
				cout << endl << "Provide Rating (1 - 5): ";
				cin >> num;
				checkIntInput(cin,num);
				if(num>=1 && num<=5)
					break;
			}
			R[i].set_user_feedback(str);
			R[i].set_user_rating(num);
			R[i].set_ride_status("Complete");
			for(int j=0; D[j].get_id()!="N/A";j++)
			{
				if (D[j].get_id()==R[i].get_DriverID())
				{
					float x=0.00;
					ride::rideCount++;
					// Update Rating, Total rides, points, num of passengers, and in ride variable of user, wallet balance of both
					D[j].set_rating( ( (D[j].get_total_rides()*D[j].get_rating()) + num)/( D[j].get_total_rides() + 1) );
					D[j].set_total_rides(D[j].get_total_rides()+1);
					P.set_total_rides(P.get_total_rides()+1);
					P.set_points(P.get_points() + (R[i].get_fare()/10));
					D[j].set_points(D[j].get_points() + (R[i].get_fare()/10));
					D[j].set_balance(D[j].get_balance() + R[i].get_fare() - R[j].get_discount());
					x = P.get_balance() - R[i].get_fare() + R[i].get_discount();
					P.set_balance(x);
					D[j].set_numOfPassengers(D[j].get_numOfPassengers()-1);
					cout << endl << R[i];
					getch();
				}
			}
		}
	}
}

void editBio(passenger &UOB) 
{
	string str;
	char ch;
	int i = 0, flag, user, ans=1;
	system("cls");
	cout << "Enter your password to edit bio: ";
	ch=getch();
	while(ch!=13)
	{
		str.push_back(ch);
		cout<<'*';
		ch=getch();
	}
	if (str == UOB.get_password())
	{
		while(ans!=0)
		{
			cout << "\n\nEnter 1 to change Full Name\nEnter 2 to change Address\nEnter 3 to change Age\nEnter 4 to change Phone Number\nPress 5 to change password\nPress 6 to change security question.\nEnter 0 to Exit" << endl;
			cin >> ans;
			if (ans == 1)
			{
				bool x=0;
				cout << endl << "Current Name: " << UOB.get_full_name();
					while(!x)
					{
						cout << "\nEnter New Full Name: ";
						cin.ignore();
						getline(cin,str);
						x = vcheckNum(str);
					}
					UOB.set_full_name(str);
					cout << "Full Name changed!";
					cout << "New Name: " << UOB.get_full_name();
			}
			else if (ans == 2)
			{
				int ans1=1;
				cout << endl << "Current Address: " << UOB.get_area();
				cout << "\n1. North Nazimabad  2. Water Pump" << endl;
				cout << "3. Gulshan Iqbal    4. Johar" << endl;
				cout << "5. Malir Cantt.     6. Lyari Express" << endl;
				while(ans1 <1 || ans1 > 6)
				{
					cout << "\nEnter your new address: ";
					cin >> ans1;
				}
				UOB.set_area(LOCS[ans1-1]);
				cout << "\nAddress Changed!";
			}
			else if (ans == 3)
			{
				int num;
				cout << endl << "Current Age: " << UOB.get_age();
				cout << endl << "\nEnter New Age: ";
				cin >> num;
				UOB.set_age(num);
				cout << "\nAge Changed!";
			}
			else if (ans == 4)
			{
				string str;
				bool x=0;
				cout << endl << "Current Phone Number: " << UOB.get_phone_num();
				while(!x || str.size()!=11)
				{
					cout << endl << "\nEnter new phone number: ";
					cin >> str;
					x=vcheckChar(str);
				}
				cout << "\nPhone Number changed!";
			}
			else if (ans == 5)
			{
				string str=UOB.get_password(),str2;
				int i=1;
				cout << endl << "Current Password: " << str[0];
				while(i < str.size()-1)
				{
					cout << "*";
					i++;
				}
				cout << str[i];
				i=0;
				while(i<3)
				{
					string str1;
					cout << "\nEnter New Password: ";
					ch=getch();
					while(ch!=13)
					{
						str1.push_back(ch);
						cout<<'*';
						ch=getch();
					}
					cout << "\nConfirm Password: ";
					ch=getch();
					while(ch!=13)
					{
						str2.push_back(ch);
						cout<<'*';
						ch=getch();
					}
					if (str1 == str2)
					{
						cout << "\nPassword Changed!";
						UOB.set_password(str);
						break;
					}
					i++;
					cout << "\tTRY AGAIN! (Attempts remaining: " << 3-i << ")";
				}
			}
			else if (ans == 6)
			{
				string str;
				int num2=0;
				cout << "\nCurrent Security Question: " << endl << "\t" << QUE[UOB.get_queNum()];
				cout << "\n\nCurrent Security Answer: " << UOB.get_queAns() << endl;
				cout << "\n\t\tTHE SECURITY QUESTIONS:" << endl;
				for(int j=0;j<5;j++)
				{
					cout << QUE[j] << endl;
				}
				while(num2<1 || num2>5)
				{
					cout << "\nEnter your security question number: ";
					cin >> num2;
				}
				num2--;
				cout << "Your Security Question is: " << endl;
				cout << "\t" << QUE[num2];
				cout << "\nEnter Security Answer: ";
				cin.ignore();
				getline(cin,str); 
				UOB.set_queNum(num2);
				UOB.set_queAns(str);
			}
		}
	}
	else
	{
		cout << "\tWRONG PASSWORD!";
	}
	getch();
}

void trackRide(passenger &UOB, driver D[20], ride R[50])
{
	int i,j,flag=0;
	system("cls");
	for (i=0;R[i].get_RideID()!="N/A";i++)
	{
		if(R[i].get_PassengerID()==UOB.get_id()&&(R[i].get_ride_status()=="Booked" || R[i].get_ride_status()=="In Progress"))
		{
			flag=1;
			for(j=0;D[j].get_id()!="N/A";j++)
			{
				if (D[j].get_id() == R[i].get_DriverID())
					break;
			}
			break;
		}
	}
	if (flag==0)
	{
		cout << "You haven't booked a ride.";
	}
	else
	{
		tm *CT;
		CT = new tm;
		time_t curr_time;
		tm * curr_tm;
		time(&curr_time);
		CT = localtime(&curr_time);
		int timeVar1,timeVar2;
		cout << "Your driver for today, " <<D[j].get_full_name() << " , has covered....." << endl;
		if(R[i].get_ride_status()=="Booked")
		{
			timeVar1 = calculateTimeDiff(R[i].get_booking_time(),*CT);
			timeVar2 = calculateTimeDiff(R[i].get_booking_time(),R[i].get_start_time());
		}
		else
		{
			timeVar1 = calculateTimeDiff(R[i].get_start_time(),*CT);
			timeVar2 = calculateTimeDiff(R[i].get_start_time(),R[i].get_end_time());
		}
		int x;
		x = timeVar2/50;
		timeVar1/=x;
		timeVar2/=x;
	    auto progress = 0;
	    while (progress < 50 && timeVar1 >0) 
		{
	        std::this_thread::sleep_for(200ms);
	        progress += 1;
	        std::cout << '\r' << '[' << std::string(progress, '#') << std::string(50- progress ,' ')<< ']' << "\t" << progress *2<< "%" << std::flush;
	   		timeVar1--;
	    }
	    cout << "\n...this much progress.";
	    cout << endl << "\tThese are the ride details: \n" << endl;
	    cout << R[i];
		cout << "\n\nThese are the driver's details! " << endl;
		cout << "Driver Name: " << D[j].get_full_name() << endl;
		cout << "Driver's Phone Number: " << D[j].get_phone_num() << endl;
		cout << "Van's Name: " << D[j].get_ride_name() << endl;
		cout << "Van's Registration Number: " << D[j].get_ride_regNumber() << endl;
		cout << "Van Color: " << D[j].get_ride_color() << endl;
		cout << "\n\t\tENJOY YOUR RIDE BAMMER! ";
	}
}

void aboutUs()
{
	int i=0;
	cout << "\n\t\t";
	while(i<56)
	{
		cout << "-";
		i++;
	}
	cout << "\n\t\t\t";
	admin::displayAdminCount();
	cout << "\n\t\t\t";
	driver::displayDriverCount();
	cout << "\n\t\t\t";
	passenger::displayUserCount();
	cout << "\n\t\t\t";
	ride::displayRideCount();
	string str="SEMESTER PROJECT (BAM)";
	cout << "\n\t\t\t\t";
	for(int i=0;str[i]!='\0';i++)
	{
		std::this_thread::sleep_for(50ms);
		cout << str[i];
	}	
	str = "Made by: ";
	cout << "\n\t\t\t";
	for(int i=0;str[i]!='\0';i++)
	{
		std::this_thread::sleep_for(50ms);
		cout << str[i];
	}	
	cout << "\n\t\t\t\t";
	str = "21K-4864 Bilal Ahmed";
	for(int i=0;str[i]!='\0';i++)
	{
		std::this_thread::sleep_for(50ms);
		cout << str[i];
	}
	str = "21K-3192 Muhammad Shahid";
	cout << "\n\t\t\t\t";
	for(int i=0;str[i]!='\0';i++)
	{
		std::this_thread::sleep_for(50ms);
		cout << str[i];
	}
	str = "21K-3340 Atif Ali";
	cout << "\n\t\t\t\t";
	for(int i=0;str[i]!='\0';i++)
	{
		std::this_thread::sleep_for(50ms);
		cout << str[i];
	}
	i=0;
	cout << "\n\t\t";
	while(i<56)
	{
		cout << "-";
		i++;
	}	
}

void displayRideHistory(passenger &UOB, ride R[100])
{
	system("cls");
	int j=0,flag=0,ans=0;
	ride temp[50]; 
	tm T;
	cout << "\t\tRATE LIST" << endl;
	cout << "\t\t---------" << endl;
	cout << "\n\tBase Fare:            Rs. 50" << endl;
	cout << "\n\tCancellation Charges: Rs. 20" << endl;
	cout << "\n\tFare per km:          Rs. 8.5" << endl << endl;
	for (int i=0; R[i].get_RideID()!="N/A"; i++)
	{
		if (R[i].get_PassengerID()==UOB.get_id())
		{
			flag = 1;
			temp[j]=R[i];
			j++;
		}
	}
	if (flag == 0)
	{
		cout << "You haven't booked any rides. Please feel free to book-a-BAM!";
	}
	else
	{
		cout << "  Ride ID\tDriver ID\t"<< setw(20) << left << "Pickup Location" << setw(20) << left << "Dropoff Location" << setw(6) << left << "Fare\tDate" << endl;			
		for (int i=0; i<j;i++)
		{
			T=temp[i].get_start_time();
			cout << i+1 << ". "<< temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t\t" << setw(20) << left << temp[i].get_pickup_location() << setw(20) << left << temp[i].get_dropoff_location() << setw(6) << left << temp[i].get_fare() << "\t" << T.tm_mday << "/" << T.tm_mon<< "/" << T.tm_year << endl;
		}
		while(ans<1 || ans>j)
		{	
			cout << "\nFor which ride would you like to see details of? ";
			cin >> ans;
			checkIntInput(cin,ans);
		}
		cout << "\n\tThe ride details are as follows: \n";
		cout << temp[ans-1];
	}
}

void bookRide(passenger &P, driver drivers[20], ride R[100], promo PR[20])
{
	int y,k,timeVar,ans,ans1=0,ans2=0,var,ans3=2,j=0,flag=0, seats=0, flagForPromo=0, check=0, flagCheck=0;
	tm ST, *curr_tm;
	time_t curr_time;
	time(&curr_time);
	float fare;
	float x,tempVar,distance[6] = { 11.5, 21.4, 5, 13.5, 29.5, 9.3 };
	driver temp[20];
	string str,str1;
	system("cls");
	for (int i=0; R[i].get_RideID()!="N/A";i++)
	{
		if(R[i].get_PassengerID()==P.get_id() && R[i].get_ride_status()=="Booked")
			flagCheck=1;		//TO CHECK IF ALREADY BOOKED OR NOT
	}
	if (flagCheck==1)
		cout << "YOU HAVE ALREADY BOOKED RIDE.";
	else
	{
		while(ans1<1 || ans1>6)
		{
			cout << "1. North Nazimabad  2. Water Pump" << endl;
			cout << "3. Gulshan Iqbal    4. Johar" << endl;
			cout << "5. Malir Cantt.     6. Lyari Express" << endl;
			cout << "Enter start location: ";
			cin >> ans1;
			checkIntInput(cin,ans1);
		}
		var=ans1;
		ans1-=2;
		if(ans1<0)
		{
			ans1=6+ans1;
		}
		while(ans2<1 || ans2>6)
		{
			cout << "\n1. North Nazimabad  2. Water Pump" << endl;
			cout << "3. Gulshan Iqbal    4. Johar" << endl;
			cout << "5. Malir Cantt.     6. Lyari Express" << endl;	
			cout << "Enter dropoff location: ";
			cin >> ans2;
			checkIntInput(cin,ans2);
		}
		while(ans3!=1 && ans3!=0)
		{
			cout << "Would you like to use your current preference? (" << P.get_preferences() << " , 1 for Yes and 0 for No): ";
			cin >> ans3;
			checkIntInput(cin,ans3);
			if (ans3==1)
			{
				str = P.get_preferences();
			}
			else if (ans3==0)
			{
				cout << "\n1. AC\t2. Non-AC\t3. Any.";
				cout << "\nEnter preference: ";
				cin >> ans3;
				checkIntInput(cin,ans3);
				str = pref[ans3-1];
				break;
			}
		}
		while(seats<1 || seats>8)
		{
			cout << "Enter the number of passengers (including you): ";
			cin >> seats;
			checkIntInput(cin,seats);
			if (seats<1 || seats>8)
				cout << "Please select seats from 1-8! " << endl;
			else
				break;	
		}
		
		refresh_curr_locations(drivers);
		curr_tm = localtime(&curr_time);
		cout << "  " << setw(20) << left << "Driver's Name" << "Type\tRating\tCurrent Location" << endl;
		for (int i=0; drivers[i].get_id()!="N/A"; i++)
		{
			if (drivers[i].get_current_location() == LOCS[ans1] && (drivers[i].get_ride_type() == str || str == "Any") && drivers[i].get_numOfPassengers() < drivers[i].get_numOfSeats()  && calculateTimeDiff(*curr_tm,drivers[i].get_ending_time()) > 0  && ((drivers[i].get_numOfSeats()-drivers[i].get_numOfPassengers()) >= seats))
			{
				//Dynamically storing these drivers in an array
				temp[j]=drivers[i];
				flag = 1;
				cout << j+1 << " " << setw(20) << left << drivers[i].get_full_name() << drivers[i].get_ride_type() << "\t" << drivers[i].get_rating() << "\t" << drivers[i].get_current_location() << endl;
				j++;
			}
		}
		if (flag == 0)
		{
			cout << "Sorry. There are no drivers available that suit your need.";
			getch();
		}
		else if (flag == 1)
		{
			while(ans<0 || ans >j)
			{
				cout << "Enter selection: ";
				cin >> ans;
				checkIntInput(cin,ans);
			}
			int promo_ans=2;
			while(promo_ans<0 || promo_ans >1)
			{
				cout << "Do you have a promo code? (1 for Yes, 0 for No)";
				cin >> promo_ans;
				checkIntInput(cin,promo_ans);
			}
			if (promo_ans == 1)
			{
				string code;
				cout << "Enter promo code: ";
				cin >> code;
				for (check=0; PR[check].get_code()!="N/A"; check++)
				{
					if (code == PR[check].get_code())
					{
						tm *CurrTm, tempTMVAR;
						time_t curr_time;
						time(&curr_time);
						CurrTm = localtime(&curr_time);
						tempTMVAR = *CurrTm;
//						delete(CurrTm);
						bool x;
						x = compareDateTime(PR[check].get_expiry_date(),tempTMVAR);
						if (x==1)
						{
							flagForPromo=1;
							cout << "\nPROMO CODE ADDED!" << endl;
							break;
						}
						else
							cout << "\nPromo has expired. You will proceed without a promo. \nIn order to cancel your ride, please go to 'Cancel Ride' in user menu." << endl;
					}
				}
			}
			tm ET, *tmVar;
			time_t curr_time;
			time(&curr_time);
			tmVar = localtime(&curr_time);
			ET = *tmVar;
//			delete(tmVar);
			int i;
			for (i=0; i<100 ;i++)
			{
				if (R[i].get_RideID()=="N/A")
				{
					float discount=0;
					str1 = generateID(R);
					string arr[7]={str1,P.get_id(),temp[ans-1].get_id(),LOCS[var-1],LOCS[ans2-1],"N/A","Booked"};
					fare = calculateDistance(ans1+2,ans2)*seats*8.5+50;
					if (flagForPromo == 1)
					{
						discount = (fare*PR[check].get_discount())/100;
						if (discount >= PR[check].get_discount_limit())
						{
							discount = PR[check].get_discount_limit();
						}
					}
					R[i].set_details(arr,0,fare,discount);
					for(int l=0; drivers[l].get_id()!="N/A";l++)
					{
						if (drivers[l].get_id() == temp[ans-1].get_id())
							drivers[l].set_numOfPassengers( drivers[l].get_numOfPassengers() + seats);
					}
				/* CALCULATION OF DRIVERS ESTIMATED TIME TO ARRIVAL START*/
					ST = temp[ans-1].get_starting_time();
					x = 45.0*(calculateTimeDiff(ST,ET))/3600.0;
					x/=90.2;
					y = x;
					tempVar = x-y;
					tempVar*=90.2;
					for (k=0; k<6; k++)
					{
						if(LOCS[k]==temp[ans-1].get_starting_route())
						{
							break;
						}
					}
					for (;;k++)
					{
						k%=6;
						if(distance[k]>tempVar)
						{
							break;
						}
						tempVar-=distance[k];
						cout << tempVar << endl;
					}
					timeVar = (((distance[k]-tempVar)*3600.0)/45.0);
				/* CALCULATION OF DRIVERS ESTIMATED TIME TO ARRIVAL END*/
					R[i].set_start_time(timeVar);	
					R[i].set_end_time((calculateDistance(ans1+2,ans2)/45)*3600);
					cout << "Ride Confirmed!" << endl;
					break;
				}
			}
			cout << R[i];
		}
	}
}

void signup(passenger P[40])
{
	bool x=0;
	system("cls");
	int num=0,ans=0,ans2=0,num2=0,flag=0;
	string str1,str2,str3,str4,str5,str6;
	while(!x)
	{
		cin.ignore();
		cout << "Enter your full name: ";
		getline(cin,str1);
		x = vcheckNum(str1);
	}
	while(num<5 || num>100)
	{
		cout << "Enter Age: ";
		cin >> num;
	}
	x=0;
	while(!x || str2.size()!=13)
	{
		cout << "Enter your CNIC: ";
		cin >> str2;
		x=vcheckChar(str2);
		for(int i=0; P[i].get_id()!="N/A";i++)
		{
			if(P[i].get_cnic()==str2)
			{
				flag=1;
				cout << "\nUSER ALREADY REGISTERED WITH THIS CNIC!" << endl;
				break;
			}
		}
	}	
	x=0;
	while(ans <1 || ans > 6)
	{
		cout << "1. North Nazimabad  2. Water Pump" << endl;
		cout << "3. Gulshan Iqbal    4. Johar" << endl;
		cout << "5. Malir Cantt.     6. Lyari Express" << endl;
		cout << "Enter your address: ";
		cin >> ans;
		checkIntInput(cin,ans);
	}
	x=0;
	while(!x || str3.size()!=11 || flag!=0)
	{
		flag=0;
		cout << "Enter your phone number: ";
		cin >> str3;
		x = vcheckChar(str3);
		for(int i=0; P[i].get_id()!="N/A";i++)
		{
			if(P[i].get_phone_num()==str3)
			{
				flag=1;
				cout << "\nUSER ALREADY REGISTERED WITH THIS PHONE NUMBER!" << endl;
				break;
			}
		}
	}
	while(ans2<1 || ans2 >3)
	{
		cout << "1. AC\t2. Non-AC\t3. Any" << endl;
		cout << "Enter your preference: ";
		cin >> ans2;
		checkIntInput(cin,ans2);
	}
	str4 = generateID(P);
	cout << "Your User ID will be: " << str4 << endl;
	while(1)
	{
		cout << "Enter Password: ";
		cin >> str5;
		char ch;
		string str7;
		ch=getch();
		while(ch!=13)
		{
			str2.push_back(ch);
			cout<<'*';
			ch=getch();
		}
		cout << "Confirm Password: ";
		ch=getch();
		while(ch!=13)
		{
			str7.push_back(ch);
			cout<<'*';
			ch=getch();
		}
		if(str5==str7)
			break;
		else
			cout << "Invalid confirmation. Please try again." << endl;
	}
	cout << "\n\n\tSECURITY QUESTIONS" << endl;
	for(int i=0;i<5;i++)
	{
		cout << QUE[i] << endl;
	}
	while(num2<1 || num2>5)
	{
		cout << "\nEnter your security question number: ";
		cin >> num2;
		checkIntInput(cin,num2);
	}
	num2--;
	cout << "Your Security Question is: " << endl;
	cout << "\t" << QUE[num2];
	cout << "\nEnter Security Answer: ";
	cin.ignore();
	getline(cin,str6); 
	for (int i=0; i<50; i++)		//CHANGE CONDITION!!!!!
	{
		if (P[i].get_id()=="N/A")
		{
			P[i].set_details(str1,str2,LOCS[ans-1],str3,pref[ans2-1],str4,str5,str6,num,num2);
			break;
		}
	}
	passenger::passengerCount++;
//	cout << "Passenger Count = " << passenger::passengerCount;
	cout << "\n\t\tYou have been registered!";
	getch();
}

void cancelRide(passenger &UOB, driver D[20], ride R[100])
{
	int i,j,ans;
	time_t curr_time;
	tm *current_tm;
	time(&curr_time);
	current_tm = localtime(&curr_time);
	system("cls");
	if (UOB.get_in_ride()==1)
	{
		cout << "You're already in ride." << endl;
	}
	else
	{
		for (i=0; R[i].get_PassengerID()!="N/A"; i++)
		{
			if (R[i].get_PassengerID()==UOB.get_id() && R[i].get_ride_status()=="Booked")
			{
				for (j=0; D[j].get_id()!="N/A";j++)
				{
					if (R[i].get_DriverID()==D[j].get_id())
						break;
				}
				cout << "\t\tThis is the ride you will be cancelling: " << endl;
				cout << R[i];
				if (calculateTimeDiff(R[i].get_booking_time(),*current_tm) < 120)
				{
					cout << "\n\nThere will be no charges.\nAre you sure you want to proceed? (1 for Yes, 0 for No)  ";
					cin >> ans;
					checkIntInput(cin,ans);
					if (ans == 0)
						break;
					else
					{
						R[i].set_ride_status("Cancelled");
						R[i].set_fare(0);
						D[j].set_numOfPassengers(D[j].get_numOfPassengers()-1);
						R[i].set_discount(0);
					}
				}
				else
				{
					cout << "\n\nThere will be Rs. 20 deducted from your wallet.\nAre you sure you want to proceed? (1 for Yes, 0 for No)  ";
					cin >> ans;
					if (ans == 0)
						break;
					else
					{
						R[i].set_ride_status("Cancelled");
						R[i].set_fare(20);
						D[j].set_numOfPassengers(D[j].get_numOfPassengers()-1);
						R[i].set_discount(0);
						UOB.set_balance(UOB.get_balance()-20);
					}	
				}
			}
		}	
	}
}

void EditDriverBio(driver &DOB) 
{
	string str;
	char ch;
	int i = 0, flag, user, ans=1;
	cout << "\n\n\t\tEnter your password to edit bio: ";
	ch=getch();
	while(ch!=13)
	{
		str.push_back(ch);
		cout<<'*';
		ch=getch();
	}
	if (str == DOB.get_password())
	{
		while(ans!=0)
		{
			system("cls");
			cout << "\n\nEnter 1 to change Full Name\nEnter 2 to change Address\nEnter 3 to change Age\nEnter 4 to change Phone Number\nPress 5 to change Password\nEnter 6 to change Security Question\nEnter 7 to change Van Details\nEnter 0 to Exit" << endl;
			cin >> ans;
			checkIntInput(cin,ans);
			if (ans == 1)
			{
				bool x=0;
				cout << endl << "Current Name: " << DOB.get_full_name();
					while(!x)
					{
						cout << "\nEnter New Full Name: ";
						cin.ignore();
						getline(cin,str);
						x = vcheckNum(str);
					}
					DOB.set_full_name(str);
					cout << "Full Name changed!";
					cout << "New Name: " << DOB.get_full_name();
			}
			else if (ans == 2)
			{
				int ans1=1;
				cout << endl << "Current Address: " << DOB.get_current_location();
				cout << "\n1. North Nazimabad  2. Water Pump" << endl;
				cout << "3. Gulshan Iqbal    4. Johar" << endl;
				cout << "5. Malir Cantt.     6. Lyari Express" << endl;
				while(ans1 <1 || ans1 > 6)
				{
					cout << "\nEnter your new address: ";
					cin >> ans1;
					checkIntInput(cin,ans);
				}
				DOB.set_current_location(LOCS[ans1-1]);
				cout << "\nAddress Changed!";
			}
			else if (ans == 3)
			{
				int num;
				cout << endl << "Current Age: " << DOB.get_age();
				cout << endl << "\nEnter New Age: ";
				cin >> num;
				DOB.set_age(num);
				cout << "\nAge Changed!";
			}
			else if (ans == 4)
			{
				string str;
				bool x=0;
				cout << endl << "Current Phone Number: " << DOB.get_phone_num();
				while(!x || str.size()!=11)
				{
					cout << endl << "\nEnter new phone number: ";
					cin >> str;
					x=vcheckChar(str);
				}
				cout << "\nPhone Number changed!";
			}
			else if (ans == 5)
			{
				string str=DOB.get_password(),str2;
				int i=1;
				cout << endl << "Current Password: " << str[0];
				while(i < str.size()-1)
				{
					cout << "*";
					i++;
				}
				cout << str[i];
				i=0;
				while(i<3)
				{
					string str1;
					cout << "\nEnter New Password: ";
					ch=getch();
					while(ch!=13)
					{
						str1.push_back(ch);
						cout<<'*';
						ch=getch();
					}
					cout << "\nConfirm Password: ";
					ch=getch();
					while(ch!=13)
					{
						str2.push_back(ch);
						cout<<'*';
						ch=getch();
					}
					if (str1 == str2)
					{
						cout << "\nPassword Changed!";
						DOB.set_password(str);
						break;
					}
					i++;
					cout << "\tTRY AGAIN! (Attempts remaining: " << 3-i << ")";
				}
			}
			else if (ans == 6)
			{
				int num2;
				string str1;
				cout << endl << "\t\tSECURITY QUESTIONS";
				for (int i=0; i<5; i++)
				{
					cout << i+1 << " " << QUE[i] << endl;
				}
				while(num2<1 || num2>5)
				{
					cout << "\nEnter your security question number: ";
					cin >> num2;
					checkIntInput(cin,num2);
				}
				num2--;
				cout << "Your Security Question is: " << endl;
				cout << "\t" << QUE[num2];
				cout << "\nEnter Security Answer: ";
				getline(cin,str1); 
				DOB.set_queNum(num2);
				DOB.set_queAns(str1);
			}
			else if(ans==7){
				int  x , num1 , num2;
				string str3, str4 , str5 , str6; 
				cout << "\tDriver's Vehicle Credentials" << endl << endl;
			while(str3<"1" || str3 >"2")
			{
				cout << "1. AC\t2. Non-AC" << endl;
				cout << "Enter Driver Van Type: ";
				cin >> str3;
			}
			x=0;
			while(!x)
			{
				cin.ignore();
				cout << "Enter Name Of Vehicle: " << endl;
				getline(cin, str4);
				x = vcheckNum(str4);
			}
			while(str5.size()!=7 || str5[3]!='-')
			{
				cout << "Enter Vehicle Registration Number (XXX-000) :" << endl;
				getline(cin, str5);
			}
				x=0;
			while(!x)
			{
				cout << "Enter Vehicle Colour:" << endl;
				getline(cin, str6);
				x = vcheckNum(str6);
			}
			while(num1 < 1 || num1 >30)
			{
				cout << "Enter Vehicle seats: ";
				cin >> num1;
			}
			
			DOB.set_van_details(str3,str4,str6,str5,num1,0);
			}
			getch();
		}
	}
	else
	{
		cout << "WRONG PASSWORD!";
		getch();
	}	
}

void displayDriverHistory(driver &DOB, ride R[100])
{
	int j=0, ans=0, flag=0;
	ride temp[20];
	for(int i=0; R[i].get_RideID()!="N/A"; i++)
	{
		if (DOB.get_id()==R[i].get_DriverID())
		{
			temp[j]=R[i];
			j++;
			flag=1;
		}
	}
	if (flag == 0)
	{
		cout << "\nPlease complete few rides BAM-Driver!";
	}
	else
	{
		tm tempVar;
		cout << "  Ride ID  Driver ID  Passenger ID  Fare  Pickup Location  Date  User Feedback" << endl;
		for(int i=0; i<j; i++)
		{
			tempVar = temp[j].get_start_time();
			cout << i+1 << " " << temp[i].get_RideID() << "\t" << temp[i].get_DriverID() << "\t" << temp[i].get_PassengerID() << "\t" << temp[i].get_fare() << "\t" << temp[i].get_pickup_location() << "\t" << tempVar.tm_mday <<"/"<<tempVar.tm_mon<<"/"<<tempVar.tm_year<<"\t" << temp[i].get_user_feedback()<< endl;
		}
		while(ans<1 || ans>j)
		{
			cout << "\n\tEnter selection: ";
			cin >> ans;
			checkIntInput(cin,ans);
		}
		system("cls");
		cout << temp[ans-1];
		getch();
	}
}

void displayCurrPassengers(driver DOB, passenger P[20], ride R[100])
{
	system("cls");
	int j=0;
	if (DOB.get_numOfPassengers()==0)
		cout << "\n\nNo Passengers booked";
	else
	{
		cout << "\t\tPASSENGERS IN VAN";
		cout << "\nID\tDropoff Location\tFare Collection" << endl;
		for (int i=0; R[i].get_RideID()!="N/A";i++)
		{
			if (R[i].get_DriverID()==DOB.get_id() && R[i].get_ride_status()=="In Progress")
			{
				cout << j+1 << R[i].get_PassengerID() << "\t" << R[i].get_dropoff_location() << "\t" << R[i].get_fare() << endl;
				j++;
			}
		}
		j=0;
		cout << "\n\t\tPASSENGERS THAT HAVE BOOKED YOU" << endl;
		cout << "\nID\tDropoff Location\tFare Collection" << endl;
		for (int i=0; R[i].get_RideID()!="N/A";i++)
		{
			if (R[i].get_DriverID()==DOB.get_id() && R[i].get_ride_status()=="Booked")
			{
				cout << j+1 << R[i].get_PassengerID() << "\t" << R[i].get_dropoff_location() << "\t" << R[i].get_fare() << endl;
				j++;
			}
		}
	}	
}

void driver_menu(passenger P[15],driver &DOB,ride R[15])
{
	int ans;
	driver arr[2];
	arr[0]=DOB;
	while(ans!=5)
	{
		system("cls");
		refresh_curr_locations(arr);
		DOB=arr[0];
		for (int i=0; R[i].get_RideID()!="N/A"; i++)
		{
			for(int j=0; P[j].get_id()!="N/A";j++)
			{
				if (R[i].get_PassengerID() == P[j].get_id() && R[i].get_ride_status()=="Booked")
				{
					time_t curr_time;
					tm * curr_tm;
					time(&curr_time);
					curr_tm = localtime(&curr_time);
					if (calculateTimeDiff(*curr_tm,R[i].get_start_time())<0)
					{
						P[j].set_in_ride(1);
						R[i].set_ride_status("In Progress");
					}
				}
				else if (R[i].get_PassengerID()==P[j].get_id() && R[i].get_ride_status()=="In Progress")
				{
					time_t curr_time;
					tm * curr_tm;
					time(&curr_time);
					curr_tm = localtime(&curr_time);
					if (calculateTimeDiff(*curr_tm,R[i].get_end_time())<0)
					{
						P[j].set_in_ride(0);
						R[i].set_ride_status("Incomplete");
					}
				}
			}
		}
		cout << "1. Display Current Passengers." << endl;
		cout << "2. Display Bio." << endl;
		cout << "3. Display Ride History." << endl;
		cout << "4. Edit Bio." << endl;
		cout << "5. Exit." << endl;
		cout << "What would you like to do? ";
		cin >> ans;
		checkIntInput(cin,ans);
		if (ans == 1)
		{
			displayCurrPassengers(DOB,P,R);
		}
		else if (ans == 2)
		{
			system("cls");
			cout << DOB;
		}
		else if (ans == 3)
		{
			displayDriverHistory(DOB,R);
		}
		else if (ans == 4)
		{
			EditDriverBio(DOB);
		}
		getch();
	}
}

void admin_menu(admin AOB,passenger POB[15],driver DOB[15],ride R[100], promo PR[20])
{
	int ans;
	while(ans!=7)
	{
		system("cls");
		cout << "1. Display Registered Drivers of your area. \n";
		cout << "2. Display Registered Users of your area. \n";
		cout << "3. Display all rides of your area. \n";
		cout << "4. Register Driver. \n";
		cout << "5. Provide promo code. \n";
		cout << "6. Relieve driver. \n";
		cout << "7. To Exit. \n";
		cout << "What would you like to do: ";
		cin >> ans;
		checkIntInput(cin,ans);
		if (ans == 1)
		{
			displayDrivers(AOB.get_area(),DOB);
		}
		else if (ans == 2)
		{
			displayUsers(AOB.get_area(),POB);
		}
		else if (ans == 3)
		{
			displayAllRides(AOB.get_area(),POB,DOB,R);
		}
		else if (ans == 4)
		{
			registerDriver(DOB);
		}
		else if (ans == 5)
		{
			addPromo(PR);
		}
		else if (ans == 6)
		{
			removeDriver(AOB.get_area(), DOB);
		}
	}
}

void user_menu(passenger &UOB, driver D[10],ride R[100], promo PR[20])
{
	int ans=0;
	refresh_user_menu(UOB,D,R);
	while(ans!=9)
	{
		system("cls");
		cout << "1. Book a ride. \n";
		cout << "2. Track your ride. \n";
		cout << "3. Display Bio. \n";
		cout << "4. Edit Bio. \n";
		cout << "5. Ride History. \n";
		cout << "6. Refresh. \n"; 
		cout << "7. Cancel Ride. \n"; 
		cout << "8. About Us. \n";
		cout << "9. To Exit. \n";
		cin >> ans;
		checkIntInput(cin,ans);
		switch (ans)
		{
			case 1:
				bookRide(UOB,D,R,PR);
				break;
			case 2:
				trackRide(UOB,D,R);
				break;
			case 3:
				system("cls");
				cout << UOB;
				break;
			case 4:
				editBio(UOB);
				break;
			case 5:
				displayRideHistory(UOB,R);
				break;
			case 6:
				refresh_user_menu(UOB,D,R);
				break;
			case 7:
				cancelRide(UOB,D,R);
				break;
			case 8:
				aboutUs();
				break;
			case 9:
				break;
			default:
				break;
		}
		getch();
	}
}

void signin(passenger P[25],admin A[6], driver D[25],ride R[100], promo PR[20])
{
	int attempts=0,flag=0,ansf;
	string str1;
	while(attempts<3)
	{
		string str2;
		char ch;
		system("cls");
		cout << "Enter Username: ";
		cin >> str1;
		cout << "Enter Password: ";
		ch=getch();
		while(ch!=13)
		{
			str2.push_back(ch);
			cout<<'*';
			ch=getch();
		}
		if (str1[0]=='U')
		{
			int i=0;
			while(P[i].get_id()!="N/A")
			{
				if(str1 == P[i].get_id() && str2 == P[i].get_password())
				{
					flag=1;
					cout << endl << "Login Succesful!";
					getch();
					user_menu(P[i],D,R, PR);
					break;
				}
				i++;
			}
			if (flag == 1)
				break;
		}
		else if (str1[0]=='D')
		{
			int i=0;
			while(D[i].get_password()!="N/A")
			{
				if(str1 == D[i].get_id() && str2 == D[i].get_password())
				{
					flag=1;
					cout << endl << "Login Succesful!";
					getch();
					driver_menu(P,D[i],R);
					break;
				}
				i++;
			}
			if (flag == 1)
				break;
		}
		else if (str1[0]=='A')
		{
			int i=0;
			while(i<6)
			{
				if(str1 == A[i].get_id() && str2 == A[i].get_password())
				{
					flag=1;
					cout << endl << "Login Succesful!";
					getch();
					admin_menu(A[i],P,D,R,PR);
					break;
				}
				i++;
			}
			if (flag == 1)
				break;
		}
		if (flag == 0)
		{
			cout << "\n\nUNSUCCESSFUL LOGIN ATTEMPT! Press 1 if you forgot password else press any key to continue:  ";
			cin >> ansf;
			checkIntInput(cin,ansf);
			if (ansf == 1)
			{
				bool x=0,flagp=0;
				string str_pnum, str_ans;
				cout << "\n\t";
				while(!x || str_pnum.size()!=11)
				{
					cout << "Enter your phone number: ";
					cin >> str_pnum;
					x= vcheckChar(str_pnum);
				}
				for(int i=0; P[i].get_id()!="N/A";i++)
				{
					if(P[i].get_phone_num() == str_pnum)
					{
						flagp=1;
						cout << "\n\t" << QUE[P[i].get_queNum()] << endl << "\t";
						cin.ignore();
						getline(cin,str_ans);
						if (str_ans == P[i].get_queAns())
						{	
							getch();
							user_menu(P[i],D,R,PR);
						}
					}
				}
				for(int i=0; A[i].get_id()!="N/A";i++)
				{
//					cout << A[i].get_phone_num();
					if(A[i].get_phone_num() == str_pnum)
					{
//						cout << A[i].get_id();
						flagp=1;
						cout << "\n\t" << QUE[A[i].get_queNum()] << endl << "\t";
						cin.ignore();
						getline(cin,str_ans);
						if (str_ans == A[i].get_queAns())
						{
							cout << "LOGIN SUCCESFUL!";
							getch();
							admin_menu(A[i],P,D,R,PR);
							break;
						}
					}
				}
				for(int i=0; D[i].get_id()!="N/A";i++)
				{
					if(D[i].get_phone_num() == str_pnum)
					{
						flagp=1;
						cout << "\n\t" << QUE[D[i].get_queNum()] << endl << "\t";
						cin.ignore();
						getline(cin,str_ans);
						if (str_ans == D[i].get_queAns())
						{
							cout << "LOGIN SUCCESFUL!";
							getch();
							driver_menu(P,D[i],R);
						}
					}
				}
				if (flagp == 0)
				{
					cout << "\nNo account with the phone number ( " << str_pnum << " ) exists. \n";
					getch();
				}
				else
					break;
			}
//			getch();
			attempts++;
			continue;
		}	
	}
	getch();
}

int main()
{
	system("COLOR 80");
	passenger P[40];
	admin A[6];
	driver D[20];
	ride R[100];
	promo PR[20];
	extract(P,A,D,R,PR);
	int ans =0;
	while(ans !=3)
	{
		system("cls");
		cout << "\t\t\tWelcome to BAM Travel Management and Cab Booking System!\n\n";
		cout << "1. Sign In." << endl;
		cout << "2. Sign Up." << endl;
		cout << "3. Exit." <<endl;
		cout << "\nWhat would you like to do: ";
		cin >> ans;
		checkIntInput(cin,ans);
		if (ans == 1)
		{
			signin(P,A,D,R, PR);
		}
		else if (ans == 2)
		{
			signup(P);
		}
		else if (ans == 3)
		{
			cout << "Thank you for using BAM Services! Until next time :)";
//			return 0;
		}
		else
		{
			cout << "Invalid Input!";
		}
		getch();
	}
	update(P,A,D,R,PR);
	return 0;
}