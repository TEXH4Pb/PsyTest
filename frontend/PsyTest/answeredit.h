#ifndef ANSWEREDIT_H
#define ANSWEREDIT_H

#include <QWidget>
#include "../../backend/PsyTest/PsyTest/PsyTest.h"

namespace Ui {
class AnswerEdit;
}

class AnswerEdit : public QWidget
{
    Q_OBJECT

public:
    explicit AnswerEdit(QWidget* parent = nullptr);
    explicit AnswerEdit(QWidget* parent, PsyTest::answer);
    ~AnswerEdit();
    PsyTest::answer getAnswer();
    void setAnswer(PsyTest::answer a);

private slots:
    void on_pushButton_clicked();

private:
    Ui::AnswerEdit *ui;
};

#endif // ANSWEREDIT_H
