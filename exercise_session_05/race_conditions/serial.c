#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80

int read_file(char *path,int *buff,int *size){

    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_count = 0,i=0;

    
    /* Open file */
    FILE *file = fopen(path, "r");
    
    if (!file)
    {
        perror(path);
        return EXIT_FAILURE;
    }
    
    /* Get each line until there are none left */
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        /* Print each line */
        //printf("line[%06d]: %s", ++line_count, line);
        buff[i] = atoi(line);
        i++;
        
    }
    
    *size = i;
    /* Close file */
    if (fclose(file))
    {
        return EXIT_FAILURE;
        perror(path);
    }
    return 0;
}






int main(int argc, char *argv[]){

	int num_size, true_n0=646016;
	int numbers[2000000];
	
	read_file("num.txt",numbers,&num_size);
	printf("Size of integer array/file: %d\n",num_size);

    // first loop
    int maxval = 0;
    for (int i=0;i<num_size;i++) if (numbers[i] > maxval) maxval = numbers[i];
    printf("max number in file: %d\n",maxval);	

    // second loop
    int num_n0 = 0;
    for (int i=0;i<num_size;i++) if (numbers[i] == 0) num_n0++;
    printf("number of 0s in file: %d\n",num_n0);  
    printf("true number of 0s in file: %d\n",true_n0);  

    return 0;
}
