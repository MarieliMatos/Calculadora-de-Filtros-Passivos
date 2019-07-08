#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->filtro->addItem("Passivo");
    ui->filtro->addItem("Ativo");

    ui->tipo_filtro->addItem("Passa Baixa");
    ui->tipo_filtro->addItem("Passa Alta");
    ui->tipo_filtro->addItem("Passa Banda");
    ui->tipo_filtro->addItem("Rejeita Faixa");

    ui->mult_fc->addItem("Hz");
    ui->mult_fc->addItem("kHz");
    ui->mult_fc->addItem("MHz");
    ui->mult_fc->addItem("GHz");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Seleciona o filtro */
void MainWindow::on_filtro_currentIndexChanged(const QString &f)
{
    if (f == "Passivo")   
        filtro = "passivo";

    else if(f == "Ativo")
    {
        ui->topologia->clear();
        ui->topologia->addItem("Butterworth");
        ui->topologia->addItem("Chebyshev");
        filtro = "ativo";
    }
    //qDebug()<<filtro;
}

/* Seleciona o tipo de filro */
void MainWindow::on_tipo_filtro_currentIndexChanged(const QString &t)
{
    ui->topologia->clear();
    if (t == "Passa Alta")
    {
        ui->topologia->addItem("RC");
        ui->topologia->addItem("RL");
        tf = "pa";
    }
    else if (t == "Passa Baixa")
    {
        ui->topologia->addItem("RC");
        ui->topologia->addItem("RL");
        tf = "pb";
    }
    else if (t == "Rejeita Faixa")
    {
        ui->topologia->addItem("RLC");
        tf = "rf";
    }
    else if (t == "Passa Banda")
    {
        ui->topologia->addItem("RLC");
        tf = "pbanda";
    }

    //qDebug()<<tf;
}

/* Seleciona topologia do filtro*/
void MainWindow::on_topologia_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "RL")
    {
        ui->comp_2->hide();
        ui->mult_2->hide();
        ui->ind_radiobutton->hide();
        ui->comp2_valor->hide();
        ui->ind_radiobutton->hide();
        ui->f_radiobutton->hide();
        ui->comp->setText("Indutor");
        ui->fc->setText("Frequência de Corte");
        ui->mult->clear();
        ui->mult->addItem("mH");
        ui->mult->addItem("uH");
        ui->mult->addItem("nH");
        ui->larg_banda->hide();
        ui->larg_banda_valor->hide();
        ui->larg_banda_mult->hide();
        topologia = "rl";
    }
    else if(arg1 == "RC")
    {
        ui->comp_2->hide();
        ui->mult_2->hide();
        ui->cap_radiobutton->hide();
        ui->ind_radiobutton->hide();
        ui->larg_banda_radiobutton->hide();
        ui->f_radiobutton->hide();
        ui->comp2_valor->hide();
        ui->mult->clear();
        ui->fc->setText("Frequência de Corte");
        ui->comp->setText("Capacitor");
        ui->mult->addItem("uF");
        ui->mult->addItem("nF");
        ui->mult->addItem("pF");
        ui->larg_banda->hide();
        ui->larg_banda_valor->hide();
        ui->larg_banda_mult->hide();
        topologia = "rc";
    }

    else if (arg1 == "RLC")
    {
        ui->mult->clear();
        ui->comp->setText("Capacitor");
        ui->mult->addItem("uF");
        ui->mult->addItem("nF");
        ui->mult->addItem("pF");

        ui->fc->setText("Frequência Central");
        ui->cap_radiobutton->show();
        ui->comp_2->show();
        ui->mult_2->show();
        ui->ind_radiobutton->show();
        ui->larg_banda_radiobutton->show();
        ui->f_radiobutton->show();
        ui->comp2_valor->show();
        ui->comp_2->setText("Indutor");
        ui->mult_2->addItem("mH");
        ui->mult_2->addItem("uH");
        ui->mult_2->addItem("nH");

        ui->larg_banda_mult->addItem("Hz");
        ui->larg_banda_mult->addItem("kHz");
        ui->larg_banda_mult->addItem("MHz");
        ui->larg_banda_mult->addItem("GHz");

        ui->larg_banda->show();
        ui->larg_banda_valor->show();
        ui->larg_banda_mult->show();

        topologia = "rlc";
    }
    //qDebug()<<topologia;
}

/* Armazena os valores capacitores e indutores */
void MainWindow::on_comp_valor_valueChanged(double valor)
{
    if (topologia == "rl")
    {
        ind = valor;
    }
    else if (topologia == "rc")
    {
        cap = valor;
    }
    else if (topologia == "rlc")
    {
        cap = valor;
    }
    //qDebug()<< "Capacitor" <<cap;
    //qDebug()<< "Indutor" <<ind;
}

/* Armazena o valor do indutor se o filtro for RLC */
void MainWindow::on_comp2_valor_valueChanged(double valor)
{
    ind = valor;
    //qDebug()<< "Indutor inf" <<ind;
}

/* Armazena o valor do multiplicador */
void MainWindow::on_mult_currentTextChanged(const QString &arg1)
{
    if (arg1 == "nF")
        multiplicador_cap = 0.00000001;
    else if (arg1 == "uF")
        multiplicador_cap = 0.000001;
    else if (arg1 == "pF")
        multiplicador_cap = 0.000000000001;

    else if (arg1 == "nH")
        multiplicador_ind = 0.000000001;
    else if (arg1 == "uH")
        multiplicador_ind = 0.000001;
    else if (arg1 == "mH")
        multiplicador_ind = 0.001;

    //qDebug()<< "Capacitor mult" <<multiplicador_cap;
    //qDebug()<< "Indutor mult" <<multiplicador_ind;
}

/* Armazena o valor do multiplicador do indutor se for RLC */
void MainWindow::on_freq_valor_valueChanged(double arg1)
{
    freq = arg1;
   // qDebug()<< "freq" <<freq;
}

/* Armazena o valor do multiplicador da frequência */
void MainWindow::on_mult_fc_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Hz")
        multiplicador_freq = 1;
    else if (arg1 == "kHz")
        multiplicador_freq = 1000;
    else if (arg1 == "MHz")
        multiplicador_freq = 10000000;
    else if (arg1 == "GHz")
        multiplicador_freq = 1000000000;
    //qDebug()<< "multiplicador_freq" <<multiplicador_freq;
}

/* Armazena o valor da frequência */
void MainWindow::on_mult_2_currentTextChanged(const QString &arg1)
{
    if (arg1 == "nH")
        multiplicador_ind = 0.000000001;
    else if (arg1 == "uH")
        multiplicador_ind = 0.000001;
    else if (arg1 == "mH")
        multiplicador_ind = 0.001;
    //qDebug()<< "Indutor mult" <<multiplicador_ind;
}

/*  */
void MainWindow::on_calc_clicked()
{
    int qtd = 0;
    if (topologia == "rlc")
    {
        qtd = ui->f_radiobutton->isChecked() + ui->ind_radiobutton->isChecked() + ui->cap_radiobutton->isChecked() + ui->larg_banda_radiobutton->isChecked();
        if (qtd != 3)
            QMessageBox::information(this, tr("Aviso"), tr("É preciso 3 dados"));

        else
            configura_filtro();
    }
    else
        configura_filtro();
}

/* Configura os filtros */
void MainWindow::configura_filtro(void)
{
    if (filtro == "passivo")
    {
        Filtro_Passivo _filtro_passivo(tf, topologia, ind, cap, freq, multiplicador_cap, multiplicador_ind, multiplicador_freq, largura_banda, multiplicador_largura_banda);
        res = _filtro_passivo.calculo_filtro();
        if (tf == "pa")
        {
            yaxis = 90;
            _yaxis = 0;
            if (topologia == "rc")
            {
                QPixmap img(":/pics/Imagens/pa_rc.png");
                ui->res->setText("R = ");
                ui->calc_res->setNum(res);
                ui->circuito->setPixmap(img);

            }
            else if (topologia == "rl")
            {
                QPixmap img(":/pics/Imagens/pa_rl.png");
                ui->res->setText("R = ");
                ui->calc_res->setNum(res);
                ui->circuito->setPixmap(img);
            }
            bode = _filtro_passivo.bode_magnitude_pa();
            fase = _filtro_passivo.bode_fase_pa();
        }
        if (tf == "pb")
        {
            yaxis = -90;
            _yaxis = 0;
            ui->res->setText("R = ");

            if (topologia == "rc")
            {
                QPixmap img(":/pics/Imagens/pb_rc.png");
                ui->circuito->setPixmap(img);
                ui->calc_res->setNum(res);
            }
            else if (topologia == "rl")
            {
                QPixmap img(":/pics/Imagens/pb_rl.png");
                ui->circuito->setPixmap(img);
                ui->calc_res->setNum(res);
            }
            bode = _filtro_passivo.bode_magnitude_pb();
            fase = _filtro_passivo.bode_fase_pb();
        }

        else if (tf == "pbanda")
        {
            QPixmap img(":/pics/Imagens/passa_faixa.png");
            yaxis = 90;
            _yaxis = -90;
            _filtro_passivo.rlc_dados(tipo_rlc());
            res = _filtro_passivo.calculo_filtro();
            ui->circuito->setPixmap(img);
            ui->calc_res->setNum(res);
            ui->res->setText("R = ");

            if (tipo_rlc() == 0)
            {
                ui->rlc_label->setText("C = ");
                ui->rlc_valor->setNum(_filtro_passivo.get_cap());
            }
            else if (tipo_rlc() == 1)
            {
                ui->rlc_label->setText("L = ");
                ui->rlc_valor->setNum(_filtro_passivo.get_ind());
            }
            else if (tipo_rlc() == 2)
            {
                ui->rlc_label->setText("f = ");
                ui->rlc_valor->setNum(_filtro_passivo.get_freq());
            }
            else if (tipo_rlc() == 3)
            {
                ui->rlc_label->setText("b = ");
                ui->rlc_valor->setNum(_filtro_passivo.get_banda());
            }

            bode = _filtro_passivo.bode_magnitude_pfaixa();
            fase = _filtro_passivo.bode_fase_pfaixa();
        }
        else if (tf == "rf")
        {
            yaxis = 90;
            _yaxis = -90;
             QPixmap img(":/pics/Imagens/rejeita_faixa.png");
             _filtro_passivo.rlc_dados(tipo_rlc());
             res = _filtro_passivo.calculo_filtro();
             ui->circuito->setPixmap(img);
             ui->calc_res->setNum(res);
             ui->res->setText("R = ");

             if (tipo_rlc() == 0)
             {
                 ui->rlc_label->setText("C = ");
                 ui->rlc_valor->setNum(_filtro_passivo.get_cap());
             }
             else if (tipo_rlc() == 1)
             {
                 ui->rlc_label->setText("L = ");
                 ui->rlc_valor->setNum(_filtro_passivo.get_ind());
             }
             else if (tipo_rlc() == 2)
             {
                 ui->rlc_label->setText("f = ");
                 ui->rlc_valor->setNum(_filtro_passivo.get_freq());
             }
             else if (tipo_rlc() == 3)
             {
                 ui->rlc_label->setText("b = ");
                 ui->rlc_valor->setNum(_filtro_passivo.get_banda());
             }

             bode = _filtro_passivo.bode_magnitude_rf();
             fase = _filtro_passivo.bode_fase_rf();
        }
    }
    for(double i = 0.0; i<((freq*multiplicador_freq)/(cap*multiplicador_cap)) ; i+=100)
        x.append(i);
    /*qDebug() << " MainWindow::configura_filtro limit" << ((freq*multiplicador_freq)/(cap*multiplicador_cap));
    qDebug() << " MainWindow::configura_filtro x.size" << x.size();
    qDebug() << " MainWindow::configura_filtro ind" << ind;
    qDebug() << " MainWindow::configura_filtro freq" << freq;*/
    plot_bode();
}

/* Plota o gráfico de Bode */
void MainWindow::plot_bode(void)
{
    ui->magnitude->clearItems();
    ui->magnitude->addGraph();
    ui->magnitude->graph(0)->setData(x,bode,1);
    ui->magnitude->xAxis->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    ui->magnitude->xAxis->setTicker(logTicker);
    ui->magnitude->xAxis->setRange(0, 10000000);
    ui->magnitude->yAxis->setRange(0,1);
    ui->magnitude->yAxis->setLabel("|H(f)|");
    ui->magnitude->xAxis->setLabel("f(Hz)");
    ui->magnitude->xAxis->grid();

    ui->fase->addGraph();
    ui->fase->graph(0)->setData(x,fase);
    //ui->fase->plotLayout()->insertRow(0);
    ui->fase->xAxis->setRange(0,100000);
    ui->fase->yAxis->setRange(_yaxis,yaxis);
    ui->fase->yAxis->setLabel("°");
    ui->fase->xAxis->setLabel("f(Hz)");

    ui->fase->replot();
    //ui->fase->plotLayout();
    ui->magnitude->replot();
}

void MainWindow::on_larg_banda_valor_valueChanged(double arg1)
{
    largura_banda = arg1;
    //qDebug() << "largura_banda" << largura_banda;
}

void MainWindow::on_larg_banda_mult_currentTextChanged(const QString &mult)
{
    if (mult == "Hz")
        multiplicador_largura_banda = 1;
    else if (mult == "kHz")
        multiplicador_largura_banda = 1000;
    else if (mult == "MHz")
        multiplicador_largura_banda = 1000000;
    else if (mult == "GHz")
        multiplicador_largura_banda = 1000000000;
    //qDebug() << "multiplicador_largura_banda" << multiplicador_largura_banda;
}

int MainWindow::tipo_rlc(void)
{
    int ret = 0;
    if (!ui->cap_radiobutton->isChecked())
        ret = 0;
    else if (!ui->ind_radiobutton->isChecked())
        ret = 1;
    else if (!ui->f_radiobutton->isChecked())
        ret = 2;
    else if (!ui->larg_banda_radiobutton->isChecked())
        ret = 3;
    return ret;
}
