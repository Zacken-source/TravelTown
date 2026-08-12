#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "economy/Treasury.hpp"

TEST_CASE("Solde initial correct")
{
    Treasury t(5000);
    CHECK(t.getBalance() == 5000);
}
TEST_CASE("Depense reussie si fonds suffisants")
{
    Treasury t(1000);
    CHECK(t.spend(300, "Test") == true);
    CHECK(t.getBalance() == 700);
}
TEST_CASE("Depense refusee si fonds insuffisants")
{
    Treasury t(100);
    CHECK(t.spend(500, "Test") == false);
    CHECK(t.getBalance() == 100);
}
TEST_CASE("Revenu augmente le solde")
{
    Treasury t(0);
    t.earn(250, "Test");
    CHECK(t.getBalance() == 250);
}
TEST_CASE("Historique correct")
{
    Treasury t(1000);
    t.spend(200, "A");
    t.earn(100, "B");
    CHECK(t.getHistory().size() == 2);
    CHECK(t.getHistory()[0].amount == -200);
    CHECK(t.getHistory()[1].amount == 100);
}