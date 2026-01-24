cmake_minimum_required(VERSION 3.16)

idf_component_register(
                        SRCS "./src/status_led.cpp"
                        INCLUDE_DIRS "./include"
                        REQUIRES rgbled_if wifi_nat_router_if
                    )