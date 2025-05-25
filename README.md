# GraphQuest

GraphQuest es un juego de consola donde el jugador recorre un laberinto representado como un grafo de escenarios conectados. En cada escenario se pueden encontrar ítems, tomar decisiones y avanzar, todo mientras se gestiona un inventario limitado por peso y se intenta maximizar el puntaje antes de que se agote el tiempo.

---------------------------------------------------------------------------------

## Estructura del Proyecto

├──base **Definiciones de estructura de mis escenarios y jugador, ademas de las funciones y grafos que se utilizan en el juego**
├──data    **Archivo donde estan los escenarios e items (formato CSV)**
├── logica    **Definición de mis funciones generales, y relacionadas con los grafos**
├── tdas  **Funciones de tdas, son las mismas que en tareas pasadas, solo que agregue los de map, y algunas extra para la lecturadel       archivo csv, los diferentes split para las separaciones**
├── main.c     **Menú principal del programa**  
└── README.md  **Este archivo**

---------------------------------------------------------------------------------

## ¿Cómo compilar y ejecutar?
* Requisitos: Tener gcc instalado en tu sistema (puedes usar MinGW en Windows o gcc en Linux/macOS).*

Se compila el programa ejecutando el siguiente comando en la terminal (cmd o bash):

gcc -Ibase -Itdas -Ilogica main.c logica/funciones.c logica/grafo.c tdas/map.c tdas/list.c tdas/extra.c -o graphquest.exe -lm

**Esto creara un ejecutable**
*Luego ejecuta el programa así:*

./graphquest

---------------------------------------------------------------------------------

# Funciones implementadas : 

1) Mostrar información actual: Ver el escenario actual, los ítems disponibles y el estado del jugador.

2) Recoger ítems: Agregar ítems al inventario, respetando el límite de peso.

3) Descartar ítems: Eliminar ítems del inventario para liberar peso.

4) Avanzar: Moverse a otro escenario (norte, sur, este, oeste) si existe una conexión.

5) Ver puntaje: Mostrar el puntaje actual del jugador basado en ítems recogidos.

6) Terminar juego: Salir del juego antes de que el tiempo se agote.

7) Cargar CSV de laberinto: Automáticamente al inicio desde laberinto.csv.

---------------------------------------------------------------------------------

## Funcionalidades con detalles o mejoras pendientes

-⚠️ Tiempo restante: Aunque se gestiona en la estructura, podría no actualizarse correctamente en todos los movimientos.(como ejemplo cuando, haces un movimiento incorrecto, este no te lo cuenta como movimiento, por lo que no se resta el tiempo).

-⚠️ Final del juego: Si el escenario final se alcanza, no se muestra una pantalla de victoria ni un mensaje especial.(no tuve imaginacion para agregarle algo, es bastante simple la verdad).

-⚠️Tambien pude ver que algunos textos, como cuando llega a la cocina, la descripcion se puede notar un error con respecto a las tildes, ya que como el compilador no acepta esos caracteres de forma nativa, intente agregar el <locale>, pero por lo visto no funciona, no sabria como arreglar ese detalle tampoco.

---------------------------------------------------------------------------------

# 💡 Ejemplo de uso(no es estrictamente así, pero contiene las mismas funcionalidades):

====== Graphquest ======
1. Inicia la partida
2. Salir
Seleccione una opcion:

**seleccionas 1**

=== Estado del Jugador ===
Tiempo restante: 10
Peso total: 0
Puntaje total: 0
Escenario actual: Entrada principal
Descripcion: Una puerta rechinante abre paso a esta mansion olvidada por los dioses y los conserjes. El aire huele a humedad y a misterios sin resolver.     
Caminos disponibles: [1: Abajo]
Items en el escenario:

Inventario:
==========================

========== MENU ==========
1. Recoger items
2. Descartar items
3. Avanzar (moverse)
4. Reiniciar jugador
0. Salir
Seleccione una opcion:

**seleccionas 3**

Direcciones:
0 = Arriba, 1 = Abajo, 2 = Izquierda, 3 = Derecha
Ingrese direccion:

**seleccionas 1**

=== Estado del Jugador ===
Tiempo restante: 9
Peso total: 0
Puntaje total: 0
Escenario actual: Cocina
Descripcion: Restos de una batalla culinaria. Cuchillos por aqui, migajas por alla. Alguien cocinoâ?¦ o fue cocinado.
Caminos disponibles: [0: Arriba] [1: Abajo] [3: Derecha]
Items en el escenario:
- Cuchillo (valor: 3, peso: 1)
- Pan (valor: 2, peso: 1)

Inventario:
==========================

========== MENU ==========
1. Recoger items
2. Descartar items
3. Avanzar (moverse)
4. Reiniciar jugador
0. Salir
Seleccione una opcion:

**seleccionas 1**

1. Cuchillo (valor: 3, peso: 1)
2. Pan (valor: 2, peso: 1)
Seleccione el numero del item a recoger (0 para cancelar):

**seleccionas 1**

=== Estado del Jugador ===
Tiempo restante: 9
Peso total: 1
Puntaje total: 3
Escenario actual: Cocina
Descripcion: Restos de una batalla culinaria. Cuchillos por aqui, migajas por alla. Alguien cocinoâ?¦ o fue cocinado.
Caminos disponibles: [0: Arriba] [1: Abajo] [3: Derecha]
Items en el escenario:
- Pan (valor: 2, peso: 1)

Inventario:
- Cuchillo (valor: 3, peso: 1)
==========================

========== MENU ==========
1. Recoger items
2. Descartar items
3. Avanzar (moverse)
4. Reiniciar jugador
0. Salir
Seleccione una opcion:

**seleccionas 0**

Gracias por jugar GraphQuest.
Presione enter para continuar...

---------------------------------------------------------------------------------