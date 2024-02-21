project(GameLib)

set(SOURCE_FILES)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

set(SOURCE_FILES Game.cpp Game.h MainFrame.cpp MainFrame.h pch.h GameView.cpp GameView.h NullBug.cpp NullBug.h BugRedundancy.cpp BugRedundancy.h Bug.cpp Bug.h CodeDlg.cpp CodeDlg.h Clock.cpp Clock.h FatBug.cpp FatBug.h FeatureBug.cpp FeatureBug.h ids.h GarbageBug.cpp GarbageBug.h Item.cpp Item.h Program.cpp Program.h Score.cpp Score.h ClockVisitor.cpp ClockVisitor.h LevelBegin.cpp LevelBegin.h LevelEnd.cpp LevelEnd.h FixedScoreVisitor.cpp FixedScoreVisitor.h OopsScoreVisitor.cpp OopsScoreVisitor.h MissedScoreVisitor.cpp MissedScoreVisitor.h)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)