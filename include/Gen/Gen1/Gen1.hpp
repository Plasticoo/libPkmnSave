#ifndef _PKMN_GEN1_HPP_
#define _PKMN_GEN1_HPP_

#include "Constants.hpp"
#include "Gen/Gen1/Enums.hpp"
#include "Gen/Gen1/Structs.hpp"
#include "IGlobal.hpp"
#include "Rom.hpp"
#include "Rom/RomInterface.hpp"
#include "Utils.hpp"

#include <fstream>
#include <memory>

//template<class Derived>
namespace Gen1
{
template<typename T>
struct Gen1: IGlobal {
    static_assert(std::is_same<Rom32kb, T>::value, "This class only accepts 32kb files.");

    Gen1(std::filesystem::path const& file)
    {
        this->m_rom = std::make_unique<Rom<T>>(file);
        this->load_file();
    }

    auto get_checksum() const -> std::uint8_t override
    {
        return this->m_rom->data[C::GEN1::OFFSETS::CHECKSUM];
    }

    auto calc_checksum() const -> std::uint8_t override
    {
        std::uint8_t checksum{ 0 };
        for (auto i = C::GEN1::OFFSETS::CHECKSUM_INIT_OFFSET;
             i <= C::GEN1::OFFSETS::CHECKSUM_END_OFFSET; i++) {
            checksum += m_rom->data[i];
        }
        return ~checksum;
    }

    auto set_checksum() -> void
    {
        auto checksum = this->calc_checksum();
        // NOTE: *(this->checksum) = checksum
        this->checksum[0] = checksum;
    }

    auto load_file() -> void
    {
        if (this->m_rom == nullptr) {
            return;
        }

        this->player_name = &this->m_rom->data[C::GEN1::OFFSETS::PLAYER_NAME];
        this->pokedex_owned = &this->m_rom->data[C::GEN1::OFFSETS::POKEDEX_OWNED];
        this->pokedex_seen = &this->m_rom->data[C::GEN1::OFFSETS::POKEDEX_SEEN];
        this->money = &this->m_rom->data[C::GEN1::OFFSETS::MONEY];
        this->rival_name = &this->m_rom->data[C::GEN1::OFFSETS::RIVAL_NAME];
        this->options = &this->m_rom->data[C::GEN1::OFFSETS::OPTIONS];
        this->badges = &this->m_rom->data[C::GEN1::OFFSETS::BADGES];
        this->player_trainer_id = (std::uint16_t*)&this->m_rom->data[C::GEN1::OFFSETS::PLAYER_TRAINER_ID];
        this->pikachu_friendship = &this->m_rom->data[C::GEN1::OFFSETS::PIKACHU_FRIENDSHIP];
        this->current_pc_box = &this->m_rom->data[C::GEN1::OFFSETS::CURRENT_PC_BOX];
        this->casino_coins = &this->m_rom->data[C::GEN1::OFFSETS::CASINO_COINS];
        this->current_box_list = (struct Structs::pkmn_box*)&this->m_rom->data[C::GEN1::OFFSETS::CURRENT_BOX_LIST];
        this->checksum = &this->m_rom->data[C::GEN1::OFFSETS::CHECKSUM];

        this->pocket_item_list = (struct Structs::items_bag*)&this->m_rom->data[C::GEN1::OFFSETS::POCKET_ITEM_LIST];
        this->pc_item_list = (struct Structs::items_pc*)&this->m_rom->data[C::GEN1::OFFSETS::PC_ITEM_LIST];
        this->time_played = (struct Structs::pkmn_time*)&this->m_rom->data[C::GEN1::OFFSETS::TIME_PLAYED];
        this->team_pokemon_list = (struct Structs::pkmn_party*)&this->m_rom->data[C::GEN1::OFFSETS::TEAM_POKEMON_LIST];

        this->pc_box[0] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000];
        this->pc_box[1] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000 + (1122 * 1)];
        this->pc_box[2] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000 + (1122 * 2)];
        this->pc_box[3] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000 + (1122 * 3)];
        this->pc_box[4] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000 + (1122 * 4)];
        this->pc_box[5] = (struct Structs::pkmn_box*)&this->m_rom->data[0x4000 + (1122 * 5)];

        this->pc_box[6] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000];
        this->pc_box[7] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000 + (1122 * 1)];
        this->pc_box[8] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000 + (1122 * 2)];
        this->pc_box[9] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000 + (1122 * 3)];
        this->pc_box[10] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000 + (1122 * 4)];
        this->pc_box[11] = (struct Structs::pkmn_box*)&this->m_rom->data[0x6000 + (1122 * 5)];
    }

	auto get_rom_size() const -> std::uint32_t
	{
		return this->m_rom->get_size();
	}

    auto save_changes(std::filesystem::path const& file_name) const -> bool
    {
        std::ofstream out;

        if (!this->m_rom) {
            return false;
        }

        out.open(file_name, std::ios::out | std::ios::binary);

        if (!out.is_open()) {
            return false;
        }

        for (auto i = 0; i < C::GEN1::SIZES::FILE; i++) {
            out.write((char*)&this->m_rom->data[i], 1);
        }

        return true;
    }

    auto get_player_name() const -> std::string
    {
        if (this->player_name == nullptr) {
            return nullptr;
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (this->player_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[this->player_name[i]];
        }

        return name;
    }
    auto set_player_name(std::string const& name) -> void
    {
        std::size_t size = name.size();

        if (this->player_name == nullptr || name.empty()) {
            return;
        }

        if (size >= 7) {
            size = 7;
        }

        for (auto i = 0; i < size; i++) {
            this->player_name[i] = this->get_character_code(name[i]);
        }

        this->player_name[++size] = 'P';

        while (size < 11) {
            this->player_name[++size] = 0x0;
        }
    }

    auto get_rival_name() const -> std::string
    {
        if (this->rival_name == nullptr) {
            return nullptr;
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (this->rival_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[this->rival_name[i]];
        }

        return name;
    }
    auto set_rival_name(std::string const& name) -> void
    {
        std::size_t size = name.size();

        if (this->rival_name == nullptr || name.empty()) {
            return;
        }

        if (size >= 7) {
            size = 7;
        }

        for (auto i = 0; i < size; i++) {
            this->rival_name[i] = this->get_character_code(name[i]);
        }

        this->rival_name[++size] = 'P';

        while (size < 11) {
            this->rival_name[++size] = 0x0;
        }
    }

    auto get_pokedex_owned_total() const -> std::uint8_t
    {
        std::uint8_t total = 0;

        for (auto i = 0; i < 151; i++) {
            if (this->get_pokedex_owned(i)) {
                total++;
            }
        }

        return total;
    }
    auto get_pokedex_owned(std::uint8_t const index) const -> bool
    {
        if (this->pokedex_owned && index < 152) {
            return (this->pokedex_owned[index >> 3] >> (index & 7) & 1) == 1;
        }

        return false;
    }
    auto set_pokedex_owned(std::uint8_t const index, bool const owned) -> void
    {
        if (owned) {
            this->pokedex_owned[index >> 3] |= 1 << (index & 7);
        } else {
            this->pokedex_owned[index >> 3] &= ~(1 << (index & 7));
        }
    }

    auto get_pokedex_seen_total() const -> std::uint8_t
    {
        std::uint8_t total = 0;

        for (auto i = 0; i < 151; i++) {
            if (this->get_pokedex_seen(i)) {
                total++;
            }
        }

        return total;
    }
    auto get_pokedex_seen(std::uint8_t const index) const -> bool
    {
        if (this->pokedex_seen && index < 152) {
            return (this->pokedex_seen[index >> 3] >> (index & 7) & 1) == 1;
        }

        return false;
    }
    auto set_pokedex_seen(std::uint8_t const index, bool const seen) -> void
    {
        if (seen) {
            this->pokedex_seen[index >> 3] |= 1 << (index & 7);
        } else {
            this->pokedex_seen[index >> 3] &= ~(1 << (index & 7));
        }
    }

    auto get_money() const -> std::uint32_t
    {
        if (!this->money) {
            return 0x7FFFFFFF;
        }

        if (this->money[1] == 0 && this->money[2] == 0) {
            return Utils::__bcd_to_dec(this->money, 1);
        } else if (this->money[1] != 0 && this->money[2] == 0) {
            return Utils::__bcd_to_dec(this->money, 2);
        }

        return Utils::__bcd_to_dec(this->money, C::GEN1::SIZES::MONEY);
    }

    auto set_money(std::uint32_t const value) -> void
    {
        if (!this->money) {
            return;
        }

        // std::uint8_t buffer[C::GEN1::SIZES::MONEY];
        std::array<std::uint8_t, C::GEN1::SIZES::MONEY> buffer;

        Utils::__dec_to_bcd(value, buffer.data());

        std::memcpy(this->money, buffer.data(), C::GEN1::SIZES::MONEY);
    }

    auto get_casino_coins() const -> std::uint16_t
    {
        if (!this->casino_coins) {
            return 0;
        }

        if (this->casino_coins[1] == 0) {
            return Utils::__bcd_to_dec(this->casino_coins, 1);
        }

        return Utils::__bcd_to_dec(this->casino_coins, C::GEN1::SIZES::CASINO_COINS);
    }

    auto set_casino_coins(std::uint16_t const value) -> void
    {
        if (!this->casino_coins) {
            return;
        }

        std::array<std::uint8_t, C::GEN1::SIZES::CASINO_COINS> buffer;

        Utils::__dec_to_bcd(value, buffer.data());

        if (Utils::n_digits(value) == 1 || Utils::n_digits(value) == 2) {
            this->casino_coins[0] = buffer[0];
            this->casino_coins[1] = 0;

            return;
        }

        std::memcpy(this->casino_coins, buffer.data(), C::GEN1::SIZES::CASINO_COINS);
    }

    auto get_time_played(struct Structs::pkmn_time* dest) const -> void
    {
        if (this->time_played && dest) {
            dest->hours = this->time_played->hours;
            dest->maxed = this->time_played->maxed;
            dest->minutes = this->time_played->minutes;
            dest->seconds = this->time_played->seconds;
            dest->frames = this->time_played->frames;

            return;
        }
    }

    auto set_time_played(std::uint8_t const hours, std::uint8_t const minutes, std::uint8_t const seconds, std::uint8_t const frames) -> void
    {
        if (hours <= 255 &&
            minutes <= 59 &&
            seconds <= 59 &&
            this->time_played) {
            this->time_played->frames = frames;
            this->time_played->seconds = seconds;
            this->time_played->minutes = minutes;
            this->time_played->hours = hours;

            if (hours == 255 && minutes == 59 && seconds == 59 && frames == 59) {
                this->time_played->maxed = 255;
            }

            return;
        }
    }

    auto get_current_pc_box() const -> std::uint8_t
    {
        if (this->current_pc_box) {
            return (current_pc_box[0] & 0b01111111) + 1;
        }

        return 0;
    }

    // TODO: set 8th bit if needed
    auto set_current_pc_box(std::uint8_t const index) -> void
    {
        std::uint8_t idx;

        if (this->current_pc_box && index <= 20) {
            if (index == 0) {
                idx = 0;
            } else {
                idx = index - 1;
            }

            this->current_pc_box[0] = idx;
        }
    }

    auto get_badge(enum Enums::badges const badge) const -> bool
    {
        if (this->badges) {
            return ((this->badges[0] & (1 << badge)) >> badge) == 1 ? true : false;
        }

        return false;
    }

    auto set_badge(enum Enums::badges const badge) -> void
    {
        if (this->badges) {
            this->badges[0] ^= (1 << badge);
        }
    }

    auto get_option(enum Enums::options const flag) const -> std::uint8_t
    {
        if (!this->options) {
            return 0;
        }

        return options[0] & C::GEN1::OPTIONS::LOOKUP_TABLE[flag];
    }

    auto set_option(enum Enums::options const flag) -> void
    {
        if (!this->options) {
            return;
        }

        Utils::set_clear_bits(&this->options[0], C::GEN1::OPTIONS::LOOKUP_TABLE[flag]);
    }

    auto get_pikachu_friendship() const -> std::uint8_t
    {
        if (this->pikachu_friendship) {
            return this->pikachu_friendship[0];
        }

        return 0;
    }

    auto set_pikachu_friendship(std::uint8_t const value) -> void
    {
        if (this->pikachu_friendship) {
            this->pikachu_friendship[0] = value;
            return;
        }
    }

    auto get_item_bag_count() const -> std::uint8_t
    {
        return this->pocket_item_list->count;
    }

    auto get_item_bag(std::uint8_t const index) const -> struct Structs::item*
    {
        if (index <= C::GEN1::SIZES::BAG_ITEM) {
            return &this->pocket_item_list->item[index];
        }

        return nullptr;
    }

    // TODO: This is not doing what it is supposed to do
    auto set_item_bag(struct Structs::item* items, std::uint8_t const index, std::uint8_t const item, std::uint8_t const count) -> void
    {
        if (index <= C::GEN1::SIZES::BAG_ITEM) {
            items[index].index = item;
            items[index].count = count;

            return;
        }
    }

    auto get_item_pc_count() const -> std::uint8_t
    {
        return this->pc_item_list->count;
    }

    auto get_item_pc(std::uint8_t const index) const -> struct Structs::item*
    {
        if (index <= C::GEN1::SIZES::PC_ITEM) {
            return &this->pc_item_list->item[index];
        }

        return nullptr;
    }

    // TODO: This is not doing what it is supposed to do
    auto set_item_pc(struct Structs::item* items, std::uint8_t const index, std::uint8_t const item, std::uint8_t const count) -> void
    {
        if (index <= C::GEN1::SIZES::PC_ITEM) {
            items[index].index = item;
            items[index].count = count;

            return;
        }
    }

    auto get_pokemon_party() const -> struct Structs::pkmn_party*
    {
        if (this->team_pokemon_list) {
            return this->team_pokemon_list;
        }

        return nullptr;
    }

    auto get_pokemon_in_party(std::uint8_t index) const -> struct Structs::pkmn_data_party*
    {
        if (this->team_pokemon_list) {
            return &this->team_pokemon_list->pokemon[index];
        }

        return nullptr;
    }

    auto get_pokemon_in_party_trainer_name(std::uint8_t index) const -> std::string
    {
        auto _name = this->team_pokemon_list->original_trainer_name[index];

        if (_name == nullptr) {
            return "";
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[_name[i]];
        }

        return name;
    }

    auto get_pokemon_in_party_name(std::uint8_t index) const -> std::string
    {
        auto _name = this->team_pokemon_list->pokemon_name[index];

        if (_name == nullptr) {
            return "";
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[_name[i]];
        }

        return name;
    }

    auto get_current_pc_box_list() const -> struct Structs::pkmn_box*
    {
        if (this->current_box_list) {
            return this->current_box_list;
        }

        return nullptr;
    }

    auto get_pokemon_in_current_box(std::uint8_t index) const -> struct Structs::pkmn_data_box*
    {
        if (this->current_box_list) {
            return &this->current_box_list->pokemon[index];
        }

        return nullptr;
    }

    auto get_pokemon_in_current_box_name(std::uint8_t index) const -> std::string
    {
        auto _name = this->current_box_list->pokemon_name[index];

        if (_name == nullptr) {
            return "";
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[_name[i]];
        }

        return name;
    }

    auto get_pokemon_box(std::uint8_t box) const -> struct Structs::pkmn_box*
    {
        if (this->pc_box[box]) {
            return this->pc_box[box];
        }

        return nullptr;
    }

    auto get_pokemon_in_box(std::uint8_t box, std::uint8_t index) const -> struct Structs::pkmn_data_box*
    {
        if (this->pc_box[box] != nullptr) {
            return &this->pc_box[box]->pokemon[index];
        }

        return nullptr;
    }

    auto get_pokemon_in_box_trainer_name(std::uint8_t box, std::uint8_t index) const -> std::string
    {
        auto _name = this->pc_box[box]->original_trainer_name[index];

        if (_name == nullptr) {
            return "";
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[_name[i]];
        }

        return name;
    }

    auto get_pokemon_in_box_name(std::uint8_t box, std::uint8_t index) const -> std::string
    {
        auto _name = this->pc_box[box]->pokemon_name[index];

        if (_name == nullptr) {
            return "";
        }

        std::string name = "";
        for (auto i = 0; i < C::GEN1::SIZES::PLAYER_NAME; i++) {
            if (_name[i] == 'P') {
                break;
            }

            name += C::GEN1::FONT[_name[i]];
        }

        return name;
    }

    auto get_character_code(std::uint8_t const c) const -> std::uint8_t
    {
        int i;

        for (i = 0; i < C::GEN1::SIZES::FONT; i++) {
            if (c == C::GEN1::FONT[i]) {
                return i;
            }
        }

        // return space code, as in, invalid character
        return 0x7F;
    }

  private:
    std::unique_ptr<Rom<T>> m_rom;

    std::uint8_t* player_name;
    std::uint8_t* pokedex_owned;
    std::uint8_t* pokedex_seen;
    std::uint8_t* money;
    std::uint8_t* rival_name;
    std::uint8_t* options;
    std::uint8_t* badges;
    std::uint8_t* pikachu_friendship;
    std::uint8_t* current_pc_box;
    std::uint8_t* casino_coins;
    std::uint8_t* item_count;
    std::uint8_t* checksum;

    std::uint16_t* player_trainer_id;

    struct Structs::items_bag* pocket_item_list;
    struct Structs::items_pc* pc_item_list;
    struct Structs::pkmn_time* time_played;
    struct Structs::pkmn_party* team_pokemon_list;
    struct Structs::pkmn_box* current_box_list;
    struct Structs::pkmn_box* pc_box[12];
};
}

#endif
