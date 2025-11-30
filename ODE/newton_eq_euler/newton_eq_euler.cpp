/*****************************************************
 * Description:
 *   Solves Newton's law of cooling using Euler method
 *   and generates a CSV file and PDF plot.
 *
 * Units:
 *   Temperature            : [°C]
 *   Time                   : [s]
 *   Cooling coefficient k  : [1/s]
 *
 * Files generated:
 *   - data_newton_euler.csv
 *   - plot_newton_cooling.pdf
 *
 * Notes:
 *   - PDF uses Latin Modern font (LaTeX style)
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>

int main() {

    double T = 100.0;
    double T_env = 25.0;
    double k = 0.007;
    double dt = 1;
    double t_final = 1200.0;

    // Save data to CSV
    FILE *f = fopen("newton_euler.csv", "w");

    // Check file opening
    if (!f) { perror("Error opening CSV"); return 1;}

    // Euler method loop
    for (double t = 0; t <= t_final; t += dt) {
        fprintf(f, "%f %f\n", t, T);
        T = T + dt * (-k * (T - T_env));  
    }

    // Close CSV file
    fclose(f);


// Plot 
    FILE *gp = popen("gnuplot", "w");
    if (!gp) {perror("Error opening gnuplot"); return 1;}

    // Plot (dynamic padding 10%)
    fprintf(gp,
            "set terminal pdfcairo enhanced color font 'Latin Modern Roman,14'\n"
            "set output 'newton_cooling.pdf'\n"
            "set xlabel 'Time (s)'\n"
            "set ylabel 'Temperature (°C)'\n"
            "set grid lw 1 lc rgb '#cc'\n" 
            "stats 'newton_euler.csv' using 1 name 'X' nooutput\n"
            "stats 'newton_euler.csv' using 2 name 'Y' nooutput\n"
            "xpad = (X_max - X_min) * 0.10\n"   
            "ypad = (Y_max - Y_min) * 0.10\n"
            "set xrange [X_min - xpad : X_max + xpad]\n"
            "set yrange [Y_min - ypad : Y_max + ypad]\n"
            "plot 'newton_euler.csv' using 1:2 with lines lw 2 title 'Euler'\n"
    );

    // Close gnuplot
    pclose(gp);

    // Notify user
    printf("Plot saved.\n");

    // End program
    return 0;
}
