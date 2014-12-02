#pragma once

#include "../Shared.h"
#include "AbstractRundownWidget.h"
#include "ui_RundownDeckLinkInputWidget.h"

#include "Global.h"

#include "CasparDevice.h"

#include "GpiDevice.h"

#include "OscSubscription.h"
#include "Animations/ActiveAnimation.h"
#include "Commands/AbstractCommand.h"
#include "Commands/AbstractPlayoutCommand.h"
#include "Commands/DeckLinkInputCommand.h"
#include "Events/Inspector/DeviceChangedEvent.h"
#include "Events/Inspector/LabelChangedEvent.h"
#include "Events/Inspector/TargetChangedEvent.h"
#include "Models/LibraryModel.h"

#include <QtCore/QString>
#include <QtCore/QTimer>

#include <QtWidgets/QWidget>

class WIDGETS_EXPORT RundownDeckLinkInputWidget : public QWidget, Ui::RundownDeckLinkInputWidget, public AbstractRundownWidget, public AbstractPlayoutCommand
{
    Q_OBJECT

    public:
        explicit RundownDeckLinkInputWidget(const LibraryModel& model, QWidget* parent = 0, const QString& color = Color::DEFAULT_TRANSPARENT_COLOR,
                                            bool active = false, bool loaded = false, bool paused = false, bool playing = false,
                                            bool inGroup = false, bool compactView = false);

        virtual AbstractRundownWidget* clone();

        virtual bool isGroup() const;
        virtual bool isInGroup() const;

        virtual AbstractCommand* getCommand();
        virtual LibraryModel* getLibraryModel();

        virtual void setActive(bool active);
        virtual void setInGroup(bool inGroup);
        virtual void setColor(const QString& color);
        virtual QString getColor() const;

        virtual void setExpanded(bool /* expanded */) {}

        virtual bool executeCommand(Playout::PlayoutType::Type type);

        virtual void readProperties(boost::property_tree::wptree& pt);
        virtual void writeProperties(QXmlStreamWriter* writer);

        virtual void setCompactView(bool compactView);

        virtual void clearDelayedCommands();

        virtual void setUsed(bool used);

    private:
        bool active;
        bool loaded;
        bool paused;
        bool playing;
        bool inGroup;
        bool compactView;
        QString color;
        LibraryModel model;
        DeckLinkInputCommand command;
        ActiveAnimation* animation;
        QString delayType;
        bool markUsedItems;

        OscSubscription* stopControlSubscription;
        OscSubscription* playControlSubscription;
        OscSubscription* playNowControlSubscription;
        OscSubscription* loadControlSubscription;
        OscSubscription* pauseControlSubscription;
        OscSubscription* clearControlSubscription;
        OscSubscription* clearVideolayerControlSubscription;
        OscSubscription* clearChannelControlSubscription;

        QTimer executeTimer;

        void checkEmptyDevice();
        void checkGpiConnection();
        void checkDeviceConnection();
        void configureOscSubscriptions();

        Q_SLOT void executeClearVideolayer();
        Q_SLOT void executeClearChannel();
        Q_SLOT void channelChanged(int);
        Q_SLOT void executeLoad();
        Q_SLOT void executePlay();
        Q_SLOT void executePause();
        Q_SLOT void executeStop();
        Q_SLOT void videolayerChanged(int);
        Q_SLOT void delayChanged(int);
        Q_SLOT void allowGpiChanged(bool);
        Q_SLOT void remoteTriggerIdChanged(const QString&);
        Q_SLOT void gpiConnectionStateChanged(bool, GpiDevice*);
        Q_SLOT void deviceConnectionStateChanged(CasparDevice&);
        Q_SLOT void deviceAdded(CasparDevice&);
        Q_SLOT void stopControlSubscriptionReceived(const QString&, const QList<QVariant>&);
        Q_SLOT void playControlSubscriptionReceived(const QString&, const QList<QVariant>&);
        Q_SLOT void playNowControlSubscriptionReceived(const QString&, const QList<QVariant>&);
        Q_SLOT void loadControlSubscriptionReceived(const QString&, const QList<QVariant>&);
        Q_SLOT void pauseControlSubscriptionReceived(const QString&, const QList<QVariant>&);
        Q_SLOT void clearControlSubscriptionReceived(const QString&, const QList<QVariant>&);
        Q_SLOT void clearVideolayerControlSubscriptionReceived(const QString&, const QList<QVariant>&);
        Q_SLOT void clearChannelControlSubscriptionReceived(const QString&, const QList<QVariant>&);
        Q_SLOT void labelChanged(const LabelChangedEvent&);
        Q_SLOT void deviceChanged(const DeviceChangedEvent&);
};
