#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

void printFileToScreen(int mark);
void writeToFile();
void menu();
void doTask(int option);
void markComplete(int option);
void appendToFile(char *task, int line);
void deleteLine(int line);

//Clears buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

#define COMPLETE 'Y'//'✓' //"[x]"
#define INCOMPLETE 'N' //"[]"
#define BANNER "===== TODO LIST ====="
#define MAX_SIZE 1024

/* What Todo
 * 3. Understand if user completed their task and write to file on that line
 * 4. Complete and incomplete variables giving trouble
 * 5. Finish implementing the change between complete and incomplete
 * 6. Add Delete option
*/


int main(){
    int option = 0;
    while(option != 5){
        menu();
        printf("Choose Option: ");
        if(scanf("%d", &option) == 1){
            doTask(option);
        }
        else{
            printf("Not Valid Input\n");
            break;
        }
    }

    /* FILE *fp; */
    /* char todo[256]; */

    /* printf("Task: "); */

    /* if (fgets(todo, sizeof(todo), stdin)==0) { */
    /*     exit(1); */
    /* } */

    /* fp = fopen("todo.txt", "r"); */

    /* // Checks if there is an error opening the FILE */
    /* if (fp == NULL){ */
    /*     printf("Error Opening File\n"); */
    /*     exit(1); */
    /* } */

    /* writeToFile(todo); */

    /* printFileToScreen(); */

    /* fclose(fp); */

    /* return 0; */
}

void doTask(int option){
    int mark = 0;
    if(option == 1){
        system("clear");
        printf("\n");
        printFileToScreen(0);
        printf("\n");
    }
    else if(option == 2){
        clear_input_buffer();
        writeToFile();
    }
    else if(option == 3){
        printf("\n");
        clear_input_buffer();
        printFileToScreen(1);
        printf("Enter task number to mark complete: ");
        if(scanf("%d", &mark) == 1){
            markComplete(mark);
        }
        else{
            printf("Not Valid Input\n");
        }
    }
    else if(option == 4){
        printf("\n");
        clear_input_buffer();
        printFileToScreen(1);
        printf("Enter task number to delete: ");
        if(scanf("%d", &mark) == 1){
            deleteLine(mark);
        }
        else{
            printf("Not Valid Input\n");
        }
 
    }
}


void printFileToScreen(int mark){
    int count = 1;
    FILE *fp = fopen("todo.txt", "r");
    char firstChar;
    char todoList[MAX_SIZE];
    printf("%s\n", BANNER);
    while(fgets(todoList, MAX_SIZE, fp) != NULL){
        if(mark == 1)
            printf("%d. %s",count, todoList);
        else
            printf("%s", todoList);
        count++;
    }
}


/* void writeToFile(char *text){ */
void writeToFile(){
    FILE *fp = fopen("todo.txt", "a");
    char todo[256];

    printf("Task: ");

    if (fgets(todo, sizeof(todo), stdin)==0) {
        exit(1);
    }

    fprintf(fp, "%c %s",INCOMPLETE, todo);
    fclose(fp);
}

// Will be the Menu Interaction to tell the program what to do
void menu(){
    printf("%s\n", BANNER);
    printf("1. View Tasks\n");
    printf("2. Add Task\n");
    printf("3. Mark Task Complete\n");
    printf("4. Delete Task\n");
    printf("5. Exit\n");
}


//Save current file into bufffer, change line in buffer, save buffer to file
void markComplete(int mark){
    int count = 1;
    FILE *fpIn = fopen("todo.txt", "r");
    char firstChar;
    char todoList[MAX_SIZE];
    char buffer[MAX_SIZE][MAX_SIZE];
    int currentLine = 0;

    // Grabs max lines of the filew
    while(fgets(buffer[currentLine], MAX_SIZE, fpIn) != NULL){
        currentLine++;
    }
    fclose(fpIn);

    char* modifyLine = buffer[mark-1];
    int lineLength = strlen(modifyLine);

    if(modifyLine[0] == COMPLETE){
        modifyLine[0] = INCOMPLETE;
    }
    else{
        modifyLine[0] = COMPLETE;
    }

    FILE *fpOut = fopen("todo.txt", "w");
    for(int i = 0; i< currentLine; i++){
        fputs(buffer[i], fpOut);
    }

    fclose(fpOut);

}


void deleteLine(int line){
    int count = 1;
    FILE *fpIn = fopen("todo.txt", "r");
    char firstChar;
    char todoList[MAX_SIZE];
    char buffer[MAX_SIZE];
    int currentLine = 0;

    FILE *tempFile = fopen("temp.txt", "w");

    // Grabs max lines of the filew
    while(fgets(buffer, sizeof(buffer), fpIn) != NULL){
        if(count != line){
            fputs(buffer, tempFile);
        }
        count++;
    }
    fclose(fpIn);
    fclose(tempFile);

    remove("todo.txt");
    rename("temp.txt", "todo.txt");


}
