// Autor: Alberto Aguilar
// Fecha: Junio de 2021

#pragma once


#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <vector>
#include <BoxController.h>
#include <QVector2D>

namespace vista
{

    /**
    * Clase base de los diagramas
    */
    class Diagram
    {

        public:

        Diagram(QString name, int w, int h, QGraphicsScene* scene, shared_ptr<BoxController> controller) :
        from_line(nullptr), box_controller(controller), text(name), graphic_scene(scene), width(w), height(h), from_diagram(nullptr)
        {
         }

        protected:
        /**
        *  Texto que se ve en el diagrama
        */
        QString text;

        /**
        * Objeto que muestra el texto
        */
        QGraphicsTextItem* graphic_text;

        /**
        * Controlador del back end
        */
        std::shared_ptr<BoxController> box_controller;

        /**
        * Controlador de cajas del Back end
        */
        vector< QGraphicsEllipseItem*> end_circles;

        /**
        * Controlador de cajas del Back end
        */
        vector< QGraphicsLineItem* > to_lines;

        /**
        * Lista de diagramas que apuntan hacia mi
        */
        vector<Diagram*> pointing_me;

        /**
        * Objeto que dibuja una linea que va desde este diagrama hacia otro
        */
        QGraphicsLineItem* from_line;

        /**
        * Diagrama hacia el que se apunta
        */
        Diagram* from_diagram;

        /**
        * Escena grafica donde se dibujan los objetos
        */
        QGraphicsScene* graphic_scene; 

        /**
        * Ancho del diagrama
        */
        float width;

        /**
        * Alto del diagrama
        */
        float height;


        /**
        * Caja con los datos del diagrama
        */
        shared_ptr<Box> box;
        public:
 
        /**
        * Devuelve la linea que sale de este diagrama y va hacia otro
        */
        QGraphicsLineItem* get_from_line()
        {
            return from_line;
        }

        /**
        * Anade una linea que conecta desde otro diagrama a este
        * @param line Linea que se anade
        */
        void add_to_line(QGraphicsLineItem* line);
       
    
        /**
        * Anade una linea que conecta de este a otro
        * @param d diagrama hacia el que se conecta
        * @param line linea que se anade
        */
        void set_from_connection(Diagram* d, QGraphicsLineItem* line);

        /**
        * Devuelve el diagrama hacia el que esta conectado
        */
        Diagram* get_from_diagram()
        {
            return from_diagram;
        }

        /**
        * Devuelve el nombre del diagrama
        */
        string get_name()
        {
            return text.toStdString();
        }

        /**
        * Elimina una linea que va de otro diagrama a este
        */
        void delete_to_line(QGraphicsLineItem* line);
        
        /*
        *   Se llama para borrar el objeto. Borra todos sus graficos para que desaparezca de la escena
        */
        void delete_all();

        /**
        * Actualiza la posicion del circulo rojo de conexion
        */
        void update_end_circle(QGraphicsEllipseItem* end_circle, QLineF line);

        /**
        * Actualiza la posicion del circulo rojo de conexion
        */
        void update_end_circle(QLineF line);
    };
}