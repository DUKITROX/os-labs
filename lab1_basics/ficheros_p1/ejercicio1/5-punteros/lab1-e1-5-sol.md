## punteros1.c
### ¿Qué operador utilizamos para declarar una variable como un puntero a otro tipo?

`*`

### ¿Qué operador utilizamos para obtener la dirección de una variable?

`&`

### ¿Qué operador se utiliza para acceder al contenido de la dirección “a la que apunta” un puntero?

`*`

### Hay un error en el código. ¿Se produce en compilación o en ejecución? ¿Por qué se produce?

En ejecución. Estamos intentado acceder a zonas ilegales de memori.

## punteros2.c
### ¿Cuántos bytes se reservan en memoria con la llamada a malloc()?
Se reservan 4*127 = 508 bytes.
### ¿Cuál es la dirección del primer y último byte de dicha zona reservada?

- **primer byte**: 0x12d604890
- **ultimo byte**: dir_base + total_bytes - 1 = 0x12d604890+508−1 = 0x12d604a8b

### ¿Por qué el contenido de la dirección apuntada por ptr es 7 y no 5 en el primer printf()?

```c
	*ptr = 5;
	ptr[0] = 7;
	ptr2 = ptr;
    print(...)
```
porque el puntero a un array hace referencia a su primer elemento, el cual ha sido modificado con `ptr[0] = 7`.

### ¿Por qué se modfica el contenido de ptr[1] tras la sentencia *ptr2=15;?

Porque
1. `ptr2` apuntaba al mismo sitio que `ptr`
2. luego se incrementó en 1 (avanzo 4 bytes) por lo que ahora apunta a `ptr[1]`
3. mientras apuntaba a `ptr[1]` se hizo `*ptr2 = 15`

### Indica dos modos diferentes de escribir el valor 13 en la dirección correspondiente a ptr[100].

```c
ptr[100] = 13;
*(100 + ptr) = 13;
```

### Hay un error en el código. ¿Se manifiesta en compilación o en ejecución? Aunque no se manifieste, el error está. ¿Cuál es?

No se manifiesta en ninguno, pero efectivamente, hay un error!
```c
	free(ptr);
	*ptr = 3;
	printf("Address pointed by ptr %p. Memory content at that address: %d \n",
			ptr, *ptr);
```
Tras liberar la memoria reservada, `ptr` queda como *dangling pointer* por lo que luego estamos accediendo y modificando zonas de memoria que podrían ser o no ser ilegales, resultando en *undefined behavior*

## punteros3.c
### ¿Por qué cambia el valor de ptr[13] tras la asignación ptr = &c;?

Al ser `c` un entero, `ptr` deja de guardar la dirección de un array, por lo que `ptr[13]` simplemente a lo que sea que haya guardado **13*4 bytes** más adelante de `ptr`.

### El código tiene (al menos) un error. ¿Se manifiesta en compilación o en ejecución? ¿Por qué?

Se manifiesta en ejecución resultando de *undefined behavior* debdio a intentar liberar memoria estática que **no** se había reservado.

### ¿Qué ocurre con la zona reservada por malloc() tras a asignación ptr = &c;? ¿Cómo se puede acceder a ella? ¿Cómo se puede liberar dicha zona?

Perdemos acceso a esa zona de memoria y tenemos un *memory leak*. Ya no podemos acceder a ella. La forma de liberarla sería hacerlo antes de asignar `ptr = &c`. 