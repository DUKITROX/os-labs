#include <semaphore.h>

#define SHM_NAME "/sharedmemory"
#define MUTEX_NAME "/pot_mutex"

typedef struct {
	int servings;
}shared_t;
