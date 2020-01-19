// -*- C++ -*-
/*!
 * @file  TargetManager.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "TargetManager.h"
#include "TargetInfo.h"
#include "math.h"


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
  m_tidyUpManagerPort.registerConsumer("targetPose", "RTC::TidyUpManager", m_tidyUpManager);
  
  // Set CORBA Service Ports
  addPort(m_tidyUpManagerPort);
  
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
	if (m_currentPoseIn.isNew) {
		m_currentPoseIn.read();
	}
	if (m_pointIn.isNew()) {
		m_pointIn.read();
		std::string data = m_point.data;
		std::cout << "[RTC:TargetManager] Receiven Command (" << data << ")" << std::endl;
		std::stringstream ss{ data };

		std::vector<TargetInfo> get_poses, return_poses;
		std::string string_pose, string_pose2;

		// split()
		while (std::getline(ss, string_pose, ',')) {
			std::vector<double> d;
			std::stringstream ss2{ string_pose };
			int count = 0;
			while (std::getline(ss2, string_pose2, ' ')) {
				float d_in = std::stod(string_pose2);
				if ((count == 0) || (count == 1)) {
					get_poses.pose.push_back(d_in);
				}
				else if (count == 2) {
					get_poses.kind = string_pose2;
				}
				else {
					std::cout << "unknown string:" << data << std::endl;
					return RTC::RTC_ERROR;
				}
				count++;
			}
		}

		// 与えられた座標がすでにあるものかどうかの判定
		if (poses.empty()) {
			poses = get_poses;
		}
		else {
			for (TargetInfo g_p : get_poses) {
				for (auto p : poses) {
					if ((p.kind == g_p.kind) && (p.pose[0] + threshould > g_p.pose[0]) && (p.pose[0] - threshould > g_p.pose[0]) && 
												(p.pose[1] + threshould > g_p.pose[1]) && (p.pose[1] - threshould > g_p.pose[1])) {
						continue;
					}
				}
				return_poses.push_back(g_p);
			}
			poses = return_poses;
		}

		if (poses.size() > 0) {
			double distance;
			distance = pow(m_currentPose.data.position.x - poses[0].pose[0], 2) + pow(m_currentPose.data.position.y - poses[0].pose[1], 2);
			distance = pow(distance, 1 / 2);
			int nearest_idx = 0;
			for (int i = 1; i++; i < poses.size()) {
				double d = pow(m_currentPose.data.position.x - poses[i].pose[0], 2) + pow(m_currentPose.data.position.y - poses[i].pose[1], 2);
				if (d < distance) {
					distance = d;
					nearest_idx = i;
				}
			}
			TargetInfo return_pose = poses[nearest_idx];
			RTC::RETURN_VALUE retval = m_tidyUpManager->tidyup(return_pose);

			if (retval = RTC::RETURN_VALUE::RETVAL_OK) {
				poses.erase(poses.begin() + nearest_idx);
				std::cout << "tidy up success!" << std::endl;
			}
			else {
				std::cout << "error is occured:" << retval << std::endl;
			}
		}
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


