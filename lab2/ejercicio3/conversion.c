#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "record.h"

typedef enum {
	TEXT,
	BINARY
} io_mode_t;

struct options{
	FILE* infile;
	FILE* outfile;
	io_mode_t input_mode;
	io_mode_t output_mode;
};

struct options process_options(int argc, char* argv[]){
	if(argc<3){
		fprintf(stderr, "Uso: %s [-i t|b] [-o t|b] fichero_entrada fichero_salida\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	struct options options;
	options.infile=NULL;
	options.outfile=NULL;
	options.input_mode=TEXT;
	options.output_mode=TEXT;

	int opt;
	while((opt = getopt(argc, argv, "hi:o:")) != -1) {
		switch(opt) {
		case 'h':
			fprintf(stderr, "Uso: %s [-i t|b] [-o t|b] fichero_entrada fichero_salida\n", argv[0]);
			exit(0);
		case 'i':
			if(strcmp(optarg, "t") == 0){
				options.input_mode=TEXT;
			}else if(strcmp(optarg, "b") == 0){
				options.input_mode=BINARY;
			}else{
				fprintf(stderr, "Invalid option %s for [-i t|b]\n", optarg);
				exit(EXIT_FAILURE);
			}
			break;
		case 'o':
			if(strcmp(optarg, "t") == 0){
				options.output_mode=TEXT;
			}else if(strcmp(optarg, "b") == 0){
				options.output_mode=BINARY;
			}else{
				fprintf(stderr, "Invalid option %s for [-o t|b]\n", optarg);
				exit(EXIT_FAILURE);
			}
			break;
		default:
			exit(EXIT_FAILURE);
		}
	}

	if(argc - optind < 2) {
		fprintf(stderr, "Debe especificar fichero_entrada y fichero_salida\n");
		exit(EXIT_FAILURE);
	}

	char* input_filename = argv[optind];
	char* output_filename = argv[optind + 1];

	if(strcmp(input_filename, "-") == 0) {
		options.infile = stdin;
	} else {
		if(options.input_mode == TEXT) {
			options.infile = fopen(input_filename, "r");
		} else {
			options.infile = fopen(input_filename, "rb");
		}
		if(options.infile == NULL) {
			fprintf(stderr, "The input file %s could not be opened: ", input_filename);
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}

	if(strcmp(output_filename, "-") == 0) {
		options.outfile = stdout;
	} else {
		if(options.output_mode == TEXT) {
			options.outfile = fopen(output_filename, "w");
		} else {
			options.outfile = fopen(output_filename, "wb");
		}
		if(options.outfile == NULL) {
			fprintf(stderr, "The output file %s could not be opened: ", output_filename);
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}

	return options;
}

int main(int argc, char* argv[]){

	struct options options = process_options(argc, argv);

	SimpleRecord record;
	int records_processed = 0;

	while(1) {
		if(options.input_mode == TEXT) {
			if(fscanf(options.infile, "%d %lf %s", &record.id, &record.value, record.label) != 3) break;	
		}else if(options.input_mode == BINARY){
			if(fread(&record, sizeof(SimpleRecord), 1, options.infile) != 1) break;
		}
		
		if(options.output_mode == TEXT) 
			fprintf(options.outfile, "%d %.2f %s\n", record.id, record.value, record.label);
		else if(options.output_mode == BINARY)
			fwrite(&record, sizeof(SimpleRecord), 1, options.outfile);

		++records_processed;
	}

	if(options.infile != stdin) 
		fclose(options.infile);
	if(options.outfile != stdout) 
		fclose(options.outfile);

	printf("Registros procesados: %d\n", records_processed);
	return 0;
}
/*
Algunos comandos para testear entrada y salida estandar:
./conversion -i t -o t - - < datos.txt 
./conversion -i b -o b - - < datos.bin 
./conversion -i t -o b - - < datos.txt > datos2.bin
./conversion -i b -o t - - < datos.bin > datos2.txt
*/