#pragma once
#include <functional>
#include <string>
#include <vector>

#include "model/DatosActividad.h"
#include "model/IRepositorio.h"

namespace acad {

// Lo que la Vista puede ver: copias de solo lectura, nunca punteros al modelo.
struct FilaActividad {
    int id;
    std::string tipo;
    std::string titulo;
    std::string curso;
    std::string fechaEntrega;
    std::string detalle;
};

struct Resultado {
    bool ok;
    std::string mensaje;
};

// Controlador: coordina Vista <-> Modelo. No usa Qt, por eso se prueba sin GUI.
// La Vista lo invoca (vía señales/ranuras en main.cpp) y se suscribe a los
// cambios con alCambiar().
class ActividadController {
public:
    explicit ActividadController(IRepositorio& repositorio) : repo_(repositorio) {}

    Resultado crear(const DatosActividad& datos);
    std::vector<FilaActividad> listar() const;

    void alCambiar(std::function<void()> observador) { observador_ = std::move(observador); }

private:
    IRepositorio& repo_;
    std::function<void()> observador_;
};

}  // namespace acad
