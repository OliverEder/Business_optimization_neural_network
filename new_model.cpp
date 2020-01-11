#include "new_model.h"
#include "ui_new_model.h"
#include <QMessageBox>

new_model::new_model(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_model)
{
    ui->setupUi(this);
}

new_model::~new_model()
{
    delete ui;
}

void new_model::on_cancelar_pushButton_clicked()
{
    ui->nombre_lineEdit->setText("");
    ui->descripcion_textEdit->setText("");
    this->close();
}

void new_model::on_ok_pushButton_clicked()
{
    if(ui->nombre_lineEdit->text()=="" || ui->descripcion_textEdit->toPlainText().size()==0)
    {
        QMessageBox msgBox;
        msgBox.setText("Los campos no pueden ir vacios");
        msgBox.setIcon(QMessageBox::Information	);
        QDialog::show();
        msgBox.exec();

    }
    else {

       QString nombre_modelo;
       QString descripcion;

       nombre_modelo = ui->nombre_lineEdit->text();
       descripcion = ui->descripcion_textEdit->toPlainText();
       ui->nombre_lineEdit->setText("");
       ui->descripcion_textEdit->setText("");
       emit(info_nuevo_modelo(nombre_modelo,descripcion));
       this->close();
    }
}
