# Hashing
Funcion de Hash puntos a desarrollar :

1) INSERTAR 
2)ELIMINAR
3)BUSCAR SI ESTÁ

-La tabla tendrá tamaño (n*1,2)-1

-La tabla arranca con todos '\0' (Espacio vacío). Al insertar un elemento en un lugar vacío se crea una lista de 2 elementos ["Elemento",'\0']

-El algoritmo recibe un string.

-Que el algoritmo use el codigo ASCII de cada caracter y la posicion en la que esta para asignarle un valor de la tabla de hash.

-Cada vez que se inserta o elimina un elemento, podemos llevar registro de esto en un array para luego tener registro de las colisiones.

//Testeo del algoritmo

1) Pasarle 10k elementos y ver en promedio cuanto tarda. Repetirlo con 1M elementos y el tiempo deberia mantenerse casi constante.
2) Recorrer la tabla de hash y ver los buckets y el bucket mas largo.
