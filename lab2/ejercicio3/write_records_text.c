/*
 * Writes SimpleRecord structs to a plain-text file, one record per line.
 * Takes the output filename as an argument and formats a small static
 * array of sample data using fprintf.
 */
#include <stdio.h>
#include "record.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo_salida>\n", argv[0]);
        return 1;
    }

    SimpleRecord records[3] = {
        {1, 23.5, "Primero"},
        {2, 47.8, "Segundo"},
        {3, 12.3, "Tercero"}
    };

    const char* output_filename = argv[1];
    FILE* file;
    // el fopen devuelve un puntero al inicio del archivo abierto
    if ((file = fopen(output_filename, "w")) == NULL) {
        perror("Error al abrir el archivo para escritura.");
        return 1;
    }
    // Print every struct field in human-readable text
    for (int i = 0; i < (int)(sizeof(records) / sizeof(records[0])); i++) {
        // primer arg es en dnd escribes
        fprintf(file, "%d %.2f %s\n", records[i].id, records[i].value, records[i].label);
    }

    fclose(file);
    printf("Registros escritos correctamente en %s.\n", output_filename);
    return 0;
}
