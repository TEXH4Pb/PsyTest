QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PsyTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ../../backend/PsyTest/PsyTest/Test.cpp \
    ../../backend/PsyTest/PsyTest/Result.cpp \
    ../../backend/PsyTest/PsyTest/Question.cpp \
    ../../backend/PsyTest/PsyTest/OneOption.cpp \
    ../../backend/PsyTest/PsyTest/MultiOption.cpp \
    editform.cpp \
    answeredit.cpp \
    testform.cpp \
    answersmultiopt.cpp \
    infodialog.cpp

HEADERS += \
        mainwindow.h \
    ../../backend/PsyTest/PsyTest/Test.h \
    ../../backend/PsyTest/PsyTest/Result.h \
    ../../backend/PsyTest/PsyTest/Question.h \
    ../../backend/PsyTest/PsyTest/PsyTest.h \
    ../../backend/PsyTest/PsyTest/OneOption.h \
    ../../backend/PsyTest/PsyTest/MultiOption.h \
    editform.h \
    answeredit.h \
    testform.h \
    answersmultiopt.h \
    infodialog.h

FORMS += \
        mainwindow.ui \
    editform.ui \
    answeredit.ui \
    testform.ui \
    answersmultiopt.ui \
    infodialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
