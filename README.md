toxscreen
=========

toxscreen is currently just an idea. Things may change. Things
may never get done or started. Who knows.

See [STRUCTURE.md] for packet structure ideas.

Tools to use
------------

- Primary language: C++
- UI Library: Qt5


Project aims
------------

- Open source, cross-platform Teamviewer-like screen sharing
  using tox's custom packet sending/handling as a means of
  communication.
- Chat should be implemented using basic tox chat (and should
  be similar in style to Teamviewer's chat?).
- Similarly, file transfers can be implemented via tox's file
  transfer functions.
- Should be secure. Only let others trigger keyboard events,
  click events, file transfers, etc. if allowed.


Usage of toxav for audio/video
------------------------------

Currently unsure if using toxav for video will be efficient
enough. We will probably not want to send any screen data that
hasn't changed, which may not be possible using toxav's
functions for sending video data?

For sending audio data I can't think of any drawbacks for now.


Initiating a connection
-----------------------

Processes that screentox will go through for initiating a connection.

Guest side:
- Guest client is given some tox address by user, which is to be connected to
- Given the address, client checks if a friend is added that matches the
  address. If not, sends a friend request.
- Once added as a friend (and packet handlers registered), sends a
  screentox Info request. Wait N seconds (maybe 5 by default?).
- When a response is received, checks protocol version compatibility.
  If compatible, sends a screentox Connect request.
- If the host accepts via a Connect request, consider the session started.

Host side:
- Host client is sent a Connect request by a friend.
- If the client has received an Info request recently from the friend, and
  the protocol versions are compatible, respond to indicate success.


Custom packets
--------------

toxscreen will need to use toxcore's lossless/lossy packet
handling and sending to deal with custom packets for events
that tox doesn't itself support.

 Name      | Id   | Reliability | Description
---------- | ---- | ----------- | -----------------------------------------------------------
 Info      | 160  | Lossless    | Check for toxscreen support of another client
 Connect   | 161  | Lossless    | Request invitation to be a guest or host for screen sharing
 Perm      | 162  | Lossless    | Send permission request/info
 Key       | 170  | Lossless    | Send a keyboard key event (key code?)
 Mouse     | 171  | Lossless    | Send a mouseclick event (x/y position, key code?)
 Clipboard | 172  | Lossless    | Send a clipboard event (copy/paste data, variable length)

[STRUCTURE.md]:https://github.com/saneki/toxscreen/blob/master/STRUCTURE.md
