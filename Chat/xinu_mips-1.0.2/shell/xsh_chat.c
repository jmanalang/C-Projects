#include <kernel.h>
#include <stdlib.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>
#define message_length 100 

char username[20]; //array where user inputs the username into below are the default usernames
char user1[9]= {'u', 's', 'e', 'r', ' ', '0', '1', ':', ' '}; //Default Username for first user
char user2[9]= {'u', 's', 'e', 'r', ' ', '0', '2', ':', ' '}; //Default Username for second user
char messages[message_length]; //array reserved for messages.
int checker  = 0; //just a check if the usernames are valid. In this case it's the default names above.
int x;




command xsh_chat(ushort stdin, ushort stdout, ushort stderr, ushort nargs, char *args[]) {
	/*start login code*/
	fprintf(stdout, "Please type in your username to chat\n"); //Prompts to user to type in a username
	read(stdin, username, message_length); //stores username into a variable
	if(strncmp(username, "user01\n", 7) == 0){  //checks if valid user name
		fprintf(stdout, "password: ");
		read(stdin, messages, message_length); //checks if valid password
		if(strncmp(messages, "password1\n", 10) == 0) {
			checker = 1; //verify username and password allowing chat
		}
		 else {
			fprintf(stdout, "INVALID PASSOWORD. SHUTTING DOWN.\n"); //password is invalid ends program
			checker = 0;
		}
	} 



	else if(strncmp(username, "user02\n", 7) == 0){
		fprintf(stdout, "password: ");
		read(stdin, messages, message_length);
		if(strncmp(messages, "password2\n", 10) == 0) {
			checker = 1; //verify username and password allowing chat
		}
		 else {
			fprintf(stdout, "INVALID PASSOWORD. SHUTTING DOWN.\n");
			checker = 0;
		}
	} 


	else {
		fprintf(stdout, "Invalid Username. Exiting\n");
		checker = 0; //username is not recognized and the program shuts down
	}
	/*end login code*/

	/*=============*/

	/*Shutdown code*/

	if(strncmp(username, "/exit\n", 6)== 0 ) { //user typed exit command to leave the chat
		fprintf(stdout, "Shutting Down\n");
		checker = 0;
	}

	/*end shutdown code*/

	/*=======================*/

	/*Chat Portion of the code*/
	if(checker == 1) {
		/*just prompts*/
		fprintf(stdout, "\n");
		fprintf(stdout, "===================================================\n");
		fprintf(stdout, "You are allowed to chat!\n");
		fprintf(stdout, "Type: /exit to leave chat\n");
		fprintf(stdout, "100 Character Limit Per Line\n");
		fprintf(stdout, "Nothing will break, it will just look funny\n");
		fprintf(stdout, "===================================================\n");
		while(checker == 1) {
			if(strncmp(messages, "/exit\n", 6) == 0) {
				checker = 0; //exits the chat
			}
			if(stdin == TTY0) {
				for(x = 0; x < message_length; x++) {
					messages[x] = '\0';
				}
				read(TTY0, messages, 100); //read from other user
				write(TTY1, user1, 9); //writes the username of the user chatting
				write(TTY1, messages, 100); //write the message to the other user
			} 
			else if (stdin == TTY1) {
				for(x = 0; x < message_length; x++) {
					messages[x] = '\0';
				}
				read(TTY1, messages, 100);
				write(TTY0, user2, 9);
				write(TTY0, messages, 100);
			}
		}
	}
	return 0;
}


