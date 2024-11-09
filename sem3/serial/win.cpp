#include <windows.h>
#include <iostream>
const char* portName = "\\\\.\\COM5";
int main() {
    COMSTAT status;
    DWORD errors;
    COMSTAT tstatus;
    HANDLE handler = CreateFileA(static_cast<LPCSTR>(portName),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (handler == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            std::cerr << "ERROR: Handle was not attached.Reason : " << portName << " not available\n";
        }
        else
        {
            std::cerr << "ERROR!!!\n";
        }
    }
    else
    {
        DCB dcbSerialParameters = { 0 };

        if (!GetCommState(handler, &dcbSerialParameters))
        {
            std::cerr << "Failed to get current serial parameters\n";
        }
        else
        {
            dcbSerialParameters.BaudRate = CBR_9600;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler, &dcbSerialParameters))
            {
                std::cout << "ALERT: could not set serial port parameters\n";
            }
            else
            {
                PurgeComm(handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(2000);

                // SEND DATA
                DWORD bytesSend;
                char buffer[] = { '1' };
                if (!WriteFile(handler, (void*)buffer, 1, &bytesSend, 0))
                {
                    ClearCommError(handler, &errors, &tstatus);
                    std::cerr << "FAILED to write\n";
                }

                // READ DATA
                DWORD bytesRead;
                if (ReadFile(handler, (void*)buffer, 1, &bytesRead, 0)) {
                    std::cout << "read: " << buffer[0] << '\n';
                }
                else{
                    ClearCommError(handler, &errors, &tstatus);
                    std::cerr << "FAILED to write\n";
                }
            }
        }
    }

    CloseHandle(handler);
    return 0;
}
