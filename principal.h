#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QInputDialog>
#include <QColorDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void on_actionCerrar_triggered();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();

    void on_actionColor_triggered();

    void on_actionGrosor_triggered();

    void on_actionLibre_triggered();

    void on_actionLinea_triggered();

    void on_actionRectangulos_triggered();

    void on_actionCircunferencias_triggered();

private:
    Ui::Principal *ui;
    QImage *m_imagen; //Imagen sobre la cual se va a dibujar
    QPainter *m_painter; //El objeto painter
    QPoint m_ptInicial; //punto inicial para dibujar
    QPoint m_ptFinal;//punto final para dibujar
    int m_ancho;
    int m_opcion;
    bool m_toogle = true;
    QColor m_color = Qt::black;
};
#endif // PRINCIPAL_H
