/*****************************************************
 * Description:
 *   Solves Newton's law of cooling using Euler method
 *   and generates a CSV file and PDF plot. It compares
 *   different dt values in order show the errors 
 *   involved in the Euler method.
 *
 * Units:
 *   Temperature            : [°C]
 *   Time                   : [s]
 *   Cooling coefficient k  : [1/s]
 *
 * Files generated:
 *   - data_newton_euler_dt_errors.csv
 *   - plot_newton_cooling_dt_errors.pdf
 *
 * Notes:
 *   
 *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    double T0 = 100.0;
    double T_env = 25.0;
    double k = 0.007;
    double dt_values[] = {1, 25, 50, 75, 100, 125, 150};
    int n_dt = sizeof(dt_values) / sizeof(dt_values[0]);
    double t_final = 1200.0;

    // For each dt value, save data to a separate CSV
    for (int i = 0; i < n_dt; ++i) {
        double dt = dt_values[i];
        char filename[256];
        snprintf(filename, sizeof(filename), "newton_euler_dt_%g.csv", dt);

        FILE *f = fopen(filename, "w");

        // Check file opening
        if (!f) { perror("Error opening CSV"); return 1;}

        double T = T0;
        // Euler method loop
        for (double t = 0; t <= t_final; t += dt) {
            fprintf(f, "%f %f\n", t, T);
            T = T + dt * (-k * (T - T_env));
        }

        // Close CSV file for this dt
        fclose(f);
    }

    // Build list of existing CSV paths for the dt values
    char paths[16][256];
    int found_count = 0;

    for (int i = 0; i < n_dt; ++i) {
        char candidate[256];
        snprintf(candidate, sizeof(candidate), "newton_euler_dt_%g.csv", dt_values[i]);
        FILE *f = fopen(candidate, "r");
        if (f) {
            fclose(f);
            strncpy(paths[found_count], candidate, sizeof(paths[0]));
            paths[found_count][sizeof(paths[0]) - 1] = '\0';
            ++found_count;
        }
    }

    // Control: check if the files were found 
    if (found_count == 0) {
        fprintf(stderr, "No CSV files found for plotting.\n");
        return 1;
    }

    // Plotting with gnuplot
    FILE *gp = popen("gnuplot", "w");
    if (!gp) {perror("Error opening gnuplot"); return 1;}

     fprintf(gp,
            "set terminal pdfcairo enhanced color font 'Latin Modern Roman,14'\n"
            "set output 'newton_cooling_error_dt.pdf'\n"
            "set title 'Newton Law of Cooling: Euler Method with Different dt Values'\n"
            "set xlabel 'Time (s)'\n"
            "set ylabel 'Temperature (°C)'\n"
            "set grid lw 1 lc rgb '#cc'\n"
    );

    // Use the first found file to set ranges
    fprintf(gp, "stats '%s' using 1 name 'X' nooutput\n", paths[0]);
    fprintf(gp, "stats '%s' using 2 name 'Y' nooutput\n", paths[0]);
    fprintf(gp, "xpad = (X_max - X_min) * 0.10\n");
    fprintf(gp, "ypad = (Y_max - Y_min) * 0.10\n");
    fprintf(gp, "set xrange [X_min - xpad : X_max + xpad]\n");
    fprintf(gp, "set yrange [Y_min - ypad : Y_max + ypad]\n");

    // Plot all found CSVs overlayed
    fprintf(gp, "plot ");
    for (int i = 0; i < found_count; ++i) {
        const char *base = strrchr(paths[i], '/');
        base = base ? base + 1 : paths[i];
        char label[64] = {0};
        const char *u = strrchr(base, '_');
        if (u) {
            snprintf(label, sizeof(label), "%s", u + 1);
        } else {
            snprintf(label, sizeof(label), "%d", i);
        }
        char *dot = strchr(label, '.'); if (dot) *dot = '\0';
        fprintf(gp, "'%s' using 1:2 with lines lw 2 title 'dt=%s'%s", paths[i], label, (i == found_count - 1) ? "\n" : ", ");
    }

    // Close gnuplot
    pclose(gp);

    // End program
    return 0;
}
