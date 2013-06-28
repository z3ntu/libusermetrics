/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of version 3 of the GNU Lesser General Public License as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Pete Woods <pete.woods@canonical.com>
 */

#include <libusermetricsoutput/SyncedUserMetricsStore.h>
#include <libusermetricsoutput/SyncedUserData.h>

#include <libusermetricscommon/UserDataInterface.h>
#include <libusermetricscommon/DBusPaths.h>

using namespace com;
using namespace UserMetricsCommon;
using namespace UserMetricsOutput;

SyncedUserMetricsStore::SyncedUserMetricsStore(
		const QDBusConnection &dbusConnection, QObject *parent) :
		UserMetricsStore(parent), m_interface(DBusPaths::serviceName(),
				DBusPaths::userMetrics(), dbusConnection) {
	for (const QDBusObjectPath &path : m_interface.userDatas()) {

		QSharedPointer<canonical::usermetrics::UserData> userData(
				new canonical::usermetrics::UserData(DBusPaths::serviceName(),
						path.path(), m_interface.connection()));

		QString username(userData->username());
		insert(username, UserDataPtr(new SyncedUserData(userData)));
	}
}

SyncedUserMetricsStore::~SyncedUserMetricsStore() {
}
