# Tarea 3: Optimización

B94560 Gilbert Marquez

### Descripción

En este reporte se dará seguimiento a la aplicación del método sugerido para optimizar. El programa a optimizar es el realizado en la tarea 2, el cual es un programa que calcula las sumas de goldbach concurrentemente utilizando un mapeo por bloque. El objetivo de esta tarea es realizar dos optimizaciones siguiendo el método sugerido para optimizar. La primera optimización será implementar un mapeo dinámico mediante el uso del patrón productor-consumidor. La segunda será de elección libre, por lo que, conforme avancen las pruebas se seleccionará aquella que haya logrado una mejora de rendimiento. Finalmente, se discutirá los resultados finales a modo de conclusión.

### Primera optimización

El tiempo de ejecución del programa goldbach_pthread (Tarea 2) fue de un total de 270.50 segundos, unos 4 minutos 30 segundos aproximadamente.

En esta primera optimización no es necesario realizar profiling.

El método para optimizar que se utilizará consiste en implementación un mapeo dinámico mediante el uso del patrón productor-consumidor. Se espera que se mejore el rendimiento, aunque depende del orden en que se encuentren ordenados los datos.
