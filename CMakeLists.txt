project(RankView)

###---cmake related-------------
cmake_minimum_required (VERSION 2.6)

###---basic info settings-------
set (RANKVIEW_VERSION_MAJOR 0)
set (RANKVIEW_VERSION_RELEASE 1)
set (RANKVIEW_VERSION "${RANKVIEW_VERSION_MAJOR}.${RANKVIEW_VERSION_RELEASE}")
set (RANKVIEW_VERSION_STRING "${RANKVIEW_VERSION} (0.1 >=20110525)")

set (RANKVIEW_WEBSITE "http://yandy.combinz.com/rankview")

###---qt check and config---------
find_package(Qt4 4.5.0 COMPONENTS QtCore QtGui QtSql REQIRED)
if(QT4_FOUND)
	set(RANKVIEW_CAN_BE_COMPILED true)
else(QT4_FOUND)
	set(RANKVIEW_CAN_BE_COMPILED false)
endif(QT4_FOUND)

include(${QT_USE_FILE})

###---set include dirs------
set(VERSION_HEAD_INCLUDES
	${CMAKE_BINARY_DIR}
	)

###---set output path-------
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

###---project file---------
if(RANKVIEW_CAN_BE_COMPILED)
	add_subdirectory(src)
endif(RANKVIEW_CAN_BE_COMPILED)
