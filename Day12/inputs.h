#include <map>
#include <vector>

namespace inputs
{
    std::vector<char> GetInitialState()
    {
        std::string state = "#.####...##..#....#####.##.......##.#..###.#####.###.##.###.###.#...#...##.#.##.#...#..#.##..##.#.##";
        std::vector<char> initialState(state.size());

        for (auto i = 0; i < state.size(); i++)
        {
            auto a = state.at(i);
            initialState.push_back(a);
        }
        return initialState;
    }

    std::map<std::string, char> GetInstructions()
    {
        std::map<std::string, char> instructions;
        instructions.insert(std::make_pair(".##..", '.'));
        instructions.insert(std::make_pair("..##.", '#'));
        instructions.insert(std::make_pair(".#..#", '#'));
        instructions.insert(std::make_pair(".#.#.", '.'));
        instructions.insert(std::make_pair("..#..", '#'));
        instructions.insert(std::make_pair("###..", '#'));
        instructions.insert(std::make_pair("##..#", '.'));
        instructions.insert(std::make_pair("##...", '#'));
        instructions.insert(std::make_pair("#.###", '#'));
        instructions.insert(std::make_pair(".##.#", '#'));
        instructions.insert(std::make_pair("#....", '.'));
        instructions.insert(std::make_pair("###.#", '.'));
        instructions.insert(std::make_pair(".....", '.'));
        instructions.insert(std::make_pair(".#...", '#'));
        instructions.insert(std::make_pair("....#", '.'));
        instructions.insert(std::make_pair("#.#..", '.'));
        instructions.insert(std::make_pair("...#.", '#'));
        instructions.insert(std::make_pair("#...#", '.'));
        instructions.insert(std::make_pair("##.#.", '.'));
        instructions.insert(std::make_pair(".#.##", '#'));
        instructions.insert(std::make_pair("..#.#", '#'));
        instructions.insert(std::make_pair("#.#.#", '.'));
        instructions.insert(std::make_pair(".####", '.'));
        instructions.insert(std::make_pair("#####", '.'));
        instructions.insert(std::make_pair("..###", '.'));
        instructions.insert(std::make_pair("...##", '.'));
        instructions.insert(std::make_pair("#..##", '.'));
        instructions.insert(std::make_pair("#.##.", '.'));
        instructions.insert(std::make_pair("#..#.", '#'));
        instructions.insert(std::make_pair(".###.", '#'));
        instructions.insert(std::make_pair("##.##", '#'));
        instructions.insert(std::make_pair("####.", '.'));
        return instructions;
    }
} // namespace inputs