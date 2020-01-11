#ifndef ADD_ELEMENT_H
#define ADD_ELEMENT_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <qjsonvalue.h>
#include <iostream>

using namespace std;
namespace Ui {
class add_element;
}

class add_element : public QDialog
{
    Q_OBJECT

public:
    explicit add_element(QWidget *parent = nullptr);
    ~add_element();

private slots:

    void get_json(QJsonObject obj);

    void on_OK_pushButton_clicked();

    void on_Ingreso_doubleSpinBox_valueChanged(double arg1);

    void on_Egreso_doubleSpinBox_valueChanged(double arg1);

    void on_Bloque_comboBox_currentIndexChanged(const QString &arg1);

    void on_Elemento_comboBox_currentTextChanged(const QString &arg1);

signals:
    void send_new_elemento(QString bloque, QString elemento, QString variante, int idVariante, double ingreso, double egreso, double ganancia);

private:
    Ui::add_element *ui;
    QJsonDocument doc;
    QJsonObject obj_agregarElemento;
    QJsonArray bloc_aray;
};

#endif // ADD_ELEMENT_H
