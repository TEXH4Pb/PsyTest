#include "editform.h"
#include "ui_editform.h"

EditForm::EditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditForm)
{
    ui->setupUi(this);
    test = new PsyTest::Test();

    series = new QPieSeries();
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Общее количество прохождений: ");
    chart->setTheme(QChart::ChartThemeBlueNcs);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    chartView->setBackgroundBrush(QBrush(QColor(255,255,255)));
    chartView->setParent(ui->statsTab);
    ui->ChartVLayout->addWidget(chartView);

    currentQuestion = -1;
    currentResult = -1;
}

EditForm::~EditForm()
{
    delete ui;
}

//Сохранение теста
bool EditForm::saveTest(QString filename)
{
    if(currentQuestion > -1)
    {
        test->questions[currentQuestion] = takeQuestion();
        updateQuestion();
    }
    if(currentResult > -1)
    {
        test->results[currentResult] = takeResult();
        updateResult();
    }
    try
    {
    test->save(filename.toStdString());
    }
    catch (std::invalid_argument e)
    {
    QMessageBox::critical(this, "Не удалось сохранить файл", QString("Неверно выбран путь или запись невозможна. (%0)").arg(e.what()));
    return false;
    }
    return true;
}

bool EditForm::loadTest(QString filename)
{
    try
    {
        test->load(filename.toStdString());
    }
    catch (std::invalid_argument e)
    {
    QMessageBox::critical(this, "Не удалось открыть файл", QString("Неверно выбран путь или чтение невозможно. (%0)").arg(e.what()));
    return false;
    }
    QString tmp;

    ui->titleEdit->setText(test->title.c_str());
    ui->plainTextEdit->toPlainText().clear();
    ui->plainTextEdit->insertPlainText(test->description.c_str());

    ui->questionsList->clear();
    for(PsyTest::Question* q : test->questions)
    {
        if(q->text.empty())
            tmp = QString("Вопрос ").append(QString::number(ui->questionsList->count() + 1));
        else
            tmp = q->text.c_str();
        ui->questionsList->addItem(tmp);
    }

    ui->resultsList->clear();
    for(PsyTest::Result r : test->results)
    {
        if(r.title.empty())
            tmp = QString("Результат ").append(QString::number(ui->resultsList->count() + 1));
        else
            tmp = r.title.c_str();
        ui->resultsList->addItem(tmp);
    }
    return true;
}

//Сброс статистики
void EditForm::on_statsResetButton_clicked()
{
    if(QMessageBox::question(this, "Сброс статистики", "Вы уверены, что хотите сбросить статистику?") == QMessageBox::Yes)
    {
        test->passedTimes_set(0);
        for(PsyTest::Result r : test->results)
            r.occurrence_set(0);
        QMessageBox::information(this, "Сброс статистики", "Статистика сброшена!");
    }
}

//Редактирование названия теста
void EditForm::on_titleEdit_editingFinished()
{
    test->title = ui->titleEdit->text().toStdString();
}

//Редактирование описания текста
void EditForm::on_plainTextEdit_textChanged()
{
    test->description = ui->plainTextEdit->toPlainText().toStdString();
}


//#############//
//QUESTIONS TAB//
//#############//

//Добавление вопроса
void EditForm::on_addQuestionButton_clicked()
{
    test->questions.push_back(nullptr);
    ui->questionsList->addItem(QString("Вопрос ").append(QString::number(ui->questionsList->count()+1)));
}

//Добавление варианта ответа
void EditForm::on_addOptionButton_clicked()
{
    AnswerEdit* tmp = new AnswerEdit(ui->answersScrollBox);
    ui->scrollAreaWidgetContents->layout()->addWidget(tmp);
}

//Редактируемый вопрос сохраняется, когда пользователь выбирает другой вопрос
void EditForm::on_questionsList_itemSelectionChanged()
{
    if(currentQuestion == -1)
    {
        ui->addOptionButton->setEnabled(true);
        ui->questionText->setEnabled(true);
        ui->answersScrollBox->setEnabled(true);
        ui->multiOptionCheckBox->setEnabled(true);
        currentQuestion = ui->questionsList->currentRow();
        updateQuestion();
    }
    else
    {
        test->questions[currentQuestion] = takeQuestion();
        currentQuestion = ui->questionsList->currentRow();
        updateQuestion();
    }
}

//Создание вопроса из введённых данных и очистка списка вариантов ответов
PsyTest::Question* EditForm::takeQuestion()
{
    if(ui->multiOptionCheckBox->isChecked())
    {
        //Создаём и возвращаем MultiOption
        PsyTest::MultiOption* r = new PsyTest::MultiOption(ui->questionText->text().toStdString());
        ui->questionText->setText("");
        AnswerEdit* a;
        while(ui->scrollAreaWidgetContents->layout()->count())
        {
            a = qobject_cast<AnswerEdit*>(ui->scrollAreaWidgetContents->layout()->itemAt(0)->widget());
            r->add_answer(a->getAnswer());
            delete a;
        }
        //TODO: загрузка изображения
        return r;
    }
    else
    {
        //Создаём и возвращаем OneOption
        PsyTest::OneOption* r = new PsyTest::OneOption(ui->questionText->text().toStdString());
        ui->questionText->setText("");
        AnswerEdit* a;
        while(ui->scrollAreaWidgetContents->layout()->count())
        {
            a = qobject_cast<AnswerEdit*>(ui->scrollAreaWidgetContents->layout()->itemAt(0)->widget());
            r->add_answer(a->getAnswer());
            delete a;
        }
        //TODO: загрузка изображения
        return r;
    }
}

//Заполнение полей редактора данными выбранного вопроса
void EditForm::updateQuestion()
{
    PsyTest::Question* ptr = test->questions[currentQuestion];
    while(ui->scrollAreaWidgetContents->layout()->count())
    {
        delete ui->scrollAreaWidgetContents->layout()->itemAt(0)->widget();
    }
    if(!ptr)
    {
        ui->questionText->setText("");
        ui->multiOptionCheckBox->setChecked(false);
    }
    else
    {
        ui->questionText->setText(QString(ptr->text.c_str()));
        if(typeid(*ptr) == typeid(PsyTest::OneOption))
        {
            ui->multiOptionCheckBox->setChecked(false);
            AnswerEdit* tmp;
            for(PsyTest::answer a : dynamic_cast<PsyTest::OneOption*>(ptr)->answers)
            {
                tmp = new AnswerEdit(ui->answersScrollBox, a);
                ui->scrollAreaWidgetContents->layout()->addWidget(tmp);
            }

        }
        else
        {
            ui->multiOptionCheckBox->setChecked(true);
            AnswerEdit* tmp;
            for(std::pair<PsyTest::answer, bool> a : dynamic_cast<PsyTest::MultiOption*>(ptr)->answers)
            {
                tmp = new AnswerEdit(ui->answersScrollBox, a.first);
                ui->scrollAreaWidgetContents->layout()->addWidget(tmp);
            }
        }
    }
}

//Обновление названия вопроса в списке
void EditForm::on_questionText_editingFinished()
{
    if(ui->questionText->text().size())
        ui->questionsList->currentItem()->setText(ui->questionText->text());
    else
        ui->questionsList->currentItem()->setText(QString("Вопрос ").append(QString::number(currentQuestion + 1)));
}

//Удаление вопроса из списка
void EditForm::on_deleteQuestionButton_clicked()
{
    if(ui->questionsList->count())
    {
        test->questions.erase(test->questions.begin() + currentQuestion);
        updateQuestion();
        if(ui->questionsList->count() > 1)
        {
            ui->questionsList->takeItem(ui->questionsList->count()-1);
            for(int i = 0; i < ui->questionsList->count(); ++ i)
            {
                if(test->questions[i] && !test->questions[i]->text.empty())
                    ui->questionsList->item(i)->setText(test->questions[i]->text.c_str());
                else
                    ui->questionsList->item(i)->setText(QString("Вопрос ").append(QString::number(i + 1)));
            }
        }
        else if(ui->questionsList->count() == 1)
        {
            ui->addOptionButton->setEnabled(false);
            ui->questionText->clear();
            ui->questionText->setEnabled(false);
            ui->answersScrollBox->setEnabled(false);
            ui->multiOptionCheckBox->setChecked(false);
            ui->multiOptionCheckBox->setEnabled(false);
            ui->questionsList->clear();
            currentQuestion = -1;
            while(ui->scrollAreaWidgetContents->layout()->count())
                delete ui->scrollAreaWidgetContents->layout()->itemAt(0)->widget();
        }
    }
}

//Перемещение вопроса вверх по списку
void EditForm::on_moveUpButton_clicked()
{
    if(currentQuestion>0)
    {
        PsyTest::Question* tmp = takeQuestion();
        test->questions[currentQuestion] = test->questions[currentQuestion - 1];
        test->questions[currentQuestion - 1] = tmp;
        updateQuestion();
        if(!test->questions[currentQuestion] || test->questions[currentQuestion]->text.empty())
            ui->questionsList->currentItem()->setText(QString("Вопрос ").append(QString::number(currentQuestion + 1)));
        else
            ui->questionsList->currentItem()->setText(QString(test->questions[currentQuestion]->text.c_str()));
        ui->questionsList->setCurrentRow(currentQuestion - 1);
        if(!test->questions[currentQuestion] || test->questions[currentQuestion]->text.empty())
            ui->questionsList->currentItem()->setText(QString("Вопрос ").append(QString::number(currentQuestion + 1)));
        else
            ui->questionsList->currentItem()->setText(QString(test->questions[currentQuestion]->text.c_str()));
    }
}

//Перемещение вопроса вниз по списку
void EditForm::on_moveDownButton_clicked()
{
    if(currentQuestion < (ui->questionsList->count() - 1))
    {
        PsyTest::Question* tmp = takeQuestion();
        test->questions[currentQuestion] = test->questions[currentQuestion + 1];
        test->questions[currentQuestion + 1] = tmp;
        updateQuestion();
        if(!test->questions[currentQuestion] || test->questions[currentQuestion]->text.empty())
            ui->questionsList->currentItem()->setText(QString("Вопрос ").append(QString::number(currentQuestion + 1)));
        else
            ui->questionsList->currentItem()->setText(QString(test->questions[currentQuestion]->text.c_str()));
        ui->questionsList->setCurrentRow(currentQuestion + 1);
        if(!test->questions[currentQuestion] || test->questions[currentQuestion]->text.empty())
            ui->questionsList->currentItem()->setText(QString("Вопрос ").append(QString::number(currentQuestion + 1)));
        else
            ui->questionsList->currentItem()->setText(QString(test->questions[currentQuestion]->text.c_str()));
    }
}


//##########//
//RESULT TAB//
//##########//

//Добавление результата в список
void EditForm::on_addResultButton_clicked()
{
    test->results.push_back(PsyTest::Result());
    ui->resultsList->addItem(QString("Результат ").append(QString::number(ui->resultsList->count()+1)));
}

//Редактируемый результат сохраняется, когда пользователь выбирает другой результат
void EditForm::on_resultsList_itemSelectionChanged()
{
    if(currentResult == -1)
    {
        ui->resultTitleEdit->setEnabled(true);
        ui->resultDescEdit->setEnabled(true);
        ui->groupBox_2->setEnabled(true);
        ui->spinBox->setEnabled(true);
        ui->spinBox_2->setEnabled(true);
        currentResult = ui->resultsList->currentRow();
        updateResult();
    }
    else
    {
        test->results[currentResult] = takeResult();
        currentResult = ui->resultsList->currentRow();
        updateResult();
    }
}

//Создание результата из введённых данных
PsyTest::Result EditForm::takeResult()
{
    PsyTest::Result r("");
    r.title = ui->resultTitleEdit->text().toStdString();
    r.text = ui->resultDescEdit->toPlainText().toStdString();
    r.from = ui->spinBox->value();
    r.to = ui->spinBox_2->value();
    //TODO: сохранение изображения
    return r;
}

//Заполнение полей данными из выбранного результата
void EditForm::updateResult()
{
    ui->resultTitleEdit->setText(test->results[currentResult].title.c_str());
    ui->resultDescEdit->clear();
    ui->resultDescEdit->appendPlainText(test->results[currentResult].text.c_str());
    ui->spinBox->setValue(test->results[currentResult].from);
    ui->spinBox_2->setValue(test->results[currentResult].to);
    //TODO: изображение
}

//Удаление выбранного результата
void EditForm::on_deleteResultButton_clicked()
{
    if(ui->resultsList->count())
    {
        test->results.erase(test->results.begin() + currentResult);
        updateResult();
    }
    if(ui->resultsList->count() > 1)
    {
        ui->resultsList->takeItem(ui->resultsList->count()-1);
        for(int i = 0; i < ui->resultsList->count(); ++ i)
        {
            if(!test->results[i].title.empty())
                ui->resultsList->item(i)->setText(test->results[i].title.c_str());
            else
                ui->resultsList->item(i)->setText(QString("Результат ").append(QString::number(i + 1)));
        }
    }
    else if(ui->resultsList->count() == 1)
    {
        ui->resultTitleEdit->setEnabled(false);
        ui->resultDescEdit->setEnabled(false);
        ui->groupBox_2->setEnabled(false);
        ui->spinBox->setEnabled(false);
        ui->spinBox_2->setEnabled(false);
        ui->resultsList->clear();
        currentResult = -1;
    }
}

//Обновление названия результата в списке
void EditForm::on_resultTitleEdit_editingFinished()
{
    if(ui->resultTitleEdit->text().size())
        ui->resultsList->currentItem()->setText(ui->resultTitleEdit->text());
    else
        ui->resultsList->currentItem()->setText(QString("Результат ").append(QString::number(currentResult + 1)));
}

//Перемещение выбранного результата вверх по списку
void EditForm::on_moveUpButton_2_clicked()
{
    if(currentResult > 0)
    {
        PsyTest::Result tmp = takeResult();
        test->results[currentResult] = test->results[currentResult - 1];
        test->results[currentResult - 1] = tmp;
        updateResult();
        if(test->results[currentResult].text.empty())
            ui->resultsList->currentItem()->setText(QString("Результат ").append(QString::number(currentResult + 1)));
        else
            ui->resultsList->currentItem()->setText(QString(test->results[currentResult].title.c_str()));
        ui->resultsList->setCurrentRow(currentResult - 1);
        if(test->results[currentResult].text.empty())
            ui->resultsList->currentItem()->setText(QString("Результат ").append(QString::number(currentResult + 1)));
        else
            ui->resultsList->currentItem()->setText(QString(test->results[currentResult].title.c_str()));
    }
}

//Перемещение выбранного результата вниз по списку
void EditForm::on_moveDownButton_2_clicked()
{
    if(currentResult < (ui->resultsList->count() - 1))
    {
        PsyTest::Result tmp = takeResult();
        test->results[currentResult] = test->results[currentResult + 1];
        test->results[currentResult + 1] = tmp;
        updateResult();
        if(test->results[currentResult].text.empty())
            ui->resultsList->currentItem()->setText(QString("Результат ").append(QString::number(currentResult + 1)));
        else
            ui->resultsList->currentItem()->setText(QString(test->results[currentResult].title.c_str()));
        ui->resultsList->setCurrentRow(currentResult + 1);
        if(test->results[currentResult].text.empty())
            ui->resultsList->currentItem()->setText(QString("Результат ").append(QString::number(currentResult + 1)));
        else
            ui->resultsList->currentItem()->setText(QString(test->results[currentResult].title.c_str()));
    }
}
