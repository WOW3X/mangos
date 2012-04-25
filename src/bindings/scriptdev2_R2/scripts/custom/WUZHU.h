#include "sc_gossip.h"
#include "SharedDefines.h"
#include "Item.h"
#include "sc_creature.h"
#include "SpellMgr.h"
#include "Spell.h"
 
#define SEND_NOTIFICATION(a)      GetSession()->SendNotification(a) 	//��Ϸ��������ĶԻ�
#define isbl(p)  ((p)->getRace() == RACE_ORC||(p)->getRace()== RACE_UNDEAD||(p)->getRace() == RACE_TAUREN||(p)->getRace() == RACE_TROLL||(p)->getRace() == RACE_BLOODELF)
#define isstone(p)  ((p)->isInCombat()||(p)->IsTaxiFlying()||(p)->IsMounted())
#define isTrainer(p)  ((p)->getClass() == 1||(p)->getClass()== 2||(p)->getClass()== 3)

#define Max_BindCount		15//������ ���ܴ���16
#define Cost_MainCity		1000 
#define Cost_Level_1_Copy	10000
#define Cost_Level_2_Copy	20000
#define Cost_Level_3_Copy	30000
#define Cost_Level_1_TBCCopy	50000
#define Cost_Level_2_TBCCopy	60000
#define Cost_Level_3_TBCCopy	100000
#define Cost_Raid			1000000
#define Cost_Extent_Copy 10000 
#define Cost_Extent_Boss_Copy 100000
#define Cost_Boss	50000
#define Cost_Taxi	100000
#define Cost_BOXMessage_ID (WUZHU_TEXT_SOURCE_RANGE-1)//" ʹ�ô˹��ܽ�����G "

#define WP_YXWZID 40752//Ӣ�����µ�ID
#define WP_YQWZID 40753//�������µ�ID
#define WP_JFBID 820922//���ֱҵ�ID 

#define SFM_BL_XJN1	35018
#define SFM_BL_NTR1	18989
#define SFM_BL_SR1	6654
#define SFM_BL_WN1	17463
#define SFM_BL_JM1	10799

#define SFM_BL_XJN20	33660
#define SFM_BL_NTR20	23247
#define SFM_BL_SR20		23251
#define SFM_BL_WN20		23246
#define SFM_BL_JM20		23243

#define SFM_BL20	22721
#define SFM_BL40	32244
#define SFM_BL60	41513

#define SFM_LM_RL1	6648
#define SFM_LM_AR1	6898
#define SFM_LM_ZR1	10873
#define SFM_LM_JL1	10793
#define SFM_LM_DLN1	35711

#define SFM_LM_RL20	23228
#define SFM_LM_AR20	23240
#define SFM_LM_ZR20	23223
#define SFM_LM_JL20	23221
#define SFM_LM_DLN20	35714

#define SFM_LM20	22723
#define SFM_LM40	32240
#define SFM_LM60	39800
#define SFM_LMBL70_1 37015
#define SFM_LMBL70_2 32345
#define UPLevelIntegral 300 //������Ҫ�Ļ���
#define UPSkillIntegral_10 3000//������������Ҫ�Ļ���
#define UPSkillIntegral_50 10000//������������Ҫ�Ļ���
#define WUZHU_Wages_Money 10000//���߹���

//�ο�\game\Item.cpp uint32 Item::GetSkill() ȥ�����㼼��
const static uint32 item_weapon_skills[MAX_ITEM_SUBCLASS_WEAPON] =
{
	SKILL_AXES,     SKILL_2H_AXES,  SKILL_BOWS,          SKILL_GUNS,      SKILL_MACES,
	SKILL_2H_MACES, SKILL_POLEARMS, SKILL_SWORDS,        SKILL_2H_SWORDS, 0,
	SKILL_STAVES,   0,              0,                   SKILL_UNARMED,   0,
	SKILL_DAGGERS,  SKILL_THROWN,   SKILL_ASSASSINATION, SKILL_CROSSBOWS, SKILL_WANDS,
	0//SKILL_FISHING
};

class WUZHU_Common
{
public:
	//���ͽ�Ҳ������Ϣ
	void static SendMoneyError(Player *pPlayer)
	{
		if(!pPlayer||!pPlayer->GetSession())
			return;
		pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-2,pPlayer));//" |cffff0000��Ľ�Ǯ����.|r ");
	}

	bool static WZ_UpdateSkill(Player *pPlayer,uint32 skill,uint32 setp)
	{
		if(!pPlayer||!skill)
			return false;
		uint16 nowskillvalue=pPlayer->GetSkillValue(skill);//��ǰ���ܶ��ٵ�
		if(!nowskillvalue)
			return false;
		uint16 maxskillvalue=pPlayer->GetPureMaxSkillValue(skill);//�ܴﵽ�����ٵ�
		if(maxskillvalue==nowskillvalue)
			return false;
		int32 level=nowskillvalue+setp;
		if(level>maxskillvalue)
			level=maxskillvalue;
		if(level<0||maxskillvalue<0)
			return false;
		pPlayer->SetSkill(skill, level, maxskillvalue);
		return true;
	}


};



