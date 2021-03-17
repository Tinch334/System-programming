/*
 * A simplified implementation of the "ls" function. Has tree modes, lists all files, lists all directories, list all files and i-node number.
 * By: Martín Goñi
 */

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

typedef struct stat statDef;

void PrintUsage(FILE *stream, int exitCode);
void AnalizeDirectory(int mode, char *dirName);
void ConcatenatePath(char *path, char *path_1);
void PrintElem(int mode, char *name, statDef elem);


int main(int argc, char *argv[]){
    int nextOption;
    //What mode the program is operating in: 1. List all files, 2. List all directories, 3. List i-node number and name of files
    int mode;
    int argCount = 0;

    const char shortOptions[] = "edih";
    char passedDirStr[255];

    //This struct will store the info of the entered folder.
    struct stat passedDirInfo;
    //Stores the directory stream of the entred folder.

    /*
     *  ARGUMENT PARSING
     */

    //If no arguments are passed show usage information.
    if (argc <= 1) {
        PrintUsage(stderr, 1);
    }

    do{
        nextOption = getopt_long (argc, argv, shortOptions, NULL, NULL);
        
        //If more than one argument is specified show usage information.
        if (argCount > 1) {
            PrintUsage(stderr, 1);
        }

        switch(nextOption) {
            case 'e':
                mode = 1;
                break;

            case 'd':
                mode = 2;
                break;

            case 'i':
                mode = 3;
                break;
                
            case 'h':
                PrintUsage(stdout, 0);
                break;

            //An invalid option has been used, show usage information.
            case '?':
                PrintUsage(stderr, 1);
                break;

            //No more options, exit loop.
            case -1:
                break;

            //An unknown error, abort program
            default:
                abort();
        }

        argCount++;
    }
     while (nextOption != -1);

    argCount = 0;

    for (int i = optind; i < argc; i++) {
        if (argCount >= 1){
            PrintUsage(stderr, 1);
        }
        
        strcpy(passedDirStr, argv[i]);

        argCount++;
    }

    //If no directory is passed show usage.
    if (argCount == 0) {
        PrintUsage(stderr, 1);
    }

    /*
     *  MAIN PROGRAM
     */

    //Get information about the directory.
    stat(passedDirStr, &passedDirInfo);

    //"my_ls" on works on directories, make sure user passed a directory.
    if (!S_ISDIR(passedDirInfo.st_mode)){
        fprintf(stderr, "my_ls: %s isn't a directory\n\n", passedDirStr);
        PrintUsage(stderr, 1);
    }

    AnalizeDirectory(mode, passedDirStr);

    printf("\n\n");

    return 0;
}

void PrintUsage(FILE *stream, int exitCode){
    fprintf(stream, "Usage: my_ls <option> <directory>\n");
    fprintf(stream, "Displays elements at the specified directory according to the given option\n\n");

    fprintf(stream, "One and only one of this options has to be used\n");
    fprintf(stream, "\t-e\tList all files in <directory>\n");
    fprintf(stream, "\t-d\tList all directories in <directory>\n");
    fprintf(stream, "\t-i\tList i-node number and name of files in <directory>\n");
    fprintf(stream, "\t-h\tShow this help message and exit\n");

    exit(exitCode);
}


void AnalizeDirectory(int mode, char *dirName){
    DIR *dir;
    //Stores the pointer returned by "readdir()", which points to a "dirent" structure containing info about the element.
    struct dirent *sd;

    //Open a directory stream corresponding to the passed dir.
    printf("%s:\n", dirName);
    dir = opendir(dirName);

    //Read every element in the given dir.
    while ((sd = readdir(dir)) != NULL) {
        struct stat elem;

        //Get name of element with proper location. This means getting the name with the name of the folder it's in, with proper formatting.
        char finalName[255];
        strcpy(finalName, dirName);
        ConcatenatePath(finalName, sd->d_name);

        //Get information about the element.
        stat(finalName, &elem);
        PrintElem(mode, finalName, elem);

        //If the element is a directory call "AnalizeDirectory" on it to get it's contents.
        if (S_ISDIR(elem.st_mode)){
            //Before recursively calling "AnalizeDirectory" make shure it's not the current or previous directory to avoid an infinite loop. To do this the last element is checked against a ".", since bot the current and previous directory have it as their last char.
            if (finalName[strlen(finalName) - 1] != '.') {
                //printf("Called: %s\n", finalName);
                printf("\n\n");
                AnalizeDirectory(mode, finalName);
            }
        }
    }

    //Close the directory after use.
    closedir(dir);
}


//Concatenates path with path_1 and stores the result in path.
void ConcatenatePath(char *path, char *path_1){
    //Check if star path already has "/".
    if (path[strlen(path) - 1] == '/' ){
        strcat(path, path_1);
    }  
    else{
        //Add slash to end of path.
        strcat(path, "/");
        strcat(path, path_1);
    }
}


void PrintElem(int mode, char *name, statDef elem){
     //What mode the program is operating in: 1. List all files, 2. List all directories, 3. List i-node number and name of files
    if (mode == 1){
        if (!S_ISDIR(elem.st_mode)) {
            printf("%s ", name);
        }
    }
    else if (mode == 2){
        if (S_ISDIR(elem.st_mode)){
            printf("%s ", name);   
        }
    }
    else if (mode == 3){
        if (!S_ISDIR(elem.st_mode)) {
            printf("%s;%ld ", name, elem.st_ino);   
        }
    }

}
