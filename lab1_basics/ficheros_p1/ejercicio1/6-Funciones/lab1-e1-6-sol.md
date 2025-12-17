## arg1.c

### ¿Por qué el valor de xc no se modifica tras la llamada a sumC? ¿Dónde se modifica esa información?

No se modifica pues `xc` se pasa por copia. La modificación se le hace a la copia la cual está guardada en la pila.

### Comenta las dos declaraciones adelantadas de sum() y sumC(). Compila de nuevo, ¿Qué ocurre?

Salta un error de compilación, pues estamos llamando a una función de manera previa a su definición.

## arg2.c
### ¿Por qué cambia el valor de y tras la llamada a sum()?

La función `sum` recibe un puntero hacia la dirección de `y`, y luego dentro de la función se cambian los datos apuntados por dicho puntero.

### ¿Por qué en ocasiones se usa el operador ‘.’ y en otras ‘->’ para acceder a los campos de una estructura?

El operador `.` se usa cuando accedes a los campos de una variable instancia de un `struct`.

El operador `->` se usa igual que el anterior con la diferencia de que ahora la variable es un puntero a la estructura guardada. En verdad hacer `->` es lo mismo que hacer `(*puntero).campo`.

### ¿Por qué el valor de zc pasa a ser incorrecto sin volver a usarlo en el código?

Porque la funciona `sumC` comete un error, devuelve la dirección de `r`, una variable local que reside en la pila. Al salir de `sumC` esa memoria es liberada y `zc` se convierte en un *dangling pointer*, apuntando a una ubicación no reservada.

### Corrije el código para evitar el error producido en zc

```C
struct _complex_ * sumC( struct _complex_* a,  struct _complex_* b)
{
	struct _complex_* r = (struct _complex_*)malloc(sizeof(struct _complex_));
	r->re = a->re + b->re;
	r->im = a->im + b->im;

	// We modify the first argument
	a->re = 12.5;
	a->im = 13.4;
	return r;
}
```
Lo único ahora tendríamos que tener cuidad para liberar luego la memoria cuando hayemos acabado.