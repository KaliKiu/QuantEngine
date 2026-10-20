#include "../Engine/engine.hpp"

#include <cassert>
#include <string>
#include <vector>

int main() {
    quant::Engine engine;

    std::vector<std::size_t> lengths;
    std::vector<std::string> recorded;

    auto source = engine.addSource<std::string>(
        "test-source",
        [](auto emit) {
            emit("XAUUSD");
            emit("BTCUSD");
        }
    );

    auto length = engine.addTransform<
        std::string, std::size_t
    >(
        "length",
        [](const std::string& s) {
            return s.size();
        }
    );

    auto record = engine.addSink<std::string>(
        "record",
        [&](const std::string& s) {
            recorded.push_back(s);
        }
    );

    auto collect = engine.addSink<std::size_t>(
        "collect",
        [&](std::size_t n) {
            lengths.push_back(n);
        }
    );

    engine.connect(source, length.input);
    engine.connect(source, record);
    engine.connect(length.output, collect);

    engine.run();

    assert((recorded ==
        std::vector<std::string>{"XAUUSD", "BTCUSD"}));

    assert((lengths ==
        std::vector<std::size_t>{6, 6}));
}