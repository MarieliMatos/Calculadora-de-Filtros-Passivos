#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QVector>

#include "filtro_passivo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent=0);
    void tipo_filtro(void);
    ~MainWindow();

private slots:
    void on_filtro_currentIndexChanged(const QString &filtro);

    void on_tipo_filtro_currentIndexChanged(const QString &tipo);

    void on_topologia_currentIndexChanged(const QString &arg1);

    void on_calc_clicked();

    void on_comp_valor_valueChanged(double value);

    void on_comp2_valor_valueChanged(double value);
    
    void on_mult_currentTextChanged(const QString &arg1);

    void on_freq_valor_valueChanged(double arg1);

    void on_mult_fc_currentIndexChanged(const QString &arg1);

    void on_mult_2_currentTextChanged(const QString &arg1);

    void configura_filtro(void);

    void plot_bode(void);

    void on_larg_banda_valor_valueChanged(double arg1);

    void on_larg_banda_mult_currentTextChanged(const QString &arg1);

    int tipo_rlc(void);
private:
    Ui::MainWindow *ui;
    QString filtro;
    QString tf;
    QString topologia;
    double multiplicador_cap;
    double multiplicador_ind;
    double freq;
    double cap;
    double ind;
    double res;
    double largura_banda;
    unsigned multiplicador_freq;
    unsigned multiplicador_largura_banda;
    QVector<double> fase;
    QVector<double> x;
    int yaxis;
    int _yaxis;

    QVector<double> bode;
};

#endif // MAINWINDOW_H
