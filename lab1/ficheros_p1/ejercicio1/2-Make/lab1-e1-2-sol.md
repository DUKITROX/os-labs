### Examina el makefile, identifica las variables definidas, los objetivos (targets) y las regalas.

#### variables

`CC`: Compilador de C, establecido como `gcc`.

`CFLAGS`: Banderas o flags del compilador, establecidas como `-Wall -g` (habilita todas las advertencias y añade información de depuración).

`LIBS`: Bibliotecas a enlazar, establecidas como `-lm`(biblioteca matemática).

#### objetivos & reglas

- Regla `%.o: %.c`: compila archivos `.c` individuales a archivos objeto `.o`.
- Objetivo Principal `all`: construye el ejecutable final prueba enlazando los archivos objeto.
- Objetivo de Limpieza `clean` elimina los archivos generados (`*.o` y `prueba`).

### Ejecuta make en la linea de comandos y comprueba las ordenes que ejecuta para construir el proyecto.

Órdenes ejecutadas
```bash
gcc -Wall -g -c -o auxiliar.o auxiliar.c
gcc -Wall -g -c -o init.o init.c
gcc -Wall -g -o prueba auxiliar.o init.o -lm
```

### Marca el fichero aux.c como modificado ejecutando touch aux.c. Después ejecuta de nuevo make. ¿Qué diferencia hay con la primera vez que lo ejecutaste? ¿Por qué?

La diferencia es que ya no se vuelve a compilar `init.c` pues su última modificación es previa a su última compilación.
```bash
gcc -Wall -g -c -o auxiliar.o auxiliar.c
gcc -Wall -g -o prueba auxiliar.o init.o -lm
```

### Ejecuta la orden make clean. ¿Qué ha sucedido? Observa que el objetivo clean está marcado como phony en la directiva .PHONY: clean. ¿por qué? Para comprobarlo puedes comentar dicha línea del makefile, compilar de nuevo haciendo make, y después crear un fichero en el mismo directorio que se llame clean, usando el comando touch clean. Ejecuta ahora make clean, ¿qué pasa?

La orden elimina el ejecutable `prueba` y los archivos objeto `(*.o)`.

¿Por qué `.PHONY`?

Garantiza que la acción se ejecute siempre. Si se omite `.PHONY` y existe un archivo llamado clean, make asume que el objetivo ya está actualizado y no ejecuta la limpieza (el `rm`).

### Comenta la línea LIBS = -lm poniendo delante una almoadilla (#). Vuelve a construir el proyecto ejecutando make (haz un clean antes si es necesario). ¿Qué sucede? ¿Qué etapa es la que da problemas?

Salta un error, pues no hemos "linkeado" la librería matemática que el código de `auxiliar.c` usa.