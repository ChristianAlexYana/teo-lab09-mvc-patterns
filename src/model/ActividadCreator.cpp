#include "model/ActividadCreator.h"

namespace acad {

namespace {

void exigirTexto(const std::string& valor, const char* campo) {
    if (valor.find_first_not_of(" \t") == std::string::npos)
        throw DatosInvalidos(std::string("El campo '") + campo + "' es obligatorio");
}

void exigirRango(int valor, int min, int max, const char* campo) {
    if (valor < min || valor > max)
        throw DatosInvalidos(std::string("'") + campo + "' debe estar entre " +
                             std::to_string(min) + " y " + std::to_string(max));
}

}  // namespace

std::unique_ptr<Actividad> ActividadCreator::crear(int id, const DatosActividad& datos) const {
    exigirTexto(datos.titulo, "título");
    exigirTexto(datos.curso, "curso");
    if (!fechaValida(datos.fechaEntrega))
        throw DatosInvalidos("La fecha debe tener formato AAAA-MM-DD y existir en el calendario");
    return crearActividad(id, datos);
}

std::unique_ptr<Actividad> TareaCreator::crearActividad(int id, const DatosActividad& d) const {
    exigirRango(d.parametro, 1, 100, "peso (%)");
    return std::make_unique<Tarea>(id, d.titulo, d.curso, d.fechaEntrega, d.parametro);
}

std::unique_ptr<Actividad> ExamenCreator::crearActividad(int id, const DatosActividad& d) const {
    exigirRango(d.parametro, 1, 300, "duración (min)");
    return std::make_unique<Examen>(id, d.titulo, d.curso, d.fechaEntrega, d.parametro);
}

std::unique_ptr<Actividad> ProyectoCreator::crearActividad(int id, const DatosActividad& d) const {
    exigirRango(d.parametro, 1, 10, "integrantes");
    return std::make_unique<Proyecto>(id, d.titulo, d.curso, d.fechaEntrega, d.parametro);
}

std::unique_ptr<ActividadCreator> crearCreador(TipoActividad tipo) {
    switch (tipo) {
        case TipoActividad::Tarea:    return std::make_unique<TareaCreator>();
        case TipoActividad::Examen:   return std::make_unique<ExamenCreator>();
        case TipoActividad::Proyecto: return std::make_unique<ProyectoCreator>();
    }
    throw DatosInvalidos("Tipo de actividad desconocido");
}

}  // namespace acad
