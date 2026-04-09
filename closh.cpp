#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

int main() { 
    string commandLine;
    int count;
    char mode;

    while (true) {
        cout << "closh>";
        getline(cin, commandLine);
        if (commandLine == "exit") break;

        cout << "count> ";
        cin >> count;
        cout << "[p]arallel or [s]equential> ";
        cin >> mode;
        cin.ignore();

        vector<pid_t> children;

        for (int i = 0; i < count; i++) {
            pid_t rc = fork(); 

            if (rc < 0) {
                perror("fork failed"); 
                exit(1);
            } else if (rc == 0) {

            char* my args[2];
            myargs[0] = strdup(commandLine.c_str());
            myargs[1] = NULL;

            execvp(myargs[0], myargs);

            perror("exec failed");
            exit(1);
            }else {
                if (mode == 's') {
                    waitpid(rc, NULL, 0);
                } else {
                    children.push_back(rc);
                }
            }
         }
         if (mode == 'p') {
            for (pid_t pid : children) {
                waitpid(pid, NULL, 0);
            }
         }
    return 0;
    }        
}
    

