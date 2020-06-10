#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TemplateClass.h"
#include "QMessageBox"
#include <QClipboard>

class TemplateClass : public QMainWindow
{
    Q_OBJECT

public:
    TemplateClass(QWidget *parent = Q_NULLPTR);

private:
    Ui::TemplateClassClass ui;
	QClipboard* clipboard;

private slots:
	void selectClassType();
	void generateCode();
	void clearCode();
	void copyHeaderCode();
	void copySourcesCode();

private:
	void setCustomButtonStyle(QToolButton* button, QString imagePath, QString toolTip, int width = 38, int heigth = 38);
};
