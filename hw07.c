#include<stdio.h>
#include<math.h>
#include"myrecur.c"
#include <gsl/gsl_integration.h>
#include"gsl_int.c"
#define NMAX 100
#include"timer.h"
#include"timer.c"
#include"adjust.c"

int main (void)
{
    double vals1[NMAX + 1];
    double vals2[NMAX + 1];
    double timea;
    double timea1;
    double timeb;
    double timeb1;
    double tmin = 1.;
    double tmax = 2.;
    int nmin = 0;
    int nmax = NMAX;
    int count = 1000;

    integral_recur (nmin, nmax, vals1);
    integral_gen (nmin, nmax, vals2);

    printf ("    n    Recurrence      GSL Integrator     ABSERROR*10^9  \n");

    for (int i = 0; i < 101; i++)
    {
        printf ("   %6d     %15.15f     %15.15f      %15.15f \n", i, vals1[i],
            vals2[i], fabs (0.000000001 * (vals1[i] - vals2[i])));
    }
    int j;

    printf ("\n\n Timing the Recurfunc\n\nTime/call (usec) Total TIme (sec)   Count\n");
  
    do
    {
        timer_start ();
        for (j = 0; j < count; j++)
        {
            integral_recur (nmin, nmax, vals1);
        }
        
        timea = timer_stop ();
        timea1 = timea / count;
        printf (" %10.2f usec     %10.6f sec    %10d\n", timea1 * 0.000001, timea, count);
        count = adjust_rep_count (count, timea, tmin, tmax);
     }
     while ((timea > tmax) || (timea < tmin));
  
     printf ("Time per recurance function call = %f usec \n", timea1 * 0.000001);
     printf ("\n\nTiming gsl integration func\n\nTime / call (usec) Total Time (sec)      Count\n");

     count = 1000;
     
     do
     {
         timer_start ();
         for (j = 0; j < count; j++)
         {
             integral_gen (nmin, nmax, vals2);
         }
         timeb = timer_stop ();
         timeb1 = timeb / count;
         printf (" %10.2f usec     %10.6f sec    %10d\n", timeb1 * 0.000001, timeb, count);
         count = adjust_rep_count (count, timeb1, tmin, tmax);   // Adjusts the count 
    }
    while ((timeb > tmax) || (timeb < tmin));
    
    printf ("TIme / gsl int call = %f usec \n", timeb1 * .000001);
    printf (" %10.6f      %10.6f\n\n", timeb1, timea1);
    printf (" Ratio of gsl int / recur formula = %f\n", timeb1 / timea1);
 
    return 0;
}























