#include "doctest.h"
#include "core/Grid.hpp"

TEST_CASE("Dimensions correctes")
{
    Grid g(10, 8);
    CHECK(g.getWidth() == 10);
    CHECK(g.getHeight() == 8);
}
TEST_CASE("isValid aux bords")
{
    Grid g(10, 8);
    CHECK(g.isValid(0,  0) == true);
    CHECK(g.isValid(9,  7) == true);
    CHECK(g.isValid(10, 0) == false);
    CHECK(g.isValid(-1, 0) == false);
}
TEST_CASE("Case vide par defaut")
{
    Grid g(5, 5);
    CHECK(g.at(2, 2).isOccupied() == false);
}