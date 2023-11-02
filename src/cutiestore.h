#pragma once
#include <QFileSystemWatcher>
#include <QStandardPaths>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCborMap>

class CutieStore : public QObject {
	Q_OBJECT
	Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)
	Q_PROPERTY(QString appName READ appName WRITE setAppName NOTIFY appNameChanged)
	Q_PROPERTY(QString storeName READ storeName WRITE setStoreName NOTIFY storeNameChanged)
public:
	CutieStore(QObject *parent = 0);
	QVariantMap data();
	void setData(QVariantMap data);
	QString appName();
	void setAppName(QString appName);
	QString storeName();
	void setStoreName(QString storeName);

Q_SIGNALS:
	void dataChanged(QVariantMap data);
	void storeNameChanged(QString storeName);
	void appNameChanged(QString appName);

private Q_SLOTS:
	void onDataDirModified(QString filePath);
	void onDataFileModified(QString filePath);

private:
	void loadData();
	void saveData();
	void reload();

	QFileSystemWatcher m_watcher;
	QString m_appName;
	QString m_storeName;
	QVariantMap m_data;
};