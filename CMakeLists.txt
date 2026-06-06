# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

# 🔥 КРИТИЧНО: Принудительное включение ImageFont для LVGL v9
# Должно быть ДО include($ENV{IDF_PATH}...), иначе не применится к системным компонентам
add_compile_definitions(LV_USE_IMGFONT=1)

# Отключаем предупреждение о недостающих инициализаторах полей (часто встречается в LVGL/ESP-SR)
add_compile_options(-Wno-missing-field-initializers)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# "Trim" the build. Include the minimal set of components, main, and anything it depends on.
idf_build_set_property(MINIMAL_BUILD ON)

set(PROJECT_VER "2.0.0")
project(Murzik)
