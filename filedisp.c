/* Jose Lopez
*  CS3377 Assignment 2
*  
*  This program will be responsible for piping the first program. It will accept 3 options, -d show amount of directories,
*  -f show amount of files, and -b show total size. 
*/
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUF 1024

int main(int argc, char *argv[])
{	
	if(argc > 2){ //If arguments surpass 2, then do option that does apply.
		printf("Invalid Amount Of Arguments\n");
	}
	char str[MAX_BUF]; //Will temporary store lines from standard in
	int count = 0; //Will count which line program is currently on
	char dir[340]; //Will hold line about directories
	char fil[340]; //Will hold line about files
	char byt[340]; //Will hold line about bytes
	while(fgets(str, MAX_BUF, stdin)){ //Fgets will get complete line and store it in str
		if(count == 0){ //If first line, then we are with directories
			strcpy(dir,str);
		} 
		if(count == 1){ //If second line, then we are with files
			strcpy(fil,str);
		}
		if(count == 2){ //If third line, then we are with bytes
			strcpy(byt,str);
		}
		count++;	
	}
	//If statements will compare string with option, that option then must be which line to print
	if(strcmp(argv[1],"-d") == 0){
		printf("%s",dir);
	}
	else if(strcmp(argv[1],"-f") == 0){
		printf("%s",fil);
	}
	else if(strcmp(argv[1],"-b") == 0){
		printf("%s",byt);
	}
	else{
		printf("Invalid Argument\n");
	}
	
    return 0;
}
