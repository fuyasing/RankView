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
	colinegraphicsitem.cpp
	graphics.cpp
	rankviewdialog.cpp
	nodedata.cpp
	plotwizard.cpp
	tipgraphicsitem.cpp
	scoreview.cpp
	)

set (rankview_MOC_SRCS
	mainwindow.h
	conodegraphicsitem.h
	colinegraphicsitem.h
	graphics.h
	rankviewdialog.h
	nodedata.h
	plotwizard.h
	tipgraphicsitem.h
	scoreview.h
	)

set (rankview_RCCS
	${CMAKE_SOURCE_DIR}/rankImage.qrc
	)

set (rankview_TS_FILES
	${CMAKE_SOURCE_DIR}/i18n/rankview_zh_CN.ts
	)

qt4_wrap_cpp(rankview_MOCS ${rankview_MOC_SRCS})
qt4_add_resources(rankview_RCCS_SRCS ${rankview_RCCS})
qt4_create_translation(rankview_QMS ${rankview_SRCS} ${rankview_TS_FILES})

if(APPLE)
	add_executable (RankView
		MACOSX_BUNDLE
		${rankview_SRCS}
		${rankview_MOCS}
		${rankview_RCCS_SRCS}
		${rankview_QMS}
		)
elseif(WIN32)
	add_executable (RankView
		WIN32
		${rankview_SRCS}
		${rankview_MOCS}
		${rankview_RCCS_SRCS}
		${rankview_QMS}
		)
else(APPLE)
	add_executable (RankView
		${rankview_SRCS}
		${rankview_MOCS}
		${rankview_RCCS_SRCS}
		${rankview_QMS}
		)
endif(APPLE)
target_link_libraries (RankView ${QT_LIBRARIES})
