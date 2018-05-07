
#include <iostream>

#define CATCH_CONFIG_RUNNER
#include <Catch/catch.hpp>

unsigned int Factorial(const unsigned int n) noexcept
{
    return ((n > 1) ?  Factorial(n - 1) * n : 1);
}

TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(Factorial(0) == 1);
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(6) == 720);
    REQUIRE(Factorial(10) == 3628800);
}

inline unsigned int Area(const unsigned int length, const unsigned int width) noexcept
{
    return length * width;
}

inline unsigned int Volume(const unsigned int length, const unsigned int width, const unsigned int height) noexcept
{
    return Area(length, width) * height;
}


int main(int argc, char *argv[])
{
    // Global Setup
    Catch::Session TestSession;

    // Writing to TestSession.configData() here sets defaults.
    // This is the preferred way to set them.

    // Some user variables we want to be able to set
    int length = 0;
    int width = 0;
    int height = 0;

    // Build a new parser on top of Catch's
    auto cli
        = TestSession.cli() // Get Catch's composite command line parser
        | Catch::clara::Opt(length, "length")  // Bind variable to a new option, with a hint string
            ["-l"]["--length"]                 // The option names it will respond to.
            ("How long?")                      // The description string for the help output.
        | Catch::clara::Opt(width, "width")
            ["-w"]["--width"]
            ("How wide?")
        | Catch::clara::Opt(height, "height")
            ["-h"]["--height"]                
            ("How high?");

    // Now pass the new composite back to Catch so it uses that.
    TestSession.cli(cli);

    // Let Catch (using Clara) parse the command line
    if (TestSession.applyCommandLine(argc, argv)) {
        std::cerr << "<Error applying command line parameters to test session>\n";

        return EXIT_FAILURE;
    }

    // If set on the command line, variables are now set at this point. If the
	// variable was set, print it's value to the command line.
    if (length)
    {
        std::cout << "Length: " << length << "\n";
    }

    if (width)
    {
        std::cout << "Width: " << width << "\n";
    }

    if (height)
    {
        std::cout << "Height: " << height << "\n";
    }

    std::cout << "Area:   " << Area(length, width) << "\n";
    std::cout << "Volume: " << Volume(length, width, height) << "\n";

    // Writing to <session>.configData() or <session>.Config() here
    // ovverrides the command line args. Only do this if you know
    // you need to.

    const auto testsFailed = TestSession.run();

    // `testsFailed` is clamped to 255 as some unices only use the lower 8 bits.
    // This clamping has already been applied, so just return it here. You can
    // also do any post run clean-up here.

    return testsFailed;
}