# `ft_dda`

Esta función **implementa el algoritmo DDA (Digital Differential Analyzer)**, que se usa en raycasting para determinar el primer punto de colisión del rayo con una pared en el mapa. Esencialmente, esta función hace que el rayo avance celda por celda hasta que encuentre una pared.

## 🔹 Parámetros
- `t_cub *game`: Puntero a la estructura del juego que contiene el mapa, el jugador y los rayos.
- `int x`: Índice de la columna de la pantalla donde se lanza el rayo.

## **🔹 Obtención del rayo correspondiente**

`ray = &game->rays[x];`		Se obtiene el puntero al rayo de la columna `x` de la pantalla. 
							Cada rayo representa una línea proyectada desde la vista del jugador.

## **🔹 Bucle principal del DDA**
```c
while (1)
```
				Este bucle se ejecuta **indefinidamente** hasta que el rayo encuentre una pared. En cada iteración, se calcula si el rayo avanza en X o en Y.

## **🔹 Determinar si se avanza en X o en Y**
```c
if (ray->side_dist_x < ray->side_dist_y)
```
				- Si `side_dist_x` es menor, significa que **el siguiente borde vertical (línea en X) está más cerca**.
				- En caso contrario, significa que **el siguiente borde horizontal (línea en Y) está más cerca**.

### 🔹 Si el siguiente borde en X es más cercano
`ray->side_dist_x = ray->side_dist_x + ray->delta_dist_x;`
`ray->map_x = ray->map_x + ray->step_x;`

				- Se actualiza `side_dist_x`, sumando `delta_dist_x`.
				- Se avanza una celda en `X`, sumando `step_x`.

#### **Marcar el lado impactado**
```c
if (ray->step_x == -1)
    ray->side = WEST;
else
    ray->side = EAST;
```
				- Si `step_x` es negativo, el rayo venía **desde la derecha y ha chocado con una pared al oeste**.
				- Si `step_x` es positivo, el rayo venía **desde la izquierda y ha chocado con una pared al este**.

### 🔹 Si el siguiente borde en Y es más cercano
`ray->side_dist_y = ray->side_dist_y + ray->delta_dist_y;`
`ray->map_y = ray->map_y + ray->step_y;`

			- Se actualiza `side_dist_y`, sumando `delta_dist_y`.
			- Se avanza una celda en `Y`, sumando `step_y`.

#### **Marcar el lado impactado**
```c
if (ray->step_y == -1)
    ray->side = NORTH;
else
    ray->side = SOUTH;
```
			- Si `step_y` es negativo, el rayo venía **desde abajo y ha chocado con una pared al norte**.
			- Si `step_y` es positivo, el rayo venía **desde arriba y ha chocado con una pared al sur**.

```c
if (game->map[ray->map_y][ray->map_x] == '1')
    break;
```
			- Si la celda en la que ha entrado el rayo **es una pared ('1')**, el bucle se detiene.
			- **Este es el punto de colisión que necesitamos para calcular la proyección en pantalla.**

## esta función permite determinar la primera colisión del rayo con una pared.**
 **Hace que el raycasting funcione correctamente, moviéndose celda por celda hasta encontrar una pared.**
**Es un componente esencial del renderizado 3D basado en mapas 2D.**

## **🔹 Ejemplo práctico**
### **Escenario**
- El jugador está en `(3.5, 2.0)` dentro de una celda.
- `step_x = 1` (el rayo avanza a la derecha), `step_y = -1` (el rayo avanza hacia arriba).
- `side_dist_x = 1.2`, `side_dist_y = 0.8`.

### **Iteraciones del bucle**
 `side_dist_y < side_dist_x`, avanza en `Y`: `(3, 1)`  →  `side = NORTH`  
 `side_dist_x < side_dist_y`, avanza en `X`: `(4, 1)`  →  `side = EAST`  
 `side_dist_y < side_dist_x`, avanza en `Y`: `(4, 0)`  →  **colisión con pared** 

Después de 3 iteraciones, el rayo choca con la pared en `(4,0)`, y el algoritmo se detiene.

