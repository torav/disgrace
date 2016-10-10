/*
 * MainWindow.cpp
 *
 *  Created on: 06 ott 2016
 *      Author: lorenzo
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Commands/Legend.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow), _toggle_drag_legend(false), _dragging_legend(false) {
	_ui->setupUi(this);

	_plot = _ui->custom_plot;

	_initialise_undo_stack();
	_initialise_custom_plot();

	QObject::connect(_ui->action_toggle_range_dragging, &QAction::toggled, this, &MainWindow::toggle_range_dragging);
	QObject::connect(_ui->action_toggle_range_zooming, &QAction::toggled, this, &MainWindow::toggle_range_zooming);
	QObject::connect(_ui->action_toggle_legend, &QAction::toggled, this, &MainWindow::toggle_legend);
	QObject::connect(_ui->action_toggle_drag_legend, &QAction::triggered, this, &MainWindow::toggle_drag_legend);
	QObject::connect(_ui->action_export_as_PDF, &QAction::triggered, this, &MainWindow::export_as_pdf);

	QObject::connect(_plot, &QCustomPlot::mouseMove, this, &MainWindow::mouse_move_signal);
	QObject::connect(_plot, &QCustomPlot::mousePress, this, &MainWindow::mouse_press_signal);
	QObject::connect(_plot, &QCustomPlot::mouseRelease, this, &MainWindow::mouse_release_signal);
	QObject::connect(_plot, &QCustomPlot::beforeReplot, this, &MainWindow::before_replot);
}

MainWindow::~MainWindow() {
	delete _ui;
}

void MainWindow::add_plot(dg::Dataset &new_set, bool rescale) {
	QCPGraph *new_graph = _plot->addGraph();
	new_graph->setData(new_set.x, new_set.y);
	new_graph->setName(new_set.name());
	new_graph->addToLegend();

	if(rescale) _plot->rescaleAxes(true);
}

void MainWindow::toggle_range_dragging(bool val) {
	qDebug() << "Toggling the range dragging to" << val;
	_plot->setInteraction(QCP::iRangeDrag, val);
}

void MainWindow::toggle_range_zooming(bool val) {
	qDebug() << "Toggling the range zooming to" << val;
	_plot->setInteraction(QCP::iRangeZoom, val);
}

void MainWindow::toggle_legend(bool val) {
	qDebug() << "Toggling the legend to" << val;
	_plot->legend->setVisible(val);
	_plot->replot();
}

void MainWindow::toggle_drag_legend(bool val) {
	qDebug() << "Toggling dragging the legend to" << val;
	_toggle_drag_legend = val;
}

void MainWindow::mouse_move_signal(QMouseEvent *event) {
	if(_dragging_legend) {
		QRectF rect = _plot->axisRect()->insetLayout()->insetRect(0);
		// since insetRect is in axisRect coordinates (0..1), we transform the mouse position:
		QPointF mousePoint((event->pos().x() - _plot->axisRect()->left()) / (double) _plot->axisRect()->width(), (event->pos().y() - _plot->axisRect()->top()) / (double) _plot->axisRect()->height());
		rect.moveTopLeft(mousePoint - _drag_legend_origin);
		_plot->axisRect()->insetLayout()->setInsetRect(0, rect);
		_plot->replot();
	}

}

void MainWindow::mouse_press_signal(QMouseEvent *event) {
	if(_toggle_drag_legend && _plot->legend->selectTest(event->pos(), false) > 0) {
		_dragging_legend = true;
		_old_legend_pos = _plot->axisRect()->insetLayout()->insetRect(0).topLeft();
		// since insetRect is in axisRect coordinates (0..1), we transform the mouse position:
		QPointF mousePoint((event->pos().x() - _plot->axisRect()->left()) / (double) _plot->axisRect()->width(), (event->pos().y() - _plot->axisRect()->top()) / (double) _plot->axisRect()->height());
		_drag_legend_origin = mousePoint - _old_legend_pos;
	}
}

void MainWindow::mouse_release_signal(QMouseEvent *event) {
	Q_UNUSED(event);

	if(_dragging_legend) {
		_dragging_legend = false;
		_undo_stack->push(new dg::MoveLegendCommand(_plot, _plot->axisRect()->insetLayout(), _old_legend_pos));
	}
}

void MainWindow::before_replot() {
	// this is to prevent the legend from stretching if the plot is stretched since we've set the inset placement to be ipFree, the width/height of the legend
	// is also defined in axisRect coordinates (0..1) and thus would stretch. This is due to change in a future release (still an issue in QCP 2.0 though).
	_plot->legend->setMaximumSize(_plot->legend->minimumSizeHint());
}

void MainWindow::export_as_pdf() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Export to..."), "", tr("PDF files(*.pdf)"));

	if(filename.size() > 0) _plot->savePdf(filename);
}

void MainWindow::undo() {

}

void MainWindow::redo() {

}

void MainWindow::_initialise_axis(QCPAxis *axis) {
	axis->grid()->setPen(Qt::NoPen);
	axis->grid()->setZeroLinePen(Qt::NoPen);

	QFont font("Times New Roman", 18);

	axis->setBasePen(QPen(Qt::black, 2));
	axis->setLabelFont(font);
	axis->setTickLabelFont(font);

	// ticks
	axis->setTickLengthIn(14);
	axis->setTickPen(QPen(Qt::black, 2));

	// subticks
	axis->setSubTickLengthIn(7);
}

void MainWindow::_initialise_undo_stack() {
	_undo_stack = new QUndoStack();

	_undo_view = new QUndoView(_undo_stack);
	_undo_view->setWindowTitle(tr("Command List"));
	_undo_view->show();
	_undo_view->setAttribute(Qt::WA_QuitOnClose, false);

	_ui->action_undo->setShortcuts(QKeySequence::Undo);
	QObject::connect(_ui->action_undo, &QAction::triggered, _undo_stack, &QUndoStack::undo);

	_ui->action_redo->setShortcuts(QKeySequence::Redo);
	QObject::connect(_ui->action_redo, &QAction::triggered, _undo_stack, &QUndoStack::redo);
}

void MainWindow::_initialise_custom_plot() {
	_plot->setAutoAddPlottableToLegend(true);
	// create a top and a right axes, set their visibility to true and then connects their ranges to the bottom and left axes, respectively
	_plot->axisRect()->setupFullAxesBox(true);
	foreach(QCPAxis *axis, _plot->axisRect()->axes()) {
		_initialise_axis(axis);
	}

	QFont legend_font("Timer New Roman", 14);
	QCPLegend *legend = _plot->legend;
	legend->setFont(legend_font);

	// set the placement of the legend (index 0 in the axis rect's inset layout) to not be border-aligned (default), but freely, so we can reposition it anywhere:
	_plot->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
}
