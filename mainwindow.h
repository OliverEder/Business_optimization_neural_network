#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <qjsonvalue.h>
#include <QTreeWidgetItem>

#include "new_model.h"
#include "add_element.h"
#include "view_element.h"

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class new_model;
class add_element;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    typedef QList<int> nodo;
    typedef QList<double> nodo_dist;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void json_add_element(QJsonObject obj);

    void json_view_element(QJsonObject obj, QString item_name, QString item_parent, QString item_block);

private slots:
    void on_actionCerrar_triggered();

    void on_actionNuevo_triggered();

    QJsonObject generar_modelo_json(QString nombre_modelo, QString descripcion);

    void recibir_nuevoElemento(QString, QString, QString, int, double, double, double);

    void recibir_nuevo_modelo(QString, QString);

    void fill_treewidgets(QJsonObject obj);

    void on_actionAgregar_elemento_triggered();

    void clear_trees();

    void on_actionAbrir_triggered();

    void on_actionGuardar_triggered();

    void on_actionOptimizar_triggered();

    void optimizar(QString);

    void generar_tensor(QJsonObject);

    void calcular_maximo(QString, double *, QJsonObject);

    void generar_tensor_max(QString cadena,double *max, QJsonObject obj);

    void generar_raiz(QList<nodo> *nodos_raiz, QList<nodo_dist> *nodos_raiz_dist);

    void generar_combinatoria(QList<nodo> *nodos_raiz, QList<nodo> *nodos_grafo, QList<nodo_dist> *nodos_raiz_dist, QList<nodo_dist> *nodos_grafo_dist);

    void generar_matriz_adyacencias(QList<nodo> *nodos_grafo, QList<nodo_dist> *nodos_grafo_dist);

    void initial_distances(int **puntero_matrizU, QList<nodo> *nodos_grafo ,int nodo_s);

    int initial_min( int **puntero_matrizU, QList<nodo> *nodos_grafo ,int nodo_s);

    void pulse_generator(int **puntero_matrizU, int **puntero_matrizY ,QList<nodo> *nodos_grafo, list <int> *historico, list <int> *agenda, int *E_umbral);

    void linking_modulation(int **puntero_matrizU, QList<nodo> *nodos_grafo , list <int> *agenda, int *E_umbral);

    int min_linking(int **puntero_matrizU, list <int> *historico, QList<nodo> *nodos_grafo, int *E_umbral);

    void high_linking(int **puntero_matrizU, list <int> *historico, QList<nodo> *nodos_grafo);

    int stop_condition(int **puntero_matrizY,QList<nodo> *nodos_grafo, int nodo_g,int pulsofinal);

    void SAMPCNN(QList<nodo> *nodos_grafo, QList<nodo_dist> *nodos_grafo_dist, list<int> *ruta, QMap<QString, int> *resultados_ruta);

    void show_report(QJsonObject modelo_optimizado, QString cadena);

    void generar_reporte(QString cadena,QList<nodo> *nodos_grafo, list<int> *ruta, QMap<QString, int> *resultados_ruta);

    void on_Actions_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Asociations_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void get_json_view(QJsonObject obj_view);

    void on_Resources_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Value_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Channels_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Segments_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Relations_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_Ingress_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    new_model *new_model_window;
    add_element *add_element_window;
    view_element *view_element_window;

    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray bloc_aray;
};
#endif // MAINWINDOW_H
