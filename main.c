#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFileToScreen(int mark);
void writeToFile();
void menu();
void doTask(int option);
void markComplete(int option);
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
    // Allows User to choose from the menu screen
    int option = 0;
    while(option != 5){
        menu();
        printf("Choose Option: ");
        //Makes sure input is a valid option
        if(scanf("%d", &option) == 1){
            doTask(option);
        }
        else{
            printf("Not Valid Input\n");
            break;
        }
    }
}


// Does the task that the user picked from the menu
void doTask(int option){
    int mark = 0;
    // Views task in todo.txt file
    if(option == 1){
        system("clear");
        printf("\n");
        printFileToScreen(0);
        printf("\n");
    }
    // Add task to todo.txt file
    else if(option == 2){
        clear_input_buffer();
        writeToFile();
    }
    // Marks task as complete
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
    // Deletes task from file
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


// Will print whats in the todo.txt file to screen
void printFileToScreen(int mark){
    int count = 1;
    FILE *fp = fopen("todo.txt", "r");
    char firstChar;
    char todoList[MAX_SIZE];
    printf("%s\n", BANNER);
    // Grabs each line in the file and prints it to the screen one by one
    while(fgets(todoList, MAX_SIZE, fp) != NULL){
        // If We need to List the lines we add the line number before the line
        if(mark == 1)
            printf("%d. %s",count, todoList);
        else
            printf("%s", todoList);
        count++;
    }
}


// Writes task to the file
void writeToFile(){
    FILE *fp = fopen("todo.txt", "a");
    char todo[MAX_SIZE];

    printf("Task: ");

    // If Something is wrong with the file exit the program
    if (fgets(todo, sizeof(todo), stdin)==0) {
        exit(1);
    }

    //Automatically assume a new task is incomplete
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
// User will choose task to mark as complete / incomplete
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

    //Checks if task is already complete or incomplete
    if(modifyLine[0] == COMPLETE){
        modifyLine[0] = INCOMPLETE;
    }
    else{
        modifyLine[0] = COMPLETE;
    }

    // Write the updated task to the file
    FILE *fpOut = fopen("todo.txt", "w");
    for(int i = 0; i< currentLine; i++){
        fputs(buffer[i], fpOut);
    }

    fclose(fpOut);

}

// Will delete the task of the users choice
void deleteLine(int line){
    int count = 1;
    FILE *fpIn = fopen("todo.txt", "r");
    char firstChar;
    char todoList[MAX_SIZE];
    char buffer[MAX_SIZE];
    int currentLine = 0;

    // Create a temp file to hold updated todo list
    FILE *tempFile = fopen("temp.txt", "w");

    // Grabs max lines of the filew
    while(fgets(buffer, sizeof(buffer), fpIn) != NULL){
        // If this is not the deleted line, add it to the temp file
        if(count != line){
            fputs(buffer, tempFile);
        }
        count++;
    }
    fclose(fpIn);
    fclose(tempFile);

    // Deletes old todo file and makes the temp file the new todo file
    remove("todo.txt");
    rename("temp.txt", "todo.txt");
}
