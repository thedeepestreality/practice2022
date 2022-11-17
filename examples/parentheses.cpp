#include <iostream>

bool validParentheses(const char str[]) 
{
    return false;
}

bool testCase(const char str[], bool expected, bool& res){
    res = validParentheses(str);
    return res == expected;
}

int main()
{
    const char* str_cases[] = {
        "",
        "(",")","()",")(","()()","(()","())","(())",")(()))","(())((()())())",
        "[","]","[]","][","[][]","[[]","[]]","[[]]","][[]]]","[[]][[[][]][]]",
        "{","}","{}","}{","{}{}","{{}","{}}","{{}}","}{{}}}","{{}}{{{}{}}{}}",
        "(){}[]","([{}])","(}","[(])","[({})](]"
    };
    const size_t cNumCases = sizeof(str_cases)/sizeof(char*);
    bool expected[cNumCases] = {
        true, 
        false, false, true, false, true, false, false, true, false, true,
        false, false, true, false, true, false, false, true, false, true,
        false, false, true, false, true, false, false, true, false, true,
        true, true, false, false, false
    };
    bool result = true;
    for (size_t iter=0; iter < cNumCases; ++iter)
    {
        bool curr_validBraces;
        bool curr_test = testCase(str_cases[iter], expected[iter], curr_validBraces);
        std::cout << "test \"" << str_cases[iter] << "\" is " << (curr_test ? "ok" : "failed") << '\n';
        std::cout << "\tresult: " << curr_validBraces << " expected " << expected[iter] << '\n';
        result = result && curr_test;
    }
    std::cout << "Total result: " << result << '\n';

    return 0;
}