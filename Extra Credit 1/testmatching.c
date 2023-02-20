
#include <stdio.h>

int main(){

    int output_list[] = {0,0,0,0,0};    // Initialize an output list to print to the user at the end
    int programmers[5][5],departments[5][5];    // Initialize a 2D array for departments and a 2D array for programmers

    char filename[20];
    printf("Enter the name of the input file: ");
    scanf("%s",filename);
    FILE* fp = fopen("data.txt","r");
    if (fp == NULL){
        printf("Error: Please recheck your file");
    }
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){                          // This entire chunk right here is just file I/O from the data file
            fscanf(fp,"%d",&departments[j][i]);
        }
    }
    for (int i=0;i<5;i++){
        for (int j=0;j<5;j++){
            fscanf(fp,"%d",&programmers[j][i]);
        }
    }
    

    /*
    Start of the looping check to match all 
    programmers to a department
    */

    int allMatched = 0; // Initialize a variable to put us in the loop
    while (allMatched == 0){
        for (int i=0;i<5;i++){  // Main loop that goes once for each department

            if (output_list[i] == 0){   // Only runs if the dept hasn't been matched to a programmer already from a previous loop
                int importance = 0; // Importance starts at the zeroth index (first programmer in the list)
                int preferredProg = departments[i][importance]; // The preferred programmer for the current department
                int copy_exists = 0;    // Flag to signify if there are other copies of the current preferredProg

                /*
                Checks to see if the programmer it wants is already taken. If so, it changes the preferred programmer
                to the next one in the list then restarts the loop to check if the new choice is taken.
                Runs until it has found a choice
                */

                for (int j=0;j<5;j++){      // Loops through the output list
                    if (preferredProg == output_list[j]){   // If the preferred programmer is already in the output list
                        preferredProg = departments[i][++importance];   // Update the preferred programmer to be the next one in the list
                        j = -1;  // Put j equal to -1 so that the loop starts again. It will then check to see if the new value is in the output list
                    }

                }



                // If the choice has not been selected yet, check if any other items have that choice
                
                // Loop to mark where the copies are at

                int copies[5] = {0,0,0,0,0};
                copies[i] = 1;

                for (int j=i+1;j<5;j++){    // Loop from the next index to the end of the list to check for copies
                    if (departments[j][0] == preferredProg){    // If the other department's first choices are the same
                        copies[j] = 1;  // Mark the index of the copies with a 1
                        copy_exists = 1;
                    }
                }


                if (copy_exists == 1){  // If there are copies
                    for (int j=0;j<5;j++){  // Loop through the programmer
                    int chosenDepartment = programmers[preferredProg-1][j]; // The current dept the programmer is looking at
                    if (copies[chosenDepartment-1] == 1){   // If the index of that is marked in the copy
                        output_list[chosenDepartment-1] = preferredProg;    // Add the programmer to the output list at that dept
                        break;  // Break out of the loop since we have found the match and we don't want to continue looping

                    }
                    }
                }

                /* 
                If the preferred programmer is not already taken and there are no other copies in the other departments,
                assign that programmer to the output list at that department index
                */

            if (copy_exists == 0){   // If there are no copies anywhere in the department list
                output_list[i] = preferredProg; // Set the preferred programmer to the index of that department in the output list
            }

            }

           /*
           Final loop through the output list 
           to check if every department has a programmer
           */
          
          }
        int finished = 1;   // Initialize a variable to signify whether we're finished or not
        for (int i=0;i<5;i++){
            if (output_list[i] == 0){   // If there is an item in the output list that's equal to zero, then not every dept has found a match
                finished = 0;   // Change finished to 0. This means that the while loop will run again and iterate through each item again
            }
        }
        if (finished == 1){  // If every one has a match, then we're finished
            allMatched = 1;  // Change allMatched to 1 so that the while loop doesn't start again
        }
    }

    
    for (int i=0;i<5;i++){     // Iterate through the final output list to print the final info to the user
        printf("Department #%d will get Programmer #%d\n",i+1,output_list[i]);
    }
    
}