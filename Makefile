#############################################################################
# Makefile for building: LibraryDesign
# Generated by qmake (3.1) (Qt 5.9.3)
# Project:  LibraryDesign.pro
# Template: app
# Command: C:\qt\Qt5.9.3\5.9.3\mingw53_32\bin\qmake.exe -o Makefile LibraryDesign.pro -spec win32-g++
#############################################################################

MAKEFILE      = Makefile

first: release
install: release-install
uninstall: release-uninstall
QMAKE         = C:\qt\Qt5.9.3\5.9.3\mingw53_32\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = copy /y
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = copy /y
INSTALL_PROGRAM = copy /y
INSTALL_DIR   = xcopy /s /q /y /i
QINSTALL      = C:\qt\Qt5.9.3\5.9.3\mingw53_32\bin\qmake.exe -install qinstall
QINSTALL_PROGRAM = C:\qt\Qt5.9.3\5.9.3\mingw53_32\bin\qmake.exe -install qinstall -exe
DEL_FILE      = del
SYMLINK       = $(QMAKE) -install ln -f -s
DEL_DIR       = rmdir
MOVE          = move
SUBTARGETS    =  \
		release \
		debug


release: FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-all: FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall
debug: FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_first: FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-all: FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall

Makefile: LibraryDesign.pro ../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/win32-g++/qmake.conf ../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/spec_pre.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/qdevice.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/device_config.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/common/g++-base.conf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/common/angle.conf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/common/sanitize.conf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/common/gcc-base.conf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/qconfig.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3danimation.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3danimation_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dcore.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dcore_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dextras.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dextras_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dinput.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dinput_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dlogic.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dlogic_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquick.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquick_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickanimation.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickanimation_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickextras.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickextras_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickinput.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickinput_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickrender.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickrender_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickscene2d.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickscene2d_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3drender.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3drender_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axbase.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axbase_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axcontainer.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axcontainer_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axserver.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axserver_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_bluetooth.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_bluetooth_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_bootstrap_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_concurrent.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_concurrent_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_core.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_core_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_datavisualization.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_datavisualization_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_dbus.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_dbus_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_designer.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_designer_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_designercomponents_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_egl_support_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_fb_support_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_gamepad.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_gamepad_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_gui.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_gui_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_help.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_help_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_location.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_location_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_multimedia.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_multimedia_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_multimediawidgets.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_network.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_network_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_nfc.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_nfc_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_opengl.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_opengl_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_openglextensions.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_openglextensions_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_packetprotocol_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_positioning.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_positioning_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_printsupport.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_printsupport_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qml.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qml_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qmldebug_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qmltest.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qmltest_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quick.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quick_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quickcontrols2.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quickcontrols2_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quickparticles_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quicktemplates2_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quickwidgets.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_script.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_script_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_scripttools.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_scripttools_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_scxml.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_scxml_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_sensors.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_sensors_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_serialbus.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_serialbus_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_serialport.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_serialport_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_sql.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_sql_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_svg.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_svg_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_testlib.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_testlib_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_texttospeech.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_texttospeech_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_theme_support_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_uiplugin.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_uitools.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_uitools_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_webchannel.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_webchannel_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_websockets.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_websockets_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_widgets.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_widgets_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_winextras.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_winextras_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_xml.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_xml_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_xmlpatterns.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/qt_functions.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/qt_config.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/win32-g++/qmake.conf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/spec_post.prf \
		.qmake.stash \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/exclusive_builds.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/toolchain.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/default_pre.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/win32/default_pre.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/resolve_config.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/exclusive_builds_post.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/default_post.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/precompile_header.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/warn_on.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/qt.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/resources.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/moc.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/win32/opengl.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/uic.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/qmake_use.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/file_copies.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/win32/windows.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/testcase_targets.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/exceptions.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/yacc.prf \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/lex.prf \
		LibraryDesign.pro \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/lib/qtmain.prl \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/lib/Qt5Widgets.prl \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/lib/Qt5Gui.prl \
		../../../qt/Qt5.9.3/5.9.3/mingw53_32/lib/Qt5Core.prl
	$(QMAKE) -o Makefile LibraryDesign.pro -spec win32-g++
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/spec_pre.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/qdevice.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/device_config.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/common/g++-base.conf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/common/angle.conf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/common/sanitize.conf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/common/gcc-base.conf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/qconfig.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3danimation.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3danimation_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dcore.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dcore_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dextras.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dextras_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dinput.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dinput_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dlogic.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dlogic_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquick.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquick_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickanimation.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickanimation_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickextras.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickextras_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickinput.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickinput_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickrender.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickrender_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickscene2d.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3dquickscene2d_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3drender.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_3drender_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_accessibility_support_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axbase.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axbase_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axcontainer.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axcontainer_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axserver.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_axserver_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_bluetooth.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_bluetooth_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_bootstrap_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_concurrent.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_concurrent_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_core.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_core_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_datavisualization.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_datavisualization_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_dbus.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_dbus_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_designer.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_designer_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_designercomponents_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_egl_support_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_fb_support_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_gamepad.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_gamepad_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_gui.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_gui_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_help.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_help_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_location.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_location_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_multimedia.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_multimedia_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_multimediawidgets.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_multimediawidgets_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_network.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_network_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_nfc.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_nfc_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_opengl.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_opengl_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_openglextensions.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_openglextensions_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_packetprotocol_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_positioning.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_positioning_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_printsupport.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_printsupport_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qml.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qml_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qmldebug_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qmldevtools_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qmltest.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qmltest_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quick.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quick_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quickcontrols2.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quickcontrols2_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quickparticles_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quicktemplates2_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quickwidgets.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_quickwidgets_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_script.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_script_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_scripttools.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_scripttools_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_scxml.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_scxml_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_sensors.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_sensors_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_serialbus.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_serialbus_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_serialport.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_serialport_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_sql.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_sql_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_svg.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_svg_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_testlib.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_testlib_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_texttospeech.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_texttospeech_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_theme_support_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_uiplugin.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_uitools.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_uitools_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_webchannel.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_webchannel_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_websockets.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_websockets_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_widgets.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_widgets_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_winextras.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_winextras_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_xml.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_xml_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_xmlpatterns.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/qt_functions.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/qt_config.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/win32-g++/qmake.conf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/spec_post.prf:
.qmake.stash:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/exclusive_builds.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/toolchain.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/default_pre.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/win32/default_pre.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/resolve_config.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/exclusive_builds_post.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/default_post.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/precompile_header.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/warn_on.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/qt.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/resources.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/moc.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/win32/opengl.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/uic.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/qmake_use.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/file_copies.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/win32/windows.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/testcase_targets.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/exceptions.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/yacc.prf:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/mkspecs/features/lex.prf:
LibraryDesign.pro:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/lib/qtmain.prl:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/lib/Qt5Widgets.prl:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/lib/Qt5Gui.prl:
../../../qt/Qt5.9.3/5.9.3/mingw53_32/lib/Qt5Core.prl:
qmake: FORCE
	@$(QMAKE) -o Makefile LibraryDesign.pro -spec win32-g++

qmake_all: FORCE

make_first: release-make_first debug-make_first  FORCE
all: release-all debug-all  FORCE
clean: release-clean debug-clean  FORCE
distclean: release-distclean debug-distclean  FORCE
	-$(DEL_FILE) Makefile
	-$(DEL_FILE) .qmake.stash

release-mocclean:
	$(MAKE) -f $(MAKEFILE).Release mocclean
debug-mocclean:
	$(MAKE) -f $(MAKEFILE).Debug mocclean
mocclean: release-mocclean debug-mocclean

release-mocables:
	$(MAKE) -f $(MAKEFILE).Release mocables
debug-mocables:
	$(MAKE) -f $(MAKEFILE).Debug mocables
mocables: release-mocables debug-mocables

check: first

benchmark: first
FORCE:

$(MAKEFILE).Release: Makefile
$(MAKEFILE).Debug: Makefile