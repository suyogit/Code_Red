#include <iostream>
#include<winsock.h>
#include<windows.h>
#include<sstream>
#include<ctime>
#include<string>
#include<mysql.h>
#include<cstring>
#include<conio.h>
#include<cstring>
#include<map>
using namespace std;
int users =0;
int count_attempt=0;
int curr_user=0;
int user_no=0;
string loggedin_user="";
int loggedin_userId=0;
void showtime()
{
	time_t now = time(0);
	char *dt = ctime(&now);
	cout<<dt;
	cout<<endl<<endl;
}
class user
{
private:
string username;
string password;
string cycleLen;
string periodLen;
public:
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
string cal(int len){
    Calender calender;
            calender.setTodaysDate();
            calender.setCycleLen(len);
            while (true)
            {
                cout << "Press arrows to move date and other keys to set the start date of period!" << endl;

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
            string str_date = to_string(calender.ret_year()) +"/"+to_string(calender.ret_mon())+"/"+to_string(calender.ret_day());
            getch();
            return str_date;
}
void adduser()
{
	MYSQL *conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn ,"192.168.137.1" ,"root", "root", "codered" ,3307,NULL,0);
	if(conn)
        cout<<"connected"<<endl;
    else cout<<"not connected"<<endl;

	cout<<"Username:";
	cin>>username;
	cout<<"Password:";
	cin>>password;
    cout<<"Period Length (Default is 28 days):";
    cin>>periodLen;
    cout<<"Cycle Length:";
    cin>>cycleLen;
    int len = stoi(cycleLen);
    string str_date = cal(len);
	int qstate =0;
	stringstream ss;
	// ss<<"INSERT INTO user(username,password,periodLen,cycleLen,start_date) VALUES('"<<username<<"','"<<password<<"')";
	ss<<"INSERT INTO users(username,password,periodLen,cycleLen,start_date) VALUES('"<<username<<"','"<<password<<"','"<<periodLen<<"','"<<cycleLen<<"','"<<str_date<<"')";
	string query =  ss.str();
        const char* q= query.c_str();
        qstate = mysql_query(conn,q);
        if(qstate==0)
            cout<<"Record Inserted Succesfully ... "<<endl;
        else cout<<"Failed"<<endl;

	users++;
}
void no_users()
{
	cout<<"The users are:  "<<endl;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
    conn = mysql_real_connect(conn ,"localhost" ,"admin", "admin", "codered" ,0,NULL,0);
	if(conn)
    {
        int qstate = mysql_query(conn,"SELECT username FROM users");
    //    bool flag=false;
        if(!qstate)
        {
            res = mysql_store_result(conn);
            int i=1;
            while(row = mysql_fetch_row(res))
                {
                    cout<<i<<"."<<row[0]<<endl;
                    i++;
                }
        }
    }
}
void login()
{
	if(curr_user==1)
	{
	cout<<"Already logged in";
	return;
	}
	if(count_attempt==2)
	{
		cout<<endl<<endl;
		cout<<"No more attempts";
		exit(0);
	}
	cout<<"Enter Credentials for Login (ID Password)"<<endl;
	string user_name;
	string pass_word;

	cout<<"Username:";
	cin>>user_name;
	cout<<"Password:";
	cin>>pass_word;
	cin.ignore();
	system("cls");

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
    conn = mysql_real_connect(conn ,"localhost" ,"admin", "admin", "codered" ,0,NULL,0);
	if(conn)
    {
        int qstate = mysql_query(conn,"SELECT id,username,password FROM users");
        bool flag=false;
        if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                {
                if(row[1]==user_name && row[2]==pass_word)
                {
                        cout<<"Login Succesful"<<endl;
                        loggedin_userId = int(row[0]);
                        loggedin_user = row[1];
                        curr_user=1;
                        flag=true;
                        break;
                }
                }
                if(!flag)
                {
                    cout<<"Try again"<<endl;
                    count_attempt++;
                    cin.ignore();
                    system("cls");
                    login();
                }


        }
        else
        {
            cout<<"No Accounts Registered";
        }

    }
}

	void logout()
	{
		curr_user=0;
	}
};
