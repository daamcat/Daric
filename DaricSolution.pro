TEMPLATE = subdirs
SUBDIRS += Daric \
    DaricLib \
    DaricTest


Daric.depends = DaricLib
DaricTest.depends = DaricLib
