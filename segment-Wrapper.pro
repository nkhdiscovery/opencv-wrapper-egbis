TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/opt/cuda/lib64 -L/lib64 -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d
LIBS += -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml
LIBS += -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres
LIBS += -lopencv_ts -lopencv_video -lopencv_videostab -ltbb
LIBS += -lGL -lGLU -lrt -lpthread -lm -ldl
LIBS += -lboost_system -lboost_filesystem
INCLUDEPATH +=  -I/usr/include/opencv -I/usr/include/opencv2/


QMAKE_CXXFLAGS += -std=c++11

QMAKE_CXXFLAGS += -std=c++11 -Wall -O3
QMAKE_LFLAGS += -fopenmp -pthread

SOURCES += main.cpp \
    egbis/disjoint-set.cpp \
    egbis/filter.cpp \
    egbis/misc.cpp \
    egbis/segment-graph.cpp \
    egbis/segment-image.cpp \
    egbis/segment.cpp \
    egbis.cpp

DISTFILES +=

HEADERS += \
    egbis/convolve.h \
    egbis/disjoint-set.h \
    egbis/filter.h \
    egbis/image.h \
    egbis/imconv.h \
    egbis/imutil.h \
    egbis/misc.h \
    egbis/pnmfile.h \
    egbis/segment-graph.h \
    egbis/segment-image.h \
    egbis.h \
    nkhUtil.h \
    egbiscv.h
