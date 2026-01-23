#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cstring>
using namespace std;

void setColor(int textColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,textColor);
}

// ========================================
// BOOKING STRUCTURES
// ========================================

struct BookingRecord
{
    char bookingID[20];
    char customerName[50];
    char date[15];
    char time[10];
    int tableNumber;
    int numberOfGuests;
    char phoneNumber[20];
    char status[20];
};

struct ReceiptData
{
    char bookingID[20];
    char customerName[50];
    char date[15];
    char time[10];
    int tableNumber;
    int numberOfGuests;
    char phoneNumber[20];
    double depositAmount;
    char paymentMethod[30];
};

// ========================================
// REGISTER AND LOGIN CLASSES
// ========================================

class Register
{
    protected:
        char newusername[100], newpassword[100], username[100], password[100], ch, newregister;
};

class NewUser : public Register
{
    private:
        char confirmpassword[100];
        int c = 0, d = 0, a = 0, attempts = 0;

    public:
        NewUser()
        {
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t~~Welcome to the Restaurant Booking Management System~~";
            Sleep(3000);
            system("cls");
        }

        bool CheckCredentials(string username, string password)
        {
            string u, p;
            ifstream f;
            f.open("login in.txt");

            if(!f)
            {
                cout<<"Unable to open file!\n";
                return false;
            }
            while(f >> u >> p)
            {
                if(u == username && p == password)
                {
                    return true;
                }
            }
            return false;
        }

        bool checkUsernameExists(string username)
        {
            ifstream fin("login in.txt");
            string user, pass;
            while (fin >> user >> pass)
            {
                if (user == username)
                {
                    return true;
                }
            }
            return false;
        }

        void registeruser()
        {
            bool test = false;
            do
            {
                c = 0;
                d = 0;
                cout<<"------------------------------------------------------"<<endl;
                cout<<"                    REGISTER ACCOUNT                  "<<endl;
                cout<<"------------------------------------------------------"<<endl;
                cout<<"Enter your new username : ";
                cin.ignore();
                cin>>newusername;

                if(checkUsernameExists(newusername))
                {
                    system("cls");
                    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tThis account has been registered before, please register another one, thank you."<<endl;
                    Sleep(3000);
                    system("cls");
                    continue;
                }

                while(strlen(newusername) < 6 || strlen(newusername) > 15)
                {
                    cout<<"Username must be between 6 - 15 characters. Please re-enter: ";
                    cin.ignore();
                    cin>>newusername;

                    if(checkUsernameExists(newusername))
                    {
                        system("cls");
                        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tThis account has been registered before, please register another one, thank you."<<endl;
                        Sleep(3000);
                        system("cls");
                        cout<<"------------------------------------------------------"<<endl;
                        cout<<"                    REGISTER ACCOUNT                  "<<endl;
                        cout<<"------------------------------------------------------"<<endl;
                        cout<<"Enter your new username : ";
                        cin.ignore();
                        cin>>newusername;
                    }
                }

                cout<<"Enter your new password : ";
                while ((ch = _getch()) != '\r' && ch != '\n')
                {
                    if (ch == 8)
                    {
                        if (c > 0)
                        {
                            cout<<"\b \b";
                            c--;
                        }
                    }
                    else if(newpassword)
                    {
                        newpassword[c++] = ch;
                        putchar('*');
                    }
                }
                newpassword[c] = '\0';

                while(strlen(newpassword) < 4 || strlen(newpassword) > 8)
                {
                    c = 0;
                    cout<<"\nPassword must be between 4 and 8 characters. Please re-enter: ";
                    while ((ch = _getch()) != '\r' && ch != '\n')
                    {
                        if (ch == 8)
                        {
                            if (c > 0)
                            {
                                cout<<"\b \b";
                                c--;
                            }
                        }
                        else if (newpassword)
                        {
                            newpassword[c++] = ch;
                            putchar('*');
                        }
                    }
                    newpassword[c] = '\0';
                }

                cout<<"\nConfirm password        : ";
                while ((ch = _getch()) != '\r' && ch != '\n')
                {
                    if (ch == 8)
                    {
                        if (d > 0)
                        {
                            cout<<"\b \b";
                            d--;
                        }
                    }
                    else if (strlen(confirmpassword) < 100)
                    {
                        confirmpassword[d++] = ch;
                        putchar('*');
                    }
                }
                confirmpassword[d] = '\0';

                while(strcmp(newpassword,confirmpassword) != 0)
                {
                    cout<<"\nIncorrect, please make sure it is consistent with the new password.";
                    cout<<"\n\nConfirm password        : ";
                    d = 0;
                    while ((ch = _getch()) != '\r' && ch != '\n')
                    {
                        if (ch == 8)
                        {
                            if (d > 0)
                            {
                                cout<<"\b \b";
                                d--;
                            }
                        }
                        else if (strlen(confirmpassword) < 100)
                        {
                            confirmpassword[d++] = ch;
                            putchar('*');
                        }
                    }
                    confirmpassword[d] = '\0';
                }
                ofstream fout;
                fout.open("login in.txt",ios::app);
                fout << newusername << " " << newpassword <<"\n";
                fout.close();
                test = true;

            } while(!test);

            system("cls");
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
            Sleep(1000);
            cout<<".";
            Sleep(1000);
            cout<<".";
            Sleep(1000);
            cout<<".";
            Sleep(1000);
            system("cls");

            setColor(10);
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tSuccessful Register Account.";
            Sleep(3000);
            system("cls");
        }

        char Checklogin()
        {
            do
            {
                a = 0;
                setColor(7);
                newregister = '\0';
                cout<<"------------------------------------------------------"<<endl;
                cout<<"                    LOGIN IN ACCOUNT                  "<<endl;
                cout<<"------------------------------------------------------"<<endl;
                cin.ignore();
                cout<<"Enter your username : ";
                cin>>username;
                cout<<"Enter your password : ";
                while ((ch = _getch()) != '\r' && ch != '\n')
                {
                    if (ch == 8)
                    {
                        if (a > 0)
                        {
                            cout<<"\b \b";
                            a--;
                        }
                    }
                    else if(password)
                    {
                        password[a++] = ch;
                        putchar('*');
                    }
                }
                password[a] = '\0';
                system("cls");

                bool checking = CheckCredentials(username, password);
                if(checking)
                {
                    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
                    Sleep(1000);
                    cout<<".";
                    Sleep(1000);
                    cout<<".";
                    Sleep(1000);
                    cout<<".";
                    Sleep(1000);
                    system("cls");

                    setColor(10);
                    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tSuccessful Account.";
                    Sleep(3000);
                    system("cls");
                }
                else
                {
                    while(!checking && (attempts <= 2))
                    {
                        a = 0;
                        system("cls");
                        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
                        Sleep(1000);
                        cout<<".";
                        Sleep(1000);
                        cout<<".";
                        Sleep(1000);
                        cout<<".";
                        Sleep(1000);
                        system("cls");
                        setColor(4);
                        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tFailed Account.";
                        Sleep(3000);

                        system("cls");
                        setColor(7);
                        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tInvalid username or password, please re-enter correct username and password."<<endl;
                        Sleep(3000);
                        system("cls");
                        cout<<"THREE ATTEMPTS LOGIN SYSTEM";
                        cout<<"\n\n";
                        cout<<"\n";
                        cout<<"Username and Password Attempt No.:"<<attempts + 1;
                        cout<<"\n";
                        cout<<"Enter Username Again : ";
                        cin>>username;
                        cout<<"Enter Password Again : ";
                        while ((ch = _getch()) != '\r' && ch != '\n')
                        {
                            if (ch == 8)
                            {
                                if (a > 0)
                                {
                                    cout<<"\b \b";
                                    a--;
                                }
                            }
                            else if(password)
                            {
                                password[a++] = ch;
                                putchar('*');
                            }
                        }
                        password[a] = '\0';
                        attempts++;

                        checking = CheckCredentials(username, password);

                        if(checking)
                        {
                            system("cls");
                            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
                            Sleep(1000);
                            cout<<".";
                            Sleep(1000);
                            cout<<".";
                            Sleep(1000);
                            cout<<".";
                            Sleep(1000);
                            system("cls");

                            setColor(10);
                            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tSuccessful Account.";
                            Sleep(3000);
                            system("cls");
                            setColor(7);
                            cout<<"\n";
                            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tAccess Granted in the System.";
                            Sleep(3000);
                            system("cls");
                        }
                    }

                    if(!checking && attempts > 2)
                    {
                        system("cls");
                        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
                        Sleep(1000);
                        cout<<".";
                        Sleep(1000);
                        cout<<".";
                        Sleep(1000);
                        cout<<".";
                        Sleep(1000);
                        system("cls");
                        setColor(4);
                        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tFailed Account.";
                        Sleep(3000);
                        system("cls");
                        setColor(7);
                        cout<<"\n";
                        cout<<"Sorry, you are only allowed 3 username and password login attempts.";
                        cout<<"\nDo you want return menu and try new register? [Y/N]: ";
                        cin>>newregister;

                        if(newregister == 'Y' || newregister == 'y')
                        {
                            attempts = 0;
                            system("cls");
                            return newregister;
                        }
                        else
                        {
                            attempts = 0;
                            system("cls");
                        }
                    }
                }
            } while(CheckCredentials(username,password) != true  && (newregister == 'N' || newregister == 'n'));
            return newregister;
        }

        char* getusername()
        {
            return username;
        }

        char* getpassword()
        {
            return password;
        }

        ~NewUser()
        {
            cout<<"Thank You "<<username<<" for using this system. Have a nice day."<<endl;
        }
};

// ========================================
// A.SORTING ALGORITHMS
// (KEPT ONLY: Date + Customer Name)
// ========================================

void bubbleSortByDate(BookingRecord bookings[], int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(strcmp(bookings[j].date, bookings[j + 1].date) > 0)
            {
                BookingRecord temp = bookings[j];
                bookings[j] = bookings[j + 1];
                bookings[j + 1] = temp;
            }
        }
    }
}

void selectionSortByName(BookingRecord bookings[], int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for(int j = i + 1; j < size; j++)
        {
            if(strcmp(bookings[j].customerName, bookings[minIndex].customerName) < 0)
            {
                minIndex = j;
            }
        }

        if(minIndex != i)
        {
            BookingRecord temp = bookings[i];
            bookings[i] = bookings[minIndex];
            bookings[minIndex] = temp;
        }
    }
}

void sortBookings(char* currentUsername)
{
    BookingRecord bookings[100];
    int count = 0;

    ifstream fin("bookings.txt");
    if(!fin)
    {
        cout << "\n\t\tNo bookings found!" << endl;
        cout << "\n\t\tPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    while(fin >> bookings[count].bookingID >> bookings[count].customerName
          >> bookings[count].date >> bookings[count].time
          >> bookings[count].tableNumber >> bookings[count].numberOfGuests
          >> bookings[count].phoneNumber >> bookings[count].status)
    {
        if(strcmp(bookings[count].customerName, currentUsername) == 0)
        {
            count++;
        }
    }
    fin.close();

    if(count == 0)
    {
        cout << "\n\t\tYou have no bookings to sort!" << endl;
        cout << "\n\t\tPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    int sortChoice;
    cout << "\n\t\t========================================" << endl;
    cout << "\t\t       SORT BOOKINGS                    " << endl;
    cout << "\t\t========================================" << endl;
    cout << "\t\t1. Sort by Date (Ascending)" << endl;
    cout << "\t\t2. Sort by Customer Name (Ascending)" << endl;
    cout << "\t\t3. Back to Menu" << endl;
    cout << "\t\t========================================" << endl;
    cout << "\t\tEnter your choice: ";
    cin >> sortChoice;

    system("cls");

    switch(sortChoice)
    {
        case 1:
            bubbleSortByDate(bookings, count);
            cout << "\n\t\tBookings sorted by Date!" << endl;
            break;
        case 2:
            selectionSortByName(bookings, count);
            cout << "\n\t\tBookings sorted by Customer Name!" << endl;
            break;
        case 3:
            return;
        default:
            cout << "\n\t\tInvalid choice!" << endl;
            return;
    }

    cout << "\n\t\t========================================" << endl;
    cout << "\t\t       SORTED BOOKING LIST              " << endl;
    cout << "\t\t========================================" << endl;

    for(int i = 0; i < count; i++)
    {
        cout << "\n\t\tBooking #" << i + 1 << endl;
        cout << "\t\t----------------------------------------" << endl;
        cout << "\t\tBooking ID      : " << bookings[i].bookingID << endl;
        cout << "\t\tCustomer Name   : " << bookings[i].customerName << endl;
        cout << "\t\tDate            : " << bookings[i].date << endl;
        cout << "\t\tTime            : " << bookings[i].time << endl;
        cout << "\t\tTable Number    : " << bookings[i].tableNumber << endl;
        cout << "\t\tNumber of Guests: " << bookings[i].numberOfGuests << endl;
        cout << "\t\tPhone Number    : " << bookings[i].phoneNumber << endl;
        cout << "\t\tStatus          : " << bookings[i].status << endl;
    }

    cout << "\n\t\tPress any key to continue...";
    cin.ignore();
    cin.get();
}

// ========================================
//  A.EDIT BOOKING FUNCTION
// ========================================

void editBooking(char* currentUsername)
{
    BookingRecord bookings[100];
    int count = 0;
    char searchID[20];
    int foundIndex = -1;

    ifstream fin("bookings.txt");
    if(!fin)
    {
        cout << "\n\t\tNo bookings found!" << endl;
        cout << "\n\t\tPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    while(fin >> bookings[count].bookingID >> bookings[count].customerName
          >> bookings[count].date >> bookings[count].time
          >> bookings[count].tableNumber >> bookings[count].numberOfGuests
          >> bookings[count].phoneNumber >> bookings[count].status)
    {
        count++;
    }
    fin.close();

    cout << "\n\t\t========================================" << endl;
    cout << "\t\t       YOUR BOOKINGS                    " << endl;
    cout << "\t\t========================================" << endl;

    int userBookingCount = 0;
    for(int i = 0; i < count; i++)
    {
        if(strcmp(bookings[i].customerName, currentUsername) == 0)
        {
            userBookingCount++;
            cout << "\n\t\tBooking ID: " << bookings[i].bookingID << endl;
            cout << "\t\tDate: " << bookings[i].date << " | Time: " << bookings[i].time << endl;
            cout << "\t\tTable: " << bookings[i].tableNumber << " | Guests: " << bookings[i].numberOfGuests << endl;
            cout << "\t\t----------------------------------------" << endl;
        }
    }

    if(userBookingCount == 0)
    {
        cout << "\n\t\tYou have no bookings to edit!" << endl;
        cout << "\n\t\tPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n\t\tEnter Booking ID to edit: ";
    cin >> searchID;

    for(int i = 0; i < count; i++)
    {
        if(strcmp(bookings[i].bookingID, searchID) == 0 &&
           strcmp(bookings[i].customerName, currentUsername) == 0)
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex == -1)
    {
        cout << "\n\t\tBooking not found or you don't have permission to edit it!" << endl;
        cout << "\n\t\tPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    system("cls");
    cout << "\n\t\t========================================" << endl;
    cout << "\t\t       EDIT BOOKING                     " << endl;
    cout << "\t\t========================================" << endl;
    cout << "\n\t\tCurrent Booking Details:" << endl;
    cout << "\t\t----------------------------------------" << endl;
    cout << "\t\t1. Date            : " << bookings[foundIndex].date << endl;
    cout << "\t\t2. Time            : " << bookings[foundIndex].time << endl;
    cout << "\t\t3. Table Number    : " << bookings[foundIndex].tableNumber << endl;
    cout << "\t\t4. Number of Guests: " << bookings[foundIndex].numberOfGuests << endl;
    cout << "\t\t5. Phone Number    : " << bookings[foundIndex].phoneNumber << endl;
    cout << "\t\t========================================" << endl;

    int editChoice;
    cout << "\n\t\tWhat would you like to edit?" << endl;
    cout << "\t\t1. Date" << endl;
    cout << "\t\t2. Time" << endl;
    cout << "\t\t3. Table Number" << endl;
    cout << "\t\t4. Number of Guests" << endl;
    cout << "\t\t5. Phone Number" << endl;
    cout << "\t\t6. Edit All Fields" << endl;
    cout << "\t\t7. Cancel" << endl;
    cout << "\t\t----------------------------------------" << endl;
    cout << "\t\tEnter your choice: ";
    cin >> editChoice;

    cin.ignore();

    switch(editChoice)
    {
        case 1:
            cout << "\n\t\tEnter new date (DD/MM/YYYY): ";
            cin >> bookings[foundIndex].date;
            break;
        case 2:
            cout << "\n\t\tEnter new time (HH:MM): ";
            cin >> bookings[foundIndex].time;
            break;
        case 3:
            cout << "\n\t\tEnter new table number: ";
            cin >> bookings[foundIndex].tableNumber;
            break;
        case 4:
            cout << "\n\t\tEnter new number of guests: ";
            cin >> bookings[foundIndex].numberOfGuests;
            break;
        case 5:
            cout << "\n\t\tEnter new phone number: ";
            cin >> bookings[foundIndex].phoneNumber;
            break;
        case 6:
            cout << "\n\t\tEnter new date (DD/MM/YYYY): ";
            cin >> bookings[foundIndex].date;
            cout << "\t\tEnter new time (HH:MM): ";
            cin >> bookings[foundIndex].time;
            cout << "\t\tEnter new table number: ";
            cin >> bookings[foundIndex].tableNumber;
            cout << "\t\tEnter new number of guests: ";
            cin >> bookings[foundIndex].numberOfGuests;
            cout << "\t\tEnter new phone number: ";
            cin >> bookings[foundIndex].phoneNumber;
            break;
        case 7:
            return;
        default:
            cout << "\n\t\tInvalid choice!" << endl;
            return;
    }

    ofstream fout("bookings.txt");
    for(int i = 0; i < count; i++)
    {
        fout << bookings[i].bookingID << " " << bookings[i].customerName << " "
             << bookings[i].date << " " << bookings[i].time << " "
             << bookings[i].tableNumber << " " << bookings[i].numberOfGuests << " "
             << bookings[i].phoneNumber << " " << bookings[i].status << "\n";
    }
    fout.close();

    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tBooking Updated Successfully!" << endl;
    cout << "\n\t\tPress any key to continue...";
    cin.get();
}

// ========================================
// A.RECEIPT GENERATION
// ========================================

void generateReceipt(char* currentUsername)
{
    BookingRecord bookings[100];
    int count = 0;
    char searchID[20];
    int foundIndex = -1;

    ifstream fin("bookings.txt");
    if(!fin)
    {
        cout << "\n\t\tNo bookings found!" << endl;
        cout << "\n\t\tPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    while(fin >> bookings[count].bookingID >> bookings[count].customerName
          >> bookings[count].date >> bookings[count].time
          >> bookings[count].tableNumber >> bookings[count].numberOfGuests
          >> bookings[count].phoneNumber >> bookings[count].status)
    {
        count++;
    }
    fin.close();

    cout << "\n\t\t========================================" << endl;
    cout << "\t\t    GENERATE RECEIPT                    " << endl;
    cout << "\t\t========================================" << endl;

    int userBookingCount = 0;
    for(int i = 0; i < count; i++)
    {
        if(strcmp(bookings[i].customerName, currentUsername) == 0)
        {
            userBookingCount++;
            cout << "\n\t\tBooking ID: " << bookings[i].bookingID << endl;
            cout << "\t\tDate: " << bookings[i].date << " | Time: " << bookings[i].time << endl;
            cout << "\t\t----------------------------------------" << endl;
        }
    }

    if(userBookingCount == 0)
    {
        cout << "\n\t\tYou have no bookings!" << endl;
        cout << "\n\t\tPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n\t\tEnter Booking ID for receipt: ";
    cin >> searchID;

    for(int i = 0; i < count; i++)
    {
        if(strcmp(bookings[i].bookingID, searchID) == 0 &&
           strcmp(bookings[i].customerName, currentUsername) == 0)
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex == -1)
    {
        cout << "\n\t\tBooking not found!" << endl;
        cout << "\n\t\tPress any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    double depositAmount = bookings[foundIndex].numberOfGuests * 50.0;

    system("cls");
    cout << "\n\t\t========================================" << endl;
    cout << "\t\t    RESTAURANT BOOKING RECEIPT          " << endl;
    cout << "\t\t========================================" << endl;
    cout << "\n\t\tBooking ID      : " << bookings[foundIndex].bookingID << endl;
    cout << "\t\tCustomer Name   : " << bookings[foundIndex].customerName << endl;
    cout << "\t\tDate            : " << bookings[foundIndex].date << endl;
    cout << "\t\tTime            : " << bookings[foundIndex].time << endl;
    cout << "\t\tTable Number    : " << bookings[foundIndex].tableNumber << endl;
    cout << "\t\tNumber of Guests: " << bookings[foundIndex].numberOfGuests << endl;
    cout << "\t\tPhone Number    : " << bookings[foundIndex].phoneNumber << endl;
    cout << "\t\t----------------------------------------" << endl;
    cout << "\t\tDeposit Amount  : RM " << depositAmount << endl;
    cout << "\t\tStatus          : " << bookings[foundIndex].status << endl;
    cout << "\t\t========================================" << endl;
    cout << "\n\t\tThank you for your booking!" << endl;
    cout << "\t\tWe look forward to serving you." << endl;
    cout << "\t\t========================================" << endl;

    char receiptFilename[50];
    strcpy(receiptFilename, "receipt_");
    strcat(receiptFilename, searchID);
    strcat(receiptFilename, ".txt");

    ofstream receiptFile(receiptFilename);
    receiptFile << "========================================\n";
    receiptFile << "    RESTAURANT BOOKING RECEIPT          \n";
    receiptFile << "========================================\n\n";
    receiptFile << "Booking ID      : " << bookings[foundIndex].bookingID << "\n";
    receiptFile << "Customer Name   : " << bookings[foundIndex].customerName << "\n";
    receiptFile << "Date            : " << bookings[foundIndex].date << "\n";
    receiptFile << "Time            : " << bookings[foundIndex].time << "\n";
    receiptFile << "Table Number    : " << bookings[foundIndex].tableNumber << "\n";
    receiptFile << "Number of Guests: " << bookings[foundIndex].numberOfGuests << "\n";
    receiptFile << "Phone Number    : " << bookings[foundIndex].phoneNumber << "\n";
    receiptFile << "----------------------------------------\n";
    receiptFile << "Deposit Amount  : RM " << depositAmount << "\n";
    receiptFile << "Status          : " << bookings[foundIndex].status << "\n";
    receiptFile << "========================================\n";
    receiptFile << "\nThank you for your booking!\n";
    receiptFile << "We look forward to serving you.\n";
    receiptFile << "========================================\n";
    receiptFile.close();

    cout << "\n\t\tReceipt saved to: " << receiptFilename << endl;
    cout << "\n\t\tPress any key to continue...";
    cin.ignore();
    cin.get();
}

// ========================================
// STORE CLASS
// ========================================

class Store
{
    private:
        NewUser *U;
    public:
        Store(NewUser *user)
        {
            U = user;
        }

        void DisplaystoreMenu()
        {
            cout<<"-------------------------------------------------------------------"<<endl;
            cout<<"Welcome "<<U->getusername()<<" Restaurant Booking Management System"<<endl;
            cout<<"-------------------------------------------------------------------"<<endl;
            cout<<"                             1. Display Bookings                   "<<endl;
            cout<<"                             2. Sort Bookings                      "<<endl;
            cout<<"                             3. Edit Booking                       "<<endl;
            cout<<"                             4. Generate Receipt                   "<<endl;
            cout<<"                             5. Log Out                            "<<endl;
            cout<<"                             6. Exit                               "<<endl;
            cout<<"-------------------------------------------------------------------"<<endl;
        }
};

// ========================================
// MAIN FUNCTION
// ========================================

int main()
{
    char choice, conti;
    NewUser *C = new NewUser();
    Store S(C);
    int choice1;

    do
    {
        do
        {
            system("cls");
            setColor(7);
            cout<<"------------------------------------------------------"<<endl;
            cout<<"                       WELCOME                        "<<endl;
            cout<<"------------------------------------------------------"<<endl;
            cout<<"                   A. Login Account                   "<<endl;
            cout<<"                   B. Register Account                "<<endl;
            cout<<"                   C. Admin Login                     "<<endl;
            cout<<"                   D. Exit                            "<<endl;
            cout<<"------------------------------------------------------"<<endl;
            cout<<"Enter your choice : ";
            fflush(stdin);
            cin>>choice;
            system("cls");

            if(choice == 'A' || choice == 'a')
            {
                conti = C->Checklogin();
            }
            else if(choice == 'B' || choice == 'b')
            {
                C->registeruser();
                conti = C->Checklogin();
            }
            else if(choice == 'C' || choice == 'c')
            {
                cout<<"\n\t\tAdmin module - under development by Shia Sheng Long & Yam Chee Fai"<<endl;
                Sleep(3000);
            }
            else if(choice == 'D' || choice == 'd')
            {
                cout<<"Thank You for your services. Have a nice day."<<endl;
                delete C;
                exit(0);
            }
            else
            {
                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease re-enter your valid choice."<<endl;
                Sleep(3000);
            }
        } while((choice != 'A' && choice != 'a' && choice != 'B' && choice != 'b') || conti == 'Y' || conti == 'y');

        do
        {
            system("cls");
            setColor(7);
            S.DisplaystoreMenu();
            cout<<"Enter your choice : ";
            cin>>choice1;

            if(choice1 == 1)
            {
                cout<<"\n\t\tDisplay Bookings - under development by Darrshan"<<endl;
                Sleep(3000);
            }
            else if(choice1 == 2)
            {
                sortBookings(C->getusername());
            }
            else if(choice1 == 3)
            {
                editBooking(C->getusername());
            }
            else if(choice1 == 4)
            {
                generateReceipt(C->getusername());
            }
            else if(choice1 == 5)
            {
                system("cls");
                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
                Sleep(1000);
                cout<<".";
                Sleep(1000);
                cout<<".";
                Sleep(1000);
                cout<<".";
                Sleep(1000);
                system("cls");

                setColor(10);
                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLog Out Successfully.";
                Sleep(3000);
            }
            else if(choice1 == 6)
            {
                system("cls");
                cout<<"Thank You for using this system. Have a nice day."<<endl;
                delete C;
                exit(0);
            }
            else
            {
                system("cls");
                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease re-enter your valid choice."<<endl;
                Sleep(3000);
            }
        } while (choice1 != 5 && choice1 != 6);

    } while(choice1 == 5);

    delete C;
    return 0;

}
