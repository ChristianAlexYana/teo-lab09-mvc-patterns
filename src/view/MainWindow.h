#pragma once
#include <QMainWindow>
#include <QString>

#include <vector>

#include "controller/ActividadController.h"

class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QTableWidget;

// Vista: solo presenta datos y emite señales. No conoce el Modelo ni sus
// colecciones; recibe copias de solo lectura (FilaActividad) del Controlador.
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

    void mostrarFilas(const std::vector<acad::FilaActividad>& filas);
    void mostrarMensaje(const QString& texto, bool esError);

signals:
    // tipo: 0 = Tarea, 1 = Examen, 2 = Proyecto (orden del combo)
    void crearSolicitado(int tipo, const QString& titulo, const QString& curso,
                         const QString& fecha, int parametro);

private slots:
    void alPulsarAgregar();

private:
    QComboBox* tipo_;
    QLineEdit* titulo_;
    QLineEdit* curso_;
    QLineEdit* fecha_;
    QSpinBox* parametro_;
    QPushButton* agregar_;
    QTableWidget* tabla_;
    QLabel* estado_;
};
