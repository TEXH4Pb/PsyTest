#include "answersform.h"
#include "ui_answersform.h"
#include <QMessageBox>

AnswersForm::AnswersForm(PsyTest::Question* question, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswersForm)
{
    ui->setupUi(this);
    //Выбрасываем исключение, если указатель nullptr
    if(!question)
        throw std::invalid_argument("Null pointer question");
    this->question = question;
    //Определяем тип вопроса
    multiOption = (typeid(*question) == typeid(PsyTest::MultiOption));
    //В зависимости от типа вопроса заполняем форму либо checkbox'ами, либо radiobutton'ами
    if(multiOption)
    {
        for(std::pair<PsyTest::answer, bool> p : dynamic_cast<PsyTest::MultiOption*>(question)->answers)
        {
            buttons.append(new QCheckBox(this));
            buttons.last()->setText(p.first.text.c_str());
            buttons.last()->setChecked(p.second);
            ui->verticalLayout->addWidget(buttons.last());
        }
    }
    else
    {
        for(PsyTest::answer a : dynamic_cast<PsyTest::OneOption*>(question)->answers)
        {
            buttons.append(new QRadioButton(this));
            buttons.last()->setText(a.text.c_str());
            ui->verticalLayout->addWidget(buttons.last());
        }
        if(dynamic_cast<PsyTest::OneOption*>(question)->selection_get() != -1)
            buttons[dynamic_cast<PsyTest::OneOption*>(question)->selection_get()]->setChecked(true);
    }
}

AnswersForm::~AnswersForm()
{
    updateAnswer();

    delete ui;
}

void AnswersForm::updateAnswer()
{
    //Сохраняем выбор
    if(multiOption)
    {
        for(int i = 0; i < buttons.size(); ++i)
        {
            dynamic_cast<PsyTest::MultiOption*>(question)->answers[i].second = buttons[i]->isChecked();
        }
    }
    else
    {
        for(int i = 0; i < buttons.size(); ++i)
        {
            if(buttons[i]->isChecked())
                dynamic_cast<PsyTest::OneOption*>(question)->selection_set(i);
        }
    }
}
