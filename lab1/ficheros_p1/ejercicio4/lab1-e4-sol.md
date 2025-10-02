__Para representar cada una de las entradas del fichero /etc/passwd se emplea el tipo de datos passwd_entry_t (estructura definida en defs.h). Nótese que muchos de los campos almacenan cadenas de caracteres definidas como arrays de caracteres de longitud máxima prefijada, o mediante el tipo de datos char*. La función parse_passwd(), definida en show-passwd.c es la encargada de inicializar los distintos campos de la estructura. ¿Cuál es el propósito de la función clone_string() que se usa para inicializar algunos de los citados campos tipo cadena? ¿Por qué no es posible en algunos casos simplemente copiar la cadena vía strcpy() o realizando una asignación campo=cadena_existente;? Justifique la respuesta.__

La función `clone_string()` se usa para copiar el _token_ leído del fichero `/etc/passwd` con `strstep()` al _struct_ de tipo `passwd_entry` en lo que lo almacenamos, ubicado en memoria.

Hay destinos que requieren asignación de espacio dinámicamente, pues el tipo `char *` no sabe qué tan largo será. Para poder copiar una cadena a un puntero `char *`, primero se debe asignar memoria (usando `malloc`) a ese puntero. Una vez asignada, `strcpy()` se puede usar para copiar los datos. `clone_string()` te junta ambas operaciones en el mismo sitio.

Si se hiciera una simple asignación de puntero `cur_entry->user_name = token;`, el campo de la estructura `cur_entry->user_name` apuntaría directamente a la memoria dentro del buffer `line` (a través del puntero token), la cual al acabar la función, dejaría de ser válido. Además se usaría la misma memoria para múltiples entradas...

__La función strsep(), utilizada en parse_passwd(), modifica la cadena que se desea dividir en tokens. ¿Qué tipo de modificaciones sufre la cadena (variable line) tras invocaciones sucesivas de strsep()? Pista: Consúltese el valor y las direcciones de las variables del programa usando el depurador.__

La cadena `line` sufre dos modificaciones:

1. Reemplazo de Delimitador: `strsep()` reemplaza cada delimitador (el carácter `:`) con un carácter nulo (`\0`).

1. Avance del Puntero: El puntero de inicio (`lineptr`) se actualiza para apuntar al carácter inmediatamente posterior al `\0` recién insertado, consumiendo progresivamente la cadena.

Esto efectivamente convierte la cadena original en una serie de subcadenas terminadas en nulo dentro del mismo buffer.