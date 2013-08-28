// -*- C++ -*-
/*!
 * @file  RoombaRTC.cpp
 * @brief Roomba RTC
 * @date $Date$
 *
 * @author ysuga (ysuga@ysuga.net)
 * URL: http://sugarsweetrobotics.com
 *
 * LGPL
 *
 * $Id$
 */

#include "RoombaRTC.h"

#include "libroomba.h"
// Module specification
// <rtc-template block="module_spec">
static const char* roombartc_spec[] =
  {
    "implementation_id", "RoombaRTC",
    "type_name",         "RoombaRTC",
    "description",       "Roomba RTC",
    "version",           "1.0.0",
    "vendor",            "Sugar Sweet Robotics",
    "category",          "Experimental",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.model", "500series",
    "conf.default.serial_port", "COM1",
    "conf.default.baudrate", "115200",
    // Widget
    "conf.__widget__.model", "text",
    "conf.__widget__.serial_port", "text",
    "conf.__widget__.baudrate", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RoombaRTC::RoombaRTC(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_targetVelIn("targetVel", m_targetVel),
    m_updatePosIn("updatePos", m_updatePos),
    m_serviceNameIn("serviceName", m_serviceName),
    m_currentVelOut("currentVel", m_currentVel),
    m_currentPosOut("currentPos", m_currentPos),
    m_bumpersOut("bumpers", m_bumpers),
    m_infraRedsOut("infraReds", m_infraReds),
    m_roombaServicePort("roombaService")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RoombaRTC::~RoombaRTC()
{
}



RTC::ReturnCode_t RoombaRTC::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("targetVel", m_targetVelIn);
  addInPort("updatePos", m_updatePosIn);
  addInPort("serviceName", m_serviceNameIn);
  
  // Set OutPort buffer
  addOutPort("currentVel", m_currentVelOut);
  addOutPort("currentPos", m_currentPosOut);
  addOutPort("bumpers", m_bumpersOut);
  addOutPort("infraReds", m_infraRedsOut);
  
  // Set service provider to Ports
  m_roombaServicePort.registerProvider("RoombaCommand", "ssr::RoombaCommand", m_roombaCommand);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_roombaServicePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("model", m_model, "500series");
  bindParameter("serial_port", m_serial_port, "COM1");
  bindParameter("baudrate", m_baudrate, "115200");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RoombaRTC::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RoombaRTC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RoombaRTC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RoombaRTC::onActivated(RTC::UniqueId ec_id)
{
  try {
    Model  model = ::MODEL_CREATE;
    if(m_model == "500series") {
      model = ::MODEL_500SERIES;
    }
    //    m_pRoomba = //new ssr::Roomba(model, m_serial_port.c_str(), m_baudrate);
    m_pRoomba = ssr::createRoomba(model, m_serial_port.c_str(), m_baudrate);
  } catch (std::exception &e) {
    std::cerr << "Exception in creating Roomba: " << e.what() << std::endl;
    return RTC::RTC_ERROR;
  }
  m_pRoomba->safeControl();
  m_pRoomba->runAsync();

  m_roombaCommand.setRoomba(m_pRoomba);

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RoombaRTC::onDeactivated(RTC::UniqueId ec_id)
{
  delete m_pRoomba;
  m_pRoomba = NULL;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RoombaRTC::onExecute(RTC::UniqueId ec_id)
{
  if(m_targetVelIn.isNew()) {
    m_targetVelIn.read();
    m_pRoomba->setMode(::MODE_FULL);
    m_pRoomba->setTargetVelocity(m_targetVel.data.vx, m_targetVel.data.va);
  }

  //  double x, y, th;
  ssr::Pose pose = m_pRoomba->getCurrentPose();
  //m_pRoomba->getCurrentPosition(&x, &y, &th);
  m_currentPos.data.position.x = pose.x;
  m_currentPos.data.position.y = pose.y;
  m_currentPos.data.heading = pose.th;
  m_currentPosOut.write();

  //double vx, va;
  //m_pRoomba->getCurrentVelocity(&vx, &va);
  ssr::Velocity vel = m_pRoomba->getCurrentVelocity();
  m_currentVel.data.vx = vel.x;
  m_currentVel.data.vy = 0;
  m_currentVel.data.va = vel.th;
  m_currentVelOut.write();

  if(m_serviceNameIn.isNew()) {
    m_serviceNameIn.read();
    std::string service = std::string( (char*)m_serviceName.data );
    if(service == "clean") {
      //      m_pRoomba->setMode(Roomba::MODE_START);
      m_pRoomba->setMode(::MODE_NORMAL_CLEAN);
    } else if(service == "dock") {
      //      m_pRoomba->setMode(Roomba::MODE_START);
      m_pRoomba->setMode(::MODE_DOCK);
    } else if(service == "spot") {
      //      m_pRoomba->setMode(Roomba::MODE_START);
      m_pRoomba->setMode(::MODE_SPOT_CLEAN);
    } else if(service == "max") {
      //      m_pRoomba->setMode(Roomba::MODE_START;)
      m_pRoomba->setMode(::MODE_MAX_TIME_CLEAN);
    } else if(service == "sleep") {
      //      m_pRoomba->setMode(Roomba::MODE_START);
      m_pRoomba->setMode(::MODE_SLEEP);
    } 
  }
  

  return RTC::RTC_OK;
}


RTC::ReturnCode_t RoombaRTC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RoombaRTC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RoombaRTC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RoombaRTC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RoombaRTC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RoombaRTCInit(RTC::Manager* manager)
  {
    coil::Properties profile(roombartc_spec);
    manager->registerFactory(profile,
                             RTC::Create<RoombaRTC>,
                             RTC::Delete<RoombaRTC>);
  }
  
};


