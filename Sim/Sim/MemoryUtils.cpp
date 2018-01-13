#include <windows.h>
#include <stdlib.h>

void xfree(void *Ponteiro_do_Ponteiro) {
	void **Ponteiro = (void**)Ponteiro_do_Ponteiro;

	if (*Ponteiro != NULL)
		free(*Ponteiro);

	*Ponteiro = NULL;
}