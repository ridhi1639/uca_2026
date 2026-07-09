#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LOGFILE "audit.log"

int main(int argc, char *argv[]) {

    if (argc < 2)
        return 1;

    if (strcmp(argv[1], "--add") == 0 && argc == 3) {

        int fd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0644);

        write(fd, argv[2], strlen(argv[2]));
        write(fd, "\n", 1);

        close(fd);
    }

    else if (strcmp(argv[1], "--view") == 0) {

        int fd = open(LOGFILE, O_RDONLY);

        char ch;
        int line = 1;

        char num[20];
        int len = 0;
        int temp = line;

        while (temp > 0) {
            num[len++] = (temp % 10) + '0';
            temp /= 10;
        }

        for (int i = len - 1; i >= 0; i--)
            write(1, &num[i], 1);

        write(1, ": ", 2);

        while (read(fd, &ch, 1) > 0) {

            write(1, &ch, 1);

            if (ch == '\n') {
                line++;

                temp = line;
                len = 0;

                while (temp > 0) {
                    num[len++] = (temp % 10) + '0';
                    temp /= 10;
                }

                for (int i = len - 1; i >= 0; i--)
                    write(1, &num[i], 1);

                write(1, ": ", 2);
            }
        }

        close(fd);
    }

    return 0;
}
