**Cambios: primes copy.c → primes.c**

- **Análisis de argumentos (main)**
  - Corregido el error de asignación en condición: `if (argc = 2)` → `if (argc == 2)`.
  - Corregido el uso del argumento: `atoi(argv[2]);` → `n = atoi(argv[1]);`.
  - Efecto: Acepta correctamente un único argumento numérico para `n`.

- **Acumulación de suma**
  - Inicializado el acumulador: `int total;` → `int total = 0;`.
  - Corregido el typo en la acumulación: `total =+ arr[i];` → `total += arr[i];`.
  - Efecto: La suma se acumula correctamente en lugar de sobrescribirse.

- **Bucle de generación de primos (compute_primes)**
  - Eliminado el incremento solo cuando es primo.
  - Añadido incremento incondicional en cada iteración: `x++;`.
  - Efecto: Evita bucles infinitos y comprueba todos los números.

- **Comprobación de primalidad (is_prime)**
  - Considerar `< 2` como no primo: empezar con `if (x < 2)`.
  - Simplificado el bucle de divisores: `for (int i = 2; i < x; i++)`.
  - Efecto: Lógica correcta para todos los `x >= 0` (simple, no optimizada).

**Resumen del impacto**
- Evita cuelgues/bucles infinitos en la generación de primos.
- Corrige el análisis de argumentos y evita accesos fuera de rango.
- Asegura que la suma parte de un valor conocido y se acumula bien.
- Hace la prueba de primalidad lógicamente correcta para todas las entradas.

