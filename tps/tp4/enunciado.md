# COMPUTACION II


## TP4

Fecha de entrega: 16/10/2018


### Desafío
Crear una aplicación que, a través de palabras claves, busque contenido específico en páginas web.
La aplicación deberá recibir consultas desde clientes de red de manera concurrente.
Cuando un cliente se conecta, le envía la información necesaria para buscar contenido en la web por argumento
- la dir de una página web
- la palabra a buscar

El servidor debe obtener esa URL y buscar en dicha página la palabra, utilizando el protocolo HTTP.
Finalmente, el servidor, debe retornar el resultado de la búsqueda al cliente.

### Requerimientos

* Utilizar make para compilar la aplicación.

* La aplicación deberá contener como mínimo 3 módulos y 5 funciones además del main.

* El servidor debe escuchar en un puerto obtenido por argumentos. En caso de no indicarlo, usar por defecto el puerto 5000/TCP.

* Utilizar getopt para el manejo de argumentos.


#### Ejemplo modo de uso

~~~~~~~~~~~~~~~~~~~
$ ./server-tp4 -p 8080 &
$ ./cliente-tp4 -u http://www.um.edu.ar/es/ua/fi.html -t "Teléfonos" 127.0.0.1 8080

respuesta: Teléfonos: 54 261 4202017. Fax: 54 261 4202017 (Opción 9)

~~~~~~~~~~~~~~~~~~~


### Objetivos

* Utilizar un archivo Makefile para el proceso de compilación y testeo.

* Ejercitar multiprocesamiento con fork.

* Aprender a comunicar dos o más procesos a través de socket

* Aprender el protocolo estandar HTTP

