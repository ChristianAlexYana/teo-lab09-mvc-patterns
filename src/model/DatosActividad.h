#pragma once
#include <stdexcept>
#include <string>

#include "model/Actividad.h"

namespace acad {

// Datos crudos que llegan desde la Vista (o desde el CSV) antes de validar.
struct DatosActividad {
    TipoActividad tipo = TipoActividad::Tarea;
    std::string titulo;
    std::string curso;
    std::string fechaEntrega;  // AAAA-MM-DD
    // Significado según el tipo: peso % (Tarea), minutos (Examen), integrantes (Proyecto).
    int parametro = 0;
};

class DatosInvalidos : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Valida una fecha ISO AAAA-MM-DD (considera años bisiestos).
bool fechaValida(const std::string& fecha);

}  // namespace acad
