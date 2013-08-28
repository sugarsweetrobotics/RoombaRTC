set(hdrs RoombaRTC.h
    PARENT_SCOPE
    RoombaSVC_impl.h
    ${PROJECT_SOURCE_DIR}/libRoomba/include/libroomba.h
    ${PROJECT_SOURCE_DIR}/libaqua/include/Thread.h
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

