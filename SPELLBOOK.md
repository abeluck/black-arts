# Black Magic

## Spell 0x0

Passing an application's STDIN fd to another process through an abstract unix
domain socket, that the other process can subsequently read from.

## Incantations

Linux:

    $ make
    $ ./server < wizard
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

# The Masters

The crucial `[send,recv]_fd()` functions are from Thomas at
http://www.thomasstover.com/uds.html
