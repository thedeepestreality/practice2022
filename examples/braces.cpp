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
    bool result = true;
    const size_t cNumCases = 7;
    const char* str_cases[cNumCases] = {
        "", 
        "()", 
        ")(",
        "()()",
        "(()",
        "())",
        "(())"
    };
    bool expected[cNumCases] = {true, true, false, true, false, false, true};
    for (size_t iter=0; iter < cNumCases; ++iter)
    {
        bool res;
        bool curr = testCase(str_cases[iter], expected[iter], res);
        std::cout << "test \"" << str_cases[iter] << "\" is " << (curr ? "ok" : "failed") << '\n';
        std::cout << "\tresult: " << res << " expected " << expected[iter] << '\n';
        result = result & curr;
    }
    std::cout << "Total result: " << result << '\n';

    return 0;
}