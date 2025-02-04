
README_CHECK_MAP


Estos archivos son responsables de:

Leer el mapa desde el archivo de configuración.
Almacenar el mapa en game->map.
Validar que el mapa solo contenga caracteres permitidos.
Asegurar que el mapa esté cerrado (es decir, que no haya bordes abiertos).
Verificar que haya exactamente una posición de inicio del jugador.
Versión Original (Con Errores)
La versión original de las funciones de manejo del mapa incluía lógica extra y varias comprobaciones complejas (por ejemplo, verificar caracteres adyacentes, rellenar el mapa con espacios y múltiples validaciones), lo que provocó varios problemas:

Parsing Excesivamente Complejo:
El código intentaba manejar diferentes estados (antes del mapa, mientras se leía el mapa, después del mapa) usando varios flags y condiciones.
Esta complejidad a menudo hacía que el análisis fallara cuando se encontraba con líneas que no seguían estrictamente el formato esperado (como espacios adicionales o líneas en blanco).
Comprobaciones Fuera de Rango:
Al verificar los muros, la función comprobaba caracteres vecinos (por ejemplo, game->map[y][x - 1], game->map[y][x + 1], etc.) sin asegurarse de que esos índices existieran.
Esto podía provocar accesos a memoria inválidos y errores falsos como "Map not closed properly" (Mapa no cerrado correctamente).
Problemas de Manejo de Memoria y Cadenas:
La lógica para rellenar las líneas con espacios (para igualar sus longitudes) y luego verificar cada carácter conducía a posibles inconsistencias.
El manejo de la concatenación de cadenas para construir el mapa no era robusto, lo que provocaba que game->map a veces permaneciera en NULL, incluso cuando había un mapa válido presente.
Versión Corregida (Funcional)
La versión revisada simplifica el proceso considerablemente al hacer lo siguiente:

Extracción Más Simple del Mapa:
Lee el archivo línea por línea.
Hasta que se detecta la primera línea del mapa (una que comienza con '1' o '0'), la función guarda la información de texturas y colores.
Una vez detectada una línea del mapa, todas las líneas posteriores que comienzan con '1' o '0' se concatenan en una cadena de resultado.
Almacenamiento Fiable:
Después de leer el archivo, la cadena de resultado se divide por caracteres de nueva línea (\n) para formar game->map.
Se agrega una verificación para asegurarse de que, si no se encuentra un mapa válido, se genere un error.
Validación Mejorada:
La nueva versión de la función de verificación de muros (en check_map.c) solo verifica que los caracteres pertenezcan al conjunto permitido y que ningún borde del mapa o espacio adyacente comprometa el cierre del mapa.
El código que inicializa la posición del jugador también se ha simplificado, contando solo la primera aparición de una dirección válida (N, S, W, E).
¿Qué Se Corrigió y Por Qué?
Manejo de Estados:
Los múltiples flags y estados de la versión original fueron eliminados.
Ahora, la variable game->start_map simplemente se establece cuando se encuentra una línea de mapa válida.
Esto evita que el código termine prematuramente o que interprete incorrectamente líneas en blanco.
Concatenación Segura de Líneas del Mapa:
El nuevo código usa funciones auxiliares (como append_map_line o directamente ft_strjoin) para construir la cadena completa del mapa de manera segura.
La memoria se gestiona cuidadosamente al liberar las cadenas temporales, lo que garantiza que no haya fugas de memoria.
Verificación de Límites y Validación:
La validación de muros ahora verifica solo los bordes del mapa (superior, inferior, izquierda, derecha) sin realizar verificaciones fuera de los límites.
Al evitar el relleno innecesario del mapa, se reduce el riesgo de leer memoria no válida.
Mensajes de Error Más Claros y Código Más Robusto:
Se proporcionan mensajes de error claros y descriptivos cuando faltan datos en el mapa o en las texturas.
El flujo del código ahora es más lineal y fácil de depurar, lo que es especialmente útil para programadores principiantes.
Conclusión
El código original de manejo del mapa fallaba debido a: ❌ Manejo de estados innecesariamente complejo.
❌ Comprobaciones de vecinos que podían acceder a memoria fuera de los límites.
❌ Manejo deficiente de memoria y concatenación de cadenas.

La versión corregida funciona correctamente porque:
✅ Simplifica la lógica del análisis separando claramente la extracción de texturas/colores de la lectura del mapa.
✅ Usa métodos de concatenación seguros para construir la cadena final del mapa.
✅ Valida el mapa de una manera más robusta con verificaciones de límites seguras y mensajes de error claros.

