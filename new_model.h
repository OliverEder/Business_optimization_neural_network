#ifndef NEW_MODEL_H
#define NEW_MODEL_H

#include <QDialog>

namespace Ui {
class new_model;
}

class new_model : public QDialog
{
    Q_OBJECT

public:
    explicit new_model(QWidget *parent = nullptr);
    ~new_model();

signals:
    void info_nuevo_modelo(QString,QString);

private slots:
    void on_cancelar_pushButton_clicked();

    void on_ok_pushButton_clicked();

private:
    Ui::new_model *ui;
};

#endif // NEW_MODEL_H
