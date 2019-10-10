#pragma once
#include <map>
#include <string>
#include <utility>

namespace inputs
{
    std::map<std::string, std::pair<int, int>> GetData()
    {
        std::map<std::string, std::pair<int, int>> data{
			make_pair("A",std::make_pair(156, 193)),
            make_pair("B",std::make_pair(81, 315)),
            make_pair("C",std::make_pair(50, 197)),
            make_pair("D",std::make_pair(84, 234)),
            make_pair("E",std::make_pair(124, 162)),
            make_pair("F",std::make_pair(339, 345)),
            make_pair("G",std::make_pair(259, 146)),
            make_pair("H",std::make_pair(240, 350)),
            make_pair("I",std::make_pair(97, 310)),
            make_pair("J",std::make_pair(202, 119)),
            make_pair("K",std::make_pair(188, 331)),
            make_pair("L",std::make_pair(199, 211)),
            make_pair("M",std::make_pair(117, 348)),
            make_pair("N",std::make_pair(350, 169)),
            make_pair("O",std::make_pair(131, 355)),
            make_pair("P",std::make_pair(71, 107)),
            make_pair("Q",std::make_pair(214, 232)),
            make_pair("R",std::make_pair(312, 282)),
            make_pair("S",std::make_pair(131, 108)),
            make_pair("T",std::make_pair(224, 103)),
            make_pair("U",std::make_pair(83, 122)),
            make_pair("V",std::make_pair(352, 142)),
            make_pair("W",std::make_pair(208, 203)),
            make_pair("X",std::make_pair(319, 217)),
            make_pair("Y",std::make_pair(224, 207)),
            make_pair("Z",std::make_pair(327, 174)),
            make_pair("AA",std::make_pair(89, 332)),
            make_pair("BB",std::make_pair(254, 181)),
            make_pair("CC",std::make_pair(113, 117)),
            make_pair("DD",std::make_pair(120, 161)),
            make_pair("EE",std::make_pair(322, 43)),
            make_pair("FF",std::make_pair(115, 226)),
            make_pair("GG",std::make_pair(324, 222)),
            make_pair("HH",std::make_pair(151, 240)),
            make_pair("II",std::make_pair(248, 184)),
            make_pair("JJ",std::make_pair(207, 136)),
            make_pair("KK",std::make_pair(41, 169)),
            make_pair("LL",std::make_pair(63, 78)),
            make_pair("MM",std::make_pair(286, 43)),
            make_pair("NN",std::make_pair(84, 222)),
            make_pair("OO",std::make_pair(81, 167)),
            make_pair("PP",std::make_pair(128, 192)),
            make_pair("QQ",std::make_pair(127, 346)),
            make_pair("RR",std::make_pair(213, 102)),
            make_pair("SS",std::make_pair(313, 319)),
            make_pair("TT",std::make_pair(207, 134)),
            make_pair("UU",std::make_pair(154, 253)),
            make_pair("VV",std::make_pair(50, 313)),
            make_pair("WW",std::make_pair(160, 330)),
            make_pair("XX",std::make_pair(332, 163))};
    
        return data;
    }
} // namespace inputs