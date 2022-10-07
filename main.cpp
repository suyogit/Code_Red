#include "./DEFINES.hpp"
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

    return 0;
}