#include "stdafx.h"
#include <vector>
#include <assert.h>
#include <algorithm>

void dfs(
    std::vector<std::vector<int>> const &matrix,    // original matrix
    std::vector<std::vector<int>> &isVisited,          // visited flags map
    int &result,            // final result - max connected cells
    size_t row,             // visiting position - row
    size_t column,       // visiting position - column
    int &tmpResult     // middle state - connected cells of "current region", its life time is through the steps of one region round, so must use ref
)
{
    if (isVisited[row][column]) {
        // this location has been visited, there is no need to visit it again
        return;
    }

    // mark this location as visited
    isVisited[row][column] = 1;

    if (!matrix[row][column]) {
        // if this location is '0', we can stop the dfs process right now
        return;
    }

    // this location is '1', we need to count it as part of the region this time
    tmpResult += 1;
    result = std::max(tmpResult, result);

    // we try to move to the "up" direction
    // we can only move to the "up" direction when we are not at topmost row (row 0)
    if (row != 0) {
        dfs(matrix, isVisited, result, row - 1, column, tmpResult);
    }

    // we try to move to the "down" direction
    // we can only move to the "down" direction when we are not at bottommost row (row "matrix.size() - 1")
    if (row != matrix.size() - 1) {
        dfs(matrix, isVisited, result, row + 1, column, tmpResult);
    }

    // we try to move to the "left" direction
    // we can only move the the "left" direction when we are not at column 0
    if (column != 0) {
        dfs(matrix, isVisited, result, row, column - 1, tmpResult);
    }

    // we try to move to the "right" direction
    // we can only move to the "right" direction when we are not at column "matrix[0].size() - 1"
    if (column != matrix[0].size() - 1) {
        dfs(matrix, isVisited, result, row, column + 1, tmpResult);
    }

    // we try to move to the "left - up" direction
    // we can only move the the "left - up" direction when we are not at column 0 and we are not at row 0
    if (column != 0 && row != 0) {
        dfs(matrix, isVisited, result, row - 1, column - 1, tmpResult);
    }

    // we try to move to the "left - down" direction
    // we can only move to the "left - down" direction when
    //      1. column != 0 &&
    //      2. row != matrix.size() - 1
    if (column != 0 && row != matrix.size() - 1) {
        dfs(matrix, isVisited, result, row + 1, column - 1, tmpResult);
    }

    // we try to move the the "right - up" direction
    // we can only move the "right - up" direction when
    //      1. column != matrix[0].size() - 1 &&
    //      2. row != 0
    if (column != matrix[0].size() - 1 && row != 0) {
        dfs(matrix, isVisited, result, row - 1, column + 1, tmpResult);
    }

    // we try to move to the "right - down" direction
    // we can only move to the "right - down" direction when
    //      1. we are not at rightmost position "column != matrix[0].size() - 1"
    //      2. we are not at downmost position "row != matrix.size() - 1"
    if (column != matrix[0].size() - 1 && row != matrix.size() - 1) {
        dfs(matrix, isVisited, result, row + 1, column + 1, tmpResult);
    }
}

int connectedCell(std::vector<std::vector<int>> matrix) 
{
    // use asserts to check the preconditions 
    auto const rowCount = matrix.size();
    assert(0 < rowCount && rowCount < 10);
    auto const columnCount = matrix[0].size();
    assert(0 < columnCount && columnCount < 10);

    std::vector<std::vector<int>> isVisited(rowCount, std::vector<int>(columnCount, 0));
    int result = 0;

    for (size_t row = 0; row < rowCount; ++row) {
        for (size_t column = 0; column < columnCount; ++column) {
            if (isVisited[row][column]) {
                continue;
            }
            int tmpResult = 0;
            dfs(matrix, isVisited, result, row, column, tmpResult);
        }
    }

    return result;
}

int main()
{
    {
        std::vector<std::vector<int>> matrix = {
            {0, 0, 1, 1},
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0}
        };
        assert(connectedCell(matrix) == 8);
    }
    return 0;
}

