/* Jose Lopez
*  CS3377 Assignment 2
*  
*  The purpose of this assignment is to obtain information about a directory's files and subdirectories. It will calculate
*  the amount of files, directories, and size of all the files in bytes. The program will make use of an absolute path, to 
*  find the directory where information will be calculated. This path is passed as an argument. If the user puts more than
*  one argument then, the program will display error. The program depends on mostly the stat, unistd, and dirent header files
*  to allow the program to obtain information about directories and its files. 
*/
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*Will recursively go trough all files in the directory. It does this by first going through each file inside that directory
* until a directory is found. If it is found, then recall the same function but now with the address of the directory. It will
* keep doing this process until our entry structure is null, meaning every file has been processed
*/
void processDir(const char *name, int *fileCount, int *dirCount, int*sizeCount){
    DIR *dir;					//Represents current directory
    struct dirent *entry;			//Represents information about directory
    struct stat buffer;				//Used to find file information (Directory or file?, size?)
    if (!(dir = opendir(name))){		//If error opening the directory or file
        printf("%s\n", "Could Not Open File");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {	//Until every process has been processed
        if (entry->d_type == DT_DIR) {		//If current file is a directory
            char path[1024];			//Max buffer for the path name. Anything higher will be an error
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) //Ignore the . and ..
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);	//Create the new path name
            processDir(path, fileCount, dirCount, sizeCount); //Recursive call
            (*dirCount)++; 				   //Dereference pointer and increment it
        } 
	else {					//If it is a file
            char path[1024];
        	snprintf(path, sizeof(path), "%s/%s", name, entry->d_name); //Name of file plus address, so stat can find it
        	if((stat(path,&buffer)) == 0){
        		(*sizeCount) += buffer.st_size; //Dereference and add pointer
        	}
            (*fileCount)++; //Deference and add pointer
        }
    }
    closedir(dir); //Close the directory
}

/* Main Method is just responsible for initialziing all of our values that will store the file size, amount of files, and 
*  directories. It will also do some very basic input validation, such as input cannot have more than 2 arguments
*/
int main(int argc, char *argv[]) {
	if(argc > 2){ 				//If arguments is greater than 2  end program
		printf("%s", "Invalid Amount Of Arguments");
		return 0;
	} 
	int fileCount = 0;
	int dirCount = 0;
	int sizeCount = 0;
        processDir(argv[1],&fileCount, &dirCount, &sizeCount);
	//All of this output will be sent to standard out. 
    	printf("The total number of directories in directory %s is %d\n", argv[1], dirCount);
    	printf("The total number of files in directory %s is %d\n", argv[1], fileCount);
    	printf("The total number of bytes occupied by all files in %s is %d\n", argv[1],sizeCount);
    	return 0;
}
