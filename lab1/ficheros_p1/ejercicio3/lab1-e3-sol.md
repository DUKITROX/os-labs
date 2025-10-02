```c
while((opt = getopt(argc, argv, "hel:")) != -1) {
		switch(opt) {
		case 'h':
			usage();
			exit(0);
		case 'e':
			options.par_mode = EVEN;
			break;
		case 'l':
			options.lenght = atoi(optarg);
			break;
		default:
			exit(EXIT_FAILURE);
		}
	}
```
añadimos las nuevas opciones a procesar
```c
if (optind >= argc) {
    fprintf(stderr, "Invalid title\n");
    usage();
    exit(EXIT_FAILURE);
}
options.title = argv[optind];
```
en caso de que se haya indicado el titulo, se asignamos.