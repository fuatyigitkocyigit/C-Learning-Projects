//
//  main.c
//  ted_lab4
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 20
#define MAX_ELEM 10
#define HASHSIZE 1000

typedef struct {  char *name;
                  char *lastname;
                  char name_lastname[STR_LEN];
                  long int strong_hash;
                  long int weak_hash[2];
                } Student;

unsigned int hash_text (char * list);
void strong_similar (Student studentList[MAX_ELEM], unsigned int map[MAX_ELEM][MAX_ELEM]);
void weak_similar (Student studentList[MAX_ELEM], unsigned int map[MAX_ELEM][MAX_ELEM]);


int main()
{
        unsigned int same[MAX_ELEM][MAX_ELEM];

        Student studentList[MAX_ELEM] = {
        { "ahmet","yuksel", 0, 0},
        { "mehmet","arslan", 0, 0},
        { "mustafa","kemal", 0, 0},
        { "ali","kemal", 0, 0},
        { "mustafa","kemal", 0, 0},
        { "mustafa","kemal", 0, 0},
        { "mehmet","arslan", 0, 0},
        { "kemal","ahmet", 0, 0},
        { "ali","kaan", 0, 0},
        { "kemal","kaan", 0, 0},
      };


        for (int i = 0; i < 10; i++)
        {
          strcpy(studentList[i].name_lastname, studentList[i].name);
          strcat(studentList[i].name_lastname, " ");
          strcat(studentList[i].name_lastname, studentList[i].lastname);
          studentList[i].strong_hash = hash_text(studentList[i].name_lastname);
        }

        strong_similar (studentList, same);

        printf("\nelements with hash values and similarities:\n");
        for (int i = 0; i < 10; i++)
        {
            printf("\n%-20s %5ld",studentList[i].name_lastname, studentList[i].strong_hash);
                for (int j=0; j<MAX_ELEM; j++)
                        if (same[i][j] ==1)
                            printf ("%4d",j);
        }

        printf ("\n");

        weak_similar (studentList, same);

        printf("\n\nelements with weak similarities:");
        for (int i = 0; i < 10; i++)
        {
                printf("\n%-20s %5ld",studentList[i].name_lastname, studentList[i].strong_hash);
                for (int j=0; j<MAX_ELEM; j++)
                        if (same[i][j] ==2)
                                printf ("%4d",j);
        }

        printf ("\n");
        return 0;
}


unsigned int hash_text (char * list)
{
    //Created variables
    unsigned long long int hash=0;
    int size=strlen(list);
    int sizecopy=size-1;
    //
    //Created a for loop for calculating hash of every element.
    for(int i=0; i<size; i++){
        //Calculating 26^size-1
        unsigned long long int poww=(unsigned long long int)pow(26,sizecopy);
        //
        //Applying the hash formula
        hash+=(unsigned long long int)(poww*list[i]);
        //
        //Decreasing the sizecopy as the formula requires
        sizecopy--;
        //
    }
    //
    //Taking hash mod 1000
    hash%=1000;
    //
    //Returning the hash value
    return hash;
    //
}

void strong_similar (Student studentList[MAX_ELEM], unsigned int map[MAX_ELEM][MAX_ELEM])
{
    //Created two for loop eachother to compare an index with every index
    for(int i=0;i<MAX_ELEM;i++){
        for(int ii=0; ii<MAX_ELEM; ii++){
            //Cleared the map variable.
            map[i][ii] = 0;
            //
            //Can't compare with itself
            if(i==ii){
                continue;
            }
            //
            //If there is equality, add to map
            else if(studentList[i].strong_hash == studentList[ii].strong_hash){
                map[i][ii] = 1;
            }
            //
        }
    }
    //
}

void weak_similar (Student studentList[MAX_ELEM], unsigned int map[MAX_ELEM][MAX_ELEM])
{
    //Creating variables
    unsigned int hashList[MAX_ELEM][MAX_ELEM];
    char * name;
    char * surname;
    char copyNameSurname[MAX_ELEM];
    int size=strlen(studentList);
    int sizecopy=size-1;
    //
    //Creating a for loop to calculate the hash values of name and lastname separately
    for(int i=0; i<MAX_ELEM; i++){
        //Calculating hash values of name and lastname
        studentList[i].weak_hash[0]=hash_text(studentList[i].name);
        studentList[i].weak_hash[1]=hash_text(studentList[i].lastname);
        //
    }
    //
    //Creating a 2 for loop to find weak similarities
    for(int i=0; i<MAX_ELEM; i++){
        for(int ii=0; ii<MAX_ELEM; ii++){
            //Cleared the map variable.
            map[i][ii]=0;
            //
            //Can't compare with itself
            if(i==ii){
                continue;
            }
            //
            //If the students are strong similar, add to the map as strong similar
            if(studentList[i].strong_hash==studentList[ii].strong_hash){
                map[i][ii]=1;
            }
            //
            //If the name of the students are similar, add to the map as weak similar
            else if(studentList[i].weak_hash[0]==studentList[ii].weak_hash[0]){
                map[i][ii] = 2;
            }
            //
            //If lastname of students are similar, add to the map as weak similar
            else if(studentList[i].weak_hash[1]==studentList[ii].weak_hash[1]){
                map[i][ii] = 2;
            }
            //
            //If name of the student is similar to a student's lastname, add to the map as weak similar
            else if(studentList[i].weak_hash[0]==studentList[ii].weak_hash[1]){
                map[i][ii] = 2;
            }
            //
            //If the lastname of the student is similar to a student's name, add to the map as weak similar
            else if(studentList[i].weak_hash[1]==studentList[ii].weak_hash[0]){
                map[i][ii] = 2;
            }
            //
        }
    }
    //
}
