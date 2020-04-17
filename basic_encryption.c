#include <stdio.h>
#include <string.h>
#include <cs50.h>

bool validate_key(string text);
string encrypt(string text_to_encrypt, string key);

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argc == 2 && strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;

    }
    else
    {
        string key = argv[1];
        if (!validate_key(key))
        {
            printf("You didn't use proper key\n");
            return 1;
        }
        printf("plain text: ");
        string word_to_encrypt = get_string(" ");
        string test = encrypt(word_to_encrypt, key);
        printf("ciphertext:  %s\n\n", test);


    }

}

bool validate_key(string text)
{
    char UpL[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char LoL[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for (int i = 0 ; i < strlen(text); i++)
    {
        bool found = false;
        for (int y = 0; y < 26 ; y++)
        {
            if (text[i] == UpL[y] || text[i] == LoL[y])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    for (int i = 0; i < strlen(text) - 1; i++)
    {
        for (int y = i + 1; y < strlen(text); y++)
        {
            if (text[i] == text[y])
            {
                return false;
            }
        }
    }
    return true;
}

string encrypt(string text_to_encrypt, string key)
{
    char UpL[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char LoL[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for (long i = 0; i < strlen(text_to_encrypt); i++)
    {
        bool foundF = false;
        for (int y = 0; y < 26 ; y++)
        {
            if (text_to_encrypt[i] == LoL[y])
            {
                bool f = false;

                for (int z = 0; z < 26; z++)
                {

                    if (key[y] == UpL[z])
                    {
                        text_to_encrypt[i] = LoL[z];
                        f = true;
                        foundF = true;
                        break;
                    }
                }
                if (!f)
                {
                    text_to_encrypt[i] = key[y];
                    foundF = true;
                    break;

                }
                if (foundF)
                {
                    break;
                }
            }
        }
        if (foundF)
        {
            continue;
        }
        foundF = false;
        for (int y = 0; y < 26 ; y++)
        {
            if (text_to_encrypt[i] == UpL[y])
            {
                bool f2 = false;
                for (int z = 0; z < 26; z++)
                {
                    if (key[y] == LoL[z])
                    {
                        text_to_encrypt[i] = UpL[z];
                        foundF = true;
                        f2 = true;
                        break;
                    }
                }
                if (!f2)
                {
                    text_to_encrypt[i] = key[y];
                    break;
                }
            }
            if (foundF)
            {
                break;

            }
        }
    }
    return text_to_encrypt;
}