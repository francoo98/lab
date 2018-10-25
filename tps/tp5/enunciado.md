COMPUTACION II
==============


TP5: Servidor HTTP multihilado
------------------------------

- Fecha de entrega :      30/10/2018

Objetivos:
~~~~~~~~~

* Continuar familiarizandose con las herramientas de desarrollo de sistemas POSIX (Unix-like) como make, vim y man.
* Comprender y utilizar la técnica de Multihilos para convertir una tarea compleja en muchas tareas mas sencillas.
* Comprender la creación y termino de hilos y su utilidad.


Enunciado:
~~~~~~~~~

Realizar un servidor HTTP (web) multihilado, que pueda atender múltiples conexiones simultaneas.
La aplicación deberá cumplir con los estandar RFC's de HTTP 1.0.

Modo de trabajo:
~~~~~~~~~~~~~~~
El hilo de main (servidor) deberá realizar la lectura argumentos. Luego deberá crear y abrir un socket pasivo, para posteriormente, quedar bloqueado a la espera de clientes que se conecten a él.
Deberá lanzar un hilo nuevo por cada cliente que se conecte. La tarea de cada hilo será leer del socket el método de solicitud y parsear el archivo solicitado. Validará que exista el archivo solicitado, lo abrirá, leerá y lo escribirá en el descriptor del socket. Finalmente el hijo deberá terminar. El hilo de main deberá permanecer aceptando nuevas conexiones indefinidamente, indicando por stdout la dirección, puerto y archivo solicitado por cada cliente.

Requisitos de la implementación:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Debe utilizar la herramienta Makefile para la construcción del binario, prueba y borrado.
* El programa debe ser realizado al menos con tres módulos separados.
* Debe ser configurable por medio de un archivo de configuración. En el mismo deberán ser parametrizables al menos: el puerto por el que atenderá el servidor y la ruta del sistema de archivos que será la raíz de los archivos visibles para HTTP.

* El nombre del archivo de configuración deberá poder cambiarse como el argumento "-f" del archivo ejecutable en cuestión. En caso de no usar el argumento “-f”, se leerá desde el mismo directorio que la aplicación servidora el archivo “tp5.conf”.

* Soportará al menos diez accesos concurrentes y mil requerimientos por acceso. Para ello utilizar Apache benchmark. (man ab)

* Debe poder manejar, al menos, 4 tipos de archivos: jpeg, html, text y pdf (ver mime types).

* Debe devolver como mínimo, tres tipos de resultados al cliente: 200 Ok, 404 Not Found y 500 Internal Server Error (Ver especificación de HTTP 1.0).



Todo lo que no está especificado en este enunciado queda a consideración de los alumnos.

Modo de uso :
-----------------------------
$ ./tp5
  o
$ ./tp5 -f <archivo_config>
-----------------------------

Archivo de configuración
-----------------------
$ cat archivo_config

port=<nro_puerto>
droot=<document_root>

Tips :
- mime types en /etc/mime.types
- RFC 1945 - Hypertext Transfer Protocol -- HTTP/1.0
	Ver concepto de URI, URL, mime type, cabecera HTTP (request y response), HTTP status code.
- man getaddrinfo
- Linux Documentation project http://tldp.org/HOWTO/Linux+IPv6-HOWTO/
