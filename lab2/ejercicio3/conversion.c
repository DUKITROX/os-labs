/*
 * Converter between text and binary representations of SimpleRecord.
 * Accepts input/output mode flags (-i/-o with t|b) plus input and output
 * filenames (or - for stdin/stdout). Streams records from the input,
 * re-emitting them in the requested format.
 */
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

struct options process_arguments(int argc, char* argv[]){

	struct options options;
	options.infile=NULL;
	options.outfile=NULL;
	/* Default to text input and output. */
	options.input_mode=TEXT;
	options.output_mode=TEXT;

	int opt;
	while((opt = getopt(argc, argv, "hi:o:")) != -1) {
		switch(opt) {
		case 'h':
			fprintf(stderr, "Use: %s [-i t|b] [-o t|b] input_file output_file\n", argv[0]);
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
		fprintf(stderr, "input_file and output_file must be specified\n");
		exit(EXIT_FAILURE);
	}

	char* input_filename = argv[optind];
	char* output_filename = argv[optind + 1];

	//open input file
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

	//open output file
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

	struct options options = process_arguments(argc, argv);

	SimpleRecord record;
	int processed_records = 0;

	/* Loop until input parsing fails or EOF is hit. */
	while(++processed_records) {
		if(options.input_mode == TEXT) {
			if(fscanf(options.infile, "%d %lf %s", &record.id, &record.value, record.label) != 3) 
				break;	
		}else if(options.input_mode == BINARY){
			if(fread(&record, sizeof(SimpleRecord), 1, options.infile) != 1)
				break;
		}
		
		if(options.output_mode == TEXT) 
			fprintf(options.outfile, "%d %.2f %s\n", record.id, record.value, record.label);
		else if(options.output_mode == BINARY)
			fwrite(&record, sizeof(SimpleRecord), 1, options.outfile);

		++processed_records;
	}

	//close files if they were opened
	if(options.infile != stdin) 
		fclose(options.infile);
	if(options.outfile != stdout) 
		fclose(options.outfile);

	printf("Processed records: %d\n", processed_records);
	return 0;
}
/*
Some commands for testing stdio
./conversion -i t -o t - - < datos.txt 
./conversion -i b -o b - - < datos.bin 
./conversion -i t -o b - - < datos.txt > datos2.bin
./conversion -i b -o t - - < datos.bin > datos2.txt
*/
