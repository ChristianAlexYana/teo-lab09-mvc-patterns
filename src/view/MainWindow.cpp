#include "view/MainWindow.h"

#include <QComboBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Seguimiento académico");
    resize(760, 480);

    tipo_ = new QComboBox;
    tipo_->addItems({"Tarea", "Examen", "Proyecto"});
    titulo_ = new QLineEdit;
    curso_ = new QLineEdit;
    fecha_ = new QLineEdit;
    fecha_->setPlaceholderText("AAAA-MM-DD");
    parametro_ = new QSpinBox;
    parametro_->setRange(0, 300);
    agregar_ = new QPushButton("Agregar actividad");

    auto* form = new QFormLayout;
    form->addRow("Tipo", tipo_);
    form->addRow("Título", titulo_);
    form->addRow("Curso", curso_);
    form->addRow("Fecha de entrega", fecha_);
    form->addRow("Peso % / minutos / integrantes", parametro_);
    form->addRow(agregar_);

    tabla_ = new QTableWidget(0, 6);
    tabla_->setHorizontalHeaderLabels({"Id", "Tipo", "Título", "Curso", "Entrega", "Detalle"});
    tabla_->setEditTriggers(QAbstractItemView::NoEditTriggers);  // la Vista no edita datos
    tabla_->horizontalHeader()->setStretchLastSection(true);

    estado_ = new QLabel;

    auto* centro = new QWidget;
    auto* capa = new QVBoxLayout(centro);
    capa->addLayout(form);
    capa->addWidget(tabla_);
    capa->addWidget(estado_);
    setCentralWidget(centro);

    connect(agregar_, &QPushButton::clicked, this, &MainWindow::alPulsarAgregar);
}

void MainWindow::alPulsarAgregar() {
    emit crearSolicitado(tipo_->currentIndex(), titulo_->text(), curso_->text(),
                         fecha_->text(), parametro_->value());
}

void MainWindow::mostrarFilas(const std::vector<acad::FilaActividad>& filas) {
    tabla_->setRowCount(static_cast<int>(filas.size()));
    int r = 0;
    for (const auto& f : filas) {
        const QString celdas[] = {QString::number(f.id),
                                  QString::fromStdString(f.tipo),
                                  QString::fromStdString(f.titulo),
                                  QString::fromStdString(f.curso),
                                  QString::fromStdString(f.fechaEntrega),
                                  QString::fromStdString(f.detalle)};
        for (int c = 0; c < 6; ++c) tabla_->setItem(r, c, new QTableWidgetItem(celdas[c]));
        ++r;
    }
}

void MainWindow::mostrarMensaje(const QString& texto, bool esError) {
    estado_->setStyleSheet(esError ? "color: #b00020;" : "color: #1b5e20;");
    estado_->setText(texto);
}
