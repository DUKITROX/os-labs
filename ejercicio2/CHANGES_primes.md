**Changes: primes copy.c → primes.c**

- **Argument Parsing (main)**
  - Fixed assignment-as-condition: `if (argc = 2)` → `if (argc == 2)`.
  - Corrected argument usage: `atoi(argv[2]);` → `n = atoi(argv[1]);`.
  - Effect: Properly accepts a single numeric argument for `n`.

- **Sum Accumulation**
  - Initialized accumulator: `int total;` → `int total = 0;`.
  - Fixed accumulation typo: `total =+ arr[i];` → `total += arr[i];`.
  - Effect: Accumulates correctly instead of overwriting.

- **Prime Generation Loop (compute_primes)**
  - Removed increment-only-on-prime.
  - Added unconditional increment each iteration: `x++;`.
  - Effect: Avoids infinite loop; checks all numbers.

- **Primality Check (is_prime)**
  - Treat `< 2` as non-prime: start with `if (x < 2)`.
  - Simplified divisor loop: `for (int i = 2; i < x; i++)`.
  - Effect: Correct logic for all `x >= 0` (simple, not optimized).

**Summary of Impact**
- Prevents hangs/infinite loops in prime generation.
- Corrects command-line parsing; avoids out-of-bounds.
- Ensures sum starts from a known value and accumulates properly.
- Makes primality testing logically correct across inputs.

