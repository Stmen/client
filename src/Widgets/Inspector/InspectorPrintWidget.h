#pragma once

#include "../Shared.h"
#include "ui_InspectorPrintWidget.h"

#include "Commands/PrintCommand.h"
#include "Models/LibraryModel.h"

#include <QtCore/QEvent>
#include <QtCore/QObject>
#include <QtCore/QString>

#include <QtGui/QWidget>

class WIDGETS_EXPORT InspectorPrintWidget : public QWidget, Ui::InspectorPrintWidget
{
    Q_OBJECT

    public:
        explicit InspectorPrintWidget(QWidget* parent = 0);

    protected:
        virtual bool eventFilter(QObject* target, QEvent* event);

    private:
        LibraryModel* model;
        PrintCommand* command;

        void blockAllSignals(bool block);

        Q_SLOT void outputChanged(QString);
        Q_SLOT void resetOutput(QString);
};