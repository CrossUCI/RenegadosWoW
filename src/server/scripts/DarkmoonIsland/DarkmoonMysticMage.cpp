/*
 * Copyright (C) 2017-2018 AshamaneProject <https://github.com/AshamaneProject>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "ScriptedGossip.h"
#include "MotionMaster.h"
#include <G3D/Quat.h>

class npc_darkmoon_faire_mystic_mage : public CreatureScript
{
public:
    npc_darkmoon_faire_mystic_mage() : CreatureScript("npc_darkmoon_faire_mystic_mage") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        char const* GOSSIP_BUTTON;
        char const* BOX_TEXT;

        switch (LocaleConstant currentlocale = player->GetSession()->GetSessionDbcLocale())
        {
            case LOCALE_esES:
            case LOCALE_esMX:
                GOSSIP_BUTTON         = "Llévame a la zona de escala de la feria.";
                BOX_TEXT              = "Viajar a la zona de escala de la feria te costará:";
                break;
            default:
                GOSSIP_BUTTON         = "<Need translate>";
                BOX_TEXT              = "<Need translate>";
                break;
        };

        AddGossipItemFor(player, 0, GOSSIP_BUTTON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, BOX_TEXT, 25, false);
        SendGossipMenuFor(player, 18269, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        if (player->HasEnoughMoney(uint64(25)))
        {
            player->ModifyMoney(uint64(-25));

            player->PlayerTalkClass->ClearMenus();
            CloseGossipMenuFor(player);

            if (player->GetTeam() == ALLIANCE)
                creature->CastSpell(player, 101260, false);
            else
                creature->CastSpell(player, 103582, false);

            return true;
        }
        else
            player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, creature, 0, 0);

        return false;
    }
};

class npc_teleportologist_fozlebub : public CreatureScript
{
public:
    npc_teleportologist_fozlebub() : CreatureScript("npc_teleportologist_fozlebub") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        char const* GOSSIP_BUTTON;
        char const* BOX_TEXT;

        switch (LocaleConstant currentlocale = player->GetSession()->GetSessionDbcLocale())
        {
            case LOCALE_esES:
            case LOCALE_esMX:
                GOSSIP_BUTTON         = "Teletranspórtame al cañón.";
                BOX_TEXT              = "El teletransporte al cañón te costará:";
                break;
            default:
                GOSSIP_BUTTON         = "<Need translate>";
                BOX_TEXT              = "<Need translate>";
                break;
        };

        AddGossipItemFor(player, 0, GOSSIP_BUTTON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, BOX_TEXT, 1000, false);
        SendGossipMenuFor(player, 23017, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        if (player->HasEnoughMoney(uint64(1000)))
        {
            player->ModifyMoney(uint64(-1000));

            player->PlayerTalkClass->ClearMenus();
            CloseGossipMenuFor(player);

            creature->CastSpell(player, 109244, false);

            return true;
        }
        else
            player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, creature, 0, 0);

        return false;
    }
};

void AddSC_darkmoon_teleport()
{
    new npc_darkmoon_faire_mystic_mage();
	new npc_darkmoon_faire_mystic_mage();
};
