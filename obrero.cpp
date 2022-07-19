#include "obrero.h"

Obrero::Obrero(QObject *parent)
    : QObject{parent}
{

}

Obrero::Obrero(const QString &nombre, int horas, TipodeJornada jornada) : m_nombre(nombre),
    m_horas(horas),
    m_jornada(jornada)
{
    m_salarioBruto = 0;
    m_descuento = 0;
    m_salarioNeto = 0;
}

const QString &Obrero::nombre() const
{
    return m_nombre;
}

void Obrero::setNombre(const QString &newNombre)
{
    m_nombre = newNombre;
}

int Obrero::horas() const
{
    return m_horas;
}

void Obrero::setHoras(int newHoras)
{
    m_horas = newHoras;
}

TipodeJornada Obrero::jornada() const
{
    return m_jornada;
}

void Obrero::setJornada(TipodeJornada newJornada)
{
    m_jornada = newJornada;
}

double Obrero::salarioBruto() const
{
    return m_salarioBruto;
}

void Obrero::setSalarioBruto(double newSalarioBruto)
{
    m_salarioBruto = newSalarioBruto;
}

double Obrero::salarioNeto() const
{
    return m_salarioNeto;
}

void Obrero::setSalarioNeto(double newSalarioNeto)
{
    m_salarioNeto = newSalarioNeto;
}

double Obrero::descuento() const
{
    return m_descuento;
}

void Obrero::setDescuento(double newDescuento)
{
    m_descuento = newDescuento;
}

QString Obrero::toString()
{
    QString str = "";
    str.append(tr("Nombre: %1").arg(m_nombre)+ "\n");
    str.append(tr("Jornada: %1").arg(jornada2String()) + "\n");
    str.append(tr("Horas: %1").arg(QString::number(m_horas)) + "\n");
    str.append(tr("Salario Bruto: %1").arg(QString::number(m_salarioBruto)) + "$\n");
    str.append(tr("Descuento: %1").arg(QString::number(m_descuento)) + "$\n");
    str.append(tr("Salario Neto: %1").arg(QString::number(m_salarioNeto)) + "$\n");
    return str;
}

QString Obrero::jornada2String()
{
    switch (m_jornada) {
    case TipodeJornada::Matutina:
        return tr("Matutina");
        break;
    case TipodeJornada::Vespertina:
        return tr("Vespertina");
        break;
    case TipodeJornada::Nocturna:
        return tr("Nocturna");
        break;
    default:
        return "";
    }
}
