cmake_minimum_required(VERSION 3.16)

idf_component_register(
        INCLUDE_DIRS "./include"
        SRCS "./src/wifi_nat_router_config.cpp"
)