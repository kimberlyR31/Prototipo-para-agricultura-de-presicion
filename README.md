 # <p align ="center" > Prototipo de Agricultura Urbana </p>

Este proyecto se lleva a cabo para diseñar e implementar un sistema de monitoreo remoto en variables de interés en tiempo real con tecnología loT para cultivos urbanos para desarrollo interno. Con esta propuesta se propone un desarrollo de bajo costo para que los usuarios caseros colaboren para mitigar el cambio climático y traer alternativas alimentarias para todo aquel que quiera cultivar sus cultivos en sus propias casas. El código y los diseños son de acceso gratuito y están disponibles para su mejora.

Acontinuación se muestra un listado requisitos mínimos que se necesitan para replicar exitosamente el proyecto.


## Infraestructura Electrónica

- Tarjeta NodeMcu V3 para ESP8266
- Sensor de temperatura y humedad HDC1008
- Sensor de luz y proximidad CJMCU-3216
- Cable USB tipo B para Arduino™ de 30cm
- Adaptador de voltaje

## Infraestructura Blanda (Software)

Seguimos el desarrollo de la teoría de Internet de Las Cosas del autor Francis Da Costa, empleando un sistema de end device, collector y gateway integrados en un solo dispositivo (en este caso el microcontrolador NodeMCU junto con sus sensores y alimentación de energía). Se emplea un distribuidor, sistema de almacenamiento de base de datos, sistema de ETL (extracción transformación y carga) y un sistema de toma de decisiones con una visualización al usuario mediante página web y aplicación móvil. Para este fin empleamos la nube de AWS (Amazon Web Services) desarrollando los servicios mediante máquinas virtuales y desarrollos en un framework por Python 3.8.

## Sobre la conexión del hardware y envío de los datos

Después de definir los componentes de hardware y software necesarios para el proyecto, en esta etapa se explicará como se realiza la conexión del hardware mediante un diagrama esquematico. Inicialmente se conectarán los sensores HDC1008  y AP3216C a un módulo NodeMcu V3 para ESP826. La conexión del sensor con la placa requiere 8 cables. Podemos obtener energía del pin de 3V en la tarjeta NodeMcu. A continuación, se muestra la conexión utilizada:
- Conecte SCL a D1 
- Conecte SDA a D2 
- Conecte 3.3V a 3V 
- Conecte GND a G

<p align ="center" > <img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Diagrama%20esquematico%20del%20circuito.png" width="500" height="500" title="Image of Circuito Electronico"> </p>

Para poder realizar la lectura y el promedio de los datos de humedad, temperatura y luz se deberá ejecutar en la carpeta de "Códigos Arduino" el código "Promedio de 3 Variables". El envío de estos datos al servidor se realiza con el código "Con envío de trama".




