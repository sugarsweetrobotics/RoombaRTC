// -*-C++-*-
/*!
 * @file  RoombaSVC_impl.cpp
 * @brief Service implementation code of Roomba.idl
 *
 * @author ysuga (ysuga@ysuga.net)
 * URL: http://www.ysuga.net/robot/
 *
 * LGPL
 *
 */

#include "RoombaSVC_impl.h"

/*
 * Example implementational code for IDL interface ssr::RoombaCommand
 */
RoombaCommandSVC_impl::RoombaCommandSVC_impl()
{
  // Please add extra constructor code here.

}


RoombaCommandSVC_impl::~RoombaCommandSVC_impl()
{
  // Please add extra destructor code here.
}


/*
 * Methods corresponding to IDL attributes and operations
 */
void RoombaCommandSVC_impl::safeControl()
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  //#warning "Code missing in function <void RoombaCommandSVC_impl::safeControl()>"
  m_pRoomba->safeControl();
#endif
}

void RoombaCommandSVC_impl::fullControl()
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  //#warning "Code missing in function <void RoombaCommandSVC_impl::fullControl()>"
  m_pRoomba->fullControl();
#endif
}

void RoombaCommandSVC_impl::clean()
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  //  #warning "Code missing in function <void RoombaCommandSVC_impl::clean()>"
  m_pRoomba->clean();
#endif
}

void RoombaCommandSVC_impl::spotClean()
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  //#warning "Code missing in function <void RoombaCommandSVC_impl::spotClean()>"
  m_pRoomba->spotClean();
#endif
}

void RoombaCommandSVC_impl::maxClean()
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  //#warning "Code missing in function <void RoombaCommandSVC_impl::maxClean()>"
  m_pRoomba->maxClean();
#endif
}

void RoombaCommandSVC_impl::dock()
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  //#warning "Code missing in function <void RoombaCommandSVC_impl::dock()>"
  m_pRoomba->dock();
#endif
}

void RoombaCommandSVC_impl::mainBrush(CORBA::Boolean on_off)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  //#warning "Code missing in function <void RoombaCommandSVC_impl::mainBrush(CORBA::Boolean on_off)>"
  m_pRoomba->driveMainBrush((Motors)on_off);
#endif
}

void RoombaCommandSVC_impl::sideBrush(CORBA::Boolean on_off, CORBA::Boolean ccw)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  //#warning "Code missing in function <void RoombaCommandSVC_impl::sideBrush(CORBA::Boolean on_off, CORBA::Boolean ccw)>"
  //Motors flag = 0;
  m_pRoomba->driveSideBrush((Motors)on_off);//, ccw ? MOTOR_CCW : MOTOR_CW);
#endif
}

void RoombaCommandSVC_impl::vacuum(CORBA::Boolean on_off)
{
  // Please insert your code here and remove the following warning pragma
#ifndef WIN32
  //#warning "Code missing in function <void RoombaCommandSVC_impl::vacuum(CORBA::Boolean on_off)>"
  m_pRoomba->driveVacuum((Motors)on_off);
#endif
}



// End of example implementational code



