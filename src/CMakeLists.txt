include_directories (
	${VERSION_HEAD_INCLUDES}
	)

configure_file (
	"${CMAKE_SOURCE_DIR}/version_rankview.h.cmake"
	"${VERSION_HEAD_INCLUDES}/version_rankview.h"
	)

set (rankview_SRCS
	main.cpp
	mainwindow.cpp
	conodegraphicsitem.cpp
	graphics.cpp
	rankviewdialog.cpp
	nodedata.cpp
	plotwizard.cpp
	tipgraphicsitem.cpp
	)

set (rankview_MOC_SRCS
	mainwindow.h
	condegraphicsitem.h
	colinegraphicsitem.h
	graphics.h
	rankviewdialog.h
	nodedata.h
	plotwizard.h
	tipgraphicsitem.h
	)

set (rankview_UIS
	mainwindow.ui
	plotwizard.ui
	)

set (rankview_RCCS
	rankImage.qrc
	)

qt4_wrap_cpp(rankview_MOCS ${rankview_MOC_SRCS})
qt4_wrap_ui(rankview_UIS_H ${rankview_UIS})
qt4_wrap_cpp(rankview_MOCS_UI ${rankview_UIS_H})
qt4_wrap_resources(rankview_RCCS_SRCS ${rankview_RCCS})
add_definitions(-DQT_NO_DEBUG)

add_executable (RankView
	${rankview_SRCS}
	${rankview_MOCS}
	${rankview_UIS_H}
	${rankview_RCCS_SRCS}
	)
target_link_libraries (RankView ${QT_LIBRARIES})
