#include "InspectorGridWidget.h"

#include "Global.h"

#include "DatabaseManager.h"
#include "EventManager.h"
#include "Events/PreviewEvent.h"
#include "Models/TweenModel.h"

#include <QtGui/QApplication>

InspectorGridWidget::InspectorGridWidget(QWidget* parent)
    : QWidget(parent), model(NULL), command(NULL)
{
    setupUi(this);

    QObject::connect(&EventManager::getInstance(), SIGNAL(rundownItemSelected(const RundownItemSelectedEvent&)), this, SLOT(rundownItemSelected(const RundownItemSelectedEvent&)));

    loadTween();
}

void InspectorGridWidget::rundownItemSelected(const RundownItemSelectedEvent& event)
{
    this->model = event.getLibraryModel();

    blockAllSignals(true);

    if (dynamic_cast<GridCommand*>(event.getCommand()))
    {
        this->command = dynamic_cast<GridCommand*>(event.getCommand());

        this->spinBoxGrid->setValue(this->command->getGrid());
        this->spinBoxDuration->setValue(this->command->getDuration());
        this->comboBoxTween->setCurrentIndex(this->comboBoxTween->findText(this->command->getTween()));
        this->checkBoxDefer->setChecked(this->command->getDefer());
    }

    blockAllSignals(false);
}

void InspectorGridWidget::blockAllSignals(bool block)
{
    this->spinBoxGrid->blockSignals(block);
    this->spinBoxDuration->blockSignals(block);
    this->comboBoxTween->blockSignals(block);
    this->checkBoxDefer->blockSignals(block);
}

void InspectorGridWidget::loadTween()
{
    // We do not have a command object, block the signals.
    // Events will not be triggered while we update the values.
    this->comboBoxTween->blockSignals(true);

    QList<TweenModel> models = DatabaseManager::getInstance().getTween();
    foreach (TweenModel model, models)
        this->comboBoxTween->addItem(model.getValue());

    this->comboBoxTween->blockSignals(false);
}

void InspectorGridWidget::durationChanged(int duration)
{
    this->command->setDuration(duration);
}

void InspectorGridWidget::tweenChanged(QString tween)
{
    this->command->setTween(tween);
}

void InspectorGridWidget::gridChanged(int grid)
{
    this->command->setGrid(grid);

    EventManager::getInstance().firePreviewEvent(PreviewEvent());
}

void InspectorGridWidget::resetGrid(QString grid)
{
    this->spinBoxGrid->setValue(1);
    this->command->setGrid(this->spinBoxGrid->value());

    EventManager::getInstance().firePreviewEvent(PreviewEvent());
}

void InspectorGridWidget::resetDuration(QString duration)
{
    this->spinBoxDuration->setValue(Mixer::DEFAULT_DURATION);
    this->command->setDuration(this->spinBoxDuration->value());
}

void InspectorGridWidget::resetTween(QString tween)
{
    this->comboBoxTween->setCurrentIndex(this->comboBoxTween->findText(Mixer::DEFAULT_TWEEN));
    this->command->setTween(this->comboBoxTween->currentText());
}

void InspectorGridWidget::deferChanged(int state)
{
    this->command->setDefer((state == Qt::Checked) ? true : false);
}

void InspectorGridWidget::resetDefer(QString defer)
{
    this->checkBoxDefer->setChecked(Mixer::DEFAULT_DEFER);
    this->command->setDefer(this->checkBoxDefer->isChecked());
}
