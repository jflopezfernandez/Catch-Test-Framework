
#include <iostream>

#define CATCH_CONFIG_RUNNER
#include <Catch/catch.hpp>

unsigned int Factorial(unsigned int n) noexcept {
    return ((n > 1) ?  Factorial(n - 1) * n : 1);
}

TEST_CASE("Factorials are computed", "[factorial]") {
    REQUIRE(Factorial(0) == 1);
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(6) == 720);
    REQUIRE(Factorial(10) == 3628800);
}


int main()
{

}