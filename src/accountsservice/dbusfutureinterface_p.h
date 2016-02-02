/****************************************************************************
 * This file is part of Qt AccountsService Addon.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#ifndef QTACCOUNTSSERVICE_DBUSFUTUREINTERFACE_P_H
#define QTACCOUNTSSERVICE_DBUSFUTUREINTERFACE_P_H

#include <QtCore/QFutureInterface>
#include <QtCore/QObject>
#include <QtDBus/QDBusPendingCallWatcher>
#include <QtDBus/QDBusPendingReply>

#include <qtaccountsservice/qtaccountsservice_export.h>

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt AccountsService Addon API.  It exists
// purely as an implementation detail.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

namespace QtAccountsService {

template <typename T>
class DBusFutureInterface : public QObject, public QFutureInterface<T>
{
public:
    DBusFutureInterface(const QDBusPendingReply<T> &reply)
        : m_reply(reply)
        , m_watcher(Q_NULLPTR)
    {}

    virtual ~DBusFutureInterface()
    {}

    virtual QFuture<T> start()
    {
        m_watcher = new QDBusPendingCallWatcher(m_reply);
        connect(m_watcher, &QDBusPendingCallWatcher::finished, this, [this] {
            if (m_reply.isError()) {
                QDBusError error = m_reply.error();
                this->setProgressValueAndText(100, error.errorString(error.type()));
                this->reportCanceled();
            } else {
                this->reportResult(m_reply.value());
                this->reportFinished();
            }

            m_watcher->deleteLater();
            m_watcher = Q_NULLPTR;
        });

        this->reportStarted();

        return this->future();
    }

protected:
    QDBusPendingReply<T> m_reply;
    QDBusPendingCallWatcher *m_watcher;
};

} // namespace QtAccountsService

#endif // QTACCOUNTSSERVICE_DBUSFUTUREINTERFACE_P_H
