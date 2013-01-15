#pragma once

#include "../Shared.h"
#include "IPlayoutCommand.h"
#include "IRundownWidget.h"
#include "ui_RundownLevelsWidget.h"
#include "GpiDevice.h"

#include "Global.h"

#include "Commands/ICommand.h"
#include "Commands/LevelsCommand.h"
#include "Models/LibraryModel.h"

#include <QtCore/QString>

#include <QtGui/QWidget>

class WIDGETS_EXPORT RundownLevelsWidget : public QWidget, Ui::RundownLevelsWidget, public IRundownWidget, public IPlayoutCommand
{
    Q_OBJECT

    public:
        explicit RundownLevelsWidget(const LibraryModel& model, QWidget* parent = 0,
                                     const QString& color = Color::DEFAULT_MIXER_COLOR, bool active = false,
                                     bool inGroup = false, bool disconnected = false, bool compactView = false);

        virtual IRundownWidget* clone();

        virtual bool isGroup() const;

        virtual ICommand* getCommand();
        virtual LibraryModel* getLibraryModel();

        virtual void setActive(bool active);
        virtual void setInGroup(bool inGroup);
        virtual void setColor(const QString& color);

        virtual void setExpanded(bool expanded) {}

        virtual bool executeCommand(enum Playout::PlayoutType::Type type);

        virtual void readProperties(boost::property_tree::wptree& pt);
        virtual void writeProperties(QXmlStreamWriter* writer);

        virtual void setCompactView(bool compactView);

    protected:
        virtual bool eventFilter(QObject* target, QEvent* event);

    private:
        bool active;
        bool inGroup;
        bool disconnected;
        bool compactView;
        QString color;
        LibraryModel model;
        LevelsCommand command;

        void checkEmptyDevice();
        void checkGpiTriggerable();

        Q_SLOT void executeClear();
        Q_SLOT void executeClearVideolayer();
        Q_SLOT void executeClearChannel();
        Q_SLOT void channelChanged(int);
        Q_SLOT void executePlay();
        Q_SLOT void executeStop();
        Q_SLOT void videolayerChanged(int);
        Q_SLOT void delayChanged(int);
        Q_SLOT void allowGpiChanged(bool);
        Q_SLOT void gpiDeviceConnected(bool, GpiDevice*);
};