Regresiones Calculadora

Para correr las regresiones, basta con colocar el binario del programa dentro de este
directorio, renombrándolo a "calc" para que el Makefile lo pueda ejecutar. 

Si todo sale bien, la salida debería ser:

$ make test
Files 0-warmup.out and 0-warmup.ref are identical
Files 1-spaces.out and 1-spaces.ref are identical
Files 2-precision.out and 2-precision.ref are identical
Files 3-recursion.out and 3-recursion.ref are identical
Files 4-mixed.out and 4-mixed.ref are identical
OK

Para limpiar el directorio y dejar todo listo para una nueva corrida:

$ make clean
rm -f *.out || :
