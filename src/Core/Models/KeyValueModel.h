#pragma once

#include "../Shared.h"

#include <QtCore/QString>

class CORE_EXPORT KeyValueModel
{
    public:
        explicit KeyValueModel(const QString& key, const QString& value);

        const QString& getKey() const;
        const QString& getValue() const;

        void setKey(const QString& key);
        void setValue(const QString& value);

    private:
        QString key;
        QString value;
};
