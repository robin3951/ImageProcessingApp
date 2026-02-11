#include <CLI/CLI.hpp>
#include <iostream>

int main(int argc, char** argv) {
    CLI::App app{"ImageProcessing CLI"};

    int value = 0;
    app.add_option("-v,--value", value, "Ein Beispielwert");

    CLI11_PARSE(app, argc, argv);

    std::cout << "Verarbeiteter Wert: " << value << std::endl;

    return 0;
}