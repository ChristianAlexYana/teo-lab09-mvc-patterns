#pragma once
// Mini arnés de pruebas (temporal). Se migrará a Qt Test / GoogleTest
// cuando el equipo tenga el entorno Qt configurado.
#include <functional>
#include <iostream>
#include <vector>

namespace mt {

struct Caso {
    const char* nombre;
    std::function<void()> cuerpo;
};

inline std::vector<Caso>& casos() { static std::vector<Caso> c; return c; }
inline int& fallos() { static int n = 0; return n; }

struct Registro {
    Registro(const char* n, std::function<void()> f) { casos().push_back({n, std::move(f)}); }
};

inline int correr() {
    for (auto& c : casos()) {
        const int antes = fallos();
        c.cuerpo();
        std::cout << (fallos() == antes ? "[OK]    " : "[FALLO] ") << c.nombre << "\n";
    }
    std::cout << casos().size() << " pruebas, " << fallos() << " verificaciones fallidas\n";
    return fallos() == 0 ? 0 : 1;
}

}  // namespace mt

#define PRUEBA(nombre)                                         \
    static void nombre();                                      \
    static mt::Registro registro_##nombre(#nombre, nombre);    \
    static void nombre()

#define VERIFICAR(cond)                                                        \
    do {                                                                       \
        if (!(cond)) {                                                         \
            ++mt::fallos();                                                    \
            std::cerr << __FILE__ << ":" << __LINE__ << " falló: " #cond "\n"; \
        }                                                                      \
    } while (0)

#define VERIFICAR_LANZA(expr, Tipo)                                            \
    do {                                                                       \
        bool lanzo = false;                                                    \
        try { expr; } catch (const Tipo&) { lanzo = true; }                    \
        if (!lanzo) {                                                          \
            ++mt::fallos();                                                    \
            std::cerr << __FILE__ << ":" << __LINE__ << " no lanzó " #Tipo "\n"; \
        }                                                                      \
    } while (0)
