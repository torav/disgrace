/*
 * Legend.h
 *
 *  Created on: 10 Oct 2016
 *      Author: rovigattil
 */

#ifndef COMMANDS_LEGEND_H_
#define COMMANDS_LEGEND_H_

#include <QUndoStack>
#include "defs.h"
#include "../qcustomplot/qcustomplot.h"

namespace dg {

class MoveLegendCommand: public QUndoCommand {
public:
	MoveLegendCommand(QCustomPlot *plot, QCPLayoutInset *inset_layout, const QPointF &old_pos, QUndoCommand *parent = 0);
	virtual ~MoveLegendCommand();

	void undo() Q_DECL_OVERRIDE;
	void redo() Q_DECL_OVERRIDE;
	int id() const Q_DECL_OVERRIDE { return MOVE_LEGEND; }

private:
	QString _get_formatted_text(QPointF &old_pos, QPointF &new_pos);

	QCustomPlot *_plot;
	QCPLayoutInset *_inset_layout;
	QPointF _old_pos;
	QPointF _new_pos;
};

} /* namespace dg */

#endif /* COMMANDS_LEGEND_H_ */
