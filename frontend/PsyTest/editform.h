#ifndef EDITFORM_H
#define EDITFORM_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "../../backend/PsyTest/PsyTest/Test.h"
#include "../../backend/PsyTest/PsyTest/Result.h"
#include "../../backend/PsyTest/PsyTest/Question.h"
#include "../../backend/PsyTest/PsyTest/PsyTest.h"
#include "../../backend/PsyTest/PsyTest/OneOption.h"
#include "../../backend/PsyTest/PsyTest/MultiOption.h"
#include "answeredit.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class EditForm;
}

class EditForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditForm(QWidget *parent = nullptr);
    ~EditForm();
    bool saveTest(QString filename);
    bool loadTest(QString filename);

private slots:
    void on_statsResetButton_clicked();

    void on_addOptionButton_clicked();

    void on_titleEdit_editingFinished();

    void on_plainTextEdit_textChanged();

    void on_addQuestionButton_clicked();

    void on_questionsList_itemSelectionChanged();

    void on_questionText_editingFinished();

    void on_deleteQuestionButton_clicked();

    void on_moveUpButton_clicked();

    void on_moveDownButton_clicked();

    void on_addResultButton_clicked();

    void on_resultsList_itemSelectionChanged();

    void on_deleteResultButton_clicked();

    void on_resultTitleEdit_editingFinished();

    void on_moveUpButton_2_clicked();

    void on_moveDownButton_2_clicked();

    void on_imageLoadButton_clicked();

    void on_imageDeleteButton_clicked();

    void on_imageLoadButton_2_clicked();

    void on_imageDeleteButton_2_clicked();

    void on_imageLoadButton_3_clicked();

    void on_imageDeleteButton_3_clicked();

private:
    Ui::EditForm *ui;
    QPieSeries *series;
    QChart *chart;
    QChartView *chartView;
    QList<AnswerEdit*> answerOptions;

    PsyTest::Test* test;
    int currentQuestion;
    QString questionImage;
    int currentResult;
    QString resultImage;

    PsyTest::Question* takeQuestion();
    void updateQuestion();

    PsyTest::Result* takeResult();
    void updateResult();

    void updateStats();
};

#endif // EDITFORM_H
