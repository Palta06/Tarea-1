# Sistema de Gestión de Tickets

## Descripción

Este sistema permite a los usuarios gestionar el registro de tickets. Los usuarios pueden registrar nuevos tickets, asignar prioridades, ver la lista de pendientes, y más. Esta herramienta está diseñada para mejorar la eficiencia en el procesamiento de los tickets, asegurando que aquellos tickets con prioridades altas sean procesados lo más pronto posible.

## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack** de Microsoft. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

### Requisitos previos:

- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como **gcc**). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).

### Pasos para compilar y ejecutar:

1. **Descarga y descomprime el repositorio de GitHub.**
2. **Abre el proyecto en Visual Studio Code**
    - Inicia Visual Studio Code.
    - Selecciona `Archivo > Abrir carpeta...` y elige la carpeta donde descomprimiste el proyecto.
3. **Compila el código**
    - Abre el archivo principal (por ejemplo, `main.c`).
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal, compila el programa con el siguiente comando (ajusta el nombre si el archivo principal tiene otro nombre):
        
        ```powershell
        gcc tarea1.c TDAs/list.c -o tarea1
        ```
        
4. **Ejecuta el programa**
    - Una vez compilado, puedes ejecutar la aplicación con:
        
        ```
        ./tarea1.exe
        ```
        

## Funcionalidades

### Funcionando correctamente:

- Registrar tickets con su descripción, hora de registro y una prioridad inicial.
- Asignar o modificar la prioridad de los tickets.
- Ver la lista de tickets pendientes, ordenada por prioridad y hora de registro.
- Procesar siguiente ticket, respetando el orden de prioridad.

### Problemas conocidos:

- El codigo puede llegar a presentar problemas en caso de que a la hora de ingresar el ID, este sea muy grande.

### A mejorar:

- El ID del ticket que debe ingresar el usuario puede ser muy abstracto, ya que no especifica ni su tamaño, ni si este incluye solo letras o solo números.
- No Permite la edición de la descripción de los tickets.

## Ejemplo de uso

**Paso 1: Registrar un Nuevo Ticket**

Se comienza registrando un nuevo ticket.

```
Opción seleccionada: 1) Registrar ticket
Ingrese el ID del ticket: 423
Ingrese la descripción del ticket: Fallo en la batería
```

El sistema registra el ticket con una prioridad inicial "Bajo" y guarda la hora actual de registro. La prioridad inicial puede ser ajustada más tarde.

**Paso 2: Asignar Prioridad a un Ticket**

En caso de que queramos modificar la prioridad del ticket.

```
Opción seleccionada: 2) Asignar prioridad a ticket
Ingrese el ID del ticket: 423
Seleccione el nuevo nivel de prioridad (Alto, Medio, Bajo): Alto
```

El sistema actualiza la prioridad del ticket 423 a "Alto", asegurando que será una de los próximos tickets en ser atendido.

**Paso 3: Ver la Lista de Espera**

El usuario revisa la lista de espera para ver todos los tickets y sus prioridades.

```
Opción seleccionada: 3) Mostrar lista de espera
```

La lista muestra el ticket 423 en la parte superior, indicando su prioridad alta, el problema que tiene y que es el siguiente en línea para recibir atención.

**Paso 4: Atender al Siguiente Ticket**

El ticket 423 está siendo procesado basándose en su prioridad.

```
Opción seleccionada: 4) Atender al siguiente Ticket
```

El sistema muestra que el ticket 423 está siendo atendido y lo elimina de la lista de espera.
