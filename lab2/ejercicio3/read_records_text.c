#include<stdio.h>
#include "record.h"

int main(int argc, char* argv[]){
	if(argc!=2){
		fprintf(stderr, "Uso: %s <archivo_entrada>\n", argv[0]);
		return 1;
	}

	const char* input_filename = argv[1];
	FILE* file;
	// el fopen devuelve un puntero al inicio del archivo abierto
	if((file = fopen(input_filename, "r")) == NULL){ 
		perror("Error al abrir el archivo para escritura.");
		return 1;
	}

	SimpleRecord record;
	// podrias poner solo "f" pero como nos puede entrar un double, mejor poner un "long float"
	// ademas podrias comprobar tmbn while != EOF
	while(fscanf(file, "%d %lf %s", &record.id, &record.value, record.label)==3){  
		printf("ID: %d, Value %.2f, Label: %s\n", record.id, record.value, record.label);
	}

	fclose(file);
	printf("Registros leidos correctamente en %s.\n", input_filename);
	return 0;
}
