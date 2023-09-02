#include "../headers.h"

void clear_token(char token[])
{
    if (token == NULL)
        return;
    if (strlen(token) == 0)
    {
        token = NULL;
        return;
    }
    if (strlen(token) == 1 && token[0] == '\n')
    {
        token[0] = '\0';
        return;
    }
    if (token[0] == ' ' || token[0] == '\0' || token[0] == '\n' || token[0] == '\t')
    {
        token[0] = '\0';
        return;
    }
    for (int i = 0; i < strlen(token); i++)
    {
        if (token[i] == ' ' || token[i] == '\n' || token[i] == '\t')
        {
            token[i] = '\0';
            break;
        }
    }
    if (strlen(token) == 0)
    {
        token[0] = '\0';
        return;
    }
}

void remove_leading_whitespaces(char input[])
{
    int i = 0;
    while (input[i] == ' ')
    {
        i++;
    }
    int j = 0;
    while (input[i] != '\0')
    {
        input[j] = input[i];
        i++;
        j++;
    }
    input[j] = '\0';
}