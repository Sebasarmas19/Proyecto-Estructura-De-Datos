🎮 Trivia Quest: Sistema de Gestión de Misiones y Logros
Este proyecto es una aplicación de consola desarrollada en C++ que implementa un sistema completo de trivias basado en misiones. Utiliza estructuras de datos dinámicas (listas enlazadas y multilistas) para gestionar perfiles de usuario, múltiples jugadores por perfil, un sistema de logros y un tablero de clasificación (leaderboard).

🚀 Características Principales
Gestión de Perfiles: Creación, actualización y eliminación de perfiles protegidos por contraseña.

Multijugador por Perfil: Cada perfil puede tener múltiples personajes (jugadores) con estadísticas independientes.
Sistema de Misiones: Misiones categorizadas por dificultad (Fácil, Intermedio, Difícil, Extremo) con requisitos de nivel.

Lógica de Logros:

Automáticos: Basados en el desempeño en las misiones (puntaje perfecto, niveles alcanzados).
Manuales: Posibilidad de asignar distinciones especiales.
Persistencia de Datos: Carga y guardado automático en archivos de texto (.txt) para mantener el progreso de perfiles, misiones y preguntas.
Leaderboard Dinámico: Algoritmo de ordenamiento para mostrar el ranking global de jugadores basado en puntaje y nivel.

🛠️ Detalles Técnicos
El núcleo del proyecto se basa en el uso eficiente de punteros y memoria dinámica:

Estructuras (Structs): Implementación de nodos para Perfil, Player, Mision, Pregunta y Logro.
Multilistas: Relaciones jerárquicas donde un perfil apunta a una lista de jugadores, y cada jugador a una lista de logros.

Algoritmos:

Ordenamiento: Uso de Bubble Sort para organizar el Leaderboard.
Búsqueda: Localización de IDs y validación de credenciales.
Parsing: Procesamiento de cadenas de texto con find y substr para la carga de archivos.

📂 Estructura de Archivos de Datos
El sistema genera y lee los siguientes archivos para la persistencia:

perfiles.txt: Datos de cuentas y seguridad.
jugadores.txt: Estadísticas y vinculación con perfiles.
logros.txt: Registro de hitos alcanzados.
misiones.txt: Configuración de niveles y recompensas.
preguntas.txt: Banco de preguntas asociado a cada misión.

💻 Requisitos y Ejecución
Para ejecutar este proyecto, necesitas un compilador de C++ (como GCC o Clang).
