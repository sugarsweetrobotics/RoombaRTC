// -*-C++-*-
/*!
 * @file  RoombaSVC_impl.h
 * @brief Service implementation header of Roomba.idl
 *
 * @author ysuga (ysuga@ysuga.net)
 * URL: http://www.ysuga.net/robot/
 *
 * LGPL
 *
 */

#include "RoombaSkel.h"

#ifndef ROOMBASVC_IMPL_H
#define ROOMBASVC_IMPL_H

#include "Roomba.h"
 
/*!
 * @class RoombaCommandSVC_impl
 * Example class implementing IDL interface ssr::RoombaCommand
 */
class RoombaCommandSVC_impl
 : public virtual POA_ssr::RoombaCommand,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~RoombaCommandSVC_impl();

  ssr::Roomba* m_pRoomba;
 public:
  /*!
   * @brief standard constructor
   */
  RoombaCommandSVC_impl();

  void setRoomba(ssr::Roomba* pRoomba) {
    m_pRoomba = pRoomba;
  }
  /*!
   * @brief destructor
   */
   virtual ~RoombaCommandSVC_impl();

   // attributes and operations
   void safeControl();
   void fullControl();
   void clean();
   void spotClean();
   void maxClean();
   void dock();
   void mainBrush(CORBA::Boolean on_off);
   void sideBrush(CORBA::Boolean on_off, CORBA::Boolean ccw);
   void vacuum(CORBA::Boolean on_off);

};



#endif // ROOMBASVC_IMPL_H


