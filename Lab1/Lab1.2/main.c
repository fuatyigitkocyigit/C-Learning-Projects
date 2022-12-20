#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void readPointsFindMeans(double *firstMeanXp, double *firstMeanYp, double *secondMeanXp, double *secondMeanYp)
{
    //Creating variables.
    double firstPointx,firstPointy,x,y,secondPointx,secondPointy;
    //
    //Getting the first and second point.
    scanf("%lf%lf",&firstPointx,&firstPointy);
    scanf("%lf%lf",&secondPointx,&secondPointy);
    //
    //Creating count and sum variables. Our first count and sum are the first and second point.
    double closeToFirstPoint=1.0,closeToSecondPoint=1.0,sumOfcloseToFirstPointxs=firstPointx,sumOfcloseToFirstPointys=firstPointy,sumOfcloseToSecondPointxs=secondPointx,sumOfcloseToSecondPointys=secondPointy;
    //
    //Creating an infinite loop to get the inputs.
    while(1){
    //Loop will stop if it sees an EOF character.
    if(scanf("%lf%lf",&x,&y)==EOF){
        break;
    }
    //
    //Calculating the distances between the points.
    double distanceToFirstPoint=sqrt(pow(firstPointx-x,2)+pow(firstPointy-y,2));
    double distanceToSecondPoint=sqrt(pow(secondPointx-x,2)+pow(secondPointy-y,2));
    //Checking if the point is close to the first point or second point.
    if(distanceToFirstPoint<distanceToSecondPoint || distanceToFirstPoint==distanceToSecondPoint){
        //Increasing the count and adding the x,y value to the sum variable.
        closeToFirstPoint=closeToFirstPoint+1.0;
        sumOfcloseToFirstPointxs=sumOfcloseToFirstPointxs+x;
        sumOfcloseToFirstPointys=sumOfcloseToFirstPointys+y;
        //
    }
    else{
        //Increasing the count and adding the x,y value to the sum variable.
        closeToSecondPoint=closeToSecondPoint+1.0;
        sumOfcloseToSecondPointxs=sumOfcloseToSecondPointxs+x;
        sumOfcloseToSecondPointys=sumOfcloseToSecondPointys+y;
        //
    }
    //
    }
    //
    //Calculating the mean values and setting them.
    *firstMeanXp=sumOfcloseToFirstPointxs/closeToFirstPoint;
    *firstMeanYp=sumOfcloseToFirstPointys/closeToFirstPoint;
    *secondMeanXp=sumOfcloseToSecondPointxs/closeToSecondPoint;
    *secondMeanYp=sumOfcloseToSecondPointys/closeToSecondPoint;
    //
}

int main()
{
    double firstMeanX, firstMeanY, secondMeanX, secondMeanY;

    readPointsFindMeans(&firstMeanX, &firstMeanY, &secondMeanX, &secondMeanY);

    printf("Mean of points closer to the first point %.2f %.2f\n", firstMeanX, firstMeanY);
    printf("Mean of points closer to the second point %.2f %.2f\n", secondMeanX, secondMeanY);

    return 0;
}
