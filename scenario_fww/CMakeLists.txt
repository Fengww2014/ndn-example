cmake_minimum_required(VERSION 3.12)
project(scenario_fww)

set(CMAKE_CXX_STANDARD 14)

include_directories(extensions)

add_executable(scenario_fww
        extensions/custom-app.cpp
        extensions/custom-app.hpp
        extensions/hijacker.cpp
        extensions/hijacker.hpp
        extensions/ndn-app.hpp
        extensions/ndn-consumer-cbr.cpp
        extensions/ndn-consumer-cbr.hpp
        extensions/ndn-consumer.hpp
        extensions/ndn-producer-fww.cpp
        extensions/ndn-producer-fww.hpp
        scenarios/custom-apps.cpp
        scenarios/ndn-simple-custom.cpp
        scenarios/ndn-simple-with-pcap.cpp
        scenarios/ndn-simple.cpp
        scenarios/ndn-v2v-simple.cpp)
