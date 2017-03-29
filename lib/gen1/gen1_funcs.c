#include "../../include/gen1/gen1.h"

#include <stdlib.h>

u8 gen1_checksum_file(FILE* f)
{
    int i;

    u8 checksum = 0;
    u8 byte;

    fseek(f, CHECKSUM_INIT_OFFSET, SEEK_SET);

    for (i = 0; i <= CHECKSUM_END_OFFSET - CHECKSUM_INIT_OFFSET; i++) {
        fread(&byte, 1, 1, f);
        checksum += byte;
    }

    return ~checksum;
}

u8 gen1_checksum_map(u8 *file_map)
{
    int i;

    u8 checksum = 0;

    for (i = CHECKSUM_INIT_OFFSET; i <= CHECKSUM_END_OFFSET; i++) {
        checksum += file_map[i];
    }

    return ~checksum;
}

u8* load_file(FILE* f)
{
    int i;

    u8* file_map = calloc(FILE_SIZE, sizeof(u8));

    fseek(f, 0L, SEEK_SET);

    for (i = 0; i < FILE_SIZE; i++) {
        fread(&file_map[i], 1, 1, f);
    }

    return file_map;
}

void gen1_load_file(struct gen1_pkmn_file_struct* file_struct)
{
    u8  i, j;
    u32 pokemon_list_offset = TEAM_POKEMON_LIST_ADDRESS;
    u32 pokemon_list_data_offset = TEAM_POKEMON_LIST_ADDRESS + 0x8;

    u32 pc_box_offset;
    u32 pc_box_data_offset;

    file_struct->player_name = &file_struct->file_map[PLAYER_NAME_ADDRESS];
    file_struct->pokedex_owned = &file_struct->file_map[POKEDEX_OWNED_ADDRESS];
    file_struct->pokedex_seen = &file_struct->file_map[POKEDEX_SEEN_ADDRESS];
    file_struct->pocket_items = (struct gen1_pocket_item_list*)&file_struct->file_map[POCKET_ITEM_LIST_ADDRESS];
    file_struct->money = &file_struct->file_map[MONEY_ADDRESS];
    file_struct->rival_name = &file_struct->file_map[RIVAL_NAME_ADDRESS];
    file_struct->options = &file_struct->file_map[OPTIONS_ADDRESS];
    file_struct->badges = &file_struct->file_map[BADGES_ADDRESS];
    file_struct->player_trainer_id = (u16*)&file_struct->file_map[PLAYER_TRAINER_ID_ADDRESS];
    file_struct->pikachu_friendship = &file_struct->file_map[PIKACHU_FRIENDSHIP_ADDRESS];
    file_struct->pc_item_list = &file_struct->file_map[PC_ITEM_LIST_ADDRESS];
    file_struct->current_pc_box = &file_struct->file_map[CURRENT_PC_BOX_ADDRESS];
    file_struct->casino_coins = &file_struct->file_map[CASINO_COINS_ADDRESS];
    file_struct->time_played = (struct gen1_pkmn_time*)&file_struct->file_map[TIME_PLAYED_ADDRESS];
    file_struct->current_box_list = &file_struct->file_map[CURRENT_BOX_POKEMON_LIST_ADDRESS];
    file_struct->checksum = &file_struct->file_map[CHECKSUM_ADDRESS];

    file_struct->team_pokemon_list = (struct gen1_pkmn_data_struct*)&file_struct->file_map[TEAM_POKEMON_LIST_ADDRESS];

    // load pc boxes
    // TODO define offsets
    for (i = 0; i < PC_BOX_NUMBER; i++) {
        file_struct->pc_box[i] = calloc(1, sizeof(struct gen1_pkmn_box));

        for (j = 0; j < PC_BOX_SIZE; j++) {
            file_struct->pc_box[i]->pokemon_list[j]              = calloc(1, sizeof(struct gen1_pkmn_data_struct));

            file_struct->pc_box[i]->pokemon_list[j]->name        = &file_struct->file_map[pokemon_list_offset + POKEMON_NAME_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->ot_name     = &file_struct->file_map[pokemon_list_offset + POKEMON_OT_NAME_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->index       = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + INDEX_NR_SPECIES_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->hp          = (u16*)&file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + CURRENT_HP_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->level       = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + LEVEL_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->status      = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + STATUS_CONDITION_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->type[0]     = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + TYPE_1_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->type[1]     = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + TYPE_2_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->catch_item  = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + CATCH_ITEM_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->moves[0]    = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_1_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->moves[1]    = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_2_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->moves[2]    = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_3_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->moves[3]    = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_4_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->trainer_id  = (u16*)&file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + TRAINER_ID_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->xp[0]       = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + XP_POINTS_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->xp[1]       = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + XP_POINTS_OFFSET + 1];
            file_struct->pc_box[i]->pokemon_list[j]->xp[2]       = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + XP_POINTS_OFFSET + 2];
            file_struct->pc_box[i]->pokemon_list[j]->hp_ev       = (u16*)&file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + HP_EV_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->atk_ev      = (u16*)&file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + ATTACK_EV_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->def_ev      = (u16*)&file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + DEFENSE_EV_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->speed_ev    = (u16*)&file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + SPEED_EV_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->special_ev  = (u16*)&file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + SPECIAL_EV_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->iv          = (u16*)&file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + IV_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->moves_pp[0] = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_1_PP_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->moves_pp[1] = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_2_PP_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->moves_pp[2] = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_3_PP_OFFSET];
            file_struct->pc_box[i]->pokemon_list[j]->moves_pp[3] = &file_struct->file_map[pokemon_list_offset + pokemon_list_data_offset + MOVE_4_PP_OFFSET];

            file_struct->pc_box[i]->pokemon_list[j]->level_opt   = file_struct->pc_box[i]->pokemon_list[j]->level;
            file_struct->pc_box[i]->pokemon_list[j]->max_hp      = file_struct->pc_box[i]->pokemon_list[j]->hp;
            file_struct->pc_box[i]->pokemon_list[j]->atk         = NULL;
            file_struct->pc_box[i]->pokemon_list[j]->def         = NULL;
            file_struct->pc_box[i]->pokemon_list[j]->speed       = NULL;
            file_struct->pc_box[i]->pokemon_list[j]->special     = NULL;

            /* pokemon_list_offset += 44; */
            /* pokemon_list_data_offset += TEAM_POKEMON_LIST_ADDRESS; */
        }
    }
}
