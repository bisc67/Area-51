# Microsoft Developer Studio Project File - Name="*CurveCalc*" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=*CurveCalc* - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CurveCalc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CurveCalc.mak" CFG="*CurveCalc* - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "*CurveCalc* - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "*CurveCalc* - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "CurveCalc"
# PROP Scc_LocalPath "..\..\.."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "*CurveCalc* - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(X)" /I "$(X)/x_Files" /I "$(X)/Entropy" /I "$(X)/MeshUtil" /I "$(X)\..\Support" /I "$(X)\Auxiliary" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "*CurveCalc* - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(X)\Parsing" /I "$(X)" /I "$(X)/x_Files" /I "$(X)/Entropy" /I "$(X)/MeshUtil" /I "$(X)\..\Support" /I "$(X)\Auxiliary" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "*CurveCalc* - Win32 Release"
# Name "*CurveCalc* - Win32 Debug"
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Group "RscManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Support\CollisionMgr\CollisionMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\CollisionMgr\CollisionMgr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\CollisionMgr\CollisionPrimatives.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\CollisionMgr\CollisionPrimatives.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Effects\fx_Mgr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Effects\fx_Mgr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Effects\fx_Mgr_private.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\ResourceMgr\inline_ResourceMgr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\ManagerRegistration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\ManagerRegistration.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Obj_mgr\Obj_Mgr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Obj_mgr\obj_mgr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Objects\object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Objects\object.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Periodical\Periodical.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Periodical\Periodical.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Periodical\Periodical_example.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Periodical\Periodical_mgr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Periodical\Periodical_mgr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\ResourceMgr\ResourceMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\ResourceMgr\ResourceMgr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\MiscUtils\SimpleUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\MiscUtils\SimpleUtils.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\SpatialDBase\Spatial_user.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\SpatialDBase\SpatialDBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\SpatialDBase\SpatialDBase.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\SpatialDBase\SpatialDBase_inline.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\GameLib\StatsMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\GameLib\StatsMgr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\ZoneMgr\ZoneMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\ZoneMgr\ZoneMgr.hpp
# End Source File
# End Group
# Begin Group "xCore"

# PROP Default_Filter ""
# Begin Group "Auxillary"

# PROP Default_Filter ""
# Begin Group "MiscUtils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\bitstream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\bitstream.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\fileio.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\Guid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\Guid.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\mem_stream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\mem_stream.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\Property.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\Property.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\PropertyEnum.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\RTTI.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\xCore\Auxiliary\MiscUtils\slist.hpp
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Navigation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Support\Characters\AStar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Characters\AStar.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Characters\AStarNode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\Characters\AStarNode.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\navigation\ConnectionZoneMgr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\navigation\ConnectionZoneMgr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\navigation\nav_map.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\navigation\Nav_Map.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\navigation\ng_connection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\navigation\ng_connection.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\navigation\ng_node.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Support\navigation\ng_node.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CurveCalcStructs.hpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Group
# End Target
# End Project
