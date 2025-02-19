

## 
Esta función **calcula la distancia real** desde el jugador hasta el punto donde el rayo choca con una pared.Permite que la proyección en la pantalla sea correcta, evitando distorsiones en la perspectiva.

## 🔹 Parámetros
- `t_cub *game`: Estructura principal del juego que contiene toda la información.
- `int x`: Índice de la columna de la pantalla donde se lanza el rayo.

## **🔹 Obtención del rayo correspondiente**
`ray = &game->rays[x];`

Se obtiene el puntero al rayo de la columna `x` de la pantalla. Cada rayo representa una línea proyectada desde la vista del jugador.


## **🔹 Cálculo de la distancia real a la pared**
```c
if (ray->side == EAST || ray->side == WEST)
    ray->perpection_distance = (ray->map_x - game->player->x + (1 - ray->step_x) / 2.0) / ray->delta_x;
else
    ray->perpection_distance = (ray->map_y - game->player->y + (1 - ray->step_y) / 2.0) / ray->delta_y;
```

### ESTA PARTE DEL CODIGO -> Determina si la colisión fue con una pared vertical u horizontal.**
	- **Calcula la distancia corregida** teniendo en cuenta la perspectiva del jugador.
	- **Corrige el efecto de distorsión**, dividiendo la diferencia de posición entre la celda del mapa y el jugador entre la dirección en la que avanza el rayo (`delta_x` o `delta_y`).



#### ** Si la colisión es con una pared vertical  (`EAST` o `WEST`)**
```c
ray->perpection_distance = (ray->map_x - game->player->x + (1 - ray->step_x) / 2.0) / ray->delta_x;
```
- `ray->map_x - game->player->x`: Calcula la diferencia en X entre el jugador y la celda del mapa donde choca el rayo.
- `(1 - ray->step_x) / 2.0`: Ajusta el punto de colisión al centro de la celda.
- **Dividido por `ray->delta_x` para corregir la perspectiva.**

#### **Si la colisión es con una pared horizontal (`NORTH` o `SOUTH`)**
```c
ray->perpection_distance = (ray->map_y - game->player->y + (1 - ray->step_y) / 2.0) / ray->delta_y;
```
- `ray->map_y - game->player->y`: Calcula la diferencia en Y entre el jugador y la celda del mapa donde choca el rayo.
- `(1 - ray->step_y) / 2.0`: Ajusta el punto de colisión al centro de la celda.
- **Dividido por `ray->delta_y` para corregir la perspectiva.**


**Corrige la distorsión de la perspectiva**, evitando que las paredes se vean deformadas.
**Es clave para calcular la proyección de la escena en pantalla.**
**Permite que las paredes cercanas se vean más grandes y las lejanas más pequeñas.**


## **🔹 Ejemplo práctico**
### **Escenario**
- El jugador está en `(3.5, 2.0)` dentro de una celda.
- El rayo impacta en una pared a `map_x = 6`.
- `ray->step_x = 1` porque el rayo va hacia la derecha.
- `ray->delta_x = 0.5` porque el rayo avanza lentamente en X.

### **Cálculo de `perpection_distance`**
```c
(6 - 3.5 + (1 - 1) / 2.0) / 0.5 = (2.5 + 0) / 0.5 = 5.0
```
Esto significa que la distancia real del rayo hasta la pared es **5.0 unidades**, lo que se usará para escalar la proyección en pantalla correctamente.

---

## **🔹 Conclusión**
Esta función es **fundamental para que el raycasting funcione bien**. Si no se hiciera este cálculo:
 **Las paredes se verían distorsionadas.**
**El tamaño de las paredes no sería realista.**
**El renderizado en pantalla fallaría.**


