#ifndef ANSWERSFORM_H
#define ANSWERSFORM_H

#include <QWidget>
#include <QList>
#include <QCheckBox>
#include <QRadioButton>
#include "../../backend/PsyTest/PsyTest/PsyTest.h"
#include "../../backend/PsyTest/PsyTest/MultiOption.h"
#include "../../backend/PsyTest/PsyTest/OneOption.h"

namespace Ui {
class AnswersForm;
}

class AnswersForm : public QWidget
{
    Q_OBJECT

public:
    explicit AnswersForm(PsyTest::Question* question, QWidget *parent = nullptr);
    ~AnswersForm();
    void updateAnswer();

private:
    Ui::AnswersForm *ui;
    bool multiOption;
    QList<QAbstractButton*> buttons;
    PsyTest::Question* question;
};

#endif // ANSWERSFORM_H
