
#include "color.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*  PALETTE FILE
**
**  format:
**  2 bytes for "PL" -> file identifier
**  4 bytes for palette size
**  size * 4 bytes of palette colors
**
**  example dump:
**
**  50 4c SZ SZ SZ SZ CC CC CC CC CC ...
**
**  50 4c: PL
**  SZ: size byte
**  CC: color code (1 color is 4 bytes)
**
*/

size_t  ft_strncmp(char *s1, char *s2, size_t n)
{
    size_t i;

    i = 0;
    while (s1 && s2 && *s1 && *s2 && i++ < n)
    {
        if (*s1 != *s2)
            return (s1 - s2);
        s1++;
        s2++;
    }
    return (0);
}

t_color *load_palette(char *file_name, uint32_t *size)
{
    int         fd;
    
    char        prefix_buf[3];
    t_color     *palette;

    if (!size)
        return (NULL);
    *size = 0;
    fd = open(file_name, O_RDONLY, 0644);
    if (fd < 0)
        return (NULL);
    read(fd, prefix_buf, 2);
    prefix_buf[2] = 0;
    if (ft_strncmp(prefix_buf, "PL", 2))
    {
        printf ("error: invalid file format.\n");
        return (NULL);
    }
    read(fd, size, 4);
    palette = malloc(sizeof(t_color) * *size);
    if (!palette)
        return (NULL);
    if (read(fd, palette, sizeof(t_color) * *size) != sizeof(t_color) * *size)
        return (NULL);
    return (palette);
}

uint8_t export_palette(char *file_name, t_color *palette, uint32_t size)
{
    int     fd;
    size_t  size_buf;

    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (1);
    size_buf = size;
    write (fd, "PL", 2);
    write (fd, &size_buf, 4);
    write (fd, palette, sizeof(t_color) * size);
    close(fd);
    return (0);
}

