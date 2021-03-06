#include "ycc.h"

void error(const char *file_name, const char *func_name, int line,
           const char *fmt, ...) {
    fprintf(stderr, "\033[1;31m");
    fprintf(stderr, "%s:%s:%d: ", file_name, func_name, line);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    fprintf(stderr, "\33[0m");
    exit(1);
}

Vector *new_vector() {
    Vector *v = malloc(sizeof(Vector));
    v->data = malloc(sizeof(void *) * 16);
    v->capacity = 16;
    v->len = 0;
    return v;
}

void vec_push(Vector *v, void *elem) {
    if (v->capacity == v->len) {
        v->capacity *= 2;
        v->data = realloc(v->data, sizeof(void *) * v->capacity);
    }
    v->data[v->len++] = elem;
}

Map *new_map() {
    Map *map = malloc(sizeof(Map));
    map->keys = new_vector();
    map->values = new_vector();
    return map;
}

void map_set(Map *map, char *key, void *value) {
    vec_push(map->keys, key);
    vec_push(map->values, value);
}

void *map_get(Map *map, char *key) {
    for (int i = map->keys->len - 1; i >= 0; i--) {
        if (!strcmp(map->keys->data[i], key))
            return map->values->data[i];
    }
    return NULL;
}

bool map_exists(Map *map, char *key) {
    for (int i = 0; i < map->keys->len; i++) {
        if (!strcmp(map->keys->data[i], key))
            return true;
    }
    return false;
}

StringBuilder *new_stringbiulder() {
    StringBuilder *sb = malloc(sizeof(StringBuilder));
    sb->entity = (char *)malloc(sizeof(char) * 50);
    sb->capacity = 50;
    sb->len = 0;
    return sb;
}

void stringbuilder_append(StringBuilder *sb, char *str) {
    int delta_len = strlen(str);
    if (sb->capacity <= sb->len + delta_len) {
        sb->capacity += delta_len;
        sb->entity = (char *)realloc(sb->entity, sizeof(char) * sb->capacity);
    }
    memcpy(sb->entity + sb->len, str, delta_len);
    sb->len += delta_len;
}