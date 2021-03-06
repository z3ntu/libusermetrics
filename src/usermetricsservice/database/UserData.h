/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Pete Woods <pete.woods@canonical.com>
 */

#ifndef USERMETRICSSERVICE_USERDATA_H_
#define USERMETRICSSERVICE_USERDATA_H_

#include <QDjangoModel.h>

namespace UserMetricsService {

class Q_DECL_EXPORT UserData: public QDjangoModel {
Q_OBJECT

Q_PROPERTY(int id READ id WRITE setId)

Q_PROPERTY(QString username READ username WRITE setUsername)

Q_CLASSINFO("id", "primary_key=true auto_increment=true")

Q_CLASSINFO("username", "unique=true")

public:
	explicit UserData(QObject *parent = 0);

	virtual ~UserData();

	static void findById(int id, UserData *userData);

	static void findByName(const QString &name, UserData *userData);

	int id() const;

	void setId(int id);

	const QString & username() const;

	void setUsername(const QString &username);

protected:
	int m_id;

	QString m_username;
};

}
#endif // USERMETRICSSERVICE_USERDATA_H_
