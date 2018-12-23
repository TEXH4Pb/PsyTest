#include "testform.h"
#include "ui_testform.h"

TestForm::TestForm(PsyTest::Test* test, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);
    this->test = test;
    ui->titleLabel->setText(test->title.c_str());
    ui->descriptionBrowser->setText(test->description.c_str());
    currentQuestion = 0;
}

TestForm::~TestForm()
{
    delete ui;
}

//Старт прохождения теста
void TestForm::on_startButton_clicked()
{
    if(test->questions.size() < 2)
        ui->nextButton->setEnabled(false);
    //Переход на вкладку с вопросами
    ui->stackedWidget->setCurrentIndex(1);
    ui->questionBrowser->setText(test->questions.front()->text.c_str());
    ui->scrollArea->setWidget(new AnswersForm(test->questions.front(), this));
}

//Переход к предыдущему вопросу
void TestForm::on_prevButton_clicked()
{
    --currentQuestion;
    ui->questionBrowser->setText(test->questions[currentQuestion]->text.c_str());
    delete ui->scrollArea->widget();
    ui->scrollArea->setWidget(new AnswersForm(test->questions[currentQuestion], this));

    //Обновление состояния кнопок переключения вопросов
    if(currentQuestion < 1)
        ui->prevButton->setEnabled(false);
    ui->nextButton->setEnabled(true);
}

//Переход к следующему вопросу
void TestForm::on_nextButton_clicked()
{
    ++currentQuestion;
    ui->questionBrowser->setText(test->questions[currentQuestion]->text.c_str());
    delete ui->scrollArea->widget();
    ui->scrollArea->setWidget(new AnswersForm(test->questions[currentQuestion], this));

    if(currentQuestion == (test->questions.size() - 1))
        ui->nextButton->setEnabled(false);
    ui->prevButton->setEnabled(true);
}

//Переход к результатам
void TestForm::on_getResultButton_clicked()
{
    qobject_cast<AnswersForm*>(ui->scrollArea->widget())->updateAnswer();
    int r, tmp;
    try
    {
        r = test->get_result();
    }
    catch(std::logic_error e)
    {
        QMessageBox::warning(this, "", QString("Не выбран ответа для вопроса ").append(e.what()));
        return;
    }
    if(r == -1)
        QMessageBox::warning(this, "Ошибка", "Не удалось найти результат для ваших ответов. Обратитесь к автору теста за помощью.");
    else
    {
        ui->resultLabel->setText(test->results[r].title.c_str());
        ui->resultBrowser->setText(test->results[r].text.c_str());
        ui->stackedWidget->setCurrentIndex(2);

        //Обновление статистических данных
        tmp = test->passedTimes_get();
        test->passedTimes_set(tmp + 1);
        tmp = test->results[r].occurrence_get();
        test->results[r].occurrence_set(tmp + 1);
        QCoreApplication::sendEvent(this->parent(), new QEvent(QEvent::User));
    }
}

//Сохранение результатов в текстовый файл
void TestForm::on_resultSaveButton_clicked()
{
    QString tmp = QFileDialog::getSaveFileName(this, "Сохранение результатов", "", "Текстовый файл (*.txt)");
    if(!tmp.isEmpty())
        test->results[test->get_result()].to_text(tmp.toStdString());
}
