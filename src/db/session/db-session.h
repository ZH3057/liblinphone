/*
 * db-session.h
 * Copyright (C) 2010-2018 Belledonne Communications SARL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef _L_DB_SESSION_H_
#define _L_DB_SESSION_H_

#ifdef SOCI_ENABLED
	#include <soci/soci.h>
#endif // ifdef SOCI_ENABLED

#include "object/clonable-object.h"

// =============================================================================

LINPHONE_BEGIN_NAMESPACE

class DbSessionPrivate;

class DbSession : public ClonableObject {
	friend class DbSessionProvider;

public:
	DbSession ();
	explicit DbSession (const std::string &uri);
	DbSession (const DbSession &src);

	DbSession &operator= (const DbSession &src);

	operator bool () const;

	#ifdef SOCI_ENABLED
		soci::session *getBackendSession () const;
	#endif // ifdef SOCI_ENABLED

	std::string primaryKeyStr (const std::string &type = "INT") const;
	std::string primaryKeyRefStr (const std::string &type = "INT") const;
	std::string varcharPrimaryKeyStr (int length) const;

	std::string timestampType () const;

	std::string noLimitValue () const;

	long long getLastInsertId () const;

	void enableForeignKeys (bool status);

	bool checkTableExists (const std::string &table) const;

private:
	L_DECLARE_PRIVATE(DbSession);
};

LINPHONE_END_NAMESPACE

#endif // ifndef _L_DB_SESSION_H_