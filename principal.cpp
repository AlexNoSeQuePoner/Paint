#include "principal.h"
#include "ui_principal.h"

#include <QDebug>
#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    m_ancho = DEFAULT_ANCHO;
    m_opcion = 1;
    //instancia de la imagen
    m_imagen = new QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
    // Rellenar de blanco
    m_imagen->fill(Qt::white);
    //instanciar el objeto painter
    m_painter = new QPainter(m_imagen);


}

Principal::~Principal()
{
    delete ui;
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    QPen pincel;
    pincel.setColor(m_color);
    pincel.setWidth(m_ancho);
    if(m_opcion == 1){m_ptInicial = event->pos();
    }else if(m_opcion == 2){
        if(m_toogle){
            m_ptInicial = event->pos();
        }else{
            m_ptFinal = event->pos();
            m_painter->setPen(pincel);
            m_painter->drawLine(m_ptInicial, m_ptFinal);
            update();
        }
    }else if (m_opcion == 3){
        if(m_toogle){
            m_ptInicial = event->pos();
        }else{
            m_ptFinal = event->pos();
            int ancho = m_ptFinal.x() - m_ptInicial.x();
            int alto = m_ptFinal.y() - m_ptInicial.y();
            m_painter->setPen(pincel);
            m_painter->drawRect(m_ptInicial.x(), m_ptInicial.y(), ancho, alto);
            update();
        }
    }else if (m_opcion == 4){
        if(m_toogle){
            m_ptInicial = event->pos();
        }else{
            m_ptFinal = event->pos();
            int ancho = m_ptFinal.x() - m_ptInicial.x();
            int alto = m_ptFinal.y() - m_ptInicial.y();
            m_painter->setPen(pincel);
            m_painter->drawEllipse(m_ptInicial.x(), m_ptInicial.y(), ancho, alto);
            update();
        }
    }
    m_toogle = !m_toogle;
}

/**
 * @brief Principal::paintEvent Se ejecuta cada vez que se redibuja la interfaz
 * Eecuerda que esto es poniendo sin espacios "/ * *" y luego enter)
 * @param event
 */

void Principal::paintEvent(QPaintEvent *event)
{
    //Crear otro painter
    QPainter painter(this);
    // Dibujar la imagen, enviando el valor del puntero con *, porque sin este solo se obtiene el puntero
    painter.drawImage(0,0, *m_imagen);
    //Aceptar el evento
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
     if(m_opcion == 1){
        m_ptFinal = event->pos();
        QPen pincel;
        pincel.setWidth(m_ancho);
        pincel.setColor(m_color);
        m_painter->setPen(pincel);
        m_painter->drawLine(m_ptInicial, m_ptFinal);
    }
        //Actualizar la pantalla
    update();
    m_ptInicial = m_ptFinal;
}


void Principal::on_actionCerrar_triggered()
{
    close();
}

void Principal::on_actionNuevo_triggered()
{
    m_imagen->fill(Qt::white);
    update();
}

void Principal::on_actionGuardar_triggered()
{
    //Crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::home();
    QString pathArchivo = directorio.absolutePath() + "/Dibujo.png";
    //Abrir un cuadro de dialogo para seleccionar el nombre y ubicacion del archivo
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar Imagen",
                                                   pathArchivo,
                                                    "Imagen (*.png)");
    if (!fileName.isEmpty())
    {
        m_imagen->save(fileName);
    }
}

void Principal::on_actionColor_triggered()
{
    m_color = QColorDialog::getColor();
}

void Principal::on_actionGrosor_triggered()
{
    m_ancho = QInputDialog::getInt(this, "Ancho del pincel",
                                   "Ingrese el ancho del pincel,",
                                   m_ancho, 1, 100);
}

void Principal::on_actionLibre_triggered()
{
    m_opcion = 1;
}

void Principal::on_actionLinea_triggered()
{
    m_opcion = 2;
    m_toogle = true;
}

void Principal::on_actionRectangulos_triggered()
{
    m_opcion = 3;
    m_toogle = true;
}

void Principal::on_actionCircunferencias_triggered()
{
    m_opcion = 4;
    m_toogle = true;
}
