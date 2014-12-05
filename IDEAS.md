toxscreen
=========

toxscreen is currently just an idea. Things may change. Things
may never get done or started. Who knows.


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


Custom packets
--------------

toxscreen will need to use toxcore's lossless/lossy packet
handling and sending to deal with custom packets for events
that tox doesn't itself support.

--------------------------------------------------------------------------------------------
 Name     | Id   | Reliability | Description
--------------------------------------------------------------------------------------------
 Info     | 160  | Lossless    | Check for toxscreen support of another client
 Connect  | 161  | Lossless    | Request invitation to be a guest or host for screen sharing
 Perm     | 162  | Lossless    | Send permission request/info
 Key      | 170  | Lossless    | Send a keyboard key event (key code?)
 Mouse    | 171  | Lossless    | Send a mouseclick event (x/y position, key code?)
