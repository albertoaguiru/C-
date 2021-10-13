// Autor: Alberto Aguilar
// Fecha: Junio de 2021

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Flowchart.h"
#include <Test.h>
#include <BoxController.h>
#include <Diagram.h>
#include <CircularDiagram.h>
#include <RectangularDiagram.h>


using namespace example;

namespace vista
{


    class Flowchart : public QMainWindow
    {
        Q_OBJECT

    public:
        Flowchart(QWidget *parent = Q_NULLPTR);
        Test test;
    private:

        /**
        * Ventana del programa
        */
        Ui::FlowchartClass ui;



    public slots:

        /**
        * Metodo que es llamado al seleccionar un diagrama
        */
        void selected_diagram();

        /**
        * Metodo que es llamado al darle a trigger de conectar diagrama
        */
        void connect_diagram_action();

        /**
        * Metodo que es llamado al seleccionar el trigger de crear un rombo
        */
        void create_rectangle_action();

        /**
        * Metodo que es llamado al seleccionar el trigger de crear circulo
        */
        void create_circle_action();

        /**
        * Metodo que es llamado al darle al boton de crear diagrama
        */
        void create_diagram_button();

        /**
        * Metodo que es llamado al cambiar el texto del diagrama
        */
        void changed_text();

        /**
         * Metodo que es llamado al darle al trigger de desconectar diagrama
         */
        void disconnect_diagram_action();

        /**
         * Metodo que es llamado al darle al trigger de borrar diagrama
         */
        void delete_diagram_action();



    private:
        /**
        * Escena grafica donde se dibuja todo
        */
        QGraphicsScene *graphic_scene;

   

        /**
        * Variable que indica el tipo de diagrama que se creara(circular o rombo)
        */
        Type type_creation;

        /**
        * Controlador de los diagramas
        */
        std::shared_ptr<BoxController> box_controller;

        /**
        * Diagrama seleccionado para conectarlo con otro
        */
        Diagram* connection_diagram;

        /**
        * Se crea un diagrama
        * @param text Nombre del diagrama
        * @param type tipo que puede ser rombo o circulo
        */
        Diagram* create_diagram(QString text, Type type);

        /**
         * Conecta dos diagramas
         * @param a diagrama de input
         * @param b diagrama de output
         */
        void connect_diagram(Diagram* a, Diagram* b);
    };

}