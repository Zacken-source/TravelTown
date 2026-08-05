#pragma once
#include "core/Grid.hpp"
#include <queue>
#include <vector>
#include <tuple>

class AttractivenessSystem
{
public:
    void recalculate(Grid& grid)
    {

        for (int y = 0; y < grid.getHeight(); ++y)
            for (int x = 0; x < grid.getWidth(); ++x)
                grid.at(x, y).setAttractiveness(0);

        for (int y = 0; y < grid.getHeight(); ++y)
            for (int x = 0; x < grid.getWidth(); ++x)
                if (grid.at(x, y).isOccupied())
                {
                    int strength = grid.at(x, y).getBuilding()->getAttractiveness();
                    if (strength > 0) diffuse(grid, x, y, strength);
                }
    }

private:
    void diffuse(Grid& grid, int startX, int startY, int strength)
    {
        std::queue<std::tuple<int,int,int>> queue;
        queue.push({startX, startY, strength});

        std::vector<std::vector<bool>> visited(
            grid.getHeight(), std::vector<bool>(grid.getWidth(), false));
        visited[startY][startX] = true;

        const int dx[] = { 0,  0, 1, -1 };
        const int dy[] = { 1, -1, 0,  0 };

        while (!queue.empty())
        {
            auto [x, y, value] = queue.front();
            queue.pop();

            grid.at(x, y).addAttractiveness(value);

            if (value <= 1) continue;
            for (int d = 0; d < 4; ++d)
            {
                int nx = x + dx[d], ny = y + dy[d];
                if (grid.isValid(nx, ny) && !visited[ny][nx])
                {
                    visited[ny][nx] = true;
                    queue.push({nx, ny, value - 1}); // decreissance d'1 par case
                }
            }
        }
    }
};