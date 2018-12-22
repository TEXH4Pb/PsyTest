#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "infodialog.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->appState = Empty;
    this->filename = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    QMessageBox::StandardButton b;
    switch (this->appState) {
    case Edit:
        b = QMessageBox::question(this, "Сохранение файлов", "Хотите сохранить текущий тест?",
                                  QMessageBox::StandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel));
        if(b == QMessageBox::Yes)
        {
            if(this->filename.isEmpty())
                on_SaveAsAct_triggered();
            if(!this->filename.isEmpty())
                qobject_cast<EditForm*>(this->centralWidget())->saveTest(this->filename);
            else
                event->ignore();
        }
        else if (b == QMessageBox::Cancel)
            event->ignore();
        break;
    case Questioning:
        b = QMessageBox::question(this, "Прохождение теста", "Вы действительно хотите прервать прохождение теста? Прогресс прохождения не будет сохранён.",
                                  QMessageBox::StandardButtons(QMessageBox::Yes|QMessageBox::No));
        if(b != QMessageBox::Yes)
            event->ignore();
        break;
    default:
        break;
    }
}

void MainWindow::on_ExitAct_triggered()
{
    this->close();
}

void MainWindow::on_NewTestAct_triggered()
{
    QMessageBox::StandardButton b;
    switch (this->appState) {
    case Edit:
        b = QMessageBox::question(this, "Сохранение файлов", "Хотите сохранить текущий тест?",
                                  QMessageBox::StandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel));
        if(b == QMessageBox::Yes)
        {
            if(this->filename.isEmpty())
                on_SaveAsAct_triggered();
            if(!this->filename.isEmpty())
                qobject_cast<EditForm*>(this->centralWidget())->saveTest(this->filename);
            else
                return;
        }
        else if (b == QMessageBox::Cancel)
            return;
        break;
    case Questioning:
        b = QMessageBox::question(this, "Прохождение теста", "Вы действительно хотите прервать прохождение теста? Прогресс прохождения не будет сохранён.",
                                  QMessageBox::StandardButtons(QMessageBox::Yes|QMessageBox::No));
        if(b != QMessageBox::Yes)
            return;
        break;
    default:
        break;
    }
    this->filename.clear();
    this->setCentralWidget(new EditForm(this));
    this->appState = Edit;
    ui->SaveAct->setEnabled(true);
    ui->SaveAsAct->setEnabled(true);
}

void MainWindow::on_CreditsAct_triggered()
{
    InfoDialog* a = new InfoDialog(this);
    a->show();
}

void MainWindow::on_SaveAct_triggered()
{
    if(filename.isEmpty())
        on_SaveAsAct_triggered();
    else
        qobject_cast<EditForm*>(centralWidget())->saveTest(filename);
}

void MainWindow::on_SaveAsAct_triggered()
{
    filename = QFileDialog::getSaveFileName(this, "Сохранение теста", "", "Psychological Test (*.psy)");
    if(!filename.isEmpty())
        qobject_cast<EditForm*>(centralWidget())->saveTest(filename);
}

void MainWindow::on_EditTestAct_triggered()
{
    QMessageBox::StandardButton b;
    QString tmp;
    switch (this->appState) {
    case Edit:
        b = QMessageBox::question(this, "Сохранение файлов", "Хотите сохранить текущий тест?",
                                  QMessageBox::StandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel));
        if(b == QMessageBox::Yes)
        {
            if(this->filename.isEmpty())
                on_SaveAsAct_triggered();
            if(!this->filename.isEmpty())
                qobject_cast<EditForm*>(this->centralWidget())->saveTest(this->filename);
            else
                return;
        }
        else if (b == QMessageBox::Cancel)
            return;
        break;
    case Questioning:
        b = QMessageBox::question(this, "Прохождение теста", "Вы действительно хотите прервать прохождение теста? Прогресс прохождения не будет сохранён.",
                                  QMessageBox::StandardButtons(QMessageBox::Yes|QMessageBox::No));
        if(b != QMessageBox::Yes)
            return;
        break;
    default:
        break;
    }
    filename = QFileDialog::getOpenFileName(this, "Редактировать тест", "", "Psychological Test (*.psy)");
    if(filename.isEmpty())
        return;
    setCentralWidget(new EditForm(this));
    qobject_cast<EditForm*>(centralWidget())->loadTest(filename);
    appState = Edit;
    ui->SaveAct->setEnabled(true);
    ui->SaveAsAct->setEnabled(true);
}
