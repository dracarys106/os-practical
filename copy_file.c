#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    int src, dst;
    ssize_t n;
    char buffer[BUFSIZE];
    long total = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s source destination\n", argv[0]);
        return 1;
    }

    src = open(argv[1], O_RDONLY);
    if (src < 0) {
        perror("open source");
        return 1;
    }

    dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst < 0) {
        perror("open destination");
        close(src);
        return 1;
    }

    while ((n = read(src, buffer, sizeof(buffer))) > 0) {
        ssize_t written = 0;
        while (written < n) {
            ssize_t w = write(dst, buffer + written, (size_t)(n - written));
            if (w < 0) {
                perror("write");
                close(src);
                close(dst);
                return 1;
            }
            written += w;
        }
        total += n;
    }

    if (n < 0) perror("read");
    close(src);
    close(dst);

    if (n < 0) return 1;
    printf("%ld bytes copied from %s to %s\n", total, argv[1], argv[2]);
    return 0;
}
