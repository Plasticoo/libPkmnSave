#ifndef _PKMN_GEN1_ENUMS_HPP_
#define _PKMN_GEN1_ENUMS_HPP_

namespace Gen1
{
/** @brief Contains Generation I relevant enumerations. */
namespace Enums
{
    enum options {
        TEXT_SPEED = 0x0,
        SOUND,
        BATTLE_STYLE,
        BATTLE_EFFECTS
    };

    enum options_flags {
        TEXT_SPEED_FAST = 0x0,
        TEXT_SPEED_NORMAL,
        TEXT_SPEED_SLOW,

        SOUND_MONO,
        SOUND_MONO_Y,
        SOUND_STEREO,
        SOUND_EARPHONE1,
        SOUND_EARPHONE2,
        SOUND_EARPHONE3,

        BATTLE_STYLE_SWITCH,
        BATTLE_STYLE_SET,

        BATTLE_EFFECTS_ON,
        BATTLE_EFFECTS_OFF,
    };

    enum badges {
        BOULDER = 0x0,
        CASCADE,
        THUNDER,
        RAINBOW,
        SOUL,
        MARSH,
        VOLCANO,
        EARTH
    };

    enum pkmn_status {
        ASLEEP = 0x04,
        POISONED = 0x08,
        BURNED = 0x10,
        FROZEN = 0x20,
        PARALYZED = 0x40,
    };

    enum pkmn_type {
        NORMAL = 0x00,
        FIGHTING = 0x01,
        FLYING = 0x02,
        POISON = 0x03,
        GROUND = 0x04,
        ROCK = 0x05,
        BUG = 0x07,
        GHOST = 0x08,
        FIRE = 0x14,
        WATER = 0x15,
        GRASS = 0x16,
        ELECTRIC = 0x17,
        PSYCHIC = 0x18,
        ICE = 0x19,
        DRAGON = 0x1A,
    };

    enum item {
        NOTHING = 0x00,
        MASTER_BALL = 0x01,
        ULTRA_BALL = 0x02,
        GREAT_BALL = 0x03,
        POKE_BALL = 0x04,
        TOWN_MAP = 0x05,
        BICYCLE = 0x06,
        UNNAMED = 0x07,
        SAFARI_BALL = 0x08,
        POKEDEX = 0x09,
        MOON_STONE = 0x0A,
        ANTIDOTE = 0x0B,
        BURN_HEAL = 0x0C,
        ICE_HEAL = 0x0D,
        AWAKENING = 0x0E,
        PARLYZ_HEAL = 0x0F,
        FULL_RESTORE = 0x10,
        MAX_POTION = 0x11,
        HYPER_POTION = 0x12,
        SUPER_POTION = 0x13,
        POTION = 0x14,
        BOULDERBADGE = 0x15,
        CASCADEBADGE = 0x16,
        THUNDERBADGE = 0x17,
        RAINBOWBADGE = 0x18,
        SOULBADGE = 0x19,
        MARSHBADGE = 0x1A,
        VOLCANOBADGE = 0x1B,
        EARTHBADGE = 0x1C,
        ESCAPE_ROPE = 0x1D,
        REPEL = 0x1E,
        OLD_AMBER = 0x1F,
        FIRE_STONE = 0x20,
        THUNDER_STONE = 0x21,
        WATER_STONE = 0x22,
        HP_UP = 0x23,
        PROTEIN = 0x24,
        IRON = 0x25,
        CARBOS = 0x26,
        CALCIUM = 0x27,
        RARE_CANDY = 0x28,
        DOME_FOSSIL = 0x29,
        HELIX_FOSSIL = 0x2A,
        SECRET_KEY = 0x2B,
        UNNAMED2 = 0x2C,
        BIKE_VOUCHER = 0x2D,
        X_ACCURACY = 0x2E,
        LEAF_STONE = 0x2F,
        CARD_KEY = 0x30,
        NUGGET = 0x31,
        PP_UP_GLITCHED = 0x32,
        POKE_DOLL = 0x33,
        FULL_HEAL = 0x34,
        REVIVE = 0x35,
        MAX_REVIVE = 0x36,
        GUARD_SPEC = 0x37,
        SUPER_REPEL = 0x38,
        MAX_REPEL = 0x39,
        DIRE_HIT = 0x3A,
        COIN = 0x3B,
        FRESH_WATER = 0x3C,
        SODA_POP = 0x3D,
        LEMONADE = 0x3E,
        SS_TICKET = 0x3F,
        GOLD_TEETH = 0x40,
        X_ATTACK = 0x41,
        X_DEFEND = 0x42,
        X_SPEED = 0x43,
        X_SPECIAL = 0x44,
        COIN_CASE = 0x45,
        OAKS_PARCEL = 0x46,
        ITEMFINDER = 0x47,
        SILPH_SCOPE = 0x48,
        POKE_FLUTE = 0x49,
        LIFT_KEY = 0x4A,
        EXP_ALL = 0x4B,
        OLD_ROD = 0x4C,
        GOOD_ROD = 0x4D,
        SUPER_ROD = 0x4E,
        PP_UP = 0x4F,
        ETHER = 0x50,
        MAX_ETHER = 0x51,
        ELIXER = 0x52,
        MAX_ELIXER = 0x53,
        HM01 = 0xC4,
        HM02 = 0xC5,
        HM03 = 0xC6,
        HM04 = 0xC7,
        HM05 = 0xC8,
        TM01 = 0xC9,
        TM02 = 0xCA,
        TM03 = 0xCB,
        TM04 = 0xCC,
        TM05 = 0xCD,
        TM06 = 0xCE,
        TM07 = 0xCF,
        TM08 = 0xD0,
        TM09 = 0xD1,
        TM10 = 0xD2,
        TM11 = 0xD3,
        TM12 = 0xD4,
        TM13 = 0xD5,
        TM14 = 0xD6,
        TM15 = 0xD7,
        TM16 = 0xD8,
        TM17 = 0xD9,
        TM18 = 0xDA,
        TM19 = 0xDB,
        TM20 = 0xDC,
        TM21 = 0xDD,
        TM22 = 0xDE,
        TM23 = 0xDF,
        TM24 = 0xE0,
        TM25 = 0xE1,
        TM26 = 0xE2,
        TM27 = 0xE3,
        TM28 = 0xE4,
        TM29 = 0xE5,
        TM30 = 0xE6,
        TM31 = 0xE7,
        TM32 = 0xE8,
        TM33 = 0xE9,
        TM34 = 0xEA,
        TM35 = 0xEB,
        TM36 = 0xEC,
        TM37 = 0xED,
        TM38 = 0xEE,
        TM39 = 0xEF,
        TM40 = 0xF0,
        TM41 = 0xF1,
        TM42 = 0xF2,
        TM43 = 0xF3,
        TM44 = 0xF4,
        TM45 = 0xF5,
        TM46 = 0xF6,
        TM47 = 0xF7,
        TM48 = 0xF8,
        TM49 = 0xF9,
        TM50 = 0xFA,
        TM51 = 0xFB,
        TM52 = 0xFC,
        TM53 = 0xFD,
        TM54 = 0xFE,
        TM55 = 0xFF,
    };
}
}

#endif
