#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;


struct MenuItem {
    int id;
    string name;
    double price;
};

struct User {
    string name;
    string birthday;
    string email;
    string password;
    string phone_number;
    bool employee;
};

struct OrderedItem {
    string name;
    double price;
    int quantity;
};

struct Order {
    string customer_name;
    string order_date;
    double total_price;
    OrderedItem* ordered_items;
};
string Get_Date() {
    string stringTime;
    time_t tmNow;
    time(&tmNow);
    struct tm t;
    localtime_s(&t, &tmNow);
    string mon;
    if (t.tm_mon + 1 > 0 && t.tm_mon + 1 < 10)
        mon = "0" + to_string(t.tm_mon + 1);
    else
        mon = to_string(t.tm_mon + 1);
    stringTime = mon + "-" + to_string(t.tm_mday) + "-" + to_string(t.tm_year + 1900);
    return stringTime;
}
int getlinesnumber(string filename) {
    ifstream line(filename);
    int count = 0;
    string linecount;
    while (getline(line,linecount)) {
        count++;

    }
    return count;

}
bool checkemail(User* data, string email) {
    int num = getlinesnumber("users.txt");
    for (int i = 0; i < num; i++)
    {
        if (data[i].email == email)
        {
            return 1;
        }
    }
    return 0;
}
bool unique(User* data, string unique, int cas) {
    int num = getlinesnumber("users.txt");
    if (cas == 0) {
        for (int i = 0; i < num; i++)
        {
            if (data[i].email == unique)
            {
                return 0;
            }
        }
        return 1;
    }
    if (cas == 1) {
        for (int i = 0; i < num; i++)
        {
            if (data[i].password == unique)
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
void addfood()
{
    MenuItem add;

    do {
        cout << "enter the food id: ";
        cin >> add.id;
    } while (add.id < 0);
    cin.ignore();
    cout << "Enter food name: ";
    getline(cin,add.name);
    cout << "Enter the price: ";
    cin >> add.price;
    ofstream print("menu.txt" , ios::app);
    print << add.id << "\t";
    print << add.name << "\t";
    print << add.price << "\n";
    print.close();
    
}
void DisplayUsers(MenuItem* menu) {
    int usersnum = getlinesnumber("users.txt");
    User* database = new User[usersnum];
    ifstream read("users.txt");
    for (int i = 0; i < usersnum; i++)
    {
        getline(read, database[i].name, '\t');
        getline(read, database[i].birthday, '\t');
        getline(read, database[i].email, '\t');
        getline(read, database[i].password, '\t');
        getline(read, database[i].phone_number, '\t');
        read >> database[i].employee;
    }
    read.close();
     for (int i = 0; i < usersnum; i++)
     {
         cout<<  database[i].name<< '\t';
         cout << database[i].birthday << '\t';
         cout << database[i].email << '\t';
         cout << database[i].password << '\t';
         cout << database[i].phone_number << '\t';
         cout << database[i].employee << endl;
     }
     
}
void DisplayFoodItems(MenuItem* menu) {
    int m = getlinesnumber("menu.txt");
    for (int i = 0; i < m ; i++)
    {
        cout<< menu[i].id<<'\t';
        cout << menu[i].name << '\t';
        cout<< menu[i].price << '\n';
    }
}
void EditFoodItem(MenuItem* menu) {
    DisplayFoodItems(menu);
    int m = getlinesnumber("menu.txt");
    int ID;
    cout << "Enter the ID of the item you want to edit: ";
    cin >> ID;
    cin.ignore(1, '\n');
    for (int i = 0; i < m; i++)
    {
        if (ID == menu[i].id)
        {
            cout << "enter new name: ";
            getline(cin, menu[i].name);
            cout << "Enter new price: ";
            cin >> menu[i].price;
        }

    }
    ofstream print("menu.txt");
    for (int i = 0; i < m; i++) {
        print << menu[i].id << "\t";
        print << menu[i].name << "\t";
        print << menu[i].price << "\n";
    }
    print.close();
}
void DeleteItem(MenuItem*menu) {
    int m = getlinesnumber("menu.txt");
    int ID;
    cout << "Enter the ID of the item you want to edit: ";
    cin >> ID;
    cin.ignore(1, '\n');
    for (int i = ID - 1; i < m - 1; i++)
    {
        menu[i].name = menu[i + 1].name;
        menu[i].price = menu[i + 1].price;
    }
    m--;
    ofstream write("menu.txt");
    for (int i = 0; i < m; i++)
    {
        write << menu[i].id << '\t';
        write << menu[i].name << '\t';
        write << menu[i].price << endl;
    }
    write.close();

}
int ExistedID(MenuItem*menu,int id,int nb)
{
    for (int i = 0; i < nb; i++)
    {
        if (menu[i].id == id)
            return i+1;
    }
    return 0;
}
void Menu(User cos) {
    int choice;
    ifstream readitem("menu.txt");
    MenuItem menu[20];
    int m = getlinesnumber("menu.txt");
    for (int i = 0; i < m; i++)
    {
        readitem >> menu[i].id;
        readitem.ignore();
        getline(readitem, menu[i].name, '\t');
        readitem >> menu[i].price;
    }
    readitem.close();
    int l = getlinesnumber("menu.txt");
    for (int i = 0; i < l; i++)
    {
        cout << menu[i].id << '\t';
        cout << menu[i].name << '\t';
        cout << menu[i].price << '\n';
    }
    int OrdersNum=0;
    int Again = 1;
    double TAX = 0, REDU = 0, TOTAL = 0;
    Order  order;
    order.ordered_items = new OrderedItem[l];
    int place = 0;
    bool IsBirth=0;
    order.customer_name = cos.name;
    order.order_date = Get_Date();
    order.total_price = 0;
    if ((order.order_date.substr(0, 5)) == (cos.birthday.substr(0, 5)))
        IsBirth =1;
    do {
        TAX = 0;
        REDU = 0;
        place = 0;
        while (place == 0)
        {
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();
            place = ExistedID(menu, choice, l);
        } 
        cout << "Please enter quantity: ";
        cin >> order.ordered_items[OrdersNum].quantity;
        order.ordered_items[OrdersNum].name = menu[place-1].name;
        order.ordered_items[OrdersNum].price = menu[place-1].price;
        TOTAL = order.ordered_items[OrdersNum].quantity * order.ordered_items[OrdersNum].price;
        cout << order.ordered_items[OrdersNum].name << ", price " << order.ordered_items[OrdersNum].price << ", quantity" << order.ordered_items[OrdersNum].quantity << ", amount" << TOTAL << endl;
        TAX = TOTAL * 1.04;
        cout << "Total after tax" << TAX<<endl;

        if (IsBirth == 1)
        {
            REDU = TAX * 0.98;
            cout << "happy birthday " << cos.name << " you get a 2% discount" << endl;
            cout << "total after reduction: " << REDU << endl;
            order.total_price = order.total_price + REDU;
        }
        else
            order.total_price = order.total_price + TAX;
        do {
            cout << "do you want to ordre another item(1/0)";
            cin >> Again;
        } while (Again != 1 && Again != 0);
        OrdersNum++;
    } while (Again == 1);
    cout << "your Total is " << order.total_price << "$";
    ofstream OTF("orders.txt", ios::app);
    OTF << order.customer_name << "\t" << order.order_date << "\t" << order.total_price << endl;
    for(int i=0;i<OrdersNum;i++)
    {
        OTF << "@\t" << order.ordered_items[i].name << "\t" << order.ordered_items[i].price << "\t" << order.ordered_items[i].quantity << endl;
    }
    OTF.close();
}
int countAT(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open the file: " << filename << endl;
        return 0;
    }

    int count = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty() && line[0] == '@') {
            ++count;
        }
    }
    file.close();

    return count;
}
void PayRoll() {
    int nboflines = getlinesnumber("orders.txt") - countAT("orders.txt");
    string temp;
    string comp;
    Order* order = new Order[getlinesnumber("orders.txt")];
    ifstream get("orders.txt");
    int ordernum = 0;
    for (int i = 1; i < getlinesnumber("orders.txt"); i++) {
        getline(get, comp, '\t');
        if (comp != "@") {
            order[ordernum].customer_name=comp;
            getline(get, order[ordernum].order_date, '\t');
            get >> order[ordernum].total_price;
            get.ignore(1, '\n');
            ordernum++;
        }
        else {
            getline(get, temp, '\n');
        }

    }
    get.close();
    for (int i = 0; i < nboflines; i++) {
        cout << order[i].customer_name << "\t";
        cout << order[i].order_date << "\t";
        cout << order[i].total_price << "\n";
    }

    int month;
    bool validInput = false;
    do {
        cout << "Enter the month in which you want to estimate your payroll: ";
        cin >> month;
        if (month) {
            cin.ignore(1, '\n');
            validInput = true;
        }
        else {
            cin.clear();
            cin.ignore();
            validInput = false;
        }
    } while (validInput == false || month < 1 || month > 12);

    Order* Mon = new Order[nboflines];
    int count = 0;
    for (int i = 0; i < nboflines; i++) {
        if (stoi(order[i].order_date.substr(0, 2)) == month) {
            Mon[count] = order[i];
            count++;
        }
    }

    for (int i = 0; i < count; i++) {
        cout << Mon[i].customer_name << "\t" << Mon[i].order_date << "\t" << Mon[i].total_price<< "\n";
    }
    cout << endl;

    int day;
    validInput = false;
    int again = 1;
    float totalpayroll = 0;
    while (again == 1) {
        do {
            cout << "Enter your working day: ";
            cin >> day;
            if (day) {
                cin.ignore(1, '\n');
                validInput = true;
            }
            else {
                cin.clear();
                cin.ignore();
                validInput = false;
            }
        } while (validInput == false || day < 1 || day > 31);

        float payroll = 0;
        for (int i = 0; i < count; i++) {
            if (stoi(Mon[i].order_date.substr(3, 2)) == day) {
                payroll += Mon[i].total_price;
                Mon[i].total_price = 0;
            }
        }

        cout << "Your payroll on Mon day is: " << payroll * 0.15 << endl;

        validInput = false;
        do {
            cout << "Do you want to choose another day? (yes/no) (1/2): ";
            cin >> again;
            if (again) {
                cin.ignore(1, '\n');
                validInput = true;
            }
            else {
                cin.clear();
                cin.ignore();
                validInput = false;
            }
        } while (validInput == false || again < 1 || again > 2);

        totalpayroll += payroll;
    }

    cout << endl;
    cout << "Your total payroll" << totalpayroll * 0.15 << endl;

    delete[] order;
    delete[] Mon;
}
void Admin(User emp){
    int choice;
    ifstream readitem("menu.txt");
    MenuItem menu[20];
    int m = getlinesnumber("menu.txt");
    for (int i = 0; i < m; i++)
    {
        readitem >> menu[i].id;
        readitem.ignore();
        getline(readitem, menu[i].name, '\t');
        readitem >> menu[i].price;
    }
    readitem.close();
    cout << "Hello employee " << emp.name << ", you are logged in."<<endl;
    cout << "############ Welcome to restaurant administrator page ############" << endl;
    cout << "1. Display food items" << endl;
    cout << "2. Display users" << endl;
    cout << "3. Add food item" << endl;
    cout << "4. Edit food item" << endl;
    cout << "5. Delete food item" << endl;
    cout << "6. EXIT" << endl;
    do {
        cout << "Enter your choice: ";
        cin >> choice;
    } while (choice <1 || choice>6 );
    cin.ignore(1, '\n');
    if (choice == 1)
    {
        DisplayFoodItems(menu);
    }
    if (choice == 2) {
        DisplayUsers(menu);
    }
    if (choice == 3) {
        addfood();
    }
    if (choice == 4) {
        EditFoodItem(menu);
    }
    if (choice == 5) {
        DeleteItem(menu);
    }
    if (choice == 6)
    {
        PayRoll();
    }
}
void Login(User* data) {
    User login;
    string pass;
    cout << "~~~~~~~~~ Welcome to Log In page ~~~~~~~~~" << endl;
    do {
        cout << "Enter your email: ";
        cin >> login.email;
    } while (checkemail(data, login.email)==0);
    int num = getlinesnumber("users.txt");
    for (int i = 0; i < num; i++)
    {
        if (data[i].email == login.email)
        {
            login = data[i];
            break;
        }
    }
    do {
        cout << "enter your password: ";
        cin >> pass;
    } while (pass != login.password);
    if (login.employee == 0)
    {
        Menu(login);
    }
    else if (login.employee == 1)
    {
        Admin(login);
    }
}
void Register(User* data) {
    User signup;
    cout << "~~~~~~~~~~~~ Welcome to Sign Up page ~~~~~~~~~~~~" << endl;
    cout << "Enter your name: ";
    getline(cin, signup.name);
        cout << "Enter your birthday MM-DD-YYYY: ";
        cin >> signup.birthday;
        do {
            cout << "Enter your email: ";
            cin >> signup.email;
        } while (unique(data,signup.email,0)==0);
        do {
            cout << "Enter a new password: ";
            cin >> signup.password;
        } while (unique(data, signup.password, 1)==0);
        cout << "Enter your phone number: ";
        cin >> signup.phone_number;
        cout << "Are you a user or an employee ? (0 or 1) :";
        cin >> signup.employee;
        cout << endl;
        ofstream print("users.txt",ios::app);
        print << signup.name << '\t';
        print << signup.birthday << '\t';
        print << signup.email << '\t';
        print << signup.password << '\t';
        print << signup.phone_number << '\t';
        print << signup.employee << '\n';
        print.close();

}
int main() {
    int choice;
    int usersnum=getlinesnumber("users.txt");
    User* database = new User[usersnum];
    ifstream read("users.txt");
    for (int i = 0; i < usersnum; i++)
    {
        getline(read, database[i].name, '\t');
        getline(read, database[i].birthday, '\t');
        getline(read, database[i].email, '\t');
        getline(read, database[i].password, '\t');
        getline(read, database[i].phone_number, '\t');
        read >> database[i].employee;
        read.ignore(1, '\n');
    }
    read.close();
   /* for (int i = 0; i < usersnum; i++)
    {
        cout<<  database[i].name<< '\t';
        cout << database[i].birthday << '\t';
        cout << database[i].email << '\t';
        cout << database[i].password << '\t';
        cout << database[i].phone_number << '\t';
        cout << database[i].employee << endl;
    }
    */
    cout << "Welcome to Georges & Roudy Restaurant 2023" << endl;
    cout << "******************************************" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    
    do {
        cout << "Enter your choice: (1 , 2 or 3) :";
        cin >> choice;
    } while (choice != 1 && choice != 2 && choice != 3);
    cin.ignore(1, '\n');
    if (choice == 1) {
        Register(database);
    }
    if (choice == 2) {
        Login(database);
        delete[] database;
    }
    return 0;
 }