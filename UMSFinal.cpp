#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;


// ------------------ Prototypes
void mainHeader();
char adminMenu();
void clearScreen();
string loginMenu();
void addStudent();
void viewAllStudents();
void subheader();
char studentMenu();
void addStudentIntoArray(string name, int matric, int fsc, int ecat, string p1, string p2, string p3);
int seatManagementMenu();
void viewSeatsDetails();
void addUser(string name, string pass, string role);
void  print_Recd();
void aggrigate();
void generate_Mlist();
int studentInfo();//------------------- Prototypes

const int MAX_RECORDS = 20;
// Data Structures 
string usernameA[MAX_RECORDS];
string passwordsA[MAX_RECORDS];
string rolesA[MAX_RECORDS];
int userCount = 0;
int count=0;

string student_name[MAX_RECORDS];
float student_ecat[MAX_RECORDS];
float student_matric[MAX_RECORDS];
float student_fsc[MAX_RECORDS];
string student_pref1[MAX_RECORDS];
string student_pref2[MAX_RECORDS];
string student_pref3[MAX_RECORDS];
string department[] = {"CS", "CE", "EE"};
int seats[] = {0,0,0};
int entry_count=0;
bool announce = false;
float aggr[MAX_RECORDS];
int capacity=0;
string username;
// Main function
main(){


addUser("admin", "123", "ADMIN");

 string who = " ";     
 while(true){
  who =  loginMenu();
  if(who == "ADMIN"){
    char option = ' ';
      while(true){
          system("cls");
          option = adminMenu();
          if(option == '1'){
              addStudent();
          }else if(option == '2'){
              viewAllStudents();
          }else if(option == '3'){
                //--------------------------------------------------------Print the record in merit order
                print_Recd();
                	for(int i=0;i<MAX_RECORDS;i++)
						{
						cout<<student_name[i]<<"\t"<<student_matric[i]<<"\t"<<student_fsc[i]<<"\t"<<student_ecat[i]<<"\t"<<aggr[i]<<endl;
						}
          }else if(option == '4'){
              //-------------------------------------------------------- Generate merit list
			  	  generate_Mlist();
          }else if(option == '5'){
              //-------------------------------------------------------- Add Users
              cout<<"Enter username........ ";
              string username;
              cin>>username;
            
              cout<<"Enter password........ ";
              string pass;
              cin>>pass;
              
              cout<<"Enter role........";
              string role;
              cin>>role;
              addUser(username,pass,role);
              
          }else if(option == '6'){
             while(true){
               system("cls");
               int dpIndex =seatManagementMenu();
               if(dpIndex == 1 || dpIndex == 2 || dpIndex == 3){
                 cout<<"Enter New Capacity for "<<department[dpIndex-1]<<endl;
                 
                 cin>>capacity;
                 seats[dpIndex-1] = capacity;
               }else if(dpIndex == 4){
                  viewSeatsDetails();
                  clearScreen();
               }else if(dpIndex == 5){
                  break;
               }else{
                 cout<<"You chose wrong option!"<<endl;
                  clearScreen();
               }
             }//end of seats management 
          }else if(option == '7'){
             cout<<"Press 2 to Announce the Result ";
             int annouce;
             cin>>annouce;
             if(annouce == 2){
                announce = true;
             }
          }else if(option == '8'){
             break;
          }else{
            cout<<"You Chose Wrong option "<<endl;
          }
          clearScreen();
      }//end of admin wile loop
  }else if(who == "STUDENT"){
     char studentOption = ' ';
     while(true){
       system("cls");
       studentOption = studentMenu();
       if(studentOption == '1'){
            // View student information
            int st_index=studentInfo();
            	cout<<student_name[st_index]<<"\t"<<student_matric[st_index]<<"\t"<<student_fsc[st_index]<<"\t"<<student_ecat[st_index]<<"\t"<<aggr[st_index]<<endl;
       }else if(studentOption == '2'){
          if(announce){
                      //--------------------------------------------------------pending to impliment
          }else{
            cout<<"Result is not announced yet "<<endl;
          }
       }else if(studentOption == '3'){ // logout option
          cout<<"Change your password "<<endl;
       }else if(studentOption == '4'){
         break;
       }else{
         cout<<"Wrong selection! Try again";
       }
       clearScreen();
     }//end of student menu while loop
  }else if(who == "EXIT" ){
     cout<<"choose correct option"<<endl;
  }else{
    cout<<"You entered wrong option "<<endl;
  }
  clearScreen();
 }//end of while 

}//end of main function

// Function definations
void mainHeader(){
  cout<<"----------------------------------------------"<<endl;
  cout<<"--- University Admission Management System ---"<<endl;
  cout<<"----------------------------------------------"<<endl;
  
}

string loginMenu(){
   mainHeader();
   cout<<"Enter username ";
   
   cin>>username;

   cout<<"Enter password ";
   string pass;
   cin>>pass;
   

  for(int i =0; i<MAX_RECORDS; i++){
    if(usernameA[i] == username && passwordsA[i] == pass ){
       return rolesA[i];
    }
  }
  return "EXIT";
}

int seatManagementMenu(){
     mainHeader();
    cout << "Seat Management Menu > " << endl;
    cout << "1- Edit CS Capacity " << endl;
    cout << "2- Edit CE Capacity " << endl;
    cout << "3- Edit EE Capacity " << endl;
    cout << "4- View Seats Details "<<endl;
    cout << "5- Back "<<endl;
    int option;
    cin>>option;
    return option;
}
char adminMenu(){
    mainHeader();
    cout << "Admin Main Menu > " << endl;
    cout << "1- Add New Student " << endl;
    cout << "2- View All Students" << endl;
    cout << "3- Print the record in merit order " << endl;
    cout << "4- Generate Merit "<<endl;
    cout << "5- Add Users "<<endl;
    cout << "6- Seat Management "<<endl;
    cout << "7- Announce Result "<<endl;
    cout << "8- Logout " << endl;
    cout << " Choose Your Option : ";
    char option;
    cin >> option;
    return option;
}

char studentMenu(){
    mainHeader();
    cout << "Student Main Menu > " << endl;
    cout << "1- View Your Profile " << endl;
    cout << "2- Check Admission Status " << endl;
    cout << "3- Change Password "<<endl;
    cout << "4- Logout " << endl;
    cout << " Choose Your Option : ";
    char option;
    cin >> option;
    return option;
}

void clearScreen(){
    cout<<"Press anykey to continue "<<endl;
    getch();
    system("CLS");
}

void addStudent(){
    string name;
    int matric, fsc, ecat;
    string pref1, pref2, pref3;
    cout << "Enter student name ..... : ";
    cin >> name;
    cout << "Enter Matric Marks...... ";
    cin >> matric;
    cout << "Enter FSC Marks...... ";
    cin >> fsc;
    cout << "Enter Ecat Marks...... ";
    cin >> ecat;
    subheader();
    cout<<endl;
    cout << "Enter 1st Preference name ..... : ";
    cin >> pref1;
    cout << "Enter 2st Preference name...... ";
    cin >> pref2;
    cout << "Enter 3st Preference name...... ";
    cin >> pref3;
    addStudentIntoArray(name, matric, fsc, ecat, pref1, pref2, pref3);
}

void addStudentIntoArray(string name, int matric, int fsc, int ecat, string p1, string p2, string p3){
    student_name[entry_count] = name;
    student_matric[entry_count] = matric;
    student_fsc[entry_count] = fsc;
    student_ecat[entry_count] = ecat;
    student_pref1[entry_count] = p1;
    student_pref2[entry_count] = p2;
    student_pref3[entry_count] = p3;
    entry_count = entry_count + 1;
}
void viewAllStudents(){
    cout<<"Name\tMatric\tFSC\tECAT\t1st Pref\t2nd Pref\t3rd Pref"<<endl;
    for(int i=0; i<entry_count; i++){
      cout<<student_name[i]<<"\t"<<student_matric[i]<<"\t"<<student_fsc[i]<<"\t"<<student_ecat[i]<<"\t"<<department[i]<<"\t"<<department[i]<<"\t"<<department[i]<<endl;
    }
}

void subheader(){
    cout << "   Enter the Name for Preferences    " << endl;
    cout << "********************************************" << endl;
    cout<< "Choose between these disciplines "<<endl;
    cout<<"1- CS for Compter Science"<<endl;
    cout<<"2- CE for Compter Engineering"<<endl;
    cout<<"3- EE for Electrical Engineering"<<endl;
    cout << "********************************************" << endl;
}

void viewSeatsDetails(){
  cout<<"Departments Seats Details "<<endl;
  for(int i=0; i<3; i++){
      cout<<department[i]<<"   "<<seats[i]<<endl;  
  }
}

void addUser(string name, string pass, string role){
    usernameA[userCount] = name;
    passwordsA[userCount] = pass;
    rolesA[userCount] = role;
    userCount = userCount + 1;
}

void aggrigate(){ //calculate aggrigate

		for(int i=0; i<MAX_RECORDS; i++){
		 aggr[i] = student_ecat[i] / 400*100 * 0.3 + student_matric[i] / 1100*100* 0.25 + student_fsc[i] / 1100*100 * 0.45;	
		}

}
//Generate merit
void  print_Recd(){
	
	
	aggrigate();
	
	for(int i=0; i<MAX_RECORDS;i++)
		{
		for(int j=i+1; j<MAX_RECORDS;j++)
		{
				if(aggr[j]>aggr[i])
				{ //sort aggrigate
				 float temp=aggr[i];
					aggr[i]=aggr[j];
					aggr[j]=temp;
				 //sort name
				 string temp_name=student_name[i];
				 student_name[i]=student_name[j];
				 student_name[j]=temp_name;
				 //sort matric array
				 temp=student_matric[i];
				 student_matric[i]=student_matric[j];
				 student_matric[j]=temp;
				 //sort fsc
				 temp=student_fsc[i];
				 student_fsc[i]=student_fsc[j];
				 student_fsc[j]=temp;
				 //sort ecat
				 temp=student_ecat[i];
				 student_ecat[i]=student_ecat[j];
				 student_ecat[j]=temp;
				 
				}
			}
		}	
	//end sorted order

}

void generate_Mlist(){
	print_Recd();
		while(seats[count] != 0){
			for(int i=0; i<MAX_RECORDS; i++){
			
				if(count==0 && student_pref1[i] == "CS" ){

				cout<<student_name[i]<<"\t"<<student_matric[i]<<"\t"<<student_fsc[i]<<"\t"<<student_ecat[i]<<"\t"<<aggr[i]<<"\t"<<"Got admit in"<<student_pref1[i]<<endl;
		
				}
			
				if(count == 1 && student_pref2[i] == "CE"){
	
				cout<<student_name[i]<<"\t"<<student_matric[i]<<"\t"<<student_fsc[i]<<"\t"<<student_ecat[i]<<"\t"<<aggr[i]<<"\t"<<"Got admit in"<<student_pref1[i]<<endl;
		
				}
				if(count==2 && student_pref3[i] == "EE"){
			
				cout<<student_name[i]<<"\t"<<student_matric[i]<<"\t"<<student_fsc[i]<<"\t"<<student_ecat[i]<<"\t"<<aggr[i]<<"\t"<<"Got admit in"<<student_pref1[i]<<endl;
		
				}
				
			}
			count= count+1;	
			
		}
}

int studentInfo(){
	for(int i=0;i<MAX_RECORDS;i++)
				{
					if(username==student_name[i]){
						
						return i;
					}
					else{
						cout<<"No recod found";
					}
				 
				}
}