QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TomogramsSegmentation
TEMPLATE = app

include(global/global.pri)
include(interfaces/interfaces.pri)
include(sources/sources.pri)
include(forms/forms.pri)
include(resources/resources.pri)

INCLUDEPATH += C:\ \
#               C:\opencv\build\include \
#               C:\opencv\build\include\opencv \
#               C:\opencv\build\include\opencv2 \
DEPENDPATH += C:\ \
#               C:\opencv\build\include \
#               C:\opencv\build\include\opencv \
#               C:\opencv\build\include\opencv2 \

#LIBS += -LC:\opencv\build\x64\vc12\lib \
#    opencv_core2413.lib \
#    opencv_highgui2413.lib\
#    opencv_imgproc2413.lib \
#    opencv_features2d2413.lib \
#    opencv_calib3d2413.lib \
