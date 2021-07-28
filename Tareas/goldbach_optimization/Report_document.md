# Tarea 3: Optimización

B94560 Gilbert Marquez

### Descripción

En este reporte se dará seguimiento a la aplicación del método sugerido para optimizar. El programa a optimizar es el realizado en la tarea 2, el cual es un programa que calcula las sumas de goldbach concurrentemente utilizando un mapeo por bloque. El objetivo de esta tarea es realizar dos optimizaciones siguiendo el método sugerido para optimizar. La primera optimización será implementar un mapeo dinámico mediante el uso del patrón productor-consumidor. La segunda será de elección libre, por lo que, conforme avancen las pruebas se seleccionará aquella que haya logrado una mejora de rendimiento. Finalmente, se discutirá los resultados finales a modo de conclusión.

### Primera optimización

El tiempo de ejecución del programa goldbach_pthread (Tarea 2) fue de un total de 270.50 segundos, unos 4 minutos 30 segundos aproximadamente.

En esta primera optimización no es necesario realizar profiling.

El método para optimizar que se utilizará consiste en implementación un mapeo dinámico mediante el uso del patrón productor-consumidor. Se espera que se mejore el rendimiento, ya que, al usar este tipo de mapeo se busca evitar que un hilo reciba una gran carga de trabajo mientras otros reciban una pequeña carga.

Tras la implementación y las mediciones, los resultados arrojaron que efectivamente se aumentó el rendimiento del programa, pues, el tiempo de ejecución fue de 240.84 segundos, aproximadamente 4 minutos.

### Segunda optimización

Para demostrar que se logra un mejor rendimiento con esta segunda optimización, se comparará el rendimiento resultante acá con el rendimiento de la optimización anterior (tiempo de ejecución de 4 minutos).

Tras realizar el profiling, se observó que la región crítica que consume más CPU es al momento de calcular los números primos, con un 71% del CPU. Por esta razón, se intentará optimizar este proceso utilizando una criba de Eratóstenes. Este método consiste en almacenar los números en una estructura de datos y luego "tachar" aquellos que no son primos. El proceso sería algo como, tomar el primer primo que es 2 y tachar todos sus múltiplos, luego tomar el siguiente primo, que es el 3, y tachar todos los múltiplos de 3, y así sucesivamente.

Se espera que se mejore el rendimiento, ya que, la criba será compartida y se incrementará solo cuando un número es mayor que el número más grande de la criba, por lo que, no necesariamente se deben calcular todos los primos para cada número, como sí ocurría antes. Sin embargo, en el caso de que los números vengan ordenados de menor a mayor, sí se calcularán los primos para todos los números.