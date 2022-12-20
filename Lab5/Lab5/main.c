#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    unsigned int id; // student id
    char name[20]; // student name
    char surname[20]; // student surname
    char department[20]; // department of student
    int grade; // grade of student
} studentData;

void showRecords(FILE *filePtr);

int updateGrade(FILE *filePtr, unsigned int id, int newGrade);
int addStudent(FILE *filePtr, unsigned int id, char name[], char surname[], char department[], int grade);
int deleteStudent(FILE *filePtr, unsigned int id);
int showDepartmentRecord(FILE *filePtr, char department[]);

int main()
{
    unsigned int id;
    int newGrade;
    int status;
    char name[20];
    char surname[20];
    char department[20];
    int grade;

    int count;

    createBinaryFile();

    FILE *filePtr;
    filePtr = fopen("exam.bin","rb+");
    if (filePtr == NULL)
    {
        printf("Could not open exam.bin");
        return;
    }

    showRecords(filePtr);

    int option;

    printf("\nPlease choose an operation:\n");
    printf("1 : Update Grade\n");
    printf("2 : Add Student\n");
    printf("3 : Delete Student\n");
    printf("4 : Show Department Record\n");
    printf("> ");
    scanf("%d",&option);

    switch (option)
    {
    case 1:
        printf("\nStudent id: ");
        scanf("%d",&id);
        printf("New grade: ");
        scanf("%d",&newGrade);
        status = updateGrade(filePtr, id, newGrade);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("No student with id %d\n", id);
        break;
    case 2:
        printf("\nStudent id: ");
        scanf("%d",&id);
        printf("Name: ");
        scanf("%s",name);
	printf(" Surname: ");
        scanf("%s",surname);
        printf("Department: ");
        scanf("%s",department);
        printf("Grade: ");
        scanf("%d",&grade);
        status = addStudent(filePtr, id, name, surname, department, grade);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("There is already a student with id %d\n", id);
        break;
    case 3:
        printf("\nStudent id: ");
        scanf("%d",&id);
        status = deleteStudent(filePtr, id);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("No student with id %d\n", id);
        break;
    case 4:
        printf("\nDepartment: ");
        scanf("%s",department);
        count = showDepartmentRecords(filePtr, department);
        if (count == 0)
            printf("No student in department %s\n", department);
        else
            printf("There are %d students in department %s\n", count, department);
        break;
    }

    fclose(filePtr);
    return 0;
}

//Created a method to open the file.
FILE* openFile(){
    FILE *openingFile;
    openingFile=fopen("exam.bin", "rb+");
    if(openingFile==0){
        printf("Error!");
        return 0;
    }
    else{
        return openingFile;
    }
}
//

//Created a method to create and open the file.
FILE* openFileToCreate(){
    FILE *openingFile;
    openingFile=fopen("exam.bin", "wb");
    if(openingFile==0){
        printf("Error!");
        return 0;
    }
    else{
        return openingFile;
    }
}
//

//Created a method to close the given file.
void closeFile(FILE* closingFile){
    fclose(closingFile);
}
//

//Created a method to create a binary data file
void createBinaryFile(){
    //Created and opened the file with openFileToCreate method for writing
    FILE* createFile=openFileToCreate();
    //
    //Created student and set its variables
    studentData student={3,"Ozge","Saygi","CMPE",78};
    //
    //Used fseek to place the pointer to where we will write the student.
    fseek(createFile,(3)*sizeof(studentData),SEEK_SET);
    //
    //Wrote student to the file
    fwrite(&student,sizeof(studentData),1,createFile);
    //

    //Repeated the same process with different variables for 6 more student
    studentData student2={5,"Mert","Kucuk","CMPE",65};
    fseek(createFile,(5)*sizeof(studentData),SEEK_SET);
    fwrite(&student2,sizeof(studentData),1,createFile);
    ////
    studentData student3={7,"Cenk","Gulec","SENG",87};
    fseek(createFile,(7)*sizeof(studentData),SEEK_SET);
    fwrite(&student3,sizeof(studentData),1,createFile);
    ////
    studentData student4={12,"Selen","Sahin","EE",42};
    fseek(createFile,(12)*sizeof(studentData),SEEK_SET);
    fwrite(&student4,sizeof(studentData),1,createFile);
    ////
    studentData student5={15,"Dolunay","Derin","SENG",71};
    fseek(createFile,(15)*sizeof(studentData),SEEK_SET);
    fwrite(&student5,sizeof(studentData),1,createFile);
    ////
    studentData student6={19,"Suna","Yilmaz","EE",94};
    fseek(createFile,(19)*sizeof(studentData),SEEK_SET);
    fwrite(&student6,sizeof(studentData),1,createFile);
    //
    //Closed the file with closeFile method.
    closeFile(createFile);
    //
}
//

void showRecords(FILE *filePtr)
{
    fseek(filePtr, 0, SEEK_SET);

    printf("\n%-3s %-20s %-20s %-20s %s\n",
                   "ID",
                   "Name",
		           "Surname",
                   "Department",
                   "Grade");

    while (!feof(filePtr))
    {
        studentData student;
        int result = fread(&student, sizeof(studentData), 1, filePtr);
        if (result != 0 && student.id != 0)
        {
            printf("%-3d %-20s %-20s %-20s %d\n",
                   student.id,
                   student.name,
		   student.surname,
                   student.department,
                   student.grade);
        }
    }
}

int updateGrade(FILE *filePtr, unsigned int id, int newGrade)
{
    //Created an empty studentData. Will change its variables according to binary file.
    studentData emptyStudent={0,"","","",0};
    //
    //Location of student is id
    int location=id;
    //
    //Used fseek method to place the pointer to updating student.
    fseek(filePtr,location*sizeof(studentData),SEEK_SET);
    //
    //Read the data and placed it to the emptyStudent variable.
    fread(&emptyStudent,sizeof(studentData),1,filePtr);
    //
    //If the id's are matched, change grade to the newGrade.
	if(emptyStudent.id==id){
        //Changed grade to the newGrade.
        emptyStudent.grade=newGrade;
        //
        //Used fseek method to place the pointer to the place of updated student again.
        fseek(filePtr,location*sizeof(studentData),SEEK_SET);
        //
        //Wrote our new data to the binary file
        fwrite(&emptyStudent,sizeof(studentData),1,filePtr);
        //
        return 1;
    }
    //
    //Else, return 0
    else{
        return 0;
    }
    //
}

int addStudent(FILE *filePtr, unsigned int id, char name[], char surname[], char department[], int grade)
{
    //Location of student is id
    int location=id;
    //
    //Used malloc to make Dynamic Memory Allocation for 2 studentData. First one will be the new student and second one will be for checking duplicates.
    studentData* emptyStudent=(studentData*)malloc(sizeof(studentData));
    studentData* emptyStudent2=(studentData*)malloc(sizeof(studentData));
    //
    //Setting the variables of the emptyStudents. emptyStudent2 is set to be empty. We will change its variables according to binary file..
    emptyStudent->id=id;
    emptyStudent2->id=0;
    ////
    strcpy(emptyStudent->name,name);
    strcpy(emptyStudent2->name,"");
    ////
    strcpy(emptyStudent->surname,surname);
    strcpy(emptyStudent2->surname,"");
    ////
    strcpy(emptyStudent->department,department);
    strcpy(emptyStudent2->department,"");
    ////
    emptyStudent->grade=grade;
    emptyStudent2->grade=0;
    //
    //Used fseek method to place the pointer for checking duplicates.
    fseek(filePtr,(id)*sizeof(studentData),SEEK_SET);
    //
    //Read the data and placed it to the emptyStudent2 variable.
    fread(emptyStudent2,sizeof(studentData),1,filePtr);
    //
    //Check if there is already a student with the same id. If yes, return 0
    if(emptyStudent2->id==id){
        //Freed the memory
        free(emptyStudent);
        //
        return 0;
    }
    //
    //Else, add to the file.
    else{
        //Used fseek method to place the pointer to id. place for writing.
        fseek(filePtr,(id)*sizeof(studentData),SEEK_SET);
        //
        //Wrote the emptyStudent to the file
        fwrite(emptyStudent,sizeof(studentData),1,filePtr);
        //
        //Freed the memory
        free(emptyStudent);
        //
        return 1;
    }
    //
}

int deleteStudent(FILE *filePtr, unsigned int id)
{
    //Created an empty studentData. Will change its variables according to binary file.
    studentData emptyStudent={0,"","","",0};
    //
    //Location of student is id
    int location=id;
    //
    //Used fseek method to place the pointer for updating student.
    fseek(filePtr,location*sizeof(studentData),SEEK_SET);
    //
    //Read the data and placed it to the emptyStudent variable.
    fread(&emptyStudent,sizeof(studentData),1,filePtr);
    //
    //If the ID's are matched, delete the student.
    if(emptyStudent.id==id){
        //Created an empty studentData to delete the student and set it as emptyStudent2
    	studentData emptyStudent2={0,"","","",0};
        /*
        emptyStudent2.id=0;
        emptyStudent2.name="";
        emptyStudent2.surname="";
        emptyStudent2.department="";
        emptyStudent2.grade=0;
        */
        //
        //Used fseek method to place the pointer to the place of deleted student again.
    	fseek(filePtr,location*sizeof(studentData),SEEK_SET);
    	//
    	//Deleted the student and wrote the emptyStudent2 to the file.
    	fwrite(&emptyStudent2,sizeof(studentData),1,filePtr);
    	//
        return 1;
	}
	//
	//Else, return 0
	else{
        return 0;
	}
	//
}

int showDepartmentRecords(FILE *filePtr, char department[])
{
    //Created a count variable to hold the department count
    int count=0;
    //
    //Created a bool variable to check the students with the same department
    bool sameDepartment;
    //
    //Created a char variable to check the duplicates.
    char printed[20];
    //
    //Created an empty studentData. Will change its variables according to binary file.
    studentData emptyStudent = {0,"","","",0};
    //
    //Printed the table topics
    printf("\n%-3s %-20s %-20s %-20s %s\n","ID","Name","Surname","Department","Grade");
    //
    //Used fseek method to place the pointer.
    fseek(filePtr,sizeof(studentData),SEEK_SET);
    //
    //Created a while loop which will stop when there is no data.
    while(!feof(filePtr)){
        //Read data from the binary file and place it to the emptyStudent variable
        fread(&emptyStudent,sizeof(studentData),1,filePtr);
        //
        //Checking if the student is already printed (To prevent any error). If it is, then continue with next data
        if(strcmp(emptyStudent.surname,printed)==0){
            continue;
        }
        //
        //Check if the student has the same department. If has the same department, set boolean to true
        if(strcmp(emptyStudent.department,department)==0){
            sameDepartment=true;
        }
        //
        //Else, set to false
        else{
            sameDepartment=false;
        }
        //
        //If the student has same department, print it and increase the count by 1
        if(sameDepartment==true){
            printf("%-3d %-20s %-20s %-20s %d\n",emptyStudent.id,emptyStudent.name,emptyStudent.surname,emptyStudent.department,emptyStudent.grade);
            strcpy(printed,emptyStudent.surname);
            count++;
        }
        //
        //Else, continue
        else{
            continue;
        }
        //
    }
    //
    return count;
}
