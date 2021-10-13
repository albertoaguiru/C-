// Autor: Alberto Aguilar
// Fecha: Junio de 2021


#include "Flowchart.h"


namespace vista
{


    Flowchart::Flowchart(QWidget * parent)
        : QMainWindow(parent), box_controller(make_shared<BoxController>()),
        connection_diagram(nullptr)
    {
        ui.setupUi(this);
        ui.textGroup->setVisible(false);
        ui.createButton->setEnabled(false);

        // Creacion de la escena grafica donde se pinta todo

        graphic_scene = new QGraphicsScene(this);

        // Color del background

        QColor color(234, 182, 118);
        graphic_scene->setBackgroundBrush(color);

        ui.Vista->setScene(graphic_scene);

        connect(graphic_scene, SIGNAL(selectionChanged()), this, SLOT(selected_diagram()));
        connect(ui.actionUnir, SIGNAL(triggered()), this, SLOT(connect_diagram_action()));
        connect(ui.actionSeparar, SIGNAL(triggered()), this, SLOT(disconnect_diagram_action()));
        connect(ui.actionEliminar, SIGNAL(triggered()), this, SLOT(delete_diagram_action()));
        connect(ui.actionRombo, SIGNAL(triggered()), this, SLOT(create_rectangle_action()));
        connect(ui.actionCircular, SIGNAL(triggered()), this, SLOT(create_circle_action()));
        connect(ui.createButton, SIGNAL(clicked()), this, SLOT(create_diagram_button()));
        connect(ui.plainTextEdit, SIGNAL(textChanged()), this, SLOT(changed_text()));
        connect(graphic_scene, SIGNAL(mouseMoveEvent(QGraphicsSceneMouseEvent)), this, SLOT(mouseMoved(QGraphicsSceneMouseEvent)));
    }

    void Flowchart::selected_diagram()
    {
        auto selected_list = graphic_scene->selectedItems();

        if (selected_list.count() > 0)
        {
            if (connection_diagram != nullptr)
            {
                // Conexion del diagrama seleccionado con el elegido de antes

                Diagram *select_diagram = dynamic_cast<Diagram *>(selected_list[0]);

                connect_diagram(connection_diagram, select_diagram);

                // El raton vuelve a ser normal

                this->setCursor(Qt::ArrowCursor);
                connection_diagram = nullptr;

            }
        }
    }


    void Flowchart::connect_diagram_action()
    {
        auto selected_list = graphic_scene->selectedItems();
        if (selected_list.count() > 0)
        {
            connection_diagram = dynamic_cast<Diagram *>(selected_list[0]);

            // Cambio de raton para indicar que hay qeu seleccionar un diagrama para conectarlo

            this->setCursor(Qt::CrossCursor);
        }
    }

    void Flowchart::create_rectangle_action()
    {
        ui.textGroup->setVisible(true);
        ui.Vista->setVisible(false);
        type_creation = Type::rectangle;
    }

    void Flowchart::create_circle_action()
    {
        ui.textGroup->setVisible(true);
        ui.Vista->setVisible(false);
        type_creation = Type::circle;
    }

    void Flowchart::create_diagram_button()
    {
        QString name = ui.plainTextEdit->toPlainText();

        if (!name.isEmpty())
        {
            ui.textGroup->setVisible(false);
            ui.Vista->setVisible(true);

            // Creacion de nuevo diagrama

            if (type_creation == Type::rectangle)
            {
                create_diagram(name, Type::rectangle);
            }
            else
            {
                create_diagram(name, Type::circle);
            }

            ui.plainTextEdit->setPlainText("");
            ui.createButton->setEnabled(false);
        }
    }

    void Flowchart::changed_text()
    {
        QString name = ui.plainTextEdit->toPlainText();

        if (name.isEmpty())
        {
            ui.createButton->setEnabled(false);
            return;
        }

        string sname = name.toStdString();

        if (box_controller->box_exists(sname))
        {
            ui.createButton->setEnabled(false);
            return;
        }
        ui.createButton->setEnabled(true);
    }

    void Flowchart::disconnect_diagram_action()
    {
        auto selected_list = graphic_scene->selectedItems();
        if (selected_list.count() > 0)
        {
            Diagram* a = dynamic_cast<Diagram *>(selected_list[0]);
            QGraphicsLineItem *graphic_line = a->get_from_line();

            if (graphic_line != nullptr)
            {
                // Desconecta un diagrama de otro

                Diagram* c = a->get_from_diagram();
                c->delete_to_line(graphic_line);
                a->set_from_connection(nullptr, nullptr);
            }
        }
    }

    void Flowchart::delete_diagram_action()
    {
        auto selected_list = graphic_scene->selectedItems();
        if (selected_list.count() > 0)
        {

            // Borra todo el diagrama para que no salga por pantalla

            Diagram* a = dynamic_cast<Diagram *>(selected_list[0]);
            a->delete_all();

            QGraphicsItem* item = dynamic_cast<QGraphicsItem *>(selected_list[0]);
            graphic_scene->removeItem(item);
        }
    }

    Diagram *Flowchart::create_diagram(QString text, Type type)
    {
        // Crea un diagrama dependiendo del tipo elegido

        if (type == Type::rectangle)
        {
            RectangularDiagram* diagram = new RectangularDiagram(text, 0, 0, 100, 100, graphic_scene, box_controller);
            graphic_scene->addItem(diagram);
            return diagram;
        }
        else
        {
            CircularDiagram* diagram = new CircularDiagram(text, 0, 0, 150, 100, graphic_scene, box_controller);
            graphic_scene->addItem(diagram);
            return diagram;
        }
    }

    void Flowchart::connect_diagram(Diagram* a, Diagram* b)
    {
        // Si no estan unidos ya
        if (b->get_from_diagram() != a)
        {
            shared_ptr<Box> boxa = box_controller->get_box(a->get_name());
            shared_ptr<Box> boxb = box_controller->get_box(b->get_name());

            // Crea la nueva conexion

            box_controller->create_connection(boxa, boxb);

            QGraphicsLineItem* graphic_line = a->get_from_line();

            if (graphic_line != nullptr)
            {
                Diagram* c = a->get_from_diagram();
                c->delete_to_line(graphic_line);
            }

            // Coordenadas de la linea que une los diagramas

            float aX = boxa->get_center().x;
            float aY = boxa->get_center().y;
            float bX = boxb->get_center().x;
            float bY = boxb->get_center().y;

            QPointF point_a(aX, aY);
            QPointF point_b(bX, bY);

            QLineF line(point_a, point_b);

            // La linea que une a los dos diagramas

            QGraphicsLineItem* line_item = new QGraphicsLineItem(line);

            a->set_from_connection(b, line_item);
            b->add_to_line(line_item);

            graphic_scene->addItem(line_item);
        }
    }
}