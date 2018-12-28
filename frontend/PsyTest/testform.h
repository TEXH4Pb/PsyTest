#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include <QEvent>
#include <QMessageBox>
#include <QFileDialog>
#include "../../backend/PsyTest/PsyTest/Test.h"
#include "../../backend/PsyTest/PsyTest/Result.h"
#include "../../backend/PsyTest/PsyTest/Question.h"
#include "../../backend/PsyTest/PsyTest/PsyTest.h"
#include "../../backend/PsyTest/PsyTest/OneOption.h"
#include "../../backend/PsyTest/PsyTest/MultiOption.h"
#include "answersform.h"

namespace Ui {
class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(PsyTest::Test* test, QWidget *parent = nullptr);
    ~TestForm();
    PsyTest::Test* test;
    void loadTest(QString filename);

private slots:
    void on_startButton_clicked();

    void on_prevButton_clicked();

    void on_nextButton_clicked();

    void on_getResultButton_clicked();

    void on_resultSaveButton_clicked();

private:
    Ui::TestForm *ui;
    int currentQuestion;
};

#endif // TESTFORM_H
