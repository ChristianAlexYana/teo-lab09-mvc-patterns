#include <QApplication>

#include "controller/ActividadController.h"
#include "model/RepositorioActividades.h"
#include "view/MainWindow.h"

// Composición: aquí (y solo aquí) se conectan Modelo, Controlador y Vista.
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    acad::RepositorioActividades repositorio;
    acad::ActividadController controlador(repositorio);
    MainWindow ventana;

    // Vista -> Controlador (señal/ranura)
    QObject::connect(&ventana, &MainWindow::crearSolicitado, &ventana,
        [&](int tipo, const QString& titulo, const QString& curso,
            const QString& fecha, int parametro) {
            acad::DatosActividad datos;
            datos.tipo = static_cast<acad::TipoActividad>(tipo);
            datos.titulo = titulo.toStdString();
            datos.curso = curso.toStdString();
            datos.fechaEntrega = fecha.toStdString();
            datos.parametro = parametro;
            const auto r = controlador.crear(datos);
            ventana.mostrarMensaje(QString::fromStdString(r.mensaje), !r.ok);
        });

    // Controlador -> Vista (el controlador avisa; la Vista pide copias de solo lectura)
    controlador.alCambiar([&] { ventana.mostrarFilas(controlador.listar()); });

    ventana.show();
    return app.exec();
}
