#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 


// cyber cafe managment system admin contolled
// admin has 10 pc setup
//at a time he can support 10 login
//admin can create login of user and logout according to time and asks for payment //postpaid
//additional feature adding after end : admin can add special customers who might have account //prepaid
// uses signal if pc shuts down abbruptdly 
//refer quiz 2 and lab 3 for clock
//functions
//1:newlogin(username,pc_no)
//2:logout(username,pc_no)
//3:loggedin_user(filename)
//4:set_perhour_cost(cost)
//5:total_income(date)
//6:logout_all()
//7:intial_screen()


struct pc
{
    int pc_no;
    int status;
};
struct Date
{
    int day;
    int month;
    int year;
};
struct user{
    char* username;
    struct pc pcdet;
    time_t login;
    time_t logout;
    struct Date date; 
    double min;
};
void intial screen()
{
    cout << "1: NewLogin\n";
    cout << "2: Logout\n";
    cout << "3: Logged IN Users\n";
    cout << "4: Set Per Hour Cost\n";
    cout << "5: Logout All The Users\n";
    cout << "6: calculate Total Income\n";
    cout << "7: Get pc Status";
    cout << "8: Switch on/of PC";
}
void main()
{

}
