#include "add_element.h"
#include "ui_add_element.h"
#include <QJsonObject>
#include <QJsonArray>
#include <qjsonvalue.h>
#include <QDebug>
#include <QMessageBox>

add_element::add_element(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_element)
{
    ui->setupUi(this);
}

add_element::~add_element()
{
    delete ui;
}
void add_element::get_json(QJsonObject obj)
{
    //cout << "get_json" << endl;
    obj_agregarElemento=obj;
    ui->Elemento_comboBox->setEnabled(false);
    ui->Variante_comboBox->setEnabled(false);
    ui->NombreModelo_lineEdit->setText(obj["nombre"].toString());
    //se verifica que el objeto json contenga el campo bloques
    if(obj.contains("bloques"))
    {
        //Se verifica si el campo bloques contiene un arreglo
        if(obj["bloques"].isArray())
        {
            //Se genera un nuevo arreglo para los bloques
            QJsonArray arreglo_bloques;
            //Se copia el arreglo del objeto al arreglo recien creado
            arreglo_bloques=obj["bloques"].toArray();
            //se recorre el arreglo
            for(int i=0 ; i < arreglo_bloques.size() ; i++)
            {
                //se genera un nuevo objeto json
                QJsonObject objeto_bloque;
                //Se copia cada objeto del arreglo en el nuevo objeto json
                objeto_bloque= arreglo_bloques.at(i).toObject();
                //se copia el nombre de cada objeto y se agrega al combo box
                ui->Bloque_comboBox->addItem(objeto_bloque.value("Bloque").toString());
            }

        }
        else
        {
            cout << "no es un arreglo" << endl;
        }

    }
}

void add_element::on_OK_pushButton_clicked()
{
    if(ui->Bloque_comboBox->currentText().isEmpty() && ui->Elemento_comboBox->currentText().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Los campos no pueden ir vacios");
        msgBox.setIcon(QMessageBox::Information	);
        QDialog::show();
        msgBox.exec();
    }
    else
    {
        //Se envian los datos del formulario
        QString bloque =  ui->Bloque_comboBox->currentText();
        QString elemento = ui->Elemento_comboBox->currentText();
        QString variante = ui->Variante_comboBox->currentText();
        int idVariante = ui->IdVariante_lineEdit->text().toInt();
        double ingreso = ui->Ingreso_doubleSpinBox->value();
        double egreso = ui->Egreso_doubleSpinBox->value();
        double ganancia = ui->Ganancia_doubleSpinBox->value();

        //emitir la señal
        emit(send_new_elemento(bloque, elemento, variante, idVariante, ingreso, egreso, ganancia));
        ui->Bloque_comboBox->clear();
        ui->Elemento_comboBox->clear();
        ui->Variante_comboBox->clear();
        ui->Ingreso_doubleSpinBox->setValue(0);
        ui->Egreso_doubleSpinBox->setValue(0);
        ui->Ganancia_doubleSpinBox->setValue(0);
        this->close();
    }
}

void add_element::on_Ingreso_doubleSpinBox_valueChanged(double arg1)
{
    ui->Ganancia_doubleSpinBox->setValue(ui->Ingreso_doubleSpinBox->value()-ui->Egreso_doubleSpinBox->value());
}

void add_element::on_Egreso_doubleSpinBox_valueChanged(double arg1)
{
    ui->Ganancia_doubleSpinBox->setValue(ui->Ingreso_doubleSpinBox->value()-ui->Egreso_doubleSpinBox->value());
}

void add_element::on_Bloque_comboBox_currentIndexChanged(const QString &arg1)
{
    QJsonArray arreglo_bloques;
    QJsonObject objeto_bloque;
    QString bloque_currentText = ui->Bloque_comboBox->currentText();
    ui->Elemento_comboBox->clear();
    ui->Elemento_comboBox->setEnabled(true);
    ui->Variante_comboBox->setEnabled(true);

    arreglo_bloques=obj_agregarElemento["bloques"].toArray();
    for(int i=0 ; i < arreglo_bloques.size() ; i ++)
    {
        objeto_bloque = arreglo_bloques.at(i).toObject();
        if(objeto_bloque.value("Bloque").toString() == bloque_currentText)
        {
            if(objeto_bloque.value("Elementos").isArray())
            {
                QJsonArray elementos;
                QJsonObject elemento;
                elementos = objeto_bloque.value("Elementos").toArray();
                for(int i=0 ; i< elementos.size(); i++)
                {
                    elemento= elementos.at(i).toObject();
                    ui->Elemento_comboBox->addItem(elemento.value("Elemento").toString());
                }
            }
            else
            {
                ui->Elemento_comboBox->clear();
            }
        }
    }
}

void add_element::on_Elemento_comboBox_currentTextChanged(const QString &arg1)
{
    QJsonArray arreglo_bloques;
    QJsonObject objeto_bloque;

    QJsonArray arreglo_elementos;
    QJsonObject objeto_elemento;

    QJsonArray arreglo_variantes;
    QJsonObject objeto_variante;
    QString bloque_currentText = ui->Bloque_comboBox->currentText();
    QString elemento_currentText = ui->Elemento_comboBox->currentText();
    ui->Variante_comboBox->clear();
    arreglo_bloques=obj_agregarElemento["bloques"].toArray();
    for(int i=0; i< arreglo_bloques.size() ; i++)
    {
        objeto_bloque=arreglo_bloques.at(i).toObject();
        if(objeto_bloque.value("Bloque").toString() == bloque_currentText)
        {
            if(objeto_bloque.value("Elementos").isArray())
            {
                arreglo_elementos=objeto_bloque.value("Elementos").toArray();
                for(int j=0 ;  j< arreglo_elementos.size() ; j++)
                {
                    objeto_elemento=arreglo_elementos.at(j).toObject();
                    if(objeto_elemento.value("Elemento").toString() == elemento_currentText)
                    {
                        if(objeto_elemento.value("Variantes").isArray())
                        {
                            arreglo_variantes= objeto_elemento.value("Variantes").toArray();
                            for(int k=0 ; k<arreglo_variantes.size() ; k++)
                            {
                                objeto_variante=arreglo_variantes.at(k).toObject();
                                ui->Variante_comboBox->addItem(objeto_variante.value("Variante").toString());
                            }
                        }
                        else
                        {
                            ui->Variante_comboBox->clear();
                        }
                    }
                    else
                    {
                        ui->Variante_comboBox->clear();
                    }
                }
            }
            else
            {
                ui->Variante_comboBox->clear();
            }
        }
    }
}
