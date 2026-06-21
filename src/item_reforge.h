/*
 * Credits: silviu20092
 */

#ifndef _ITEM_REFORGE_H_
#define _ITEM_REFORGE_H_

#include "Define.h"

class ItemReforge
{
public:
    struct ReforgingData
    {
        uint32 guid;
        uint32 item_guid;
        uint32 stat_decrease;
        uint32 stat_increase;
        uint32 stat_value;
    };

    struct CostConfig
    {
        uint32 currencyEntry;  // 0 = gold, otherwise token item entry
        int32 amount;           // cost in copper (for gold) or token count
    };

private:
    static constexpr float PERCENTAGE_MIN = 10.0f;
    static constexpr float PERCENTAGE_MAX = 90.0f;
    static constexpr const char* RED_COLOR = "b50505";
    static constexpr const char* GREEN_COLOR = "056e3a";
    static constexpr uint32 MAX_REFORGEABLE_STATS = 15;
    static constexpr uint32 MAX_QUALITY_LEVELS = 6; // 0=poor to 5=legendary
    static constexpr uint32 MAX_EQUIPMENT_SLOTS = 19; // EQUIPMENT_SLOT_START to EQUIPMENT_SLOT_END = 19 slots
    
    bool enabled;
    bool costEnabled;
    std::vector<uint32> reforgeableStats;
    float percentage;

    // Cost per quality: costPerQuality[quality] = CostConfig
    CostConfig costPerQuality[MAX_QUALITY_LEVELS];
    // Per-slot currency override (0 = no override, use costPerQuality's currency)
    uint32 slotCurrencyOverride[MAX_EQUIPMENT_SLOTS];

    // Menu text strings
    std::string textStatsHeader;
    std::string textNone;
    std::string textNoItem;
    std::string textAlreadyReforged;
    std::string textNotReforgeable;
    std::string textReforgeable;
    std::string textGoBack;
    std::string textNoItemInSlot;
    std::string textAlreadyReforgedMsg;
    std::string textNotReforgeableMsg;
    std::string textReforge;
    std::string textWillTake;
    std::string textValueAfter;
    std::string textConfirmReforge;
    std::string textReforged;
    std::string textNotReforged;
    std::string textRestore;
    std::string textConfirmRestore;
    std::string textNotAvailable;
    std::string textSelectSlot;
    std::string textRemoveReforge;
    std::string textNevermind;
    std::string textReforgeFail;
    std::string textCostInsufficient;
    std::string textCostInfo;

    // Slot name strings
    std::string slotNames[MAX_EQUIPMENT_SLOTS];

    // Stat type name strings (configurable, fallback to hardcoded English)
    std::unordered_map<uint32, std::string> statTypeNames;

	ItemReforge();
	~ItemReforge();

	typedef std::unordered_map<uint32, ReforgingData> ReforgingDataContainer;

    ReforgingDataContainer reforgingDataMap;

    void CleanupDB() const;

    static std::string TextWithColor(const std::string& text, const std::string& color);
public:
    static constexpr const char* DefaultReforgeableStats = "6,13,14,31,32,36,37";
    static constexpr float PERCENTAGE_DEFAULT = 40.0f;
    static constexpr int VISUAL_FEEDBACK_SPELL_ID = 46331;

	static ItemReforge* instance();

    void SetEnabled(bool value);
    bool GetEnabled() const;
    void SetReforgeableStats(const std::string& stats);
    bool IsReforgeableStat(uint32 stat) const;
    const std::vector<uint32>& GetReforgeableStats() const;
    void SetPercentage(float value);
    float GetPercentage() const;

    void SetCostEnabled(bool value);
    bool IsCostEnabled() const;
    void SetQualityCost(uint32 quality, uint32 currencyEntry, int32 amount);
    CostConfig GetQualityCost(uint32 quality) const;
    void SetSlotCurrencyOverride(uint8 slot, uint32 currencyEntry);
    uint32 GetSlotCurrencyForItem(const Item* item) const;

    // Config text setters/getters
    #define DEFINE_TEXT_ACCESSOR(NAME) \
        void Set##NAME(const std::string& val) { NAME = val; } \
        const std::string& Get##NAME() const { return NAME; }

    DEFINE_TEXT_ACCESSOR(textStatsHeader)
    DEFINE_TEXT_ACCESSOR(textNone)
    DEFINE_TEXT_ACCESSOR(textNoItem)
    DEFINE_TEXT_ACCESSOR(textAlreadyReforged)
    DEFINE_TEXT_ACCESSOR(textNotReforgeable)
    DEFINE_TEXT_ACCESSOR(textReforgeable)
    DEFINE_TEXT_ACCESSOR(textGoBack)
    DEFINE_TEXT_ACCESSOR(textNoItemInSlot)
    DEFINE_TEXT_ACCESSOR(textAlreadyReforgedMsg)
    DEFINE_TEXT_ACCESSOR(textNotReforgeableMsg)
    DEFINE_TEXT_ACCESSOR(textReforge)
    DEFINE_TEXT_ACCESSOR(textWillTake)
    DEFINE_TEXT_ACCESSOR(textValueAfter)
    DEFINE_TEXT_ACCESSOR(textConfirmReforge)
    DEFINE_TEXT_ACCESSOR(textReforged)
    DEFINE_TEXT_ACCESSOR(textNotReforged)
    DEFINE_TEXT_ACCESSOR(textRestore)
    DEFINE_TEXT_ACCESSOR(textConfirmRestore)
    DEFINE_TEXT_ACCESSOR(textNotAvailable)
    DEFINE_TEXT_ACCESSOR(textSelectSlot)
    DEFINE_TEXT_ACCESSOR(textRemoveReforge)
    DEFINE_TEXT_ACCESSOR(textNevermind)
    DEFINE_TEXT_ACCESSOR(textReforgeFail)
    DEFINE_TEXT_ACCESSOR(textCostInsufficient)
    DEFINE_TEXT_ACCESSOR(textCostInfo)
    #undef DEFINE_TEXT_ACCESSOR

    void SetSlotName(uint8 slot, const std::string& name);
    void SetStatTypeName(uint32 statType, const std::string& name);
    std::string GetSlotIcon(uint8 slot, uint32 width = 30, uint32 height = 30, int x = 0, int y = 0) const;
    std::string GetSlotName(uint8 slot) const;
    std::string StatTypeToString(uint32 statType) const;

    bool IsReforgeable(const Player* player, const Item* item) const;
    bool IsAlreadyReforged(const Item* item) const;
    Item* GetItemInSlot(const Player* player, uint8 slot) const;
    uint32 CalculateReforgePct(int32 value) const;
    std::vector<_ItemStat> LoadItemStatInfo(const Item* item, bool onlyReforgeable = false) const;
    const _ItemStat* FindItemStat(const std::vector<_ItemStat>& stats, uint32 statType) const;

    bool CanAffordReforge(Player* player, const Item* item) const;
    std::string GetCostDescription(const Item* item) const;
    void ChargeReforgeCost(Player* player, const Item* item) const;

    bool Reforge(Player* player, ObjectGuid itemGuid, uint32 statDecrease, uint32 statIncrease);
    void SendItemPacket(Player* player, const Item* item) const;
    void SendItemPackets(Player* player) const;
    void HandleReload(Player* player, bool apply) const;
    void HandleReload(bool apply) const;
    const ReforgingData* GetReforgingData(const Item* item) const;
    std::vector<Item*> GetPlayerItems(const Player* player, bool inBankAlso) const;
    bool CanRemoveReforge(const Item* item) const;
    bool RemoveReforge(Player* player, ObjectGuid itemGuid);
    bool RemoveReforge(Player* player, Item* item);
    void VisualFeedback(Player* player);
    void HandleCharacterRemove(uint32 guid);

    void HandleStatModifier(Player* player, uint32 statType, int32 val, bool apply);

    static void SendMessage(Player* player, const std::string& message);
    static std::string TextRed(const std::string& text);
    static std::string TextGreen(const std::string& text);
    static std::string ItemIcon(const ItemTemplate* proto, uint32 width = 30, uint32 height = 30, int x = 0, int y = 0);
    static std::string ItemNameWithLocale(const Player* player, const ItemTemplate* itemTemplate, int32 randomPropertyId);
    static std::string ItemLink(const Player* player, const ItemTemplate* itemTemplate, int32 randomPropertyId);
    static std::string ItemLinkForUI(const Item* item, const Player* player);
};

#define sItemReforge ItemReforge::instance()

#endif
