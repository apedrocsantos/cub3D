#include "../includes/cub3D.h"

#define ERROR_CODE -1

void leave_on_error(t_data *data, char *error_statement)
{
    printf("[ERROR_HANDLER]:%d %s\n",data->map[0][0], error_statement);
    exit(ERROR_CODE);
}