#pragma once
#include <cstddef>
#include <memory>
#include <vector>

#include "model/Actividad.h"

namespace acad {

using ActividadPtr = std::shared_ptr<const Actividad>;

// Contrato de almacenamiento. El Controlador depende de esta interfaz,
// no de una implementación concreta (memoria, CSV heredado, etc.).
// Aquí se enchufará el Adapter del CSV heredado en la siguiente etapa.
class IRepositorio {
public:
    virtual ~IRepositorio() = default;

    virtual int siguienteId() = 0;
    virtual void agregar(ActividadPtr actividad) = 0;
    // Devuelve una copia de punteros a objetos const: quien lista no puede
    // modificar la colección interna ni las actividades.
    virtual std::vector<ActividadPtr> listar() const = 0;
    virtual std::size_t cantidad() const = 0;
};

}  // namespace acad
