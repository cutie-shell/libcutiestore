#include "plugin.h"

void CutieStorePlugin::registerTypes(const char *uri)
{
	qmlRegisterType<CutieStore>(uri, 1, 0, "CutieStore");
}
