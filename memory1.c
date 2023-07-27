#include "main.h"
/**
 * _calloc - funct to allocate memory
 * @nmemb: no fo elemr
 * @size: bythe for pos
 * Return: return ptr
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *ptr;
	unsigned int j;

	if (nmemb == 0 || size == 0)
		return (NULL);

	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);

	for (j = 0; j < nmemb * size; j++)
		ptr[j] = 0;

	free(ptr);
	return (ptr);
}
