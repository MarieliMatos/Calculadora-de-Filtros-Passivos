#ifndef FILTRO_PASSIVO_H
#define FILTRO_PASSIVO_H
#include <QString>
#include <QDebug>
//#include <QtMath>
#include <math.h>
#include <QVector>

#define PI 3.14159265

class Filtro_Passivo
{
public:
    Filtro_Passivo(QString tipo, QString topologia, double ind, double cap, double freq, double multiplicador_cap, double multiplicador_ind, double multiplicador_freq, double largura_banda, double multiplicador_banda);
    double calculo_filtro(void);
    void rlc_dados(int dado);
    double get_ind(void);
    double get_cap(void);
    double get_freq(void);
    double get_banda(void);
    QVector<double> bode_magnitude_pa(void);
    QVector<double> bode_magnitude_pb(void);
    QVector<double> bode_magnitude_pfaixa(void);
    QVector<double> bode_fase_pa(void);
    QVector<double> bode_fase_pb(void);
    QVector<double> bode_fase_pfaixa(void);
    QVector<double> bode_magnitude_rf(void);
    QVector<double> bode_fase_rf(void);

protected:

private:
    QString _tipo;
    QString _topologia;
    QVector<double> _bode_magnitude;
    QVector<double> _bode_fase;
    QVector<double> _bode_freq;
    double _freq;
    double _cap;
    double _ind;
    double _res;
    double _largura_banda;
};


#endif // FILTRO_PASSIVO_H
