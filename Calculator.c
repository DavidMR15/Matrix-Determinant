#include <stdio.h>
#include <stdlib.h>
// Definición de la estructura para almacenar la matriz y su determinante
struct MatrizDeterminante {
  float **matriz;
  float determinante;
  int tamano;
};
// Función para imprimir la matriz
void imprimirMatriz(float **matriz, int n, int refe) {
  printf("La matriz ingresada numero %d es:\n", refe);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%.2f\t", matriz[i][j]);
    }
    printf("\n");
  }
}

// Función recursiva para calcular el determinante por cofactores
float calcularDeterminante(float **matriz, int n);
// Función recursiva para calcular el determinante por cofactores
float calcularDeterminante(float **matriz, int n) {
  if (n == 1) {
    return matriz[0][0];
  } else if (n == 2) {
    // Caso base: matriz 2x2
    float determinante =
        (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
    return determinante;
  } else {
    // Caso general: matriz de orden mayor a 2
    float resultado = 0;

    for (int k = 0; k < n; k++) {
      // Crear la submatriz
      float *submatriz = (float *)malloc((n - 1) * sizeof(float *));
      for (int i = 0; i < n - 1; i++) {
        submatriz[i] = (float *)malloc((n - 1) * sizeof(float));
      }

      // Llenar la submatriz excluyendo la fila y columna correspondientes
      for (int i = 1; i < n; i++) {
        for (int j = 0, l = 0; j < n; j++) {
          if (j != k) {
            submatriz[i - 1][l++] = matriz[i][j];
          }
        }
      }

      // Calcular cofactor y acumular al resultado
      resultado += ((k % 2 == 0) ? 1 : -1) * matriz[0][k] *
                   calcularDeterminante(submatriz, n - 1);
      // Liberar la memoria asignada para la submatriz
      for (int i = 0; i < n - 1; i++) {
        free(submatriz[i]);
      }
      free(submatriz);
    }

    return resultado;
  }
}
int main() {
  int n;
  int numMatrices;
  printf("¿Cuántas matrices deseas ingresar?: ");
  scanf("%d", &numMatrices);
  // Array de estructuras para almacenar las matrices y sus determinantes
  struct MatrizDeterminante *matricesDeterminantes =
      (struct MatrizDeterminante *)malloc(numMatrices *
                                          sizeof(struct MatrizDeterminante));
  system("clear");
  for (int repeticion = 0; repeticion < numMatrices; repeticion++) {
    printf("Ingresa el tamaño de la matriz cuadrada numero %d: ",
           repeticion + 1);
    scanf("%d", &n);
    matricesDeterminantes[repeticion].tamano = n;
    system("clear");
    // Crear la matriz
    matricesDeterminantes[repeticion].matriz =
        (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
      matricesDeterminantes[repeticion].matriz[i] =
          (float *)malloc(n * sizeof(float));
    }
    if (matricesDeterminantes[repeticion].tamano > 0) {
      printf("Ingresa los elementos de la matriz:\n");
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          printf("Ingresa el elemento en la fila %d y columna %d: ", i + 1,
                 j + 1);
          scanf("%f", &matricesDeterminantes[repeticion].matriz[i][j]);
          system("clear");
        }
      }
    }
    matricesDeterminantes[repeticion].determinante =
        calcularDeterminante(matricesDeterminantes[repeticion].matriz, n);
  }
  // Imprimir la matriz ingresada
  for (int repeticion = 0; repeticion < numMatrices; repeticion++) {
    if (matricesDeterminantes[repeticion].tamano > 0) {
      imprimirMatriz(matricesDeterminantes[repeticion].matriz,
                     matricesDeterminantes[repeticion].tamano, repeticion + 1);
      printf("\nel determiante de la matriz es:%f\n\n",
             matricesDeterminantes[repeticion].determinante);
    } else {
      printf("\nLa matriz numero %d es Erronea\n\n", repeticion + 1);
    }
  }
  for (int k = 0; k < numMatrices; k++) {
    for (int i = 0; i < numMatrices; i++) {
      free(matricesDeterminantes[k].matriz[i]);
    }
    free(matricesDeterminantes[k].matriz);
  }
  free(matricesDeterminantes);
  return 0;
}
