#include "plot.h"

extern Solver* solver;

Plot::Plot( QWidget *parent ):
    QwtPlot( parent )
{
    setAutoFillBackground( true );
    setPalette( QPalette( QColor( 255, 255, 255 ) ) );
    updateGradient();

    //setTitle( "A Simple QwtPlot Demonstration" );
    insertLegend( new QwtLegend(), QwtPlot::RightLegend );

    // axes
    QFont font("Verdana", 8);

    QwtPlot::setAxisFont(xBottom, font);
    QwtPlot::setAxisFont(yLeft, font);
    
    QwtPlot::setAxisAutoScale( xBottom);

    QwtPlot::setAxisAutoScale( yLeft );
    QwtPlot::setAxisAutoScale( yLeft );

QwtText title("time, sec");
title.setFont(QFont("Helvetica", 10));
setAxisTitle(QwtPlot::xBottom, title);

this->axisScaleDraw(QwtPlot::xBottom)->setMinimumExtent (20);
this->axisScaleDraw(QwtPlot::yLeft)->setMinimumExtent (50);
    // canvas
    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setLineWidth( 1 );
    canvas->setFrameStyle( QFrame::Box | QFrame::Plain );
    canvas->setBorderRadius( 0 );

    QPalette canvasPalette( Qt::white );
    canvasPalette.setColor( QPalette::Foreground, QColor( 230, 230, 230 ) );
    canvas->setPalette( canvasPalette );

    setCanvas( canvas );

    // panning with the left mouse button
    ( void ) new QwtPlotPanner( canvas );

    // zoom in/out with the wheel
    ( void ) new QwtPlotMagnifier( canvas );

    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableXMin(true);
    grid->enableYMin(true);
    grid->setMajorPen(QPen(QColor( 180, 180, 180 ), 0, Qt::SolidLine));
    grid->setMinorPen(QPen(QColor( 230, 230, 230 ), 0 , Qt::SolidLine));
    grid->attach(this);
}

void Plot::populate()
{
QColor QtColours[]= {QColor("red"), QColor("darkCyan"), QColor("cyan"), QColor("magenta"),
                      QColor("darkRed"), QColor("darkMagenta"),
                      QColor("green"), QColor("darkGreen"), QColor("yellow"),
                      QColor("blue")};
int start=0;
int Index = 0;
QColor Color;


    int n = solver->get_n();
    int m = solver->get_m();
    QwtPlotCurve *curve;

    QwtPlotDict::detachItems(QwtPlotItem::Rtti_PlotCurve, true);
    for(int i = 0; i < solver->trace.size(); ++i)
    {
        Color = QtColours[start];
        start++;
        if(start == sizeof(QtColours))
        {
            start = 0;
        }
        QString name;
        if(solver->dims[i] != "")
            name = solver->dims[i];
        else
            name = solver->names[solver->trace[i]-1];
        curve = new QwtPlotCurve( name );
        curve->setRenderHint( QwtPlotItem::RenderAntialiased );
        curve->setLegendAttribute( QwtPlotCurve::LegendShowLine, true );
        curve->setPen( Color );
        curve->attach( this );
        curve->setSamples( solver->paxData[0], solver->paxData[i+1]);
    }
    replot ();
}

void Plot::updateGradient()
{
    QPalette pal = palette();
    //pal.setBrush( Qt::white );
    setPalette( pal );
}

void Plot::resizeEvent( QResizeEvent *event )
{
    QwtPlot::resizeEvent( event );

    // Qt 4.7.1: QGradient::StretchToDeviceMode is buggy on X11
    updateGradient();
}
