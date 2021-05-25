 # <div style="text-align: right"> Prototipo de Agricultura Urbana </div>

Este proyecto se lleva a cabo para diseñar e implementar un sistema de monitoreo remoto en variables de interés en tiempo real con tecnología loT para cultivos urbanos para desarrollo interno. Con esta propuesta se propone un desarrollo de bajo costo para que los usuarios caseros colaboren para mitigar el cambio climático y traer alternativas alimentarias para todo aquel que quiera cultivar sus cultivos en sus propias casas. El código y los diseños son de acceso gratuito y están disponibles para su mejora.

Acontinuación se muestra un listado requisitos mínimos que se necesitan para replicar exitosamente el proyecto.


## Infraestructura Electrónica

- Tarjeta NodeMcu V3 para ESP8266
- Sensor de temperatura y humedad HDC1008
- Sensor de luz y proximidad CJMCU-3216
- Cable USB tipo B para Arduino™ de 30cm
- Adaptador de voltaje

## Infraestructura Blanda (Software)

Seguimos el desarrollo de la teoría de Internet de Las Cosas del autor Francis Da Costa, empleando un sistema de end device, collector y gateway integrados en un solo dispositivo (en este caso el microcontrolador NodeMCU junto con sus sensores y alimentación de energía). Se emplea un distribuidor, sistema de almacenamiento de base de datos, sistema de ETL (extracción transformación y carga) y un sistema de toma de decisiones con una visualización al usuario mediante página web y aplicación móvil, para este fin empleamos la nube de AWS (Amazon Web Services) desarrollando los servicios mediante máquinas virtuales y desarrollos en un framework por Python 3.8.

Después de definir los componentes de hardware y software necesarios para el proyecto, de conocer y entender los procesos de IoT que se tiene que realizar para la recolección, almacenamiento y tratamiento de los datos, se procede al diseño e implementación del hardware. En esta etapa se explicarán algunos conceptos para tener en cuenta, también se explicarán a detalle cómo se realizó el proceso IoT del sistema que está compuesto por collection, pruning y bundling.
<img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Diagrama%20esquematico%20del%20circuito.png" width="256" height="256" title="Image of Circuito Electronico">


