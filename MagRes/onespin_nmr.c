// onespin_nmr.c
// 
// Description:
// This plots the spectrum of a single spin-1/2 particle in an NMR experiment.
// Starting from an initial density matrix, it applies a RF pulse and free evolution periods, then 
// computes and outputs the resulting NMR spectrum. Apodization and Fourier transformation are performed 
// to simulate the observed signal. Plotted using GNUplot. Data is saved to a file "onespin_nmr.dat".
//
// Inputs: 
// - rho_initial        : initial density matrix (2x2 complex matrix)
// - dt                 : time step for evolution (in seconds)
// - N                  : number of time points
// - apodization_factor : factor for exponential apodization
// - freq_offset        : frequency offset for free evolution (in Hz)
// - lb                 : line broadening factor (in Hz), used for apodization
//
// Outputs:
// - FID        : Free Induction Decay signal (complex array of length N)
// - spectrum   : NMR spectrum (complex array of length N)
// - Data file "onespin_nmr_fid.dat" containing time and FID values
// - Data file "onespin_nmr_spectrum.dat" containing frequency and spectrum values
// - GNUplot plot of the NMR spectrum (.pdf file)
// 
// Dependencies: 
// - Standard C libraries for complex numbers and file I/O
// - GNUplot for plotting the spectrum
//
// Usage:
// - Compilation: gcc -o onespin_nmr onespin_nmr.c -lm
// - Execution: ./onespin_nmr
//
// Notes:
// - This code uses C11 standard for complex number support. 
// - GNUplot needs to be installed for plotting the spectrum.
// - An handy function tracks elapsed time for performance measurement.
// - Used editor: Visual Studio Code
// 
// Author: Lorenzo Niccoli 

#include <stdio.h>
#include <complex.h>
#include <time.h>

// Pauli Matrices Initialization
void init_pauli(double complex Ix[2][2], double complex Iy[2][2], double complex Iz[2][2]) 
{
    Ix[0][0] = 0.0 + 0.0*I;  Ix[0][1] = 0.5 + 0.0*I;
    Ix[1][0] = 0.5 + 0.0*I;  Ix[1][1] = 0.0 + 0.0*I;

    Iy[0][0] = 0.0 + 0.0*I;  Iy[0][1] = 0.0 - 0.5*I;
    Iy[1][0] = 0.0 + 0.5*I;  Iy[1][1] = 0.0 + 0.0*I;

    Iz[0][0] = 0.5 + 0.0*I;  Iz[0][1] = 0.0 + 0.0*I;
    Iz[1][0] = 0.0 + 0.0*I;  Iz[1][1] = -0.5 + 0.0*I;
}

// Matrix multiplication for 2x2 matrices
void mat2_mult(double complex A[2][2], double complex B[2][2], double complex C[2][2])
{
    C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
    C[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1];
    C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
    C[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1];
}

// (Main function)      Transpose conjugate of 2x2 matrix
void mat2_conj_transpose(double complex A[2][2], double complex B[2][2]) 
{
    B[0][0] = conj(A[0][0]);
    B[0][1] = conj(A[1][0]);
    B[1][0] = conj(A[0][1]);
    B[1][1] = conj(A[1][1]);
}

// (helper function)    Print matix 
void print_matrix(double complex M[2][2], const char* name) 
{
    printf("%s = [\n", name);
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            printf(" (%6.3f,%6.3f)", creal(M[i][j]), cimag(M[i][j]));
        }
        printf("\n");
    }
    printf("]\n");
}

// (helper function)    Function to print status messages with elapsed time 
void print_status(const char* status_mgs, char* message) 
{
    static struct timespec start;
    static int first_call = 1;
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    // Initialize start time on first call
    if (first_call) { start = now; first_call = 0;}

    // Calculate elapsed time
    double elapsed_total = (now.tv_sec - start.tv_sec) +
                           (now.tv_nsec - start.tv_nsec) * 1e-9;

    // Print status message
    printf("%-15s:  %-30s %2.6f s\n", status_mgs, message, elapsed_total);
}

// Main function 
int main() {
    // Parameters 
    double complex Ix[2][2], Iy[2][2], Iz[2][2];
    double complex C[2][2], Ct[2][2];
    double complex rho[2][2];
    double complex U[2][2];
    double complex U_dag[2][2];
    double complex rho_final[2][2];
    double dt = 0.001; 
    int N = 1024;   
    double complex FID[1024];
    double complex spectrum[1024];
    double apodization_factor = 0.1;
    double freq_offset = 100.0; 
    double elapsed, elapsed_total;

    // Write Pauli matrices
    init_pauli(Ix, Iy, Iz);

    // Status message
    print_status("Inform user", "Starting simulation"); 

    // Status message
    print_status("Saving data", "data_onespin_nmr_fid.dat"); 

    // Calculate time taken for the simulation
    
    // Status message
    print_status("Saving data", "data_onespin_nmr_spectrum.dat"); 

    // Status message
    print_status("Inform user", "Simulation completed");

    // End of program
    return 0;

}
