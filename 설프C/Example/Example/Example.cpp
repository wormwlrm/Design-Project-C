#include "Example.h"

Example::Example(QWidget *parent)
	: QMainWindow(parent)
{
	initWidgets();
	initActions();
}

Example::~Example()
{

}

void Example :: initWidgets()
{
	_userInputLine = new QLineEdit;
	_calcSightPush = new QPushButton((kor("관광지")));
	_calcSatisfactionPush = new QPushButton(kor("만족도"));
	_resultLine = new QLineEdit;
	_resultRoute = new QLineEdit;
	_resultLine->setReadOnly(true);
	_resultRoute->setReadOnly(true);
	_ExitProgram = new QPushButton(kor("종료"));

	_formLayout = new QFormLayout;
	_formLayout->addRow(kor("시간 입력 : "), _userInputLine);
	_formLayout->addWidget(_calcSightPush);
	_formLayout->addWidget(_calcSatisfactionPush);
	_formLayout->addRow(kor("경로 : "), _resultRoute);
	_formLayout->addRow(kor("방문/만족 : "), _resultLine);
	_formLayout->addWidget(_ExitProgram);

	setCentralWidget(new QWidget);
	centralWidget()->setLayout(_formLayout);
}

void Example::initActions()
{
	connect(_calcSightPush, SIGNAL(clicked(bool)), this, SLOT(search_Sight()));
	connect(_calcSatisfactionPush, SIGNAL(clicked(bool)), this, SLOT(search_Satisfation()));
	connect(_ExitProgram, SIGNAL(clicked(bool)), this, SLOT(exit_Program()));
}

void Example::exit_Program()
{
	exit(100);
}

void Example::search_Sight()
{
	QString UserInput = _userInputLine->text();
	A.search_Sights(UserInput.toInt());

	string first = A.Result.first;
	string second = A.Result.second;

	char *cstr = new char[first.length() + 1];
	strcpy(cstr, first.c_str());
	_resultRoute->setText(kor(cstr));

	char *cstr2 = new char[second.length() + 1];
	strcpy(cstr2, second.c_str());
	_resultLine->setText(kor(cstr2));

	delete[] cstr;
	delete[] cstr2;
}

void Example::search_Satisfation()
{
	QString UserInput = _userInputLine->text();
	A.search_Satisfaction(UserInput.toInt());

	string first = A.Result.first;
	string second = A.Result.second;

	char *cstr = new char[first.length() + 1];
	strcpy(cstr, first.c_str());
	_resultRoute->setText(kor(cstr));

	char *cstr2 = new char[second.length() + 1];
	strcpy(cstr2, second.c_str());
	_resultLine->setText(kor(cstr2));

	delete[] cstr;
	delete[] cstr2;
}