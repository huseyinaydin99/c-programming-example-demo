#include <stdio.h>
#include <fcntl.h>
#include <sys/file.h>

void deleteFile(){
	char filePath[100];
 
    printf("Enter file path: ");
    scanf("%s", filePath);
 
    if (remove(filePath) == 0) {
        printf("File successfully deleted\n");
    } else {
        printf("File deletion failed\n");
    }
 
    return;
}

int main(int argc, char *argv[]) {
    int fd;
    if (argc < 2) {
        printf("Kullanım: %s dosya_adi\n", argv[0]);
        return 1;
    }
    fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        perror("Dosya açma hatası");
        return 1;
    }
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        perror("Dosya kilidi hatası");
        return 1;
    }
    printf("Dosya kilitlendi\n");
    return 0;
}

/*
Bu kod, verilen dosya adını alır ve dosyaya sadece okuma izni verir. Dosyayı açmaya çalışan başka bir uygulama, "Dosya kilidi hatası" mesajını görür ve dosya açamaz.

Not: Bu kodun kullanımından kaynaklanabilecek her türlü sonuç sizin sorumluluğunuzdadır.
*/