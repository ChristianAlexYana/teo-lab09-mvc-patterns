#pragma once
#include <memory>

#include "model/Actividad.h"
#include "model/DatosActividad.h"

namespace acad {

// Patrón creacional: Factory Method.
//   Creator (abstracto)  -> ActividadCreator
//   ConcreteCreator      -> TareaCreator, ExamenCreator, ProyectoCreator
//   Product              -> Actividad (Tarea, Examen, Proyecto)
// crear() es la operación plantilla: valida lo común y delega en el
// método fábrica crearActividad(), que cada creador concreto implementa.
class ActividadCreator {
public:
    virtual ~ActividadCreator() = default;
    std::unique_ptr<Actividad> crear(int id, const DatosActividad& datos) const;

protected:
    virtual std::unique_ptr<Actividad> crearActividad(int id, const DatosActividad& datos) const = 0;
};

class TareaCreator final : public ActividadCreator {
protected:
    std::unique_ptr<Actividad> crearActividad(int id, const DatosActividad& d) const override;
};

class ExamenCreator final : public ActividadCreator {
protected:
    std::unique_ptr<Actividad> crearActividad(int id, const DatosActividad& d) const override;
};

class ProyectoCreator final : public ActividadCreator {
protected:
    std::unique_ptr<Actividad> crearActividad(int id, const DatosActividad& d) const override;
};

// Selecciona el creador según el tipo. Es el único lugar que conoce
// la correspondencia tipo -> creador concreto.
std::unique_ptr<ActividadCreator> crearCreador(TipoActividad tipo);

}  // namespace acad
