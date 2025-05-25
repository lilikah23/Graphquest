#include "extra.h"

#define MAX_LINE_LENGTH 4096
#define MAX_FIELDS      128

int int_cmp(void *a, void *b) {
    int *x = (int *)a;
    int *y = (int *)b;
    return (*x == *y);
}

char **leer_linea_csv(FILE *archivo, char separador) {
    static char linea[MAX_LINE_LENGTH];
    char **campos = malloc(sizeof(char *) * MAX_FIELDS);
    int idx = 0;

    if (fgets(linea, MAX_LINE_LENGTH, archivo) == NULL) {
        free(campos);
        return NULL;  // fin de archivo
    }

    linea[strcspn(linea, "\r\n")] = '\0';  // quitar salto de línea

    char *ptr = linea;
    while (*ptr && idx < MAX_FIELDS - 1) {
        char *start;
        char campo[MAX_LINE_LENGTH];

        if (*ptr == '\"') {
            ptr++;  // saltar comilla inicial
            char *dest = campo;

            while (*ptr) {
                if (*ptr == '\"' && *(ptr + 1) == '\"') {
                    *dest++ = '\"';  // comilla escapada
                    ptr += 2;
                } else if (*ptr == '\"') {
                    ptr++;  // fin de campo entrecomillado
                    break;
                } else {
                    *dest++ = *ptr++;
                }
            }
            *dest = '\0';
            if (*ptr == separador) ptr++;
        } else {
            char *dest = campo;
            while (*ptr && *ptr != separador) {
                *dest++ = *ptr++;
            }
            *dest = '\0';
            if (*ptr == separador) ptr++;
        }

        campos[idx++] = strdup(campo);  // duplicar contenido del campo
    }

    campos[idx] = NULL;
    return campos;
}


List *split_string(const char *str, const char *delim) {
  List *result = list_create();
  char *str_copy = strdup(str);  // crea copia modificable
  char *token = strtok(str_copy, delim);

  while (token != NULL) {
    while (*token == ' ') token++;  // eliminar espacios al inicio

    char *end = token + strlen(token) - 1;
    while (*end == ' ' && end > token) {
      *end = '\0';
      end--;
    }

    list_pushBack(result, strdup(token));  // duplicar token limpio
    token = strtok(NULL, delim);
  }

  free(str_copy);  // liberar copia
  return result;
}

List *split_dyn(const char *str, const char *delim) {
    List *result = list_create();
    char *str_copy = strdup(str);  // Crea una copia modificable de la cadena
    char *token = strtok(str_copy, delim);

    while (token != NULL) {
        list_pushBack(result, strdup(token));  // Duplicar el token y agregarlo a la lista
        token = strtok(NULL, delim);
    }

    free(str_copy);  // Liberar la copia de la cadena
    return result;
}

int split(const char *str, char **result, int max_fields, const char *delim) {
    int count = 0;
    char *str_copy = strdup(str);
    char *token = strtok(str_copy, delim);
    while (token && count < max_fields) {
        result[count++] = token;
        token = strtok(NULL, delim);
    }
    result[count] = NULL;
    // Si usas strdup, debes copiar los tokens, y liberar str_copy después de usarlos
    free(str_copy);
    return count;
}

// Función para limpiar la pantalla
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void presioneTeclaParaContinuar() {
  puts("Presione enter para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}