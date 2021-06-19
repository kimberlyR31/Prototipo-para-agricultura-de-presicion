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

<p align ="center" > <img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Arquitectura%20IoT%20del%20proyecto.jpeg" width="500" height="500" title="Image of Circuito Electronico"> </p>
<p align ="center" > Imágen 1. Arquitectura IoT del proyecto. </p>
<br/>

## Sobre la conexión del hardware y envío de los datos

Después de definir los componentes de hardware y software necesarios para el proyecto, en esta etapa se explicará como se realiza la conexión del hardware mediante un diagrama esquematico. Inicialmente se conectarán los sensores HDC1008  y AP3216C a un módulo NodeMcu V3 para ESP826. La conexión del sensor con la placa requiere 8 cables. Podemos obtener energía del pin de 3V en la tarjeta NodeMcu. A continuación, se muestra la conexión utilizada:
- Conecte SCL a D1 
- Conecte SDA a D2 
- Conecte 3.3V a 3V 
- Conecte GND a G

<p align ="center" > <img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Diagrama%20esquematico%20del%20circuito.png" width="600" height="280" title="Image of Circuito Electronico"> </p>
<p align ="center" > Imágen 2. Diagrama esquemático del circuito. </p>
<br/>

Los datos generalmente se recopilan dentro del collector, se agrupan y se podan según sea necesario para la transmisión, y luego se envían generalmente a través de Internet tradicional. Para efectos del proyecto es la tarjeta NodeMCU la que cumple la función de collector. Existe tres procesos importantes que se realizan dentro del colector los cuales se explicarán a continuación. 

1.	Collection: Proceso en el cual se realiza la captura de uno o varios datos que vienen puros de los sensores y se procesan, esto mediante la comunicación I2C. 

2.	Pruning: Una de las capacidades importantes de los nodos propagadores es poder podar y optimizar las transmisiones. Los datos que pasan desde y hacia los dispositivos finales pueden combinarse con otro tráfico y enviarse en la dirección general de su "flecha" de transmisión. Aunque lo anterior describe la función genérica de los nodos propagadores, muchos también incorporarán una capacidad adicional importante: la capacidad de ser gestionados y "sintonizados" por funciones integradoras en la red.

3.	Bundling: Es el paso que se realiza del collector al distribuidor.

Para poder realizar la lectura y el promedio de los datos de humedad, temperatura y luz se deberá ejecutar en la carpeta de "Códigos Arduino" el código "Promedio de 3 Variables" en el programa arduino. El envío de estos datos al servidor se realiza con el código "Con envío de trama".

La visualización de los datos se podrá realizar al ejecutar el código "Código en servidor" el cual es el encargado de recibir la trama que es enviada por los sensores, además de procesar y graficar dicha información.

## Modelo de toma de decisiones

El un proceso de adaptación, transformación y carga que se realiza cuando se toman los datos que vienen de la base de datos, luego estos se transforman y son procesados para que queden en un modelo de toma de decisiones. Este modelo de toma de decisiones y visualización se base en un modelo de reglas. Estas reglas son las que definen el proceso de desarrollo del cultivo.
Gracias a la visualización de la información se va a poder realizar la toma decisiones que va a permitir realizar acciones para llevar a cabo el cultivo de la planta hasta su recolección. Para ello se va a construir una máquina de estados o una forma que pueda informar cómo está creciendo la planta y que tipo de estadísticas está arrojando y con ello se determinará cuando la planta está lista para cultivarse o cuanto es el momento en que se le tiene que poner de luz, agregar abono o agua. 
Este modelo de toma de decisiones se basa en un modelo de reglas de dos tipos:

## - Las reglas instantáneas 

 Estas reglas se dan cuando se están midiendo la información de los sensores casi en tiempo real. Estas reglas son las acciones y recomendaciones inmediatas que requiere el cultivo. A continuación, se muestra el pseudocódigo de algunas reglas instantáneas y cuál sería el tipo de alerta que se notificaría.
<br/>

 <p align ="center" > <img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Pseudoc%C3%B3digo%20de%20una%20regla%20instant%C3%A1nea.jpeg" title="Image of Circuito Electronico"> </p>
<p align ="center" > Imágen 3. Pseudocódigo de una regla instantánea. </p>
<br/>
<br/>

<p align ="center" > <img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Ejemplo%20de%20alerta%20generada%20por%20una%20regla%20instant%C3%A1nea.jpeg"> </p>
<p align ="center" > Imágen 4.  Ejemplo de alerta generada por una regla instantánea. </p>


## -Las reglas históricas 

Son todas aquellas reglas que necesitan utilizar todo el histórico de datos para construir acciones o recomendaciones. Estas reglas marcan los hitos más importantes en el proceso del cultivo tales como la fecha de inicio de sembrado, la etapa en que se encuentra la planta o la fecha de cosecha para el cultivo. A continuación, se muestra el pseudocódigo de algunas reglas historias y cual sería el tipo de alerta que se notificaría.
<br/>

<p align ="center" > <img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Pseudoc%C3%B3digo%20de%20una%20regla%20hist%C3%B3rica.jpeg" title="Image of Circuito Electronico"> </p>
<p align ="center" > Imágen 5. Pseudocódigo de una regla histórica. </p>
<br/>
<br/>

<p align ="center" > <img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Ejemplo%20de%20alerta%20generada%20por%20una%20regla%20hist%C3%B3rica.jpeg"> </p>
<p align ="center" > Imágen 6.  Ejemplo de alerta generada por una regla histórica. </p>


A continuación, se presentan tres gráficas que muestran el histórico de los datos recolectados por cada uno de los sensores tomando como ejemplo un cultivo de cilantro. Las gráficas muestran algunos picos en ciertas fechas debido a que como se encuentra en una fase de prototipo no se tienen continuas todas las mediciones. 

<p align ="center" > <img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Historico%20de%20datos%20de%20Humedad.jpeg" width="600" height="280" title="Image of Circuito Electronico"> </p>
<p align ="center" > Gráfica 1. Histórico de dato de Humendad. </p>
<br/>
<br/>

<p align ="center" > <img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Historico%20de%20datos%20de%20Luz.jpeg" width="600" height="280" title="Image of Circuito Electronico"> </p>
<p align ="center" > Gráfica 2. Histórico de dato de Luz. </p>
<br/>
<br/>

<p align ="center" > <img src="https://github.com/kimberlyR31/Towards-the-development-of-homemade-urban-agriculture-products-using-the-internet-of-things/blob/main/Im%C3%A1genes/Historico%20de%20datos%20de%20Temperatura.jpeg" width="600" height="280" title="Image of Circuito Electronico"> </p>
<p align ="center" > Gráfica 3. Histórico de dato de Temperatura. </p>

<br/>
<br/>
<br/>
<br/>
<br/>
<br/>



