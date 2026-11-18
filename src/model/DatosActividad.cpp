#include "model/DatosActividad.h"

#include <cctype>

namespace acad {

bool fechaValida(const std::string& f) {
    if (f.size() != 10 || f[4] != '-' || f[7] != '-') return false;
    for (std::size_t i = 0; i < f.size(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(static_cast<unsigned char>(f[i]))) return false;
    }
    const int anio = std::stoi(f.substr(0, 4));
    const int mes = std::stoi(f.substr(5, 2));
    const int dia = std::stoi(f.substr(8, 2));
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1) return false;

    static const int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool bisiesto = (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
    const int maxDia = (mes == 2 && bisiesto) ? 29 : diasMes[mes - 1];
    return dia <= maxDia;
}

}  // namespace acad
