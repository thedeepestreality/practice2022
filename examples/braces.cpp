#include <iostream>

typedef const char str16[16];

bool check(const char* str){
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

//shortest-ever braces validator
int c(char*s,int c){while(*s&&c>=0)c-=*s++*2-81;return!c;}

template <class Type>
struct CaseData{
    Type input;
    bool expected;    
};

template <class Type>
bool testCase(
    bool(*func)(Type),
    CaseData<Type> data,
    bool& res
){
    res = func(data.input);
    return res == data.expected;
}

int main()
{
    CaseData<str16> test_cases[] = {
        {"", true},
        {"(", false},
        {")", false},
        {"()",true}, 
        {")(", false},
        {"()()", true},
        {"(()", false},
        {"())", false},
        {"(())", true},
        {")(()))", false},
        {"(())((()())())", true}
    };
    const size_t cNumCases = sizeof(test_cases)/sizeof(CaseData<str16>);
    bool result = true;
    for (size_t iter=0; iter < cNumCases; ++iter)
    {
        bool curr_check;
        bool curr_test = testCase<str16>(
            check, 
            test_cases[iter], 
            curr_check
        );
        std::cout << "test \"" << test_cases[iter].input << "\" is " << (curr_test ? "ok" : "failed") << '\n';
        std::cout << "\tresult: " << curr_check << " expected " << test_cases[iter].expected << '\n';
        result = result && curr_test;
    }
    std::cout << "Total result: " << result << '\n';

    return 0;
}
