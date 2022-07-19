#include "controlador.h"

Controlador::Controlador(QObject *parent)
    : QObject{parent}
{
    this->m_modelo = nullptr;
}

void Controlador::setDatos(QString nombre, int horas, TipodeJornada jornada)
{
    this->m_modelo = new Obrero(nombre, horas, jornada);
}

bool Controlador::calcular()
{
    // Validar que el obrero no se nulo

    if(m_modelo == nullptr){
        return false;
    }

    // Determinar el valor hora

    float valorHora = 0;
    switch (m_modelo->jornada()) {
    case TipodeJornada::Matutina:
        valorHora = MATUTINO;
        break;
    case TipodeJornada::Vespertina:
        valorHora = VESPERTINO;
        break;
    case TipodeJornada::Nocturna:
        valorHora = NOCTURNO;
        break;
    }

    // Caluclo de horas extra
    int horas = m_modelo->horas();
    int horasExtra;

    if(m_modelo->horas() > 40){
        horasExtra = m_modelo->horas() - 40;
        horas = 40;
    }

    // Calcular el salario
    float salarioBruto = horas * valorHora + (horasExtra * HORA_EXTRA);
    float descuento = salarioBruto * IESS / 100.0;
    float salarioNeto = salarioBruto - descuento;

    // Estabklecer valores al objeto

    m_modelo->setSalarioBruto(salarioBruto);
    m_modelo->setDescuento(descuento);
    m_modelo->setSalarioNeto(salarioNeto);

    // Si todo va bien, retorna un TRUE
    return true;
}

QString Controlador::getDatos()
{
    return m_modelo->toString();
}
