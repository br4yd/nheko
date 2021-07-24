// SPDX-FileCopyrightText: 2021 Nheko Contributors
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef READRECEIPTSMODEL_H
#define READRECEIPTSMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QString>
#include <QDateTime>

class ReadReceiptsModel : public QAbstractListModel
{
        Q_OBJECT

        Q_PROPERTY(QString eventId READ eventId CONSTANT)
        Q_PROPERTY(QString roomId READ roomId CONSTANT)

public:
        enum Roles
        {
                Mxid,
                DisplayName,
                AvatarUrl,
                Timestamp,
        };

        explicit ReadReceiptsModel(QString event_id, QString room_id, QObject *parent = nullptr);

        QString eventId() const { return event_id_; }
        QString roomId() const { return room_id_; }

        QHash<int, QByteArray> roleNames() const override;
        int rowCount(const QModelIndex &parent) const override
        {
                Q_UNUSED(parent)
                return readReceipts_.size();
        }
        QVariant data(const QModelIndex &index, int role) const override;

public slots:
        void addUsers(const std::multimap<uint64_t, std::string, std::greater<uint64_t>> &users);

private:
        QString dateFormat(const QDateTime &then) const;

        QString event_id_;
        QString room_id_;
        QVector<QPair<QString, QDateTime>> readReceipts_;
};

#endif // READRECEIPTSMODEL_H
