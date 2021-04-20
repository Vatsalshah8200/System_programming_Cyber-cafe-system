#include "functiondec.h"
//   cout << "1: NewLogin\n";
//     cout << "2: Logout\n";
//     cout << "3: Logged IN Users\n";
//     cout << "4: Set Per Hour Cost\n";
//     cout << "5: Logout All The Users\n";
//     cout << "6: Get pc Status";
//     cout << "7: Calculate Total Income\n"
//     cout << "Enter your choice from 1 - 7";
;
int main()
{
    while(1)
    {
        int choice =  intial_screen();
        switch(choice)
        {
            case 1:
                printf("logging in new user check available pc and start the pc");
                login_newuser();
                break;
            case 2:
                printf("Logout user and shutdown pc");
                logout_user();
                break;
            case 3:
                printf("show all the logged in users details");
                Display_login_user();
                break;
            case 4:
                printf("Set per hour cost");
                break;
            case 5:
                printf("Logout all the user and shutdown all th pc");
                break;
            case 6:
                printf("Get Pc status");
                break;
            // case 7:
            //     printf("switch pc ON/OFF");
            //     break;
            case 7:
                printf("Total Income");
                break;
            default:
                break;

        }
    }
    return 0;
}