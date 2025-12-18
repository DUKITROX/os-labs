/*
 * Writes an array of SimpleRecord structs to a binary file.
 * Accepts the output filename as the sole argument and dumps three sample
 * records with fwrite in a single call.
 */
#include<stdio.h>
#include "record.h"

int main(int argc, char* argv[]){
	if(argc!=2){
		fprintf(stderr, "Uso: %s <archivo_salida>\n", argv[0]);
		return 1;
	}

	SimpleRecord records[3] = {
		{1,23.5,"Primero"},
		{2,47.8,"Segundo"},
		{3,12.3,"Tercero"}
	};

	const char* output_filename = argv[1];
	FILE* file;
	if((file = fopen(output_filename, "w")) == NULL){ 
		perror("Error al abrir el archivo para escritura.");
		return 1;
	}

	/* Persist the entire array at once since the struct is POD. */
	fwrite(records, sizeof(SimpleRecord), sizeof(records)/sizeof(SimpleRecord), file);
	fclose(file);
	printf("Registros escritos correctamente en %s.\n", output_filename);
	return 0;
}
