/*
 * chat-room.h
 * Copyright (C) 2010-2017 Belledonne Communications SARL
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

#ifndef _CHAT_ROOM_H_
#define _CHAT_ROOM_H_

#include <list>

// From coreapi
#include "private.h"

#include "address/address.h"
#include "object/object.h"
#include "conference/conference-interface.h"

#include "chat/chat-message/chat-message.h"

#include "linphone/types.h"

// =============================================================================

LINPHONE_BEGIN_NAMESPACE

class ChatRoomPrivate;

class LINPHONE_PUBLIC ChatRoom : public Object, public ConferenceInterface {
	friend class ChatMessage;
	friend class ChatMessagePrivate;

public:
	L_DECLARE_ENUM(State, L_ENUM_VALUES_CHAT_ROOM_STATE);
	L_OVERRIDE_SHARED_FROM_THIS(ChatRoom);

	ChatRoom (LinphoneCore *core);
	virtual ~ChatRoom () = default;

	void compose ();
	std::shared_ptr<ChatMessage> createFileTransferMessage (const LinphoneContent *initialContent);
	std::shared_ptr<ChatMessage> createMessage (const std::string &msg);
	std::shared_ptr<ChatMessage> createMessage ();
	void deleteHistory ();
	void deleteMessage (const std::shared_ptr<ChatMessage> &msg);
	std::shared_ptr<ChatMessage> findMessage (const std::string& messageId);
	std::shared_ptr<ChatMessage> findMessageWithDirection (const std::string &messageId, ChatMessage::Direction direction);
	std::list<std::shared_ptr<ChatMessage> > getHistory (int nbMessages);
	int getHistorySize ();
	std::list<std::shared_ptr<ChatMessage> > getHistoryRange (int startm, int endm);
	int getUnreadMessagesCount ();
	bool isRemoteComposing () const;
	void markAsRead ();

	LinphoneCore *getCore () const;

	const Address& getPeerAddress () const;
	State getState () const;

protected:
	explicit ChatRoom (ChatRoomPrivate &p);

private:
	L_DECLARE_PRIVATE(ChatRoom);
	L_DISABLE_COPY(ChatRoom);
};

LINPHONE_END_NAMESPACE

#endif // ifndef _CHAT_ROOM_H_