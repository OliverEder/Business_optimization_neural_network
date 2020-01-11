#include "view_element.h"
#include "ui_view_element.h"

view_element::view_element(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view_element)
{
    ui->setupUi(this);
}

view_element::~view_element()
{
    delete ui;
}

void view_element::on_Cancelar_pushButton_clicked()
{
    this->close();
}

void view_element::get_json(QJsonObject obj, QString item_name, QString item_parent, QString item_block)
{
    QJsonArray arreglo_bloques;
    QJsonObject objeto_bloque;
    QJsonArray arreglo_elementos;
    QJsonObject objeto_elemento;
    QJsonArray arreglo_variantes;
    QJsonObject objeto_variante;

    obj_view=obj;
    arreglo_bloques = obj_view["bloques"].toArray();
    for (int b=0 ; b<arreglo_bloques.size() ; b++)
    {
        objeto_bloque = arreglo_bloques.at(b).toObject();
        if(objeto_bloque["Bloque"] == item_block)
        {
            arreglo_elementos = objeto_bloque["Elementos"].toArray();
            for (int e=0 ; e<arreglo_elementos.size() ; e++)
            {
                objeto_elemento = arreglo_elementos.at(e).toObject();
                if(objeto_elemento["Elemento"] == item_parent)
                {
                    arreglo_variantes = objeto_elemento["Variantes"].toArray();
                    for (int v=0 ; v<arreglo_variantes.size() ; v++)
                    {
                        objeto_variante = arreglo_variantes.at(v).toObject();
                        if(objeto_variante["Variante"] == item_name)
                        {
                            int id = objeto_variante["ID"].toInt();
                            //cout << id << endl;
                            ui->Variante_lineEdit->setText(objeto_variante["Variante"].toString());
                            ui->IdVariante_lineEdit->setText(QString::number(id));
                            ui->Egreso_doubleSpinBox->setValue(objeto_variante["Egreso"].toDouble());
                            ui->Ingreso_doubleSpinBox->setValue(objeto_variante["Ingreso"].toDouble());
                            ui->Ganancia_doubleSpinBox->setValue(objeto_variante["Ganancia"].toDouble());

                        }
                    }
                }
            }
        }
    }


    ui->NombreModelo_lineEdit->setText(obj["nombre"].toString());
    ui->Bloque_lineEdit->setText(item_block);
    ui->Elemento_lineEdit->setText(item_parent);
    ui->Variante_lineEdit->setText(item_name);

}

void view_element::on_pushButton_2_clicked()
{
    QJsonArray arreglo_bloques;
    QJsonObject objeto_bloque;
    QJsonArray arreglo_elementos;
    QJsonObject objeto_elemento;
    QJsonArray arreglo_variantes;
    QJsonObject objeto_variante;

    arreglo_bloques = obj_view["bloques"].toArray();
    for (int b=0 ; b<arreglo_bloques.size() ; b++)
    {
        objeto_bloque = arreglo_bloques.at(b).toObject();
        if(objeto_bloque["Bloque"] == ui->Bloque_lineEdit->text())
        {
            arreglo_elementos = objeto_bloque["Elementos"].toArray();
            for (int e=0 ; e<arreglo_elementos.size() ; e++)
            {
                objeto_elemento = arreglo_elementos.at(e).toObject();
                arreglo_variantes = objeto_elemento["Variantes"].toArray();
                for (int v=0 ; v<arreglo_variantes.size() ; v++)
                {
                    objeto_variante = arreglo_variantes.at(v).toObject();
                    int id_lineEdit = ui->IdVariante_lineEdit->text().toInt();
                    int id_obj = objeto_variante["ID"].toInt();
                    if(id_lineEdit == id_obj)
                    {
                        cout << id_lineEdit << " " << id_obj << endl;
                        objeto_variante["Variante"] =  ui->Variante_lineEdit->text();
                        objeto_variante["Egreso"] = ui->Egreso_doubleSpinBox->value();
                        objeto_variante["Ingreso"] =  ui->Ingreso_doubleSpinBox->value();
                        objeto_variante["Ganancia"] = ui->Ganancia_doubleSpinBox->value();
                        arreglo_variantes.replace(v, objeto_variante);
                        objeto_elemento["Variantes"] = arreglo_variantes;
                        arreglo_elementos.replace(e,objeto_elemento);
                        objeto_bloque["Elementos"] = arreglo_elementos;
                        arreglo_bloques.replace(b,objeto_bloque);
                        obj_view["bloques"] = arreglo_bloques;
                        emit(send_json(obj_view));
                        this->close();
                    }

                }
            }
        }
    }
}

void view_element::on_pushButton_3_clicked()
{
    QJsonArray arreglo_bloques;
    QJsonObject objeto_bloque;
    QJsonArray arreglo_elementos;
    QJsonObject objeto_elemento;
    QJsonArray arreglo_variantes;
    QJsonObject objeto_variante;

    arreglo_bloques = obj_view["bloques"].toArray();
    for (int b=0 ; b<arreglo_bloques.size() ; b++)
    {
        objeto_bloque = arreglo_bloques.at(b).toObject();
        if(objeto_bloque["Bloque"] == ui->Bloque_lineEdit->text())
        {
            arreglo_elementos = objeto_bloque["Elementos"].toArray();
            for (int e=0 ; e<arreglo_elementos.size() ; e++)
            {
                objeto_elemento = arreglo_elementos.at(e).toObject();
                arreglo_variantes = objeto_elemento["Variantes"].toArray();
                for (int v=0 ; v<arreglo_variantes.size() ; v++)
                {
                    objeto_variante = arreglo_variantes.at(v).toObject();
                    int id_lineEdit = ui->IdVariante_lineEdit->text().toInt();
                    int id_obj = objeto_variante["ID"].toInt();
                    if(id_lineEdit == id_obj)
                    {
                        cout << id_lineEdit << " " << id_obj << endl;
                        arreglo_variantes.removeAt(v);
                        objeto_elemento["Variantes"] = arreglo_variantes;
                        arreglo_elementos.replace(e,objeto_elemento);
                        objeto_bloque["Elementos"] = arreglo_elementos;
                        arreglo_bloques.replace(b,objeto_bloque);
                        obj_view["bloques"] = arreglo_bloques;
                        emit(send_json(obj_view));
                        this->close();
                    }

                }
            }
        }
    }

}

void view_element::on_Ingreso_doubleSpinBox_valueChanged(double arg1)
{
    ui->Ganancia_doubleSpinBox->setValue(ui->Ingreso_doubleSpinBox->value()-ui->Egreso_doubleSpinBox->value());
}

void view_element::on_Egreso_doubleSpinBox_valueChanged(double arg1)
{
    ui->Ganancia_doubleSpinBox->setValue(ui->Ingreso_doubleSpinBox->value()-ui->Egreso_doubleSpinBox->value());
}
