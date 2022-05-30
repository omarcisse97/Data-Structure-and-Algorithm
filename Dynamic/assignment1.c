                                        /* Data Structure and Algorithm: Dynamic Memory Allocation and Structs 
                                                       This program is written by: Omar Cisse */ 
    
    
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_SIZE_TEST 25
    #define MAX_SIZE_COURSES 500
    #define MAX_LENGTH_NAME 20
    #define MAX_SECTION 10
    #define MAX_STUDENT 500
    #define MAX_SIZE_ID 50000
    #define MAX_LENGTH_STUDENT_NAME 20
    #define MAX_GRADE 100
    #define MAX_SCORES 20


    typedef struct student{ 
    int id; 
    char *lname; //stores last name of student 
    float *scores; //stores scores of the student. Size is taken from num_scores array. 
        float std_avg; //average score of the student (to be calculated) 
    }student; 

    typedef struct course{ 
        char *course_name; //stores course name 
        int num_sections; //number of sections 
        student **sections;//stores array of student arrays(2D array). Size is num_sections; 
        int *num_students;//stores array of number of students in each section. Size is num_sections;  
        int *num_scores; //stores array of number of assignments in each section. Size is num_sections; 
    } course; 
    
    course *read_courses(FILE *fp, int *num_courses);
    student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections);
    void process_courses(course *courses, int num_courses, FILE*output);
    void release_courses( course *courses, int num_courses);

    course *read_courses(FILE *fp, int *num_courses){
    course *temp = NULL;
    temp = (course*)malloc(*num_courses*sizeof(course));
    
        for(int i=0;i<*num_courses;i++){
        char nameC[100];
        fscanf(fp,"%s",nameC);
        int lenght = strlen(nameC) +1;
        if(lenght > MAX_LENGTH_NAME){
            free(temp);
            fclose(fp);
            exit(-1);
        }
        temp[i].course_name = (char*)malloc(lenght*sizeof(char));
        strcpy(temp[i].course_name,nameC);
        fscanf(fp,"%d", &temp[i].num_sections);
        if(temp[i].num_sections > MAX_SECTION){
            free(temp);
            fclose(fp);
            exit(-1);
        }
        temp[i].num_students = (int*)malloc(temp[i].num_sections*sizeof(int));
        temp[i].num_scores = (int*)malloc(temp[i].num_sections*sizeof(int));
        temp[i].sections = read_sections(fp,temp[i].num_students, temp[i].num_scores, temp[i].num_sections); 
        
    }

    return temp ;
    }

    student **read_sections(FILE *fp, int num_students[], int num_scores[], int num_sections){
        student** temp = NULL;
        temp = (student**)malloc(num_sections*sizeof(student*));
        for(int i=0;i<num_sections;i++){
            fscanf(fp,"%d %d", &num_students[i], &num_scores[i]);
            if(num_students[i] >MAX_STUDENT || num_scores[i] > MAX_SCORES){
                free(temp);
                fclose(fp);
                exit(-1);
            }
            temp[i] = (student*)malloc(num_students[i] *sizeof(student));
            for(int j=0;j<num_students[i];j++){
                temp[i][j].scores = (float*)malloc(num_scores[i] *sizeof(float));
                char name[100];
                fscanf(fp,"%d", &temp[i][j].id);
                fscanf(fp,"%s", name);
                int length = strlen(name) + 1;
                if(temp[i][j].id > MAX_SIZE_ID || length > MAX_LENGTH_STUDENT_NAME){
                    free(temp[i][j].scores);
                    free(temp[i]);
                    free(temp);
                    fclose(fp);
                    exit(-1);
                }
                temp[i][j].lname = (char*)malloc(length*sizeof(char));
                strcpy(temp[i][j].lname, name);
                float average = 0.0;
                for(int s=0;s<num_scores[i];s++){
                    fscanf(fp,"%f",&temp[i][j].scores[s]);
                    if(temp[i][j].scores[s] > MAX_GRADE){
                        free(temp[i][j].lname);
                        free(temp[i][j].scores);
                        free(temp[i]);
                        free(temp);
                        fclose(fp);
                        exit(-1);
                    }
                    average += temp[i][j].scores[s];
                }
                average = average/num_scores[i];
                temp[i][j].std_avg = average;

            }
        }

        return temp;
    }


    
    
    int main(){
        FILE *input;
        FILE *output;
        int t;
        int num_courses;
        course **list = NULL;
        input = fopen("assignment1input.txt", "r");
        if(input == NULL){
            exit(-1);
        }
        output = fopen("out.txt", "w");
         if(output == NULL){
            printf("Could not create the file\n");
            exit(-1);
        }
        fscanf(input,"%d",&t);
        if(t > MAX_SIZE_TEST){
            exit(-1);
        }
        list = (course**)malloc(t*sizeof(course*));
        for(int i=0;i<t;i++){
        fscanf(input,"%d", &num_courses);
        if(num_courses > MAX_SIZE_COURSES){
            free(list);
            fclose(input);
            exit(-1);
        }
        list[i] = read_courses(input,&num_courses);
        fprintf(output,"\n");
        process_courses(list[i], num_courses,output);
        release_courses(list[i],num_courses);
        }
        
        
    fclose(input);
    fclose(output);
        return 0;
    }

    void process_courses(course *courses, int num_courses,FILE *output){
        char** course_name = NULL;
        int* pass_count = NULL;
        float **list_of_averages_section = NULL;
        int *id;
        char **lname;
        float *avg_score;
        
        course_name = (char**)malloc(num_courses*sizeof(char*));
        list_of_averages_section = (float**)malloc(num_courses*sizeof(float*));
        pass_count = (int*)malloc(num_courses*sizeof(int));
        lname = (char**)malloc(num_courses*sizeof(char*));
        id = (int*)malloc(num_courses*sizeof(int));
        avg_score = (float*)malloc(num_courses*sizeof(float));



        for(int i=0;i<num_courses;i++){
            list_of_averages_section[i] = (float*)malloc(courses[i].num_sections *sizeof(float));
            int length_course = strlen(courses[i].course_name) + 1;
            course_name[i] = (char*)malloc(length_course*sizeof(char));
            strcpy(course_name[i],courses[i].course_name);
            pass_count[i] = 0; 
            int count = 0;
            for(int j=0;j<courses[i].num_sections;j++){
                float charge = 0;
                for(int k=0;k<courses[i].num_students[j];k++){
                    count++;
                    if(courses[i].sections[j][k].std_avg >= 70){
                    pass_count[i]++;
                    }
                    charge += courses[i].sections[j][k].std_avg;    
                }
                charge = charge/courses[i].num_students[j];
                list_of_averages_section[i][j] = charge;

            }
            student *temp = (student*)malloc(count*sizeof(student));
            int cb = 0;
            for(int w=0;w<courses[i].num_sections;w++){
                for(int q=0;q < courses[i].num_students[w];q++){
                    temp[cb] =courses[i].sections[w][q];
                    cb++;

                }
            }
            student the_best = temp[0];
            for(int q =0;q<count;q++){
                if(q == count-1){
                    break;
                } 
                if(the_best.std_avg < temp[q].std_avg){
                    the_best = temp[q];
                }    
            }
            
            id[i] = the_best.id;
            int lght = strlen(the_best.lname) + 1;
            lname[i] = (char*)malloc(lght*sizeof(char));
            strcpy(lname[i],the_best.lname);
            avg_score[i] = the_best.std_avg;
            
            fprintf(output,"%s  %d ", course_name[i], pass_count[i]);
            for(int j=0;j<courses[i].num_sections;j++){
                fprintf(output," %.2f  ", list_of_averages_section[i][j]);
            }
            fprintf(output," %d  %s  %.2f\n", id[i], lname[i],avg_score[i]);
            free(list_of_averages_section[i]);
            free(lname[i]);
            free(course_name[i]);
            free(temp);
        }
        free(list_of_averages_section);
        free(lname);
        free(course_name);
        free(id);
        free(avg_score);
        free(pass_count); 
    }
    
    
    void release_courses( course *courses, int num_courses){
        int i,j,k,l;
        for(i=0;i<num_courses;i++){
            for(j=0;j<courses[i].num_sections;j++){
                for(k=0;k<courses[i].num_students[j];k++){
                        free(courses[i].sections[j][k].scores);
                        free(courses[i].sections[j][k].lname);
                }  
                free(courses[i].sections[j]);
            }
            free(courses[i].sections);
            free(courses[i].num_students);
            free(courses[i].num_scores);
            free(courses[i].course_name); 
    }
    free(courses);
        }
    

