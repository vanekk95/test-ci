#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main() {
    int secret, image, result;
    if ((secret = open("secret_469x473.enc", O_RDONLY)) == -1) {
        printf("can't open secret_469x473.enc: %s\n", strerror(errno));
        return -1;
    }
    if ((image = open("image_469x473.enc", O_RDONLY)) == -1) {
        printf("can't open image_469x473.enc: %s\n", strerror(errno));
        return -1;
    }
    if ((result = open("result_469x473.raw", O_WRONLY | O_CREAT)) == -1) {
        printf("can't open result_469x473.raw: %s\n", strerror(errno));
        return -1;
    }
    char secret_buff[1024], image_buff[1024];
    ssize_t ret_sc, ret_im;
    printf("sizeof = %lu\n", sizeof(secret_buff));
    while ((ret_sc = read(secret, secret_buff, sizeof(secret_buff))) &&
           (ret_im = read(image, image_buff, sizeof(image_buff)))) {
        if (ret_sc == -1 || ret_im == -1) {
            printf("can't read file\n");
            return -1;
        }
        if (ret_sc != ret_im) {
            printf("bad case!\n");
            return -1;
        }
        for (int i = 0; i < ret_sc; i++) {
            secret_buff[i] = secret_buff[i] ^ image_buff[i];
        }
        if (write(result, secret_buff, ret_sc) != ret_sc) {
            printf("can't write\n");
            return -1;
        }
    }
    close(secret);
    close(image);
    close(result);
    return 0;
}
