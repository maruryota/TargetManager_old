// -*- C++ -*-
/*!
 * @file  TargetManagerTest.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "TargetManagerTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* targetmanager_spec[] =
  {
    "implementation_id", "TargetManagerTest",
    "type_name",         "TargetManagerTest",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "maruryota",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
TargetManagerTest::TargetManagerTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_pointIn("point", m_point),
    m_targetPosePort("targetPose")

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
TargetManagerTest::~TargetManagerTest()
{
}



RTC::ReturnCode_t TargetManagerTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("point", m_pointOut);
  
  // Set service provider to Ports
  m_targetPosePort.registerProvider("targetPose", "RTC::TidyUpManager", m_targetPose);
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  addPort(m_targetPosePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t TargetManagerTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManagerTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManagerTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManagerTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManagerTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManagerTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManagerTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManagerTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManagerTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManagerTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManagerTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void TargetManagerTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(targetmanager_spec);
    manager->registerFactory(profile,
                             RTC::Create<TargetManagerTest>,
                             RTC::Delete<TargetManagerTest>);
  }
  
};


