// 1021.RemoveOutermostParentheses.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

class Solution {
public:
    std::string removeOuterParentheses(std::string S) {
        // the range of S is [sFirstIndex: sLastIndex)
        ptrdiff_t const sFirstIndex = 0;
        ptrdiff_t const sLastIndex = S.size();

        // LoopInvariants
        // S[0, scanPos) has been scanned
        // unPairedLeftBraces: the unPaired Left Brace Positions of S[0, scanPos)
        // outerBraces: the outerBraces of S[0, scanPos) in sequence
        std::vector<ptrdiff_t> unPairedLeftBraces{};
        unPairedLeftBraces.reserve(S.size());
        std::unordered_set<ptrdiff_t> outerBraces{};
        outerBraces.reserve(S.size());
        for (ptrdiff_t scanPos = 0; scanPos < sLastIndex; ++scanPos) {
            // We are scanning the pos at scanPos
            char scanningChar = S[scanPos];
            if (scanningChar == '(') {
                unPairedLeftBraces.push_back(scanPos);
            }
            else {
                // The scanning char is ')'
                if (unPairedLeftBraces.size() == 1) {
                    // This pair is outmost
                    outerBraces.insert(unPairedLeftBraces.back());
                    unPairedLeftBraces.pop_back();
                    outerBraces.insert(scanPos);
                }
                else {
                    // This pair is not the outmose
                    unPairedLeftBraces.pop_back();
                }
            }
        }
        // PostCondition:
        // S[0, sLastIndex) has been scanned
        // outerBraces: the outerBraces of S[0, sLastIndex) in sequence

        // Loop Invariants:
        // i: S[0, i) has been scanned
        // j: S[0, j) is the no outerBraces of range S[0, i)
        ptrdiff_t j = 0;
        for (ptrdiff_t i = 0; i < sLastIndex; ++i) {
            // We are scanning S[i]
            auto it = outerBraces.find(i);
            if (it == outerBraces.end()) {
                // S[i] is not outerBrace
                S[j++] = S[i];
            }
            else {
                // S[j] is outerBrace
                // Do Nothing
            }
        }
        // Post Condition:
        // i: S[0, sLastIndex) has been scanned
        // j: S[0, j) is the no outerBraces of range S[0, sLastIndex)
        return S.substr(0, j);
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
