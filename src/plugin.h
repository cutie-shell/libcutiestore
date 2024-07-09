#pragma once
#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>

#include "cutiestore.h"

class CutieStorePlugin : public QQmlExtensionPlugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid FILE
			  "cutiestore.json")
    public:
	explicit CutieStorePlugin()
	{
	}

	void registerTypes(const char *uri) override;
};