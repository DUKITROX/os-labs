### Compila el código del ejercicio y ejecútalo

Obtenemos
```c
Hello world 	 a= 7 b= 9
Hello world 	 a= 8 b= 9
Hello world 	 a= 9 b= 9
Hello world 	 a= 9 b= 9
Hello world 	 a= 9 b= 9
```

### Obtén la salida de la etapa de pre-procesado (opción -E o la opción --save-temps para obtener la salida de todas las etapas intermedias) y en un fichero hello2.i

Ejecutamos 
```bash
gcc -E hello2.c > hello2.i
```

### ¿Qué ha ocurrido con la “llamada a min()” en hello2.i?

Ha sido directamente sustituida por `( (a<b)?a:b )`, el valor que tenía en el `#define` sustituyendo parámetros.

### ¿Qué efecto ha tenido la directiva #include <stdio.h>?

Ha incorporado al fichero `.i` todo lo presente dentro de `stdio.h`.