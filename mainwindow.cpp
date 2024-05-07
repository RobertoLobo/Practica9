#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Clases.h"
#include <QFileDialog>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    adminNeuronas = new AdminNeuronas();
    adminGrafo = new AdminGrafo();
    ui->setupUi(this);
    inicializar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inicializar(){
    ui->graphicsView->setScene(&escena);
    ui->graphicsView_2->setScene(&escenaGrafo);
    //escena.clear();
}

void MainWindow::on_actionAbrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"./",tr("Text (*.txt)"));
    QString text;
    adminNeuronas->limpiar();
    ui->cSalida->clear();
    adminNeuronas->cargarNeuronas(fileName.toStdString());
    for (Neurona *n : adminNeuronas->dameNeuronas()){
        text.append("ID: " + std::to_string(n->getId()) + "\n");
        text.append("Voltaje: " + std::to_string(n->getVoltaje()) + "\n");
        text.append("Cord X: " + std::to_string(n->getX()) + "\n");
        text.append("Cord Y: " + std::to_string(n->getY()) + "\n");
        text.append("Red: " + std::to_string(n->getRed()) + "\n");
        text.append("Green: " + std::to_string(n->getGreen()) + "\n");
        text.append("Blue: " + std::to_string(n->getBlue()) + "\n###\n");
    }
    //n2 = adminNeuronas->dameNeurona();
    ui->cNumNeuronas->setValue(adminNeuronas->dameCuenta());
    ui->cSalida->appendPlainText(text);
}


void MainWindow::on_actionGuardar_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"./untitled.png",
                                                    tr("Text (*.txt)"));
    adminNeuronas->guardarNeuronas(fileName.toStdString());
}


void MainWindow::on_btnACola_clicked()
{
    auto neurona = new Neurona();
    neurona->putId(ui->lineEdit->text().toInt());
    neurona->putVoltaje(ui->lineEdit_2->text().toFloat());
    neurona->putX(ui->lineEdit_3->text().toInt());
    neurona->putY(ui->lineEdit_4->text().toInt());
    neurona->putRed(ui->lineEdit_5->text().toInt());
    neurona->putGreen(ui->lineEdit_6->text().toInt());
    neurona->putBlue(ui->lineEdit_7->text().toInt());
    adminNeuronas->agregarCola(neurona);
}


void MainWindow::on_btnAPila_clicked()
{
    auto neurona = new Neurona();
    neurona->putId(ui->lineEdit->text().toInt());
    neurona->putVoltaje(ui->lineEdit_2->text().toFloat());
    neurona->putX(ui->lineEdit_3->text().toInt());
    neurona->putY(ui->lineEdit_4->text().toInt());
    neurona->putRed(ui->lineEdit_5->text().toInt());
    neurona->putGreen(ui->lineEdit_6->text().toInt());
    neurona->putBlue(ui->lineEdit_7->text().toInt());
    adminNeuronas->agregarPila(neurona);
}


void MainWindow::on_btnListar_clicked()
{
    QString text;
    ui->cSalida->clear();
    for (Neurona *n : adminNeuronas->dameNeuronas()){
        text.append("ID: " + std::to_string(n->getId()) + "\n");
        text.append("Voltaje: " + std::to_string(n->getVoltaje()) + "\n");
        text.append("Cord X: " + std::to_string(n->getX()) + "\n");
        text.append("Cord Y: " + std::to_string(n->getY()) + "\n");
        text.append("Red: " + std::to_string(n->getRed()) + "\n");
        text.append("Green: " + std::to_string(n->getGreen()) + "\n");
        text.append("Blue: " + std::to_string(n->getBlue()) + "\n###\n");
    }
    //n2 = adminNeuronas->dameNeurona();
    ui->cNumNeuronas->setValue(adminNeuronas->dameCuenta());
    ui->cSalida->appendPlainText(text);
}


void MainWindow::on_btnActualizar_clicked()
{
    //ui->tabla = new QTableWidget();
    short fila = 0;
    short columna = 0;
    //QTableWidgetItem *newItem;
    ui->tabla->clear();
    //ui->tabla->clearContents();

    //newItem = new QTableWidgetItem("Whoop");
    //ui->tabla->setRowCount(10);
    ui->tabla->setColumnCount(7);
    //ui->tabla->insertRow(fila);
    //ui->tabla->setItem(fila, columna++, newItem);

    for (Neurona *n : adminNeuronas->dameNeuronas()){
        columna = 0;
        //newItem = new QTableWidgetItem(QString::fromStdString(std::to_string(n->getId())));
        ui->tabla->insertRow(fila);
        ui->tabla->setItem(fila, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getId()))));
        ui->tabla->setItem(fila, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getVoltaje()))));
        ui->tabla->setItem(fila, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getX()))));
        ui->tabla->setItem(fila, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getY()))));
        ui->tabla->setItem(fila, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getRed()))));
        ui->tabla->setItem(fila, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getGreen()))));
        ui->tabla->setItem(fila++, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getBlue()))));

        //newItem = new QTableWidgetItem(datos.pop_back());
        //ui->tabla->setItem(fila, columna+1, newItem);
    }

    ui->tabla->setHorizontalHeaderLabels({"ID", "Voltaje", "Cord X", "Cord Y", "RED", "GREEN", "BLUE"});
    ui->cNumNeuronas->setValue(adminNeuronas->dameCuenta());
    //ui->tabla->show();
}

void MainWindow::on_btnBuscar_clicked()
{
    Neurona * n;
    short columna = 0;
    n = adminNeuronas->buscarID(ui->cBuscar->text().toInt());
    ui->tabla->clearContents();
    if(ui->cBuscar->text() != "" && n){
        ui->tabla->insertRow(ui->tabla->rowCount());
        ui->tabla->setItem(0, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getId()))));
        ui->tabla->setItem(0, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getVoltaje()))));
        ui->tabla->setItem(0, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getX()))));
        ui->tabla->setItem(0, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getY()))));
        ui->tabla->setItem(0, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getRed()))));
        ui->tabla->setItem(0, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getGreen()))));
        ui->tabla->setItem(0, columna++, new QTableWidgetItem(QString::fromStdString(std::to_string(n->getBlue()))));
    }
}


void MainWindow::on_btnGraficar_clicked()
{
    escena.clear();
    QPen lapiz;
    if (ui->cbModo->currentIndex() == 1){ // Modo Puntos
        for (Neurona *n : adminNeuronas->dameNeuronas()){
            QColor color(n->getRed(), n->getGreen(), n->getBlue());
            lapiz.setColor(color);
            QBrush pincel(color);
            escena.addEllipse(n->getX(), n->getY(), 5, 5, lapiz, pincel);
        }
        //QRandomGenerator::global()->bounded(1,900)
    }
    else if (ui->cbModo->currentIndex() == 2){ // Modo Circulos
        for (Neurona *n : adminNeuronas->dameNeuronas()){
            QColor color(n->getRed(), n->getGreen(), n->getBlue());
            lapiz.setColor(color);
            QBrush pincel(color, Qt::CrossPattern);
            escena.addEllipse(n->getX(), n->getY(), n->getVoltaje(), n->getVoltaje(), lapiz, pincel);
        }
    }
    escena.update();
    ui->graphicsView->update();
}


void MainWindow::on_cbOrdernar_currentTextChanged(const QString &arg1)
{
    if (ui->cbOrdernar->currentText().toStdString() == "ID (Asc)")
        adminNeuronas->ordenarID();
    else if (ui->cbOrdernar->currentText().toStdString() == "Voltaje")
        adminNeuronas->ordenarVoltaje();
}


void MainWindow::on_cbModo_currentTextChanged(const QString &arg1)
{

}


void MainWindow::on_btnLocalizar_clicked()
{
    QVector<QPointF> puntos;
    int i = 0;
    for (Neurona * n : adminNeuronas->dameNeuronas()) {
        puntos.push_back(QPointF(n->getX(), n->getY()));

    }
    /*QPair<QPointF, QPointF> par = adminNeuronas->parMasCercanos();
    escena.addLine(par.first.x(), par.first.y(), par.second.x(), par.second.y(), QPen(Qt::red));*/
    for (QPointF punto : adminNeuronas->puntosMasCercanos(puntos)){
        escena.addLine(punto.x(), punto.y(), puntos[i].x(), puntos[i].y(), QPen());
        //adminGrafo->AgregarNodo(punto.);
        i++;
    }

    escena.update();
    ui->graphicsView->update();
}


void MainWindow::on_btnGraficarGrafo_clicked()
{
    escenaGrafo.clear();
    adminGrafo->limpiar();
    QPen lapiz;
    for (Neurona *n : adminNeuronas->dameNeuronas()){
        adminGrafo->AgregarVertice(n->getId(), n->getX(), n->getY());
    }

    adminGrafo->generarAdyacencias();
    adminGrafo->ImprimeAdyacencia();

    QString text;
    ui->cSalidaGrafo->clear();
    for (auto nodo : adminGrafo->dameNodos()) {
        QColor color(0, 0, 0);
        lapiz.setColor(color);
        QBrush pincel(color);


        escenaGrafo.addEllipse(nodo->x, nodo->y, 5, 5, lapiz, pincel);
        QGraphicsTextItem *label = escenaGrafo.addText(QString::number(nodo->id));
        label->setPos(nodo->x - 15, nodo->y - 10);

        text.append("NID: " + std::to_string(nodo->id) + " (X:"+std::to_string(nodo->x)+" ,Y:"+ std::to_string(nodo->y)+") -> ");
        for (auto& edge : nodo->dameAdyacencias()) {
            Vertice * verticeAdyacente = adminGrafo->dameVertice(edge.first->id);
            escenaGrafo.addLine(nodo->x, nodo->y, verticeAdyacente->x, verticeAdyacente->y, QPen(Qt::black));
            //QGraphicsTextItem *weightLabel = escenaGrafo.addText(QString::number(edge.second));
            //weightLabel->setPos((nodo->x + verticeAdyacente->x) / 2, (nodo->y + verticeAdyacente->y) / 2);

            text.append("[ NID: " + std::to_string(edge.first->id) + ", Distance:"+std::to_string(edge.second)+"] , ");
        }
        text.append("\n");
    }
    //n2 = adminNeuronas->dameNeurona();
    ui->cNumNeuronas->setValue(adminNeuronas->dameCuenta());
    ui->cSalidaGrafo->appendPlainText(text);
    /*
    for (Vertice* v : adminGrafo->dameAdyacencias()){
        QColor color(n->getRed(), n->getGreen(), n->getBlue());
        lapiz.setColor(color);
        QBrush pincel(color);


        escenaGrafo.addEllipse(v->x, v->y, 5, 5, lapiz, pincel);
        QGraphicsTextItem *label = escenaGrafo.addText(QString::number(v->id));
        label->setPos(v->x - 5, v->y - 5);

        for (auto& edge : v->adyacencia) {


            escenaGrafo.addLine(edge.x, edge.y, edge.siguiente->x, edge.siguiente->y, QPen(Qt::black));

            QGraphicsTextItem *weightLabel = escenaGrafo.addText(QString::number(edge.peso));
            weightLabel->setPos((edge.anterior->x + edge.siguiente->x) / 2, (edge.anterior->y + edge.siguiente->y) / 2);
        }


    }*/
    escenaGrafo.update();
    ui->graphicsView_2->update();
}

