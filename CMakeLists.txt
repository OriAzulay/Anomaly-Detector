cmake_minimum_required(VERSION 3.0.0)
project(anomaly_detection_lib.cpp VERSION 0.1.0)

include(CTest)
enable_testing()
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(anomaly_detection_util.cpp MainTrain.cpp anomaly_detection_util.cpp SimpleAnomalyDetector.cpp timeseries.cpp )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
