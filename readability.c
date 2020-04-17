#include <stdio.h>
#include <cs50.h>
#include<string.h>

int count_letters(string text);
int word_count(string text);
int sentences_count(string text);

int main(void)
{
    string text = get_string("Enter the string : ");
    float L = (float)count_letters(text) * 100.0  / (float)word_count(text);
    float S = (float)sentences_count(text) * 100.0 / (float)word_count(text);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %0.0f\n", index);
    }
}

int count_letters(string text)
{
    char num[18] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '?', '!', ' ', ',', '\'', '-', ';'};
    int letter_counter = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        bool not_letter = false;
        for (int y = 0; y < 18; y++)
        {
            if (text[i] == num[y])
            {
                not_letter = true;
            }
        }
        if (!not_letter)
        {
            letter_counter++;
        }
    }
    return letter_counter;
}

int word_count(string text)
{
    int word_c = 0;
    string word = "";
    for (int i = 0; i < strlen(text); i++)
    {

        if (text[i] != ' ')
        {
            word += text[i];
        }
        else if (text[i] == ' ')
        {
            word = "";
            word_c++;
        }
        if (text[i] != ' ' && i + 1 == strlen(text))
        {
            word_c++;
        }
    }

    return word_c;
}

int sentences_count(string text)
{
    int dot_count = 0;
    for (int i = 0; i < strlen(text) ; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            dot_count++;
        }
    }
    return dot_count;
}