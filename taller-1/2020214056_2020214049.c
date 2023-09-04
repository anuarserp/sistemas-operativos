#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct timespec start, end;

int mostFrequent(int size, int* array);
float median(int size, int* array);

int compare(const void *a, const void *b) 
{
    return (*(int*)a - *(int*)b);
}

int main(int argc, char *argv[])
{
	double elapsed;

	FILE* file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("Error al abrir el archivo\n");
		exit(1);
	}

	//Lectura del archivo
	clock_gettime(CLOCK_REALTIME, &start);
	
	int size;

	fscanf(file, "%d", &size);

	int* array = (int *)malloc(size * sizeof(int));

	if (array == NULL)
	{
		printf("Error al reservar memoria\n");
		exit(1);
	}
	clock_gettime(CLOCK_REALTIME, &end);
	elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

	printf("el tiempo de ejecucion de la lectura del archivo es %fseg\n\n", elapsed);

	//Suma de los elementos del arreglo
	clock_gettime(CLOCK_REALTIME, &start);

	long int sum = 0;
	int i;

	for (i = 0; i < size; i++)
	{
		fscanf(file, "%d", &array[i]);
		sum += array[i];
	}
	
	clock_gettime(CLOCK_REALTIME, &end);
	elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

	printf("la suma es %ld\n", sum);
	printf("el tiempo de ejecucion de la suma es %fseg\n\n", elapsed);

	//Valores mas frecuentes
	clock_gettime(CLOCK_REALTIME, &start);

	int mostFrecuent = mostFrequent(size, array);

	clock_gettime(CLOCK_REALTIME, &end);
	elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
	
	printf("el tiempo de ejecucion para hallar valor mas frecuente es %fseg\n\n", elapsed);

	//Mediana
	clock_gettime(CLOCK_REALTIME, &start);
	float med = median(size, array);
	clock_gettime(CLOCK_REALTIME, &end);
	elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("la mediana es %f\n", med);
	printf("el tiempo de ejecucion para hallar de la mediana es %fseg\n\n", elapsed);

	fclose(file);
    free(array);

	return 0;
}

int mostFrequent(int size, int *array)
{
    qsort(array, size, sizeof(int), compare);

    int maxCount = 1, mostFrecuent = array[0], count = 1;
    int secMaxCount = 0, secMostFrecuent = 0; 

    for (int i = 1; i < size; i++) 
    {
        if (array[i] == array[i - 1]) 
        {
            count++;
        }
        else 
        {
            count = 1;
        }

        if (count > maxCount) {
            if (array[i] != mostFrecuent) 
			{
				secMaxCount = maxCount;
				secMostFrecuent = mostFrecuent;
			}
			maxCount = count;
			mostFrecuent = array[i];
        }

		if (count > secMaxCount && array[i] != mostFrecuent)
		{
			secMaxCount = count;
			secMostFrecuent = array[i];
		}
	}
    
    printf("Valores mas frecuentes: (%d,%d); (%d,%d)\n", mostFrecuent, maxCount, secMostFrecuent, secMaxCount);

    return mostFrecuent;
}

float median(int size, int *array)
{
	if (size % 2 == 0)
	{
		return (array[size / 2] + array[(size / 2) - 1]) / 2.0;
	}
	else
	{
		return array[size / 2];
	}
}