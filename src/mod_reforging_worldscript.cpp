/*
 * Credits: silviu20092
 */

#include "ScriptMgr.h"
#include "Config.h"
#include "Player.h"
#include "item_reforge.h"

class mod_reforging_worldscript : public WorldScript
{
public:
    mod_reforging_worldscript() : WorldScript("mod_reforging_worldscript",
        {
            WORLDHOOK_ON_AFTER_CONFIG_LOAD,
            WORLDHOOK_ON_BEFORE_WORLD_INITIALIZED
        }) {}

    void OnAfterConfigLoad(bool reload) override
    {
        bool reforgeEnableChanged = reload && sItemReforge->GetEnabled() != sConfigMgr->GetOption<bool>("Reforging.Enable", true);
        if (reforgeEnableChanged)
            sItemReforge->HandleReload(false);

        sItemReforge->SetEnabled(sConfigMgr->GetOption<bool>("Reforging.Enable", true));
        sItemReforge->SetReforgeableStats(sConfigMgr->GetOption<std::string>("Reforging.ReforgeableStats", ItemReforge::DefaultReforgeableStats));
        sItemReforge->SetPercentage(sConfigMgr->GetOption<float>("Reforging.Percentage", ItemReforge::PERCENTAGE_DEFAULT));

        // Cost system - per slot
        sItemReforge->SetCostEnabled(sConfigMgr->GetOption<bool>("Reforging.Cost.Enable", false));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_HEAD,      sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Head.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Head.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_NECK,      sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Neck.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Neck.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_SHOULDERS, sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Shoulders.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Shoulders.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_BODY,      sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Shirt.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Shirt.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_CHEST,     sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Chest.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Chest.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_WAIST,     sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Waist.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Waist.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_LEGS,      sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Legs.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Legs.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_FEET,      sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Feet.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Feet.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_WRISTS,    sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Wrists.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Wrists.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_HANDS,     sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Hands.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Hands.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_FINGER1,   sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Finger1.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Finger1.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_FINGER2,   sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Finger2.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Finger2.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_TRINKET1,  sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Trinket1.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Trinket1.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_TRINKET2,  sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Trinket2.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Trinket2.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_BACK,      sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Back.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Back.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_MAINHAND,  sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.MainHand.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.MainHand.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_OFFHAND,   sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.OffHand.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.OffHand.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_RANGED,    sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Ranged.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Ranged.Amount", 0));
        sItemReforge->SetSlotCost(EQUIPMENT_SLOT_TABARD,    sConfigMgr->GetOption<uint32>("Reforging.Cost.Slot.Tabard.Currency", 0), sConfigMgr->GetOption<int32>("Reforging.Cost.Slot.Tabard.Amount", 0));

        // Menu text
        sItemReforge->SettextStatsHeader(sConfigMgr->GetOption<std::string>("Reforging.Text.StatsHeader", "可重铸属性: "));
        sItemReforge->SettextNone(sConfigMgr->GetOption<std::string>("Reforging.Text.None", "无"));
        sItemReforge->SettextNoItem(sConfigMgr->GetOption<std::string>("Reforging.Text.NoItem", "无物品"));
        sItemReforge->SettextAlreadyReforged(sConfigMgr->GetOption<std::string>("Reforging.Text.AlreadyReforged", "已重铸"));
        sItemReforge->SettextNotReforgeable(sConfigMgr->GetOption<std::string>("Reforging.Text.NotReforgeable", "不可重铸"));
        sItemReforge->SettextReforgeable(sConfigMgr->GetOption<std::string>("Reforging.Text.Reforgeable", "可重铸"));
        sItemReforge->SettextGoBack(sConfigMgr->GetOption<std::string>("Reforging.Text.GoBack", "返回"));
        sItemReforge->SettextNoItemInSlot(sConfigMgr->GetOption<std::string>("Reforging.Text.NoItemInSlot", "该槽位没有装备物品。"));
        sItemReforge->SettextAlreadyReforgedMsg(sConfigMgr->GetOption<std::string>("Reforging.Text.AlreadyReforgedMsg", "该物品已经重铸过了。"));
        sItemReforge->SettextNotReforgeableMsg(sConfigMgr->GetOption<std::string>("Reforging.Text.NotReforgeableMsg", "该物品不可重铸。"));
        sItemReforge->SettextReforge(sConfigMgr->GetOption<std::string>("Reforging.Text.Reforge", "重铸 "));
        sItemReforge->SettextWillTake(sConfigMgr->GetOption<std::string>("Reforging.Text.WillTake", "将从 "));
        sItemReforge->SettextValueAfter(sConfigMgr->GetOption<std::string>("Reforging.Text.ValueAfter", " 重铸后的值: "));
        sItemReforge->SettextConfirmReforge(sConfigMgr->GetOption<std::string>("Reforging.Text.ConfirmReforge", "你确定要重铸这件物品吗？"));
        sItemReforge->SettextReforged(sConfigMgr->GetOption<std::string>("Reforging.Text.Reforged", "已重铸"));
        sItemReforge->SettextNotReforged(sConfigMgr->GetOption<std::string>("Reforging.Text.NotReforged", "未重铸"));
        sItemReforge->SettextRestore(sConfigMgr->GetOption<std::string>("Reforging.Text.Restore", "[还原]"));
        sItemReforge->SettextConfirmRestore(sConfigMgr->GetOption<std::string>("Reforging.Text.ConfirmRestore", "你确定吗？"));
        sItemReforge->SettextNotAvailable(sConfigMgr->GetOption<std::string>("Reforging.Text.NotAvailable", "不可用"));
        sItemReforge->SettextSelectSlot(sConfigMgr->GetOption<std::string>("Reforging.Text.SelectSlot", "选择要重铸的装备栏位"));
        sItemReforge->SettextRemoveReforge(sConfigMgr->GetOption<std::string>("Reforging.Text.RemoveReforge", "移除物品的重铸"));
        sItemReforge->SettextNevermind(sConfigMgr->GetOption<std::string>("Reforging.Text.Nevermind", "算了"));
        sItemReforge->SettextReforgeFail(sConfigMgr->GetOption<std::string>("Reforging.Text.ReforgeFail", "无法重铸物品，请重试。"));
        sItemReforge->SettextCostInsufficient(sConfigMgr->GetOption<std::string>("Reforging.Text.CostInsufficient", "你没有足够的货币来重铸这件物品。"));
        sItemReforge->SettextCostInfo(sConfigMgr->GetOption<std::string>("Reforging.Text.CostInfo", "重铸花费: "));

        // Load slot names
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_HEAD,      sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Head", "头部"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_NECK,      sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Neck", "颈部"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_SHOULDERS, sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Shoulders", "肩部"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_BODY,      sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Shirt", "衬衣"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_CHEST,     sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Chest", "胸部"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_WAIST,     sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Waist", "腰部"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_LEGS,      sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Legs", "腿部"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_FEET,      sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Feet", "脚部"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_WRISTS,    sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Wrists", "手腕"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_HANDS,     sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Hands", "手套"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_FINGER1,   sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Finger1", "手指1"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_FINGER2,   sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Finger2", "手指2"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_TRINKET1,  sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Trinket1", "饰品1"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_TRINKET2,  sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Trinket2", "饰品2"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_BACK,      sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Back", "背部"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_MAINHAND,  sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.MainHand", "主手"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_OFFHAND,   sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.OffHand", "副手"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_RANGED,    sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Ranged", "远程"));
        sItemReforge->SetSlotName(EQUIPMENT_SLOT_TABARD,    sConfigMgr->GetOption<std::string>("Reforging.Text.Slot.Tabard", "战袍"));

        // Load stat type names
        sItemReforge->SetStatTypeName(ITEM_MOD_MANA,                    sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.Mana", "法力值"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HEALTH,                  sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.Health", "生命值"));
        sItemReforge->SetStatTypeName(ITEM_MOD_AGILITY,                 sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.Agility", "敏捷"));
        sItemReforge->SetStatTypeName(ITEM_MOD_STRENGTH,                sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.Strength", "力量"));
        sItemReforge->SetStatTypeName(ITEM_MOD_INTELLECT,              sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.Intellect", "智力"));
        sItemReforge->SetStatTypeName(ITEM_MOD_SPIRIT,                 sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.Spirit", "精神"));
        sItemReforge->SetStatTypeName(ITEM_MOD_STAMINA,                sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.Stamina", "耐力"));
        sItemReforge->SetStatTypeName(ITEM_MOD_DEFENSE_SKILL_RATING,   sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.DefenseRating", "防御等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_DODGE_RATING,           sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.DodgeRating", "躲闪等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_PARRY_RATING,           sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.ParryRating", "招架等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_BLOCK_RATING,           sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.BlockRating", "格挡等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HIT_MELEE_RATING,       sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.MeleeHitRating", "近战命中等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HIT_RANGED_RATING,      sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.RangedHitRating", "远程命中等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HIT_SPELL_RATING,       sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.SpellHitRating", "法术命中等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_CRIT_MELEE_RATING,      sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.MeleeCritRating", "近战暴击等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_CRIT_RANGED_RATING,     sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.RangedCritRating", "远程暴击等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_CRIT_SPELL_RATING,      sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.SpellCritRating", "法术暴击等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HIT_TAKEN_MELEE_RATING, sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.MeleeHitTakenRating", "近战命中减免等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HIT_TAKEN_RANGED_RATING,sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.RangedHitTakenRating", "远程命中减免等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HIT_TAKEN_SPELL_RATING, sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.SpellHitTakenRating", "法术命中减免等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_CRIT_TAKEN_MELEE_RATING,sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.MeleeCritTakenRating", "近战暴击减免等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_CRIT_TAKEN_RANGED_RATING,sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.RangedCritTakenRating", "远程暴击减免等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_CRIT_TAKEN_SPELL_RATING,sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.SpellCritTakenRating", "法术暴击减免等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HASTE_MELEE_RATING,     sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.MeleeHasteRating", "近战急速等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HASTE_RANGED_RATING,    sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.RangedHasteRating", "远程急速等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HASTE_SPELL_RATING,     sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.SpellHasteRating", "法术急速等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HIT_RATING,             sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.HitRating", "命中等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_CRIT_RATING,            sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.CritRating", "暴击等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HIT_TAKEN_RATING,       sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.HitTakenRating", "命中减免等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_CRIT_TAKEN_RATING,      sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.CritTakenRating", "暴击减免等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_RESILIENCE_RATING,      sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.ResilienceRating", "韧性等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HASTE_RATING,           sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.HasteRating", "急速等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_EXPERTISE_RATING,       sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.ExpertiseRating", "精准等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_ATTACK_POWER,           sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.AttackPower", "攻击强度"));
        sItemReforge->SetStatTypeName(ITEM_MOD_RANGED_ATTACK_POWER,    sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.RangedAttackPower", "远程攻击强度"));
        sItemReforge->SetStatTypeName(ITEM_MOD_MANA_REGENERATION,      sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.ManaRegen", "法力回复"));
        sItemReforge->SetStatTypeName(ITEM_MOD_ARMOR_PENETRATION_RATING,sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.ArmorPenetration", "护甲穿透等级"));
        sItemReforge->SetStatTypeName(ITEM_MOD_SPELL_POWER,            sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.SpellPower", "法术强度"));
        sItemReforge->SetStatTypeName(ITEM_MOD_HEALTH_REGEN,           sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.HealthRegen", "生命回复"));
        sItemReforge->SetStatTypeName(ITEM_MOD_SPELL_PENETRATION,      sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.SpellPenetration", "法术穿透"));
        sItemReforge->SetStatTypeName(ITEM_MOD_BLOCK_VALUE,            sConfigMgr->GetOption<std::string>("Reforging.Text.Stat.BlockValue", "格挡值"));

        if (reforgeEnableChanged)
            sItemReforge->HandleReload(true);
    }

    void OnBeforeWorldInitialized() override
    {
        sItemReforge->LoadFromDB();
    }
};

void AddSC_mod_reforging_worldscript()
{
    new mod_reforging_worldscript();
}
