#include "model/RepositorioActividades.h"

#include <stdexcept>

namespace acad {

void RepositorioActividades::agregar(ActividadPtr actividad) {
    if (!actividad) throw std::invalid_argument("actividad nula");
    actividades_.push_back(std::move(actividad));
}

}  // namespace acad
