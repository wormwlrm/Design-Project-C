#pragma once
#include "App.h"
//#include "ui_Example.h"
#include <QtCore>
#include <QtWidgets>
#include <QMainWindow>
#include <QtCore\qstring.h>
#include <QtCore/qstringbuilder.h>

class Example : public QMainWindow
{
	Q_OBJECT

public:
	Example(QWidget *parent = Q_NULLPTR);
	~Example();

private slots:
	void search_Sight();
	void search_Satisfation();
	void exit_Program();

private:
	QLineEdit *_userInputLine;
	QPushButton *_calcSightPush;
	QPushButton *_calcSatisfactionPush;
	QLineEdit *_resultLine;
	QLineEdit *_resultRoute;
	QPushButton *_ExitProgram;

	QFormLayout *_formLayout;

	void initWidgets();
	void initActions();
	QString kor(char* str)	
	{
		QString korStr = QString::fromLocal8Bit(str);
		return korStr;	
	}
	App A;
};
