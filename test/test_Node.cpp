#include <gtest/gtest.h>
#include "Node.h"

namespace Rovi {
    namespace Homie {
        // TODO: Move 'device2' to common test fixture
        const auto device2Name = std::string{"Super car"};
        const auto device2MAC = std::string{"DE:AD:BE:EF:FE:ED"};
        const auto device2IP = std::string{"192.168.0.10"};
        const auto implementation = std::string{"esp32"};
        const auto firmwareName = std::string{"weatherstation-firmware"};
        const auto firmwareVersion = std::make_shared<Version>(1, 0, 0);
        const auto statsInterval_s = std::chrono::seconds{60};
        const auto hwInfo = std::make_shared<HWInfo>(device2MAC, device2IP, implementation);

        auto device2 = std::make_shared<Device>(device2Name, hwInfo, firmwareName, firmwareVersion, statsInterval_s);


        const auto nodeName = std::string{"Car engine"};
        const auto type = std::string{"V8"};

        const auto node = std::make_shared<Node>(nodeName, type);
        const auto nodeArray = std::make_shared<Node>(nodeName, type, 3);
        
        // TODOs:
        // - Node-Pfade
        // - Device <-> Node Verbindung testet
        // - Device-Update inkl. Nodes; Node-Update???
        // - Device.attribute(node) (inkl. arrays)

        TEST(Node, attributes) {   
            device2->addNode(node);

            auto device2Node = device2->node(node->value(Node::Attributes::nodeID));

            auto mqttRawData = device2->connectionInitialized();
            printMqttMessages(mqttRawData);
      
            {
                auto attribute = device2Node->attribute(Node::Attributes::nodeID);
                EXPECT_TRUE(attribute.second == std::string{"car-engine"});              
            }
            {
                auto attribute = device2Node->attribute(Node::Attributes::name);
                EXPECT_TRUE(attribute.second == std::string{"Car engine"});              
            }
            {
                auto attribute = device2Node->attribute(Node::Attributes::type);
                EXPECT_TRUE(attribute.second == std::string{"V8"});              
            }
            {
                // TODO
                auto attribute = device2Node->attribute(Node::Attributes::properties);
                EXPECT_TRUE(attribute.second == std::string{"Not implemented yet!"});              
            }
            {
                auto attribute = device2Node->attribute(Node::Attributes::array);
                EXPECT_TRUE(attribute.second == std::string{"0"});              
            }
            {
                EXPECT_TRUE(nodeArray->isArray());
                auto attribute = nodeArray->attribute(Node::Attributes::array);
                EXPECT_TRUE(attribute.second == std::string{"0-2"});              
            }


        }
    }
}