##---------------------------------------------------------------------------
## Author:      Dave Register
##***************************************************************************
## *   Copyright (C) 2010 by David S. Register                               *
## *   This program is free software; you can redistribute it and/or modify  *
## *   it under the terms of the GNU General Public License as published by  *
## *   the Free Software Foundation; either version 2 of the License, or     *
## *   (at your option) any later version.                                   *
## *                                                                         *
## *   This program is distributed in the hope that it will be useful,       *
## *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
## *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
## *   GNU General Public License for more details.                          *
## *                                                                         *
## *   You should have received a copy of the GNU General Public License     *
## *   along with this program; if not, write to the                         *
## *   Free Software Foundation, Inc.,                                       *
## *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.             *
## ***************************************************************************

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(onavsim_pi)

SET(PACKAGE_NAME onavsim_pi)
SET(VERBOSE_NAME onavsim)
SET(TITLE_NAME onavsim)
SET(CPACK_PACKAGE_CONTACT "Mike Rossiter")

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "4")

SET(NAME_SUFFIX "ov50")

set (CMAKE_CXX_STANDARD 11)

#SET(CMAKE_BUILD_TYPE Debug)
OPTION(onavsim_USE_SVG "Use SVG graphics" ON)

INCLUDE("cmake/PluginConfigure.cmake")

IF(onavsim_USE_SVG)
  ADD_DEFINITIONS(-Donavsim_USE_SVG)
ENDIF(onavsim_USE_SVG)

SET(SRC_onavsim
        src/AisMaker.cpp
        src/AisMaker.h
        src/bbox.cpp
        src/bbox.h
        src/onavsim_pi.h
        src/onavsim_pi.cpp
        src/onavsimOverlayFactory.cpp
        src/onavsimOverlayFactory.h
        src/onavsimUIDialogBase.cpp
        src/onavsimUIDialogBase.h
        src/onavsimUIDialog.cpp
        src/onavsimUIDialog.h
        src/icons.h
        src/icons.cpp
        src/tcmgr.cpp
        src/timectrl.cpp
        src/timectrl.h
        src/tcmgr.h
        src/tinystr.h
	src/tinyxml.h
    )


ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_onavsim})

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
