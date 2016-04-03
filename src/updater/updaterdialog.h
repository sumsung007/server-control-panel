#ifndef UPDATERDIALOG_H
#define UPDATERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProcess>
#include <QMessageBox> /* Remove+Debug: Download clicked */
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QDir>

#include "src/json.h"
#include "registriesdownloader.h"

#include "src/downloadmanager.h"
#include "src/downloadthread.h"

#include "actioncolumnitemdelegate.h"
#include "softwarecolumnitemdelegate.h"

namespace Updater
{
    namespace Ui {
        class UpdaterDialog;
    }

    class UpdaterDialog : public QDialog
    {
        Q_OBJECT

        public:
            explicit UpdaterDialog(QWidget *parent = 0);
            ~UpdaterDialog();

            void setJsonToServerStackTable(QJsonObject json);

            enum Columns {
             // Column   0             1             2             3            4         5
                SoftwareComponent, WebsiteURL, YourVersion,  LatestVersion, DownloadURL,  Action
            };

        protected:
            QStandardItemModel           *model;
            QSortFilterProxyModel        *myFilterProxyModel;
            Downloader::DownloadManager  *downloadManager;
            SoftwareRegistry::Manager    *softwareRegistry;

        private:
            Ui::UpdaterDialog *ui;
            void resetProgressBar();
            Updater::SoftwareColumnItemDelegate *softwareDelegate;
            Updater::ActionColumnItemDelegate   *actionDelegate;

        signals:
            void clicked(const QString &websiteLink);

        public slots:
            void doDownload(const QModelIndex &index);
            void doInstall(const QModelIndex &index);

            void updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
            void updateMainDownloadProgressBar();
            void downloadsFinished();

        private slots:
            void on_searchLineEdit_textChanged(const QString &arg1);
    };

}

#endif // UPDATERDIALOG_H
