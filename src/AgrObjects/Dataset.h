/*
 * Dataset.h
 *
 *  Created on: 06 ott 2016
 *      Author: lorenzo
 */

#ifndef AGROBJECTS_DATASET_H_
#define AGROBJECTS_DATASET_H_

#include <QVector>
#include <QString>
#include <QObject>
#include <QMap>
#include <QFile>
#include <QPair>
#include "../qcustomplot/qcustomplot.h"
#include "../AgrObjects/AgrSettings.h"

namespace dg {

struct SetAppearanceDetails;

class Dataset: public QObject {
Q_OBJECT

public:
	Dataset(SettingsMap *settings_map);
	virtual ~Dataset();

	QVector<double> x, y, z, dx, dy, dz;

	void set_type(QString type);
	void set_id(int n_id);
	void set_appearance(SetAppearanceDetails &new_appearance);

	SetAppearanceDetails appearance();
	void create_plottable(QCPAxisRect *axis_rect, QCPLegend *rect_legend);

	void append_header_line(QString line);
	void append_agr_line(QString line);
	void init_from_file(QFile &input, QString type);

	void write_headers(QTextStream &ts);
	void write_dataset(QTextStream &ts, int graph_id);

	bool empty() { return x.empty(); }
	int id() { return _id_dataset; }
	QCPAbstractPlottable *plottable() { return _plottable; }

	// getters and setters
	bool visible();
	void set_visible(bool is_visible);

	QString legend();
	void set_legend(QString new_legend);

signals:
	void changed(Dataset *);

private:
	QString _type;
	/// id of the dataset. It is unique on a per-graph basis.
	int _id_dataset;
	/// id of the dataset, as found in the header lines of the agr file. If the dataset was not created from an agr then its value is -1.
	int _id_header;
	/// associated QCustomPlot plottable
	QCPAbstractPlottable *_plottable;
	QPen _default_pen;
	/// legend of the associated QCPAxis
	QCPLegend *_legend;

	AgrSettings _settings;
	SettingsMap *_settings_map;

	// TODO: we should not keep a copy of these in each instance...
	QMap<QString, int> _type_to_n_column;
	QVector<QString> _implemented_types;

	void _set_plottable_data();
	void _check_type(QString type);
};

} /* namespace dg */

#endif /* AGROBJECTS_DATASET_H_ */
