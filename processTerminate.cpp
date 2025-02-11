#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/resource.h>

using namespace std;

int main() {
    pid_t pid = fork(); // Fork a new process

    if (pid == -1) {
        cerr << "Failed to create process!" << endl;
        return 1;
    } 
    else if (pid == 0) {
        // Child process: Execute a program (e.g., open TextEdit on macOS)
        execlp("open", "open", "-a", "TextEdit", NULL);
        
        // If execlp fails
        cerr << "Failed to execute process!" << endl;
        exit(1); // Exit with error
    } 
    else {
        // Parent process
        cout << "Process created successfully. PID: " << pid << endl;

        // Retrieve and display some process attributes
        struct rusage usage;
        if (getrusage(RUSAGE_CHILDREN, &usage) == 0) {
            cout << "User CPU time used: " << usage.ru_utime.tv_sec << " seconds" << endl;
            cout << "System CPU time used: " << usage.ru_stime.tv_sec << " seconds" << endl;
        } else {
            cerr << "Failed to get process attributes!" << endl;
        }

        sleep(3); // Let the process run for 3 seconds

        // Terminate the child process
        if (kill(pid, SIGTERM) == 0) {  // SIGTERM allows graceful termination
            cout << "Process terminated successfully using SIGTERM!" << endl;
        } else {
            cerr << "Failed to terminate process!" << endl;
        }

        // Wait for the child process to exit properly
        int status;
        waitpid(pid, &status, 0);

        // Check exit status
        if (WIFEXITED(status)) {
            cout << "Child process exited with status: " << WEXITSTATUS(status) << endl;
        } else {
            cout << "Child process did not exit normally!" << endl;
        }
    }

    return 0;
}
