## - Determinación de la Dirección del Rayo en Raycasting


## Define cómo y cuándo el rayo cruza las celdas del mapa, asegurando que se detecten las paredes correctamente y la escena se vea bien.


##  Descripción
Esta función se encarga de determinar en qué dirección se moverá el rayo en los ejes **X** e **Y**, estableciendo el valor de `step_x` y `step_y`. También calcula la distancia inicial hasta la siguiente intersección con una línea del mapa en cada eje.

##  Parámetros
- `t_cub *game`: Puntero a la estructura principal del juego que contiene información sobre el jugador, el mapa y los rayos.
- `int x`: Índice de la columna en la pantalla donde se lanza el rayo.

## **🔹 Obtención del rayo correspondiente**

`ray = &game->rays[x];`

Se obtiene el puntero al rayo correspondiente a la columna `x` de la pantalla.  
Cada rayo representa una línea proyectada desde la vista del jugador.

#### **Ejemplo:**
Si `x = 50`, entonces `ray` apunta a `game->rays[50]`, que almacena los datos del rayo para esa columna.


## **🔹 Definición del sentido del paso en el eje X**
```c
if (ray->delta_x < 0)
{
    ray->step_x = -1;
    ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
}
else
{
    ray->step_x = 1;
    ray->side_dist_x = (ray->map_x + 1.0 - game->player->x) * ray->delta_dist_x;
}
```
- `step_x` indica si el rayo **se mueve hacia la izquierda (-1) o hacia la derecha (+1)**.
- `side_dist_x` almacena la distancia inicial **desde la posición del jugador hasta la primera intersección con una línea vertical**.

### **Explicación detallada**
- Si `delta_x < 0`, significa que el rayo se mueve **hacia la izquierda**, por lo que:
  - `step_x = -1`, indicando que cada paso reducirá `map_x`.
  - `side_dist_x` se calcula como la distancia desde la posición actual del jugador hasta el borde izquierdo de la celda.

- Si `delta_x >= 0`, significa que el rayo se mueve **hacia la derecha**, por lo que:
  - `step_x = 1`, indicando que cada paso aumentará `map_x`.
  - `side_dist_x` se calcula como la distancia desde la posición actual del jugador hasta el borde derecho de la celda.

#### **Ejemplo:**
Si el jugador está en `x = 4.7` dentro de la celda `4`:
- Si el rayo va **hacia la izquierda**, `side_dist_x = (4.7 - 4) * delta_dist_x`.
- Si el rayo va **hacia la derecha**, `side_dist_x = (5 - 4.7) * delta_dist_x`.

## **🔹 Definición del sentido del paso en el eje Y**
```c
if (ray->delta_y < 0)
{
    ray->step_y = -1;
    ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
}
else
{
    ray->step_y = 1;
    ray->side_dist_y = (ray->map_y + 1.0 - game->player->y) * ray->delta_dist_y;
}
```
- `step_y` indica si el rayo **se mueve hacia arriba (-1) o hacia abajo (+1)**.
- `side_dist_y` almacena la distancia inicial **desde la posición del jugador hasta la primera intersección con una línea horizontal**.

### ** Explicación detallada**
- Si `delta_y < 0`, significa que el rayo se mueve **hacia arriba**, por lo que:
  - `step_y = -1`, indicando que cada paso reducirá `map_y`.
  - `side_dist_y` se calcula como la distancia desde la posición del jugador hasta el borde superior de la celda.

- Si `delta_y >= 0`, significa que el rayo se mueve **hacia abajo**, por lo que:
  - `step_y = 1`, indicando que cada paso aumentará `map_y`.
  - `side_dist_y` se calcula como la distancia desde la posición del jugador hasta el borde inferior de la celda.

#### **Ejemplo:**
Si el jugador está en `y = 3.2` dentro de la celda `3`:
- Si el rayo va **hacia arriba**, `side_dist_y = (3.2 - 3) * delta_dist_y`.
- Si el rayo va **hacia abajo**, `side_dist_y = (4 - 3.2) * delta_dist_y`.

## **Importancia de estos cálculos en el Raycasting**
1. **Determinan la dirección en la que el rayo se moverá en el mapa.**  
   - `step_x` y `step_y` permiten que el algoritmo DDA sepa si el rayo debe moverse hacia adelante o hacia atrás en cada eje.

2. **Calculan la distancia inicial hasta la primera intersección.**  
   - `side_dist_x` y `side_dist_y` permiten saber cuánto debe avanzar el rayo antes de cruzar una línea en el mapa.

3. **Garantizan que el raycasting funcione correctamente en cualquier dirección.**  
   - Sin estos cálculos, el rayo podría moverse en la dirección equivocada o quedar atrapado sin avanzar.


## **Resumen**
```md
| Condición                | Movimiento en X / Y | Valor de `step` | Cálculo de `side_dist` |
|--------------------------|--------------------|----------------|------------------------|
| `delta_x < 0`           | Izquierda          | `step_x = -1`  | `(player_x - map_x) * delta_dist_x` |
| `delta_x >= 0`          | Derecha            | `step_x = 1`   | `(map_x + 1.0 - player_x) * delta_dist_x` |
| `delta_y < 0`           | Arriba             | `step_y = -1`  | `(player_y - map_y) * delta_dist_y` |
| `delta_y >= 0`          | Abajo              | `step_y = 1`   | `(map_y + 1.0 - player_y) * delta_dist_y` |
```

Este cálculo es fundamental en el algoritmo de raycasting, ya que **define cómo avanzará el rayo en el mapa y en qué momento cruzará las líneas de las celdas**. 🚀


***************************

# Lo más importantes

## 🔹 1. Determinar si el rayo se mueve a la izquierda o derecha (`step_x`)
```c
if (ray->delta_x < 0)
    ray->step_x = -1;
else
    ray->step_x = 1;
```
### ¿Por qué es importante?
- Define si el rayo avanza **hacia la izquierda (-1)** o **hacia la derecha (+1)** en el mapa.
- `step_x` es clave para saber **cómo moverse en el eje X** cada vez que el rayo avanza.

###🔹 ¿Qué fallaría sin esto?
- El rayo **no avanzaría correctamente** y se quedaría atrapado sin moverse en la dirección correcta.
- Podría moverse al revés, haciendo que el **raycasting renderice paredes incorrectas**.

---

## 🔹 2. Determinar si el rayo se mueve hacia arriba o abajo (`step_y`)
```c
if (ray->delta_y < 0)
    ray->step_y = -1;
else
    ray->step_y = 1;
```
###  ¿Por qué es importante?
- Define si el rayo se mueve **hacia arriba (-1)** o **hacia abajo (+1)** en el mapa.
- `step_y` es clave para saber **cómo moverse en el eje Y** cada vez que el rayo avanza.

### 🔹 ¿Qué fallaría sin esto?
- El rayo **no cruzaría celdas correctamente** en el eje Y.
- Se movería en una dirección incorrecta, causando **errores en la detección de colisiones con paredes**.

---

## 🔹 3. Calcular la distancia hasta la primera línea vertical (`side_dist_x`)
```c
if (ray->delta_x < 0)
    ray->side_dist_x = (game->player->x - ray->map_x) * ray->delta_dist_x;
else
    ray->side_dist_x = (ray->map_x + 1.0 - game->player->x) * ray->delta_dist_x;
```
###  ¿Por qué es importante?
- Determina **cuánto falta para que el rayo toque la primera línea vertical** en el mapa.
- Se usa en el **algoritmo DDA** para avanzar en X correctamente.

### 🔹 ¿Qué fallaría sin esto?
- El rayo **no sabría cuándo cruzar una línea en X**, por lo que **no detectaría correctamente las paredes**.
- Sin `side_dist_x`, **el raycasting no funcionaría en direcciones diagonales**.

---

## 🔹 4. Calcular la distancia hasta la primera línea horizontal (`side_dist_y`)
```c
if (ray->delta_y < 0)
    ray->side_dist_y = (game->player->y - ray->map_y) * ray->delta_dist_y;
else
    ray->side_dist_y = (ray->map_y + 1.0 - game->player->y) * ray->delta_dist_y;
```
###  ¿Por qué es importante?
- Determina **cuánto falta para que el rayo toque la primera línea horizontal** en el mapa.
- Se usa en el **algoritmo DDA** para avanzar en Y correctamente.

### 🔹 ¿Qué fallaría sin esto?
- El rayo **no sabría cuándo cruzar una línea en Y**, por lo que **detectaría mal las paredes**.
- **Si el rayo se mueve en diagonal, fallaría completamente**.

---

Si esta función **no existiera o estuviera mal implementada**, el raycasting tendría los siguientes problemas:

 **No avanzaría correctamente en el mapa**.
 **No detectaría bien las paredes** y el renderizado sería incorrecto.
 **Podría entrar en bucles infinitos** si el rayo no sabe cuándo cruzar en X o Y.
 **Los movimientos del rayo serían impredecibles**, causando errores en el renderizado del mundo.

---

## 🔹 Conclusión
esta es **esencial para que el raycasting funcione correctamente**. Define **cómo y cuándo el rayo cruza cada celda del mapa**, asegurando que **detecte correctamente las paredes y renderice la escena sin errores**.

Sin ella, **el algoritmo de raycasting fallaría completamente**. 🚀

