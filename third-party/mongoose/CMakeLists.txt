cmake_minimum_required(VERSION 3.16)

idf_component_register(SRCS "./mongoose/mongoose.c"
                            "./mongoose/mongoose_esp32_millis.c"
                            "./mongoose/mongoose_fs.c"
                            "./mongoose/mongoose_glue.c"
                            "./mongoose/mongoose_impl.c"
                       INCLUDE_DIRS "./"
                       REQUIRES esp_timer app_update)

component_compile_options(-DMG_ENABLE_LINES)