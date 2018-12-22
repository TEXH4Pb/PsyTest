#include "answeredit.h"
#include "ui_answeredit.h"

AnswerEdit::AnswerEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswerEdit)
{
    ui->setupUi(this);
}

AnswerEdit::AnswerEdit(QWidget *parent, PsyTest::answer a):AnswerEdit(parent)
{
    ui->lineEdit->setText(a.text.c_str());
    ui->spinBox->setValue(a.points);
}

AnswerEdit::~AnswerEdit()
{
    delete ui;
}

PsyTest::answer AnswerEdit::getAnswer()
{
    PsyTest::answer r;
    r.text = ui->lineEdit->text().toStdString();
    r.points = ui->spinBox->value();
    return r;
}

void AnswerEdit::setAnswer(PsyTest::answer a)
{
    ui->lineEdit->setText(a.text.c_str());
    ui->spinBox->setValue(a.points);
}

void AnswerEdit::on_pushButton_clicked()
{
    this->close();
    this->deleteLater();
}
