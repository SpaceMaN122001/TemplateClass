#include "TemplateClass.h"

TemplateClass::TemplateClass(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	setWindowIcon(QIcon(":/TemplateClass/res/mainico.png"));
	setCustomButtonStyle(ui.okToolButton, ":/TemplateClass/res/ok.png", "Apply", 21 ,21);
	setCustomButtonStyle(ui.clearToolButton, ":/TemplateClass/res/clear.png", "Clear", 21 ,21);
	setCustomButtonStyle(ui.headerCodeCopyToolButton, ":/TemplateClass/res/copy.png", "Copy header code", 16 ,16);
	setCustomButtonStyle(ui.sourcesCodeCopyToolButton, ":/TemplateClass/res/copy.png", "Copt sources code", 16 ,16);
	ui.headerImageLabel->hide();
	ui.soucesImageLabel->hide();

	ui.headerCodeTextEdit->setText("");

	QString s1 = "class name";

	connect(ui.classTypeLabelComboBox, SIGNAL(activated(QString)), this, SLOT(selectClassType()));
	connect(ui.okToolButton, SIGNAL(clicked()), this, SLOT(generateCode()));
	connect(ui.clearToolButton, SIGNAL(clicked()), this, SLOT(clearCode()));
	connect(ui.headerCodeCopyToolButton, SIGNAL(clicked()), this, SLOT(copyHeaderCode()));
	connect(ui.sourcesCodeCopyToolButton, SIGNAL(clicked()), this, SLOT(copySourcesCode()));

	clipboard = QApplication::clipboard();
}

void TemplateClass::selectClassType()
{
	if (ui.classTypeLabelComboBox->currentText() != "Class") {

		ui.InheritanceFromLabel->hide();
		ui.InheritanceFromLineEdit->hide();
		ui.InheritanceTypeLabel->hide();
		ui.InheritanceTypeComboBox->hide();

	} 
	
	if (ui.classTypeLabelComboBox->currentText() == "Qt Widget" || ui.classTypeLabelComboBox->currentText() == "Qt Main window") {

		ui.InheritanceFromLabel->setText("Form name");
		ui.InheritanceFromLabel->show();
		ui.InheritanceFromLineEdit->show();

	} else {

		ui.InheritanceFromLabel->setText("Inheritance from");
		ui.InheritanceFromLabel->show();
		ui.InheritanceFromLineEdit->show();
		ui.InheritanceTypeLabel->show();
		ui.InheritanceTypeComboBox->show();
	}
}

void TemplateClass::generateCode()
{
	QString headerCode = "";
	QString sourcesCode = "";
	QString include = "#include ";

	if (ui.classNameLineEdit->text().remove(" ") == nullptr) { QMessageBox::warning(this, "Atention!", "Please input class name"); return; }

	if (ui.classTypeLabelComboBox->currentText() == "Qt Widget") {

		if(ui.InheritanceFromLineEdit->text().remove(" ") == nullptr) { QMessageBox::warning(this, "Atention!", "Please input form name"); return; }

		headerCode = "#include <QtWidgets> \n";
		headerCode += include + "\"ui_name.h\" \n";
		headerCode.replace("name", ui.InheritanceFromLineEdit->text());
		headerCode += "\n class " + ui.classNameLineEdit->text() + " : public QWidget";
		headerCode += "\n { \n Q_OBJECT \n public: \n explicit " + ui.classNameLineEdit->text() + "(QWidget *parent = nullptr); \n" + "~" + ui.classNameLineEdit->text() + "(); \n";
		headerCode += "private: \n Ui:: " + ui.InheritanceFromLineEdit->text() + " ui; \n };";

		ui.headerCodeTextEdit->setText(headerCode);

		sourcesCode = include + "\"name.h\" \n \n name::name(QWidget *parent) : QWidget(parent) \n { \n ui.setupUi(this); \n } \n \n name::~name() \n { \n } \n";
		sourcesCode.replace("name", ui.classNameLineEdit->text());

		ui.sourcesCodeTextEdit->setText(sourcesCode);
	}

	if (ui.classTypeLabelComboBox->currentText() == "Qt Main window") {

		if (ui.InheritanceFromLineEdit->text().remove(" ") == nullptr) { QMessageBox::warning(this, "Atention!", "Please input form name"); return; }

		headerCode = "#include <QtWidgets> \n";
		headerCode += "#include <QMainWindow> \n";
		headerCode += include + "\"ui_name.h\" \n";
		headerCode.replace("name", ui.InheritanceFromLineEdit->text());
		headerCode += "\n class " + ui.classNameLineEdit->text() + " : public QMainWindow";
		headerCode += "\n { \n Q_OBJECT \n public: \n explicit " + ui.classNameLineEdit->text() + "(QWidget *parent = nullptr); \n" + "~" + ui.classNameLineEdit->text() + "(); \n";
		headerCode += "private: \n Ui:: " + ui.InheritanceFromLineEdit->text() + " ui; \n };";

		ui.headerCodeTextEdit->setText(headerCode);

		sourcesCode = include + "\"name.h\" \n \n name::name(QWidget *parent) : QMainWindow(parent) \n { \n ui.setupUi(this); \n } \n \n name::~name() \n { \n } \n";
		sourcesCode.replace("name", ui.classNameLineEdit->text());

		ui.sourcesCodeTextEdit->setText(sourcesCode);
	}

	if (ui.classTypeLabelComboBox->currentText() == "Class") {

		if (ui.InheritanceFromLineEdit->text().remove(" ") == nullptr) {

			headerCode = "class name \n { \n public: \n name(); \n ~name(); \n };";
			headerCode.replace("name", ui.classNameLineEdit->text());
			ui.headerCodeTextEdit->setText(headerCode);

			sourcesCode = include + "\"name.h\" \n \n name::name() \n { \n } \n \n name::~name() \n { \n } \n";
			sourcesCode.replace("name", ui.classNameLineEdit->text());

			ui.sourcesCodeTextEdit->setText(sourcesCode);
		}

		if (ui.InheritanceFromLineEdit->text() != nullptr) {

			headerCode = include + "\"name.h\" \n";
			headerCode.replace("name", ui.InheritanceFromLineEdit->text());
			headerCode += "\n class name : " + ui.InheritanceTypeComboBox->currentText() + " " + ui.InheritanceFromLineEdit->text();
			headerCode += " \n { \n public: \n name(); \n ~name(); \n };";

			headerCode.replace("name", ui.classNameLineEdit->text());
			ui.headerCodeTextEdit->setText(headerCode);

			sourcesCode = include + "\"name.h\" \n \n name::name() \n { \n } \n \n name::~name() \n { \n } \n";
			sourcesCode.replace("name", ui.classNameLineEdit->text());

			ui.sourcesCodeTextEdit->setText(sourcesCode);
		}

	}
}

void TemplateClass::clearCode()
{
	ui.headerCodeTextEdit->setText("");
	ui.sourcesCodeTextEdit->setText("");
	ui.classNameLineEdit->setText("");
	ui.InheritanceFromLineEdit->setText("");
}

void TemplateClass::copyHeaderCode()
{
	clipboard->setText(ui.headerCodeTextEdit->toPlainText());
}

void TemplateClass::copySourcesCode()
{
	clipboard->setText(ui.sourcesCodeTextEdit->toPlainText());
}

void TemplateClass::setCustomButtonStyle(QToolButton* button, QString imagePath, QString toolTip, int width, int heigth)
{
	QSize iconSize(width, heigth);
	QPixmap map(imagePath);
	QIcon icon(map);
	button->setIcon(icon);
	button->setIconSize(iconSize);
	button->setStyleSheet("QToolButton { background-color: transparent; }");
	button->setToolTip(toolTip);
}
