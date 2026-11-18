#include "mini_test.h"
#include "model/ActividadCreator.h"
#include "model/RepositorioActividades.h"

using namespace acad;

static DatosActividad base(TipoActividad t, int parametro) {
    return {t, "Práctica 09", "Tecnología de Objetos", "2026-11-25", parametro};
}

PRUEBA(factory_crea_cada_tipo_concreto) {
    const auto tarea = crearCreador(TipoActividad::Tarea)->crear(1, base(TipoActividad::Tarea, 20));
    const auto examen = crearCreador(TipoActividad::Examen)->crear(2, base(TipoActividad::Examen, 90));
    const auto proyecto = crearCreador(TipoActividad::Proyecto)->crear(3, base(TipoActividad::Proyecto, 2));
    VERIFICAR(tarea->tipo() == TipoActividad::Tarea);
    VERIFICAR(examen->tipo() == TipoActividad::Examen);
    VERIFICAR(proyecto->tipo() == TipoActividad::Proyecto);
    VERIFICAR(tarea->detalle() == "Peso: 20%");
    VERIFICAR(examen->id() == 2);
}

PRUEBA(factory_rechaza_titulo_vacio) {
    auto d = base(TipoActividad::Tarea, 10);
    d.titulo = "   ";
    VERIFICAR_LANZA(crearCreador(d.tipo)->crear(1, d), DatosInvalidos);
}

PRUEBA(factory_rechaza_parametro_fuera_de_rango) {
    VERIFICAR_LANZA(crearCreador(TipoActividad::Tarea)->crear(1, base(TipoActividad::Tarea, 0)), DatosInvalidos);
    VERIFICAR_LANZA(crearCreador(TipoActividad::Examen)->crear(1, base(TipoActividad::Examen, 301)), DatosInvalidos);
    VERIFICAR_LANZA(crearCreador(TipoActividad::Proyecto)->crear(1, base(TipoActividad::Proyecto, 11)), DatosInvalidos);
}

PRUEBA(fecha_valida_considera_calendario) {
    VERIFICAR(fechaValida("2026-11-18"));
    VERIFICAR(fechaValida("2028-02-29"));   // bisiesto
    VERIFICAR(!fechaValida("2027-02-29"));  // no bisiesto
    VERIFICAR(!fechaValida("2026-13-01"));
    VERIFICAR(!fechaValida("18/11/2026"));
    VERIFICAR(!fechaValida(""));
}

PRUEBA(repositorio_asigna_ids_y_conserva_orden) {
    RepositorioActividades repo;
    const int a = repo.siguienteId();
    repo.agregar(crearCreador(TipoActividad::Tarea)->crear(a, base(TipoActividad::Tarea, 5)));
    const int b = repo.siguienteId();
    repo.agregar(crearCreador(TipoActividad::Examen)->crear(b, base(TipoActividad::Examen, 60)));
    VERIFICAR(a == 1 && b == 2);
    VERIFICAR(repo.cantidad() == 2);
    VERIFICAR(repo.listar().front()->id() == 1);
}

PRUEBA(repositorio_rechaza_actividad_nula) {
    RepositorioActividades repo;
    VERIFICAR_LANZA(repo.agregar(nullptr), std::invalid_argument);
}

int main() { return mt::correr(); }
