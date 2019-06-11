CFLAGS= -g -Wall
TARGETS= Mysql y C
OBJECTS =
HEAD=
LDLIBS= -lpthread

inicio:
	$(CC) -o main *.c $(LDLIBS)
	@echo "Ejecutable creado exitosamente"

clean:
	rm -fv *~ *.o
	@echo "Archivos borrados exitosamente"

ejecutar:
	./main
 
