#include "filtro_passivo.h"

Filtro_Passivo::Filtro_Passivo(QString tipo, QString topologia, double ind, double cap, double freq, double multiplicador_cap, double multiplicador_ind, double multiplicador_freq, double largura_banda, double multiplicador_banda)
{
    _tipo = tipo;
    _topologia = topologia;
    _ind = ind*multiplicador_ind;
    _cap = cap*multiplicador_cap;
    _freq = freq*multiplicador_freq;
    _largura_banda = largura_banda*multiplicador_banda;
}

double Filtro_Passivo::calculo_filtro(void)
{
    _res = 0;
    if (_tipo == "pa")
    {
        if (_topologia == "rc")
            _res = 1/(2*PI*_freq*_cap);
        else if (_topologia == "rl")
            _res = 2*PI*_freq*_ind;

    }
    else if (_tipo == "pb")
    {
        if (_topologia == "rc")
            _res = 1/(2*PI*_freq*_cap);
        else if (_topologia == "rl")
            _res = 2*PI*_freq*_ind;
    }
    else if (_tipo == "pbanda" || _tipo == "rf")
    {
        _res = _largura_banda*_ind;
    }
    return _res;
}

/* Cálculo de magnitutde para filtros Passa Altas */
QVector<double> Filtro_Passivo::bode_magnitude_pa(void)
{
    double i, calc = 0.0;
    _bode_magnitude.clear();
    QVectorIterator<double> it(_bode_magnitude);
    double limit = _freq/_cap;

    for(i = 0.0; i<limit; i+=100)
    {
        if (_topologia == "rc")
            calc = _res/(sqrt(pow(_res,2) + pow((1/(2*PI*i*_cap)),2)));
        else if (_topologia == "rl") {
            calc = (2*PI*i*_ind)/sqrt(pow(_res,2) + pow(2*PI*i*_ind,2));
        }
        //qDebug() << " calc =" << calc;
        _bode_magnitude.append(calc);

    }
    return _bode_magnitude;
}

QVector<double> Filtro_Passivo::bode_fase_pa(void)
{
    double i, calc = 0.0;
    _bode_fase.clear();
    QVectorIterator<double> it(_bode_fase);
    double limit = 100000;
    for (i = 0.0; i < limit; i += 100)
    {
        if (_topologia == "rc")
            calc = atan(1/(2*PI*i*_res*_cap))*(180/PI);
        else if(_topologia == "rl")
            calc = atan(_res/(2*PI*i*_ind));
        //qDebug() << " bode_fase_pb_calc =" << calc;
        _bode_fase.append(calc);
    }
    return _bode_fase;
}
QVector<double> Filtro_Passivo::bode_magnitude_pb(void)
{
    double i, calc = 0.0;
    _bode_magnitude.clear();
    QVectorIterator<double> it(_bode_magnitude);
    double limit = _freq/_cap;

    for(i = 0.0; i < limit; i += 100)
    {
        if (_topologia == "rc")
            calc = 1/(sqrt(1 + pow((2*PI*i*_res*_cap),2)));

        else if (_topologia == "rl")
            calc = (_res)/sqrt(pow(_res,2) + pow(2*PI*i*_ind,2));
        _bode_magnitude.append(calc);
    }
    return _bode_magnitude;
}

QVector<double> Filtro_Passivo::bode_fase_pb(void)
{
    double i, calc = 0.0;
    _bode_fase.clear();
    QVectorIterator<double> it(_bode_fase);
    double limit = 1000000;
    for (i = 0.0; i < limit; i += 100)
    {
        if (_topologia == "rc")
            calc = -atan(2*PI*i*_res*_cap)*(180/PI);

        else if (_topologia == "rl")
            calc = atan((-2*PI*i*_ind)/_res)*(180/PI);
        //qDebug() << " bode_fase_pb_calc =" << calc;
        _bode_fase.append(calc);
    }
    return _bode_fase;
}

QVector<double> Filtro_Passivo::bode_magnitude_pfaixa(void)
{
    double i, calc = 0.0;
    double aux1 = 0.0, aux2 = 0.0;
    _bode_magnitude.clear();
    QVectorIterator<double> it(_bode_magnitude);
    double limit = 100000;

    for (i = 0; i < limit; i+=100)
    {
        aux1 = (1/(_ind*_cap)) -  pow((2*PI*i),2);
        aux2 = (2*PI*i)*(_res/_ind);

        calc = aux2/sqrt(pow(aux1,2) + pow(aux2,2));

        _bode_magnitude.append(calc);
        //qDebug() << "Filtro_Passivo::bode_magnitude_pfaixa" << calc;
    }
    return _bode_magnitude;
}

QVector<double> Filtro_Passivo::bode_fase_pfaixa(void)
{
    double i, calc = 0.0, aux1 = 0.0,  aux2 = 0.0, aux3 = 0.0;
    _bode_fase.clear();

    QVectorIterator<double> it(_bode_fase);
    double limit = 10000;

    for (i = 0.0; i < limit; i += 100)
    {
        aux1 = 2*PI*i;
        aux2 = _res/_ind;
        aux3 = 1/(_ind*_cap);
        calc = atan((aux3-pow(aux1,2))/(aux1*aux2))*(180/PI);
        _bode_fase.append(calc);
        //qDebug() << "Filtro_Passivo::bode_fase_pfaixa =" << calc;
    }

    return _bode_fase;
}

QVector<double> Filtro_Passivo::bode_magnitude_rf(void)
{
    double i, calc = 0.0;
    double aux1 = 0.0, aux2 = 0.0;
    _bode_magnitude.clear();
    QVectorIterator<double> it(_bode_magnitude);
    double limit = _freq/_cap;

    for (i = 0; i < limit; i+=100)
    {
        aux1 = (1/(_ind*_cap)) -  pow((2*PI*i),2);
        aux2 = (2*PI*i)*(_res/_ind);

        calc = (qAbs(aux1))/sqrt(pow(aux1,2) + pow(aux2,2));

        _bode_magnitude.append(calc);
        //qDebug() << "Filtro_Passivo::bode_magnitude_pfaixa" << calc;
    }
    return _bode_magnitude;
}

QVector<double> Filtro_Passivo::bode_fase_rf(void)
{
    double i, calc = 0.0, aux1 = 0.0,  aux2 = 0.0, aux3 = 0.0;
    _bode_fase.clear();

    QVectorIterator<double> it(_bode_fase);
    double limit = 100000;

    for (i = 0.0; i < limit; i += 100)
    {
        aux1 = 2*PI*i;
        aux2 = 1/(_res*_cap);
        aux3 = 1/(_ind*_cap);
        calc = atan((aux1*aux2)/(aux3 - pow(aux1,2)))*(180/PI);
        _bode_fase.append(calc);
       // qDebug() << "Filtro_Passivo::bode_fase_pfaixa =" << calc;
    }

    return _bode_fase;
}
void Filtro_Passivo::rlc_dados(int dado)
{
    if (dado == 0)
    {
        _cap = 1/(pow(2*PI*_freq,2)*_ind);
        _res = calculo_filtro();
    }
    else if (dado == 1)
    {
        _ind = 1/(pow(2*PI*_freq,2)*_cap);
       _res = _ind*_largura_banda;
    }
    else if (dado == 2)
        _freq = 1/sqrt(_ind*_cap);
    else if (dado == 3)
    {
        _largura_banda = _res/_ind;
        _res = calculo_filtro();
    }
}

double Filtro_Passivo::get_cap(void)
{
    return _cap;
}

double Filtro_Passivo::get_ind(void)
{
    return _ind;
}

double Filtro_Passivo::get_freq(void)
{
    return _freq;
}

double Filtro_Passivo::get_banda(void)
{
    return _largura_banda;
}
