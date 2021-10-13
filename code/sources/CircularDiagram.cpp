// Autor: Alberto Aguilar
// Fecha: Junio de 2021

#include "CircularDiagram.h"

vista::CircularDiagram::CircularDiagram(QString name, int x, int y, int w, int h, QGraphicsScene* scene, shared_ptr<BoxController> controller)
:
    QGraphicsEllipseItem(x, y, w, h), Diagram(name, w, h, scene, controller)
{
    // Esto permite mover el objeto y recibir notificacion de que se ha movido

    setFlags
    (
        QGraphicsItem::ItemIsSelectable
        | QGraphicsItem::ItemIsMovable
        | QGraphicsItem::ItemSendsGeometryChanges
    );
    string n = text.toStdString();

    // Creacion del box

    box_controller->create_box(n, Type::rectangle, vec2(x, y), w, h);
    box = box_controller->get_box(n);

    // Creacion del texto

    graphic_text = new QGraphicsTextItem(text);
    float width = graphic_text->textWidth();
    QPointF center(box->get_center().x - w / 2, box->get_center().y - h / 2);
    graphic_text->setPos(center);
    graphic_text->setZValue(1);

    graphic_scene->addItem(graphic_text);

    //Seleccion de los colores

    QPen pen(Qt::red);
    setPen(pen);
    pen.setWidth(4);
    setBrush(Qt::white);
}

QVariant vista::CircularDiagram::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
  if (change == GraphicsItemChange::ItemPositionHasChanged)
    {
        string name = text.toStdString();
        box = box_controller->get_box(name);

        // ACtualizacion de la posicion

        QPointF newPos = value.toPointF();

        box_controller->set_box_location(name, vec2(newPos.x(), newPos.y()));

        QPointF center(box->get_center().x, box->get_center().y);


        QPointF text_pos(box->get_center().x - width / 2, box->get_center().y - height / 2);
        graphic_text->setPos(text_pos);

        // Actualizacion de las lineas de entrada
        for (int i = 0; i < to_lines.size(); i++)
        {
            QLineF old_line = to_lines[i]->line();

            QLineF new_line(old_line.p1(), center);

            to_lines[i]->setLine(new_line);

            QPointF direction = new_line.p2() - new_line.p1();

            update_end_circle(end_circles[i], new_line);

        }

        // Actualizacion de la linea de salida
        if (from_line != nullptr)
        {
            QLineF old_line = from_line->line();

            QLineF new_line(center, old_line.p2());

            from_line->setLine(new_line);

            get_from_diagram()->update_end_circle(new_line);
        }
    }

    return __super::itemChange(change, value);
}
