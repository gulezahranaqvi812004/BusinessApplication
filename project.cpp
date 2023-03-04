#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctime>
using namespace std;

// global data for user
string user_name[100];
string passcode[100];
string roles[100];
int user_salary[100];
int user_count = 0;

//____________________ function definations____________________________

// interface  functions
void interface_of_application();
void header();
void press();
void print_time();

// file handling functions
void store_to_file();
void loadDataFromFile();
void delete_from_file(string name, string password, string role);
void store_data_of_items_to_file();
void load_data_of_items();
string getField(string record, int field);
void readData();
string get_field_for_items(string line, int field);

// some other functions and variables that support concern functionalities
void view_user();
int login_page();

// count that stores the index of the user who signs up
int store = 0;

// validation functions
int validation(int number);
bool name_check(string name);
bool role_check(string role);
bool password_validation(string password);

// functions for sign in
void login_in();
bool sign_in(string userName, string password, string role);
string return_role(string name, string password);

// functions for  sign up
bool is_valid_user_name(string userName, string password, string role);
void add_user(string userName, string password, string role, int salary);
void sign_up();

// functions for admin
int admin_menu();
void admin_functionality();
void returned_function_of_admin();

// admin choices
void admin_choice1();
void admin_choice_2();
void admin_choice_3();
void admin_choice_4();
void admin_choice_5();
void admin_choice_6();
void admin_choice_7();
void admin_choice_8();
void admin_choice_9();
void admin_choice_10();
void admin_choice_11();

// supporting fuctions
void delete_user_from_array(string name, string password, string role);
void delete_device_from_array(string device_name);
void add_salary(string name, string password, string role, int salary);
void update_stock(string item_name, int updated_stock);
void update_customer_id(string name, string previousPassword, string newPassword);

// global data related to items
string item_collections[100];
int item_price[100];
int item_count = 0;
int item_quantity[100];

// functions related to items
void store_data_of_items_to_array(string device_name, int device_price, int quantity);
bool check_item_already_exist(string device_name);

// global data for customer
string wishList[100];
string feed_back[100];
// customer functionalities
void customer_functionality();
int customer_menu();
void go_back_to_customer_menu();

// customer choice
void customer_choice_1();
void customer_choice_2();
void customer_choice_3();
void customer_choice_4();
void customer_choice_5();
void add_to_wishlist();
void see_wish_list();
void give_feed_back();

// supporting function for customer
bool search_device(string device_name);
void purchase_a_device(string name);
int view_price(string name);
bool check_stock(string name);
void clear_item_from_stock(string name);
void update_password(string userName, string role, string newPassword);
void update_name(string userName, string role, string newName);
void initialization_of_wishList();
void initialization_of_feed_back();
// employee function
void employee_functionality();
int employee_menu();

// employee choices
void employee_choice_1();
void employee_choice_2();

// supporting function for employees
int search_salary(string name, string password, string role);
bool is_password_already_taken(string password);
void go_back_to_employee_menu();
main()
{
    loadDataFromFile();
    load_data_of_items();
    initialization_of_wishList();
    initialization_of_feed_back();
    interface_of_application();

    int choice = 3;
    while (choice != 0)
    {
        choice = login_page();
        if (choice == 1)
        {
            sign_up();
        }
        if (choice == 2)
        {
            login_in();
        }
        if (choice == 3)
        {
            view_user();
        }
    }
}
void interface_of_application()
{
    system("cls");
    print_time();
    header();
}
// function that prints time
void print_time()
{
    time_t currentTime = time(0);

    // Convert the current time to a string format
    char *timeString = ctime(&currentTime);

    // Print the current time to the console
    cout << "The current time is: " << timeString << endl;
}
// header function
void header()
{
    system("color 5");
    
    cout << "  *****************************************                 " << endl;
    cout << "  *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*                 " << endl;
    cout << "  *^                                     ^*                 " << endl;
    cout << "  *^         MOBILE SHOP                 ^*                 " << endl;
    cout << "  *^       Management System             ^*                 " << endl;
    cout << "  *^                                     ^*                 " << endl;
    cout << "  *^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*                 " << endl;
    cout << "  *****************************************                 " << endl;
}
// getch function
void press()
{
    cout << "Press any key to continue ";
    getch();
}
//  function that prints first menu(sign in / sign up)
int login_page()
{
    int login_choice;
    cout << "Press 1 for sign up" << endl;
    cout << "Press 2 for sign in" << endl;
    cout << "Press 3 to view all users " << endl;
    cout << "Press 0 to exit" << endl;
    cout << "Enter your choice: ";
    cin >> login_choice;
    login_choice = validation(login_choice);
    return login_choice;
}
// validation function for integer
int validation(int number)
{
    while (cin.fail() || number<0)
    {
        cin.clear();
        cin.ignore(100, '\n');
        cout
            << "Invalid input !!" << endl
            << "Enter an integer: ";
        cin >> number;
    }
    return number;
}
// password validation
bool password_validation(string password)
{
    bool flag = false;
    if (password.length() == 8)
    {
        flag = true;
    }
    return flag;
}
// sign up function
void sign_up()
{
    interface_of_application();
    string name;
    string password;
    string role;
    int salary = 0;
    bool check;
    bool check1 = false;
    bool check2 = false;
    bool check3 = false;
    while (check1 == false)
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        check1 = name_check(name);
    }
    while (check3 == false)
    {
        cout << "Enter your password(must contains 8 letterrs): ";
        // cin.ignore();
        getline(cin, password);
        check3 = password_validation(password);
    }
    while (check2 == false)
    {
        cout << "Enter your role(customer/admin/employee): ";
        // cin.ignore();
        getline(cin, role);
        check2 = role_check(role);
    }
    check = is_valid_user_name(name, password, role);
    if (check == false)
    {
        cout << "User alredy exist" << endl;
    }
    else
    {
        add_user(name, password, role, salary);
        store_to_file();
        cout << "Successfully sign up" << endl;
    }
}
// validation function for name
bool name_check(string name)
{
    bool flag = false;
    int i = 0;
    while (i < name.length())
    {
        if (name.length() <= 2)
        {
            cout << "Your Name Should  Be Atleast 3 Characters Long" << endl;
            getch();
            break;
        }
        if ((name[i] > 63 && name[i] < 91) || (name[i] > 96 && name[i] < 123) || name[i] == ' ')
        {
            i++;

            flag = true;
        }
        else
        {
            flag = false;
            break;
        }
    }

    return flag;
}
// validation function for role
bool role_check(string role)
{
    bool value = false;
    if (role == "customer" || role == "admin" || role == "employee")
    {
        value = true;
    }
    return value;
}
// function that check that either name or password is already taken or not
bool is_valid_user_name(string userName, string password, string role)
{
    bool flag = true;
    for (int index = 0; index < user_count; index++)
    {
        if (user_name[index] == userName && (passcode[index] == password && roles[index] == role))
        {
            flag = false;
            break;
        }
    }
    return flag;
}
// function that store user details in arrays
void add_user(string userName, string password, string role, int salary)
{
    user_name[user_count] = userName;
    passcode[user_count] = password;
    roles[user_count] = role;
    user_salary[user_count] = salary;
    user_count++;
}
// function that store user details in file
void store_to_file()
{

    fstream file;
    file.open("usersDetails.txt", ios::out);
    for (int x = 0; x < user_count; x++)
    {
        file << user_name[x] << ",";
        file << passcode[x] << ",";
        file << roles[x] << ",";
        file << user_salary[x] << ",";
        file << wishList[x] << ",";
        file << feed_back[x] << endl;
    }
    file.close();
}
// function that load data from file to array
void loadDataFromFile()
{
    string record;
    fstream file;
    file.open("usersDetails.txt", ios::in);
    while (getline(file, record))
    {
        if (record != "")
        {
            user_name[user_count] = getField(record, 1);
            passcode[user_count] = getField(record, 2);
            roles[user_count] = getField(record, 3);
            user_salary[user_count] = stoi(getField(record, 4));
            wishList[user_count] = (getField(record, 5));
            feed_back[user_count] = (getField(record, 6));
            user_count++;
        }
    }
    file.close();
}
// function to separate data
string getField(string record, int field)
{

    int commmaCount = 1;
    string item;
    for (int x = 0; x < record.length(); x++)
    {
        if (record[x] == ',')
        {
            commmaCount++;
        }
        else if (commmaCount == field)
        {
            item = item + record[x];
        }
    }
    return item;
}
// login function
void login_in()
{
    interface_of_application();
    string name;
    string password;
    string role;
    int salary = 0;
    bool check;
    bool check1 = false;
    bool check2 = false;
    while (check1 == false)
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        check1 = name_check(name);
    }
    while (check2 == false)
    {
        cout << "Enter your password: ";
        //  cin.ignore();
        getline(cin, password);
        check2 = password_validation(password);
    }
    role = return_role(name, password);
    check = sign_in(name, password, role);
    if (check == true)
    {
        cout << "Welcome" << endl
             << endl;

        if (role == "admin")
        {
            admin_functionality();
        }
        else if (role == "customer")
        {
            customer_functionality();
        }
        else if (role == "employee")
        {
            employee_functionality();
        }
    }
    else
    {
        cout << "Go and first sign up" << endl
             << endl;
    }
}
// function that check either user has signed up or not
bool sign_in(string userName, string password, string role)
{
    bool flag = false;
    for (int index = 0; index < user_count; index++)
    {
        if (user_name[index] == userName && (passcode[index] == password && roles[index] == role))
        {
            store = index;
            flag = true;
            break;
        }
    }
    return flag;
}
// funtion that search role of the user who is signing in
string return_role(string name, string password)
{
    string value_to_be_returned;
    for (int index = 0; index < user_count; index++)
    {
        if (user_name[index] == name && passcode[index] == password)
        {
            value_to_be_returned = roles[index];
            break;
        }
    }
    return value_to_be_returned;
}
// function that load data of items from file to array
void load_data_of_items()
{
    string line;
    fstream file;
    string record;
    file.open("items.txt", ios::in);
    while (getline(file, record))
    {
        if (record != "")
        {
            item_collections[item_count] = get_field_for_items(record, 1);
            item_price[item_count] = stoi(get_field_for_items(record, 2));
            item_quantity[item_count] = stoi(get_field_for_items(record, 3));
            item_count++;
        }
    }
    file.close();
}
// funtion that store data of items to file
void store_data_of_items_to_file()
{
    fstream file;
    file.open("items.txt", ios::out);
    for (int x = 0; x < item_count; x++)
    {
        file << item_collections[x] << ",";
        file << item_price[x] << ",";
        file << item_quantity[x] << endl;
    }
    file.close();
}
// function that separate data of items according to comma
string get_field_for_items(string line, int field)
{
    int commmaCount = 1;
    string item;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ',')
        {
            commmaCount++;
        }
        else if (commmaCount == field)
        {
            item = item + line[i];
        }
    }
    return item;
}
// funtion that store items to array during execution
void store_data_of_items_to_array(string device_name, int device_price, int quantity)
{
    item_collections[item_count] = device_name;
    item_price[item_count] = device_price;
    item_quantity[item_count] = (quantity);
    item_count++;
}
// function to view all users
void view_user()
{
    interface_of_application();
    cout << "Names "
         << "\t\t"
         << "Password "
         << "\t\t"
         << "Role" << endl;
    for (int index = 0; index < user_count; index++)
    {
        cout << user_name[index] << "\t\t" << passcode[index] << "\t\t" << roles[index] << "\t\t" << user_salary[index] << endl;
    }
    cout << endl
         << endl;
}

//___________________admin functions_______________
// functions that display admin menu
int admin_menu()
{
    int admin_choice;
    interface_of_application();
    cout << "Press 1 to add an employee" << endl;
    cout << "Press 2 to view yours employee" << endl;
    cout << "Press 3 to delete an employee" << endl;
    cout << "Press 4 to add a new product " << endl;
    cout << "Press 5 to view your products" << endl;
    cout << "Press 6 to delete product " << endl;
    cout << "Press 7 to update salary of any employee " << endl;
    cout << "Press 8 to view customers" << endl;
    cout << "Press 9 to update stock" << endl;
    cout << "Press 10 to update credentials of any employee " << endl;
    cout << "Press 11 to view feed back of customers " << endl;
    cout << "Press 0 to exit " << endl;
    cout << "Enter your choice: ";
    cin >> admin_choice;
    admin_choice = validation(admin_choice);
    return admin_choice;
}
// funtion that bring user to admin menu
void returned_function_of_admin()
{
    press();
    admin_functionality();
}
// function that go to the concern function according to admin choice
void admin_functionality()
{

    int returned_choice = -1;
    returned_choice = admin_menu();
    // while (returned_choice != 0)
    {
        system("cls");
        header();

        if (returned_choice == 1)
        {
            admin_choice1();
        }
        else if (returned_choice == 2)
        {
            admin_choice_2();
        }
        else if (returned_choice == 3)
        {
            admin_choice_3();
        }
        else if (returned_choice == 4)
        {
            admin_choice_4();
        }
        else if (returned_choice == 5)
        {
            admin_choice_5();
        }
        else if (returned_choice == 6)
        {
            admin_choice_6();
        }
        else if (returned_choice == 7)
        {
            admin_choice_7();
        }
        else if (returned_choice == 8)
        {
            admin_choice_8();
        }
        else if (returned_choice == 9)
        {
            admin_choice_9();
        }
        else if (returned_choice == 10)
        {
            admin_choice_10();
        }
        else if (returned_choice == 11)
        {
            admin_choice_11();
        }
        else if (returned_choice == 0)
        {
            login_page();
        }
    }
}
// admin choice number 1
void admin_choice1()
{
    cout << "________________Menu 1_________________" << endl;
    bool check;
    string name;
    string password;
    int salary;
    string role;
    bool check1 = false;
    bool check2 = false;
    while (check1 == false)
    {
        cout << "Enter name of employee: ";
        cin.ignore();
        getline(cin, name);
        check1 = name_check(name);
    }
    while (check2 == false)
    {
        cout << "Enter password of employee (must contains 8 letterrs): ";
        // cin.ignore();
        getline(cin, password);
        check2 = password_validation(password);
    }
    cout << "Enter the salary of employee: ";
    cin >> salary;
    salary = validation(salary);
    role = "employee";
    check = is_valid_user_name(name, password, role);
    if (check == true)
    {

        add_user(name, password, role, salary);
        store_to_file();
        cout << "Your desired entry has successfully entered." << endl;
    }
    else
    {
        cout << "Can't enter your  record because it is repititive!" << endl;
    }

    returned_function_of_admin();
}
// admin choice number 2
void admin_choice_2()
{
    cout << "________________Menu 2_________________" << endl;
    cout << "Name"
         << "\t\t"
         << "Password"
         << "\t\t"
         << "Salary " << endl;
    for (int index = 0; index < user_count; index++)
    {
        if (roles[index] == "employee")
        {
            cout << user_name[index] << "\t\t" << passcode[index] << "\t\t" << user_salary[index] << endl;
        }
    }
    returned_function_of_admin();
}
// admin choice number 3
void admin_choice_3()
{
    cout << "________________Menu 3_________________" << endl;
    string name;
    string del_password;
    string del_role;
    bool check;
    bool check1 = false;
    bool check2 = false;
    while (check1 == false)
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        check1 = name_check(name);
    }
    cout << "enter password: ";
    cin >> del_password;
    while (check2 == false)
    {
        cout << "Enter your role: ";
        cin >> del_role;
        check2 = role_check(del_role);
    }
    check = is_valid_user_name(name, del_password, del_role);
    if (check == false)
    {
        delete_user_from_array(name, del_password, del_role);
        store_to_file();
        cout << "Succesfully deleted" << endl;
    }
    else
    {
        cout << "User does no exist" << endl;
    }
    returned_function_of_admin();
}
// funtion that delete user from array
void delete_user_from_array(string name, string password, string role)
{

    for (int index = 0; index < user_count; index++)
    {
        if ((user_name[index] == name && passcode[index] == password) && roles[index] == role)
        {
            passcode[index] = passcode[index + 1];
            passcode[index + 1] = "";
            user_name[index] = user_name[index + 1];
            user_name[index + 1] = "";
            roles[index] = roles[index + 1];
            roles[index + 1] = "";
            user_salary[index] = user_salary[index + 1];
            user_salary[index] = 0;
            wishList[index] = wishList[index + 1];
            wishList[index] = "";
            user_count--;
        }
    }
}
// admin choice number 4
void admin_choice_4()
{

    cout << "________________Menu 4_________________" << endl;
    bool check;
    string device_name;
    int price;
    int quantity;
    cout << "Enter name of device: ";
    cin.ignore();
    getline(cin, device_name);
    cout << "Enter price of your device: ";
    cin >> price;
    price = validation(price);
    cout << "Enter how many pieces you want to enter: ";
    cin >> quantity;
    quantity = validation(quantity);
    check = check_item_already_exist(device_name);
    if (check == true)
    {
        cout << "Your entered item is already present. " << endl;
    }
    else
    {

        store_data_of_items_to_array(device_name, price, quantity);
        store_data_of_items_to_file();

        cout << "Successfully added " << endl;
    }

    returned_function_of_admin();
}
// function that check either item already exist or not to avoid repitition of items
bool check_item_already_exist(string device_name)
{
    bool find = false;
    for (int index = 0; index < item_count; index++)
    {
        if (item_collections[index] == device_name)
        {
            find = true;
        }
    }
    return find;
}
// admin choice number 5
void admin_choice_5()
{
    cout << "________________Menu 5_________________" << endl;
    cout << "Product Name  "
         << "\t"
         << "Product price"
         << "\t"
         << "No. of pieces " << endl;
    for (int i = 0; i < item_count; i++)
    {
        cout << item_collections[i] << "\t\t"
             << item_price[i] << "\t\t"
             << item_quantity[i] << endl;
    }
    returned_function_of_admin();
}
// admin choice number 6
void admin_choice_6()
{
    cout << "________________Menu 6_________________" << endl;
    string name;
    bool check;
    cout << "Enter the name of device you want to delete: ";
    cin.ignore();
    getline(cin, name);
    check = check_item_already_exist(name);
    if (check == true)
    {
        delete_device_from_array(name);
        store_data_of_items_to_file();
        cout << "Successfully deleted" << endl;
    }
    else
    {
        cout << "Device does not exist" << endl;
    }
    returned_function_of_admin();
}
// funtion that delete device from array
void delete_device_from_array(string device_name)
{
    for (int index = 0; index < item_count; index++)
    {
        if (item_collections[index] == device_name)
        {
            item_collections[index] = item_collections[index + 1];
            item_collections[index + 1] <= "0";
            item_price[index] = item_price[index + 1];
            item_price[index + 1] = 0;
            item_quantity[index] = 0;
            item_count--;
        }
    }
}
// admin choice number 7
void admin_choice_7()
{
    int salary;
    string name;
    string password;
    string role;
    bool check;
    bool check1 = false;
    bool check2 = false;
    while (check1 == false)
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        check1 = name_check(name);
    }
    cout << "Enter password of employee: ";
    cin >> password;
    while (check2 == false)
    {
        cout << "Enter your role: ";
        //  cin.ignore();
        getline(cin, role);
        check2 = role_check(role);
    }
    cout << "Enter the updated salary: ";
    cin >> salary;
    salary = validation(salary);
    check = is_valid_user_name(name, password, role);
    if (check == false)
    {
        add_salary(name, password, role, salary);
        cout << "Successfully updated " << endl;
    }
    else
    {
        cout << "Can't find your entered employee!" << endl;
    }
    returned_function_of_admin();
}
// function that update salary
void add_salary(string name, string password, string role, int salary)
{
    for (int index = 0; index < user_count; index++)
    {
        if (user_name[index] == name && passcode[index] == password && roles[index] == role)
        {
            user_salary[index] = salary;
            store_to_file();
        }
    }
}
// admin choice number 8
void admin_choice_8()
{
    cout << "Customers are: " << endl;
    for (int index = 0; index < user_count; index++)
    {
        if (roles[index] == "customer")
        {
            cout << user_name[index] << endl;
        }
    }

    returned_function_of_admin();
}
// admin choice number 9
void admin_choice_9()
{
    string item_name;
    int updated_stock;
    cout << "Enter the name of the device of which you wanted to add stock: ";
    cin.ignore();
    getline(cin, item_name);
    cout << "Enter the updated stock: ";
    cin >> updated_stock;
    update_stock(item_name, updated_stock);
    store_data_of_items_to_file();
    returned_function_of_admin();
}
// function that update the stock
void update_stock(string item_name, int updated_stock)
{
    for (int index = 0; index < item_count; index++)
    {
        if (item_collections[index] == item_name)
        {
            item_quantity[index] = item_quantity[index] + updated_stock;
        }
    }
}
// admin choice number 10
void admin_choice_10()
{
    string name;
    string previousPassword;
    string newPassword;
    bool check1 = false;
    bool already_taken;
    while (check1 == false)
    {
        cout << "Enter name of the employee of which you wanted to change passowrd: ";
        cin.ignore();
        getline(cin, name);
        check1 = name_check(name);
    }
    cout << "Enter previous password of that employee: ";
    // cin.ignore();
    getline(cin, previousPassword);
    cout << "Enter new password of that employee: ";
    //  cin.ignore();
    getline(cin, newPassword);
    already_taken = is_password_already_taken(newPassword);
    if (already_taken == false)
    {
        update_customer_id(name, previousPassword, newPassword);
        store_to_file();
    }
    else
    {
        cout << "Can't update because this password is already taken " << endl;
    }
    returned_function_of_admin();
}
// function that update customer credentials
void update_customer_id(string name, string previousPassword, string newPassword)
{
    for (int index = 0; index < user_count; index++)
    {
        if (user_name[index] == name && passcode[index] == previousPassword)
        {
            passcode[index] = newPassword;
        }
    }
}
// function to view_feed_back
void admin_choice_11()
{
    for (int index = 0; index < user_count; index++)
    {
        if (feed_back[index] != " " || feed_back[index] != "e")
        {
            cout << user_name[index] << "\t\t\t" << feed_back[index] << endl;
        }
    }
    returned_function_of_admin();
}

//___________________employee functions_______________
// function that display employee menu
int employee_menu()
{
    int choice = 0;
    cout
        << "Press 1 to view your ID" << endl;
    cout << "Press 2 to change password" << endl;
    cout << "Press 3 to exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    choice = validation(choice);
    return choice;
}
// function that call function according to choice of employee
void employee_functionality()
{
    interface_of_application();
    int choice = -1;
    // while (choice != 3)
    {
        choice = employee_menu();
        if (choice == 1)
        {
            employee_choice_1();
        }
        else if (choice == 2)
        {
            employee_choice_2();
        }
        else if (choice == 3)
        {
            login_page();
        }
    }
}
// function that bring user back to menu of  employee
void go_back_to_employee_menu()
{
    interface_of_application();
    employee_functionality();
    press();
}
// function of employee choice number 1
void employee_choice_1()
{
    string name;
    string password;
    int salary;
    bool check1 = false;
    bool check2 = false;
    while (check1 == false)
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        check1 = name_check(name);
    }
    while (check2 == false)
    {
        cout << "Enter your password: ";
        // cin.ignore();
        getline(cin, password);
        check2 = password_validation(password);
    }
    string role = "employee";
    salary = search_salary(name, password, role);
    
    cout << "Your salary is: " << salary << endl;
    go_back_to_employee_menu();
}
// function that search for salary of employee
int search_salary(string name, string password, string role)
{
    int salary;
    for (int index = 0; index < user_count; index++)
    {
        if (user_name[index] == name && passcode[index] == password && roles[index] == role)
        {
            user_salary[index] = salary;
        }
    }
    return salary;
}
// function of employee choice number 2
void employee_choice_2()
{
    string name;
    string previousPassword;
    string newPassword;
    string role = "employee";
    bool is_present_check;
    bool check;
    bool check1 = false;
    bool check2 = false;
    while (check1 == false)
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        check1 = name_check(name);
    }
    cout << "Enter your previous password: ";
    cin >> previousPassword;
    is_present_check = is_valid_user_name(name, previousPassword, role);
    if (is_present_check == false)
    {
        while (check2 == false)
        {
            cout << "Enter your new password: ";
            cin >> newPassword;
            check2 = password_validation(newPassword);
        }
        check = is_password_already_taken(newPassword);
        if (check == false)
        {
            update_customer_id(name, previousPassword, newPassword);
            store_to_file();
            cout << "Successfully change your password!" << endl;
        }
        else
        {
            cout << "This password has already taken! " << endl;
        }
    }
    else
    {
        cout << "Invalid credentials! " << endl;
    }
    go_back_to_employee_menu();
}
// function that check either password is already taken or not
bool is_password_already_taken(string password)
{
    bool is_taken = false;
    for (int index = 0; index < user_count; index++)
    {
        if (passcode[index] == password)
        {
            is_taken = true;
        }
    }
    return is_taken;
}

//___________________customer functions_______________
// function that initialize entire string to empty to avoid error
void initialization_of_wishList()
{
    for (int x = 0; x < 100; x++)
    {
        wishList[x] = "No wish";
    }
}
// function that brings user back to customer menu
void go_back_to_customer_menu()
{
    press();
    customer_functionality();
}
// function that prints customer menu
int customer_menu()
{
    int choice;
    cout << "Welcome!" << endl;
    cout << "Press 1 to view mneu " << endl
         << "Press 2 to check the availability of your desired device" << endl
         << "Press 3 to purchase phone" << endl
         << "Press 4 to change your pin code" << endl
         << "Press 5 to change your name" << endl
         << "Press 6 to add anything to your wish list" << endl
         << "Press 7 to see your wish list" << endl
         << "Press 8 to give feedback " << endl
         << "Press 0 to exit" << endl
         << "Enter your choice: ";
    cin >> choice;
    choice = validation(choice);
    return choice;
}
// function that calls the concern functions according to choice
void customer_functionality()
{
    int customer_choice = -1;
    //  while (customer_choice != 0)
    {
        system("cls");
        header();
        customer_choice = customer_menu();
        if (customer_choice == 1)
        {
            customer_choice_1();
        }
        else if (customer_choice == 2)
        {

            customer_choice_2();
        }
        else if (customer_choice == 3)
        {
            customer_choice_3();
        }
        else if (customer_choice == 4)
        {
            customer_choice_4();
        }
        else if (customer_choice == 5)
        {
            customer_choice_5();
        }
        else if (customer_choice == 6)
        {
            add_to_wishlist();
        }
        else if (customer_choice == 7)
        {
            see_wish_list();
        }
        else if (customer_choice == 8)
        {
            give_feed_back();
        }
        else if (customer_choice == 0)
        {
            login_page();
        }
    }
}
// function for customer choice number 1
void customer_choice_1()
{
    for (int index = 0; index < item_count; index++)
    {
        if (item_collections[index] != "0")
        {
            cout << item_collections[index] << endl;
        }
    }
    go_back_to_customer_menu();
}
// function for customer choice number 2
void customer_choice_2()
{
    string name;
    bool is_found;
    cout << "Enter the name of the device you wanted to purchase: ";
    cin.ignore();
    getline(cin, name);
    is_found = search_device(name);
    if (is_found == true)
    {
        cout << "Your desired device is available! " << endl;
    }
    else
    {
        cout << "Sorry for inconvinience your desired device is not available! " << endl;
    }
    go_back_to_customer_menu();
}
// function that check either device is present or not
bool search_device(string device_name)
{
    bool flag = false;
    for (int index = 0; index < item_count; index++)
    {
        if (item_collections[index] == device_name)
        {
            flag = true;
        }
    }
    return flag;
}
// function for customer choice number 3
void customer_choice_3()
{
    char conform;
    string name;
    int price;
    bool is_found;
    bool is_available;
    cout << "Enter the name of the device you wanted to purchase: ";
    cin.ignore();
    getline(cin, name);
    is_found = search_device(name);
    is_available = check_stock(name);
    if (is_found == true)
    {
        if (is_available == true)
        {
            // cout << "Your desired device is available! " << endl;
            price = view_price(name);
            cout << "Price of your desired device is: " << price << endl;
            cout << "Press y to confirm your choice and 'n' to cancel it: ";
            cin >> conform;
            if (conform == 'y')
            {
                purchase_a_device(name);
                store_data_of_items_to_file();
                cout << "Thank you for purchasing!" << endl;
            }
        }
        else
        {
            clear_item_from_stock(name);
            store_data_of_items_to_file();
            cout << "Out of stock" << endl;
        }
        go_back_to_customer_menu();
    }
}
// funtion that display price of device
int view_price(string name)
{
    int price;
    for (int index = 0; index < item_count; index++)
    {
        if (item_collections[index] == name)
        {
            price = item_price[index];
        }
    }
    return price;
}
// function that check either device is in the stock or not
bool check_stock(string name)
{
    bool is_avialable = true;
    for (int index = 0; index < item_count; index++)
    {
        if (item_collections[index] == name && item_quantity[index] == 0)
            is_avialable = false;
    }
    return is_avialable;
}
// function that decrease stock if device is purchased by user
void purchase_a_device(string name)
{
    for (int index = 0; index < item_count; index++)
    {

        if (item_collections[index] == name && item_quantity[index] != 0)
        {
            item_quantity[index] = item_quantity[index] - 1;
        }
    }
}
// function that clear item when it quantity becomes zero
void clear_item_from_stock(string name)
{
    for (int index = 0; index < item_count; index++)
    {
        if (item_collections[index] == name && item_quantity[index] == 0)
        {

            item_collections[index] = item_collections[index + 1];
            item_collections[index + 1] = "0";
            item_price[index] = item_price[index + 1];
            item_price[index + 1] = 0;
            item_quantity[index] = item_quantity[index + 1];
            item_quantity[index + 1] = 0;
            item_count--;
            store_data_of_items_to_file();
        }
    }
}
// function for customer choice number 4
void customer_choice_4()
{
    string name;
    string password;
    string newPassword;
    bool found;
    string role = "customer";
    bool check1 = false;
    bool check2 = false;
    while (check1 == false)
    {
        cout << "Enter your name: ";
        cin >> name;
        check1 = name_check(name);
    }
    cout << "Enter your previous password: ";
    cin >> password;
    found = is_valid_user_name(name, password, role);
    if (found == true)
    {
        cout << "You have entered wrong credentials: ";
    }
    else
    {

        while (check2 == false)
        {
            cout << "Enter your new password: ";
            cin.ignore();
            getline(cin, password);
            cout << password << endl;
            check2 = password_validation(password);
        }
        update_password(name, role, newPassword);
        store_to_file();
    }
    go_back_to_customer_menu();
}
// function that update password
void update_password(string userName, string role, string newPassword)
{
    for (int index = 0; index < user_count; index++)
    {
        if (user_name[index] == userName && roles[index] == role)
        {
            passcode[index] = newPassword;
        }
    }
}
// function for customer choice number 5
void customer_choice_5()
{
    string name;
    string password;
    string newName;
    bool found;
    string role = "customer";
    bool check1 = false;
    bool check2 = false;
    while (check1 == false)
    {
        cout << "Enter your name: ";
        cin >> name;
        check1 = name_check(name);
    }
    while (check2 == false)
    {
        cout << "Enter your password: ";
        cin >> password;
        check2 = password_validation(password);
    }
    found = is_valid_user_name(name, password, role);
    if (found == true)
    {
        cout << "You have entered wrong credentials: ";
    }
    else
    {
        cout << "Enter your new name: ";
        cin.ignore();
        getline(cin, newName);
        update_name(name, role, newName);
        store_to_file();
    }
    go_back_to_customer_menu();
}
// function that update name
void update_name(string userName, string role, string newName)
{
    for (int index = 0; index < user_count; index++)
    {
        if (user_name[index] == userName && roles[index] == role)
        {
            user_name[index] = newName;
        }
    }
}
// function for customer choice number 6
void add_to_wishlist()
{
    string device_name;
    cout << "Enter a device which you wanted to add in your wish list: ";
    cin.ignore();
    getline(cin, device_name);
    wishList[store] = device_name;
    store_to_file();
    go_back_to_customer_menu();
}
// function for customer choice number 7
void see_wish_list()
{
    cout << user_name[store] << endl;
    cout << wishList[store] << endl;
    store_to_file();
    go_back_to_customer_menu();
}
// initialization of wish list
void initialization_of_feed_back()
{
    for (int x = 0; x < 100; x++)
    {
        feed_back[x] = "Not given now";
    }
}
// function for customer choice number 8
void give_feed_back()
{
    string sentence;
    cout << "Enter a device which you wanted to add in your wish list: ";
    cin.ignore();
    getline(cin, sentence);
    feed_back[store] = sentence;
    store_to_file();
    go_back_to_customer_menu();
}