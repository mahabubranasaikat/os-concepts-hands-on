#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork(); // Fork a new process

    if (pid == -1) {
        // Fork failed
        cerr << "Failed to create process!" << endl;
        return 1;
    } else if (pid == 0) {
        // Child process: Execute a program (e.g., open TextEdit on macOS)
        execlp("open", "open", "-a", "TextEdit", NULL);

        // If execlp fails
        cerr << "Failed to execute process!" << endl;
        return 1;
    } else {
        // Parent process: Wait for the child process to complete
        cout << "Process created successfully. PID: " << pid << endl;
        wait(NULL);
    }

    return 0;
}
