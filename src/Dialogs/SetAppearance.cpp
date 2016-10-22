#include "SetAppearance.h"

#include <QMessageBox>
#include <QPushButton>

#include "../AgrObjects/AgrFile.h"
#include "ui_SetAppearance.h"

namespace dg {

SetAppearance::SetAppearance(AgrFile *agr_file, QWidget *parent) :
		QDialog(parent), _ui(new Ui::SetAppearance), _agr_file(agr_file) {
	_ui->setupUi(this);
	_ui->list_curves->setModel(agr_file->graphs()[0]);

	_setup_widgets();

	_mapper = new QDataWidgetMapper(this);
	_mapper->setModel(agr_file->graphs()[0]);
	_mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	_mapper->addMapping(_ui->line_legend, AgrGraph::Legend);
	// TODO: we should set up a model for the combobox to make it possible to use currentData rather than currentText
	_mapper->addMapping(_ui->cb_line_style, AgrGraph::LineStyle, "currentText");
	_mapper->addMapping(_ui->sb_line_width, AgrGraph::LineWidth);
	_mapper->addMapping(_ui->line_colour, AgrGraph::LineColour);
	_mapper->addMapping(_ui->cb_symbol_type, AgrGraph::SymbolType);
	_mapper->addMapping(_ui->sb_symbol_size, AgrGraph::SymbolSize);
	_mapper->addMapping(_ui->symbol_colour, AgrGraph::SymbolColour);

	// connects the list widget to the mapper, so that the latter is notified when the user changes the selected set
	QObject::connect(_ui->list_curves->selectionModel(), &QItemSelectionModel::currentRowChanged, _mapper, &QDataWidgetMapper::setCurrentModelIndex);
	QObject::connect(agr_file->graphs()[0], &AgrGraph::dataChanged, _mapper, &QDataWidgetMapper::setCurrentModelIndex);

	// set up the colour pickers
	QAction *line_colour_action = _ui->line_colour->addAction(QIcon(), QLineEdit::TrailingPosition);
	line_colour_action->setData(QVariant("pick_colour_action"));
	connect(line_colour_action, &QAction::triggered, this, &SetAppearance::pick_colour);
	connect(_ui->line_colour, &QLineEdit::textChanged, this, &SetAppearance::change_btn_colour_background);

	QAction *symbol_colour_action = _ui->symbol_colour->addAction(QIcon(), QLineEdit::TrailingPosition);
	symbol_colour_action->setData(QVariant("pick_colour_action"));
	connect(symbol_colour_action, &QAction::triggered, this, &SetAppearance::pick_colour);
	connect(_ui->symbol_colour, &QLineEdit::textChanged, this, &SetAppearance::change_btn_colour_background);

	QObject::connect(_ui->button_box->button(QDialogButtonBox::Apply), &QPushButton::clicked, _mapper, &QDataWidgetMapper::submit);
}

SetAppearance::~SetAppearance() {
	delete _mapper;
	delete _ui;
}

void SetAppearance::show() {
	QWidget::show();
	QModelIndex idx = _ui->list_curves->currentIndex();
	if(idx.row() == -1) {
		QModelIndex first_idx = _agr_file->graphs()[0]->index(0, 0);
		_ui->list_curves->setCurrentIndex(first_idx);
	}
}

void SetAppearance::pick_colour() {
	QAction *action = static_cast<QAction *>(QObject::sender());
	QList<QWidget *> widgets = action->associatedWidgets();

	// we need to loop over the associated widgets to find the associated QLineEdit
	foreach(QWidget *w, widgets) {
		QLineEdit *le = dynamic_cast<QLineEdit *>(w);
		if(le) {
			qDebug() << w;
			const QColor colour = QColorDialog::getColor(QColor(le->text()), this, tr("Pick a colour"));
			if(colour.isValid()) le->setText(colour.name());
		}
	}
}

void SetAppearance::change_btn_colour_background(const QString &colour_name) {
	QLineEdit *le = dynamic_cast<QLineEdit *>(QObject::sender());
	if(!le) {
		qCritical() << "QObject::sender() cannot be cast to a QLineEdit *";
		exit(1);
	}

	QString ss_text = QString("background-color: %1").arg(colour_name);
	foreach(QAction *action, le->actions()) {
		if(action->data().toString() == QString("pick_colour_action")) {
			QPixmap pixmap(100, 100);
			pixmap.fill(QColor(colour_name));
			action->setIcon(QIcon(pixmap));
		}
	}
}

void SetAppearance::_setup_widgets() {
	// graph combo box
	// TODO: we want to use a model for this


	// line style
	_ui->cb_line_style->setIconSize(QSize(80, 14));
	for(int pen_style = Qt::NoPen; pen_style < Qt::CustomDashLine; pen_style++) {
		QPixmap pix(80, 14);
		// make the option's background the same colour of the widget's background
		pix.fill(palette().color(QPalette::Background));

		QBrush brush(Qt::black);
		QPen pen(brush, 2.5, (Qt::PenStyle) pen_style);

		QPainter painter(&pix);
		painter.setPen(pen);
		painter.drawLine(2, 7, 78, 7);

		_ui->cb_line_style->addItem(QIcon(pix), QString::number(pen_style), pen_style);
	}

	// symbol type
	_ui->cb_symbol_type->setIconSize(QSize(80, 14));
	for(int symbol_type = QCPScatterStyle::ssNone; symbol_type < QCPScatterStyle::ssPeace; symbol_type++) {
		QCPScatterStyle ss((QCPScatterStyle::ScatterShape) symbol_type);
		ss.setSize(10);
		QPixmap pix(15, 15);
		pix.fill(palette().color(QPalette::Background));

		QCPPainter qp(&pix);
		ss.applyTo(&qp, QPen(Qt::black));
		ss.drawShape(&qp, 7, 7);
		QIcon icon = QIcon(pix);

		_ui->cb_symbol_type->addItem(icon, QString::number(symbol_type), symbol_type);
	}
}

} /* namespace dg */
