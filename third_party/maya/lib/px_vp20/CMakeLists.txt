set(PXR_PACKAGE px_vp20)

pxr_shared_library(${PXR_PACKAGE}
    LIBRARIES
        gf
        ${MAYA_OpenMaya_LIBRARY}
        ${MAYA_OpenMayaUI_LIBRARY}
        ${MAYA_OpenMayaRender_LIBRARY}
        ${OPENGL_gl_LIBRARY}

    INCLUDE_DIRS
        ${OPENGL_INCLUDE_DIRS}
        ${MAYA_INCLUDE_DIRS}

    PUBLIC_HEADERS
        api.h
        
    PUBLIC_CLASSES
        utils
        utils_legacy
)

