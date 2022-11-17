#include <iostream>

bool check(const char str[]){
    int counter = 0;
    int idx = 0;
    while (str[idx] != '\0'){
        if (str[idx++] == '(')
            ++counter;
        else
            --counter;
        if (counter < 0)
            return false;
    }
    return counter == 0;
}

bool testCase(const char str[], bool expected, bool& res){
    res = check(str);
    return res == expected;
}

int main()
{
    const char* str_cases[] = {
        "",
        "(",
        ")",
        "()", 
        ")(",
        "()()",
        "(()",
        "())",
        "(())",
        ")(()))",
        "(())((()())())"
    };
    const size_t cNumCases = sizeof(str_cases)/sizeof(char*);
    bool expected[cNumCases] = {true, false, false, true, false, true, false, false, true, false, true};
    bool result = true;
    for (size_t iter=0; iter < cNumCases; ++iter)
    {
        bool curr_check;
        bool curr_test = testCase(str_cases[iter], expected[iter], curr_check);
        std::cout << "test \"" << str_cases[iter] << "\" is " << (curr_test ? "ok" : "failed") << '\n';
        std::cout << "\tresult: " << curr_check << " expected " << expected[iter] << '\n';
        result = result && curr_test;
    }
    std::cout << "Total result: " << result << '\n';

    return 0;
}
