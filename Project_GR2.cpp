#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <conio.h>
using namespace std;

// ==================== COLOR FUNCTION ====================
void setColor(int color) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ==================== CUSTOM EXCEPTIONS ====================
class FileNotFoundException 
{
	public:
		    const char* what() 
			{ 
				return "File not found!"; 
			}
};

class InvalidInputException 
{
	public:
    		const char* what() 
			{ 
				return "Invalid input provided!"; 
			}
};

class BookingConflictException 
{
	public:
    		const char* what() 
			{ 
				return "Booking slot already taken!"; 
			}
};

class InvalidTableException 
{
	public:
    		const char* what() 
			{ 
				return "Invalid table number (1-10 only)!"; 
			}
};

// ==================== REGISTRATION & LOGIN CLASSES ====================
class Register 
{
	protected:
    			char newusername[100], newpassword[100], username[100], password[100], ch, newregister;
};

class NewUser : public Register 
{
	private:
		    char confirmpassword[100];
		    int c, d, a, attempts;
    
	public:
    		NewUser() 
			{
		        c = 0;
		        d = 0;
		        a = 0;
		        attempts = 0;
		        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t~~Welcome to the Restaurant Booking Management System~~";
		        Sleep(3000);
		        system("cls");
    		}
    
   			bool CheckCredentials(string user, string pass) 
			{
		        string u, p;
		        ifstream f;
		        f.open("login in.txt");
		        
		        if (!f) 
				{
		            cout<<"Unable to open file!\n";
		            return false;
		        }
		        
		        while (f >> u >> p) 
				{
		            if (u == user && p == pass) 
					{
		                f.close();
		                return true;
		            }
		        }
		        f.close();
		        return false;
		    }
    
		    bool checkUsernameExists(string user) 
			{
		        ifstream fin("login in.txt");
		        string u, p;
		        while (fin >> u >> p) 
				{
		            if (u == user) 
					{
		                fin.close();
		                return true;
		            }
		        }
		        fin.close();
		        return false;
		    }
    
    		void registeruser() 
			{
        		bool test = false;
        		do 
				{
		            c = 0;
		            d = 0;
		            system("cls");
		            cout<<"------------------------------------------------------"<<endl;
		            cout<<"                    REGISTER ACCOUNT                  "<<endl;
		            cout<<"------------------------------------------------------"<<endl;
		            cout<<"Enter your new username : ";
		            cin.ignore();
		            cin>>newusername;
		            
		            if (checkUsernameExists(newusername)) 
					{
		                system("cls");
		                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tThis account has been registered before, please register another one, thank you."<<endl;
		                Sleep(3000);
		                system("cls");
		                continue;
		            }
		            
		            while (strlen(newusername) < 6 || strlen(newusername) > 15) 
					{
		                cout<<"Username must be between 6 - 15 characters. Please re-enter: ";
		                cin.ignore();
		                cin>>newusername;
		                
		                if (checkUsernameExists(newusername)) 
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
							else if (newpassword) 
							{
		                    	newpassword[c++] = ch;
		                    	putchar('*');
		                	}
		            }
		            newpassword[c] = '\0';
		            
		            while (strlen(newpassword) < 4 || strlen(newpassword) > 8) 
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
		            
		            while (strcmp(newpassword, confirmpassword) != 0) 
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
		            fout.open("login in.txt", ios::app);
		            fout<<newusername<<" "<<newpassword<<"\n";
		            fout.close();
		            
		            // Also save to users.txt for compatibility
		            ofstream userFile;
		            userFile.open("users.txt", ios::app);
		            userFile<<newusername<<" "<<newpassword<<" "<<newusername<<" 0000000000\n";
		            userFile.close();
		            
		            test = true;
		            
		        } while (!test);
		        
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
		        setColor(7);
		    }
    
		    char Checklogin() 
			{
		        do 
				{
		            a = 0;
		            setColor(7);
		            newregister = '\0';
		            system("cls");
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
							else if (password) 
							{
			                    password[a++] = ch;
			                    putchar('*');
		                	}
		            }
		            password[a] = '\0';
		            system("cls");
		            
		            bool checking = CheckCredentials(username, password);
		            if (checking) 
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
		                setColor(7);
		            } 
						else 
						{
			                while (!checking && (attempts <= 2)) 
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
			                    cout<<"Username and Password Attempt No.:" << attempts + 1;
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
										else if (password) 
										{
				                            password[a++] = ch;
				                            putchar('*');
			                        	}
			                    }
			                    password[a] = '\0';
			                    attempts++;
			                    
			                    checking = CheckCredentials(username, password);
			                    
			                    if (checking) 
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
		                
			                if (!checking && attempts > 2) 
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
			                    
			                    if (newregister == 'Y' || newregister == 'y') 
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
		        } while (CheckCredentials(username, password) != true && (newregister == 'N' || newregister == 'n'));
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

// ==================== STRUCT DEFINITIONS ====================
struct BookingData 
{
    int bookingID;
    char username[50];
    int tableNumber;
    char date[11];
    int timeSlot;
    char phone[15];
    char status[20];
};

struct MenuItem 
{
    string itemID, itemName, category;
    float price;
};

struct Feedback 
{
    int feedbackID;
    char username[50];
    int rating;
    char comment[500];
    char date[11];
};

struct UserData 
{
    char username[50];
    char password[50];
    char fullName[100];
    char phone[15];
};

struct node
{
    string product_ID, product_name, category;
    float product_price;
    node *next;
};

struct Product
{
	string product_ID, product_name, category;
    float product_price;
};

class LinkedList
{
	protected:
				string newname, pi, product_i, pn, product_n, newcategory, pc, product_c;
				float newprice, pp = 0.00, product_p;
				int filedisplay = 0, p, count;
				bool whi, found, insfound, updfound, delfound, same, changes, exsits;
				node *temp, *head, *prev, *tail; 
				Product *P;
				ifstream f;

	public:
			LinkedList()
			{
				resetbase();
			}
			
			void resetbase()
			{
				newname = "";               
			    newprice = 0.0;
			    newcategory = "";
			    whi = false;
			    found = false;
			    insfound = false;
			    updfound = false;
				delfound = false;
				same = false;
			    changes = false;
			    exsits = false;
			    pi = "";
				product_i = "";
				pn = "";
				product_n = "";
			    pp = 0.00;
				product_p = 0.00;
				pc = "";
				product_c = ""; 
			    filedisplay = 0;
				p = 0;
			}
			
			void displayFile()
			{
				//Display the All Product from the txt file
				cout<<"\n--------------------------------------------------------------------------------------"<<endl;
				cout<<"        Product ID           Product Name          Product Price           Category   "<<endl;
				cout<<"--------------------------------------------------------------------------------------"<<endl;
				count = 0;	
				while(f >> pi >> pn >> pp >> pc)
				{ 
					cout<<setw(14)<<pi<<setw(26)<<pn<<setw(17)<<"RM "<<pp<<setw(19)<<pc<<endl;
					if(filedisplay == 0)
					{
					    head = new node;
					    head->next = NULL;
					    head->product_ID = pi;
					    head->product_name = pn;            
					    head->product_price = pp;
					    head->category = pc;
					    tail = head;      
					}
					    if(filedisplay >= 1)
					    {
						    temp = new node;
						    temp->product_ID = pi;
						    temp->product_name = pn;            
						    temp->product_price = pp;
						    temp->category = pc;
						    temp->next = NULL;
						    tail->next = temp;
						    tail = temp;  
						}
					filedisplay++;
					count++;
				}
				cout<<"--------------------------------------------------------------------------------------"<<endl;
			}
			
			void display_File1()
			{
				//Display the All Product from the txt file
				cout<<"\n--------------------------------------------------------------------------------------"<<endl;
				cout<<"        Product ID           Product Name          Product Price           Category   "<<endl;
				cout<<"--------------------------------------------------------------------------------------"<<endl;
				P = new Product[count];
				int i = 0;
				while(f >> pi >> pn >> pp >> pc)
				{ 
					cout<<setw(14)<<pi<<setw(26)<<pn<<setw(17)<<"RM "<<pp<<setw(19)<<pc<<endl;
					if(i < count)
					{
						P[i].product_ID = pi;
						P[i].product_name = pn;
						P[i].product_price = pp;
						P[i].category = pc;	
						i++;
					}
				}
				cout<<"--------------------------------------------------------------------------------------"<<endl;
								
				if(count == 0)
				{
					return;
				}							
			}
			
			void displayvalue()
			{
				P = new Product[count];
				int i = 0;
				while(f >> pi >> pn >> pp >> pc)
				{ 
					if(i < count)
					{
						P[i].product_ID = pi;
						P[i].product_name = pn;
						P[i].product_price = pp;
						P[i].category = pc;	
						i++;
					}
				}
								
				if(count == 0)
				{
					return;
				}					
			}
			
			void display()
			{
				temp = head;
				cout<<"--------------------------------------------------------------------------------------"<<endl;
				cout<<"        Product ID           Product Name          Product Price           Category   "<<endl;
				cout<<"--------------------------------------------------------------------------------------"<<endl;
																	                    
				while(temp != NULL && exsits != true)
				{
					cout<<setw(14)<<temp->product_ID<<setw(26)<<temp->product_name<<setw(17)<<"RM "<<temp->product_price<<setw(19)<<temp->category<<endl;
					temp = temp->next;
				}
				cout<<"--------------------------------------------------------------------------------------"<<endl;
			}
			
			void display1()
			{
				temp = head;
				cout<<"\n--------------------------------------------------------------------------------------"<<endl;
				cout<<"        Product ID           Product Name          Product Price           Category   "<<endl;
				cout<<"--------------------------------------------------------------------------------------"<<endl;
				while(temp != NULL)
				{
					cout<<setw(14)<<temp->product_ID<<setw(26)<<temp->product_name<<setw(17)<<"RM "<<temp->product_price<<setw(19)<<temp->category<<endl;
					temp = temp->next;
				}
				cout<<"--------------------------------------------------------------------------------------"<<endl;
			}

			void display2()
			{
				cout<<"--------------------------------------------------------------------------------------"<<endl;
				cout<<"        Product ID           Product Name          Product Price           Category   "<<endl;
				cout<<"--------------------------------------------------------------------------------------"<<endl;
				for(int i=0;i<count;i++)
				{																		                    
					cout<<setw(14)<<P[i].product_ID<<setw(26)<<P[i].product_name<<setw(17)<<"RM "<<P[i].product_price<<setw(19)<<P[i].category<<endl;
				}
				cout<<"--------------------------------------------------------------------------------------"<<endl;
			}
};

class InsertionSort
{
	private:
			Product current;
		 	int j, answer;
		 	bool condition;

	public:		
			int categoryOrder(char c) 
			{
			    c = toupper(c);
			    if (c == 'M') 
			    {
					return 0;
				}
			    	else if (c == 'S') 
			    	{				
						return 1;
					}
			    		else if (c == 'D') 
			    		{					
							return 2;
						}
			    			else if (c == 'P') 
			    			{
								return 3;
							}
								else
								{			
			    					return 9;
			    				}
			}

			void insertionSortById_Asc(Product *array, int MAX)
			{
				for (int i=1;i<MAX;i++)
			    {
			        current = array[i];
			        j = i;
			
			        while ((j > 0) && (current.product_ID < array[j-1].product_ID))
			        {
						array[j] = array[j-1];
						j--;
						array[j] = current;
			        }			
			    }
			}
			
			void insertionSortById_Desc(Product *array, int MAX)
			{
				for (int i=1;i<MAX;i++)
			    {
			        current = array[i];
			        j = i;
			
			        while ((j > 0) && (current.product_ID > array[j-1].product_ID))
			        {
						array[j] = array[j-1];
						j--;
						array[j] = current;
			        }			
			    }
			}
						
			void insertionSortByName_Asc(Product *array, int MAX)
			{
			    for (int i=1;i<MAX;i++)
			    {
			        current = array[i];
			        j = i;
			
			        while ((j>0) && (current.product_name < array[j-1].product_name))
			        {
			            array[j] = array[j - 1]; 
			            j--;
			            array[j] = current;
			        }			
			    }		    
			}
			
			void insertionSortByName_Desc(Product *array, int MAX)
			{
			    for (int i=1;i<MAX;i++)
			    {
			        current = array[i];
			        j = i;
			
			        while((j>0) && (current.product_name > array[j-1].product_name))
					{
			            array[j] = array[j - 1]; 
			            j--;
			            array[j] = current;
			        }			
			    }			    
			}
									
			void insertionSortByPrice_Asc(Product *array, int MAX)
			{
			    for (int i=1;i<MAX;i++)
			    {
			        current = array[i];
			        j = i;
			
			        while ((j>0) && (current.product_price < array[j-1].product_price))
			        {
			            array[j] = array[j - 1]; 
			            j--;
			            array[j] = current;
			        }			
			    }
			}	

			void insertionSortByPrice_Desc(Product *array, int MAX)
			{	
				for (int i=1;i<MAX;i++)
			    {
			        current = array[i];
			        j = i;
			
			        while((j>0) && (current.product_price > array[j-1].product_price))
			        {
			            array[j] = array[j - 1]; 
			            j--;
			            array[j] = current;
			        }			
			    }
			}
				
			void insertionSortByCategory(Product *array, int MAX)
			{								
				for(int i=1;i<MAX;i++)
			    {
			        current = array[i];
			        j = i;
			    
			       	while(j > 0 && categoryOrder(current.category[0]) < categoryOrder(array[j-1].category[0])  || (categoryOrder(current.category[0]) == categoryOrder(array[j-1].category[0]) && (current.product_ID < array[j-1].product_ID)))
			       	{
						array[j] = array[j-1];
						j--;
						array[j] = current;			
					}
			    }
			}
};

class BinarySearch 
{
	private:
			int first, mid, last, found;
			
	public:
			int BinarySearchById(Product *array, int MAX, string target)
			{
				first = 0;
				last = MAX - 1;
				found = 0;
				
				while((found == 0) && (first <= last))
				{
					mid = (first + last) / 2;
					
					if(target == array[mid].product_ID)
					{
						found = 1;
					}
						else
						{
							if(target < array[mid].product_ID)
							{
								last = mid - 1;
							}
								else
								{
									first = mid + 1;
								}
						}
				}
				
				if(found)
				{
					return mid;	
				}
					else
					{
						return -1;
					}
			}

			int BinarySearchByName(Product *array, int MAX, string target)
			{
				first = 0;
				last = MAX - 1;
				found = 0;
				
				while((found == 0) && (first <= last))
				{
					mid = (first + last) / 2;
					
					if(target == array[mid].product_name)
					{
						found = 1;
					}
						else
						{
							if(target < array[mid].product_name)
							{
								last = mid - 1;
							}
								else
								{
									first = mid + 1;
								}
						}
				}
				
				if(found)
				{
					return mid;	
				}
					else
					{
						return -1;
					}
			}
};

// ==================== QUEUE IMPLEMENTATION ====================
class WaitingQueue 
{
	private:
		    struct QueueNode 
			{
		        char username[50];
		        int tableNumber;
		        char date[11];
		        int timeSlot;
		        QueueNode* next;
		    };
    QueueNode* front;
    QueueNode* rear;
    int size;

	public:
		    WaitingQueue() 
			{
		        front = NULL;
		        rear = NULL;
		        size = 0;
		    }

		    ~WaitingQueue() 
			{
		        while (front != NULL) 
				{
		            QueueNode* temp = front;
		            front = front->next;
		            delete temp;
		        }
		    }

		    void enqueue(const char* user, int table, const char* dt, int slot) 
			{
		        QueueNode* newNode = new QueueNode;
		        strcpy(newNode->username, user);
		        newNode->tableNumber = table;
		        strcpy(newNode->date, dt);
		        newNode->timeSlot = slot;
		        newNode->next = NULL;
		
		        if (rear == NULL) 
				{
		            front = rear = newNode;
		        } 
					else 
					{
			            rear->next = newNode;
			            rear = newNode;
		        	}
		        size++;
		    }

		    bool dequeue(char* user, int& table, char* dt, int& slot) 
			{
		        if (front == NULL) 
				{
					return false;
				}
		
		        QueueNode* temp = front;
		        strcpy(user, front->username);
		        table = front->tableNumber;
		        strcpy(dt, front->date);
		        slot = front->timeSlot;
		
		        front = front->next;
		        if (front == NULL) 
				{
					rear = NULL;
				}	
		        delete temp;
		        size--;
		        return true;
		    }

		    bool isEmpty() 
			{
		        return front == NULL;
		    }

		    int getSize() 
			{
		        return size;
		    }

		    void display() 
			{
		        if (isEmpty()) 
				{
		            cout<<"Waiting queue is empty.\n";
		            return;
		        }
		        QueueNode* temp = front;
		        int pos = 1;
		        cout<<"\n=== WAITING QUEUE ===\n";
		        while (temp != NULL) 
				{
		            cout<<pos++<<". "<<temp->username<<" | Table: "<<temp->tableNumber<<" | Date: "<<temp->date<<" | Slot: "<<temp->timeSlot<<"\n";
		            temp = temp->next;
		        }
		    }
};



// ==================== HASH TABLE IMPLEMENTATION ====================
class HashTable 
{
	private:
		    static const int TABLE_SIZE = 100;
		    
		    struct HashNode 
			{
		        char key[50];
		        int value;
		        HashNode* next;
		    };
    
    		HashNode* table[TABLE_SIZE];

		    int hashFunction(const char* key) 
			{
		        int hash = 0;
		        for (int i = 0; key[i] != '\0'; i++) 
				{
		            hash = (hash * 31 + key[i]) % TABLE_SIZE;
		        }
		        return hash;
		    }

			public:
				    HashTable() 
					{
				        for (int i = 0; i < TABLE_SIZE; i++) 
						{
				            table[i] = NULL;
				        }
				    }

				    ~HashTable() 
					{
				        for (int i = 0; i < TABLE_SIZE; i++) 
						{
				            HashNode* current = table[i];
				            while (current != NULL) 
							{
				                HashNode* temp = current;
				                current = current->next;
				                delete temp;
				            }
				        }
				    }

				    void insert(const char* key, int value) 
					{
				        int index = hashFunction(key);
				        HashNode* newNode = new HashNode;
				        strcpy(newNode->key, key);
				        newNode->value = value;
				        newNode->next = table[index];
				        table[index] = newNode;
				    }

				    bool search(const char* key, int& value) 
					{
				        int index = hashFunction(key);
				        HashNode* current = table[index];
				        
				        while (current != NULL) 
						{
				            if (strcmp(current->key, key) == 0) 
							{
				                value = current->value;
				                return true;
				            }
				            current = current->next;
				        }
				        return false;
				    }

				    bool remove(const char* key) 
					{
				        int index = hashFunction(key);
				        HashNode* current = table[index];
				        HashNode* prev = NULL;
				
				        while (current != NULL) 
						{
				            if (strcmp(current->key, key) == 0) 
							{
				                if (prev == NULL) 
								{
				                    table[index] = current->next;
				                } 
									else 
									{
				                    	prev->next = current->next;
				                	}
				                delete current;
				                return true;
				            }
				            prev = current;
				            current = current->next;
				        }
				        return false;
				    }
};

// ==================== BASE CLASSES ====================
class User 
{
	protected:
			    char username[50];
			    char password[50];

	public:
		    User() 
			{		    	
		        strcpy(username, "");
		        strcpy(password, "");
		    }

    		virtual ~User() {}
    		virtual void displayMenu() {};

		    void setUsername(const char* user) 
			{
		        strcpy(username, user);
		    }

		    void setPassword(const char* pass) 
			{
		        strcpy(password, pass);
		    }

		    const char* getUsername() 
			{
		        return username;
		    }
};

class Record 
{
	protected:
		    int recordID;
		    char date[11];
	
	public:
		    Record() 
			{
		        recordID = 0;
		        strcpy(date, "");
		    }
		
		    virtual ~Record() {}	
		    virtual void display() {}
		    virtual void save() {}
		
		    int getRecordID() 
			{
		        return recordID;
		    }
};

// ==================== DERIVED CLASSES ====================
class Customer : public User 
{
	private:
		    char fullName[100];
		    char phone[15];

	public:
		    Customer() : User() 
			{
		        strcpy(fullName, "");
		        strcpy(phone, "");
		    }
		
		    ~Customer() {}
		
		    void setFullName(const char* name) 
			{
		        strcpy(fullName, name);
		    }
		
		    void setPhone(const char* ph) 
			{
		        strcpy(phone, ph);
		    }
		
		    const char* getFullName() 
			{
		        return fullName;
		    }
		
		    const char* getPhone() 
			{
		        return phone;
		    }
		
		    void displayMenu();
		    void addBooking();
		    void editBooking();
		    void deleteBooking();
		    void viewBookings();
		    void searchBooking();
		    void sortMyBookings();
		    void addFeedback();
		    void viewMenu();
		    void generateReport();	
		    friend void validatePhone(Customer& c);
		    friend void displayCustomerInfo(Customer& c);
};

class Admin : public User, public LinkedList 
{
	private:
	    	char employeeID[20];

	public:
		    Admin() : User() 
			{
		        strcpy(employeeID, "ADMIN001");
		    }
		
		    ~Admin() {}
			
			void resetAll()
			{
				resetbase();
			}
			
		    void displayMenu();
		    void viewAllBookings();
		    void searchBooking();
		    void manageMenu();
		    void viewFeedback();
		    void sortAllBookings();
		    void deleteBooking();
		    void generateReports();
		    void manageWaitingList();	
		    friend void grantAdminAccess(Admin& a);
};

class BookingRecord : public Record 
{
	private:
		    char customerUsername[50];
		    int tableNumber;
		    int timeSlot;
		    char phone[15];
		    char status[20];

	public:
		    BookingRecord() : Record() 
			{
		        strcpy(customerUsername, "");
		        tableNumber = 0;
		        timeSlot = 0;
		        strcpy(phone, "");
		        strcpy(status, "confirmed");
		    }
		
		    ~BookingRecord() {}
		
		    void display() 
			{
		        cout<<recordID<<" | "<<customerUsername<<" | Table: "<<tableNumber<<" | Date: "<<date<<" | Slot: "<<timeSlot<<" | "<<status<<"\n";
		    }
		
		    void save() 
			{
		        ofstream file("bookings.txt", ios::app);
		        if (file.is_open()) 
				{
		            file<<recordID<<" "<<customerUsername<<" "<<tableNumber<<" "<<date<<" "<<timeSlot<<" "<<phone<<" "<<status<<"\n";
		            file.close();
		        }
		    }
		
		    void setData(int id, const char* user, int table, const char* dt, int slot, const char* ph) 
			{
		        recordID = id;
		        strcpy(customerUsername, user);
		        tableNumber = table;
		        strcpy(date, dt);
		        timeSlot = slot;
		        strcpy(phone, ph);
		        strcpy(status, "confirmed");
		    }
		
		    friend void calculateTotalRevenue(BookingRecord& b);
		    friend bool checkAvailability(BookingRecord& b);
};

// ==================== GLOBAL VARIABLES ====================
WaitingQueue waitingQueue;
HashTable bookingHash;
int nextBookingID = 1001;

// ==================== HELPER FUNCTIONS ====================
void clearScreen() 
{
    system("cls");
}

void pauseScreen() 
{
    cout<<"\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void displayHeader(const char* title) 
{
    cout<<"\n";
    cout<<"========================================\n";
    cout<<"   "<<title << "\n";
    cout<<"========================================\n";
}

const char* getTimeSlotDisplay(int slot) 
{
    switch(slot) 
	{
        case 1:
				return "08:00-10:00";
        case 2: 
				return "10:00-12:00";
        case 3: 
				return "12:00-14:00";
        case 4: 
				return "14:00-16:00";
        case 5: 
				return "16:00-18:00";
        default: 
				return "Invalid";
    }
}

bool isValidDate(const char* date) 
{
    if (strlen(date) != 10) 
	{
		return false;
	}
	
    if (date[2] != '-' || date[5] != '-') 
	{
		return false;
	}
    
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    
    return (day >= 1 && day <= 31 && month >= 1 && month <= 12);
}

int countBookings() 
{
    ifstream file("bookings.txt");
    int count = 0;
    BookingData temp;
    
    while (file >> temp.bookingID >> temp.username >> temp.tableNumber >> temp.date >> temp.timeSlot >> temp.phone >> temp.status) 
	{
        count++;
    }
    file.close();
    return count;
}

int countMenuItems() 
{
    ifstream file("menu.txt");
    int count = 0;
    MenuItem temp;
    
    while (file >> temp.itemID >> temp.itemName >> temp.price >> temp.category) 
	{
        count++;
    }
    file.close();
    return count;
}

void loadBookingsToArray(BookingData*& bookings, int& size) 
{
    size = countBookings();
    if (size == 0) 
	{
        bookings = NULL;
        return;
    }

    bookings = new BookingData[size];
    ifstream file("bookings.txt");
    
    for (int i = 0; i < size; i++) 
	{
        file>>bookings[i].bookingID>>bookings[i].username>>bookings[i].tableNumber>>bookings[i].date>>bookings[i].timeSlot>>bookings[i].phone>>bookings[i].status;
    }
    file.close();
}

void saveBookingsFromArray(BookingData* bookings, int size) 
{
    ofstream file("bookings.txt");
    for (int i = 0; i < size; i++) 
	{
        file<<bookings[i].bookingID<<" "<<bookings[i].username<<" "<<bookings[i].tableNumber<<" "<<bookings[i].date<<" "<<bookings[i].timeSlot<<" "<<bookings[i].phone<<" "<<bookings[i].status<<"\n";
    }
    file.close();
}

// ==================== SORTING ALGORITHM (INSERTION SORT) ====================
int dateToInt(const char* d) 
{
    return (d[6]-'0')*10000000 + (d[7]-'0')*1000000 +(d[8]-'0')*100000 + (d[9]-'0')*10000 +(d[3]-'0')*1000 + (d[4]-'0')*100 + (d[0]-'0')*10 + (d[1]-'0');
}

void insertionSortby_date(BookingData *arr, int MAX)
{
	BookingData BD;
	int j;
	
	for(int i=1;i<MAX;i++)
	{
		BD = arr[i];
		j = i;
		
		int key = dateToInt(BD.date);
		while (j > 0 && key < dateToInt(arr[j-1].date))
		{
			arr[j] = arr[j-1];
			j--;
			arr[j] = BD;
		}
	}
}

void insertionSortby_tableNumber(BookingData *arr, int MAX)
{
	BookingData BD;
	int j;
			
	for(int i=1;i<MAX;i++)
	{
		BD = arr[i];
		j = i;
		
		while((j > 0) && (BD.tableNumber < arr[j-1].tableNumber))
		{
			arr[j] = arr[j-1];
			j--;
			arr[j] = BD;
		}
	}
}

void insertionSortby_timeSlot(BookingData *arr, int MAX)
{
	BookingData BD;
	int j;
	
	for(int i=1;i<MAX;i++)
	{
		BD = arr[i];
		j = i;
		
		while((j > 0) && (BD.timeSlot < arr[j-1].timeSlot))
		{
			arr[j] = arr[j-1];
			j--;
			arr[j] = BD;
		}
	}
}

void insertionSortby_bookingId(BookingData *arr, int MAX)
{
	BookingData BD;
	int j;
	
	for(int i=1;i<MAX;i++)
	{	
		BD = arr[i];
		j = i;
					
		while((j > 0) && (BD.bookingID < arr[j-1].bookingID))
		{
			arr[j] = arr[j-1];
			j--;
			arr[j] = BD;
		}
	}
}

int Min(BookingData *arr, int pos, int MAX)
{
	int i, index = pos;
	BookingData m;
	m = arr[pos];
	int key = dateToInt(m.date);
	for(i=pos+1;i<MAX;i++)
	{
		if(dateToInt(arr[i].date) < key)
		{
			m = arr[i];
			index = i;
		}
	}
	return index;
}

void SelectionSortby_date(BookingData *arr, int MAX)
{
	int i, k;
	BookingData temp;
	
	for(i=0;i<MAX;i++)
	{
		k = Min(arr,i,MAX);
		if(dateToInt(arr[k].date) < dateToInt(arr[i].date))
		{
			temp = arr[k];
			arr[k] = arr[i];
			arr[i] = temp;
		}
	}
}

int Min_2(BookingData *arr, int pos, int MAX)
{
	int i, index = pos;
	BookingData m;
	m = arr[pos];
	for(i=pos+1;i<MAX;i++)
	{
		if(arr[i].tableNumber < m.tableNumber)
		{
			m = arr[i];
			index = i;
		}
	}
	return index;
}

void SelectionSortby_tableNumber(BookingData *arr, int MAX)
{
	int i, k;
	BookingData temp;
	for(i=0;i<MAX;i++)
	{
		k = Min_2(arr,i,MAX);
		if(arr[k].tableNumber < arr[i].tableNumber)
		{
			temp = arr[k];
			arr[k] = arr[i];
			arr[i] = temp;
		}
	}
}

int Min_3(BookingData *arr, int pos, int MAX)
{
	int i, index = pos;
	BookingData m;
	m = arr[pos];
	for(i=pos+1;i<MAX;i++)
	{
		if(arr[i].bookingID < m.bookingID)
		{
			m = arr[i];
			index = i;
		}
	}
	return index;
}

void SelectionSortby_bookingId(BookingData *arr, int MAX)
{
	int i, k;
	BookingData temp;
	
	for(i=0;i<MAX;i++)
	{
		k = Min_3(arr,i,MAX);
		if(arr[k].bookingID < arr[i].bookingID)
		{
			temp = arr[k];
			arr[k] = arr[i];
			arr[i] = temp;
		}
	}
}

// Overloaded sorting functions
void sortBookings(BookingData arr[], int size)
{
	insertionSortby_date(arr, size);
}

void sortBookings(BookingData arr[], int size, int criteria)
{
	if(criteria == 1)
	{
		insertionSortby_date(arr, size);
	}
		else if(criteria == 2)
		{
			insertionSortby_tableNumber(arr, size);
		}
			else if(criteria == 3)
			{
				insertionSortby_timeSlot(arr, size);
			}
				else
				{
					insertionSortby_bookingId(arr, size);
				}
}

void sortBookings_2(BookingData arr[], int size)
{
	SelectionSortby_date(arr, size);
}

void sortBookings_2(BookingData arr[], int size, int criteria)
{
	if(criteria == 1)
	{
		SelectionSortby_date(arr, size);
	}
		else if(criteria == 2)
		{
			SelectionSortby_tableNumber(arr, size);
		}
			else
			{
				SelectionSortby_bookingId(arr, size);
			}
}

// ==================== SEARCHING ALGORITHM (BINARY SEARCH) ====================
int binarySearch(BookingData arr[], int size, int bookingID) 
{
    int mid;
    int first = 0;
    int last = size - 1;
    int found = 0;
	
    while ((found == 0) && (first <= last))
	{
        mid = (first + last) / 2;

        if (bookingID == arr[mid].bookingID)
        {
        	found = 1;
		}
			else
			{
				if(bookingID < arr[mid].bookingID)
				{
					last = mid - 1;
				}
					else
					{
						first = mid + 1;
					}
			}
    }
    
    if(found)
    {
    	return mid;
	}
		else
		{
			return -1;
		}
}

int binarySearch(BookingData arr[], int size, const char* username) 
{
    int mid;
    int first = 0;
    int last = size - 1;
    int found;

    while ((found == 0) && (first <= last))
	{
        mid = (first + last) / 2;

        if (username == arr[mid].username)
        {
        	found = 1;
		}
			else
			{
				if(username < arr[mid].username)
				{
					last = mid - 1;
				}
					else
					{
						first = mid + 1;
					}
			}
    }
    
    if(found)
    {
    	return mid;
	}
		else
		{
			return -1;
		}
}

//Overloaded search functions
int Search(BookingData arr[], int size, int bookingID) 
{
	return binarySearch(arr, size, bookingID);
}

int Search(BookingData arr[], int size, const char* username) 
{
    return binarySearch(arr, size, username);
}

// ==================== FRIEND FUNCTIONS ====================
void validatePhone(Customer& c) 
{
    while (strlen(c.phone) < 10 || strlen(c.phone) > 15) 
	{
        cout<<"Invalid phone number! Enter again (10-15 digits): ";
        cin>>c.phone;
    }
}

void displayCustomerInfo(Customer& c) 
{
    cout<<"\n=== CUSTOMER INFORMATION ===\n";
    cout<<"Username: " <<c.username<<"\n";
    cout<<"Full Name: "<<c.fullName<<"\n";
    cout<<"Phone: "<<c.phone<<"\n";
}

void grantAdminAccess(Admin& a) 
{
    cout<<"Admin access granted to: "<<a.username<<"\n";
    cout<<"Employee ID: "<<a.employeeID<<"\n";
}

void calculateTotalRevenue(BookingRecord& b) 
{
    cout<<"Revenue calculation for Booking ID: "<<b.recordID<<"\n";
}

bool checkAvailability(BookingRecord& b) 
{
    ifstream file("bookings.txt");
    BookingData temp;
    
    while (file >> temp.bookingID >> temp.username >> temp.tableNumber >> temp.date >> temp.timeSlot >> temp.phone >> temp.status) 
	{
        if (temp.tableNumber == b.tableNumber && strcmp(temp.date, b.date) == 0 && temp.timeSlot == b.timeSlot &&strcmp(temp.status, "confirmed") == 0) 
		{
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

// ==================== AUTHENTICATION FUNCTIONS ====================
bool customerLogin(Customer& customer, NewUser& loginSystem) 
{
    char result = loginSystem.Checklogin();
    
    if (result == 'Y' || result == 'y') 
	{
        return false; // Return to register
    }
    
    // Load customer data from users.txt
    ifstream file("users.txt");
    UserData temp;
    while (file >> temp.username >> temp.password >> temp.fullName >> temp.phone) 
	{
        if (strcmp(temp.username, loginSystem.getusername()) == 0) 
		{
            customer.setUsername(temp.username);
            customer.setPassword(temp.password);
            customer.setFullName(temp.fullName);
            customer.setPhone(temp.phone);
            file.close();
            return true;
        }
    }
    file.close();
    
    // If not found in users.txt, use login credentials
    customer.setUsername(loginSystem.getusername());
    customer.setPassword(loginSystem.getpassword());
    customer.setFullName(loginSystem.getusername());
    customer.setPhone("0000000000");
    return true;
}

bool adminLogin(Admin& admin) 
{
    clearScreen();
    int a = 0;
    char user[50], pass[50], ch;
    
    setColor(7);
    cout<<"------------------------------------------------------"<<endl;
    cout<<"                    ADMIN LOGIN                       "<<endl;
    cout<<"------------------------------------------------------"<<endl;
    cin.ignore();
    cout<<"Enter admin username : ";
    cin>>user;
    cout<<"Enter admin password : ";
    
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
			else if (pass) 
			{
	            pass[a++] = ch;
	            putchar('*');
        	}
    }
    pass[a] = '\0';
    
    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin132") == 0) 
	{
        admin.setUsername(user);
        admin.setPassword(pass);
        
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
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tAdmin Access Granted.";
        Sleep(3000);
        system("cls");
        setColor(7);
        
        grantAdminAccess(admin);
        pauseScreen();
        return true;
    }
    
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
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tInvalid admin credentials!";
    Sleep(3000);
    system("cls");
    setColor(7);
    
    pauseScreen();
    return false;
}

// ==================== CUSTOMER FUNCTIONS ====================
void Customer::displayMenu() 
{
    int choice;
    do 
	{
        clearScreen();
        displayHeader("CUSTOMER MENU");
        cout<<"Welcome, "<<fullName<<"!\n\n";
        cout<<"1. Add Booking\n";
        cout<<"2. Edit Booking\n";
        cout<<"3. Delete Booking\n";
        cout<<"4. View My Bookings\n";
        cout<<"5. Search Booking\n";
        cout<<"6. Sort Bookings\n";
        cout<<"7. Add Feedback\n";
        cout<<"8. View Menu\n";
        cout<<"9. Generate My Report\n";
        cout<<"0. Logout\n";
        cout<<"\nEnter choice: ";
        cin>>choice;
        
        switch(choice) 
		{
            case 1: 
					addBooking(); 
					break;
            case 2: 
					editBooking(); 
					break;
            case 3: 
					deleteBooking(); 
					break;
            case 4: 
					viewBookings(); 
					break;
            case 5: 
					searchBooking(); 
					break;
            case 6: 
					sortMyBookings(); 
					break;
            case 7: 
					addFeedback(); 
					break;
            case 8: 
					viewMenu(); 
					break;
            case 9: 
					generateReport(); 
					break;
            case 0: 
					cout<<"Logging out...\n"; 
					pauseScreen(); 
					break;
            default: 
					cout<<"Invalid choice!\n"; 
					pauseScreen();
        }
    } while(choice != 0);
}

void Customer::addBooking() 
{
    clearScreen();
    displayHeader("ADD NEW BOOKING");
    
    BookingRecord booking;
    int table, slot;
    char dt[11], ph[15], confirm;
    
    try 
	{
        cout<<"Available Tables: 1-10\n";
        cout<<"Enter table number: ";
        cin>>table;
        
        if (table < 1 || table > 10) 
		{
            throw InvalidTableException();
        }
        
        cout<<"\nEnter date (DD-MM-YYYY): ";
        cin>>dt;
        
        if (!isValidDate(dt)) 
		{
            throw InvalidInputException();
        }
        
        cout<<"\nTime Slots:\n";
        cout<<"1. 08:00-10:00\n";
        cout<<"2. 10:00-12:00\n";
        cout<<"3. 12:00-14:00\n";
        cout<<"4. 14:00-16:00\n";
        cout<<"5. 16:00-18:00\n";
        cout<<"Enter time slot (1-5): ";
        cin>>slot;
        
        if (slot < 1 || slot > 5) 
		{
            throw InvalidInputException();
        }
        
        cout<<"Enter phone number: ";
        cin>>ph;
        
        booking.setData(nextBookingID, username, table, dt, slot, ph);
        
        if (!checkAvailability(booking)) 
		{
            throw BookingConflictException();
        }
        
        cout<<"\n=== BOOKING SUMMARY ===\n";
        cout<<"Table: "<<table<<"\n";
        cout<<"Date: "<<dt<<"\n";
        cout<<"Time: "<<getTimeSlotDisplay(slot)<<"\n";
        cout<<"Phone: "<<ph<<"\n";
        cout<<"\nConfirm booking? (y/n): ";
        cin>>confirm;
        
        if (confirm == 'y' || confirm == 'Y') 
		{
            booking.save();
            bookingHash.insert(username, nextBookingID);
            nextBookingID++;
            cout<<"\nBooking confirmed successfully!\n";
        } 
			else 
			{
            	cout<<"\nBooking cancelled.\n";
        	}
        
    } 
	catch (InvalidTableException& e) 
	{
        cout<<"\nError: "<<e.what()<<"\n";
    } 
	catch (InvalidInputException& e) 
	{
        cout<<"\nError: "<<e.what()<<"\n";
    } 
	catch (BookingConflictException& e) 
	{
        cout<<"\nError: "<< e.what()<<"\n";
        cout<<"Would you like to join the waiting list? (y/n): ";
        cin>>confirm;
        if (confirm == 'y' || confirm == 'Y') 
		{
            waitingQueue.enqueue(username, table, dt, slot);
            cout<<"Added to waiting list. Position: "<<waitingQueue.getSize()<<"\n";
        }
    }
    
    pauseScreen();
}

void Customer::editBooking() 
{
    clearScreen();
    displayHeader("EDIT BOOKING");
    
    BookingData* bookings;
    int size;
    loadBookingsToArray(bookings, size);
    
    if (size == 0) 
	{
        cout<<"No bookings found.\n";
        pauseScreen();
        return;
    }
    
    cout<<"Your bookings:\n";
    for (int i = 0; i < size; i++) 
	{
        if (strcmp(bookings[i].username, username) == 0) 
		{
            cout<<bookings[i].bookingID<<". Table "<<bookings[i].tableNumber<<" | "<<bookings[i].date<<" | Slot "<<bookings[i].timeSlot<<"\n";
        }
    }
    
    int id;
    cout<<"\nEnter booking ID to edit: ";
    cin>>id;
    
    bool found = false;
    for (int i = 0; i < size; i++) 
	{
        if (bookings[i].bookingID == id && strcmp(bookings[i].username, username) == 0) 
		{
            found = true;
            cout<<"\nWhat would you like to edit?\n";
            cout<<"1. Table Number\n";
            cout<<"2. Date\n";
            cout<<"3. Time Slot\n";
            cout<<"4. Phone Number\n";
            int choice;
            cin>>choice;
            
            switch(choice) 
			{
                case 1:
	                    cout<<"Enter new table number (1-10): ";
	                    cin>>bookings[i].tableNumber;
	                    break;
                case 2:
	                    cout<<"Enter new date (DD-MM-YYYY): ";
	                    cin>>bookings[i].date;
	                    break;
                case 3:
	                    cout<<"Enter new time slot (1-5): ";
	                    cin>>bookings[i].timeSlot;
	                    break;
                case 4:
	                    cout<<"Enter new phone number: ";
	                    cin>>bookings[i].phone;
	                    break;
                default:
	                    cout<<"Invalid choice!\n";
	                    delete[] bookings;
	                    pauseScreen();
	                    return;
            }
            
            saveBookingsFromArray(bookings, size);
            cout<<"\nBooking updated successfully!\n";
            break;
        }
    }
    
    if (!found) 
	{
        cout<<"Booking not found or you don't have permission to edit it.\n";
    }
    
    delete[] bookings;
    pauseScreen();
}

void Customer::deleteBooking() 
{
    clearScreen();
    displayHeader("DELETE BOOKING");
    
    BookingData* bookings;
    int size;
    loadBookingsToArray(bookings, size);
    
    if (size == 0) 
	{
        cout<<"No bookings found.\n";
        pauseScreen();
        return;
    }
    
    cout<<"Your bookings:\n";
    for (int i = 0; i < size; i++) 
	{
        if (strcmp(bookings[i].username, username) == 0) 
		{
            cout<<bookings[i].bookingID<<". Table "<<bookings[i].tableNumber<<" | "<<bookings[i].date<<" | Slot "<<bookings[i].timeSlot<<" | "<<bookings[i].status<<"\n";
        }
    }
    
    int id;
    cout<<"\nEnter booking ID to delete: ";
    cin>>id;
    
    char confirm;
    cout<<"Are you sure? (y/n): ";
    cin>>confirm;
    
    if (confirm != 'y' && confirm != 'Y') 
	{
        delete[] bookings;
        pauseScreen();
        return;
    }
    
    bool found = false;
    for (int i = 0; i < size; i++) 
	{
        if (bookings[i].bookingID == id && strcmp(bookings[i].username, username) == 0) 
		{
            strcpy(bookings[i].status, "cancelled");
            found = true;
            
            char waitUser[50];
            int waitTable, waitSlot;
            char waitDate[11];
            if (waitingQueue.dequeue(waitUser, waitTable, waitDate, waitSlot)) 
			{
                cout<<"\nNotifying "<<waitUser<<" from waiting list...\n";
            }
            break;
        }
    }
    
    if (found) 
	{
        saveBookingsFromArray(bookings, size);
        cout<<"\nBooking cancelled successfully!\n";
    } 
		else 
		{
        	cout<<"Booking not found.\n";
    	}
    
    delete[] bookings;
    pauseScreen();
}

void Customer::viewBookings() 
{
    clearScreen();
    displayHeader("MY BOOKINGS");
    
    ifstream file("bookings.txt");
    BookingData booking;
    bool found = false;
    
    cout<<"ID"<<setw(11)<<"Table"<<setw(15)<<"Date"<<setw(15)<<"Time"<<setw(16)<<"Status"<<"\n";
    cout<<string(65, '-')<<"\n";
    
    while (file >> booking.bookingID >> booking.username >> booking.tableNumber >> booking.date >> booking.timeSlot >> booking.phone >> booking.status) 
	{
        if (strcmp(booking.username, username) == 0) 
		{
            cout<<booking.bookingID<<setw(7)<<booking.tableNumber<<setw(20)<<booking.date<<setw(15)<<getTimeSlotDisplay(booking.timeSlot)<<setw(15)<<booking.status<<"\n";
            found = true;
        }
    }
    file.close();
    
    if (!found) 
	{
        cout<<"No bookings found.\n";
    }
    
    pauseScreen();
}

void Customer::searchBooking() 
{
    clearScreen();
    displayHeader("SEARCH BOOKING");
    
    cout<<"Search by:\n";
    cout<<"1. Booking ID\n";
    cout<<"2. Date\n";
    int choice;
    cin>>choice;
    
    BookingData* bookings;
    int size;
    loadBookingsToArray(bookings, size);
    
    if (size == 0) 
	{
        cout<<"No bookings found.\n";
        pauseScreen();
        return;
    }
    
    bool found = false;
    
    if (choice == 1) 
	{
        int id;
        cout<<"Enter booking ID: ";
        cin>>id;
        
        sortBookings_2(bookings, size, 0);
        int index = Search(bookings, size, id);
        
        if (index != -1 && strcmp(bookings[index].username, username) == 0) 
		{
            cout<<"\nBooking found:\n";
            cout<<"ID: " << bookings[index].bookingID<<"\n";
            cout<<"Table: "<<bookings[index].tableNumber<<"\n";
            cout<<"Date: "<<bookings[index].date<<"\n";
            cout<<"Time: "<<getTimeSlotDisplay(bookings[index].timeSlot)<<"\n";
            cout<<"Status: "<<bookings[index].status<<"\n";
            found = true;
        }
    } 
		else if (choice == 2) 
		{
	        char searchDate[11];
	        cout<<"Enter date (DD-MM-YYYY): ";
	        cin>>searchDate;
	        
	        for (int i = 0; i < size; i++) 
			{
	            if (strcmp(bookings[i].username, username) == 0 && strcmp(bookings[i].date, searchDate) == 0) 
				{
	                cout<<"\nBooking ID: "<<bookings[i].bookingID<<" | Table: "<<bookings[i].tableNumber<<" | Slot: "<<bookings[i].timeSlot<<"\n";
	                found = true;
	            }
	        }
	    }
    
    if (!found) 
	{
        cout<<"No matching bookings found.\n";
    }
    
    delete[] bookings;
    pauseScreen();
}

void Customer::sortMyBookings() 
{
    clearScreen();
    displayHeader("SORT BOOKINGS");
    
    cout<<"Sort by:\n";
    cout<<"1. Date\n";
    cout<<"2. Table Number\n";
    int choice;
    cin>>choice;
    
    BookingData* bookings;
    int size;
    loadBookingsToArray(bookings, size);
    
    if (size == 0) 
	{
        cout<<"No bookings found.\n";
        pauseScreen();
        return;
    }
    
    sortBookings_2(bookings, size, choice);
    
    cout<<"\nSorted Bookings:\n";
    cout<<"ID"<<setw(11)<<"Table"<<setw(15)<<"Date"<<setw(15)<<"Time"<<"\n";
    cout<<string(50, '-')<<"\n";
    
    for (int i = 0; i < size; i++) 
	{
        if (strcmp(bookings[i].username, username) == 0) 
		{
            cout<<bookings[i].bookingID<<setw(7)<<bookings[i].tableNumber<<setw(20)<<bookings[i].date<<setw(15)<<getTimeSlotDisplay(bookings[i].timeSlot)<<"\n";
        }
    }
    
    delete[] bookings;
    pauseScreen();
}

void Customer::addFeedback() 
{
    clearScreen();
    displayHeader("ADD FEEDBACK");
    
    Feedback fb;
    
    ifstream countFile("feedback.txt");
    int count = 0;
    Feedback temp;
    while (countFile >> temp.feedbackID >> temp.username >> temp.rating >> temp.comment >> temp.date) 
	{
        count++;
    }
    countFile.close();
    
    fb.feedbackID = count + 1;
    strcpy(fb.username, username);
    
    cout<<"Rate your experience (1-5): ";
    cin>>fb.rating;
    
    if (fb.rating < 1 || fb.rating > 5) 
	{
        cout<<"Invalid rating!\n";
        pauseScreen();
        return;
    }
    
    cout<<"Enter your comment: ";
    cin.ignore();
    cin.getline(fb.comment, 500);
    
    cout<<"Enter date (DD-MM-YYYY): ";
    cin>>fb.date;
    
    ofstream file("feedback.txt", ios::app);
    file<<fb.feedbackID<<" "<<fb.username<<" "<<fb.rating<<" "<<fb.comment<<" "<<fb.date<<"\n";
    file.close();
    
    cout<<"\nFeedback submitted successfully!\n";
    pauseScreen();
}

void Customer::viewMenu() 
{
    clearScreen();
    displayHeader("RESTAURANT MENU");
    
    try 
	{
        ifstream file("product.txt");
        if (!file) 
		{
            throw FileNotFoundException();
        }
        
        MenuItem item;
        cout<<setw(6)<<"ID"<<setw(20)<<"Item"<<setw(15)<<"Price"<<setw(15)<<"Category"<<"\n";
        cout<<string(60, '-')<<"\n";
        
        while (file >> item.itemID >> item.itemName >> item.price >> item.category) 
		{
            cout<<setw(6)<<item.itemID<<setw(20)<<item.itemName<<setw(12)<<"RM "<<fixed<<setprecision(2)<<item.price<<setw(11)<<item.category<<"\n";
        }
        cout<<string(60, '-')<<"\n";
        file.close();
    } 
	catch (FileNotFoundException& e) 
	{
        cout<<"Error: "<<e.what()<<"\n";
    }
    
    pauseScreen();
}

void Customer::generateReport() 
{
    clearScreen();
    displayHeader("GENERATE BOOKING REPORT");
    
    char filename[100];
    strcpy(filename, "customer_reports/");
    strcat(filename, username);
    strcat(filename, "_summary.txt");
    
    ofstream outFile(filename);
    
    outFile<<"=== BOOKING SUMMARY REPORT ===\n";
    outFile<<"Customer: "<<username<<"\n";
    outFile<<"Name: "<<fullName<<"\n\n";
    
    ifstream inFile("bookings.txt");
    BookingData booking;
    int total = 0, confirmed = 0, cancelled = 0;
    
    outFile<<"ID"<<setw(11)<<"Table"<<setw(15)<<"Date"<<setw(15)<<"Time"<<setw(16)<<"Status"<<"\n";
    outFile<<string(65, '-')<<"\n";
    
    while (inFile >> booking.bookingID >> booking.username >> booking.tableNumber >> booking.date >> booking.timeSlot >> booking.phone >> booking.status) 
	{
        if (strcmp(booking.username, username) == 0) 
		{
            outFile<<booking.bookingID<<setw(7)<<booking.tableNumber<<setw(20)<<booking.date<<setw(15)<<getTimeSlotDisplay(booking.timeSlot)<<setw(15)<<booking.status<<"\n";
            total++;
            if (strcmp(booking.status, "confirmed") == 0) 
			{
				confirmed++;
			}
			
            if (strcmp(booking.status, "cancelled") == 0) 
			{
				cancelled++;
			}
        }
    }
    inFile.close();
    
    outFile<<"\n=== SUMMARY ===\n";
    outFile<<"Total Bookings: "<<total<<"\n";
    outFile<<"Confirmed: "<<confirmed<<"\n";
    outFile<<"Cancelled: "<<cancelled<<"\n";
    outFile<<"===============\n";
    
    outFile.close();
    
    cout<<"Report saved to: "<<filename<<"\n\n";
    
    ifstream displayFile(filename);
    string line;
    while (getline(displayFile, line)) 
	{
        cout<<line<<"\n";
    }
    displayFile.close();
    
    pauseScreen();
}

// ==================== ADMIN FUNCTIONS ====================
void Admin::displayMenu() 
{
    int choice;
    do 
	{
        clearScreen();
        displayHeader("ADMIN MENU");
        cout<<"1. View All Bookings\n";
        cout<<"2. Search Booking\n";
        cout<<"3. Manage Menu Items\n";
        cout<<"4. View Feedback\n";
        cout<<"5. Sort Bookings\n";
        cout<<"6. Delete Booking\n";
        cout<<"7. Generate Reports\n";
        cout<<"8. Manage Waiting List\n";
        cout<<"0. Logout\n";
        cout<<"\nEnter choice: ";
        cin>>choice;
        
        switch(choice) 
		{
            case 1: 
					viewAllBookings(); 
					break;
            case 2: 
					searchBooking(); 
					break;
            case 3: 
					manageMenu(); 
					break;
            case 4: 
					viewFeedback(); 
					break;
            case 5: 
					sortAllBookings(); 
					break;
            case 6: 
					deleteBooking(); 
					break;
            case 7: 
					generateReports(); 
					break;
            case 8: 
					manageWaitingList(); 
					break;
            case 0: 
					cout<<"Logging out...\n"; 
					pauseScreen(); 
					break;
            default: 
					cout<<"Invalid choice!\n"; 
					pauseScreen();
        }
    } while(choice != 0);
}

void Admin::viewAllBookings() 
{
    clearScreen();
    displayHeader("ALL BOOKINGS");
    
    ifstream file("bookings.txt");
    BookingData booking;
    
    cout<<"ID"<<setw(15)<<"Customer"<<setw(10)<<"Table"<<setw(10)<<"Date"<<setw(15)<<"Time"<<setw(16)<<"Status"<<"\n";
    cout<<string(80, '-')<<"\n";
    
    while (file >> booking.bookingID >> booking.username >> booking.tableNumber >> booking.date >> booking.timeSlot >> booking.phone >> booking.status) 
	{
        cout<<booking.bookingID<<setw(14)<<booking.username<<setw(7)<<booking.tableNumber<<setw(15)<<booking.date<<setw(15)<<getTimeSlotDisplay(booking.timeSlot)<<setw(15)<<booking.status<<"\n";
    }
    file.close();
    
    pauseScreen();
}

void Admin::searchBooking() 
{
    clearScreen();
    displayHeader("SEARCH BOOKING");
    
    cout<<"Search by:\n";
    cout<<"1. Booking ID\n";
    cout<<"2. Customer Username\n";
    cout<<"3. Table Number\n";
    int choice;
    cin>>choice;
    
    BookingData* bookings;
    int size;
    loadBookingsToArray(bookings, size);
    
    if (size == 0) 
	{
        cout<<"No bookings found.\n";
        pauseScreen();
        return;
    }
    
    bool found = false;
    
    if (choice == 1) 
	{
        int id;
        cout<<"Enter booking ID: ";
        cin>>id;
        
        sortBookings(bookings, size, 0);
        int index = Search(bookings, size, id);
        
        if (index != -1) 
		{
            cout<<"\nBooking found:\n";
            cout<<"ID: "<<bookings[index].bookingID<<"\n";
            cout<<"Customer:"<<bookings[index].username<<"\n";
            cout<<"Table: "<<bookings[index].tableNumber<<"\n";
            cout<<"Date: "<<bookings[index].date<<"\n";
            cout<<"Time: "<<getTimeSlotDisplay(bookings[index].timeSlot)<<"\n";
            cout<<"Phone: "<<bookings[index].phone<<"\n";
            cout<<"Status: "<<bookings[index].status<<"\n";
            found = true;
        }
    } 
		else if (choice == 2) 
		{
	        char searchUser[50];
	        cout<<"Enter username: ";
	        cin>>searchUser;
	        
	        for (int i = 0; i < size; i++)
			{
	            if (strcmp(bookings[i].username, searchUser) == 0) 
				{
	                cout<<"\nID: "<<bookings[i].bookingID<<" | Table: "<<bookings[i].tableNumber<<" | Date: "<<bookings[i].date<<" | Status: "<<bookings[i].status<<"\n";
	                found = true;
	            }
	        }
    	} 
			else if (choice == 3) 
			{
		        int table;
		        cout<<"Enter table number: ";
		        cin>>table;
		        
		        for (int i = 0; i < size; i++) 
				{
		            if (bookings[i].tableNumber == table) 
					{
		                cout<<"\nID: "<<bookings[i].bookingID<<" | Customer: "<<bookings[i].username<<" | Date: "<<bookings[i].date<<" | Slot: "<<bookings[i].timeSlot<<"\n";
		                found = true;
		            }
		        }
		    }
		    
    if (!found) 
	{
        cout<<"No matching bookings found.\n";
    }
    
    delete[] bookings;
    pauseScreen();
}

void Admin::manageMenu() 
{
	int choice, secondchoice, thirdchoice, samechoice, afterchoice, search, exits, fourthchoice, fifthchoice, sixthchoice, result, result_1, result_2;
	InsertionSort IS;
	BinarySearch BS;
    clearScreen();
    displayHeader("MANAGE MENU ITEMS");
    
    do
    {
    	system("cls");
		cout<<"1. Add Menu Item\n";
		cout<<"2. Delete Menu Item\n";
		cout<<"3. Edit Menu Items\n";
		cout<<"4. View All Items or Sort All Items\n";
		cout<<"5. Search Items\n";
		cout<<"6. Exit\n";
		choice;
		cin>>choice;
		
		do
		{   
		    if (choice == 1) 
			{
		    	cout<<fixed<<setprecision(2);			
				do
				{
					resetAll();
					f.open("product.txt"); 
							            	
					if(!f)
					{
						cout<<"No Product found!\n";
						exit(0);
					}
							                    
					system("cls");
					displayFile();
					f.close();
												
					//check whether inside file is empty or not
					if(pi == "" && pn == "" && pp == 0.00)
					{
						head = new node;
						head->next = NULL;
						exsits = true;
					}
							                    
					if(exsits == true)
					{
						cout<<"\nInsert your product id                    : ";
						cin>>product_i;
						cout<<"Insert your product name                  : ";
						cin>>product_n;
						cout<<"Insert your product price                 : ";
						cin>>product_p;
						do
						{
					
							cout<<"Insert your Category [M - Mainfood, S - Sidefood, D - Drinks, P - Pastry] : ";
							cin>>product_c;	
							if(product_c != "M" && product_c != "m"  && product_c != "S"  && product_c != "s"  && product_c != "D"  && product_c != "d"  && product_c != "P" && product_c != "p")
							{
								cout<<"Invalid Category. Please re-enter the correct valid category. Thank You.\n"<<endl;
							}
						} while(product_c != "M" && product_c != "m"  && product_c != "S"  && product_c != "s"  && product_c != "D"  && product_c != "d"  && product_c != "P" && product_c != "p");
									
						head->product_ID = product_i;
						head->product_name = product_n;
						head->product_price = product_p;
						head->category = product_c;
							
						insfound = true;  
						changes = true;   
					}
						else
						{
							//Insert a new product id, product name and price and which node will be add before
							cout<<"\nInsert your product id                    : ";
							cin>>product_i;
								    
							f.open("product.txt"); 
							displayvalue();
							f.close();
							IS.insertionSortById_Asc(P,count);
							result_1 = BS.BinarySearchById(P,count,product_i);
							
							while(result_1 != -1)
							{
								do
								{
									do
								    {
										system("cls");
										display();											                    												
										cout<<"The Product id is already have the list of Product:"<<endl;
										cout<<"Do you want update the Product or Enter other Product ID? "<<endl;	                            	                                
								        cout<<"Enter 00 to go update the Product."<<endl;
								        cout<<"Enter 01 to enter other Product ID."<<endl;
								        cout<<"\nWhat is your choice : ";
								        cin>>samechoice;
								                                        
								        if(samechoice == 00)
								        {
								            do
								            {
								                do
								                {
								                    f.open("product.txt"); 
													displayvalue();
													f.close();
										            system("cls");
													display();														                    
											        cout<<"Enter 00 to updated your "<<product_i<<" name."<<endl;
											        cout<<"Enter 01 to updated your "<<product_i<<" price."<<endl;
											        cout<<"Enter 02 to updated your "<<product_i<<" category."<<endl;
											        cout<<"Enter 03 to updated your "<<product_i<<" name, price and category."<<endl;
											        cout<<"Enter 04 to return previous."<<endl;
											        cout<<"Enter 05 to exit."<<endl;
											        cout<<"\nWhat is your choice : ";
											        cin>>afterchoice;
											                                                
											        if(afterchoice == 00)
											        {
											            do
											            {
												            cout<<"Enter your new "<<product_i<<" name    : ";
												            cin>>newname;
												                    
												            IS.insertionSortByName_Asc(P,count);
												            result_2 = BS.BinarySearchByName(P,count,newname);
												                    
												            if(result_2 != -1)
												            {
												                cout<<"The product name is already have in the list menu. Please try enter another Product Name. Thank You.\n"<<endl;
															}
														} while(result_2 != -1);
											                    
														temp = head;                     
											            while(temp != NULL)
											            {
											                if(product_i == temp->product_ID)
											                {
											                    temp->product_name = newname;				                                                				                                            
													            same = false;
													            changes = true;    
													            updfound = true;
													            p = 1;				                                                
											                }
											                temp = temp->next;
											            }
							
											            system("cls");
														cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
														sleep(1);
														cout<<".";
														sleep(1);
														cout<<".";
														sleep(1);
														cout<<".";
														sleep(1);
														system("cls");
																		                                                                         
														if(updfound == true && p == 1)
														{
															setColor(10);
															cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Successfully.";
															sleep(3);
														}
															else
															{
																setColor(4);				
																cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Failed.";
																sleep(3);
															}
											        }
											            else if(afterchoice == 01)
											            {
											                temp = head;
											                cout<<"Enter your new "<<product_i<<" price : ";
											                cin>>newprice;
											                while(temp != NULL)
											                {
											                    if(product_i == temp->product_ID)
											                    {
											                        temp->product_price = newprice;
											                        same = false;
													                changes = true;    
													                updfound = true; 
													                p = 1;
											                    }
											                    temp = temp->next;
											                }
											                                                    
											                system("cls");
															cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
															sleep(1);
															cout<<".";
															sleep(1);
															cout<<".";
															sleep(1);
															cout<<".";
															sleep(1);
															system("cls");											                                    
											                                                    
												            if(updfound == true && p == 1)
															{
																setColor(10);
																cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Successfully.";
																sleep(3);
															}
																else
																{	
																	setColor(4);			
																	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Failed.";
																	sleep(3);
																}
											            }
											                else if(afterchoice == 02)
											                {
											                    temp = head;
											                    do
											                    {														
													                cout<<"Enter your new category [M - Mainfood, S - Sidefood, D - Drinks, P - Pastry] : ";
													                cin>>newcategory;
												                            
												                    if(newcategory != "M" && newcategory != "m"  && newcategory != "S"  && newcategory != "s"  && newcategory != "D"  && newcategory != "d"  && newcategory != "P" && newcategory != "p")
																	{
																		cout<<"Invalid Category. Please re-enter the correct valid category. Thank You.\n"<<endl;
																	}
																} while(newcategory != "M" && newcategory != "m"  && newcategory != "S"  && newcategory != "s"  && newcategory != "D"  && newcategory != "d"  && newcategory != "P" && newcategory != "p");
												                            
																while(temp != NULL)
												                {
												                    if(product_i == temp->product_ID)
												                    {
												                        temp->category = newcategory;
												                        same = false;
														                changes = true;    
														                updfound = true; 
														                p = 1;
												                    }
												                    temp = temp->next;
												                }
												                                                    
												                system("cls");
																cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
																sleep(1);
																cout<<".";
																sleep(1);
																cout<<".";
																sleep(1);
																cout<<".";
																sleep(1);
																system("cls");											                                    
												                                                    
													            if(updfound == true && p == 1)
																{
																	setColor(10);
																	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Successfully.";
																	sleep(3);
																}
																	else
																	{	
																		setColor(4);			
																		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Failed.";
																		sleep(3);
																	}
															}
											                    else if(afterchoice == 03)
											                    {
											                        do
											                        {
												                        cout<<"Enter your new "<<product_i<<" name    : ";
												                        cin>>newname;
												                        IS.insertionSortByName_Asc(P,count);
															            result_2 = BS.BinarySearchByName(P,count,newname);
															                    
															            if(result_2 != -1)
															            {
															                cout<<"The product name is already have in the list menu. Please try enter another Product Name. Thank You.\n"<<endl;
																		}
																	} while(result_2 != -1);
																			
																	temp = head;
											                        cout<<"Enter your new "<<product_i<<" price   : ";
											                        cin>>newprice;
											                        do
												                    {														
														                cout<<"Enter your new category [M - Mainfood, S - Sidefood, D - Drinks, P - Pastry] : ";
														                cin>>newcategory;
													                            
													                    if(newcategory != "M" && newcategory != "m"  && newcategory != "S"  && newcategory != "s"  && newcategory != "D"  && newcategory != "d"  && newcategory != "P" && newcategory != "p")
																		{
																			cout<<"Invalid Category. Please re-enter the correct valid category. Thank You.\n"<<endl;
																		}
																	} while(newcategory != "M" && newcategory != "m"  && newcategory != "S"  && newcategory != "s"  && newcategory != "D"  && newcategory != "d"  && newcategory != "P" && newcategory != "p");
											                                    
																	while(temp != NULL)
											                        {
											                            if(product_i == temp->product_ID)
											                            {
											                                temp->product_name = newname;
											                                temp->product_price = newprice;
											                                temp->category = newcategory;
											                                same = false;
													                        changes = true;    
													                        updfound = true; 
													                        p = 1;			                                                        
											                            }
											                            temp = temp->next;
											                        }
							
											                        system("cls");
																	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
																	sleep(1);
																	cout<<".";
																	sleep(1);
																	cout<<".";
																	sleep(1);
																	cout<<".";
																	sleep(1);
																	system("cls");
											                                                        
											                        if(updfound == true && p == 1)
																	{
																		setColor(10);
																		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Successfully.";
																		sleep(3);
																		system("cls");
																	}
																		else
																		{	
																			setColor(4);			
																			cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Failed.";
																			sleep(3);
																			system("cls");
																		}
											                    }
											                        else if(afterchoice == 04)
											                        {
											                            result_1 = -1;
											                            changes = false;
											                            break;
											                        }
											                            else if(afterchoice == 05)
											                            {
											                                result_1 = -1;
											                                changes = true;
											                                break;
																		}
												                            else
												                            {
												                                system("cls");
												                                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tInvalid Choice. Please try again."<<endl;
												                                sleep(3);
												                            }
												                    
													//Display after updated the product and saved to file again                
													ofstream fout1;        
												    fout1.open("product.txt");
													temp = head;
																	                    
													while(temp != NULL)
													{
														fout1<<temp->product_ID<<" "<<temp->product_name<<" "<<temp->product_price<<" "<<temp->category<<endl;    
														temp = temp->next;
													}
																	                
													fout1.close();
												    setColor(7);
											                                        
										        } while(afterchoice != 00 && afterchoice != 01 && afterchoice != 02 && afterchoice != 03 && afterchoice != 04 && afterchoice != 05); 
											} while (afterchoice == 00 || afterchoice == 01 || afterchoice == 02 || afterchoice == 03);
								        }
								            else if(samechoice == 01)
								            {
								                cout<<"Please enter other Product ID to insert   : ";
								                cin>>product_i;
								                        
								                IS.insertionSortById_Asc(P,count);
												result_1 = BS.BinarySearchById(P,count,product_i); 
														
												if(result_1 == -1)
												{
													break;
												}                   
								            }
								                else
								                {
								                    system("cls");
								                    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tInvalid Choice. Please try again."<<endl;
								                    sleep(3);
								                    system("cls");
								                }
								    } while (afterchoice == 04);
								} while(samechoice != 00 && samechoice != 01);
							}
							//
								                        
							//See checking the changes has been changing
							if(result_1 == -1 && changes == false)
							{
								do
								{
									cout<<"Insert your product name                  : ";
									cin>>product_n;
									f.open("product.txt"); 
									displayvalue();
									f.close();
									IS.insertionSortByName_Asc(P,count);
									result_2 = BS.BinarySearchByName(P,count,product_n);
												                    
									if(result_2 != -1)
									{
										cout<<"The product name is already have in the list menu. Please try enter another Product Name. Thank You.\n"<<endl;
									}
								} while(result_2 != -1);
								                            
								cout<<"Insert your product price                 : ";
								cin>>product_p;
										    
								do
								{						  
									cout<<"Insert your Category [M - Mainfood, S - Sidefood, D - Drinks, P - Pastry] : ";
									cin>>product_c;
												
									if(product_c != "M" && product_c != "m"  && product_c != "S"  && product_c != "s"  && product_c != "D"  && product_c != "d"  && product_c != "P" && product_c != "p")
									{
										cout<<"Invalid Category. Please re-enter the correct valid category. Thank You.\n"<<endl;
									}
								} while(product_c != "M" && product_c != "m"  && product_c != "S"  && product_c != "s"  && product_c != "D"  && product_c != "d"  && product_c != "P" && product_c != "p");          
										    
								p = 0;
							}
								                        						                	
							if(changes == false)
							{
								//insertion and additional the node into the bottom
								temp = head;	                        
								while(temp != NULL && p != 1)
								{
									tail = temp;
									temp = temp->next;
								}	
																			
								if(tail != NULL && p != 1)
								{
									temp = new node;
									temp->product_ID = product_i;
									temp->product_name = product_n;
									temp->product_price = product_p;
									temp->category = product_c;
									temp->next = NULL;
								    tail->next = temp;
								    tail = temp;
								    insfound = true;
								}
							}
						}
							                                           
						if(insfound == true && p == 0)
						{
							system("cls");
							cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
							sleep(1);
							cout<<".";
							sleep(1);
							cout<<".";
							sleep(1);
							cout<<".";
							sleep(1);
							system("cls");
							setColor(10);
							cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tInsert Product Successfully.";
							sleep(3);
							ofstream fout1;
								                    
							//Display after insertion the product and saved to file again
							fout1.open("product.txt");
							temp = head;
									                    
							while(temp != NULL)
							{
								fout1<<temp->product_ID<<" "<<temp->product_name<<" "<<temp->product_price<<" "<<temp->category<<endl;    
								temp = temp->next;
							}
							fout1.close();
						}
							else if(insfound == false && p == 0)
							{
								system("cls");
								cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
								sleep(1);
								cout<<".";
								sleep(1);
								cout<<".";
								sleep(1);
								cout<<".";
								sleep(1);
								system("cls");
								setColor(4);
								cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tInsert Product Failed.";
								sleep(3);
							}
								else
								{
								    system("cls");
									cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
									sleep(1);
									cout<<".";
									sleep(1);
									cout<<".";
									sleep(1);
									cout<<".";
									sleep(1);
									system("cls");
								}
					do
					{
						setColor(7);		
						system("cls");
						display1();
						cout<<"Enter 00 to continue insert product."<<endl;
						cout<<"Enter 01 to exit."<<endl;
							                        
						cout<<"\nWhat is your choice : ";
						cin>>thirdchoice;
							                    
						if(thirdchoice != 00 && thirdchoice != 01)
						{
							system("cls");
							cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease enter valid choice. Thank You."<<endl;
							sleep(3);
						}														
					} while (thirdchoice != 00 && thirdchoice != 01);				                    
				} while(thirdchoice == 00);
				resetAll();
				system("cls");
				cout<<"Note:"<<endl;
				cout<<"Enter 1 to insert menu item.                          "<<endl;
				cout<<"Enter 2 to deleted menu item.                         "<<endl;
				cout<<"Enter 3 to updated menu item.                         "<<endl;
				cout<<"Enter 4 to view menu item or sort menu item.          "<<endl;
				cout<<"Enter 5 to search menu item.                          "<<endl;
				cout<<"Enter 6 to exit.                                      "<<endl;
				cout<<"Enter other number to return back.                    "<<endl;
				display();			                        
				cout<<"What is your choice : ";
				cin>>choice;
		    } 
				else if (choice == 2) 
				{
			        cout<<fixed<<setprecision(2);
					do
					{
						resetAll();
						f.open("product.txt"); 					            	
							            				                    
						if(!f)
						{
						    cout<<"No Product found!\n";
						    exit(0);
						}
						                    
						system("cls");
						displayFile();
						f.close();
										
						//check whether inside file is empty or not	
						if (pi == "" && pn == "" && pp == 0.00)
						{
						    exsits = true;
						    cout<<"The product is empty. Please insert the new product and can delete product."<<endl;
						    cout<<"\nPress any key to continue...";
						    cin.ignore();
						    cin.get();	
							thirdchoice = -1;		                
						}        
						    else
						    {
						        //Delete a product name, product price and quantity and which product will be delete
						        cout<<"\nDelete your product id : ";
						        cin>>product_i;
						                    
						        f.open("product.txt"); 
							    displayvalue();
							    f.close();
							    IS.insertionSortById_Asc(P,count);
							    result_1 = BS.BinarySearchById(P,count,product_i);
						                            
						        if(result_1 == -1)
						        {
						            cout<<"Product ID not found!"<<endl;
						            cout<<"\nPress any key to continue...";
						            cin.ignore();
	   								cin.get();
						        }
						        //
						                                
						        //deletion and not delete the first node First Part
						        temp = head;
						        while((temp != NULL) && (temp->product_ID != product_i))
						        {
						            prev = temp;
						            temp = temp->next;
						            whi = true;
						        }
						                                
						        //Special case for delete the first node
						        if(whi == false)
						        {
						            head = head->next;
						            delete temp;
						            delfound = true;
						        }
						                                
						        //deletion and not delete the first node Second Part
						        if(temp != NULL && whi == true)
						        {
						            prev->next = temp->next;
						            delete temp;
						            delfound = true;
						        }
						                            
							    system("cls");
								cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
								sleep(1);
								cout<<".";
								sleep(1);
								cout<<".";
								sleep(1);
								cout<<".";
								sleep(1);
								system("cls");
								                                                
						        if(delfound == true)
						        {
						            setColor(10);
						            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tDelete Product Successfully.";
						        }
						            else
						            {
						                setColor(4);
						                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tDelete Product Failed.";
						            }
								sleep(3);
								system("cls");
								setColor(7);  
							}
						                        
						//Display after delete the product and saved to file again
						ofstream fout4;
						fout4.open("product.txt");
						temp = head;
						while(temp != NULL && exsits != true)
						{
						    fout4<<temp->product_ID<<" "<<temp->product_name<<" "<<temp->product_price<<" "<<temp->category<<endl;
						    temp = temp->next;
						}
						fout4.close();
						                    
						if(exsits != true)
						{
							do
							{
								setColor(7);		
								system("cls");
								display1();
								cout<<"Enter 00 to continue deleted product."<<endl;
								cout<<"Enter 01 to exit."<<endl;
								                        
								cout<<"\nWhat is your choice : ";
								cin>>thirdchoice;
								                    
								if(thirdchoice != 00 && thirdchoice != 01 && thirdchoice != 02)
								{
									system("cls");
									cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease enter valid choice. Thank You."<<endl;
									sleep(3);
								}
																	
							} while (thirdchoice != 00 && thirdchoice != 01);	
						}																																		        							                
					} while(thirdchoice == 00 && exsits != true);
					resetAll();
					
					system("cls");
					temp = head;
					cout<<"Note:"<<endl;
					cout<<"Enter 1 to insert menu item.                          "<<endl;
					cout<<"Enter 2 to deleted menu item.                         "<<endl;
					cout<<"Enter 3 to updated menu item.                         "<<endl;
					cout<<"Enter 4 to view menu item or sort menu item.          "<<endl;
					cout<<"Enter 5 to search menu item.                          "<<endl;
					cout<<"Enter 6 to exit.                                      "<<endl;
					cout<<"Enter other number to return back.                    "<<endl;
					display();						                        
					cout<<"What is your choice : ";
					cin>>choice;
		   		}
					else if(choice == 3)
					{
						cout<<fixed<<setprecision(2);	
						do
						{		
							resetAll();							
							f.open("product.txt"); 
													
							if(!f)
							{
								cout<<"No Product found!\n";
								exit(0);
							}
									                
							system("cls");    
							displayFile();
							f.close();
									                    
							//check whether inside file is empty or not
							if (pi == "" && pn == "" && pp == 0.00)
							{
								exsits = true;
								cout<<"The product is empty. Please insert the new product and can updated product."<<endl;
								cout<<"\nPress any key to continue...";
							    cin.ignore();
							    cin.get();
								thirdchoice = -1;
							} 
								else
								{
									//Updated a product name, product price and which product will be updated    
									cout<<"\nUpdate your product id : ";
									cin>>product_i;
									
									//Checking whether in User enter product name is valid or not   
									f.open("product.txt"); 
									displayvalue();
									f.close();	
														                                              
									do
									{																
										IS.insertionSortById_Asc(P,count);
										result_1 = BS.BinarySearchById(P,count,product_i);
										if(result_1 == -1)
										{
										    cout<<"Product ID not found!"<<endl;
								            cout<<"\nPress any key to continue...";
								            cin.ignore();
			   								cin.get();	   							
								            break;
										}
										// 
										 							                    
										do
										{
										    do
										    {
										    	f.open("product.txt"); 
												displayvalue();
												f.close();	
												//updated the product from the node 															
												system("cls");
												display();	                    
												cout<<"Enter 00 to updated your "<<product_i<<" name."<<endl;
												cout<<"Enter 01 to updated your "<<product_i<<" price."<<endl;
												cout<<"Enter 02 to updated your "<<product_i<<" category."<<endl;
												cout<<"Enter 03 to updated your "<<product_i<<" name, price and category."<<endl;
												cout<<"Enter 04 to reset your ID and updated."<<endl;
												cout<<"Enter 05 to exit."<<endl;
												cout<<"\nWhat is your choice : ";
												cin>>afterchoice;
											                            	
											    if(afterchoice == 00)
											    {
											    	do
											    	{
											            cout<<"Enter your new "<<product_i<<" name    : ";
												        cin>>newname;
											        	IS.insertionSortByName_Asc(P,count);
												        result_2 = BS.BinarySearchByName(P,count,newname);
												                    
												        if(result_2 != -1)
												        {
												            cout<<"The product name is already have in the list menu. Please try enter another Product Name. Thank You.\n"<<endl;
														}
													} while(result_2 != -1);
													
													temp = head;                        
											        while(temp != NULL)
											        {													
											            if(product_i == temp->product_ID)
											            {
											                temp->product_name = newname;
											                updfound = true;
											            }
											        	temp = temp->next;
											        }
											                                
											        system("cls");
													cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
													sleep(1);
													cout<<".";
													sleep(1);
													cout<<".";
													sleep(1);
													cout<<".";
													sleep(1);
													system("cls");
											                                
											        if(updfound)
											        {
											            setColor(10);
														cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Successfully.";
														sleep(3);
														system("cls");
													}	
														else
														{
															setColor(4);			
															cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Failed.";
															sleep(3);
															system("cls");
														}
												}
													else if(afterchoice == 01)
													{
														temp = head;
											            cout<<"Enter your new "<<product_i<<" price   : ";
												        cin>>newprice;
												                                
												        while(temp != NULL)
												        {
												            if(product_i == temp->product_ID)
												            {
												                temp->product_price = newprice;
												                updfound = true;
												            }
												            temp = temp->next;
												    	}
												                                
												        system("cls");
														cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
														sleep(1);
														cout<<".";
														sleep(1);
														cout<<".";
														sleep(1);
														cout<<".";
														sleep(1);
														system("cls");
												                                
												        if(updfound)
												        {
												            setColor(10);
															cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Successfully.";
															sleep(3);
															system("cls");
														}	
															else
															{
																setColor(4);			
																cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Failed.";
																sleep(3);
																system("cls");
															}
													}
														else if(afterchoice == 02)
														{
															temp = head;
											                do
											                {														
													            cout<<"Enter your new category [M - Mainfood, S - Sidefood, D - Drinks, P - Pastry] : ";
													            cin>>newcategory;
												                            
												                if(newcategory != "M" && newcategory != "m"  && newcategory != "S"  && newcategory != "s"  && newcategory != "D"  && newcategory != "d"  && newcategory != "P" && newcategory != "p")
																{
																	cout<<"Invalid Category. Please re-enter the correct valid category. Thank You.\n"<<endl;
																}
															} while(newcategory != "M" && newcategory != "m"  && newcategory != "S"  && newcategory != "s"  && newcategory != "D"  && newcategory != "d"  && newcategory != "P" && newcategory != "p");
												                            
															while(temp != NULL)
												            {
												                if(product_i == temp->product_ID)
												                {
												                    temp->category = newcategory;
														            updfound = true; 
												                }
												                temp = temp->next;
												            }
												                                                    
												            system("cls");
															cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
															sleep(1);
															cout<<".";
															sleep(1);
															cout<<".";
															sleep(1);
															cout<<".";
															sleep(1);
															system("cls");											                                    
												                                                    
													        if(updfound == true)
															{
																setColor(10);
																cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Successfully.";
																sleep(3);
															}
																else
																{	
																	setColor(4);			
																	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Failed.";
																	sleep(3);
																}
														}
															else if(afterchoice == 03)
															{
																do
																{	
																	cout<<"Enter your new "<<product_i<<" name    : ";
												                    cin>>newname;
																	IS.insertionSortByName_Asc(P,count);
												                    result_2 = BS.BinarySearchByName(P,count,newname);
												                    
												                    if(result_2 != -1)
												                    {
												                    	cout<<"The product name is already have in the list menu. Please try enter another Product Name. Thank You.\n"<<endl;
																	}
																} while(result_2 != -1);
																
																temp = head;
												                cout<<"Enter your new "<<product_i<<" price   : ";
													            cin>>newprice;
													            do
												                {														
														            cout<<"Enter your new category [M - Mainfood, S - Sidefood, D - Drinks, P - Pastry] : ";
														            cin>>newcategory;
													                            
													                if(newcategory != "M" && newcategory != "m"  && newcategory != "S"  && newcategory != "s"  && newcategory != "D"  && newcategory != "d"  && newcategory != "P" && newcategory != "p")
																	{
																		cout<<"Invalid Category. Please re-enter the correct valid category. Thank You.\n"<<endl;
																	}
																} while(newcategory != "M" && newcategory != "m"  && newcategory != "S"  && newcategory != "s"  && newcategory != "D"  && newcategory != "d"  && newcategory != "P" && newcategory != "p");        
													            
																while(temp != NULL)
													            {
													                if(product_i == temp->product_ID)
													                {
													                    temp->product_name = newname;
													                    temp->product_price = newprice;
													                    temp->category = newcategory;
													                    updfound = true;
													                }
													            	temp = temp->next;
													            }
													                                
													            system("cls");
																cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
																sleep(1);
																cout<<".";
																sleep(1);
																cout<<".";
																sleep(1);
																cout<<".";
																sleep(1);
																system("cls");
													                                
													            if(updfound)
													            {
													                setColor(10);
																	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Successfully.";
																	sleep(3);
																	system("cls");
																}	
																	else
																	{
																		setColor(4);			
																		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Failed.";
																		sleep(3);
																		system("cls");
																	}
															}
																else if(afterchoice == 04)
																{
																	system("cls");
																	display();
																						
																	//Reset a product id and updated what your want updated   
																    cout<<"\nReset your product id : ";
																    cin>>product_i;
																    updfound = false;
																}
																	else if(afterchoice == 05)
																	{
																		break;
																	}
																		else
																		{
																			system("cls");
												                            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tInvalid Choice. Please try again."<<endl;
												                            sleep(3);
												                            system("cls");
																		}
												
													//Display after updated the product and saved to file again
													ofstream fout4;
													fout4.open("product.txt");
													temp = head;
													while(temp != NULL && exsits != true)
													{
														fout4<<temp->product_ID<<" "<<temp->product_name<<" "<<temp->product_price<<" "<<temp->category<<endl;
														temp = temp->next;
													}
													fout4.close();	
													setColor(7);
											} while(afterchoice != 00 && afterchoice != 01 && afterchoice != 02 && afterchoice != 03 && afterchoice != 04 && afterchoice != 05);
										} while(afterchoice == 00 || afterchoice == 01 || afterchoice == 02 || afterchoice == 03);
									} while(afterchoice == 04);
							    }
							
							if(result_1 == -1 || !updfound)			
							{
								system("cls");
								cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
								sleep(1);
								cout<<".";
								sleep(1);
								cout<<".";
								sleep(1);
								cout<<".";
								sleep(1);
								system("cls");
													                                
								setColor(4);			
								cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tUpdated Product Failed.";
								sleep(3);
								system("cls");						
							}
								else
								{
								    system("cls");
									cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tProcessing";
									sleep(1);
									cout<<".";
									sleep(1);
									cout<<".";
									sleep(1);
									cout<<".";
									sleep(1);
									system("cls");
								}						
							            								                    
							if(exsits != true)
							{
								do
								{
									setColor(7);		
									system("cls");
									display1();
									cout<<"Enter 00 to continue updated product."<<endl;
									cout<<"Enter 01 to exit."<<endl;
										                        
									cout<<"\nWhat is your choice : ";
									cin>>thirdchoice;
										                    
									if(thirdchoice != 00 && thirdchoice != 01)
									{
										system("cls");
										cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease enter valid choice. Thank You."<<endl;
										sleep(3);
									}
																			
								} while (thirdchoice != 00 && thirdchoice != 01);
							}					                    
						} while(thirdchoice == 00 && exsits != true);
						resetAll();
						
						system("cls");
						temp = head;
						cout<<"Note:"<<endl;
						cout<<"Enter 1 to insert menu item.                          "<<endl;
						cout<<"Enter 2 to deleted menu item.                         "<<endl;
						cout<<"Enter 3 to updated menu item.                         "<<endl;
						cout<<"Enter 4 to view menu item or sort menu item.          "<<endl;
						cout<<"Enter 5 to search menu item.                          "<<endl;
						cout<<"Enter 6 to exit.                                      "<<endl;
						cout<<"Enter other number to return back.                    "<<endl;
						display();							                        
						cout<<"What is your choice : ";
						cin>>choice;
					}
						else if(choice == 4)
						{
							cout<<fixed<<setprecision(2);
							do
							{	
								resetAll();							
								f.open("product.txt"); 
														
								if(!f)
								{
									cout<<"No Product found!\n";
									exit(0);
								}
										                
								system("cls");    
								displayFile();
								f.close();
										                    
								//check whether inside file is empty or not
								if (pi == "" && pn == "" && pp == 0.00)
								{
									exsits = true;
									cout<<"The product is empty. Please insert the new product and can display or sort product."<<endl;
									cout<<"\nPress any key to continue...";
								    cin.ignore();
								    cin.get();
									thirdchoice = -1;
								} 
									else
									{
										do
										{
											do
											{
												sixthchoice = 0;
												fifthchoice = 0;
												//Choose a what you love to displayed or sorted by product     
												cout<<"Enter 1 to displayed Product (Orignally)         "<<endl;
												cout<<"Enter 2 to displayed Product (Sorted by ID)      "<<endl;
												cout<<"Enter 3 to displayed Product (Sorted by Name)    "<<endl;
												cout<<"Enter 4 to displayed Product (Sorted by Price)   "<<endl;	
												cout<<"Enter 5 to displayed Product (Sorted by Category)"<<endl;	
												cout<<"Enter 6 to Exit                                  "<<endl;								    
												cout<<"\nWhat is your choice : ";
												cin>>fourthchoice;
														        
												if(fourthchoice == 1)
												{
														system("cls");
														display();
														cout<<"\nPress any key to continue...";
													    cin.ignore();
													    cin.get();
												}
													else if(fourthchoice == 2)											
													{	
														system("cls");													
														do
														{			
															f.open("product.txt"); 			
															display_File1();
															f.close();
															cout<<"Enter 1 to Sorted By ID (Low -> High)"<<endl;
															cout<<"Enter 2 to Sorted By ID (High -> Low)"<<endl;
															cout<<"Enter 3 to Return"<<endl;
															cout<<"\nWhat is your choice : ";
															cin>>fifthchoice;
																			
															if(fifthchoice == 1)
															{
																IS.insertionSortById_Asc(P,count);					
															}
																else if(fifthchoice == 2)
																{
																	IS.insertionSortById_Desc(P,count);	
																}
																	else if(fifthchoice == 3)
																	{
																		system("cls");
																		display();
																		break;	
																	}
																		else
																		{
																			system("cls");
																			cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tInvalid Choice. Please try again."<<endl;
																			sleep(3);
																			system("cls");
																		}
															if(fifthchoice == 1 || fifthchoice == 2)
															{
																system("cls");
																display2();														
																cout<<"\nPress any key to continue...";
															    cin.ignore();
															    cin.get();
															}
														} while(fifthchoice != 1 && fifthchoice != 2 && fifthchoice != 3);
													}
														else if(fourthchoice == 3)
														{
															system("cls");													
															do
															{			
																f.open("product.txt"); 			
																display_File1();
																f.close();
																cout<<"Enter 1 to Sorted By Name (A -> Z)"<<endl;
																cout<<"Enter 2 to Sorted By Name (Z -> A)"<<endl;
																cout<<"Enter 3 to Return"<<endl;
																cout<<"\nWhat is your choice : ";
																cin>>fifthchoice;
																			
																if(fifthchoice == 1)
																{
																	IS.insertionSortByName_Asc(P,count);					
																}
																	else if(fifthchoice == 2)
																	{
																		IS.insertionSortByName_Desc(P,count);	
																	}
																		else if(fifthchoice == 3)
																		{
																			system("cls");
																			display();
																			break;	
																		}	
																			else
																			{
																				system("cls");
																				cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tInvalid Choice. Please try again."<<endl;
																				sleep(3);
																				system("cls");
																			}
																if(fifthchoice == 1 || fifthchoice == 2)
																{
																	system("cls");
																	display2();															
																	cout<<"\nPress any key to continue...";
																    cin.ignore();
																    cin.get();
																}
															} while(fifthchoice != 1 && fifthchoice != 2 && fifthchoice != 3);
														}
															else if(fourthchoice == 4)
															{
																system("cls");													
																do
																{	
																	f.open("product.txt"); 			
																	display_File1();
																	f.close();
																	cout<<"Enter 1 to Sorted By Price (Low -> High)"<<endl;
																	cout<<"Enter 2 to Sorted By Price (High -> Low)"<<endl;
																	cout<<"Enter 3 to Return"<<endl;
																	cout<<"\nWhat is your choice : ";
																	cin>>fifthchoice;
																				
																	if(fifthchoice == 1)
																	{
																		IS.insertionSortByPrice_Asc(P,count);	
																	}
																		else if(fifthchoice == 2)
																		{
																			IS.insertionSortByPrice_Desc(P,count);	
																		}
																			else if(fifthchoice == 3)
																			{
																				system("cls");
																				display();
																				break;	
																			}	
																				else
																				{
																					system("cls");
																					cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tInvalid Choice. Please try again."<<endl;
																					sleep(3);
																					system("cls");
																				}
																	if(fifthchoice == 1 || fifthchoice == 2)
																	{
																		system("cls");
																		display2();																
																		cout<<"\nPress any key to continue...";
																	    cin.ignore();
																	    cin.get();
																	}
																} while(fifthchoice != 1 && fifthchoice != 2 && fifthchoice != 3);
															}
																else if(fourthchoice == 5)
																{
																	system("cls");													
																	do
																	{			
																		f.open("product.txt"); 			
																		display_File1();
																		f.close();
																		cout<<"Enter 1 to Sort ALL Products By Category (M -> S -> D -> P)"<<endl;
																		cout<<"Enter 2 to Return"<<endl;
																		cout<<"\nWhat is your choice : ";
																		cin>>sixthchoice;
																		
																		if(sixthchoice == 1)	
																		{		
																			IS.insertionSortByCategory(P,count);					
																		}
																			else if(sixthchoice == 2)
																			{
																				system("cls");
																				display();
																				break;
																			}
																				else
																				{
																					system("cls");
																					cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tInvalid Choice. Please try again."<<endl;
																					sleep(3);
																					system("cls");
																				}
																		if(sixthchoice == 1)
																		{
																			system("cls");
																			display2();																	
																			cout<<"\nPress any key to continue...";
																		    cin.ignore();
																		    cin.get();
																		}
																	} while(sixthchoice != 1 && sixthchoice != 2);
																}
																	else if(fourthchoice == 6)
																	{
																		break;	
																	}
																		else
																		{
																			system("cls");
																		    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tInvalid Choice. Please try again."<<endl;
																		    sleep(3);												            
																			system("cls");
																		    display();
																		}
											} while(fifthchoice == 3 || sixthchoice == 2);
										} while(fourthchoice != 1 && fourthchoice != 2 && fourthchoice != 3 && fourthchoice!= 4 && fourthchoice != 5 && fourthchoice != 6);									
																							                    						                    
										if(exsits != true)
										{
											do
											{
												setColor(7);		
												system("cls");
												display1();
												cout<<"Enter 00 to continue displayed or sorted product."<<endl;
												cout<<"Enter 01 to exit."<<endl;
															                        
												cout<<"\nWhat is your choice : ";
												cin>>thirdchoice;
															                    
												if(thirdchoice != 00 && thirdchoice != 01)
												{
													system("cls");
													cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease enter valid choice. Thank You."<<endl;
													sleep(3);
												}																					
											} while (thirdchoice != 00 && thirdchoice != 01);
										}
									}
							} while(thirdchoice == 00 && exsits != true);
							resetAll();
							
							system("cls");
							cout<<"Note:"<<endl;
							cout<<"Enter 1 to insert menu item.                          "<<endl;
							cout<<"Enter 2 to deleted menu item.                         "<<endl;
							cout<<"Enter 3 to updated menu item.                         "<<endl;
							cout<<"Enter 4 to view menu item or sort menu item.          "<<endl;
							cout<<"Enter 5 to search menu item.                          "<<endl;
							cout<<"Enter 6 to exit.                                      "<<endl;
							cout<<"Enter other number to return back.                    "<<endl;
							display();							                        
							cout<<"What is your choice : ";
							cin>>choice;	
						}
							else if(choice == 5)
							{
								cout<<fixed<<setprecision(2);	
								do
								{		
									resetAll();							
									f.open("product.txt"); 
															
									if(!f)
									{
										cout<<"No Product found!\n";
										exit(0);
									}
											                
									system("cls");  
									displayFile();
									f.close();  							    
											                    
									//check whether inside file is empty or not
									if (pi == "" && pn == "" && pp == 0.00)
									{
										exsits = true;
										cout<<"The product is empty. Please insert the new product and can search product."<<endl;
										cout<<"\nPress any key to continue...";
									    cin.ignore();
									    cin.get();
										thirdchoice = -1;
									} 
										else
										{
											system("cls");
											do
											{
												f.open("product.txt"); 											
												display_File1();
												f.close();							
												//Search a product name or product id and list what you want to search
												cout<<"Enter 1 to search product by id.  "<<endl;
												cout<<"Enter 2 to search product by name."<<endl;
												cout<<"Enter 3 to exit.                  "<<endl;
												cout<<"\nWhat your to search? : ";
												cin>>search;
																
												if(search == 1)
												{
													system("cls");
													IS.insertionSortById_Asc(P,count);	
													display2();
													cout<<"Please enter your want to search product id : ";
													cin>>product_i;													
																
													result = BS.BinarySearchById(P,count,product_i);												
																											
													if(result != -1)
													{			
														system("cls");
														cout<<"--------------------------------------------------------------------------------------"<<endl;
														cout<<"        Product ID           Product Name          Product Price           Category   "<<endl;
														cout<<"--------------------------------------------------------------------------------------"<<endl;															                    
														cout<<setw(14)<<P[result].product_ID<<setw(26)<<P[result].product_name<<setw(17)<<"RM "<<P[result].product_price<<setw(19)<<P[result].category<<endl;
													}
														else
														{
															system("cls");										
															IS.insertionSortById_Asc(P,count);
															display2();
															cout<<"Data Not Found!!"<<endl;
														}
													cout<<"--------------------------------------------------------------------------------------"<<endl;
													cout<<"\nPress any key to continue...";
													cin.ignore();
													cin.get();
																	
													if(exsits != true)
													{
														do
														{
															setColor(7);		
															system("cls");
															display1();
															cout<<"Enter 00 to continue search product."<<endl;
															cout<<"Enter 01 to exit."<<endl;
																				                        
															cout<<"\nWhat is your choice : ";
															cin>>thirdchoice;
																				                    
															if(thirdchoice != 00 && thirdchoice != 01)
															{
																system("cls");
																cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease enter valid choice. Thank You."<<endl;
																sleep(3);
															}
																													
														} while (thirdchoice != 00 && thirdchoice != 01);
													}
												}
													else if(search == 2)
													{
														system("cls");
														IS.insertionSortByName_Asc(P,count);	
														display2();
														cout<<"Please enter your want to search product name : ";
														cin>>product_n;
																	
														result = BS.BinarySearchByName(P,count,product_n);
																		
														if(result != -1)
														{			
															system("cls");
															cout<<"--------------------------------------------------------------------------------------"<<endl;
															cout<<"        Product ID           Product Name          Product Price           Category   "<<endl;
															cout<<"--------------------------------------------------------------------------------------"<<endl;															                    
															cout<<setw(14)<<P[result].product_ID<<setw(26)<<P[result].product_name<<setw(17)<<"RM "<<P[result].product_price<<setw(19)<<P[result].category<<endl;
														}
															else
															{
																system("cls");												
																IS.insertionSortByName_Asc(P,count);
																display2();
																cout<<"Data Not Found!!"<<endl;
															}
														cout<<"--------------------------------------------------------------------------------------"<<endl;
														cout<<"\nPress any key to continue...";
														cin.ignore();
														cin.get();
															
														if(exsits != true)
														{
															do
															{
																setColor(7);		
																system("cls");
																display1();
																cout<<"Enter 00 to continue search product."<<endl;
																cout<<"Enter 01 to exit."<<endl;
																					                        
																cout<<"\nWhat is your choice : ";
																cin>>thirdchoice;
																					                    
																if(thirdchoice != 00 && thirdchoice != 01)
																{
																	system("cls");
																	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease enter valid choice. Thank You."<<endl;
																	sleep(3);
																}
																														
															} while (thirdchoice != 00 && thirdchoice != 01);
														}
													}
														else if(search == 3)
														{
															if(exsits != true)
															{
																do
																{
																	setColor(7);		
																	system("cls");
																	display1();
																	cout<<"Enter 00 to continue search product."<<endl;
																	cout<<"Enter 01 to exit."<<endl;
																						                        
																	cout<<"\nWhat is your choice : ";
																	cin>>thirdchoice;
																						                    
																	if(thirdchoice != 00 && thirdchoice != 01)
																	{
																		system("cls");
																		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease enter valid choice. Thank You."<<endl;
																		sleep(3);
																	}
																															
																} while (thirdchoice != 00 && thirdchoice != 01);
															}
															break;	
														}											
											} while(search != 1 && search != 2);	
										}			                    
								} while(thirdchoice == 00 && exsits != true);
								resetAll();								
								system("cls");
								cout<<"Note:"<<endl;
								cout<<"Enter 1 to insert menu item.                          "<<endl;
								cout<<"Enter 2 to deleted menu item.                         "<<endl;
								cout<<"Enter 3 to updated menu item.                         "<<endl;
								cout<<"Enter 4 to view menu item or sort menu item.          "<<endl;
								cout<<"Enter 5 to search menu item.                          "<<endl;
								cout<<"Enter 6 to exit.                                      "<<endl;
								cout<<"Enter other number to return back.                    "<<endl;
								display();							                        
								cout<<"What is your choice : ";
								cin>>choice;
							}
								else if(choice == 6)
								{
									pauseScreen();							
								}
										else
										{
											system("cls");
								            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease enter valid choice. Thank You."<<endl;
								            sleep(3);
										}
		
		} while (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5);
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6); 
}

void Admin::viewFeedback() 
{
    clearScreen();
    displayHeader("CUSTOMER FEEDBACK");
    
    ifstream file("feedback.txt");
    Feedback fb;
    
    cout<<"ID"<<setw(13)<<"Customer"<<setw(10)<<"Rating"<<setw(10)<<"Comment"<<setw(30)<<"Date"<<"\n";
    cout<<string(75, '-')<<"\n";
    
    while (file >> fb.feedbackID >> fb.username >> fb.rating >> fb.comment >> fb.date) 
	{
        cout<<fb.feedbackID<<setw(15)<<fb.username<<setw(6)<<fb.rating<<setw(10)<<fb.comment<<setw(36)<<fb.date<<"\n";
    }
    file.close();
    
    pauseScreen();
}

void Admin::sortAllBookings() 
{
    clearScreen();
    displayHeader("SORT BOOKINGS");
    
    cout<<"Sort by:\n";
    cout<<"1. Date\n";
    cout<<"2. Table Number\n";
    cout<<"3. Time Slot\n";
    int choice;
    cin>>choice;
    
    BookingData* bookings;
    int size;
    loadBookingsToArray(bookings, size);
    
    if (size == 0) 
	{
        cout<<"No bookings found.\n";
        pauseScreen();
        return;
    }
    
    sortBookings(bookings, size, choice);
    
    cout<<"\nSorted Bookings:\n";
    cout<<"ID"<<setw(15)<<"Customer"<<setw(10)<<"Table"<<setw(15)<<"Date"<<setw(15)<<"Time"<<"\n";
    cout<<string(65, '-')<<"\n";
    
    for (int i = 0; i < size; i++) 
	{
        cout<<bookings[i].bookingID<<setw(14)<<bookings[i].username<<setw(7)<<bookings[i].tableNumber<<setw(20)<<bookings[i].date<<setw(15)<<getTimeSlotDisplay(bookings[i].timeSlot)<<"\n";
    }
    
    delete[] bookings;
    pauseScreen();
}

void Admin::deleteBooking() 
{
    clearScreen();
    displayHeader("DELETE BOOKING");
    
    int id;
    cout<<"Enter booking ID to delete: ";
    cin>>id;
    
    BookingData* bookings;
    int size;
    loadBookingsToArray(bookings, size);
    
    bool found = false;
    for (int i = 0; i < size; i++) 
	{
        if (bookings[i].bookingID == id) 
		{
            strcpy(bookings[i].status, "cancelled");
            found = true;
            break;
        }
    }
    
    if (found) 
	{
        saveBookingsFromArray(bookings, size);
        cout<<"\nBooking deleted successfully!\n";
    } 
		else 
		{
        	cout<<"Booking not found.\n";
    	}
    
    delete[] bookings;
    pauseScreen();
}

void Admin::generateReports() 
{
    clearScreen();
    displayHeader("GENERATE REPORTS");
    
    ofstream outFile("admin_reports.txt");
    
    outFile<<"=== MONTHLY BOOKING REPORT ===\n";
    outFile<<"Report Generated: November 2025\n\n";
    
    ifstream inFile("bookings.txt");
    BookingData booking;
    int total = 0, confirmed = 0, cancelled = 0;
    int tableCounts[11] = {0};
    int slotCounts[6] = {0};
    
    while (inFile >> booking.bookingID >> booking.username >> booking.tableNumber >> booking.date >> booking.timeSlot >> booking.phone >> booking.status) 
	{
        total++;
        if (strcmp(booking.status, "confirmed") == 0) 
		{
			confirmed++;
		}
		
        if (strcmp(booking.status, "cancelled") == 0) 
		{
			cancelled++;
		}
        tableCounts[booking.tableNumber]++;
        slotCounts[booking.timeSlot]++;
    }
    inFile.close();
    
    outFile<<"Total Bookings: "<<total<<"\n";
    outFile<< "Confirmed: "<<confirmed<<"\n";
    outFile<<"Cancelled: "<<cancelled<<"\n";
    outFile<<"Cancellation Rate: "<<fixed<<setprecision(2)<<(total > 0 ? (cancelled * 100.0 / total) : 0)<< "%\n\n";
    
    outFile << "=== TABLE POPULARITY ===\n";
    int maxTable = 1;
    for (int i = 1; i <= 10; i++) 
	{
        if (tableCounts[i] > tableCounts[maxTable]) 
		{
			maxTable = i;
		}        
		outFile<<"Table "<<i<<": "<<tableCounts[i]<<" bookings\n";
    }
    outFile<<"\nMost Popular Table: Table "<<maxTable<<"\n\n";
    
    outFile<<"=== TIME SLOT POPULARITY ===\n";
    int maxSlot = 1;
    for (int i = 1; i <= 5; i++) 
	{
        if (slotCounts[i] > slotCounts[maxSlot]) 
		{
			maxSlot = i;
		}
        outFile<<"Slot "<<i<<" ("<<getTimeSlotDisplay(i)<<"): "<<slotCounts[i]<<" bookings\n";
    }
    outFile<<"\nMost Popular Time: "<<getTimeSlotDisplay(maxSlot)<<"\n";
    outFile<<"===========================\n";
    
    outFile.close();
    
    cout<<"Report saved to: admin_reports.txt\n\n";
    
    ifstream displayFile("admin_reports.txt");
    string line;
    while (getline(displayFile, line)) 
	{
        cout<<line<<"\n";
    }
    displayFile.close();
    
    pauseScreen();
}

void Admin::manageWaitingList() 
{
    clearScreen();
    displayHeader("WAITING LIST MANAGEMENT");
    
    waitingQueue.display();
    
    cout<<"\n1. Process Next in Queue\n";
    cout<<"2. View Queue Only\n";
    int choice;
    cin>>choice;
    
    if (choice == 1) 
	{
        char user[50], dt[11];
        int table, slot;
        
        if (waitingQueue.dequeue(user, table, dt, slot)) 
		{
            cout<<"\nProcessing booking for: "<<user<<"\n";
            cout<<"Table: "<<table<<", Date: "<<dt<<", Slot: "<<slot<< "\n";
            cout<<"Notified customer to confirm booking.\n";
        } 
			else 
			{
            	cout<<"Queue is empty.\n";
        	}
    }
    
    pauseScreen();
}

// ==================== MAIN FUNCTION ====================
int main() 
{
    NewUser loginSystem;
    int choice;
    
    do 
	{
        clearScreen();
        setColor(7);
        displayHeader("RESTAURANT BOOKING SYSTEM");
        cout<<"          1. Customer Login\n";
        cout<<"          2. Customer Register\n";
        cout<<"          3. Admin Login\n";
        cout<<"          0. Exit\n";
        cout<<"\n          Enter choice: ";
        cin>>choice;
        
        switch(choice) 
		{
            case 1: 
			{
	                Customer customer;
	                if (customerLogin(customer, loginSystem)) 
					{
	                    customer.displayMenu();
	                }
	                break;
            }
            case 2: 
			{
	                loginSystem.registeruser();
	                break;
            }
            case 3: 
			{
	                Admin admin;
	                if (adminLogin(admin)) 
					{
	                    admin.displayMenu();
	                }
	                break;
            }
            case 0:
	                clearScreen();
	                setColor(10);
	                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tThank you for using our system!\n";
	                Sleep(2000);
	                setColor(7);
	                break;
            default:
	                cout<<"\nInvalid choice!\n";
	                pauseScreen();
        }
    } while(choice != 0);
    
    return 0;
}
