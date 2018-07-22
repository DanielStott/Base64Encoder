#include <iostream>
#include <cassert>

static const std::string base64_table =
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
        //Takes 3 characters from the character array to be encoded
        for(unsigned int j = 0; j < 3; j++)
        {
            //Checks if there's still characters left to be encoded
            if(i <= arraySize)
            {
                standardChar[j] = charArray[i++];
                continue;
            }
            i++;
        }

        //If there is less than 3 characters left to be encoded
        if(i > arraySize)
        {
            unsigned int charsLeft = (i - arraySize);
            if(charsLeft <= 2)
            {
                output += base64_table[standardChar[0] >> 2];
                output += base64_table[((standardChar[0] & 0x03) << 4) + ((standardChar[1] & 0xf0) >> 4)];
            }
            if(charsLeft == 1)
            {
                output += base64_table[((standardChar[1] & 0xf) << 2) + ((standardChar[2] & 0xc0) >> 6)];
            }
            break;
        }

        //encodes the characters into base64

        //Takes the first 6 bits from the first character
        output += base64_table[standardChar[0] >> 2];
        //Takes the last 2 bits of the first character and first 4 of the second character
        output += base64_table[((standardChar[0] & 0x03) << 4) + ((standardChar[1] & 0xf0) >> 4)];
        //Takes the last 4 six bits of the second character and the first 2 of the third character
        output += base64_table[((standardChar[1] & 0xf) << 2) + ((standardChar[2] & 0xc0) >> 6)];
        //Takes the last 6 bits from the last character
        output += base64_table[standardChar[2] & 0x3f];
    }

    //Adds padding
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


