#pragma once
#include <map>
#include <mutex>
#include <atomic>

struct GA_Character;
struct GW_SkillRecord;
class SkillEntry;

#define PARSE_SKILLDATA(attribute) ((std::string)skillCommonImg[#attribute]) == "" ? 0 : (int)evaluator.Eval(((std::string)skillCommonImg[#attribute]), "", d);
#define PARSE_SKILLDATA_STRING(attribute) #attribute == "" ? 0 : (int)evaluator.Eval(#attribute, "", d);

class SkillInfo
{
	std::atomic<int> m_nOnLoadingSkills;
	std::mutex m_mtxSkillResLock;
	std::map<int, std::map<int, SkillEntry*> *> m_mSkillByRootID;

public:
	SkillInfo();
	~SkillInfo();

	int GetLoadingSkillCount() const;


	const std::map<int, std::map<int, SkillEntry*> *>& GetSkills() const;
	const std::map<int, SkillEntry*> * GetSkillsByRootID(int nRootID) const;
	const SkillEntry* GetSkillByID(int nSkillID) const;

	static SkillInfo* GetInstance();
	int GetBundleItemMaxPerSlot(int nItemID, GA_Character* pCharacterData);
	void IterateSkillInfo();
	void LoadSkillRoot(int nSkillRootID, void* pData);
	SkillEntry* LoadSkill(int nSkillRootID, int nSkillID, void* pData);
	void LoadLevelData(int nSkillID, SkillEntry* pEntry, void* pData);
	void LoadLevelDataByLevelNode(int nSkillID, SkillEntry* pEntry, void* pData);
	void LoadLevelDataSpecial();
	int GetSkillLevel(GA_Character* pCharacter, int nSkillID, SkillEntry** pEntry, int bNoPvPLevelCheck, int bPureStealSLV, int bNotApplySteal, int bCheckSkillRoot);

	GW_SkillRecord* GetSkillRecord(int nSkillID, int nSLV, long long int tExpired);
};

