## Parte C: Comparación y Análisis

### 1. Compara los tamaños de mis_datos.txt y mis_datos.bin. ¿Cuál es más grande o más pequeño? ¿A qué se debe la diferencia? (Considera cómo se almacenan los números y las cadenas en cada formato).

```bash
ls -lh data.txt data.bin 
-rw-r--r-- 1 501 dialout 96 Oct  3 13:18 data.bin
-rw-r--r-- 1 501 dialout 48 Oct  3 13:03 data.txt
```
Vemos que `data.txt` ocupa 48 bytes mientras que `data.bin` ocupa 96 bytes.
La diferencia se debe a que `data.txt` guarda los datos en formato texto, luego por ejemplo, para representar `1`, lo guarda como caracter por lo que usa solo 1 byte, mientras que `data.bin` guarda el binario de la representación en memoria de nuestros structs, es por esto que el mismo `1` de antes ahora se guarda como entero ocupando 4 bytes.

### 2. Describe lo que ocurre al intentar ver el fichero binario con cat. ¿Por qué no es legible?
```bash
cat data.bin 
?7@Primerofffff?G@Segundo??????(@Tercero
```
Al usar cat sobre un fichero binario, la terminal intenta interpretar los bytes como caracteres de texto, muchos de los cuales no corresponden a caracteres legibles, lo cual hace que se muestren caracteres invalidos como `?` o que no se muestre nada directamente, en lugar del contenido real.

### 3. Observando la salida de xxd o hexdump para mis_datos.bin, ¿puedes identificar aproximadamente dónde empieza y termina cada SimpleRecord? ¿Se parece la representación binaria a cómo se alinearían los campos de la struct en memoria?

```bash
cat datos.txt 
1 23.50 Primero
2 47.80 Segundo
3 12.30 Tercero

xxd datos.bin 
00000000: 0100 0000 0000 0000 0000 0000 0080 3740  ..............7@
00000010: 5072 696d 6572 6f00 0000 0000 0000 0000  Primero.........
00000020: 0200 0000 0000 0000 6666 6666 66e6 4740  ........fffff.G@
00000030: 5365 6775 6e64 6f00 0000 0000 0000 0000  Segundo.........
00000040: 0300 0000 0000 0000 9a99 9999 9999 2840  ..............(@
00000050: 5465 7263 6572 6f00 0000 0000 0000 0000  Tercero.........
```
Vemos que cada simple record ocupa dos filas, en la primera se almacena `id` (4 bytes), 4 bytes de padding para que `value` que es un `double` y ocupa 8 bytes empiece alineadamente, 8 bytes de `value`. Tras eso, en la segundo fila aparecen 16 bytes representando `label`, la cual habíamos definido con tamaño máximo de 16 caracteres en total.

### 4. Menciona brevemente una ventaja y una desventaja de usar el formato de texto y una ventaja y desventaja de usar el formato binario para almacenar estos datos estructurados.

**Texto:**

* **Ventaja:** Legible y fácil de editar.
* **Desventaja:** Más lento de procesar por programas.

**Binario:**

* **Ventaja:** Lectura/escritura rápida y consistente para tipos de datos fijos.
* **Desventaja:** No legible y, en algunos casos como al almacenar números pequeños, ocupa más espacio que texto.

### 5. Considera que se reaizara una modificación en la estructura SimpleRecord de tal forma que la etiqueta se representase como char* y su memoria se reservase dinámicamente con malloc, quedando la estructura como sigue:

```c
typedef struct {
    int id;                 // Identificador entero
    double value;       // Un valor de punto flotante
    char* label;        // Etiqueta de texto 
} SimpleRecord;
```

Responde a las siguientes preguntas asumiendo que se dispone de un array de estructuras de este tipo (en memoria) correctamente inicializado:

#### ¿Se podría escribir en un fichero binario el array de estructuras con una única llamada a fwrite() como en B.1? ¿Por qué? En caso negativo, propón un mecanismo para hacerlo correctamente, prestando especial atención a la representación de la cadena en disco.

Nom pues `char*` es un puntero, por lo que lo que estarías escribiendo en memoria sería realmente la dirección a la que apunta.

Un mecanismo correcto para escribir el array de estructuras en una sola llamada sería: primero estimas una cota superior para las longitudes que puedan tener los `labels` (maximo de los `strlen()+1` vale) tras lo cual te creas un array auxiliar en donde `label` esté definido como `char label[LABEL_MAX_LEN + 1];` como antes, tras lo cual procedes a compiar el array anterior en el auxiliar. Finalmente haces `fwrite` de este nuevo array auxiliar.

Si nos permitimos hacer varias llamadas a `fwrite` se nos simplifica la cosa, puesto que por cada `char* label` podemos simplemente llamar
```c
fwrite(label, sizeof(char), strlen(label), file)
```
#### ¿Asumiendo que hemos logrado escribir el citado array en binario en un fichero, podría leerse el array de golpe con una única llamada a fread() como en B.2? ¿Por qué? En caso negativo, propón un método para hacerlo correctamente.

No, pues como cada ´label´ tiene tamaño distinto, `fread` espera que todos los elementos a leer tengan el mismo tamaño (segundo argumento que recibe).

Como mecanismo alternativo, leer todo con 1 solo `fread` sería imposible, por lo que tendríamos que, por cada elemento del array, leer por un lado el `id` y `value`, y luego, leer caracter a caracter hasta que leamos `\0` tras lo cual sabremos que hemos acabado. Finalmente tocará ignorar cierto padding hasta estar en una dirección de memoria múltiplo de 4 (pues lo siguiente nos tocará leer un `int`).

## Parte D: Conversión de formatos binario y texto

