// 1312.MinimumInsertionStepsToMakeAStringPalindrome.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Solution {
public:
    int minInsertions(std::string s) {
    }

private:
    int slnRecursion(std::string s, ptrdiff_t first, ptrdiff_t last, std::vector<std::vector<int>> &dp) {
        // handle base case first
        ptrdiff_t len = last - first;
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return 0;
        }

        // find it in dp cache
        if (dp[first][last] != -1) {
            return dp[first][last];
        }

        // len >= 2
        // the checking range is [first, last)
        char chFront = s[first];
        char chBack = s[last - 1];
        if (chFront == chBack) {
            dp[first][last] = slnRecursion(s, first + 1, last - 1, dp);
            return dp[first][last];
        }
        else {
            // chFront != chBack
            dp[first][last] = 1 + std::min(
                slnRecursion(s, first + 1, last, dp),
                slnRecursion(s, first, last - 1,dp)
            );
            return dp[first][last];
        }
    }
};

int main()
{
    std::cout << "Hello World!\n"; 
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
