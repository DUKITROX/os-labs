## main1.c

### ¿Por qué el primer printf() imprime valores distintos para ‘a’ con los modificadores %d y %c?

```c
printf("a = %d a = %c \n", a, a);
```
Porque en el primer caso `a` se interpreta como número y en el segundo como `char`.

### ¿Cuánto ocupa un tipo de datos char?
1 byte

### ¿Por qué el valor de ‘a’ cambia tanto al incrementarlo en 6? (la respuesta está relacionada con la cuestión anterior)

Al ser de tipo char y aumentarlo en 6, el carácter que representa es el correspondiente a 6 entradas más abajo que el suyo previo en la tabla ascii, es por esto que da la impresión de cambiar mucho.

### Si un “long” y un “double” ocupan lo mismo, ¿por qué hay 2 tipos de datos diferentes?

Ocupan lo mismo pero lo que representan tiene formatos distintos. Un `long` se representa en complemento a 2, mientras que un `double` se representa dividiendo sus bits en signo, base, exponente y mantisa.

## main2.c

### ¿Tenemos un problema de compilación o de ejecución?

De compilación.

### ¿Por qué se da el problema?. Soluciónalo, compila y ejecuta de nuevo.


```
main2.c:13:5: error: variable length array declaration not allowed at file scope                                                      
int array2[a];  
```
Al crear arrays **globales**, su tamaño ha de ser constante y conocido en tiempo de compilación.
Para solucionarlo simplemente creamos una constante con el valor que le queríamos poner.
```c
#define A 7
int array2[A];
```

### ¿Qué significa el modificar "%lu" en printf()?

`unsigned long`

### ¿A qué dirección apunta "pc"? ¿Coincide con la de alguna variable anteriormente declarada? Si es así, ¿Coinciden los tamaños de ambas?

`pc` apunta a 0x100bb808 que coincide con la dirección de `x`.
Los tamaños de ambas no coinciden pues `x` es un caracter (tamaño 1 byte) `pc` es un puntero (tamaño 8).

### ¿Coincide el valor del tamaño de array1 con el número de elementos del array? ¿Por qué?

No, pues los elementos de `array` son enteros (ocupan 4 bytes), por lo que el tamaño total es distinto al número de elementos.

### ¿Coinciden las direcciones a la que apunta str1 con la de str2?

No. A pesar de representar el mismo string, se guardan es sitios distintos de memoria.

### ¿Por qué los tamaños (según sizeof()) de str1 y str2 son diferentes?

Porque `char* str1` es un puntero luego su tamaño son 8 bytes, mientras que `char str2[]` es un array de caractéres luego su tamaño, es el tamaño total del araray, en este caso 21 (contamos caracter final `\O`).