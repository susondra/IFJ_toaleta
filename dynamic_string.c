#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dynamic_string.h"

#define INITIAL_CAPACITY 16

bool dynamic_string_init(Dynamic_string *dyn_str)
{
    dyn_str->str = (char *)malloc(INITIAL_CAPACITY * sizeof(char));
    if (dyn_str->str == NULL)
    {
        return false;
    }
    dyn_str->str[0] = '\0'; // Start with an empty string
    dyn_str->length = 0;
    dyn_str->capacity = INITIAL_CAPACITY;
    return true;
}

bool dynamic_string_resize(Dynamic_string *dyn_str, size_t new_capacity)
{
    char *new_str = (char *)realloc(dyn_str->str, new_capacity * sizeof(char));
    if (new_str == NULL)
    {
        return false;
    }
    dyn_str->str = new_str;
    dyn_str->capacity = new_capacity;
    return true;
}

bool dynamic_string_add_char(Dynamic_string *dyn_str, char c)
{
    if (dyn_str->length + 1 >= dyn_str->capacity)
    {
        if (!dynamic_string_resize(dyn_str, dyn_str->capacity * 2))
        {
            return false;
        }
    }
    dyn_str->str[dyn_str->length++] = c;
    dyn_str->str[dyn_str->length] = '\0';
    return true;
}

bool dynamic_string_add_const_str(Dynamic_string *dyn_str, const char *src)
{
    size_t src_len = strlen(src);
    while (dyn_str->length + src_len >= dyn_str->capacity)
    {
        if (!dynamic_string_resize(dyn_str, dyn_str->capacity * 2))
        {
            return false;
        }
    }
    strcat(dyn_str->str, src);
    dyn_str->length += src_len;
    return true;
}

void dynamic_string_clear(Dynamic_string *dyn_str)
{
    dyn_str->length = 0;
    dyn_str->str[dyn_str->length] = '\0';
}

void dynamic_string_free(Dynamic_string *dyn_str)
{
    free(dyn_str->str);
    dyn_str->str = NULL;
    dyn_str->length = 0;
    dyn_str->capacity = 0;
}

void dynamic_string_print(Dynamic_string *dyn_str)
{
    printf("%s\n", dyn_str->str);
}

/*
int main()
{
    Dynamic_string dyn_str;
    if (!dynamic_string_init(&dyn_str))
    {
        return 1;
    }

    dynamic_string_add_const_str(&dyn_str, "Hello, ");
    dynamic_string_add_const_str(&dyn_str, "world!");

    printf("%s\n", dyn_str.str); // Output: Hello, world!

    dynamic_string_free(&dyn_str);
    return 0;
}
*/