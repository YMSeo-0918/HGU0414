#include "header.h"

int main(int argc, char** argv)
{
    int student_id = atoi(argv[1]);

    char student_name[100];
    int student_section;

    // open the student info file
    FILE* fp;
    fp = fopen("data//student_info.txt", "r");

    // read student info until it finds the student_id
    // hint: you can use fscanf(fp, "%s %s %s\n", buffer1, buffer2, buffer3)
    // hint: use atoi(str) function to convert string to integer
    int temp = 0;
    int non = 0;    
    while(temp != student_id){
    	fscanf(fp,"%d %s %d", &temp, student_name, &student_section); 
    	non++;
    
   }

    fclose(fp);

    // Print the (1) result
    printf("Student ID: %d, Name: %s, Section Number: %d\n", 
            student_id, student_name, student_section);
    if(non>100) {
	printf("There is no student with the student ID: %d", student_id);
	exit(-1); 
    }   
    // open the section score
    if (student_section == 1)
    {
        fp = fopen("data//scores_section1.dat", "r");
    }
    else
    {
        fp = fopen("data//scores_section2.dat", "r");
    }
    
    // read scores and copy values to an integer array
    const int num_sec_students = 50;
    int sec_scores[num_sec_students];
    
    // hint: use fread() function to read binary file	
    int i=0;
    while(!feof(fp)){
    	fread(sec_scores+i,sizeof(int),1,fp);
	i++;
    }    
    fclose(fp);

    // calculate mean and variance
    double sec_mean;
    double sec_var;

    sec_mean = calMean(sec_scores,num_sec_students);    
    sec_var = calVariance(sec_scores, num_sec_students);
    // Print the (2) result
    printf("The average score and s.d of Section %d ", student_section);
    printf("are %.2f and %.2f, respectively.\n", sec_mean, sqrt(sec_var));

    // get student's score
    int student_score;
    // note that the student info and scores 
    // are sorted according to increasing order of student id

    // sort scores
    if(student_section == 1)
    	student_score = sec_scores[student_id-32000000-1];
    else student_score = sec_scores[student_id-32000050-1];
    sortArray(sec_scores, num_sec_students);
	// find student's rank in the section
    int student_rank = findRank(student_score, sec_scores, num_sec_students);

    // Print the (3) result
    printf("The student's score is %d and the rank is %d in Section %d.\n",
        student_score, student_rank, student_section);

    return 0;
}
