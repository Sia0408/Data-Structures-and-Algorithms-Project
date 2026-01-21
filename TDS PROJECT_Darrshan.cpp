// USER MODULE: ADD BOOKING + DISPLAY BOOKINGS

#include <fstream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <cstdio>     
#include <cstdlib>    
#include <conio.h>    
#include <windows.h>  
#include <iostream>


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

// -----------------------------
// Linked List Node
// -----------------------------
struct BookingNode
{
    BookingRecord data;
    BookingNode* next;
};

void initBookingList(BookingNode*& head, BookingNode*& tail)
{
    head = NULL;
    tail = NULL;
}

void insertBookingEnd(BookingNode*& head, BookingNode*& tail, const BookingRecord& rec)
{
    BookingNode* temp = new BookingNode;
    temp->data = rec;
    temp->next = NULL;

    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}

void freeBookingList(BookingNode*& head)
{
    while (head != NULL)
    {
        BookingNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void loadBookingsToList(BookingNode*& head, BookingNode*& tail, const char* filename = "bookings.txt")
{
    initBookingList(head, tail);

    std::ifstream in(filename);
    if (!in.is_open())
    {
        
        return;
    }

    BookingRecord b{};
    while (in >> b.bookingID >> b.customerName >> b.date >> b.time
              >> b.tableNumber >> b.numberOfGuests >> b.phoneNumber >> b.status)
    {
        insertBookingEnd(head, tail, b);
    }
}

int getMaxBookingNumber(BookingNode* head)
{
    int maxNum = 0;
    BookingNode* temp = head;

    while (temp != NULL)
    {
        
        if (temp->data.bookingID[0] == 'B' || temp->data.bookingID[0] == 'b')
        {
            int num = std::atoi(temp->data.bookingID + 1);
            if (num > maxNum) maxNum = num;
        }
        temp = temp->next;
    }
    return maxNum;
}

bool appendBookingToFile(const BookingRecord& b, const char* filename = "bookings.txt")
{
    std::ofstream out(filename, std::ios::app);
    if (!out.is_open()) return false;

    out << b.bookingID << " "
        << b.customerName << " "
        << b.date << " "
        << b.time << " "
        << b.tableNumber << " "
        << b.numberOfGuests << " "
        << b.phoneNumber << " "
        << b.status << "\n";

    return true;
}

// =====================================================
// FUNCTION 1: ADD BOOKING (User)
// =====================================================
void addBooking_LL(char* currentUsername)
{
    try
    {
        if (currentUsername == NULL || std::strlen(currentUsername) == 0)
            throw std::runtime_error("Username is empty.");

        BookingNode* head = NULL;
        BookingNode* tail = NULL;

        loadBookingsToList(head, tail);
        int nextNum = getMaxBookingNumber(head) + 1;

        BookingRecord b{};
        std::snprintf(b.bookingID, sizeof(b.bookingID), "B%03d", nextNum);
        std::strncpy(b.customerName, currentUsername, sizeof(b.customerName) - 1);

        system("cls");
        std::cout << "------------------------------------------------------\n";
        std::cout << "                     ADD BOOKING\n";
        std::cout << "------------------------------------------------------\n";
        std::cout << "Booking ID : " << b.bookingID << "\n";
        std::cout << "Username   : " << b.customerName << "\n\n";

        std::cout << "Enter date (DD/MM/YYYY) : ";
        std::cin >> b.date;

        std::cout << "Enter time (HH:MM)      : ";
        std::cin >> b.time;

        std::cout << "Enter table number      : ";
        std::cin >> b.tableNumber;

        std::cout << "Enter number of guests  : ";
        std::cin >> b.numberOfGuests;

        std::cout << "Enter phone number      : ";
        std::cin >> b.phoneNumber;

        std::strncpy(b.status, "CONFIRMED", sizeof(b.status) - 1);

        if (b.tableNumber <= 0) throw std::runtime_error("Invalid table number.");
        if (b.numberOfGuests <= 0) throw std::runtime_error("Invalid number of guests.");

        // store in linked list 
        insertBookingEnd(head, tail, b);

        // save to file (persistence)
        if (!appendBookingToFile(b))
            throw std::runtime_error("Failed to write to bookings.txt");

        std::cout << "\n\t\tBooking created successfully!\n";
        std::cout << "\t\tYour Booking ID: " << b.bookingID << "\n";
        std::cout << "\n\t\tPress any key to continue...";
        _getch();

        freeBookingList(head);
    }
    catch (const std::exception& e)
    {
        std::cout << "\n\t\t[ERROR] " << e.what() << "\n";
        std::cout << "\t\tPress any key to continue...";
        _getch();
    }
}

// =====================================================
// FUNCTION 2: DISPLAY BOOKINGS (User)
// =====================================================
void displayBookings_LL(char* currentUsername)
{
    try
    {
        if (currentUsername == NULL || std::strlen(currentUsername) == 0)
            throw std::runtime_error("Username is empty.");

        BookingNode* head = NULL;
        BookingNode* tail = NULL;

        loadBookingsToList(head, tail);

        system("cls");
        std::cout << "------------------------------------------------------\n";
        std::cout << "                    MY BOOKINGS\n";
        std::cout << "------------------------------------------------------\n\n";

        std::cout << std::left
                  << std::setw(8)  << "ID"
                  << std::setw(12) << "Date"
                  << std::setw(8)  << "Time"
                  << std::setw(8)  << "Table"
                  << std::setw(8)  << "Guests"
                  << std::setw(15) << "Phone"
                  << std::setw(12) << "Status" << "\n";

        std::cout << "-----------------------------------------------------------------------\n";

        bool found = false;

       
        BookingNode* temp = head;
        while (temp != NULL)
        {
            if (std::strcmp(temp->data.customerName, currentUsername) == 0)
            {
                found = true;
                std::cout << std::left
                          << std::setw(8)  << temp->data.bookingID
                          << std::setw(12) << temp->data.date
                          << std::setw(8)  << temp->data.time
                          << std::setw(8)  << temp->data.tableNumber
                          << std::setw(8)  << temp->data.numberOfGuests
                          << std::setw(15) << temp->data.phoneNumber
                          << std::setw(12) << temp->data.status << "\n";
            }
            temp = temp->next;
        }

        if (!found)
            std::cout << "\n\t\tNo bookings found for your account.\n";

        std::cout << "\n\t\tPress any key to continue...";
        _getch();

        freeBookingList(head);
    }
    catch (const std::exception& e)
    {
        std::cout << "\n\t\t[ERROR] " << e.what() << "\n";
        std::cout << "\t\tPress any key to continue...";
        _getch();
    }
}
