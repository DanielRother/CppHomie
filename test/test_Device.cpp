#include <gtest/gtest.h>
#include "Device.h"

namespace Rovi {
    namespace Homie {
        const auto deviceName = std::string{"Super car"};
        const auto deviceMAC = std::string{"DE:AD:BE:EF:FE:ED"};
        const auto deviceIP = std::string{"192.168.0.10"};
        const auto implementation = std::string{"esp32"};
        const auto firmwareName = std::string{"weatherstation-firmware"};
        const auto firmwareVersion = std::make_shared<Version>(1, 0, 0);
        const auto statsInterval_s = std::chrono::seconds{60};
        const auto hwInfo = std::make_shared<HWInfo>(deviceMAC, deviceIP, implementation);

        auto device = std::make_shared<Device>(deviceName, hwInfo, firmwareName, firmwareVersion, statsInterval_s);
        const auto baseMqttPath = std::string{"homie/super-car-deadbeeffeed/"};

        TEST(Device, attributes) {         
            {
                auto attribute = device->attribute(Device::Attributes::deviceID);
                EXPECT_TRUE(attribute.second == std::string{"super-car-deadbeeffeed"});
            } 
            {
                auto attribute = device->attribute(Device::Attributes::homie);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$homie/"});
                EXPECT_TRUE(attribute.second == std::string{"3.0.1"});
            } 
            {
                auto attribute = device->attribute(Device::Attributes::name);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$name/"});
                EXPECT_TRUE(attribute.second == deviceName);
            } 
            {
                // TODO 
                auto attribute = device->attribute(Device::Attributes::state);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$state/"});
                EXPECT_TRUE(attribute.second == std::string{"init"});
            } 
            {
                auto attribute = device->attribute(Device::Attributes::localip);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$localip/"});
                EXPECT_TRUE(attribute.second == deviceIP);
            } 
            {
                auto attribute = device->attribute(Device::Attributes::mac);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$mac/"});
                EXPECT_TRUE(attribute.second == deviceMAC);
            } 
            {
                auto attribute = device->attribute(Device::Attributes::firmwareName);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$fw/name/"});
                EXPECT_TRUE(attribute.second == firmwareName);
            } 
            {
                auto attribute = device->attribute(Device::Attributes::firmwareVersion);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$fw/version/"});
                EXPECT_TRUE(attribute.second == std::string{"1.0.0"});
            } 
            {
                auto attribute = device->attribute(Device::Attributes::nodes);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$nodes/"});
                EXPECT_TRUE(attribute.second == std::string{""});
            } 
            {
                auto attribute = device->attribute(Device::Attributes::implementation);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$implementation/"});
                EXPECT_TRUE(attribute.second == implementation);
            } 
            {
                auto attribute = device->attribute(Device::Attributes::stats);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$stats/"});
                std::cout << "second: " << attribute.second << std::endl;
                EXPECT_TRUE(attribute.second == std::string{"uptime,signal,cputemp,cpuload,battery,freeheap,supply"});
            } 
            {
                auto attribute = device->attribute(Device::Attributes::statsInterval_s);
                EXPECT_TRUE(mqttPathToString(attribute.first) == baseMqttPath + std::string{"$stats/interval/"});
                EXPECT_TRUE(attribute.second == std::string{"60"});
            } 
        }

        TEST(Device, connectionInitialized) {
            auto mqttRawData = device->connectionInitialized();
            // printMqttMessages(mqttRawData);

            // TODO: Add testcase
            EXPECT_TRUE(false);
        }

        TEST(Device, stateChanges) {
            auto intervall = std::chrono::seconds{60};
            // TODO: Imlement
            EXPECT_TRUE(false);
        }

        TEST(Device, statistic) {
            {
                auto stat = device->statictic(Stats::uptime);
                EXPECT_TRUE(mqttPathToString(stat.first) == baseMqttPath + std::string{"$stats/uptime/"});
                EXPECT_TRUE(atoll(stat.second.c_str()) >= 0);
            }  
            {
                auto stat = device->statictic(Stats::signal);
                EXPECT_TRUE(mqttPathToString(stat.first) == baseMqttPath + std::string{"$stats/signal/"});
                EXPECT_TRUE(stat.second == "100");
            }  
            {
                auto stat = device->statictic(Stats::cputemp);
                EXPECT_TRUE(mqttPathToString(stat.first) == baseMqttPath + std::string{"$stats/cputemp/"});
                EXPECT_TRUE(stat.second == "50");
            }  
            {
                auto stat = device->statictic(Stats::cpuload);
                EXPECT_TRUE(mqttPathToString(stat.first) == baseMqttPath + std::string{"$stats/cpuload/"});
                EXPECT_TRUE(stat.second == "0");
            }  
            {
                auto stat = device->statictic(Stats::battery);
                EXPECT_TRUE(mqttPathToString(stat.first) == baseMqttPath + std::string{"$stats/battery/"});
                EXPECT_TRUE(stat.second == "100");
            }  
            {
                auto stat = device->statictic(Stats::freeheap);
                EXPECT_TRUE(mqttPathToString(stat.first) == baseMqttPath + std::string{"$stats/freeheap/"});
                EXPECT_TRUE(stat.second == "5242880");
            }  
            {
                auto stat = device->statictic(Stats::supply);
                EXPECT_TRUE(mqttPathToString(stat.first) == baseMqttPath + std::string{"$stats/supply/"});
                EXPECT_TRUE(stat.second == "3.3");
            }  
        }

        TEST(Device, update) {
            // sleep(2);
            auto mqttRawData = device->update();
            // printMqttMessages(mqttRawData);

            EXPECT_TRUE(false);
        }
    }
}