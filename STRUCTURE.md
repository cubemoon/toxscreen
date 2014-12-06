toxscreen packet structure ideas
================================

Ideas on toxscreen packet structures.

Packet Header / Ids
-------------------

```
// Lossless packet id constants (these may change)
// This currently assumes we'll be registering separate tox packet handlers
// for each toxscreen packet type
#define TOXSCREEN_ID_INFO 160
#define TOXSCREEN_ID_CONNECT 161
#define TOXSCREEN_ID_PERMISSIONS 162
#define TOXSCREEN_ID_EVENT_KEY 170
#define TOXSCREEN_ID_EVENT_MOUSE 171
#define TOXSCREEN_ID_EVENT_CLIPBOARD 172

// Packet header present in all toxscreen packets
struct toxscreen_packet_header {
  uint64_t timestamp; // Time sent
};
```


Info
----

Info packets would be used to request toxscreen support and protocol version information
from friends. They could also be used to send version information without requesting anything.

```
struct toxscreen_info_packet {
  uint8_t info_flag; // -------X : If set, requesting a response with friend's version info
  uint64_t version;  // toxscreen protocol version id
};
```


Connecting
----------

Connect packets would be used to request connections.

```
// Used to request connections
struct toxscreen_connect_packet {
  uint8_t connect_flag; // -------X : If set, request connecting to host as guest
                        //            Otherwise, request friend connect as guest to host
                        // ------X- : If set, informing that we're disconnecting
                        // XXXXXX-- : Reserved
};
```


Events
------

Event packets would be used to request events from guest to host. These requests
may be ignored by the host if the guest doesn't have the proper permissions to trigger
certain events.

```
// Signals a keyboard event
struct event_keyboard_packet {
  uint8_t key_flags; // -------X : If set, key down event. Otherwise key up event.
                     // ------X- : If set, simple key event. (necessary?)
  uint32_t key_code; // Unsure how this will work cross-platform...
};

// Signals a mouse click event
// This may be sent to only indicate updated X/Y position, as
// certain mouse buttons may be considered "down" (from mouse down),
// which would be used for drag and drop, etc.
struct event_mouse_packet {
  uint8_t mouse_flags; // -------X : If set, mouse down event. Otherwise mouse up event.
                       // ------X- : If set, simple click event. (necessary?)
  uint8_t button_id;   // Button Id
  uint32_t x;          // X position
  uint32_t y;          // Y position
};

// Signals a clipboard event
struct event_clipboard_packet {
  uint64_t size;                 // Amount of data involved in this event
  uint8_t buffer[SOME_MAX_SIZE]; // Data to send, doesn't need to be a buffer with a max size
};
```


Permissions
-----------

Permission packets would be used to request certain permissions when sent from
guest to host, or inform a guest of their permissions if sent from host to guest.

```
// Request certain permissions
struct permission_request_packet {
  uint32_t permissions_flag; // As specified in permission_info_packet,
                             // with the desired value
};

// Permission information packet
// Sent from host -> guest to inform the guest of what they're allowed to do.
struct permission_info_packet {
  uint32_t permissions_flag; // -------X : Keyboard events enabled
                             // ------X- : Mouse events enabled
                             // -----X-- : Audio enabled
                             // ----X--- : File transfer enabled
                             // ---X---- : Chat enabled
                             // --X----- : Screen switch enabled?
                             // -X------ : Clipboard transfer enabled
                             // X------- : Reserved (with the 24 other bits)
};
```
