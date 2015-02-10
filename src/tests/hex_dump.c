#include <stdio.h>

#define LINE_LEN 16


int main(int argc, char **argv, char **envs)
{
    int result = 0;
    int str_iter = 0;
    int line_iter = 0;
    FILE *ifl;
    int get_byte;
    unsigned char byte;
    char str[LINE_LEN * 2 + 1] = {0};

    if (2 != argc)
    {
        result = -1;
        printf("Use: %s <filename>\n", argv[0]);

    }
    else
    {
        FILE *ifl = fopen(argv[1], "rb");
        if ( ! ifl)
        {
            printf("Can`t open file: `%s`", argv[1]);
        }
        else
        {
            get_byte = fgetc(ifl);
            while(EOF != get_byte)
            {
                byte = get_byte;
                if (LINE_LEN > line_iter)
                {
                    if ('\n' == byte)
                    {
                        str[str_iter++] = '\\';
                        str[str_iter++] = 'n';
                    }
                    else if ('\f' == byte)
                    {
                        str[str_iter++] = '\\';
                        str[str_iter++] = 'f';
                    }
                    else if ('\t' == byte)
                    {
                        str[str_iter++] = '\\';
                        str[str_iter++] = 't';
                    }
                    else if (0xc == byte)
                    {
                        str[str_iter++] = '\\';
                        str[str_iter++] = 'c';
                    }
                    else if ('\r' == byte)
                    {
                        str[str_iter++] = '\\';
                        str[str_iter++] = 'r';
                    }
                    else if ('\v' == byte)
                    {
                        str[str_iter++] = '\\';
                        str[str_iter++] = 'v';
                    }
                    else if ('\a' == byte)
                    {
                        str[str_iter++] = '\\';
                        str[str_iter++] = 'a';
                    }
                    else if ('\b' == byte)
                    {
                        str[str_iter++] = '\\';
                        str[str_iter++] = 'b';
                    }
                    else
                    {
                        str[str_iter++] = byte;
                    }
                    line_iter++;
                    printf("%.2x ", byte);
                }
                else
                {
                    str_iter = 0;
                    line_iter = 0;
                    printf("| %s\n", str);
                }
                get_byte = fgetc(ifl);
            }

            while (LINE_LEN > line_iter)
            {
                line_iter++;
                printf("   ");
            }
            printf("| %s\n", str);
            fclose(ifl);
        }
    }
    return result;
}
