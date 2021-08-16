#pragma once
/*#include "C:\qwt\src\qwt_legend.h"
#include <qlayout.h>
#include "C:\qwt\src\qwt_plot.h"
#include "C:\qwt\src\qwt_plot_grid.h"
#include "C:\qwt\src\qwt_plot_curve.h"
#include "C:\qwt\src\qwt_legend.h"
#include "C:\qwt\src\qwt_point_data.h"
#include "C:\qwt\src\qwt_plot_canvas.h"
#include "C:\qwt\src\qwt_scale_draw.h"
#include "C:\qwt\src\qwt_plot_panner.h"
#include "C:\qwt\src\qwt_plot_magnifier.h"
#include "C:\qwt\src\qwt_text.h"
#include "C:\qwt\src\qwt_symbol.h"
#include "C:\qwt\src\qwt_math.h"*/
#include "qwt_legend.h"
#include "qwt_plot.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_curve.h"
#include "qwt_legend.h"
#include "qwt_point_data.h"
#include "qwt_plot_canvas.h"
#include "qwt_scale_draw.h"
#include "qwt_plot_panner.h"
#include "qwt_plot_magnifier.h"
#include "qwt_text.h"
#include "qwt_symbol.h"
#include "qwt_math.h"
#include <qlayout.h>
#include <math.h>
#include <QFont>
#include <QDebug>

#include <solver.h>

class FunctionData: public QwtSyntheticPointData
{
public:
    FunctionData( double( *y )( double ) ):
        QwtSyntheticPointData( 100 ),
        d_y( y )
    {
    }

    virtual double y( double x ) const
    {
        return d_y( x );
    }

private:
    double( *d_y )( double );
};


class Plot : public QwtPlot
{
public:
    Plot( QWidget *parent = NULL );
	/*
	number of curves
	curves data with double arrays n curves + 1
	length of arrays
	*/
public slots:
	void populate();
protected:
    virtual void resizeEvent( QResizeEvent * );

private:
    
    void updateGradient();
};
