# Capítulo 9: scripting básico

Aquí te he dejado el paquete de materiales de este capítulo, que en realidad consiste en el script de **Dogmole** terminado.

## ¿Scripting básico?

Eso mismo pone. En este capítulo vamos a definir el gameplay de **Dogmole Tuppowski** y vamos a aprender algunas nociones básicas de scripting.

El sistema de scripting de **MTE MK1** es muy sencillo y parece bastante limitado, pero te puedes empepinar bastante y conseguir cosas medianamente complejas con algo de maña. De hecho, el scripting a partir de v5.0 es bastante más potente ya que se ha integrado la versión más reciente de MSC3, el sistema empleado en MK2, sustituyendo al MSC original, por lo que si practicas puedes lograr en tu juegos diseños de gameplay bastante complejos. Las reglas de **Dogmole** son sencillas a propósito, y nos servirán para ilustrar un comportamiento sencillo y aprender. Luego veremos el script de diferentes juegos mojonos para que veáis cómo hemos conseguido hacer las cosas.

El sistema de scripting tiene muchos comandos y comprobaciones diferentes. Como no quiero convertir este curso en una referencia con una lista de cosas interminables. Para ello puedes consultar la referencia completa de MSC3. No está de más echarle un ojaldre cuando tengas las nociones básicas.

Refresquemos un poco

Recordemos que el script está formado por secciones, y que cada sección incluye cláusulas. Cada cláusula no es más que una lista de comprobaciones y una lista de comandos: si todas las comprobaciones son ciertas, se ejecutarán los comandos.

Controlamos qué cláusulas se ejecutarán colocándolas en una u otra sección. Recordemos las secciones que existen y cuándo se ejecutan:

ENTERING GAME: Esta sección se ejecutará nada más empezar la partida, y nunca más.

ENTERING ANY: Esta sección se ejecutará al entrar en cada pantalla, y también al pisar un enemigo. Sí, no tiene lógica alguna, pero es así porque viene muy bien para determinadas cosas.

ENTERING SCREEN n: Esta sección se ejecutará al entrar en la pantalla N.

PRESS_FIRE AT ANY: Esta sección se ejecutará al pulsar acción, sin importar en qué pantalla estemos.

FRESS_FIRE AT SCREEN n: Esta sección se ejecutará al pusar acción, si estamos en la pantalla N, y también al pisar un enemigo. Tampoco tiene lógica, pero también viene bien.

ON_TIMER_OFF: Esta sección se ejecutará si tenemos un temporizador, este llega a 0, y hemos configurado en config.h que ocurra esto.

¡Vamos a ello!

Antes de empezar vamos a recapitular, porque es importante que sepamos qué estamos haciendo. Recordemos, pues, cuál era el diseño de gameplay de nuestro Dogmole Tuppowsky:

En primer lugar, la puerta de la universidad está cerrada, y para abrirla hay que matar a todos los monjes. Hay 20 monjes puestos por todo el mapa, en la parte de abajo (las dos filas inferiores) y hay que cargárselos a todos. Cuando estén todos muertos, habrá que quitar el piedro que colocamos en el mapa a la entrada de la universidad.

Luego hay que programar la lógica del pedestal, dentro de la universidad. Si tocamos el pedestal llevando un objeto, lo perdemos y se incrementará un flag contando el número de objetos que hemos depositado. Cuando este número llegue a 10, habremos ganado el juego.

El script de este juego va a ser muy sencillo. Lo primero que tenemos que mirar es qué vamos a necesitar almacenar para destinar algunas flags para ello. En nuestro caso, como el motor ya se encarga de contar los monjes que hemos matado, sólo necesitaremos ir contando las cajas que vamos depositando y además necesitaremos recordar si hemos quitado el piedro o no. Vamos a usar dos flags: la 1 y la 3. ¿Por qué estas dos y no otras? Pues porque sí. En realidad, da igual.
Recordemos que mencionamos en el anterior capítulo que era interesante apuntar qué hacía cada flag al principio de nuestro script:

# flags:
# 1 – cuenta general de objetos.
# 3 – 1 = puerta de la universidad abierta.
Contando monjes muertos

Vaya título ¿eh? Pero mola. Lo primero que vamos a ver es cómo contar los monjes muertos para quitar el piedro de la pantalla 2. Antes que nada, tenemos que ver qué es lo que vamos a quitar. La pantalla 2 es esta, y he marcado el piedro que tenemos que quitar por scripting:



Si contamos un poquito, nos damos cuenta de que el piedro ocupa las coordenadas (12, 7). Las apuntamos.
Hemos dicho que vamos a usar el flag 3 para almacenar si ya hemos matado a todos los monjes o no. Si el flag 3 vale 1, significará que hemos matado a todos los monjes, y en ese caso habría que modificar esa pantalla para borrar el piedro de la posición que tenemos anotada. ¿Por qué no empezar por ahí? Creemos, pues, una cláusula para cuando entremos en la pantalla 2:

# Entrada de la universidad

ENTERING SCREEN 2

	# Control de la puerta de la universidad.

	IF FLAG 3 = 1

	THEN

		SET TILE (12, 7) = 0

	END

END
Poco hay de nuevo en esta primera cláusula de gameplay que hemos escrito: se trata de la comprobación del valor de un flag. En vez de el IF TRUE que habíamos usado hasta ahora, escribimos IF FLAG 3 = 1 que sólo evaluará a cierto si el valor de nuestro flag 3 es, precisamente, 1. En este caso, se ejecutará el cuerpo de la cláusula: SET TILE (12, 7) = 0 escribirá el tile vacío sobre el espacio que ocupa el piedro, eliminándolo. Por tanto, cuando entremos en esta pantalla con el flag 3 a 1, se borrará el piedro y no habrá obstáculo. ¿Se pilla el concepto?

Sigamos, entonces. Hemos dicho que el flag 3 a 1 significa que hemos matado a todos los enemigos, pero el flag 3 no se va a poner a 1 automáticamente. Necesitamos crear una regla que, efectivamente, lo ponga a 1.

Como en la pantalla donde aparece el piedro no hay monjes, nunca se dará la situación de que matemos al último monje en la pantalla del piedro. Esto es: siempre estaremos en otra pantalla cuando matemos al último monje. Por tanto, un buen sitio para comprobar que hemos matado a todos los monjes es al entrar en cualquier pantalla, o sea, en nuestra sección ENTERING ANY. Y mejor todavía, por la particularidad esa que mencionamos antes de que ENTERING ANY se ejecuta también cuando pisamos a un enemigo. Cada vez que entremos en una pantalla, comprobaremos que el número de enemigos eliminados vale 20 y, si se da el caso, pondremos el flag 3 a 1:



# Abrir la universidad

ENTERING ANY

	IF ENEMIES_KILLED_EQUALS 20

	IF FLAG 3 = 0

	THEN

		SET FLAG 3 = 1

		SOUND 7

		SOUND 8

		SOUND 9

		SOUND 7

		SOUND 8

		SOUND 9

	END

END
Con esto conseguimos justo lo que queremos. Fíjate que hay una nueva comprobación: IF ENEMIES_KILLED_EQUALS 20 será cierta si el número de enemigos eliminados (o monjes) vale exactamente 20. Si eso es cierto, acto seguido comprobamos el valor del flag 3 para ver que vale 0. Con esto lo que hacemos es asegurarnos de que esta cláusula sólo se ejecutará una vez, o de lo contrario se ejecutaría al entrar en cada pantalla.

Si todo se ha cumplido, pondremos el flag 3 a 1 (que es lo que queríamos) además de soltar una serie de pitidos pochos. Sí, el comando SOUND n toca el sonido n. Se trata de los sonidos del engine. Puedes mirar a qué corresponde cada número en el archivo beeper.h, al final.

Con esto tendremos lista la primera parte de nuestro gameplay: si todos los enemigos están muertos, colocamos el flag 3 a 1. En la pantalla 2, si el flag 3 vale 1, quitamos el piedro.

Lógica de las cajas

Ahora sólo nos queda definir la segunda parte del gameplay. Si recordáis, tenemos configurado el motor con ONLY_ONE_OBJECT. Eso significa que el máximo de objetos que podemos recoger es uno, o sea, que sólo podemos llevar una caja.

El objetivo del juego es llevar 10 cajas al mostrador de la Universidad, por tanto tendremos que programar en el script la lógica que haga que, si llevamos un objeto y activamos el mostrador, se nos reste ese objeto y se incremente el contador de objetos entregados, que hemos dicho que será el flag 1.

El mostrador está en la pantalla 0, si recordáis: lo hemos pintado con SET TILE desde nuestro script en la sección ENTERING SCREEN 0. El pedestal ocupa las posiciones (3, 7) y (4, 7).

Vamos a escribir ahora un trozo de script que, si pulsamos la tecla de acción en la pantalla 0, comprueba que estamos tocando el pedestal y que llevamos un objeto, para eliminar ese objeto e incrementar en uno la cuenta.

Lo primero que tenemos que resolver es la detección de que estamos tocando el pedestal. Si el pedestal ocupase un sólo tile en (x, y), sería muy sencillo:

IF PLAYER_TOUCHES x, y
Si cualquier pixel del jugador toca el tile (x, y), esa condición evalúa a cierto. El problema es que nuestro pedestal ocupa dos tiles. Una solución sería escribir dos cláusulas idénticas, una con un PLAYER_TOUCHES 3, 7 y la otra con un PLAYER_TOUCHES 4, 7, pero eso no será necesario ya que tenemos otras herramientas.

Para comprobar que estamos dentro de un area tenemos dos comprobaciones especiales:

IF PLAYER_IN_X x1, x2
IF PLAYER_IN_Y y1, y2


La primera evaluará a cierto si la coordenada x, en píxels, de la esquina superior izquierda del cuadro del sprite de nuestro personaje está entre x1 y x2. La segunda lo hará si la coordenada y, en píxels, de la esquina superior izquierda del cuadro del sprite de nuestro personaje está entre y1 e y2.

Veámoslo con un dibujo. Aquí vemos un área delimitada por x1, x2 y por y1, y2. El jugador estará “dentro” de ese área si el píxel marcado en rojo (el de la esquina superior izquierda del sprite) está “dentro” de ese área.

Cuando queremos comprobar que nuestro personaje esté dentro del área rectangular que ocupa un conjunto de tiles, tendremos que seguir la siguiente fórmula para calcular los valores de x1, x2, y1 e y1. Si (tx1,ty1) son las coordenadas (en tiles) del tile superior izquierdo del rectángulo y (tx2, ty2) son las coordenadas (también en tiles) del tile inferior derecho, esto es:



Con el área definida aquí, los valores de x1, x2 e y1, y2 que tendremos que usar en el script son los que se obtienen con las siguientes fórmulas:

x1 = tx1 * 16 – 15
x2 = tx2 * 16 + 15	y1 = ty1 * 16 – 15
y2 = ty2 * 16 + 15
Para verlo, de nuevo, un dibujito. Fíjate que he superpuesto un sprite para que veáis que para que “toque” los tiles debe estar en el rectángulo definido por las coordenadas (x1, y1) y (x2, y2):



Sí, si no estáis acostumbrados a hacer números programando esto es un lío de cojones, pero en realidad no lo es tanto cuando memorizáis la fórmula, o, mejor, si la comprendéis. Se multiplica por 16 para pasar de coordenadas de tiles a coordenadas de pixels porque los tiles miden 16×16 pixels. La suma y resta de 15 es para hacer “colisión por caja” con el sprite.

Sé que podríamos haber diseñado el scripting para ocultar un poco estos tejemanejes, pero así, exigiendo que el programador haga un par de operaciones matemáticas por su cuenta, eliminamos mucha complejidad en el código ya que le estamos dando al motor los datos “mascaditos”.

Para terminar de verlo, trasladémonos a nuestro caso y hagamos las operaciones necesarias utilizando los valores de nuestro juego. Aquí, el rectángulo está formado únicamente por dos tiles en las coordenadas (3, 7) y (4, 7). Los tiles de las esquinas son esos dos tiles, precisamente, por lo que tx1 valdra 3, ty1 valdrá 7, tx2 valdrá 4 y ty2 valdrá también 7. De ese modo, siguiendo las fórmulas:

x1 = 3 * 16 – 15 = 33
x2 = 4 * 16 + 15 = 79	y1 = 7 * 16 – 15 = 97
y2 = 7 * 16 + 15 = 127
O sea, que para tocar el mostrador, el sprite debe estar entre 33 y 79 en la coordenada X y entre 97 y 127 en la coordenada Y. Veámoslo gráficamente con un gráfico lioso: fíjate como para que el sprite esté tocando el mostrador, el píxel superior izquierdo del cuadrado de su sprite (marcado en rojo) debe estar dentro del área que hemos definido:



Además, tendremos que comprobar que llevemos una caja en el inventario. Sería algo así:



PRESS_FIRE AT SCREEN  0

	# Detectar pedestal. 

	# Lo detectamos definiendo un rectángulo de píxels. 

	# Luego comprobamos si el jugador ha cogido un objeto. 

	# Si todo se cumple, decrementamos el número de objetos e incrementamos FLAG 1

	IF PLAYER_IN_X 33, 79

	IF PLAYER_IN_Y 97, 127

	IF PLAYER_HAS_OBJECTS

	THEN

		INC FLAG 1, 1

		DEC OBJECTS 1

		SOUND 7

	END

END
Ahí está todo lo que hemos visto: primeramente, comprobamos la posición de Dogmole con IF PLAYER_IN_X e IF_PLAYER_IN_Y. Si todo se cumple, comprobamos que tengamos un objeto recogido con IF PLAYER_HAS_OBJECTS. Si se cumple todo haremos tres cosas: primero, incrementaremos en 1 el flag 1 mediante INC FLAG 1, 1. Luego decrementaremos en 1 en número de objetos recogidos (con lo que volverá a ser 0, y podremos volver a recoger otra caja) con DEC OBJECTS 1. Finalmente, tocaremos el sonido número 7.

Hecho esto, sólo nos queda una cosa que hacer: comprobar que hemos llevado las 10 cajas. Un buen sitio para hacerlo es justo después de la anterior cláusula. Como todas las cláusulas de una sección se ejecutan en orden, justo después de contabilizar colocaremos la comprobación de que ya hemos puesto 10 para terminar el juego. Ampliamos, por tanto, la sección PRESS_FIRE AT SCREEN 0 con la nueva cláusula. Quedaría así:



PRESS_FIRE AT SCREEN  0

	# Detectar pedestal. 

	# Lo detectamos definiendo un rectángulo de píxels. 

	# Luego comprobamos si el jugador ha cogido un objeto. 

	# Si todo se cumple, decrementamos el número de objetos e incrementamos FLAG 1

	IF PLAYER_IN_X 33, 79

	IF PLAYER_IN_Y 97, 127

	IF PLAYER_HAS_OBJECTS

	THEN

		INC FLAG 1, 1

		DEC OBJECTS 1

		SOUND 7

	END



	# Fin del juego

	# Si llevamos 10 cajas, ¡hemos ganado!

	IF FLAG 1 = 10

	THEN

		WIN GAME

	END IF

END
De nuevo, muy sencillo: si llevamos 10 cajas (o sea, si el flag1 vale 10), habremos ganado. El comando WIN GAME hace que el juego termine con éxito y se muestre la pantalla del final.

¿Ves que no ha sido tanto? Vale, lo de las coordenadas es un poco lío, pero tampoco es para echarse a llorar. O sí, si eres una persona sensible.

Mejora interesante

Tal y como hemos configurado nuestro güego, el jugador tiene que pulsar acción para activar el mostrador y depositar un objeto. No es un problema, pero molaría más que el jugador no tuviese que pulsar nada. Precisamente para eso introdujimos en el motor lo que hemos llamado “la zona de fuego”, o fire zone. Esta zona de fuego no es más que un rectángulo en pantalla, especificado en píxels. Si el jugador entra en el rectángulo, el motor se comporta como si hubiese pulsado acción. La zona de fuego se desactiva automáticamente al cambiar de pantalla, por lo que si la definimos en un ENTERING SCREEN n, sólo estará activo mientras estemos en esa pantalla.

Esto viene divinamente para nuestros propósitos: si al entrar en la pantalla 0 definimos una zona de fuego alrededor del mostrador, en cuanto el jugador lo toque se ejecutará la lógica que hemos programado en el script para dejar el objeto que lleve e incrementar el contador.

La zona de fuego se define con el comando SET_FIRE_ZONE, que recibe las coordenadas x1, y1, x2, e y2 del rectángulo que queramos usar como zona de fuego. Si queremos hacer coincidir la zona de fuego con un rectángulo formado por tiles, como es nuestro caso, se aplican las mismas fórmulas que explicamos antes. O sea, que vamos a usar exactamente los mismos valores.

Lo primer que tenemos que hacer es decirle al motor que vamos a usar zonas de fuego. Para ello, tenemos que activar la directiva correspondiente en nuestro config.h:

#define ENABLE_FIRE_ZONE // Allows to define a zone which auto-triggers «FIRE»
Hecho esto, sólo tendremos que modificar la sección ENTERING SCREEN 0 añadiendo el comando SET_FIRE_ZONE x1, y1, x2, y2 al final del todo:



# Vestíbulo de la universidad

ENTERING SCREEN 0

	# Decoración y pedestal

	IF TRUE

	THEN

		# Pedestal

		SET TILE (3, 7) = 22

		SET TILE (4, 7) = 23

		# Decoración

		SET TILE (1, 5) = 29

		SET TILE (1, 6) = 20

		SET TILE (1, 7) = 21

		SET TILE (6, 6) = 20

		SET TILE (6, 7) = 21

		SET TILE (7, 7) = 28

		SET TILE (1, 2) = 27

		SET TILE (1, 3) = 28

		SET TILE (2, 2) = 29

		SET TILE (2, 3) = 27

		SET TILE (3, 2) = 32

		SET TILE (3, 3) = 33

		SET TILE (9, 1) = 30

		SET TILE (9, 2) = 30

		SET TILE (9, 3) = 31

		# Fire zone (x1, y1, x2, y2):

		SET_FIRE_ZONE 33, 97, 79, 127

	END

END
La pregunta que te harás es ¿por qué #@!! no lo habéis metido en el juego? Pues porque esta característica, que se incluyó originalmente en la rama 4.0 (en el juego de el Hobbit) se reintrodujo con la versión 3.99.1.

Tío, estoy un poco perdido

Me hago cargo. Hay que hacerse un poco el coco al funcionamiento del script. Creo que es ideal empezar por algo muy sencillo, incluso más sencillo que el Dogmole que hemos visto, e ir progresando.

Se me ocurre algo genial: íbamos a terminar aquí el capítulo de scripting básico, pero creo que nos vendría muy bien ver juntos los scripts de algunos de nuestros juegos. Voy a elegir unos cuantos juegos con un script sencillo, y lo iremos explicando paso por paso. Sería interesante que, mientras tanto, fueses jugando al juego para ver cómo afectan las diferentes cláusulas.

Cheril Perils

El güego con el que estrenamos el motor de scripting fue Cheril Perils. Entonces todo estaba en pañales y era muy sencillo. El script de Cheril Perils es el script más sencillo de todos nuestros güegos con Script: aquí sólo se hace una cosa: que hayamos matado a todos los enemigos, en cuyo caso quitaremos los pinchos de la primera pantalla. Estos pinchos:



En principio se parece mucho a parte de lo que hemos hecho en Dogmole: al entrar en la pantalla, comprobamos que hemos matado a todos los enemigos (hay 60 en total). Si se da el caso, imprimimos el tile vacío sobre los pinchos:



ENTERING SCREEN 20

    IF ENEMIES_KILLED_EQUALS 60

    THEN

        SET TILE (2, 7) = 0

        SET TILE (2, 8) = 0

    END

END
Pero aquí ocurre algo que no nos pasaba en el Dogmole: hay enemigos en la pantalla donde hay que quitar los pinchos. No nos vale con detectar esto al entrar, ya que si matamos al último bicho en esta pantalla (puede suceder) necesitaríamos salir y volver a entrar en la pantalla para que el motor se coscase. Necesitamos más código que detecte que hemos matado al último bicho y que se ejecute cuando lo matemos. Recordemos que había una peculiaridad en el motor: cuando pisamos a un bicho se ejecuta la sección PRESS_FIRE AT SCREEN correspondiente a la pantalla actual. Esto nos viene genial: poniendo el mismo código en esta sección que en ENTERING SCREEN solucionamos el problema.

Ni cortos ni perezosos…



PRESS_FIRE AT SCREEN 20

    IF ENEMIES_KILLED_EQUALS 60

    THEN

        SET TILE (2, 7) = 0

        SET TILE (2, 8) = 0

    END

END
Ahora vamos a detectar que “salimos”. Si no hiciésemos nada, saliendo de la pantalla 20 por la izquierda nos encajamos en la pantalla 19… Que además está en la otra punta del mapa. En el juego original, esto estaba solucionado con un hack guarro, pero con la versión actual de **MTE MK1** puede hacerse bien.

Lo primero será definir una zona de fuego que cubra la parte izquierda de la pantalla, de forma que se ejecute la sección PRESS_FIRE AT SCREEN 20 cuando nos acerquemos a ella. Añadimos, pues, la definición de la zona de fuego en la sección ENTERING SCREEN 20 (no nos olvidemos, además, de activar la funcionalidad en config.h). Nos queda así:



ENTERING SCREEN 20

    IF ENEMIES_KILLED_EQUALS 60

    THEN

        SET TILE (2, 7) = 0

        SET TILE (2, 8) = 0

    END



    IF TRUE

    THEN

        SET_FIRE_ZONE 0, 0, 15, 159

    END

END
¿Queda claro? Al entrar en la pantalla 20 pasan dos cosas: primero se comprueba si el número de enemigos vale 60, en cuyo caso se eliminan los tiles-pincho que bloquean la salida. Luego, en cualquier caso (IF TRUE) se define una zona de fuego que cubre todo una tira pegada a la izquierda de 15 pixels de ancho. En cuanto el jugador entre en esta zona (no podrá hacerlo si no se ha eliminado la barrera: simplemente no puede pasar), se ejecutará la sección PRESS_FIRE AT SCREEN 20. Ahora tendremos que añadir código en la sección PRESS_FIRE AT SCREEN 20 para detectar que el jugador está intentando salir por la izquierda y, en ese caso, terminar el juego con éxito. Quedaría así:



PRESS_FIRE AT SCREEN 20

    IF ENEMIES_KILLED_EQUALS 60

    THEN

        SET TILE (2, 7) = 0

        SET TILE (2, 8) = 0

    END

    

    IF PLAYER_IN_X 0, 15

    THEN

        WIN

    END

END
Recapitulemos para que quede bien claro. Veamos lo que pasaría, paso por paso. Imaginemos que llegamos a la pantalla 20 después de haber matado a todos los malos. Esta es la secuencia de acontecimientos:

1. Al entrar en la pantalla 20, después de dibujarla y tal, se ejecuta la sección ENTERING SCREEN 20. En ella, se comprueba que llevamos 60 enemigos matados, cosa que es cierta, y se elimina la barrera. Además, se define una zona de fuego de 15 pixels de ancho en la parte izquierda del área de juego.

2. Se ejecuta el bucle principal del juego. El jugador juega y tal y cual, ve la barrera abierta, y se dirige a la izquierda.

3. Cuando el jugador entra en la zona de fuego, se ejecuta la sección PRESS_FIRE AT SCREEN 20. En ella, se comprueba que llevamos 60 enemigos matados y se elimina la barrera. Esto es redundante y podría evitarse con un flag, pero nos da igual… tampoco se nota. Lo importante es lo que ocurre luego: comprueba que la coordenada X del jugador, en pixels, esté entre 0 y 15, cosa que es cierta (ya que hemos entrado en esta sección por haber entrado en la zona de fuego, que está definida justo en ese area), por lo que ejecuta WIN y se nos muestra el final del güego.

¿Se pilla? ¿Vemos otro? ¿Que quieres ver lo del flag para eliminar la redundancia? Perfecto.

Tenemos todos los flags libres, así que pillaremos el 1. El método es sencillo: lo ponemos a 0 al entrar en la pantalla, a 1 cuando eliminemos la barrera, y sólo eliminaremos la barrera en PRESS_FIRE AT SCREEN 20 si está a 0. Lo pongo todo junto, ya deberías poder seguirlo solo:



ENTERING SCREEN 20

    IF TRUE

    THEN

        SET_FIRE_ZONE 0, 0, 15, 159

        SET FLAG 1 = 0

    END



    IF ENEMIES_KILLED_EQUALS 60

    THEN

        SET TILE (2, 7) = 0

        SET TILE (2, 8) = 0

        SET FLAG 1 = 1

    END

END



PRESS_FIRE AT SCREEN 20

    IF ENEMIES_KILLED_EQUALS 60

    IF FLAG 1 = 0

    THEN

        SET FLAG 1 = 1

        SET TILE (2, 7) = 0

        SET TILE (2, 8) = 0

    END

    

    IF PLAYER_IN_X 0, 15

    THEN

        WIN

    END

END
Ahora sí, vamos a ver otro.

Sgt. Helmet Training Day

Vamos a ver ahora un script un poco más largo, pero igualmente sencillo. En este juego la misión es recoger las cinco bombas, llevarlas a la pantalla del ordenador (pantalla 0) para depositarlas, y luego volver al principio (pantalla 24).
Hay muchas formas de hacer esto. La que usamos nosotros para montarlos es bastante sencilla:

Podemos contar el número de objetos que llevamos desde el script, por lo que las bombas serán objetos normales y corrientes del motor. Las colocamos con el colocador como hotspot de tipo 1.

Cuando lleguemos a la pantalla del ordenador, haremos una animación chula colocando las bombas alrededor. Usamos el colocador porque mola para saber las coordenadas de cada casilla (si pones el ratón sobre una casilla salen las coordenadas arriba del todo) y apuntamos en un papel donde las vamos a pintar.

Usaremos el flag 1 para comprobar que hemos colocado las bombas. Al principio del juego valdrá 0, y lo pondremos a 1 cuando coloquemos las bombas.

Cuando entremos en la pantalla 24, que es la pantalla principal, comprobaremos el valor del flag 1, y si vale 1, terminará el juego.

Además, iremos imprimiendo textos en la pantalla con lo que vamos haciendo. Recordemos que en config.h había tres directivas que mencionamos por encima hace algunos capítulos:



#define LINE_OF_TEXT		0	// If defined, scripts can show text @ Y = #

#define LINE_OF_TEXT_X		1	// X coordinate.

#define LINE_OF_TEXT_ATTR	71	// Attribute
Sirven para configurar donde sale una linea de texto que podremos escribir desde el script con el comando TEXT. Para ello dejamos sitio libre en el marco: fíjate como hay sitio en la fila de arriba, ya que hemos configurado la linea de texto en las coordenadas (x, y) = (1, 0).



Lo primero que hará nuestro script, por tanto, será definir un par de mensajes que aparecerán por defecto al entrar en cada pantalla, dependiendo de valor del flag 1. Esto lo hacemos en la sección ENTERING ANY. Esta sección, recordemos, se ejecuta al entrar en cada pantalla, justo antes de la sección ENTERING SCREEN n correspondiente. Atención a esto: nos permitirá definir un texto general que podamos sobrescribir fácilmente si hace falta para alguna pantalla en concreto, ya que si ponemos texto en ENTERING SCREEN n sobrescribirá el que pusomos en ENTERING ANY al ejecutarse después.

Para imprimir texto en la linea de texto definida, usamos el comando TEXT. El texto que le sigue va sin comillas. Usaremos el carácter de subrayado _ para representar los espacios. Es conveniente, además, rellenar con espacios para que, si hay que sobrescribir un texto largo con uno corto, se borre entero.

La longitud máxima de los textos dependerá de tu marco de juego y de cómo hayas definido su posición. En nuestro caso la hemos colocado en (x, y) = (1, 0) porque tenemos borde a la izquierda y a la derecha, con lo que la longitud máxima será de 30 caracteres.

Escribamos nuestra sección ENTERING ANY, pues. Hemos dicho que imprimiremos un texto u otro dependiendo del valor del flag 1:



ENTERING ANY

    IF FLAG 1 = 0

    THEN

        TEXT BUSCA_5_BOMBAS_Y_EL_ORDENADOR!

    END

    

    IF FLAG 1 = 1

    THEN

        TEXT MISION_CUMPLIDA!_VUELVE_A_BASE

    END

END
No tiene misterio ¿verdad? Si el flag 1 vale 0, o sea, la situación del principio del juego (todos los flags de ponen a 0 al empezar), al entrar en cada pantalla aparecerá el texto “BUSCA 5 BOMBAS Y EL ORDENADOR” en la zona del marco definida para la linea de texto. Si el flag 1 vale 1, cosa que ocurrirá cuando coloquemos las bombas en el ordenador, el texto por defecto que aparecerá al entrar en las pantallas será “MISION CUMPLIDA! VUELVE A BASE”.

Vamos a hacernos un croquis mierder de la pantalla para ver donde va el ordenador y las bombas:



Vamos ahora con la chicha. Lo primero que haremos será escribir las condiciones para la pantalla del ordenador, que es la pantalla 0. En esta pantalla tenemos que hacer varias cosas. Tengámoslas claras antes de empezar:

Siempre que entremos tendremos que pintar el ordenador, que está compuesto por los tiles 32 a 38 del tileset. Lo haremos como hemos visto, con SET TILE.

Además, tendremos que definir un area de fuego alrededor del ordenador para que el juego detecte automáticamente cuando nos acercamos a él.

Si volvemos a entrar en la pantalla después de haber colocado las bombas (puede pasar), tendremos que coscarnos de ello y pintar también las bombas.

Si entramos por primera vez (no hemos puesto las bombas) escribiremos un mensajito de ayuda que diga “PON LAS CINCO BOMBAS Y CORRE”

Si nos acercamos al ordenador, habrá que hacer la animación chula de poner las bombas, y además colocar el flag 1 a 1.

Ahora que tenemos algo de experiencia, nos daremos cuenta que las cuatro primeras cosas se hacen al entrar en la pantalla, y la última al pulsar acción (o entrar en la zona de fuego). Vayamos una por una. Empecemos por las cosas que hay que hacer al entrar en esta pantalla. Me gusta empezar por las cosas que hay que hacer siempre: pintar el ordenador y definir la zona de fuego:



ENTERING SCREEN 0



    # Siempre: pintar el ordenador.

    IF TRUE

    THEN

        SET TILE (6, 3) = 32

        SET TILE (7, 3) = 33

        SET TILE (8, 3) = 34

        SET TILE (6, 4) = 36

        SET TILE (7, 4) = 37

        SET TILE (8, 4) = 38

        SET_FIRE_ZONE 80, 32, 159, 95

    END
Si te fijas, hemos usado las fórmulas que explicamos antes para definir un área amplia alrededor del ordenador. En concreto, el área equivale al rectángulo formado desde el tile (x, y) = (5, 2) hasta el (9, 5). O sea, un reborde de un tile alrededor de los seis tiles que ocupa el ordenador. Coge un papel de cuadritos y te lías menos.
Seguimos: si entramos luego de haber colocado las bombas (algo que puede pasar) tendremos que coscarnos y pintar las bombas. Nada más sencillo:



    # Si ya hemos puesto las bombas: pintarlas.

    IF FLAG 1 = 1

    THEN

        SET TILE (4, 4) = 17

        SET TILE (4, 2) = 17

        SET TILE (7, 1) = 17

        SET TILE (10, 2) = 17

        SET TILE (10, 4) = 17

    END
Nos hemos fijado en el croquis, por supuesto, para saber las posiciones de las bombas. La bomba está en el tile 17, que es el tile que se usa para pintar los objetos, si recordáis.

Ahora solo queda poner un texto de ayuda si no hemos colocado aún las bombas. Fíjate que ocurre lo que dijimos: como esta sección se ejecuta después de ENTERING ANY, el texto que imprimamos aquí sobrescribirá el que ya hubiese. Es por eso, además, que usamos espacios en blanco alrededor: centrarán el texto y eliminarán los caracteres del texto anterior, que es más largo:



    # Si no, mensajito.

    IF FLAG 1 = 0

    THEN

        TEXT _PON_LAS_CINCO_BOMBAS_Y_CORRE_

    END

END
Listo. Ahora sólo queda reaccionar a la zona de fuego, en la sección PRESS_FIRE AT SCREEN 0. Haremos algunas comprobaciones y luego haremos la animación:



PRESS_FIRE AT SCREEN 0

    IF PLAYER_IN_X 80, 159

    IF PLAYER_IN_Y 32, 95

    IF OBJECT_COUNT = 5

    IF FLAG 1 = 0

    THEN

        SET FLAG 1 = 1

        SET TILE (4, 4) = 17

        SHOW

        SOUND 0

        SET TILE (4, 2) = 17

        SHOW

        SOUND 0

        SET TILE (7, 1) = 17

        SHOW

        SOUND 0

        SET TILE (10, 2) = 17

        SHOW

        SOUND 0

        SET TILE (10, 4) = 17

        SHOW

        SOUND 0

        TEXT ____AHORA_VUELVE_A_LA_BASE____

    END

END
Veámoslo poco a poco, porque hay cosas nuevas:

Lo primero es comprobar que estamos donde tenemos que estar (el jugador siempre puede pulsar la tecla acción en vez de entrar en la zona de fuego, y no mola ejecutarlo si el jugador está en cualquier sitio). Eso lo hacemos como ya hemos visto: con PLAYER_IN_X y PLAYER_IN_Y y las mismas coordenadas de la zona de fuego.

Lo siguiente es comprobar que tenemos las cinco bombas, o lo que es lo mismo, que tenemos cinco objetos. Esto se hace con OBJECT_COUNT, que representa el número de objetos que el jugador lleva recogidos.

Por último, muy importante, hay que comprobar que aún no hemos dejado las bombas, o cosas divertidas podrían pasar.
Si se cumplen todas estas condiciones, pondremos el flag 1 a 1 (ya hemos puesto las bombas) y hacemos la animación, que consiste en ir pintando una a una las bombas y tocando un sonido. Ves ahí el comando SHOW, necesario porque los cambios que hagamos en la pantalla no serán visibles hasta que se actualice, cosa que pasa normalmente al volver al bucle principal, pero no en medio de la ejecución de una cláusula. Como queremos que se vea cada bomba justo después de pintarla, llamamos a SHOW. Cada sonido, además, parará la ejecución durante unos instantes (estamos en modo 48K), lo que nos viene genial. Por último, imprimiremos un texto de ayuda, de nuevo con espacios a los lados para completar los 30 caracteres máximos y borrar lo que hubiese del texto anterior.

Y con esto hemos terminado todo lo que había que hacer en la pantalla 0.

Si seguimos con nuestro guión, lo próximo que había que hacer era volver a la pantalla inicial, que es la 24. Lo que queda por hacer es bastante sencillo: consiste en comprobar, al entrar en la pantalla 24, que el flag 1 vale 1. Esto sólo pasará si anteriormente hemos colocado las bombas, por lo que no necesitamos más… Simplemente comprobamos eso y, si se cumple, terminamos el juego con éxito… Nada más sencillo que hacer esto:



ENTERING SCREEN 23

    IF FLAG 1 = 1

    THEN

        WIN

    END

END
¡Ea! Ya tenemos el juego programado. En el script de Sgt. Helmet hay un detalle más: nuestro habitual “vendo moto seminueva”. Pero eso lo dejo ya, no tiene nada de especial: imprimir tiles, definir zona de fuego, detectar posición, y escribir un texto. Todo eso lo sabes hacer ya.

Arf, arf.

Podría seguir, pero mejor lo dejamos por ahora. En el próximo capítulo seguiremos viendo ejemplos paso por paso, pero ya con scripts más complejos como, por ejemplo, el de Cadàveriön. Luego ya seguiremos viendo cosas interesantes, como juegos de 128K, cambiar la música y los efectos, fases comprimidas… Uf, no vamos a terminar nunca.

Entretanto te recuerdo que en el archivo motor_de_clausulas.txt que está en /script puedes ver una lista de los comandos y las comprobaciones disponibles, por si te pica la curiosidad.

¡Hasta otra!