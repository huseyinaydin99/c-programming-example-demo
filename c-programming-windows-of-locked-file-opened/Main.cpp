#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hFile;
    hFile = CreateFile("sample.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Dosya açma hatası: %d\n", GetLastError());
        return 1;
    }

    if (LockFile(hFile, 0, 0, 100, 0)) {
        printf("Dosya kilitlendi.\n");
        // Dosyayı kullanın
        // ...
        UnlockFile(hFile, 0, 0, 100, 0);
        printf("Dosya kilidi açıldı.\n");
    } else {
        printf("Dosya kilidi açma hatası: %d\n", GetLastError());
        return 1;
    }

    CloseHandle(hFile);
    return 0;
}