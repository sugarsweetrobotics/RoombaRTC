set(hdrs RoombaRTC.h
    PARENT_SCOPE
    RoombaSVC_impl.h
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

