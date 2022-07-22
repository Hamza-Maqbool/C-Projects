#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
using namespace std;

// FUCNTION PROTO_TYPES.........

bool loginMenu();
char main_manu(char option);
char admin_option(char option);
char staff_option(char option);
char user_option(char option);
void header();
void clearsceern();
void display_staff_info();
void quantity();
void addstaffintoArray(string sname, string id, string mobile, string duty);
void addstaff();
void addstaffintofile(string sname, string id, string mobile, string duty);
void addproductintofile(string pname, int pprice, int pquan);
void addproductintoArray(string pname, int pprice, int pquan);
void addproduct();
void loadStaffData();
void loadProductData();
void AddPharmacyname();
void loadPharmacyname();
void Putproductdataintofile();
void Putstaffdataintofile();

// DATA STRUCTURES........

const int MAX_RECORDS = 20;
string mobileA[MAX_RECORDS];
string idA[MAX_RECORDS];
string staffnameA[MAX_RECORDS];
string dutyA[MAX_RECORDS];
string productnameA[MAX_RECORDS];
int productpriceA[MAX_RECORDS];
int quantityA[MAX_RECORDS];
int entry_countS = 0;
string rnameA[MAX_RECORDS];
string reasonA[MAX_RECORDS];
string deletepA[MAX_RECORDS];
int count_AP = 0;
int count_DP = 0;
int quantity_p = 0;
string Pname = "0";
char option, op;
int count = 0, count_s = 0, count_pn = 0, countr = 0,countsum = 0,len;
float result;

// MAIN FUNCTION..........

main()
{

    while (true)
    {
        header();
        option = main_manu(option);// FUNCTION CALLING OF MAIN MANU
        if(option != '1' && option != '2' && option != '3' && option != '4')
        {
            cout<< "INVALID OPTION....."<<endl;
        }
        loadStaffData();
        if (option == '1')
        {
            cout << "ENTER THE ADMIN PASSWORD : ";
            string password;
            cin >> password;
            clearsceern();
            while (true)
            {

                if (password == "007") // ADMIN PASSWORD
                {
                    // ADMIN OPTIONS

                    header();
                    op = admin_option(op);
                    if(op != '1' && op != '2' && op != '3' && op != '4' && op != '5' && op != '6' && op != '7')
                    {
                        cout<< "INVALID OPTION....."<<endl;
                    }
                    if (op == '1')
                    {
                        AddPharmacyname(); // FUNCTION CALLING
                    }
                    else if (op == '2')
                    {
                        loadPharmacyname(); // FUNCTION CALLING
                    }
                    else if (op == '3')
                    {
                        addstaff(); // FUNCTION CALLING
                    }
                    else if (op == '4')
                    {
                        cout << "NAME" << "\t\t\t\t" << "ID" << "\t" << "MOBILE" << "\t\t" << "DUTY" << endl;
                       
                        display_staff_info(); // FUNCTION CALLING
                    }
                    else if (op == '5')
                    {
                        cout<<"Enter the name of staff member you want to delete: ";
                        string delS;
                        cin>>delS;
                        bool found1 = 0;
                        for (int i = 0; i < entry_countS; i++)
                        {
                            if (delS == staffnameA[i])
                            {
                                found1 = 1;
                                staffnameA[i] = "REMOVE.";
                                idA[i] = "REMOVE.";
                                mobileA[i] = "REMOVE.";
                                dutyA[i] = "REMOVE.";
                            }
                           
                        }
                        if(found1 == 0)
                        {
                            cout << "THIS STAFF MEMBER NOT WORKING HERE..." <<endl;
                        }
                        Putstaffdataintofile(); // FUNCTION CALLING
                    }

                    else if (op == '6')
                    {
                        loadProductData(); // FUNCTION CALLING
                        if (count_AP == 0)
                        {
                            cout << "NO PRODUCT ADD BY STAFF MEMBER " << endl;
                        }
                        else if (count_AP != 0)
                        {
                            cout << "Productname" << "\t" << "Quantity" << "\t" << "Price" << endl;
                            quantity(); // FUNCTION CALLING
                        }
                    }
                    else if (op == '7')
                    {
                        break;
                    }
                }

                if (password != "007")
                {
                    cout << "YOU ENTER WRONG PASSWORD...." << endl;
                    break;
                }

                clearsceern();
            }
            clearsceern();

        } // END OF ADMIN OPTIONS
        else if (option == '2')
        {
            bool staff = loginMenu(); // FUNCTION CALLING WHETER THE ID IS CORRECT OR NOT....
            clearsceern();
            loadProductData();
            
            while (true)
            {
                if (staff == 1)
                {
                    //STAFF OPTIONS
                    header();
                    op = staff_option(option); // FUNCTION CALLING FOR STAFF OPTION
                    if(op != '1' && op != '2' && op != '3' && op != '4' && op != '5')
                    {
                        cout<< "INVALID OPTION....."<<endl;
                    }

                    if (op == '1')
                    {
                        addproduct(); // FUNCTION CALLING
                    }
                    else if (op == '2') //PRODUCT DELETED OPTION
                    {
                        cout<<"Enter the name of product you want to delete: ";
                        string delP;
                        int quant;
                        bool found1 = 0;
                        cin>>delP;
                        for (int i = 0; i < count_AP; i++)
                        {
                            if (delP == productnameA[i])
                            {
                                found1 = 1;
                                cout<<"Enter the quantity you want to delete: ";
                                cin >> quant;
                                quantityA[i] = quantityA[i]-quant;
                                if(quantityA[i] == 0)
                                {
                                    productnameA[i] = "DELETED";
                                    productpriceA[i] = 0;
                                }
                                break;
                            }
                            
                        }
                        if(found1 == 0)
                        {
                            cout << "THIS PRODUCT IS NOT FOUND..." <<endl;
                        }
               
                    }
                    else if (op == '3')
                    {
                        // SORTING THE PRODUCT ACCORDING TO PRICE
                        for (int i = 0; i < count_AP - 1; i++)
                        {
                            for (int j = i + 1; j < count_AP ; j++)
                            {
                                if (productpriceA[i] > productpriceA[j])
                                {
                                    swap(productpriceA[j], productpriceA[i]);
                                    swap(productnameA[j], productnameA[i]);
                                    swap(quantityA[j], quantityA[i]);
                                }
                            }
                        }
                        for (int i = 0; i < count_AP; i++) //DISPLAYING THE SORTED PRODUCT
                        {
                            cout << "Product__Name" << "\t" << "Product__Quantity" << "\t" << "Product__Price" << endl;
                            cout << productnameA[i] << "\t\t\t" << quantityA[i] << "\t\t\t" << productpriceA[i] << endl;
                        }
                    }
                    else if (op == '4')
                    {
                        
                        if (count_AP == 0)
                        {
                            cout << "NO PRODUCT ADD BY STAFF.." << endl;
                        }
                        else if (count_AP != 0)
                        {
                            cout << "Product__Name" << "\t" << "Product__Quantity" << "\t" << "Product__Price" << endl;
                            quantity();
                        }
                    }
                    else if (op == '5')
                    {
                        break;
                    }
                }

                else
                {
                    cout << "YOU ENTER WRONG ID......  " << endl;
                    break;
                }
                clearsceern();
            }
            clearsceern();
        } // END OF WHILE LOOP // END OF STAFF OPTIONS.
        else if (option == '3')
        {
            // USER OPTION
            clearsceern();
            loadProductData();
            while (true)
            {
                header();
                op = user_option(option); // FUNCTION CALLING FOR USER OPTION
                if(op != '1' && op != '2' && op != '3' && op != '4' && op != '5'&& op != '6')
                {
                    cout<< "INVALID OPTION....."<<endl;
                }
                if (op == '1')
                {
                    cout << "productname" << "\t" << "quantity" << "\t" << "price" << endl;
                    quantity();
                }
                if (op == '2')
                {
                    cout << "NO DISCOUNTED PRODUCT AVAILABLE AT THIS TIME " << endl;
                }
                else if (op == '3') // BUY THE PRODUCT OPTION
                {
                    cout << "ENTER HOW MANAY PRODUCT YOU WANT TO BUY : " << endl;
                    int buy;
                    cin >> buy;
                    cout << "WHICH PRODUCT YOU WANT TO BUY : " << endl;
                    string a;
                    cin >> a;
                    cout << "ENTER QUANTITY OF THE PRODUCT YOU WANT TO BUY : " << endl;
                    int qu;
                    cin >> qu;
                    int decrese;
                    string yes;
                    int price,j;
                    bool isfound1 = 0;
                    for (int i = 0; i < count_AP; i++)
                    {
                        if (a == productnameA[i])
                        {
                            isfound1 = 1;
                            j = i;
                            break;
                        }
                    }
                    if(isfound1 == 1)
                    {
                        cout << "ARE YOU SURE YOU WANT TO PURCHASE THIS PRODUCT PRESS (YES) OTHERWISE PRESS (NO)" << endl;
                        cin >> yes;
                        if (yes == "YES")
                        {
                            if (quantityA[j] >= qu)
                            {
                                for(int i = 0; i < buy;i++)
                                {
                                    decrese = quantityA[i] - qu;
                                    quantityA[i] = decrese;
                                    price = qu * productpriceA[i];
                                    countsum = countsum + price;
                                }
                                
                            }
                            else
                            {
                                cout << "NOT ENOUGH QUANTITY AVAILABLE AT THIS TIME....." << endl;
                            }
                        }
                    }
                    else if (isfound1 == 0)
                    {
                        cout << "THIS PRODUCT IS NOT AVAILABLE......." << endl;
                    }
                }
                else if (op == '4') // VEIW THE BILL OPTION
                {

                    if (countsum > 1000)
                    {
                        result = countsum * 0.30;
                        result = countsum - result;
                        cout << "YOU GET 30 % DISCOUNT YOUR BILL WIL BE : " << result << endl;
                    }
                    else
                    {
                        cout << "YOUR BILL WIL BE : " << countsum << endl;
                    }
                }
                else if (op == '5') // RETURN THE PRODUCT OPTION
                {
                    loadProductData(); // FUNCTION CALLING
                    cout << "ENTER WHICH PRODUCT YOU RETURN : ";
                    string ab;
                    cin >> ab;
                    cout << "ENTER CONDITION OF THE PRODUCT....  IF USE PREES (U) AND IF NOT PREES (N)" << endl;
                    char use;
                    cin >> use;
                    cout << "ENTER QUANTITY OF THE PRODUCT YOU WANT TO RETURN : " << endl;
                    int qu;
                    cin >> qu;
                    bool isfound = 0;
                    int increase,price;
                    for (int i = 0; i < count_AP; i++)
                    {
                        if (ab == productnameA[i] && use == 'N')
                        {
                            isfound = 1;
                            increase = quantityA[i] + qu;
                            quantityA[i] = increase;
                            price = qu * productpriceA[i];
                            cout << "YOUR RETURN AMOUNT WILL BE : " << price << endl;
                        }
                    }
                    if (isfound == 0)
                    {
                        cout << "YOU CANNOT RETURN THE PRODUCT.." << endl;
                    }
                }
                else if (op == '6')
                {
                    break;
                }
                clearsceern();
            }
            clearsceern();
        }
        else if (option == '4')
        {
            break;
        }
    } // END OF MAIN WHILE LOOP.
    Putproductdataintofile(); // FUNCTION CALLING
    Putstaffdataintofile(); // FUNCTION CALLING
}
// END OF MAIN FUNCTION......

// FUNCTIONS IMPLEMENTATIONS....
void header()
{
    cout << "                                                    " << endl;
    cout << "   *********************************************** " << endl;
    cout << "             PHARMACY MANAGEMENT SYSTEM            " << endl;
    cout << "                                                  " << endl;
    cout << "   ***********************************************" << endl;
    cout << "                                                  " << endl;
}
char main_manu(char option)
{
    cout << "  LOGIN AS ADMIN " << endl;
    cout << "  PRESS  1.      " << endl;
    cout << "                                                  " << endl;
    cout << "  LOGIN AS STAFF MEMBER  " << endl;
    cout << "  PRESS  2.      " << endl;
    cout << "                                                  " << endl;
    cout << "  LOGIN AS USER      " << endl;
    cout << "  PRESS  3.      " << endl;
    cout << "                                                  " << endl;
    cout << "  EXIT           " << endl;
    cout << "  PRESS 4.       " << endl;
    cout << "                                             " << endl;
    cout << "  SELECT YOUR OPTION.......... " << endl;     
    cin >> option;
    return option;
}
char admin_option(char option)
{
    cout << "1. SELECT  PHARMACY NAME." << endl;
    cout << "2. VEIW  PHARMACY NAME." << endl;
    cout << "3. ADD STAFF MEMBER." << endl;
    cout << "4. VIEW STAFF MEMBER." << endl;
    cout << "5. REMOVE STAFF MEMBER." << endl;
    cout << "6. VIEW PRODUCT LIST." << endl;
    cout << "7.  TO GO BACK" << endl;
    cout << "SELECT YOUR OPTION....." << endl;

    cin >> option;
    return option;
}
char staff_option(char option)
{
    cout << "1. ADD PRODUCT." << endl;
    cout << "2. DELETE PRODUCT." << endl;
    cout << "3. SORT THE PRODUCT." << endl;
    cout << "4. CHECK QUANTITY OF PRODUCT." << endl;
    cout << "5. TO GO BACK." << endl;
    cout << "SELECT YOUR OPTION....." << endl;
    cin >> option;
    return option;
}
int MOBILE;
char user_option(char option)
{
    cout << " 1. VIEW AVAILABLE PRODUCTS AND PRICE." << endl;
    cout << " 2. VEIW DISCOUNTED PRODUCTS." << endl;
    cout << " 3. BUY THE PRODUCT " << endl;
    cout << " 4. VEIW THE BILL .(IF HE/SHE SHOPING MORE THAN 1000 HE/SHE WILL GET 30% DISCOUNT)" << endl;
    cout << " 5. RETURN THE PRODUCT." << endl;
    cout << " 6. TO GO BACK." << endl;
    cout << "SELECT YOUR OPTION....." << endl;
    cin >> option;
    return option;
}
void display_staff_info()
{
    
    for (int i = 0; i < entry_countS; i++)
    {
        cout << staffnameA[i] << "\t\t\t" << idA[i] << "\t" << mobileA[i] << "\t" << dutyA[i] << endl;
    }
}
void clearsceern()
{
    cout << "PRESS ANY KEY TO CONTIUNE......" << endl;
    getch();
    system("cls");
}
void quantity()
{
    
    for (int i = 0; i < count_AP; i++)
    {
        cout << productnameA[i] << "\t\t" << quantityA[i] << "\t\t" << productpriceA[i] << endl;
    }
}
bool loginMenu()
{

    loadStaffData();
    cout << "ENTER YOUR NAME : ";
    string username;
    string pass;
    cin.ignore();
    getline(cin , username);
    while(true)
    {
        cout << "ENTER YOUR STAFF ID : ";
        cin >> pass;
        int passlen = pass.length();
        if(passlen < 6)
        {
            cout<< "ENTER SIX CHARACTERS PASSWORD..."<<endl;
        }
        if(passlen >= 6)
        {
            break;
        }
    }
    for (int i = 0; i < MAX_RECORDS; i++)
    {
        if (staffnameA[i] == username && idA[i] == pass)
        {
            return 1;
        }
    }
    return 0;
}
void addstaff()
{
    string sname, id, mobile, duty;
    bool passfound = 0;
    cout << " ENTER THE NEW STAFF MEMBER NAME : ";
    cin.ignore();
    getline(cin , sname);
    cout << " ENTER HIS/HER MOBILE NUMBER : ";
    getline(cin , mobile);
    cout << " ENTER HIS/HER DUTY : ";
    getline(cin , duty);
    while(true) // STRONG PASSWORD IMPLEMEMTATIONS.....RECOMDATIONS
    {
        cout << " ENTER HIS/HER LOGIN ID : ";
        getline(cin , id);
        len = id.length();
        if(len >= 6)
        {
            for(int i = 0 ; i < len; i++)
            {
                if(id[i] == '@' || id[i] == '#' || id[i] == '$' || id[i] == '%' || id[i] == '^' || id[i] == '&' || id[i] == '*'|| id[i] == '!')
                {
                    passfound = 1;
                    addstaffintoArray(sname, id, mobile, duty); // FUNCTION CALLING
                    addstaffintofile(sname, id, mobile, duty); // FUNCTION CALLING
                    break;
                }              
            }
                if(passfound == 1)
                {
                    break;
                }
                if(passfound == 0)
                { 
                    cout << "ENTER STRONG PASSWORD.....";
                    cout << "LIKE.......@786786...."<<endl;
      
                }
        } 
        else
        {
            cout << "ENTER SIX CHARCATER PASSWORD....."<< endl;
        }
    }
}    
    

void addstaffintoArray(string sname, string id, string mobile, string duty)
{
    staffnameA[entry_countS] = sname;
    idA[entry_countS] = id;
    mobileA[entry_countS] = mobile;
    dutyA[entry_countS] = duty;
    entry_countS++;
}
void addstaffintofile(string sname, string id, string mobile, string duty)
{
    fstream file;
    file.open("staff info.txt", ios::app);
    file << sname << "\t\t\t" << id << "\t" << mobile << "\t" << duty << endl;
    file.close();
}
void addproduct()
{
    string pname;
    int pprice, pquan;
    cout << "ENTER THE NAME OF THE PRODUCT : ";
    cin.ignore();
    getline(cin , pname);
    cout << "ENTER THE NEW PRODUCT PRICE : ";
    cin >> pprice;
    cout << "ENTER THE PRODUCT QUANTITY : ";
    cin >> pquan;
    addproductintoArray(pname, pprice, pquan); // FUNCTION CALLING
    addproductintofile(pname, pprice, pquan); // FUNCTION CALLING
}
void addproductintoArray(string pname, int pprice, int pquan)
{
    productnameA[count_AP] = pname;
    productpriceA[count_AP] = pprice;
    quantityA[count_AP] = pquan;
    count_AP++;
}
void addproductintofile(string pname, int pprice, int pquan)
{
    fstream myfile;
    myfile.open("productInfo.txt", ios::app);
    myfile << pname << "\t\t\t" << pquan << "\t\t\t\t" << pprice << endl;
    myfile.close();
}
void loadStaffData()
{
    fstream file;
    file.open("staff info.txt", ios::in);
  
    int i = 0;
    while (!file.eof())
    {
        file >> staffnameA[i];
        file >> idA[i];
        file >> mobileA[i];
        file >> dutyA[i];
        i++;
    }
    entry_countS = i;
    file.close();
}
void loadProductData()
{
    fstream file;
    file.open("productInfo.txt", ios::in);
  
    int j = 0;
    while (!file.eof())
    {
        file >> productnameA[j];
        file >> quantityA[j];
        file >> productpriceA[j];
        j++;
        
    }
    count_AP = j - 1;
    file.close();
}
void loadPharmacyname()
{
    fstream file;
    string phar_name;
    file.open("PHARMACY NAME.txt", ios::in);
     while (!file.eof())
    {
       getline(file , phar_name);
       cout << phar_name << endl;
       if (phar_name[0]=='\0')
       {
           cout<<"PHARMACY NAME IS NOT SELECTED....YET"<<endl;
       }
       
    }
    file.close();
}
void AddPharmacyname()
{
    fstream file;
    cout << "1. ENTER PHARMACY NAME : " << endl;
    file.open("PHARMACY NAME.txt", ios::out);
    cin.ignore();
    getline(cin , Pname);
    file << Pname;
    file.close();
}
void Putproductdataintofile()
{
    fstream file("productInfo.txt",ios::out);
    for(int i = 0 ; i<count_AP ; i++)
    {
        file << productnameA[i] << "\t\t" << quantityA[i] << "\t\t" << productpriceA[i] << endl;
    }
    file.close();
}
void Putstaffdataintofile()
{
    fstream file("staff info.txt",ios::out);
    for(int i = 0 ; i < entry_countS -1 ; i++)
    {
        file << staffnameA[i] << "\t\t" << idA[i] << "\t" << mobileA[i] << "\t" << dutyA[i] << endl;
    }
    file.close();
}