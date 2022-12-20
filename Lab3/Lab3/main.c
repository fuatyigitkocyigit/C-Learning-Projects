//
//  main.c
//  ted_lab
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STR_LEN 20
#define MAX_ELEM 10
#define HASHSIZE 1000


unsigned int hash_text (char * list) ;
void strong_similar (int hval[MAX_ELEM], int map[MAX_ELEM][MAX_ELEM]) ;
void weak_similar (char list[MAX_ELEM][STR_LEN],int map[MAX_ELEM][MAX_ELEM]) ;

int main()
{
    unsigned int hashed_vals[MAX_ELEM];
    unsigned int same[MAX_ELEM][MAX_ELEM];
    char list[MAX_ELEM][STR_LEN];

    printf("Enter 10 elements:\n");
    int i = 0;
    for(i = 0; i < MAX_ELEM; i++){
        scanf("%[^\n]%*c", list[i]);
    }

    for (int i = 0; i < 10; i++)
        hashed_vals[i] = hash_text(list[i]) ;

    strong_similar (hashed_vals, same) ;

    printf("\nelements with hash values and similarities:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("\n%-20s %5d",list[i],hashed_vals[i]);
        for (int j=0; j<MAX_ELEM;j++)
            if (same[i][j] ==1)
                printf ("%4d",j) ;
    }

    printf ("\n");

    weak_similar (list,same) ;

    printf("\n\nelements with weak similarities:");
    for (int i = 0; i < 10; i++)
    {
        printf("\n%-20s %5d",list[i],hashed_vals[i]);
        for (int j=0; j<MAX_ELEM;j++)
            if (same[i][j] ==2)
                printf ("%4d",j) ;
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

void strong_similar (int hval[MAX_ELEM], int map[MAX_ELEM][MAX_ELEM])
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
            else if(hval[i] == hval[ii]){
                map[i][ii] = 1;
            }
            //
        }
    }
    //
}

void weak_similar (char list[MAX_ELEM][STR_LEN],int map[MAX_ELEM][MAX_ELEM])
{
    //Creating variables
    //int size=strlen(list);
    //int sizecopy=size-1;
    //unsigned int hashList[MAX_ELEM][MAX_ELEM];
    //int size=0;
    //char * name;
    //char * surname;
    //char copyNameSurname[MAX_ELEM];
    /*//Creating a for loop to take name and surname separately
    for(int i=0; i<MAX_ELEM; i++){
        char * name=strtok(list[i], " ");
        char * surname =strtok(NULL, " ");
        //Calculating hash values of name and surname
        hashList[i][0]=hash_text(name);
        hashList[i][1]=hash_text(surname);
        //
    }
    *///
    /*//Creating a 2 for loop to find weak similarities
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
            ////If there is similarity, add to map
            if((hashes[i][0]==hashes[ii][0]||hashes[i][0]==hashes[ii][1]||hashes[i][1]==hashes[ii][0]||hashes[i][1]==hashes[ii][0])){
                map[i][ii] = 2;
            }
            //
        }
    }
    *///
}
