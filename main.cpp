/*#include "./DEFINES.hpp"
#include "./Calender.cpp"

bool handleCalenderInput(int key, Calender &calender)
{
    switch (key)
    {
    case 72: // move up
        calender.subDay(7);
        return true;
    case 80: // move down
        calender.addDay(7);
        return true;
    case 75: // move left
        calender.subDay(1);
        return true;
    case 77: // move right
        calender.addDay(1);
        return true;
    }

    return false; // key is not handled
}

int main(void)
{

    Calender calender;
    calender.setTodaysDate();

    while (true)
    {
        cout << "Press arrows to move date and other keys to set current" << endl;
        bool arrowKeysPressed = getch() == 224;
        if (arrowKeysPressed)
        {
            int key = getch();

            if (!handleCalenderInput(key, calender)) // break from loop if anything other than arroow key pressed
                break;
        }
        else
            break;
    }
    // Have to put below date to the database;
    cout<<"Date: "<<calender.ret_year()<<"/"<<calender.ret_mon()<<"/"<<calender.ret_day()<<endl;
    cout<<"This is the end of the program."<<endl;
    getch();
    return 0;
}

*/

//////
#include "./DEFINES.hpp"
#include "./Calender.cpp"
#include "./login.cpp"
using namespace std;
bool handleCalenderInput(int key, Calender &calender)
{
    switch (key)
    {
    case 72: // move up
        calender.subDay(7);
        return true;
    case 80: // move down
        calender.addDay(7);
        return true;
    case 75: // move left
        calender.subDay(1);
        return true;
    case 77: // move right
        calender.addDay(1);
        return true;
    }

    return false; // key is not handled
}

int main(void)
{
    showtime();

    cout << " \t \t \t \t \t Period Tracking System " << endl
         << endl
         << endl
         << endl;
    user u1;
    int x;
    int choice = 0;

    do
    {
        cout << endl;
        cout << "Choose from the Following:" << endl;
        cout << "1. Login" << endl;
        cout << "2. Add user " << endl;
        cout << "3. Check no of users " << endl;
        cout << "4. Print users" << endl;
        cout << "5. Check current user details" << endl;
        cout << "6. Logout" << endl;
        cout << "0 to exit" << endl;
        cin >> x;
        string no2;
        switch (x)
        {
        case 1:
            u1.login();
            break;
        case 2:
            u1.adduser();
            u1.login();
            break;
        case 3:
            cout << users;
            break;
        case 4:
            u1.no_users();
            break;
        case 5:
        { // b1.print_user();
        if(loggedin_userId>0){
            cout << "Hi "
                 << " " << loggedin_user;
            Calender calender;
            calender.setTodaysDate();

            while (true)
            {
                cout << "Press arrows to move date" << endl;

                bool arrowKeysPressed = getch() == 224;
                if (arrowKeysPressed)
                {
                    int key = getch();

                    if (!handleCalenderInput(key, calender)) // break from loop if anything other than arroow key pressed
                        break;
                }
                else

                    break;
            }
            // Have to put below date to the database;
            cout << "Date: " << calender.ret_year() << "/" << calender.ret_mon() << "/" << calender.ret_day() << endl;
            cout << "This is the end of the program." << endl;
            getch();
        }
        else
            cout<<"Login to see User Credentials."<<endl;
        }
        break;
        case 6:
            u1.logout();
            break;
        case 0:
            choice = 1;
        }
    } while (choice == 0);

    return 0;
}
