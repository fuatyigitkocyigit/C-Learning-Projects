#include <stdio.h>
#include <stdlib.h>

int divisorPower(int numArg, int dArg)
{
    //Creating a power counter variable and starting it from 0.
    int power=0;
    //
    //If the number is bigger than divisor, it can't be divided so we return 0.
    if(dArg>numArg){
        return 0;
    }
    //
    //If the number is equal to the divisor, this means that is the end of our recursion and it will return 1.
    else if(dArg==numArg){
        return 1;
    }
    //
    //I started my power count from 0. If the divisor divides the number evenly, with the recursion, I increased power count and divided the number to the division and repeated the method with recursion.
    else if(numArg%dArg==0){
        //I divided the number to the divisor here.
        numArg=numArg/dArg;
        //
        //Then I created my recursion, so I can find my final power count.
        power=1+divisorPower(numArg,dArg);
        //
    }
    //
    //Then I returned the power count result.
    return power;
    //
}

int main()
{
    int num;
    int d;
    int p;

    printf("Enter number> ");
    scanf("%d", &num);
    printf("Enter divisor> ");
    scanf("%d", &d);
    p = divisorPower(num, d);
    printf("%d power of %d divides %d evenly.", p, d, num);

    return 0;
}

