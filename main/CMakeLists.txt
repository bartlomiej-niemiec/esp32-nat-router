cmake_minimum_required(VERSION 3.16)

idf_component_register(SRCS "main.cpp"
                       REQUIRES wifi_nat_router_app
                       )