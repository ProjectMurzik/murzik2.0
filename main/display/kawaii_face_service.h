#pragma once

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Инициализация сервиса эмоций lvgl_kawaii_face
 * @param parent Родительский LVGL-объект (контейнер для лица)
 */
void kawaii_face_service_init(lv_obj_t *parent);

#ifdef __cplusplus
}
#endif
