####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -std=c++11 -O2 -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = amazon.cpp \
		book.cpp \
		clothing.cpp \
		db_parser.cpp \
		hash.cpp \
		heap.cpp \
		movie.cpp \
		msort.cpp \
		mydatastore.cpp \
		product.cpp \
		product_parser.cpp \
		qt.cpp \
		user.cpp \
		util.cpp moc_qt.cpp
OBJECTS       = amazon.o \
		book.o \
		clothing.o \
		db_parser.o \
		hash.o \
		heap.o \
		movie.o \
		msort.o \
		mydatastore.o \
		product.o \
		product_parser.o \
		qt.o \
		user.o \
		util.o \
		moc_qt.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		hw8.pro
QMAKE_TARGET  = hw8
DESTDIR       = 
TARGET        = hw8

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: hw8.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile hw8.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile hw8.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/hw81.0.0 || $(MKDIR) .tmp/hw81.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/hw81.0.0/ && $(COPY_FILE) --parents book.h clothing.h datastore.h db_parser.h hash.h heap.h movie.h msort.h mydatastore.h product.h product_parser.h qt.h review.h user.h util.h .tmp/hw81.0.0/ && $(COPY_FILE) --parents amazon.cpp book.cpp clothing.cpp db_parser.cpp hash.cpp heap.cpp movie.cpp msort.cpp mydatastore.cpp product.cpp product_parser.cpp qt.cpp user.cpp util.cpp .tmp/hw81.0.0/ && (cd `dirname .tmp/hw81.0.0` && $(TAR) hw81.0.0.tar hw81.0.0 && $(COMPRESS) hw81.0.0.tar) && $(MOVE) `dirname .tmp/hw81.0.0`/hw81.0.0.tar.gz . && $(DEL_FILE) -r .tmp/hw81.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_qt.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_qt.cpp
moc_qt.cpp: mydatastore.h \
		product.h \
		review.h \
		datastore.h \
		user.h \
		util.h \
		msort.h \
		qt.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qt.h -o moc_qt.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

amazon.o: amazon.cpp product.h \
		review.h \
		mydatastore.h \
		datastore.h \
		user.h \
		util.h \
		db_parser.h \
		product_parser.h \
		qt.h \
		msort.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o amazon.o amazon.cpp

book.o: book.cpp book.h \
		product.h \
		review.h \
		util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o book.o book.cpp

clothing.o: clothing.cpp clothing.h \
		product.h \
		review.h \
		util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o clothing.o clothing.cpp

db_parser.o: db_parser.cpp db_parser.h \
		datastore.h \
		product.h \
		review.h \
		user.h \
		product_parser.h \
		util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o db_parser.o db_parser.cpp

hash.o: hash.cpp hash.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hash.o hash.cpp

heap.o: heap.cpp heap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o heap.o heap.cpp

movie.o: movie.cpp movie.h \
		product.h \
		review.h \
		util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o movie.o movie.cpp

msort.o: msort.cpp msort.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o msort.o msort.cpp

mydatastore.o: mydatastore.cpp mydatastore.h \
		product.h \
		review.h \
		datastore.h \
		user.h \
		util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mydatastore.o mydatastore.cpp

product.o: product.cpp product.h \
		review.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o product.o product.cpp

product_parser.o: product_parser.cpp product_parser.h \
		product.h \
		review.h \
		book.h \
		util.h \
		clothing.h \
		movie.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o product_parser.o product_parser.cpp

qt.o: qt.cpp qt.h \
		mydatastore.h \
		product.h \
		review.h \
		datastore.h \
		user.h \
		util.h \
		msort.h \
		hash.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qt.o qt.cpp

user.o: user.cpp user.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o user.o user.cpp

util.o: util.cpp util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o util.o util.cpp

moc_qt.o: moc_qt.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qt.o moc_qt.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

