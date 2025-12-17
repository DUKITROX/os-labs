## strings1.c
### El código contiene un error. ¿Se manifiesta en compilación o en ejecución? ¿Por qué se produce? Soluciona el error comentando la(s) línea(s) afectadas. Vuelve a compilar y ejecutar.

El error es de ejecución (*undefined behavior*), pues hacemos uso de `msg` sin haberla inicializado antes.

### ¿En qué dirección está la letra 'B' de la cadena "Bonjour"? ¿Y la de la la letra 'j'?

- La letra `B` está en la dirección apuntada por `p`, 0x10055bf08.
- La letra `j` está en la dirección apuntada por `p` + 3, 0x10055bf0B.

### Tras la asignación p=msg2;, ¿cómo podemos recuperar la dirección de la cadena "Bonjour"?

No podemos pues se pierde. Para recuperarla la tendríamos que haber guardado antes en una variable auxiliar.

### ¿Por qué la longitud de las cadenas p y msg2 es 2 tras la línea 30? Se asignan 3 bytes a 'p' que modifican a ambos, pero luego la longitud es sólo 2.

Porque hemos ejecutado `p[2] = '\0';` que indica final de cadena. Además, como previamente guardamos en `p` la dirección apuntada por `str2`, los cambios se ven reflejados en ambas variables.

### ¿Por qué strlen() devuelve un valor diferente a sizeof()?
- `strlen()` devuelve la longitud de la cadena (la posición del caracter `\0`)
- `sizeof()` devuelve la tamaño en bytes de **todo** el array, no solo hasta `\0`.

## strings2.c
### El código de copy no funciona. ¿Por qué?

Lo unico que se está haciendo es asignar una variable que ha sido pasado por copia y que desaparecerá una vez nos salgamos de la función, luego no estamos haciendo nada.
```c
void copy(char* org, char* dst)
{
	dst = org;
}
```

### Usa ahora la función copy2() (descomenta la línea correspondiente). ¿Funciona la copia?

Sí funciona, pues recibimos `dst` como puntero de puntero, y actualizamos puntero apuntado por el primer puntero (un poco trabalenguas pero es así :-D)

### Propón una implementación correcta de la copia.

```c
void copy(char* org, char dst[])
{
	int i;
	for (i=0;i<=strlen(org);i++)
		dst[i] = org[i];
}
```
Lo único, como `*char dst` está guardado en *read-only* areas de la memoria, el parametro pasado como *destino*  debería ser de tipo `char dst[]` en vez de `*char dst`.


### ¿Qué hace la función mod()? ¿Por qué funciona?

Copia la cadea `org` en `dst` pero sin copiar el `\0` por lo que al imprimir `dst` se quedarán los valores no actualizados que habia de antes.

Funciona porque la cadena a modificar es de tipo `char str[]`.