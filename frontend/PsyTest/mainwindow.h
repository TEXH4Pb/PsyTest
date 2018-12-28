#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "editform.h"
#include "testform.h"
#include "infodialog.h"

enum FormStates
{
    Empty,
    Edit,
    Questioning,
    ResultView,
    StatsView
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    FormStates appState;
    QString filename;
private slots:
    void on_ExitAct_triggered();

    void on_NewTestAct_triggered();

    void on_CreditsAct_triggered();

    void on_SaveAct_triggered();

    void on_SaveAsAct_triggered();

    void on_EditTestAct_triggered();

    void on_LaunchTestAct_triggered();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event);
    bool event(QEvent *event);
};

#endif // MAINWINDOW_H
