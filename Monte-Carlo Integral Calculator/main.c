/*
 *Author: Haomin Lin
 *Completed Time: 08/29/2019
 *Function: Calculating Integral
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* get the time to be the seed for random numbers */

/* function declarations */
double get_function_value(double x);
double get_K(double a, double b);
double compute_Z(double a, double b, double K, double N);
double test_integral(double a, double b);

int main(void)
{
    printf("Hi, I can compute the integral of a defined function\n");
    
    double a, b; /* declare external data */
    double N; /* Define the times the user wants the experiment to run */
    int active; /* define a variable to decide the following operation */
    
    /* get the external data */
    printf("Enter the value of a: ");
    scanf("%lf", &a);
    printf("Enter the value of b: ");
    scanf("%lf", &b);
    
    /* test if a > b and correct that */
    while (a > b){
        printf("Sorry, this pair of inputs is incorrect, try another one\n");
        printf("Enter the value of a: ");
        scanf("%lf", &a);
        printf("Enter the value of b: ");
        scanf("%lf", &b);
    }
    
    active = test_integral(a, b); /* get the result of the test of integral */
    
   /* get the user's choice for undoable integral */
    while(active == 0){
        printf("Which one do you prefer, 1 for changing a & b,\n2 for modifying your function: ");
        scanf("%d", &active);
        if(active == 2){
            printf("Please motify the function.\n");
        }
        
        /* re-enter the range of integral */
        while(active == 1){
            printf("Enter the value of a: ");
            scanf("%lf", &a);
            printf("Enter the value of b: ");
            scanf("%lf", &b);
            active = test_integral(a, b);
        }
    }

    /* continue if the integral is legal */
    if(active == 3){
        double K = get_K(a,b); /* get K as the upper border of the sample space */

        /* get the number of random points from user */
        while(active){
            printf("Enter the number of test points (enter 0 if you want to quit): ");
            scanf("%lf", &N);
            
            /* end the input section */
            if(N == 0){
                break;
            }
            else{
                /* compute the integral */
                compute_Z(a, b, K ,N);
            }
        }
    }
    printf("Thank you for trusting me!\n");
}

    

/*
 *get_function_value(x) gets the value of a certain function
 * it returns the value of a function at a certain point
 */
double get_function_value(double x)
{
    double y; /* define the return value */
    y = x * x; /* function expression */
    return y;
}

/*
 *get_K(a, b) gets the value of the sample space
 *it returns two times the appromixate maximum of the function in range [a,b]
 */
double get_K(double a, double b)
{
    double x, y_pre, y_next; /* declare variables of the function */
    double y = get_function_value(a); /* assign the first value of the function to y */
    double K; /* define the value of the upper border of sample space */
    
    /* find the maximum value of the function in specific range */
    for (x = a; x <= b; x += 0.001){
        y_pre = get_function_value(x);
        y_next = get_function_value(x + 0.001);
            
        /* assign the larger value to y */
        if (y_pre <= y_next)
                y = y_next;
    }

    K = y * 2; /* define K as two times the maximum in certain range */
    return K;
}

/*
 *compute_Z(a, b, K, N) computes the integral value of a certain function
 *it returns the value of integral with different conditions
 *a and b are given from external input
 *K is defined by get_K and N is defined in the main function
 */
double compute_Z(double a, double b, double K, double N)
{
    int n = 0; /* initialize the counter */
    float Z; /* declare the value of integral */
    srand((unsigned)time(0)); /* make sure random numbers are different everytime */

    /* generate random numbers in the sample space */
    for (int i = 0; i <= N; i++){
        double x_rand = a + (b - a) * rand() * 1.0 / RAND_MAX ;
        double y_rand = K * rand() * 1.0 / RAND_MAX;
    
        /* compare the value of the function and that of random points */
        if (get_function_value(x_rand) > y_rand){
        n = n + 1; /* count the points whose value is larger than that of the function */
        }
    }
    /* calculate the value of the integral */
    Z = n * K * (b - a) / N;
    printf("The value of integral with N = %g:\n", N);
    printf("%.10f\n", Z);
    return Z;
}

/*
 *judge_function(a, b) analyzes whether there are undefined points involved in the integral
 *it returns a value the indicates whether the integral should be calculated
 *a and b are given from external input
 */
double test_integral(double a, double b)
{
    double x, y_prev, y_cur;
    /* initialize the variable for judging whether integral can be calculated */
    int active = 1; /* initialize the indicator */
    
    /* test if this integral involves undefined points */
    for(x = a; x <= b; x++){
        y_prev = get_function_value(x);
        y_cur = get_function_value(x - 0.001);
        
        /* test if there exists unexpected difference that indicates discontinuities */
        if((y_cur - y_prev) > 1000000000 || (y_cur - y_prev) < -1000000000){
            printf("We can't compute the integral, change the range or the function\n");
            return(active = 0);
            }
        }
    /* return a value for pass if the integral goes through the test */
    active = 3;
    return active;
}
