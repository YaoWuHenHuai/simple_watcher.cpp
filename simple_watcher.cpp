#include <sys/inotify.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
int main (void)
{
        int fd, wd;
        char buf[200];
        fd = inotify_init();

        //we receive a new inbound from the frontend meaining the user has added a device to his account, so we will add this new device to the database,
        wd = inotify_add_watch(fd, "/var/www/veljos.com/login/display/apis/db_apis/inbound/", IN_CREATE);
        char variable[10] = "Hello";
        while(1)
        {
                read(fd, buf, 200);
                printf("\n File name received: %s AA \n", ((struct inotify_event*)buf)->name);


                //create a flag for further handler(in order t avoid conflict with other queries)
                ofstream myFile("/var/www/veljos.com/login/display/apis/db_apis/flag/o_flag.txt");

                //run sh function which will add device and related to database,
                system("./new_user.sh");

                printf("\n Should run service... \n");

                sleep(10);
                //basically the watcher wont work till that files is rm, it will be removed by the sh script, trhough the function updatE_o_flag
                ifstream file("/var/www/veljos.com/login/display/apis/db_apis/flag/o_flag.txt");
                while(file.is_open()){
                sleep(4);
                ifstream file("/var/www/veljos.com/login/display/apis/db_apis/flag/o_flag.txt");
                }
        }
        return 0;
}
