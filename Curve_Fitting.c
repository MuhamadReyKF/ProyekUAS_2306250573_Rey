#include <stdio.h>
#include <math.h>
#include <float.h>

// Data eksperimen (konsentrasi f dan laju pertumbuhan k)
#define N 6
double f[N] = {1, 2, 4, 6, 10, 20};   // Substrat (g/L)
double k[N] = {0.12, 0.19, 0.29, 0.36, 0.43, 0.48}; // Laju pertumbuhan (1/jam)

// Fungsi saturasi: k_model = kmax * f / (K + f)
double model(double kmax, double K, double f) {
    return kmax * f / (K + f);
}

// Hitung error kuadrat total untuk parameter tertentu
double calc_error(double kmax, double K) {
    double error = 0;
    for (int i = 0; i < N; i++) {
        double kfit = model(kmax, K, f[i]);
        error += pow(kfit - k[i], 2);
    }
    return error;
}

int main() {
    double best_kmax = 0, best_K = 0;
    double min_error = DBL_MAX;

    // Grid search
    for (double kmax = 0.4; kmax <= 0.6; kmax += 0.001) {
        for (double K = 2.0; K <= 10.0; K += 0.01) {
            double error = calc_error(kmax, K);
            if (error < min_error) {
                min_error = error;
                best_kmax = kmax;
                best_K = K;
            }
        }
    }

    printf("Hasil Curve Fitting Model Saturasi:\n");
    printf("kmax optimum = %.4f\n", best_kmax);
    printf("K optimum    = %.4f\n", best_K);
    printf("Error total  = %.6f\n\n", min_error);

    printf("Perbandingan Data Eksperimen dan Hasil Fitting:\n");
    printf(" f\tk_eksperimen\tk_fitting\n");
    for (int i = 0; i < N; i++) {
        double kfit = model(best_kmax, best_K, f[i]);
        printf("%4.1f\t%.3f\t\t%.3f\n", f[i], k[i], kfit);
    }

    return 0;
}
