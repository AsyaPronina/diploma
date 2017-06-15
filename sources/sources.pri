INCLUDEPATH += $$PWD/model \
               $$PWD/views \
               $$PWD/presenters \
               $$PWD/


SOURCES += $$PWD/main.cpp \
           $$PWD/model/domainmodel.cpp \
           $$PWD/model/tomogram.cpp \
           $$PWD/views/mainwindow.cpp \
           $$PWD/views/viewfactory.cpp \
           $$PWD/views/propertyview.cpp \
           $$PWD/views/sliceview.cpp \
           $$PWD/views/volumeview.cpp \
           $$PWD/presenters/mainpresenter.cpp \
           $$PWD/presenters/slicepresenter.cpp \
           $$PWD/presenters/propertypresenter.cpp \    
           $$PWD/presenters/volumepresenter.cpp

HEADERS += $$PWD/model/domainmodel.h \
           $$PWD/model/tomogram.h \
           $$PWD/views/mainwindow.h \
           $$PWD/views/viewfactory.h \
           $$PWD/views/propertyview.h \
           $$PWD/views/sliceview.h \
           $$PWD/views/volumeview.h \
           $$PWD/presenters/mainpresenter.h \
           $$PWD/presenters/slicepresenter.h \
           $$PWD/presenters/propertypresenter.h \    
           $$PWD/presenters/volumepresenter.h

