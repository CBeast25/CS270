// P1 Assignment
// Author: Carson Evans 
// Date:   1/22/2020
// Class:  CS270
// Email:  carsone@colostate.edu

// Include files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// example of a global array
double input[5];
double output[4];

void computeSphere(double radius, double *addressOfArea)
{
    *addressOfArea = (4.0 / 3.0) * 3.141593 * radius * radius * radius;
}

void computeCube(double side, double *addressOfArea)
{
    *addressOfArea = side * side * side;
}

void computeTetrahedron(double side, double *addressOfArea)
{
    *addressOfArea = 0.117851 * side * side * side;
}

void computeCylinder(double radius, double height, double *addressOfArea)
{
    *addressOfArea = 3.141593 * radius * radius * height;
}

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 6) {
        printf("usage: ./P1 <double> <double> <double> <double> <double>\n");
        return EXIT_FAILURE;
    }

    // Parse arguments
    input[0] = atof(argv[1]);
    input[1] = atof(argv[2]);
    input[2] = atof(argv[3]);
    input[3] = atof(argv[4]);
    input[4] = atof(argv[5]);

    // Call function
    computeSphere(input[0], &output[0]);
    computeCube(input[1], &output[1]);
    computeTetrahedron(input[2], &output[2]);
    computeCylinder(input[3], input[4], &output[3]);
    
    // Print results
    printf("SPHERE, radius = %.5f, volume = %.5f.\n", input[0], output[0]);
    printf("CUBE, side = %.5f, volume = %.5f.\n", input[1], output[1]);
    printf("TETRAHEDRON, side = %.5f, volume = %.5f.\n", input[2], output[2]);
    printf("CYLINDER, radius = %.5f, height = %.5f, volume = %.5f.\n", input[3], input[4], output[3]);

    // Return success
    return EXIT_SUCCESS;
}
