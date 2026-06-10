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

/**
 * @brief Установка эмоции по имени события
 * @param event_name Имя события ("love", "happy", "thinking" и т.д.)
 * @note Потокобезопасна, можно вызывать из любого потока
 */
void kawaii_face_set_emotion(const char *event_name);

#ifdef __cplusplus
}
#endif
