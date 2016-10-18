/*
 * DataManager.cpp
 *
 *  Created on: 12 Oct 2016
 *      Author: rovigattil
 */

#include "DataManager.h"

namespace dg {

DataManager::DataManager(QCustomPlot *plot, QObject *parent):
		QAbstractTableModel(parent),
		_plot(plot) {
	_default_pen.setWidth(2);

	_default_colors.push_back(Qt::black);
	_default_colors.push_back(Qt::red);
	_default_colors.push_back(Qt::green);
	_default_colors.push_back(Qt::blue);
	_default_colors.push_back(QColor("orange"));
	_default_colors.push_back(QColor("brown"));
	_default_colors.push_back(QColor("magenta"));

	_curr_color = _default_colors.begin();
	_new_appearance.dataset = NULL;
}

DataManager::~DataManager() {
	QMap<Dataset *, QCPAbstractPlottable *>::iterator it = _datasets.begin();
	while(it != _datasets.end()) {
		delete it.key();
		++it;
	}
}

Dataset *DataManager::_parse_next_dataset(QFile &input) {
	Dataset *new_ds = new Dataset();

	int n_columns = -1;
	int n_lines = 0;
	while(!input.atEnd()) {
		QString line = QString(input.readLine()).trimmed();
		if(line[0] != '#' && line.size() > 0) {
			// the regexp makes it possible to split the line in the presence of *any* whitespace
			QStringList spl = line.split(QRegExp("\\s"));
			if(n_columns == -1) n_columns = spl.size();
			bool conv_ok = true;

			switch(n_columns) {
			case 1: {
				new_ds->x.push_back(n_lines);
				double val = spl[0].toDouble(&conv_ok);
				new_ds->y.push_back(val);
				break;
			}
			case 2:
			default: {
				double val = spl[0].toDouble(&conv_ok);
				new_ds->x.push_back(val);
				val = spl[1].toDouble(&conv_ok);
				new_ds->y.push_back(val);
			}
			}

			n_lines++;
		}
		else if(!new_ds->empty()) return new_ds;
	}

	return new_ds;
}

void DataManager::add_datasets_from_file(QString filename, bool rescale_x, bool rescale_y) {
	QFile input(filename);
	if(!input.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qCritical() << "File" << filename << "is not readable";
		return;
	}

	while(!input.atEnd()) {
		Dataset *curr_dataset = _parse_next_dataset(input);
		curr_dataset->set_name(filename);

		QCPCurve *new_graph = new QCPCurve(_plot->xAxis, _plot->yAxis);
		new_graph->setPen(_next_pen());
		new_graph->setData(curr_dataset->x, curr_dataset->y);
		new_graph->setName(curr_dataset->name());
		new_graph->addToLegend();

		QObject::connect(curr_dataset, &Dataset::data_changed, this, &DataManager::update_graph_data);
		_datasets[curr_dataset] = new_graph;
		_sorted_datasets.push_back(curr_dataset);
	}

	if(rescale_x) {
		_plot->xAxis->rescale();
		_plot->xAxis2->rescale();
	}
	if(rescale_y) {
		_plot->yAxis->rescale();
		_plot->yAxis2->rescale();
	}
	_plot->replot();
}

void DataManager::update_graph_data(Dataset *ds) {
	if(_datasets.contains(ds)) {
		QCPCurve *associated_graph = static_cast<QCPCurve *>(_datasets.value(ds));
		if(!associated_graph) {
			qCritical() << "The QCPAbstractPlottable pointer associated to a dataset does not point to a QCPCurve object";
			return;
		}

		associated_graph->setData(ds->x, ds->y);
		_plot->replot();
	}
}

int DataManager::rowCount(const QModelIndex& parent) const {
	return _datasets.size();
}

int DataManager::columnCount(const QModelIndex& parent) const {
	return 5;
}

Qt::ItemFlags DataManager::flags(const QModelIndex &index) const {
	if (!index.isValid()) return Qt::ItemIsEnabled;

	return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QVariant DataManager::data(const QModelIndex& index, int role) const {
	if(!index.isValid()) return QVariant();
	if(index.row() >= _datasets.size() || index.row() < 0) return QVariant();

	int n_set = index.row();
	QVariant res;
	QCPCurve *graph = static_cast<QCPCurve *>(_datasets[_sorted_datasets[n_set]]);

	if(role == Qt::DisplayRole || role == Qt::EditRole) {
		switch(index.column()) {
		case Name:
			res = tr("Set %1 [%2]").arg(n_set).arg(graph->dataCount());
			break;
		case Legend:
			res = graph->name();
			break;
		case LineStyle:
			res = QString::number(graph->pen().style());
			break;
		case LineWidth:
			res = graph->pen().width();
			break;
		case LineColour:
			res = graph->pen().color().name();
			break;
		default:
			qCritical() << "The DataManager model has only" << columnCount() <<  "columns";
		}
	}

	return res;
}

bool DataManager::setData(const QModelIndex &index, const QVariant &value, int role) {
	if(index.isValid() && role == Qt::EditRole) {
		if(index.row() >= _datasets.size() || index.row() < 0) return false;
		int n_set = index.row();
		Dataset *dataset = _sorted_datasets[n_set];
		QCPCurve *graph = static_cast<QCPCurve *>(_datasets[dataset]);

		if(dataset != _new_appearance.dataset) _old_appearance = _new_appearance = _current_appearance(dataset);

		switch(index.column()) {
		case Name:
			break;
		case Legend:
			_new_appearance.legend = value.toString();
			break;
		case LineStyle:
			// we need to explicitly set the old appearance's pen properties because of QPen implicit sharing facilities
			_old_appearance.pen.setStyle(graph->pen().style());
			_new_appearance.pen.setStyle((Qt::PenStyle) value.toString().toInt());
			break;
		case LineWidth:
			_old_appearance.pen.setWidth(graph->pen().width());
			_new_appearance.pen.setWidth(value.toInt());
			break;
		case LineColour:
			_old_appearance.pen.setColor(graph->pen().color());
			_new_appearance.pen.setColor(QColor(value.toString()));
			break;
		default:
			qCritical() << "The DataManager model has only" << columnCount() <<  "columns";
		}

		return true;
	}

	return false;
}

void DataManager::emit_dataChanged(Dataset *dataset) {
	int n_set = _sorted_datasets.indexOf(dataset);
	if(n_set == -1) qCritical() << "The dataset involved in the change cannot be found in the list of datasets";
	else {
		QModelIndex index = createIndex(n_set, 0);
		emit dataChanged(index, index);
	}
}

bool DataManager::submit() {
	SetAppearanceCommand *nc = new SetAppearanceCommand(this, _old_appearance, _new_appearance);
	emit new_command(nc);

	return true;
}

SetAppearanceDetails DataManager::_current_appearance(Dataset *dataset) {
	QCPCurve *graph = static_cast<QCPCurve *>(_datasets[dataset]);

	SetAppearanceDetails res;
	res.dataset = dataset;
	res.legend = graph->name();
	res.pen = graph->pen();

	return res;
}

QPen DataManager::_next_pen() {
	QPen new_pen(_default_pen);
	new_pen.setColor(*_curr_color);
	_curr_color++;
	if(_curr_color == _default_colors.end()) _curr_color = _default_colors.begin();

	return new_pen;
}

} /* namespace dg */
