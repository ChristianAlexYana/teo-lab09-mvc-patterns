#include "controller/ActividadController.h"
#include "mini_test.h"
#include "model/RepositorioActividades.h"

using namespace acad;

// Repositorio falso: demuestra que el controlador solo depende de IRepositorio.
class RepoFalso final : public IRepositorio {
public:
    int siguienteId() override { return ++id; }
    void agregar(ActividadPtr a) override { ++agregados; ultimo = std::move(a); }
    std::vector<ActividadPtr> listar() const override { return ultimo ? std::vector{ultimo} : std::vector<ActividadPtr>{}; }
    std::size_t cantidad() const override { return agregados; }
    int id = 0;
    int agregados = 0;
    ActividadPtr ultimo;
};

static DatosActividad valido() {
    return {TipoActividad::Examen, "Parcial 3", "Tecnología de Objetos", "2026-12-01", 90};
}

PRUEBA(controlador_crea_y_lista_sin_gui) {
    RepositorioActividades repo;
    ActividadController ctrl(repo);
    const auto r = ctrl.crear(valido());
    VERIFICAR(r.ok);
    const auto filas = ctrl.listar();
    VERIFICAR(filas.size() == 1);
    VERIFICAR(filas[0].tipo == "Examen");
    VERIFICAR(filas[0].detalle == "Duración: 90 min");
}

PRUEBA(controlador_notifica_solo_si_hubo_cambio) {
    RepositorioActividades repo;
    ActividadController ctrl(repo);
    int avisos = 0;
    ctrl.alCambiar([&] { ++avisos; });

    VERIFICAR(ctrl.crear(valido()).ok);
    VERIFICAR(avisos == 1);

    auto invalido = valido();
    invalido.fechaEntrega = "2026-02-30";
    const auto r = ctrl.crear(invalido);
    VERIFICAR(!r.ok);
    VERIFICAR(!r.mensaje.empty());
    VERIFICAR(avisos == 1);          // no hubo notificación extra
    VERIFICAR(repo.cantidad() == 1);  // el modelo quedó intacto
}

PRUEBA(controlador_funciona_con_repositorio_falso) {
    RepoFalso repo;
    ActividadController ctrl(repo);
    VERIFICAR(ctrl.crear(valido()).ok);
    VERIFICAR(repo.agregados == 1);
    VERIFICAR(ctrl.listar().size() == 1);
}

PRUEBA(controlador_lista_son_copias_de_solo_lectura) {
    RepositorioActividades repo;
    ActividadController ctrl(repo);
    ctrl.crear(valido());
    auto filas = ctrl.listar();
    filas.clear();                    // la Vista puede manipular su copia...
    VERIFICAR(repo.cantidad() == 1);  // ...sin afectar al modelo
    VERIFICAR(ctrl.listar().size() == 1);
}

int main() { return mt::correr(); }
