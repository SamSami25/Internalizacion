#include "salarios.h"

#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Objeto para manejar las traducciones
    QTranslator traducion;
    // Solicitando al usuario que seleccione un idioma
    QStringList idiomas;
    idiomas << "Francés" << "Inglés" << "Ruso" << "Portugues";
    QString idiomaSeleccionado = QInputDialog::getItem(NULL,
                               "Idioma",
                               "Seleccione un idioma",
                               idiomas);
    // Dependiendo del idioma seleccionado, carga el archivo de rtaducción
    if (idiomaSeleccionado == "Francés"){
        traducion.load(":/Salarios_fr.qm");
    }else if (idiomaSeleccionado == "Inglés"){
        traducion.load(":/Salarios_en_US.qm");
    }else if(idiomaSeleccionado == "Ruso"){
        traducion.load(":/Salarios_ru.qm");
    }else{
        traducion.load(":/Salarios_pt.qm");
    }
    // Si es diferente de español, se instala la traducción en TODA la aplicación
    if (idiomaSeleccionado != "Español"){
        a.installTranslator(&traducion);
    }
    // Muestra la ventana principal
    Salarios w;
    w.show();
    return a.exec();
}
