# Black Magic

## Spell 0x0: STDIN Sleight of Hand

Passing an application's STDIN fd to another process through an abstract unix
domain socket, that the other process can subsequently read from.

## Incantations

Linux:

    $ make
    $ ./server < ../wizard
    (open another terminal)
    $ ./client

Android (after setting up your NDK environment):

    $ make clean # if you did previous
    $ make -f Makefile.android
    $ adb push server /data/local/tmp/
    $ adb push client /data/local/tmp/
    $ adb push wizard /sdcard/
    $ adb shell "/data/local/tmp/server < /sdcard/wizard"
    (open another terminal)
    $ adb shell /data/local/tmp/client

## Spell 0x1: Switcharoo

invoker.py invokes server and communicates to it via STDIN and STDOUT, but
server doesn't have a flippin clue, so server opens a unix domain socket and
waits connections from someone who does. client knows what's up, so server passes its
STDIN and STDOUT fds to client, then exits.

invoker is now communicating with client.

## Incantations

Linux:

    $ make
    $ python invoker.py < ../wizard
    (open another terminal)
    $ ./client


# The Masters

The crucial `[send,recv]_fd()` functions are from Thomas at
http://www.thomasstover.com/uds.html
