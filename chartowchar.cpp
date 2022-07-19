#include <iostream>
#include <string>

void printcharbuf(char * buf, unsigned int bufsize) {
    // print buf content
    std::cout << "buf = { ";
    for (unsigned int i = 0; i < bufsize; i++) {
        std::cout << std::hex << (int) buf[i];
        if (i+1 != bufsize)
            std::cout << ", ";
    }
    std::cout << " }\n";
}

void printwcharbuf(wchar_t * buf, unsigned int bufsize) {
    // print buf content
    std::cout << "buf = { ";
    for (unsigned int i = 0; i < bufsize; i++) {
        std::cout << std::hex << (int) buf[i];
        if (i+1 != bufsize)
            std::cout << ", ";
    }
    std::cout << " }\n";
}

void char2wchar(std::wstring & ws) {
    std::cout << "\n\n--\nchar2wchar\n\n";
    const unsigned int length = 3;
    char wstr[(length+1)*sizeof(wchar_t)] = { 0x41, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x7f };

    // Create a buffer of wchar_t's
    // The buffer size is (length+1) * sizeof(wchar_t). The +1 is for the terminating null.
    char * buf = NULL;
    unsigned int bufsize = (length + 1) * sizeof(wchar_t); // +1 for terminating null
    std::cout << "bufsize = (length + 1 ) * sizeof(wchar_t) = " << bufsize << "\n";
    buf = new char[(length + 1 ) * sizeof(wchar_t)];
    std::cout << "buf = " << static_cast<void*>(buf) << "\n";

    // Fill buf with known chars
    for (unsigned int i = 0; i < bufsize; i++) {
        buf[i] = wstr[i];
    }

    printcharbuf(buf, bufsize);

    std::cout << "Set buf NULL terminator\n";
    *(wchar_t*)(buf+length*sizeof(wchar_t)) = L'\0';

    printcharbuf(buf, bufsize);

    // assign string
    ws = (wchar_t*) buf;

    // Free temp buffer
    delete [] buf;
}

void wchar2char(std::wstring & ws) {
    std::cout << "\n\n--\nwchar2char\n\n";
    const unsigned int length = 3;
    wchar_t wstr[length+1] = { 0x00000041, 0x00000042, 0x00000043, 0x7f7f7f7f };

    // Create a buffer of wchar_t's
    // The buffer size is (length+1). The +1 is for the terminating null.
    wchar_t * buf = NULL;
    unsigned int bufsize = length + 1; // +1 for terminating null
    std::cout << "bufsize = length + 1 = " << bufsize << "\n";
    buf = new wchar_t[length + 1];
    std::cout << "buf = " << static_cast<void*>(buf) << "\n";

    // Fill buf with known wchar_t
    for (unsigned int i = 0; i < bufsize; i++) {
        buf[i] = wstr[i];
    }

    printwcharbuf(buf, bufsize);

    std::cout << "Set buf NULL terminator\n";
    buf[length] = L'\0';

    printwcharbuf(buf, bufsize);

    // assign string
    ws = buf;

    // Free buffer
    delete [] buf;
}

int main() {
    std::cout << "sizeof(char) is " << sizeof(char) << "\n";
    std::cout << "sizeof(wchar_t) is " << sizeof(wchar_t) << "\n";
    std::wstring ws1;
    char2wchar(ws1);
    printf("string = %S\n", ws1.c_str());
    std::wstring ws2;
    wchar2char(ws2);
    printf("string = %S\n", ws2.c_str());
    return 0;
}
