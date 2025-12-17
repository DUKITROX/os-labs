#define LABEL_MAX_LEN 15

typedef struct { // por lo general "typedef" se usa para structs para evitar tener que escribir "struct SimpleRecord record" siempre, mirar linea 15
	int id;
	double value;
	char label[LABEL_MAX_LEN + 1];
} SimpleRecord;
