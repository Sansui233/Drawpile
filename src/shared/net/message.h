/*
   DrawPile - a collaborative drawing program.

   Copyright (C) 2013 Calle Laakkonen

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*/
#ifndef DP_NET_MESSAGE_H
#define DP_NET_MESSAGE_H

namespace protocol {

/**
 * DrawPile network protocol message types
 */
enum MessageType {
	// Login stream
	MSG_LOGIN,
	// Command stream
	MSG_CANVAS_RESIZE,
	MSG_LAYER_CREATE,
	MSG_LAYER_ATTR,
	MSG_LAYER_ORDER,
	MSG_LAYER_DELETE,
	MSG_PUTIMAGE,
	MSG_TOOLCHANGE,
	MSG_PEN_MOVE,
	MSG_PEN_UP,
	MSG_ANNOTATION_CREATE,
	MSG_ANNOTATION_RESHAPE,
	MSG_ANNOTATION_EDIT,
	MSG_ANNOTATION_DELETE,
	MSG_UNDO,
	// Meta stream
	MSG_USER_JOIN,
	MSG_USER_ATTR,
	MSG_USER_LEAVE,
	MSG_CHAT,
	MSG_LAYER_ACL,
	MSG_SNAPSHOT,
	MSG_STREAMPOS
};

class Message {
	friend class MessagePtr;
public:
	Message(MessageType type): _type(type), _refcount(0) {}
	virtual ~Message() = default;
	
	/**
	 * \brief Get the type of this message.
	 * @return message type
	 */
	MessageType type() const { return _type; }
	
	/**
	 * \brief Check if this message type is a command stream type
	 * 
	 * Command stream messages are the messages directly related to drawing.
	 * The canvas can be reconstructed exactly using only command messages.
	 * @return true if this is a drawing command
	 */
	bool isCommand() const { return _type >= MSG_CANVAS_RESIZE && _type <= MSG_UNDO; }

	/**
	 * \brief Get the message
	 * @return message length in bytes
	 */
	int length() const { return 3 + payloadLength(); }
	
protected:
	/**
	 * \brief Get the length of the message payload
	 * @return payload length in bytes
	 */
	virtual int payloadLength() const = 0;
	
private:
	const MessageType _type;

	int _refcount;
};

/**
* @brief A reference counting pointer for Messages
*
* This object is the length of a normal pointer so it can be used
* efficiently with QList.
*/
class MessagePtr {
public:
	explicit MessagePtr(Message *msg)
		: _ptr(msg)
	{
		Q_ASSERT(_ptr);
		Q_ASSERT(_ptr->_refcount==0);
		++_ptr->_refcount;
	}

	MessagePtr(const MessagePtr &ptr) : _ptr(ptr._ptr) { ++_ptr->_refcount; }

	~MessagePtr()
	{
		Q_ASSERT(_ptr->_refcount>0);
		if(--_ptr->_refcount == 0)
			delete _ptr;
	}

	MessagePtr &operator=(const MessagePtr &msg)
	{
		if(msg._ptr != _ptr) {
			Q_ASSERT(_ptr->_refcount>0);
			if(--_ptr->_refcount == 0)
				delete _ptr;
			_ptr = msg._ptr;
			++_ptr->_refcount;
		}
	}

	Message &operator*() const { return *_ptr; }
	Message *operator ->() const { return _ptr; }

	template<class msgtype> msgtype &cast() const { return static_cast<msgtype&>(*_ptr); }

private:
	Message *_ptr;
};

}

#endif
