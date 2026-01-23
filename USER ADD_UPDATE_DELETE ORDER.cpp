// ===============================
// USER ORDER FOOD MODULE (Linked List + product.txt)
// Records: OrderItem (id, name, price, category, qty)
// Functions: Add / Update / Delete / Display
// ===============================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <conio.h>

using namespace std;

// -------------------------------
// MENU RECORD (from product.txt)
// -------------------------------
struct MenuItem
{
    char id[20];
    char name[50];
    double price;
    char category[10];
};

// -------------------------------
// ORDER LINKED LIST NODE
// -------------------------------
struct OrderNode
{
    MenuItem item;     // id, name, price, category
    int qty;           // user quantity
    OrderNode* next;
};

// -------------------------------
// Load menu from product.txt into array (NO vector)
// product.txt format example:  M1 Handburger 3 M
// -------------------------------
int loadMenu(MenuItem menu[], int maxSize, const char* filename = "product.txt")
{
    ifstream fin(filename);
    if(!fin.is_open()) return 0;

    int count = 0;
    while(count < maxSize &&
          fin >> menu[count].id >> menu[count].name >> menu[count].price >> menu[count].category)
    {
        count++;
    }
    fin.close();
    return count;
}

void displayMenu(const MenuItem menu[], int count)
{
    cout << "\n==================== MENU LIST ====================\n";
    cout << left << setw(10) << "ID"
         << setw(20) << "NAME"
         << setw(12) << "PRICE(RM)"
         << setw(10) << "CAT" << "\n";
    cout << "---------------------------------------------------\n";

    for(int i = 0; i < count; i++)
    {
        cout << left << setw(10) << menu[i].id
             << setw(20) << menu[i].name
             << setw(12) << fixed << setprecision(2) << menu[i].price
             << setw(10) << menu[i].category << "\n";
    }
    cout << "---------------------------------------------------\n";
}

int findMenuIndexById(const MenuItem menu[], int count, const char* targetId)
{
    for(int i = 0; i < count; i++)
    {
        if(strcmp(menu[i].id, targetId) == 0)
            return i;
    }
    return -1;
}

// -------------------------------
// Linked-list helpers
// -------------------------------
void initOrderList(OrderNode*& head, OrderNode*& tail)
{
    head = NULL;
    tail = NULL;
}

OrderNode* createOrderNode(const MenuItem& mi, int qty)
{
    OrderNode* n = new OrderNode;
    n->item = mi;
    n->qty = qty;
    n->next = NULL;
    return n;
}

OrderNode* findOrderNode(OrderNode* head, const char* targetId)
{
    OrderNode* cur = head;
    while(cur != NULL)
    {
        if(strcmp(cur->item.id, targetId) == 0)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

void addOrderItem(OrderNode*& head, OrderNode*& tail, const MenuItem& mi, int qty)
{
    // if already exists, just add quantity
    OrderNode* existing = findOrderNode(head, mi.id);
    if(existing != NULL)
    {
        existing->qty += qty;
        return;
    }

    // otherwise add new node at end (lecture-style insert end)
    OrderNode* node = createOrderNode(mi, qty);
    if(head == NULL)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
}

bool updateOrderQty(OrderNode* head, const char* id, int newQty)
{
    OrderNode* n = findOrderNode(head, id);
    if(n == NULL) return false;

    n->qty = newQty;
    return true;
}

bool deleteOrderItem(OrderNode*& head, OrderNode*& tail, const char* id)
{
    OrderNode* cur = head;
    OrderNode* prev = NULL;

    while(cur != NULL)
    {
        if(strcmp(cur->item.id, id) == 0)
        {
            if(prev == NULL) // delete head
                head = cur->next;
            else
                prev->next = cur->next;

            if(cur == tail) // if deleting tail
                tail = prev;

            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

double calcOrderTotal(OrderNode* head)
{
    double total = 0.0;
    OrderNode* cur = head;
    while(cur != NULL)
    {
        total += (cur->item.price * cur->qty);
        cur = cur->next;
    }
    return total;
}

void displayOrder(OrderNode* head)
{
    cout << "\n==================== YOUR ORDER ====================\n";
    if(head == NULL)
    {
        cout << "No items ordered yet.\n";
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(18) << "NAME"
         << setw(10) << "CAT"
         << setw(8)  << "QTY"
         << setw(12) << "PRICE"
         << setw(12) << "SUBTOTAL" << "\n";
    cout << "----------------------------------------------------\n";

    OrderNode* cur = head;
    while(cur != NULL)
    {
        double sub = cur->item.price * cur->qty;
        cout << left << setw(10) << cur->item.id
             << setw(18) << cur->item.name
             << setw(10) << cur->item.category
             << setw(8)  << cur->qty
             << setw(12) << fixed << setprecision(2) << cur->item.price
             << setw(12) << fixed << setprecision(2) << sub << "\n";
        cur = cur->next;
    }
    cout << "----------------------------------------------------\n";
    cout << "TOTAL: RM " << fixed << setprecision(2) << calcOrderTotal(head) << "\n";
}

void freeOrderList(OrderNode*& head)
{
    while(head != NULL)
    {
        OrderNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Optional: save order lines to ONE shared file for record consistency (admin can read too)
// Format: username id name price category qty
bool appendOrderToFile(const char* username, OrderNode* head, const char* filename="orders.txt")
{
    ofstream fout(filename, ios::app);
    if(!fout.is_open()) return false;

    OrderNode* cur = head;
    while(cur != NULL)
    {
        fout << username << " "
             << cur->item.id << " "
             << cur->item.name << " "
             << cur->item.price << " "
             << cur->item.category << " "
             << cur->qty << "\n";
        cur = cur->next;
    }
    return true;
}

// -------------------------------
// USER MENU (Add / Update / Delete / Display)
// Call: userOrderFoodMenu(currentUsername);
// -------------------------------
void userOrderFoodMenu(char* currentUsername)
{
    try
    {
        if(currentUsername == NULL || strlen(currentUsername) == 0)
            throw runtime_error("Username is empty (order module).");

        MenuItem menu[200];
        int menuCount = loadMenu(menu, 200, "product.txt");
        if(menuCount == 0)
            throw runtime_error("Menu file (product.txt) not found or empty.");

        OrderNode* head = NULL;
        OrderNode* tail = NULL;
        initOrderList(head, tail);

        int choice = 0;
        do
        {
            system("cls");
            cout << "========================================\n";
            cout << "         ORDER FOOD (USER MENU)\n";
            cout << "========================================\n";
            cout << "Logged in as: " << currentUsername << "\n\n";
            cout << "1. Display Menu\n";
            cout << "2. Add Order Food\n";
            cout << "3. Update Order Quantity\n";
            cout << "4. Delete Order Item\n";
            cout << "5. Display Current Order\n";
            cout << "6. Checkout (save to orders.txt)\n";
            cout << "7. Back\n";
            cout << "----------------------------------------\n";
            cout << "Enter choice: ";
            cin >> choice;

            if(choice == 1)
            {
                system("cls");
                displayMenu(menu, menuCount);
                cout << "\nPress any key...";
                _getch();
            }
            else if(choice == 2)
            {
                system("cls");
                displayMenu(menu, menuCount);

                char id[20];
                int qty;
                cout << "\nEnter Product ID to add: ";
                cin >> id;

                int idx = findMenuIndexById(menu, menuCount, id);
                if(idx == -1)
                {
                    cout << "Item not found. Press any key...";
                    _getch();
                }
                else
                {
                    cout << "Enter quantity: ";
                    cin >> qty;
                    if(qty <= 0) throw runtime_error("Quantity must be > 0.");

                    addOrderItem(head, tail, menu[idx], qty);
                    cout << "Added to order. Press any key...";
                    _getch();
                }
            }
            else if(choice == 3)
            {
                system("cls");
                displayOrder(head);

                char id[20];
                int newQty;
                cout << "\nEnter Product ID to update: ";
                cin >> id;
                cout << "Enter new quantity: ";
                cin >> newQty;

                if(newQty <= 0)
                    throw runtime_error("New quantity must be > 0.");

                if(updateOrderQty(head, id, newQty))
                    cout << "Updated. Press any key...";
                else
                    cout << "Item not found in order. Press any key...";
                _getch();
            }
            else if(choice == 4)
            {
                system("cls");
                displayOrder(head);

                char id[20];
                cout << "\nEnter Product ID to delete: ";
                cin >> id;

                if(deleteOrderItem(head, tail, id))
                    cout << "Deleted. Press any key...";
                else
                    cout << "Item not found in order. Press any key...";
                _getch();
            }
            else if(choice == 5)
            {
                system("cls");
                displayOrder(head);
                cout << "\nPress any key...";
                _getch();
            }
            else if(choice == 6)
            {
                system("cls");
                displayOrder(head);

                if(head == NULL)
                {
                    cout << "\nNothing to checkout. Press any key...";
                    _getch();
                }
                else
                {
                    if(!appendOrderToFile(currentUsername, head, "orders.txt"))
                        throw runtime_error("Failed to write orders.txt");

                    cout << "\nCheckout saved to orders.txt.\n";
                    cout << "Press any key...";
                    _getch();

                    // clear current order after checkout
                    freeOrderList(head);
                    initOrderList(head, tail);
                }
            }

        } while(choice != 7);

        freeOrderList(head);
    }
    catch(const exception& e)
    {
        cout << "\n[ORDER ERROR] " << e.what() << "\nPress any key...";
        _getch();
    }
}
