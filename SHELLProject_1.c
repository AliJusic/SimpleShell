#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<stdbool.h>
#include<dirent.h>


/* Program header:
 * This program implements a simple shell (mysh) that allows users to enter commands.
 * The shell supports basic commands such as 'myls,' 'mypwd,' 'mygrep,' and 'mycd,' and executes them
 * by forking new processes. It provides a command-line interface for basic file and directory operations.
 */


int main(int argc, char *argv[], char *envp[]) 
{ 
 char temp[100];
 bzero(temp, 100);
 
 /* Variable initialization */ 
 char c = '\0';
 pid_t child_id;
 printf("mysh# ");
 while(c != EOF) { 
    c = getchar(); 
    switch(c) { 
    case '\n': /* parse and execute. */
            
            char *token = strtok(temp, " "); // Tokenize the command string using space as a delimiter.
            char *command = token; // Extract the command from the tokenized string.

            char *args[100]; // Array for storing command arguments
            int arg_count = 0;
            // Go through the tokenized string to extract and store arguments.
            while(token != NULL){
                args[arg_count++] = token; // Assign the current token to the args array and increment the counter.
                token = strtok(NULL, " "); // Move to the next token in the string.
            }
            args[arg_count] = NULL; // Set the last element of the args array to NULL to indicate the end of arguments.

            // Check the commands, when found, execute the corresponding actinos
            if(strcmp(command, "myls") == 0){    
                // Fork a new process to execute 'myls' command.            
                if((child_id = fork()) == 0){    
                    execv("../../bin/ls", args);  // Execute the ls command
                }
            }
            else if(strcmp(command, "mypwd") == 0){
                // Fork a new process to execute 'mypwd' command.               
                if((child_id = fork()) == 0){       
                    execv("../../bin/pwd", args);  // Execute the pwd command
                }
            }

             else if(strcmp(command, "mygrep") == 0){  
                // Fork a new process to execute 'mypwd' command.             
                if((child_id = fork()) == 0){       
                    execvp("../../bin/grep", args);  // Execute the grep command
                }
            }

            else if(strcmp(command, "mycd") == 0){               
                // Check if the user has entered an arguments for  file destination
                if(arg_count > 1) {
                    // Change the current directory to the directory user has entered, which is at args[1]. 
                    if (chdir(args[1]) == -1) {
                        perror("cd");
                    }
                } else {
                    fprintf(stderr, "cd: missing argument\n"); // User has not enetered a destination file
                }
            }
            else{
                // Print an error message for invalid commands.
                printf("Invalid command\n");               
            }

        // Clear the temporary buffer for the next input.
        bzero(temp,100);
        break; 
    default: 
        // Append the current character to the temporary buffer.
        strncat(temp, &c, 1); 
        break; 
    } 
 } 
 /* some processing before terminating. */ 
 return 0; 
} 
