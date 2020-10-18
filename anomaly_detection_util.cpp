#include <math.h>
#include "anomaly_detection_util.h"

float avg(float* x, int size){
    float meanSum = 0.0;
    for(int i = 0; i < size; i++){
        meanSum += x[i];
    }
	return (meanSum / size);
}

// returns the variance of X and Y
float var(float* x, int size){
    float mean_pow = 0.0;
    for (int i = 0; i < size; i++){
        mean_pow += pow(x[i],2);
    }
    mean_pow = mean_pow / size;
    return mean_pow - pow(avg(x, size), 2);
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float covSum = 0.0;
    // condition if the array's size are matching
    while ((sizeof(x) / sizeof(*x)) == (sizeof(y) / sizeof(*y)))
    {
        for(int i = 0; i < size; i++){
        covSum += x[i] * y[i];
    }
    covSum = covSum / size;
	return covSum - (avg(x, size) * avg(y, size));
    }
	return 0;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    float cov_val = cov(x, y, size);
	return cov_val / (sqrt(var(x, size)) * sqrt(var(y, size)));
}

/**
// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){

	return Line(0,0);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	return 0;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	return 0;
}

**/


