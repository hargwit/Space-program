#ifndef GSLROUTINE_H
#define GSLROUTINE_H

//GSL libraries
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_matrix.h>

#include<cmath>
#include <fstream>
#include <iomanip>

int numBod;
bool flag=true;
std::ofstream out;
int width=30;

int func (double t, const double y[], double f[],void *params){
    (void)(t); /* avoid unused parameter warning */
    double* par = *(double **)params;
    double G=4*M_PI*M_PI;
    //Calculate sun component
    double rXSun=0;
    double rYSun=0;
    int j;  //position in array
    for(int i=0;i<numBod;i++){
        j=4*i;
        double mi=*(par+i);
        double ax = (G*mi*y[j]/pow(y[j]*y[j]+y[j+1]*y[j+1],1.5));
        double ay = (G*mi*y[j+1]/pow(y[j]*y[j]+y[j+1]*y[j+1],1.5));
        rXSun+=ax;
        rYSun+=ay;
    }

    //Define all other positions
    int l;
    for(int i=0;i<numBod;i++){
        j=4*i;
        f[j]=y[j+2]; //Rx
        f[j+1]=y[j+3];  //Ry
        f[j+2]=-G*y[j]/pow(y[j]*y[j]+y[j+1]*y[j+1],1.5)-rXSun;  //vx
        f[j+3]=-G*y[j+1]/pow(y[j]*y[j]+y[j+1]*y[j+1],1.5)-rYSun; //vy
        for(int k=0;k<numBod;k++){
            if(i!=k){
                double mk=*(par+k);
                l=4*k;
                f[j+2]+=-G*mk*(y[j]-y[l])/pow(pow(y[j]-y[l],2)+pow(y[j+1]-y[l+1],2),1.5);   //vx
                f[j+3]+=-G*mk*(y[j+1]-y[l+1])/pow(pow(y[j]-y[l],2)+pow(y[j+1]-y[l+1],2),1.5); //vy
            }
        }
    }

    return GSL_SUCCESS;
}

double* fourthOrderRK(size_t dim, double y[],double param[]){

    //Equates to 0.01 years calculation
    double datapoints = 1;
    int numSteps = 400;
    double h=0.000025;

    numBod=log(dim)/log(2.0)-1;
    //Error predicitions
    double epsrel = 7e-10;
    double epsabs = 7e-10;

    //Variable to store status of calculation
    int s;
    double t=0.0;
    //Set up gsl system with function and jacobian
    gsl_odeiv2_system sys = { func, 0, dim,&param};
    //Allocate a new driver for the step function
    //The driver acts as the user interface, starting and stopping integration.
    gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,h, epsabs, epsrel);

    for (int i = 0; i < datapoints; i++){
        //Perform step function for n steps
        s = gsl_odeiv2_driver_apply_fixed_step (d, &t, h, numSteps,y);
    }

    //Free up the memory taken by the driver.
    gsl_odeiv2_driver_free (d);
    return y;
}

double * adaptiveFourthOrderRK(size_t dim, double y[],double param[]){
    numBod=log(dim)/log(2.0)-1;

    //Set the step type to fourth order runge-kutta
    const gsl_odeiv2_step_type * T = gsl_odeiv2_step_rk4;
    //Allocate instance of stepping function
    gsl_odeiv2_step * s = gsl_odeiv2_step_alloc (T,dim);
    //Create a new control object
    gsl_odeiv2_control * c = gsl_odeiv2_control_y_new(1e-6,0.0);
    //Allocate instance of evolution function system
    gsl_odeiv2_evolve * e = gsl_odeiv2_evolve_alloc(dim);
    //Set up the system with the function and it's jacobian and the number of dimensions
    gsl_odeiv2_system sys = { func,0, dim,&param};

    //Set high and low
    double low=0.0,high=0.01;
    //Initialize first t value
    double t=low;
    //Set step size
    double h=0.000001;

    //Cacluate using adaptive 4th order RK from low to high
    while(t<high){

        //apply evolution function
        int status = gsl_odeiv2_evolve_apply (e, c, s,&sys,&t, high,&h, y);
        //Check status
        if (status != GSL_SUCCESS){
            break;
        }

    }

    //Free memory taken by gsl components
    gsl_odeiv2_evolve_free (e);
    gsl_odeiv2_control_free (c);
    gsl_odeiv2_step_free (s);
    return y;
}


#endif // GSLROUTINE_H

