// Autor: Alberto Aguilar
// Fecha: Junio de 2021

#include <Diagram.h>

namespace vista
{ 

    void Diagram::add_to_line(QGraphicsLineItem* line)
    {
        to_lines.push_back(line);

        //El circulo de conexion
        QGraphicsEllipseItem* item = new QGraphicsEllipseItem(0, 0, 30, 30);

        //Setting color

        item->setZValue(2);
        QPen pen(Qt::black);

        item->setPen(pen);
        pen.setWidth(4);
        item->setBrush(Qt::red);
        item->setTransformOriginPoint(0, 0);

        // Update de la posicion del circulo del final que indica que es una conexion de entrada
        update_end_circle(item, line->line());

        graphic_scene->addItem(item);
        end_circles.push_back(item);
    }

    void Diagram::set_from_connection(Diagram* d, QGraphicsLineItem* line)
    {
        from_diagram = d;
        from_line = line;
        if (d != nullptr)
        {
            d->pointing_me.push_back(this);
        }
    }

    void Diagram::delete_to_line(QGraphicsLineItem* line)
    {
        for (int i = 0; i < to_lines.size(); i++)
        {
            //Si es la linea que se quiere borrar se borra
            if (line == to_lines[i])
            {
                QGraphicsLineItem* line = to_lines[i];

                to_lines.erase(to_lines.begin() + i);
                delete line;

                QGraphicsEllipseItem* end_circle = end_circles[i];
                end_circles.erase(end_circles.begin() + i);
                delete end_circle;

                return;
            }
        }
    }
    void Diagram::delete_all()
    {
        //Se pone nulos los punteros que tengan a este objeto para que no accedan nunca a este diagrama

        for (int i = 0; i < pointing_me.size(); i++)
        {
            pointing_me[i]->set_from_connection(nullptr, nullptr);
        }

        // Borrado de todas las lineas que tenga de entrada
        for (int i = 0; i < to_lines.size(); i++)
        {     
            QGraphicsLineItem* line = to_lines[i];
            delete line;

            QGraphicsEllipseItem* end_circle = end_circles[i];
            delete end_circle;
        }

        to_lines.clear();
        end_circles.clear();

        //Borrado de la linea de salida
        if (from_line != nullptr)
        {
            Diagram* c = from_diagram;
            c->delete_to_line(from_line);
            set_from_connection(nullptr, nullptr);
        }

        graphic_scene->removeItem(graphic_text);

    }

    void Diagram::update_end_circle(QGraphicsEllipseItem *end_circle, QLineF line)
    {
        QVector2D a(line.p1().x(), line.p1().y());
        QVector2D b(line.p2().x(), line.p2().y());

        QVector2D direction = a - b;

        direction.normalize();

        QPointF center(box->get_center().x, box->get_center().y);
        float distance = width / 2;
        QVector2D final_p = QVector2D(b.x() - 15, b.y() - 15);

        //La posicion del circulo rojo de entrada es la direccion por la distancia
        final_p += direction * distance;
        end_circle->setPos(final_p.x(), final_p.y());
    }

    void Diagram::update_end_circle(QLineF line)
    {
        for (int i = 0; i < end_circles.size(); i++)
        {
            if (to_lines[i]->line() == line)
            {
                update_end_circle(end_circles[i], line);
                return;
            }
        }  
    }
}