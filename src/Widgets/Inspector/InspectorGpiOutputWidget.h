#pragma once

#include "../Shared.h"
#include "ui_InspectorGpiOutputWidget.h"
#include "Commands/GpiOutputCommand.h"

#include <QWidget>

class WIDGETS_EXPORT InspectorGpiOutputWidget : public QWidget, Ui::InspectorGpiOutputWidget
{
    Q_OBJECT
    
    public:
        explicit InspectorGpiOutputWidget(QWidget *parent = 0);

    protected:
        virtual bool eventFilter(QObject* target, QEvent* event);

    private:
        GpiOutputCommand* command;

        void blockAllSignals(bool block);

        Q_SLOT void gpoPortChanged(int);
        Q_SLOT void resetGpoPort(QString);
        Q_SLOT void triggerOnNextChanged(int);
};
