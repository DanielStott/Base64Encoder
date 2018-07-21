#include <iostream>
#include <cassert>

static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string base64_encode(const std::string &input)
{
    std::string output;
    const char *charArray = input.c_str();
    unsigned int arraySize = (int)input.size();
    unsigned int paddingSize = ((arraySize * 8) % 24);
    char standardChar[3];

    for(unsigned int i = 0; i < arraySize;)
    {
        for(unsigned int j = 0; j < 3; j++)
        {
            if(i <= arraySize)
            {
                standardChar[j] = charArray[i++];
                continue;
            }
            i++;
        }

        if(i > arraySize)
        {
            unsigned int charsLeft = (i - arraySize);
            if(charsLeft <= 2)
            {
                output += base64_chars[standardChar[0] >> 2];
                output += base64_chars[((standardChar[0] & 0x03) << 4) + ((standardChar[1] & 0xf0) >> 4)];
            }
            if(charsLeft == 1)
            {
                output += base64_chars[((standardChar[1] & 0xf) << 2) + ((standardChar[2] & 0xc0) >> 6)];
            }
            break;
        }

        output += base64_chars[standardChar[0] >> 2];
        output += base64_chars[((standardChar[0] & 0x03) << 4) + ((standardChar[1] & 0xf0) >> 4)];
        output += base64_chars[((standardChar[1] & 0xf) << 2) + ((standardChar[2] & 0xc0) >> 6)];
        output += base64_chars[standardChar[2] & 0x3f];
    }

    if(paddingSize == 16)
    {
        output += "=";
    }
    else if(paddingSize == 8) {
        output += "==";
    }

    return output;
}



int main()
{
    assert(base64_encode("hello") == "aGVsbG8=");
    assert(base64_encode("bob") == "Ym9i");
    assert(base64_encode("sausage") == "c2F1c2FnZQ==");
    assert(base64_encode("").empty());

    return 0;
}


