#include "stdafx.h"
#include <vector>
#include <assert.h>
#include <algorithm>

void dfs(
    std::vector<std::vector<int>> const &matrix,
    std::vector<std::vector<int>> &isVisited,
    int &maxConnectedCells,            
    size_t row,             
    size_t column,       
    int &connectedCellsOfThisRegion)
{
    if (isVisited[row][column]) {
        return;
    }

    isVisited[row][column] = 1;

    if (!matrix[row][column]) {
        return;
    }

    connectedCellsOfThisRegion += 1;
    maxConnectedCells = std::max(connectedCellsOfThisRegion, maxConnectedCells);

    const bool canMoveUp = (row != 0);
    const bool canMoveDown = (row != matrix.size() - 1);
    const bool canMoveLeft = (column != 0);
    const bool canMoveRight = (column != matrix[0].size() - 1);

    if (canMoveUp) {
        dfs(matrix, isVisited, maxConnectedCells, row - 1, column, connectedCellsOfThisRegion);
    }

    if (canMoveDown) {
        dfs(matrix, isVisited, maxConnectedCells, row + 1, column, connectedCellsOfThisRegion);
    }

    if (canMoveLeft) {
        dfs(matrix, isVisited, maxConnectedCells, row, column - 1, connectedCellsOfThisRegion);
    }

    if (canMoveRight) {
        dfs(matrix, isVisited, maxConnectedCells, row, column + 1, connectedCellsOfThisRegion);
    }

    if (canMoveLeft && canMoveUp) {
        dfs(matrix, isVisited, maxConnectedCells, row - 1, column - 1, connectedCellsOfThisRegion);
    }

    if (canMoveLeft && canMoveDown) {
        dfs(matrix, isVisited, maxConnectedCells, row + 1, column - 1, connectedCellsOfThisRegion);
    }

    if (canMoveRight && canMoveUp) {
        dfs(matrix, isVisited, maxConnectedCells, row - 1, column + 1, connectedCellsOfThisRegion);
    }

    if (canMoveRight && canMoveDown) {
        dfs(matrix, isVisited, maxConnectedCells, row + 1, column + 1, connectedCellsOfThisRegion);
    }
}

int connectedCell(std::vector<std::vector<int>> matrix) 
{
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
            int connectedCellsOfThisRegion = 0;
            dfs(matrix, isVisited, result, row, column, connectedCellsOfThisRegion);
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

