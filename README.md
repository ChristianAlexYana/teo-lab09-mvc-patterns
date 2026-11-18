# Práctica de Laboratorio N.° 09 — Patrones de diseño y MVC con Qt

Universidad Nacional de San Agustín de Arequipa · Tecnología de Objetos · EPIS

Aplicación de seguimiento académico (tareas, exámenes y proyectos) con
arquitectura **MVC**, **Factory Method** (creacional) y, en la siguiente etapa,
**Adapter** (estructural) para importar un CSV heredado.

## Integrantes

| Integrante | Usuario GitHub |
|---|---|
| _Nombre 1_ | _@usuario1_ |
| _Nombre 2_ | _@usuario2_ |

## Estado del avance (≈30 %)

| Entregable | Estado |
|---|---|
| Modelo (Actividad, IRepositorio, RepositorioActividades) | Hecho |
| Factory Method (Tarea / Examen / Proyecto con validación) | Hecho |
| Controlador sin dependencia de Qt | Hecho |
| Pruebas de modelo y controlador sin GUI | Hecho (10 pruebas) |
| Vista Qt (MainWindow, señales/ranuras) | Escrita, **sin compilar aún** con Qt 6 |
| Diagramas de clases y secuencia (crear, listar) | Hecho (PlantUML) |
| Adapter para CSV heredado + flujo "cargar" | Pendiente |
| Comparación antes/después, respuestas, video | Pendiente |

Detalle en [`docs/avance_30.md`](docs/avance_30.md).

## Estructura

```
src/model/        Modelo (C++ estándar, sin Qt)
src/controller/   Controlador (C++ estándar, sin Qt)
src/view/         Vista (Qt 6 Widgets)
src/main.cpp      Composición y conexión por señales/ranuras
tests/            Pruebas sin GUI
docs/diagramas/   PlantUML
```

Regla de dependencias: `Vista → Controlador → Modelo`. El Modelo y el
Controlador no incluyen ningún encabezado de Qt.

## Compilar y probar

Requisitos: C++20, CMake ≥ 3.21 y (opcional, para la GUI) Qt 6 Widgets.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/seguimiento        # solo si Qt 6 fue encontrado
```

Si Qt 6 no está instalado, CMake compila únicamente el núcleo y las pruebas.

## Versiones usadas

- g++ 13.3, CMake 3.28 (núcleo y pruebas verificados)
- Qt 6: _completar con la versión del equipo al compilar la GUI_
