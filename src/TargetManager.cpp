// -*- C++ -*-
/*!
 * @file  TargetManager.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "TargetManager.h"

// Module specification
// <rtc-template block="module_spec">
static const char* targetmanager_spec[] =
  {
    "implementation_id", "TargetManager",
    "type_name",         "TargetManager",
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
TargetManager::TargetManager(RTC::Manager* manager)
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
TargetManager::~TargetManager()
{
}



RTC::ReturnCode_t TargetManager::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("point", m_pointIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_targetPosePort.registerConsumer("targetPose", "RTC::TidyUpManager", m_targetPose);
  
  // Set CORBA Service Ports
  addPort(m_targetPosePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t TargetManager::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManager::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManager::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManager::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManager::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t TargetManager::onExecute(RTC::UniqueId ec_id)
{
	if (m_pointIn.isNew()) {
		m_pointIn.read();
		std::string data = m_point.data;
		std::cout << "[RTC:TargetManager] Receiven Command (" << data << ")" << std::endl;
		std::stringstream ss{ data };

		std::vector<std::vector<float>> get_poses;
		std::string string_pose, string_pose2;

		// split()
		while (std::getline(ss, string_pose, ',')) {
			std::vector<float> d;
			std::stringstream ss2{ string_pose };
			while (std::getline(ss2, string_pose2, ' ')) {
				float d_in = std::stod(string_pose2);
				d.push_back(d_in);
			}
			get_poses.push_back(d);
		}

		// 与えられた座標がすでにあるものかどうかの判定
	}

	// posesがひとつ以上あればTidyUpManagerへ


  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t TargetManager::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManager::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManager::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManager::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t TargetManager::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void TargetManagerInit(RTC::Manager* manager)
  {
    coil::Properties profile(targetmanager_spec);
    manager->registerFactory(profile,
                             RTC::Create<TargetManager>,
                             RTC::Delete<TargetManager>);
  }
  
};


