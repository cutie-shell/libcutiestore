#include "cutiestore.h"
#include <QCoreApplication>

CutieStore::CutieStore(QObject *parent)
: QObject(parent), m_appName(QCoreApplication::applicationName()), m_storeName("") {
	connect(&m_watcher, SIGNAL(directoryChanged(QString)),
		this, SLOT(onDataDirModified(QString)));
	connect(&m_watcher, SIGNAL(fileChanged(QString)),
		this, SLOT(onDataFileModified(QString)));
}

void CutieStore::onDataDirModified(QString filePath) {
	Q_UNUSED(filePath);
	QString dirPath = QDir(
		QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)
	).filePath(m_appName);
	QString storeFilePath = QDir(dirPath).filePath(m_storeName + ".dat");
	if (QFile(storeFilePath).exists() &&
		!m_watcher.files().contains(storeFilePath)) 
		m_watcher.addPath(storeFilePath);
}

void CutieStore::onDataFileModified(QString filePath) {
	Q_UNUSED(filePath);
	loadData();
}

QVariantMap CutieStore::data() {
	return m_data;
}

void CutieStore::setData(QVariantMap data) {
	m_data = data;
	saveData();
}

QString CutieStore::storeName() {
	return m_storeName;
}

void CutieStore::setStoreName(QString storeName){
	m_storeName = storeName;
	reload();
}

QString CutieStore::appName() {
	return m_appName;
}

void CutieStore::setAppName(QString appName){
	m_appName = appName;
	reload();
}

void CutieStore::loadData() {
	QString dirPath = QDir(
		QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)
	).filePath(m_appName);
	QString filePath = QDir(dirPath).filePath(m_storeName + ".dat");
	QFile loadFile(filePath);
	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Couldn't open store file.");
		return;
	}

	QByteArray saveData = loadFile.readAll();
	m_data = QCborValue::fromCbor(saveData).toMap().toVariantMap();
	emit dataChanged(m_data);
}

void CutieStore::saveData() {
	QString dirPath = QDir(
		QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)
	).filePath(m_appName);
	QString filePath = QDir(dirPath).filePath(m_storeName + ".dat");
	if (!QDir(dirPath).exists()) {
		QDir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation))
			.mkpath(m_appName);
	}
	QFile saveFile(filePath);
	if (!saveFile.open(QIODevice::WriteOnly))  {
		qWarning("Couldn't open store file.");
		return;
	}

	saveFile.write(QCborValue::fromVariant(m_data).toCbor());
	reload();
}

void CutieStore::reload() {
	if (QDir(QDir(
		QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)
	).filePath(m_appName)).exists()) {
		m_watcher.addPath(QDir(
			QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)
		).filePath(m_appName));
		m_watcher.addPath(QDir(QDir(
			QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)
		).filePath(m_appName)).filePath(m_storeName + ".dat"));
		loadData();
	}
}