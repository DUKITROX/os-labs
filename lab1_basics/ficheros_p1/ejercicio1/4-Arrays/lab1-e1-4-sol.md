## array1.c

### ¿Por qué no es necesario escribir "&list" para obtener la dirección del array list?

Por defecto, C procesa `list[i]` como `*(list + i)` luego `list` ya de por sí es algo así como un puntero a la primera posición del array, por lo que no tiene sentido acceder a el con `&list`.

### ¿Qué hay almacenado en la dirección de list?

`list[0]`

### ¿Por qué es necesario pasar como argumento el tamaño del array en la función init_array?

Al pasar `int array[]` es lo mismo que pasar un puntero a la primera posición del array, es por esto que no se puede inferir el tamaño de este y hace falta pasárselo como parámetro.

### ¿Por qué el tamaño devuelto por sizeof() para el array de la función init_array no coincide con el declarado en main()?

Porque si recordamos `array` es realmente un puntero a su primer elemento, luego `sizeof(array)` devuelve el tamaño de dicho puntero, 8.

### ¿Por qué NO es necesario pasar como argumento el tamaño del array en la función init_array2?

Porque array tiene la *indicación* de que tiene tamaño `N` y esta al ser una constante global, podemos acceder a ella dentro de la función.

### ¿Coincide el tamaño devuelto por sizeof() para el array de la función init_array2 con el declarado en main()?

No, pues en el main, `list` ya sabe su tamaño, pero dentro de la función `init_array2` lo que se pasa realmente es un puntero al primero elemento del array, no todo el array.

## array2.c

### ¿La copia del array se realiza correctamente? ¿Por qué?

No, pues en
```c
void copyArray(int src[],int dst[],int size)
{
 	dst = src;
}
```
el paso de parámetros en C es siempre por copia, y de los arrays se pasan sus punteros por copia, luego lo único que hace la función es modificar el valor de `dst` que al ser una copia del puntero, desaparecerá al salir de la función.

### Si no es correcto, escribe un código que sí realice la copia correctamente.

```c
void copyArray(int src[],int dst[],int size)
{
	int i;
	for(i=0;i<size;i++)
		dst[i]=src[i];
}
```