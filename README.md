# SimpleShell
Simple shell with 4 functions. It reads input from the user, parses it, and executes commands.
Fully implemented commands: 
-	ls - Lists the files and directories in the current directory.
-	pwd - Prints the current working directory, showing the full path to the present location in the file system.
-	grep - Prints the current working directory, showing the full path to the present location in the file system.
-	cd - Changes the current directory to the specified location.
When it comes to system calls, the shell uses the fork() system call in if statements to create a new process for command execution. It then uses execv() or execvp() to replace the  child process's image with the specified command.
