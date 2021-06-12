#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int executing_comands(char** argv){
    
    char  PATH[1024], *current_login;
    int for_cp, status;
    FILE *file1, *file2;
    if (strcmp(argv[0], "exit") == 0)
        exit(0);
    else if (strcmp(argv[0], " whoami") == 0){
        current_login = getenv("User");
        printf("\nCurrent login: ");
        printf("%s\n", current_login);
    }
    else if (strcmp(argv[0], "help") == 0){
        printf(" This Microshell project is made by Danila Prymak\n\n");
        printf(" For AMU \n");
        printf(" It supports the following comands:  \n");
        printf("\thelp \n\tcd \n\texit \n\town inmplementation: cp ,rm \n\twhoami \n\tchcolour(colour support)  ");
        printf("\n able to handle wrong comands");
        printf("\n display a prompt in the form [***path***] $$$$-->>, where {path} is\n the path to the current working directory;\n");
    }
    else if (strcmp(argv[0], "cd") == 0){
        if (argv[1] != NULL)
            chdir(argv[1]);
        else{
            chdir(getenv("Home"));}
    }
    else if (strcmp(argv[0], "pwd") == 0){
        getcwd(PATH, sizeof(PATH));
        printf("Your current directory is " );
        printf("%s\n", PATH);
    }
    else if (strcmp(argv[0], "chcolour") == 0){
        char cur_colour[20];
        printf("choose colour:\ngreen \nyellow \nblue \nred \ndef\n");
        fgets(cur_colour,sizeof(cur_colour),stdin);
        cur_colour[strlen(cur_colour)-1] = '\0';
        if (strcmp(cur_colour, "red") == 0){
            printf("\033[0;31m");
        }
        else if (strcmp(cur_colour, "blue") == 0) {
            printf("\033[0;34m");
         }
        else if (strcmp(cur_colour, "yellow") == 0) {
            printf("\033[0;33m");
        }
        else if (strcmp(cur_colour,"def") == 0){
            printf("\033[0m");
         }
        else{
            printf("no such a color\n");
        }
    }
    else if(strcmp(argv[0], "rm") == 0){
        file1 = fopen(argv[1], "w");
        for_cp = remove(argv[1]);
        if(for_cp != 0){
            printf("wrong name\n");
        }
    }
    else if (strcmp(argv[0], "cp") == 0){
        file1 = fopen(argv[2], "w");
        file2 = fopen(argv[1], "r");
        while((for_cp = getc(file2)) != EOF)
            putc(for_cp,file1);
        fclose(file1);
        fclose(file2);
    }else{
            if (fork() !=0)
                waitpid(-1, &status, 0);
            else{
                execvp(argv[0], argv);
                printf("Wrong name of comand\n please use \"help\" comand to see supported ones\n ");
                exit(0);
            }
        }
return 0; 
    
}

int main(){
    
        char line[1001], cwd[1024], *argv[200], *word;
        int i;
        while(1){
                if (getcwd(cwd, sizeof(cwd))!= NULL){
                printf("<<$$$$[***%s***] $$$$>>", cwd);
                fgets(line, 1001, stdin);
                word = strtok(line,  " \n\r\t\v");
                for(i = 0; i < 200 && word !=NULL;i++){
                        argv[i]= word;
                        word = strtok(NULL," \n\r\t\v");
                }
                argv[i] = NULL;
                if (argv[0] == NULL)
                    continue;
                else 
                    (executing_comands(argv));
                }
        }
}
