#include "controller/ActividadController.h"

#include "model/ActividadCreator.h"

namespace acad {

Resultado ActividadController::crear(const DatosActividad& datos) {
    try {
        const auto creador = crearCreador(datos.tipo);
        // Limitación conocida del avance: el id se reserva antes de validar,
        // así que un intento inválido deja un hueco en la numeración.
        std::unique_ptr<Actividad> nueva = creador->crear(repo_.siguienteId(), datos);
        repo_.agregar(ActividadPtr(std::move(nueva)));
    } catch (const DatosInvalidos& e) {
        return {false, e.what()};
    }
    if (observador_) observador_();
    return {true, "Actividad registrada"};
}

std::vector<FilaActividad> ActividadController::listar() const {
    std::vector<FilaActividad> filas;
    for (const auto& a : repo_.listar())
        filas.push_back({a->id(), aTexto(a->tipo()), a->titulo(), a->curso(),
                         a->fechaEntrega(), a->detalle()});
    return filas;
}

}  // namespace acad
