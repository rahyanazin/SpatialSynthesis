QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  \
                $$PWD/rtaudio \
                $$PWD/audioAnalysis \
                $$PWD/synthesis \
                $$PWD/filter \
                $$PWD/fftw \
                $$PWD/numpy

HEADERS +=  \
            Controller.h \
            SpatialSound.h \
            filter/CIPIC.h \
            #filter/CIPIC_Table.h \
            filter/Head.h \
            filter/HeadModel.h \
            filter/HeadModelTable.h \
            #filter/PinnaModel.h \
            #filter/PinnaModelTable.h \
            rtaudio/RtAudio.h \
            filter/Filter.h \
            filter/Bandpass.h \
            filter/Lowpass.h \
            filter/Highpass.h \
            synthesis/Oscillator.h \
            synthesis/Sine.h \
            synthesis/Square.h \
            synthesis/WhiteNoise.h \
            audioAnalysis/SignalPlot.h \
            audioAnalysis/TransferFunctionPlot.h \
            audioAnalysis/SpectrumPlot.h \
            Synthesizer.h \
            numpy/npy.hpp

SOURCES +=  main.cpp \
            Controller.cpp \
            SpatialSound.cpp \
            filter/CIPIC.cpp \
            #filter/CIPIC_Table.cpp \
            filter/Head.cpp \
            filter/HeadModel.cpp \
            filter/HeadModelTable.cpp \
            #filter/PinnaModel.cpp
            filter/PinnaModelTable.cpp \
            rtaudio/RtAudio.cpp \
            filter/Filter.cpp \
            filter/Bandpass.cpp \
            filter/Lowpass.cpp \
            filter/Highpass.cpp \
            synthesis/Oscillator.cpp \
            synthesis/Sine.cpp \
            synthesis/Square.cpp \
            synthesis/WhiteNoise.cpp \
            audioAnalysis/SignalPlot.cpp \
            audioAnalysis/TransferFunctionPlot.cpp \
            audioAnalysis/SpectrumPlot.cpp \
            Synthesizer.cpp

RESOURCES += $$PWD/resources/qml.qrc

DEFINES +=  __WINDOWS_DS__ _WIN32

LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.18362.0/um/x64/"
LIBS += -luser32 -ldsound -lole32 -lmf -lmfreadwrite -lmfplat -lmfuuid -lwinmm
LIBS += $$PWD/fftw/libfftw3-3.lib

DISTFILES +=
