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

#ifndef USERMETRICSOUTPUT_USERMETRICSIMPL_H_
#define USERMETRICSOUTPUT_USERMETRICSIMPL_H_

#include <libusermetricsoutput/UserMetrics.h>
#include <libusermetricsoutput/UserDataStore.h>
#include <libusermetricscommon/DateFactory.h>
#include <libusermetricsoutput/ColorThemeImpl.h>
#include <libusermetricsoutput/ColorThemeProvider.h>
#include <libusermetricsoutput/qvariantlistmodel.h>

#include <QtCore/QSharedPointer>
#include <QtCore/QScopedPointer>

namespace UserMetricsOutput {

class UserMetricsImpl: public UserMetrics {
Q_OBJECT

public:
	UserMetricsImpl(QSharedPointer<UserMetricsCommon::DateFactory> dateFactory,
			QSharedPointer<UserDataStore> dataSetStore,
			QSharedPointer<ColorThemeProvider> colorThemeProvider,
			QObject *parent = 0);

	virtual ~UserMetricsImpl();

	virtual void setLabel(const QString &label);

	virtual QString label() const;

	virtual QString username() const;

	virtual void setUsername(const QString &username);

	virtual ColorTheme * firstColor() const;

	virtual QAbstractItemModel *firstMonth() const;

	virtual int currentDay() const;

	virtual void setCurrentDay(int currentDay);

	virtual ColorTheme * secondColor() const;

	virtual QAbstractItemModel *secondMonth() const;

public Q_SLOTS:
	virtual void nextDataSourceSlot();

	virtual void readyForDataChangeSlot();

protected:
	virtual void prepareToLoadDataSource();

	virtual void finishLoadingDataSource();

	virtual void setUsernameInternal(const QString &username);

	void updateMonth(QVariantListModel &month, const int dayOfMonth,
			const int daysInMonth, QVariantList::const_iterator& index,
			const QVariantList::const_iterator& end);

	QSharedPointer<UserMetricsCommon::DateFactory> m_dateFactory;

	QSharedPointer<UserDataStore> m_userDataStore;

	QSharedPointer<ColorThemeProvider> m_colorThemeProvider;

	QString m_label;

	QScopedPointer<ColorThemeImpl> m_firstColor;

	QScopedPointer<QVariantListModel> m_firstMonth;

	QScopedPointer<ColorThemeImpl> m_secondColor;

	QScopedPointer<QVariantListModel> m_secondMonth;

	int m_currentDay;

	bool m_noDataForUser;

	bool m_oldNoDataForUser;

	QString m_username;

	UserDataStore::const_iterator m_userDataIterator;

	UserDataStore::UserDataPtr m_userData;

	UserData::const_iterator m_dataSetIterator;

	UserData::DataSetPtr m_dataSet;
};

}

#endif /* USERMETRICSOUTPUT_USERMETRICSIMPL_H_ */
