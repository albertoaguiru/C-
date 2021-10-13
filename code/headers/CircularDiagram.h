// Autor: Alberto Aguilar
// Fecha: Junio de 2021

#pragma once

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <vector>
#include <BoxController.h>
#include <Diagram.h>

namespace vista
{
    /*
    * Clase del diagrama Circular. Hereda de una elipse y de un diagrama
    */
    class CircularDiagram : public QGraphicsEllipseItem, public Diagram
    {
    public:
        CircularDiagram(QString name, int x, int y, int w, int h, QGraphicsScene *scene, shared_ptr<BoxController> controller);

        // QGraphicItem overrides
        /**
        * Metodo que es llamado por QT cuando se mueve un diagrama
        */
        virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value) override;
 
    };
}