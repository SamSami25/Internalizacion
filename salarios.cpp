#include "salarios.h"
#include "ui_salarios.h"

Salarios::Salarios(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Salarios)
{
    ui->setupUi(this);
    m_control = new Controlador();
}

Salarios::~Salarios()
{
    delete ui;
}


void Salarios::on_btnCalcular_clicked()
{
    calcular();
}


void Salarios::on_actionNuevo_triggered()
{
    // Limpiar widgets
    limpiar();
    // Limpiar el texto de calculos
    ui->outTexto->clear();
    // Mostrar mensaje de estado
    ui->statusbar->showMessage(tr("Nueva hoja de calculos de salario"),3000);
}

void Salarios::limpiar()
{
    // Limpiar widgets
    ui->intNombre->setText("");
    ui->intHoras->setValue(0);
    ui->intMatutina->setChecked(true);
    ui->intNombre->setFocus();
}

void Salarios::calcular()
{
    // Obtener los datos de la GUI

    QString nombre = ui->intNombre->text();

    int horas = ui->intHoras->value();

    TipodeJornada jornada;

    if(ui->intMatutina->isChecked()){
        jornada = TipodeJornada::Matutina;
    }else if (ui->intVespertina->isChecked()){
        jornada = TipodeJornada::Vespertina;
    }else{
        jornada = TipodeJornada::Nocturna;
    }

    //Validar datos
    if(nombre == "" || horas == 0){
        QMessageBox::warning(this,tr("Advertencia"),tr("El nombre y/o el numero de horas es incorrecto"));
        return;
    }

    // Establecer datos
    m_control->setDatos(nombre, horas, jornada);

    // Calcular salarios
    if(m_control->calcular()){
        // Mostrar los resultados
        ui->outTexto->appendPlainText(m_control->getDatos());
    }else{
        QMessageBox::critical(this,tr("ERROR"),tr("No se puede calcular el salario"));
    }

    // Limpiar widgets
    limpiar();

    // Mostrar mensaje de estado
    ui->statusbar->showMessage(tr("Salario de %1").arg(nombre) + tr(" calculado"),5000);
}


void Salarios::on_actionCalcular_triggered()
{
    calcular();
}


void Salarios::on_actionSalir_triggered()
{
    if(ui->outTexto->toPlainText().isEmpty()){
        this->close();
    }
    QMessageBox::StandardButton reply = QMessageBox::question(this,tr("Salir"),tr("Hay informacion que no se guardo"),QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);

    if(reply == QMessageBox::Save){
        on_actionGuardar_triggered();
        QApplication::quit();
    }

    if(reply == QMessageBox::Cancel){
        return;
    }

    if(reply == QMessageBox::No){
        QApplication::quit();
    }

}


void Salarios::on_actionGuardar_triggered()
{

    QString nombreArchivo;
    QFile archivo(nombreArchivo);
    if(archivo.exists()){
        archivo.setFileName(nombreArchivo);
        if(archivo.open(QFile::WriteOnly | QFile::Truncate)){

            QTextStream salida(&archivo);
            // Enviar los datos del resultado a la salida
            salida << ui->outTexto->toPlainText();
            // Mostrar mensaje en la barra de estados
            ui->statusbar->showMessage(tr("Datos guardados"), 5000);
            // Crear el archivo
            archivo.close();
        }
    }else{
        guardarComo();
    }

}



void Salarios::on_actionAcerca_de_Salarios_triggered()
{
    // Crear un objeto del cuadro de dialogo
    Acerca *dialog = new Acerca(this);
    // Enviar datos a la otra ventana
    dialog->setVersion(VERSION);
    //Mostrar la ventana en modo MODAL
    dialog->exec();
    // Luego de cerrar de la ventana, se acceden a los datos de la misma
    qDebug() << dialog->valor();
}


void Salarios::on_actionAbrir_triggered()
{
    QString nombreArchivo = QFileDialog::getOpenFileName(this,tr("Abrir archivo de calculo de salarios"));
    QFile archivo(nombreArchivo);

    if(!archivo.exists()){
        return;
    }

    archivo.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!archivo.isOpen()){
        return;
    }

    QString contenido = archivo.readAll();
    ui->outTexto->setPlainText(contenido);
    archivo.close();

}

void Salarios::guardarComo()
{
    // Abrir un cuadro de dialogo para seleccionar el path y archivo a guardadr
    QString nombreArchivo = QFileDialog::getSaveFileName(this,tr("Guardar Calculos de Salarios"),QDir::home().absolutePath() + tr("/salarios.txt"),tr("Archivos de texto (*.txt)"));
    QFile archivo(nombreArchivo);
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        //Crear un objeto "stream" de texto
        QTextStream salida(&archivo);
        // Enviar los datos del resultado a la salida
        salida << ui->outTexto->toPlainText();
        // Mostrar mensaje en la barra de estados
        ui->statusbar->showMessage(tr("Datos guardados en: %1").arg(nombreArchivo), 5000);
        // Crear el archivo
        archivo.close();
    }else{
        // Mensaje de error
        QMessageBox::warning(this,tr("Guardar archivo"),tr("Nose puede acceder al archivo para guardar los datos"));
    }

}

