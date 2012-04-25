/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
* This program is free software licensed under GPL version 2
* Please see the included DOCS/LICENSE.TXT for more information */

#ifndef SC_SYSTEM_H
#define SC_SYSTEM_H

extern DatabaseType SD2Database;
extern std::string  strSD2Version;                          //version info: database entry and revision

#define TEXT_SOURCE_RANGE -1000000                          //the amount of entries each text source has available

#define TEXT_SOURCE_TEXT_START      TEXT_SOURCE_RANGE
#define TEXT_SOURCE_TEXT_END        TEXT_SOURCE_RANGE*2 + 1

#define TEXT_SOURCE_CUSTOM_START    TEXT_SOURCE_RANGE*2
#define TEXT_SOURCE_CUSTOM_END      TEXT_SOURCE_RANGE*3 + 1

#define TEXT_SOURCE_GOSSIP_START    TEXT_SOURCE_RANGE*3
#define TEXT_SOURCE_GOSSIP_END      TEXT_SOURCE_RANGE*4 + 1

struct ScriptPointMove
{
    uint32 uiCreatureEntry;
    uint32 uiPointId;
    float  fX;
    float  fY;
    float  fZ;
    uint32 uiWaitTime;
};

struct StringTextData
{
    uint32 uiSoundId;
    uint8  uiType;
    uint32 uiLanguage;
    uint32 uiEmote;
};

//wuzhu start
struct WUZHU_GameTele
{
	uint32 target_mapId;
	float  target_X;
	float  target_Y;
	float  target_Z;
	float  target_Orientation;
};

struct WUZHU_Teleport_Template
{	
	uint32 Type;//Type ȡֵ ����˵�� ͬһ���˵���Type����Ϊ3ʱ�����ڴ���ʦ�뱦ʯ��ͬʱ����
	//0 ע�����˵�  		1 ����ʦר�ò˵�  		2 ��ʯר�ò˵�  		3 ����ʦ�뱦ʯ���ò˵� 
	uint32 MenuClass;//�˵������
	//����ֵ0��Ϊ0ֵ�Ĳ˵�����Ϊ��ҳ�˵����֣�����ֵ�Զ��塣
	uint32 Icon;//�˵�ǰ���ͼ��(0-15)
	std::string Title;//�˵�����������
	uint32 PRG;//�������
	/*
	ȡֵ ����˵�� ����˵�� ����һ���ȽϹؼ�����ֵ��ȡֵ1Ϊ���˵������ǻ�����һ���Ӳ˵��Ķ��壬��ȡ��ֵʱ���˲˵���������г�����Action�ֶ�ֵ����MenuClassֵ��������е��Ӳ˵���Ҳ�������ǳ�˵�ĵڶ��༰�������Ӳ˵��ȡ�
	���й��ܶԴ��ͱ�ʯ�ʹ���ʦ��֧�֣�ֻ�����ߵ��̵�ͼ����̳ǵ����ÿ�����÷���������ͬ

	5 ���͵� ʹ�������ݿ��game_tele��ĵļ�¼IDֵ���ڱ���Action�ļ�¼���д��ͣ�����ӵ����ǧ�����͵㹩����Զ���ѡ��ʹ�ã����Դ��͵�����������䡣����Ҫ�ض�����⽫�ܴ�������ϵͳ��Դ��ʹ�á� 
	10 ������е� ���Թ涨�ȼ������ѵ��ʽ�VIP����Ӫ������Ϊ����������GM������ֹ�� 
	20 ���� ���Թ涨�ȼ������ѵ��ʽ�VIP����Ӫ������Ϊ����������GM������ֹ�� 
	22 �󶨳���¯ʯ ���Թ涨�ȼ������ѵ��ʽ�VIP����Ӫ������Ϊ����������GM������ֹ��
	40 ����װ���;� ���Թ涨�ȼ������ѵ��ʽ�VIP����Ӫ������Ϊ����������GM������ֹ�� 
	70 ��ʯ�̳�(ֻ���ڱ�ʯ)
	��ʯ�̵���Ʒ������item_vendor�����á���PRGΪ70ʱ��Actionֵ�ֱ��Ӧ�����ݿ���ı�item_vendor��entryֵ��ÿһ��ֵ����һ�����࣬��������ӷ��࣬ɾ�����޸ĵȡ�	
	90 ���߹��� ���Թ涨�ȼ�����Ӧ��money��ʾ1������ȡ���ʽ�VIP����Ӫ������Ϊ����������GM������ֹ�� 
	110 �������ʱ���� ���Թ涨�ȼ������ѵ��ʽ�VIP����Ӫ������Ϊ����������GM������ֹ�� 
	111 ������� ���Թ涨�ȼ������ѵ��ʽ�VIP����Ӫ������Ϊ����������GM������ֹ�� 
	120 ���ֲ鿴 ���Թ涨�ȼ������ѵ��ʽ�VIP����Ӫ������Ϊ����������GM������ֹ�� 	
	130 ԭ�ظ��� ���Թ涨�ȼ������ѵ��ʽ�VIP����Ӫ������Ϊ����������GM������ֹ�� 	
	140 ������ҳ ������ҳ������ ��ֻ���ڴ���ʦ

	200 �汾��Ϣ ������Ϸ�汾 	�˹��ܿ�������ͨ�˵�����ɡ��൱����һ���Ӳ˵�������˵��ٷ�����һ�����˵����ݼ�Ϊ��ʾ���ݡ�
	80 �����̳�
	��NPC����ʦ ���Թ涨�ȼ���VIP����Ӫ������Ϊ������GM������ֹ��������Ϊ��ʯʹ��ʱ��item_trainer�����ã���PRGΪ110ʱ��item_trainer���ID��Ӧ9��ְҵȡֵΪ��1��2��3��4��5��7��8��9��11�����ζ�Ӧ��ɫ��9��ְҵ,1սʿ(Warrior)��2ʥ��ʿ(Paladin)��3����(Hunter)��4����(Rogue)��5��ʦ(Priest)��7������˾(Shaman)��8��ʦ(Mage)��9��ʦ(Warlock)��11��³��(Druid)
	��ΪNPCʹ��ʱ��npc_trainer�����NPC��¼������������ʦ��ͬ��һ��NPCֻ�ܽ�һ�༼�ܣ�����������Ҫ���ID��NPC 
	*/
	uint32 Action;//�๦��ָ����ֵ�ĺ���ȡ����PRGֵ
	//��PRGΪ1ʱ������һ��ϵ��MenuClassֵ��ȵ��Ӳ˵��࣬��PRGΪ5ʱ����һ�����͵㣬�˴��͵�ľ�����Ϣ�μ������ݿ��game_tele����PRGΪ70ʱ����һϵ����Ʒ�ķ��࣬����μ������ݿ�item_vendor��
	uint32 Level;//ʹ�ô˲˵�����С�ȼ����ƣ�ȫ����Ч
	std::string Message;//��Money��Integral����0ʱ��Ч
	uint32 Money;//������ȡ��ң�ȫ����Ч
	uint32 Integral;//������ȡ���֣���MoneyֵΪ0ʱ��Ч��ȫ����Ч
	uint32 PTeam;//������Ӫ���ƣ������в˵���Ч ȡֵΪ��0������Ӫ��469���ˣ�67���䡣����ֵ��Ч�������ڽ�ɫ��Ӫ�Ĳ˵��������г� 
	uint32 VIP;//���ܵ�VIP���ƣ�0����ֹ��1����VIP���ţ�����ֹ��ΪVIPʹ�õĲ˵����ܣ���ͨ��ҽ���������GM������ֹ
	uint32 SpellID;//PRGֵΪ110��111ʱ���ֶ���Ч,110ʱΪ���ܱ�ţ�111Ϊ�������ģ��
	uint32 P_class;//ְҵ��ֹ��ȫ����ЧP_class; 
	//ȡֵ��Χ��1��2��3��4��5��7��8��9��11�����ζ�Ӧ��ɫ��9��ְҵ,1սʿ(Warrior)��2ʥ��ʿ(Paladin)��3����(Hunter)��4����(Rogue)��5��ʦ(Priest)��7������˾(Shaman)��8��ʦ(Mage)��9��ʦ(Warlock)��11��³��(Druid)	
};

struct TeleportHolder
{
	TeleportHolder( uint32 i,WUZHU_Teleport_Template p) : TeleportId(i),Teleport(p) {}
	uint32 TeleportId;
	WUZHU_Teleport_Template Teleport;
	bool operator <(TeleportHolder item)
	{
		if(TeleportId<item.TeleportId)
			return true;
		else
			return false;
	};
}; 

struct WUZHU_FLY_DATA
{
	uint32 entry;
	uint32 minlevel;
	uint32 maxlevel;
	std::string name;
	uint32 Speed;
	uint32 Flags;
	uint32 AllowableClass;
	uint32 AllowableRace;
	uint32 itemid;
	uint32 spell;
};
//wuzhu end

#define pSystemMgr SystemMgr::Instance()

class SystemMgr
{
    public:
        SystemMgr();
        ~SystemMgr() {}

        static SystemMgr& Instance();

        //Maps and lists
        typedef UNORDERED_MAP<int32, StringTextData> TextDataMap;
        typedef UNORDERED_MAP<uint32, std::vector<ScriptPointMove> > PointMoveMap;
		//wuzhu start
		 UNORDERED_MAP<uint32, WUZHU_GameTele> GameTele_Map;//����
		 UNORDERED_MAP<uint32, WUZHU_Teleport_Template> Teleport_Template_Map;//��ʯ�˵���
		//GameTele_Map    m_mGameTele_Map;
		//Teleport_Template_Map m_mTeleport_Template_Map;
		//wuzhu end

        //Database
        void LoadVersion();
        void LoadScriptTexts();
        void LoadScriptTextsCustom();
        void LoadScriptGossipTexts();
        void LoadScriptWaypoints();
		//wuzhu start
		void LoadWUZHU_texts();
		void LoadGameTele_Map();
		void LoadTeleport_Template_Map();
		void LoadWUZHU_Fly_Data();
		uint32 LoadWUZHU_Fly_Data(int minlevel,int maxlevel,int flags);
		void FreeFly_Data();

		WUZHU_FLY_DATA *GetFlyData(uint32 level,int flags);
		//wuzhu end

        //Retrive from storage
        StringTextData const* GetTextData(int32 uiTextId) const
        {
            TextDataMap::const_iterator itr = m_mTextDataMap.find(uiTextId);

            if (itr == m_mTextDataMap.end())
                return NULL;

            return &itr->second;
        }

        std::vector<ScriptPointMove> const &GetPointMoveList(uint32 uiCreatureEntry) const
        {
            static std::vector<ScriptPointMove> vEmpty;

            PointMoveMap::const_iterator itr = m_mPointMoveMap.find(uiCreatureEntry);

            if (itr == m_mPointMoveMap.end())
                return vEmpty;

            return itr->second;
        }

    protected:
        TextDataMap     m_mTextDataMap;                     //additional data for text strings
        PointMoveMap    m_mPointMoveMap;                    //coordinates for waypoints

		//wuzhu start 100903
		WUZHU_FLY_DATA *m_mFlyData_S40;//40ǰ����
		uint32 m_uFlyDataMap_S40Count;
		WUZHU_FLY_DATA *m_mFlyData_S60;//60ǰ����
		uint32 m_uFlyDataMap_S60Count;
		WUZHU_FLY_DATA *m_mFlyData_S80;//80ǰ����
		uint32 m_uFlyDataMap_S80Count;
		WUZHU_FLY_DATA *m_mFlyData_T40;//40ǰ��������
		uint32 m_uFlyDataMap_T40Count;
		WUZHU_FLY_DATA *m_mFlyData_T60;//60ǰ��������
		uint32 m_uFlyDataMap_T60Count;
		WUZHU_FLY_DATA *m_mFlyData_T80;//80ǰ��������
		uint32 m_uFlyDataMap_T80Count;
		//wuzhu end
};

#endif
