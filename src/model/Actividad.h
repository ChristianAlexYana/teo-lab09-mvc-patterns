#pragma once
#include <string>
#include <utility>

namespace acad {

enum class TipoActividad { Tarea, Examen, Proyecto };

std::string aTexto(TipoActividad tipo);

// Producto abstracto del Factory Method.
// Inmutable: una vez creada no cambia, así la Vista no puede alterarla.
class Actividad {
public:
    Actividad(int id, std::string titulo, std::string curso, std::string fechaEntrega)
        : id_(id), titulo_(std::move(titulo)), curso_(std::move(curso)),
          fechaEntrega_(std::move(fechaEntrega)) {}
    virtual ~Actividad() = default;

    int id() const { return id_; }
    const std::string& titulo() const { return titulo_; }
    const std::string& curso() const { return curso_; }
    const std::string& fechaEntrega() const { return fechaEntrega_; }

    virtual TipoActividad tipo() const = 0;
    virtual std::string detalle() const = 0;

private:
    int id_;
    std::string titulo_;
    std::string curso_;
    std::string fechaEntrega_;  // formato ISO AAAA-MM-DD
};

// Productos concretos.
class Tarea final : public Actividad {
public:
    Tarea(int id, std::string titulo, std::string curso, std::string fecha, int pesoPorcentual)
        : Actividad(id, std::move(titulo), std::move(curso), std::move(fecha)),
          peso_(pesoPorcentual) {}
    TipoActividad tipo() const override { return TipoActividad::Tarea; }
    std::string detalle() const override;
    int pesoPorcentual() const { return peso_; }
private:
    int peso_;
};

class Examen final : public Actividad {
public:
    Examen(int id, std::string titulo, std::string curso, std::string fecha, int duracionMin)
        : Actividad(id, std::move(titulo), std::move(curso), std::move(fecha)),
          duracion_(duracionMin) {}
    TipoActividad tipo() const override { return TipoActividad::Examen; }
    std::string detalle() const override;
    int duracionMin() const { return duracion_; }
private:
    int duracion_;
};

class Proyecto final : public Actividad {
public:
    Proyecto(int id, std::string titulo, std::string curso, std::string fecha, int integrantes)
        : Actividad(id, std::move(titulo), std::move(curso), std::move(fecha)),
          integrantes_(integrantes) {}
    TipoActividad tipo() const override { return TipoActividad::Proyecto; }
    std::string detalle() const override;
    int integrantes() const { return integrantes_; }
private:
    int integrantes_;
};

}  // namespace acad
