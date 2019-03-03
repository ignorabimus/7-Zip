7-Zip
=====

Fork of [7-Zip](https://www.7-zip.org/)


Features
--------

* based on 7-Zip 19.00
* implemented setting process/thread priority for ZIP compression


set process priority
--------------------

add command line option -mprocpri[0-5].

| Level      | process priority            |         |
-------------|-----------------------------|---------|
| -mprocpri0 | IDLE_PRIORITY_CLASS         |         |
| -mprocpri1 | BELOW_NORMAL_PRIORITY_CLASS |         |
| -mprocpri2 | NORMAL_PRIORITY_CLASS       | default |
| -mprocpri3 | ABOVE_NORMAL_PRIORITY_CLASS |         |
| -mprocpri4 | HIGH_PRIORITY_CLASS         |         |
| -mprocpri5 | REALTIME_PRIORITY_CLASS     |         |

set thread priority
--------------------

add command line option -mthrdpri[0-6].

| Level      | thread priority               |         |
-------------|-------------------------------|---------|
| -mthrdpri0 | THREAD_PRIORITY_IDLE          |         |
| -mthrdpri1 | THREAD_PRIORITY_LOWEST        |         |
| -mthrdpri2 | THREAD_PRIORITY_BELOW_NORMAL  |         |
| -mthrdpri3 | THREAD_PRIORITY_NORMAL        | default |
| -mthrdpri4 | THREAD_PRIORITY_ABOVE_NORMAL  |         |
| -mthrdpri5 | THREAD_PRIORITY_HIGHEST       |         |
| -mthrdpri6 | THREAD_PRIORITY_TIME_CRITICAL |         |
