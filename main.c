#include "functiondec.h"

//   cout << "1: NewLogin\n";
//     cout << "2: Logout\n";
//     cout << "3: Logged IN Users\n";
//     cout << "4: Set Per Hour Cost\n";
//     cout << "5: Logout All The Users\n";
//     cout << "6: Get pc Status";
//     cout << "7: Calculate Total Income\n"
//     cout << "8: Switch on/off PC";
//              9: send message to computer
//     cout << "Enter your choice from 1 - 8";

int main()
{
    ///////////pthread_mutex_init(&mutexthread,NULL);
    pthread_rwlock_init(&rw_lock, NULL);
    for(int i=0;i<10;i++)
    {
        total_pc[i].pc_no = i;
        total_pc[i].status = 0;
        pipe(filed[i]);
    }

    while(1)
    {
        int choice =  intial_screen();
        switch(choice)
        {
            case 1:
                printf("logging in user check available pc and start the pc\n\n");
                login_newuser();
                break;
            case 2:
                printf("Logout user and shutdown pc\n\n");
                logout_user();
                break;
            case 3:
                printf("show all the logged in users details\n\n");
                Display_login_user();
                break;
            case 4:
                printf("Set per hour cost\n\n");
                setcost();
                break;
            case 5:
                printf("Logout all the user and shutdown all th pc\n\n");
                logoutall();
                break;
            case 6:
                printf("Get Pc status\n\n");
                getpcstatus();
                break;
            case 7:
                printf("Total Income\n\n");
                getincome();
                break;
            case 8:
                printf("switch pc ON/OFF\n\n");
                changepcstatus();
                break;
            case 9:
                printf("Enter Details to add balance to account\n\n");
                prepaidplan();
                // printf("Send Message to computers and users\n\n");
                // sendmsg();
                break;
            default:
                break;

        }
    }
    pthread_rwlock_destroy(&rw_lock);
    ////////////pthread_mutex_destroy(&mutexthread);
    return 0;
}