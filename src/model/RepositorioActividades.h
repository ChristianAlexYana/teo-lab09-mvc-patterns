#pragma once
#include "model/IRepositorio.h"

namespace acad {

// Repositorio en memoria (implementación por defecto de IRepositorio).
class RepositorioActividades final : public IRepositorio {
public:
    int siguienteId() override { return ++ultimoId_; }
    void agregar(ActividadPtr actividad) override;
    std::vector<ActividadPtr> listar() const override { return actividades_; }
    std::size_t cantidad() const override { return actividades_.size(); }

private:
    int ultimoId_ = 0;
    std::vector<ActividadPtr> actividades_;
};

}  // namespace acad
