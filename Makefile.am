AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = libcgmath-@CGMATH_API_VERSION@.la
libcgmath_@CGMATH_API_VERSION@_la_SOURCES = \
	src/EulerAngle.cpp src/Matrix.cpp src/Quaternion.cpp src/Utl.cpp \
	src/Vector4.cpp src/Vector3.cpp src/Vector2.cpp

libcgmath_@CGMATH_API_VERSION@_la_LDFLAGS = -version-info $(CGMATH_SO_VERSION)

cgmath_includedir = $(includedir)/cgmath-$(CGMATH_API_VERSION)
cgmath_include_HEADERS = \
	include/CGM/Def.hpp include/CGM/EulerAngle.hpp include/CGM/Matrix.hpp \
	include/CGM/Quaternion.hpp include/CGM/Utl.hpp include/CGM/Vector2.hpp \
	include/CGM/Vector3.hpp include/CGM/Vector4.hpp

AM_CPPFLAGS = -I$(srcdir)/include/CGM

cgmath_libincludedir = $(libdir)/cgmath-$(CGMATH_API_VERSION)

pkgconfigdir = $(libdir)/pkgconfig
#pkgconfig_DATA = cgmath-$(CGMATH_API_VERSION).pc

dist_noinst_SCRIPT = autogen.sh
