#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;

void setColor(int textColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,textColor);
}

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
				sleep(3);
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
	                	sleep(3);
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
		                	sleep(3);
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
				sleep(1);
				cout<<".";
				sleep(1);
				cout<<".";
				sleep(1);
				cout<<".";
				sleep(1);
				system("cls");
								
				setColor(10);
				cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tSuccessful Register Account.";
				sleep(3);
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
						sleep(1);
						cout<<".";
						sleep(1);
						cout<<".";
						sleep(1);
						cout<<".";
						sleep(1);
						system("cls");
						
						setColor(10);
						cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tSuccessful Account.";
						sleep(3);
						system("cls");
					}
						else
						{
							while(!checking && (attempts <= 2))
							{
								a = 0;
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
								cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tFailed Account.";
								sleep(3);
								
								system("cls");
								setColor(7);
								cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\tInvalid username or password, please re-enter correct username and password."<<endl;
								sleep(3);
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
										sleep(1);
										cout<<".";
										sleep(1);
										cout<<".";
										sleep(1);
										cout<<".";
										sleep(1);
										system("cls");
								
										setColor(10);
										cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tSuccessful Account.";
										sleep(3);
										system("cls");
										setColor(7);
										cout<<"\n";
										cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tAccess Granted in the System.";
										sleep(3);
										system("cls");
									}
							}
									
								if(!checking && attempts > 2)
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
									cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tFailed Account.";
									sleep(3);
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
				cout<<"                             1.                                    "<<endl;
				cout<<"                             2.                                    "<<endl;
				cout<<"                             3.                                    "<<endl;
				cout<<"                             4.                                    "<<endl;
				cout<<"                             5. Log Out                            "<<endl;
				cout<<"                             6. Exit                               "<<endl;
				cout<<"-------------------------------------------------------------------"<<endl;
			}
};

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
			
			if(choice == 'A')
			{
				conti = C->Checklogin();
			}
				else if(choice == 'B')
				{
					C->registeruser();
					conti = C->Checklogin();
				}
					else if(choice == 'C')
					{
						
					}
						else if(choice == 'D')
						{
							cout<<"Thank You for your services. Have a nice day."<<endl;
							exit(0);
						}
								else
								{
									cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease re-enter your valid choice."<<endl;
									sleep(3);
								}
		} while(choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' || conti == 'Y' || conti == 'y');
		
			do
			{
				system("cls");
				setColor(7);
				S.DisplaystoreMenu();
				cout<<"Enter your choice : ";
				cin>>choice1;
				
				if(choice1 == 1)
				{
					
				}	
					else if(choice1 == 2)
					{
						
					}
						else if(choice1 == 3)
						{
							
						}
							else if(choice1 == 4)
							{
								
							}
								else if(choice1 == 5)
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
									cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tLog Out Successfully.";
									sleep(3);
								}
									else if(choice1 == 6)
									{
										system("cls");
									}
										else
										{
											system("cls");
											cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tPlease re-enter your valid choice."<<endl;
											sleep(3);
										}
			} while (choice1 != 1 && choice1 != 2 && choice1 != 3 && choice1 != 4 && choice1 != 5 && choice1 != 6);
			
	} while(choice1 == 5 && choice != 6);
	delete C;
	return 0;
}