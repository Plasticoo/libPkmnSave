#ifndef _PKMN_ROMFACTORY_HPP_
#define _PKMN_ROMFACTORY_HPP_

#include "Rom.hpp"
#include "RomInterface.hpp"

struct RomFactory {
    static auto make_rom(std::filesystem::path const& file) -> std::unique_ptr<RomInterface>;
};

#endif
