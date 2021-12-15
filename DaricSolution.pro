TEMPLATE = subdirs

# Directories relative to the directory of meta-project. Each subdir must contain a .pro file with the same
# name as its directory name:
SUBDIRS += \
    Daric \
    DaricLib \
    DropboxQt/dropboxQt \
    DaricTest \
#    DaricGTest

# Which project depends on which (The name is equal to subdir name, and to .pro file name inside subdir)
# Example: Daric.depends = DaricLib tells qMake that Daric.pro can build only if DaricLib.pro builds.
DaricLib.depends += DropboxQt/dropboxQt
Daric.depends += DaricLib
DaricTest.depends = DaricLib
#DaricGTest.depends = DaricLib

