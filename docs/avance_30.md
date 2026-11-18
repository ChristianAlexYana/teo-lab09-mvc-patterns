# Avance 30 % — Práctica 09

## Qué se implementó

- **MVC.** Modelo y Controlador en C++ estándar; solo la Vista usa Qt.
  La Vista recibe `FilaActividad` (copias) y no puede tocar las colecciones
  del Modelo. `IRepositorio::listar()` devuelve punteros a objetos `const`.
- **Factory Method.** `ActividadCreator::crear()` valida los datos comunes y
  delega en `crearActividad()`, que implementan `TareaCreator`, `ExamenCreator`
  y `ProyectoCreator`. La GUI y el controlador no instancian clases concretas
  de actividad.
- **Pruebas sin GUI.** `test_modelo` (6) y `test_controlador` (4), incluyendo un
  repositorio falso que demuestra que el controlador depende solo de `IRepositorio`.

## Respuestas preliminares

**¿Qué problema concreto justifica Factory Method?**
Antes la GUI hacía `new Tarea(...)`, `new Examen(...)` y conocía las reglas de
cada tipo. Con el patrón, agregar un tipo nuevo exige una subclase de
`ActividadCreator` y una línea en `crearCreador()`, sin tocar la Vista.

**¿Qué dependencias no debe tener el Modelo?**
Ni de Qt ni de la Vista ni del Controlador. Verificable: `src/model` no incluye
encabezados de Qt y compila en la biblioteca `nucleo` sin enlazar Qt.

**Costo de Factory Method:** más clases (3 creadores + 1 abstracta) para solo
tres tipos. Se justifica porque la validación específica queda aislada por tipo.

_Pendiente: respuestas sobre Adapter y verificación del beneficio con métricas._

## Limitaciones conocidas

- El id se reserva antes de validar, por lo que un intento inválido deja un hueco
  en la numeración.
- Las pruebas usan un arnés mínimo (`tests/mini_test.h`); se migrarán a Qt Test o
  GoogleTest.
- La Vista no ha sido compilada con Qt 6 todavía.
- El controlador es C++ puro y la conexión por señales/ranuras se hace en
  `main.cpp`; se evaluará un envoltorio `QObject` si el diseño final lo requiere.

## Siguiente etapa (≈70 %)

1. `RepositorioCsvAdapter` que implemente `IRepositorio` sobre el lector CSV heredado.
2. Diagrama de secuencia "cargar" definitivo y pruebas del Adapter.
3. Comparación antes/después (dependencias por archivo, archivos modificados al
   agregar un tipo de actividad).
4. Respuestas finales, video, URL del commit evaluado y versiones de software.
