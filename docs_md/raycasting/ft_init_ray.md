# ft_init_ray - Inicialización de un Rayo en Raycasting

## Descripción
Esta función inicializa los datos de un rayo para la columna `x` de la pantalla. 
Se usa en el algoritmo de raycasting para determinar la dirección y posición del rayo.

## Parámetros
- `t_cub *game`: Puntero a la estructura principal del juego que contiene información sobre el jugador, el mapa y los rayos.
- `int x`: Índice de la columna en la pantalla donde se lanza el rayo.
- `double ray_angle`: Ángulo del rayo en radianes que define su dirección.

### Obtención del rayo correspondiente

`ray = &game->rays[x];`		Se obtiene el puntero al rayo correspondiente a la columna `x` de la pantalla.
							Cada rayo representa una línea proyectada desde la vista del jugador.
							####Ejemplo####:
							Si `x = 50`, entonces `ray` apunta a `game->rays[50]`, que almacena los datos del rayo para esa columna.

### Asignación del ángulo del rayo
`ray->ray_angle = ray_angle;`	Se almacena el ángulo del rayo. 
								Que se usará para determinar su dirección en el espacio del juego.
								####Ejemplo###:
								Si el jugador mira a 90° y el FOV es 60°, el primer rayo a la izquierda tendrá un ángulo de 60° y el último un ángulo de 120°.

### Cálculo de dirección del rayo

`ray->delta_x = cos(ray_angle);`
`ray->delta_y = sin(ray_angle);`	Se calculan los valores de desplazamiento en los ejes X e Y.
									- `cos(ray_angle)`: Determina cuánto avanza el rayo en el eje X.
									- `sin(ray_angle)`: Determina cuánto avanza el rayo en el eje Y.
									####Ejemplo####:
									- Si ``` ray_angle = 0°```, el rayo avanza solo en X.
									- Si `ray_angle = 90°`, el rayo avanza solo en Y.
									- Si `ray_angle = 45°`, el rayo avanza en diagonal con un movimiento equilibrado entre X e Y.

### Ubicación inicial del rayo en el mapa
`ray->map_x = (int)game->player->x;`
`ray->map_y = (int)game->player->y;`	Convierte las coordenadas flotantes del jugador a enteros.
										Para determinar en qué celda del mapa se encuentra.
										####Ejemplo####:
										- Si el jugador está en `(4.7, 3.2)`, la conversión da `(4,3)`, indicando la celda del mapa en la que está ubicado.


### Manejo de división por cero y cálculo de distancias diferenciales
```c
if (ray->delta_x == 0)
{
    ray->delta_dist_x = 1e30;
}
else
{
    ray->delta_dist_x = fabs(1 / ray->delta_x);
}

if (ray->delta_y == 0)
{
    ray->delta_dist_y = 1e30;
}
else
{
    ray->delta_dist_y = fabs(1 / ray->delta_y);
}
```

### 
calcula **cuánto debe avanzar el rayo** en los ejes X e Y antes de chocar con la siguiente línea del mapa. También **evita la división por 0** cuando el rayo es completamente vertical u horizontal.

### 

```c
if (ray->delta_x == 0)
    ray->delta_dist_x = 1e30;  		// Un número muy grande para evitar errores matemáticos

			- Si `delta_x == 0`, significa que el rayo **no se mueve en el eje X**, solo en Y (vertical).
			- Si intentáramos calcular `1 / delta_x`, obtendríamos **una división por 0**, lo que es un error en C.
			- Para evitarlo, asignamos `ray->delta_dist_x = 1e30`, lo que significa que el rayo **prácticamente nunca tocará una línea vertical**.

else
    ray->delta_dist_x = fabs(1 / ray->delta_x);

			- Si `delta_x` **no** es 0, podemos calcular `delta_dist_x` sin problema.
			- `fabs(1 / delta_x)` se usa para obtener **siempre un valor positivo**.

if (ray->delta_y == 0)
    ray->delta_dist_y = 1e30;

			- Si `delta_y == 0`, significa que el rayo **no se mueve en el eje Y**, solo en X (horizontal).
			- De nuevo, para evitar **división por 0**, asignamos un número muy grande.

else
    ray->delta_dist_y = fabs(1 / ray->delta_y);

			- Si `delta_y` **no** es 0, podemos calcular `delta_dist_y` sin problema.
			- `fabs(1 / delta_y)` asegura que el valor sea **positivo**.

```c

-Para qué se hacen estos if - else?
	Para evitar división por cero.

Cuando delta_x == 0 o delta_y == 0, intentar calcular 1 / delta_x o 1 / delta_y generaría un error de división por 0.
	Se asigna un valor muy grande (1e30) para indicar que el rayo prácticamente nunca cruzará una línea en esa dirección, lo que es correcto si el rayo es completamente vertical u horizontal.
	Para garantizar que las distancias sean siempre positivas.

Como delta_x y delta_y pueden ser negativos. 
	Dependiendo de la dirección del rayo, calcular 1 / delta_x podría dar un resultado negativo.
	Se usa fabs(1 / delta_x) y fabs(1 / delta_y) para asegurar que delta_dist_x y delta_dist_y siempre sean positivos.
	Para determinar correctamente el avance del rayo en el mapa.

delta_dist_x y delta_dist_y representan la distancia hasta la próxima celda en los ejes X e Y.
	Si delta_dist_x < delta_dist_y, el rayo avanza en X antes de cruzar en Y.
	Si delta_dist_y < delta_dist_x, el rayo avanza en Y antes de cruzar en X.

Esto es fundamental para que el algoritmo DDA (Digital Differential Analyzer) funcione correctamente.
Para permitir que el raycasting funcione en cualquier dirección.

Sin estos if - else, el raycasting solo funcionaría en ciertas direcciones y fallaría cuando el rayo sea exactamente vertical (90° o 270°) u horizontal (0° o 180°).
Al manejar estos casos especiales, el rayo se mueve correctamente sin importar el ángulo.
```