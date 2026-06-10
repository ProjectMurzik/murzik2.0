#include "kawaii_face_service.h"
#include "lvgl_kawaii_face.h"
#include "esp_log.h"
#include "esp_timer.h"
#include <string.h>

static const char *TAG = "kawaii_face";

// Таблица маппинга событий → эмоции (все 17)
static const struct {
    const char *event;
    face_emotion_t emotion;
} EMOTION_MAP[] = {
    {"idle",           FACE_NEUTRAL},
    {"wake_word",      FACE_SURPRISED},
    {"listening",      FACE_NEUTRAL},
    {"thinking",       FACE_WORKING_HARD},
    {"speaking",       FACE_HAPPY},
    {"success",        FACE_EXCITED},
    {"error",          FACE_SAD},
    {"critical_error", FACE_CRY},
    {"love",           FACE_LOVE},
    {"playful",        FACE_PLAYFUL},
    {"wink",           FACE_WINK},
    {"silly",          FACE_SILLY},
    {"smirk",          FACE_SMIRK},
    {"confused",       FACE_CONFUSED},
    {"cool",           FACE_COOL},
    {"sleepy",         FACE_SLEEPY},
    {"worried",        FACE_WORRIED},
    {"angry",          FACE_ANGRY},
};

static esp_timer_handle_t s_reset_timer = NULL;

static void reset_to_neutral(void *arg) {
    face_set_emotion(FACE_NEUTRAL, true);
}

void kawaii_face_set_emotion(const char *event_name) {
    if (!event_name) return;

    for (int i = 0; i < sizeof(EMOTION_MAP) / sizeof(EMOTION_MAP[0]); i++) {
        if (strcmp(event_name, EMOTION_MAP[i].event) == 0) {
            ESP_LOGI(TAG, "Emotion: %s → %d", event_name, EMOTION_MAP[i].emotion);
            face_set_emotion(EMOTION_MAP[i].emotion, true);

            // Авто-возврат к NEUTRAL через 5 сек (кроме idle/sleepy)
            if (strcmp(event_name, "idle") != 0 && strcmp(event_name, "sleepy") != 0) {
                if (s_reset_timer == NULL) {
                    esp_timer_create_args_t args = { .callback = reset_to_neutral };
                    esp_timer_create(&args, &s_reset_timer);
                }
                esp_timer_stop(s_reset_timer);
                esp_timer_start_once(s_reset_timer, 5000000);
            } else if (s_reset_timer) {
                esp_timer_stop(s_reset_timer);
            }
            return;
        }
    }
    ESP_LOGW(TAG, "Unknown emotion event: %s", event_name);
}

void kawaii_face_service_init(lv_obj_t *parent) {
    face_config_t cfg = {
        .parent          = parent,
        .animation_speed = 30,
        .blink_interval  = 3000,
        .auto_blink      = true,
    };
    ESP_ERROR_CHECK(face_animation_init(&cfg));
    face_set_emotion(FACE_NEUTRAL, false);

    ESP_LOGI(TAG, "Kawaii Face Service initialized with %d emotions",
             (int)(sizeof(EMOTION_MAP) / sizeof(EMOTION_MAP[0])));
}
