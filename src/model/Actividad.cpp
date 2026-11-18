#include "model/Actividad.h"

namespace acad {

std::string aTexto(TipoActividad tipo) {
    switch (tipo) {
        case TipoActividad::Tarea:    return "Tarea";
        case TipoActividad::Examen:   return "Examen";
        case TipoActividad::Proyecto: return "Proyecto";
    }
    return "Desconocido";
}

std::string Tarea::detalle() const    { return "Peso: " + std::to_string(peso_) + "%"; }
std::string Examen::detalle() const   { return "Duración: " + std::to_string(duracion_) + " min"; }
std::string Proyecto::detalle() const { return "Integrantes: " + std::to_string(integrantes_); }

}  // namespace acad
