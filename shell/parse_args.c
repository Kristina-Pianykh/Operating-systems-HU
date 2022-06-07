#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CAPACITY 156

char ***allocate_mem(int capacity)
{
    char ***progs;
    progs = (char ***)malloc(capacity * sizeof(char **));
    memset(progs, 0, capacity * sizeof(char *));

    for (int i = 0; i < capacity; i++)
    {
        progs[i] = (char **)malloc(capacity * sizeof(char *));
        memset(progs[i], 0, capacity * sizeof(char *));
    }
    return progs;
}

void free_memory(char ***str_array, int length)
{

    for (int i = 0; i < length; i++)
    {
        free(str_array[i]);
    }
    free(str_array);
}

char **split_string(char *line, char *delimiter)
{
    // int capacity = 10;
    char **tokens = (char **)malloc(CAPACITY * sizeof(char *));
    int idx = 0;

    char *split_item = strtok(line, delimiter);
    if (split_item == NULL)
        return NULL;
    while (split_item != NULL)
    {
        tokens[idx++] = split_item;
        split_item = strtok(NULL, delimiter);
    }
    tokens[idx] = NULL;
    return tokens;
}

char *read_input_line()
{
    char *line = NULL;
    size_t buflen = 0;
    getline(&line, &buflen, stdin);
    return line;
}

int count_strings_in_arr(char **str_arr)
{
    int idx = 0;
    int nulls = 0;
    int count = 0;

    while (nulls < 2)
    {
        if (str_arr == NULL)
            return 0;
        if (str_arr[idx] == NULL)
        {
            nulls++;
            idx++;
            continue;
        }
        nulls = 0;
        count++;
        idx++;
    }
    return count;
}

void print_arr_of_str(char **str_arr)
{
    int idx = 0;
    int nulls = 0;
    while (nulls < 2)
    {
        if (str_arr == NULL)
        {
            break;
        }
        if (str_arr[idx] == NULL)
        {
            nulls++;
            idx++;
            continue;
        }
        nulls = 0;
        printf("%s ", str_arr[idx]);
        idx++;
    }
    printf("\n");
}

int main()
{
    while (1)
    {
        char *line = read_input_line();

        char **progs = split_string(line, "|");
        char ***cmd_args = allocate_mem(CAPACITY);
        for (int i = 0; i < CAPACITY; i++)
        {
            cmd_args[i] = split_string(progs[i], " \n");
            if (cmd_args[i] == NULL)
                break;
        }

        /* print cmd_args*/
        for (int i = 0; i < CAPACITY; i++)
        {
            if (cmd_args[i] == 0 || cmd_args[i] == NULL)
                break;

            printf("cmd_args[%d], %d item(s): ", i, count_strings_in_arr(cmd_args[i]));
            print_arr_of_str(cmd_args[i]);
        }
        printf("\n");

        free(progs);
        free(line);
        free_memory(cmd_args, CAPACITY);
    }
    return 1;
}