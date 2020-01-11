#ifndef VIEW_ELEMENT_H
#define VIEW_ELEMENT_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <qjsonvalue.h>
#include <iostream>

using namespace std;
namespace Ui {
class view_element;
}

class view_element : public QDialog
{
    Q_OBJECT

public:
    explicit view_element(QWidget *parent = nullptr);
    ~view_element();

private slots:
    void on_Cancelar_pushButton_clicked();

    void get_json(QJsonObject obj, QString item_name, QString item_parent, QString item_block);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_Ingreso_doubleSpinBox_valueChanged(double arg1);

    void on_Egreso_doubleSpinBox_valueChanged(double arg1);

signals:
    void send_json(QJsonObject obj);

private:
    Ui::view_element *ui;
    QJsonDocument doc;
    QJsonObject obj_view;
    QJsonArray bloc_aray;
};

#endif // VIEW_ELEMENT_H
