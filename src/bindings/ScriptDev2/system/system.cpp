/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
* This program is free software licensed under GPL version 2
* Please see the included DOCS/LICENSE.TXT for more information */

#include "precompiled.h"
#include "system.h"
#include "../config.h"
#include "ProgressBar.h"
#include "ObjectMgr.h"
#include "Database/DatabaseEnv.h"

DatabaseType SD2Database;
std::string  strSD2Version;

SystemMgr::SystemMgr()
{
}

SystemMgr& SystemMgr::Instance()
{
    static SystemMgr pSysMgr;
    return pSysMgr;
}

void SystemMgr::LoadVersion()
{
    //Get Version information
    QueryResult* pResult = SD2Database.PQuery("SELECT version FROM sd2_db_version LIMIT 1");

    if (pResult)
    {
        Field* pFields = pResult->Fetch();

        strSD2Version = pFields[0].GetCppString();

        delete pResult;
    }
    else
        script_error_log("Missing `sd2_db_version` information.");

    // Setup version info and display it
    if (strSD2Version.empty())
        strSD2Version.append("ScriptDev2 ");

    strSD2Version.append("SD2_FULLVERSION_WUZHU");

    outstring_log("Loading %s", strSD2Version.c_str());
    // outstring_log("");
}

void SystemMgr::LoadScriptTexts()
{
    outstring_log("SD2: Loading Script Texts...");
    LoadMangosStrings(SD2Database, "script_texts", TEXT_SOURCE_TEXT_START, TEXT_SOURCE_TEXT_END);

    QueryResult* pResult = SD2Database.PQuery("SELECT entry, sound, type, language, emote FROM script_texts WHERE entry BETWEEN %i AND %i", TEXT_SOURCE_GOSSIP_END, TEXT_SOURCE_TEXT_START);

    outstring_log("SD2: Loading Script Texts additional data...");

    if (pResult)
    {
        BarGoLink bar(pResult->GetRowCount());
        uint32 uiCount = 0;

        do
        {
            bar.step();
            Field* pFields = pResult->Fetch();
            StringTextData pTemp;

            int32 iId           = pFields[0].GetInt32();
            pTemp.uiSoundId     = pFields[1].GetUInt32();
            pTemp.uiType        = pFields[2].GetUInt32();
            pTemp.uiLanguage    = pFields[3].GetUInt32();
            pTemp.uiEmote       = pFields[4].GetUInt32();

            if (iId >= 0)
            {
                error_db_log("SD2: Entry %i in table `script_texts` is not a negative value.", iId);
                continue;
            }

            if (pTemp.uiSoundId)
            {
                if (!GetSoundEntriesStore()->LookupEntry(pTemp.uiSoundId))
                    error_db_log("SD2: Entry %i in table `script_texts` has soundId %u but sound does not exist.", iId, pTemp.uiSoundId);
            }

            if (!GetLanguageDescByID(pTemp.uiLanguage))
                error_db_log("SD2: Entry %i in table `script_texts` using Language %u but Language does not exist.", iId, pTemp.uiLanguage);

            if (pTemp.uiType > CHAT_TYPE_ZONE_YELL)
                error_db_log("SD2: Entry %i in table `script_texts` has Type %u but this Chat Type does not exist.", iId, pTemp.uiType);

            m_mTextDataMap[iId] = pTemp;
            ++uiCount;
        } while (pResult->NextRow());

        delete pResult;

        //outstring_log("");
        outstring_log(">> Loaded %u additional Script Texts data.", uiCount);
    }
    else
    {
        BarGoLink bar(1);
        bar.step();
        //outstring_log("");
        outstring_log(">> Loaded 0 additional Script Texts data. DB table `script_texts` is empty.");
    }
}

void SystemMgr::LoadScriptTextsCustom()
{
    outstring_log("SD2: Loading Custom Texts...");
    LoadMangosStrings(SD2Database, "custom_texts", TEXT_SOURCE_CUSTOM_START, TEXT_SOURCE_CUSTOM_END);

    QueryResult* pResult = SD2Database.PQuery("SELECT entry, sound, type, language, emote FROM custom_texts WHERE entry BETWEEN %i AND %i", TEXT_SOURCE_CUSTOM_END, TEXT_SOURCE_CUSTOM_START);

    outstring_log("SD2: Loading Custom Texts additional data...");

    if (pResult)
    {
        BarGoLink bar(pResult->GetRowCount());
        uint32 uiCount = 0;

        do
        {
            bar.step();
            Field* pFields = pResult->Fetch();
            StringTextData pTemp;

            int32 iId              = pFields[0].GetInt32();
            pTemp.uiSoundId        = pFields[1].GetUInt32();
            pTemp.uiType           = pFields[2].GetUInt32();
            pTemp.uiLanguage       = pFields[3].GetUInt32();
            pTemp.uiEmote          = pFields[4].GetUInt32();

            if (iId >= 0)
            {
                error_db_log("SD2: Entry %i in table `custom_texts` is not a negative value.", iId);
                continue;
            }

            if (pTemp.uiSoundId)
            {
                if (!GetSoundEntriesStore()->LookupEntry(pTemp.uiSoundId))
                    error_db_log("SD2: Entry %i in table `custom_texts` has soundId %u but sound does not exist.", iId, pTemp.uiSoundId);
            }

            if (!GetLanguageDescByID(pTemp.uiLanguage))
                error_db_log("SD2: Entry %i in table `custom_texts` using Language %u but Language does not exist.", iId, pTemp.uiLanguage);

            if (pTemp.uiType > CHAT_TYPE_ZONE_YELL)
                error_db_log("SD2: Entry %i in table `custom_texts` has Type %u but this Chat Type does not exist.", iId, pTemp.uiType);

            m_mTextDataMap[iId] = pTemp;
            ++uiCount;
        } while (pResult->NextRow());

        delete pResult;

        //outstring_log("");
        outstring_log(">> Loaded %u additional Custom Texts data.", uiCount);
    }
    else
    {
        BarGoLink bar(1);
        bar.step();
        //outstring_log("");
        outstring_log(">> Loaded 0 additional Custom Texts data. DB table `custom_texts` is empty.");
    }
}

void SystemMgr::LoadScriptGossipTexts()
{
    outstring_log("SD2: Loading Gossip Texts...");
    LoadMangosStrings(SD2Database, "gossip_texts", TEXT_SOURCE_GOSSIP_START, TEXT_SOURCE_GOSSIP_END);
}

void SystemMgr::LoadScriptWaypoints()
{
    // Drop Existing Waypoint list
    m_mPointMoveMap.clear();

    uint64 uiCreatureCount = 0;

    // Load Waypoints
    QueryResult* pResult = SD2Database.PQuery("SELECT COUNT(entry) FROM script_waypoint GROUP BY entry");
    if (pResult)
    {
        uiCreatureCount = pResult->GetRowCount();
        delete pResult;
    }

    outstring_log("SD2: Loading Script Waypoints for " UI64FMTD " creature(s)...", uiCreatureCount);

    pResult = SD2Database.PQuery("SELECT entry, pointid, location_x, location_y, location_z, waittime FROM script_waypoint ORDER BY pointid");

    if (pResult)
    {
        BarGoLink bar(pResult->GetRowCount());
        uint32 uiNodeCount = 0;

        do
        {
            bar.step();
            Field* pFields = pResult->Fetch();
            ScriptPointMove pTemp;

            pTemp.uiCreatureEntry   = pFields[0].GetUInt32();
            uint32 uiEntry          = pTemp.uiCreatureEntry;
            pTemp.uiPointId         = pFields[1].GetUInt32();
            pTemp.fX                = pFields[2].GetFloat();
            pTemp.fY                = pFields[3].GetFloat();
            pTemp.fZ                = pFields[4].GetFloat();
            pTemp.uiWaitTime        = pFields[5].GetUInt32();

            CreatureInfo const* pCInfo = GetCreatureTemplateStore(pTemp.uiCreatureEntry);

            if (!pCInfo)
            {
                error_db_log("SD2: DB table script_waypoint has waypoint for nonexistent creature entry %u", pTemp.uiCreatureEntry);
                continue;
            }

            if (!pCInfo->ScriptID)
                error_db_log("SD2: DB table script_waypoint has waypoint for creature entry %u, but creature does not have ScriptName defined and then useless.", pTemp.uiCreatureEntry);

            m_mPointMoveMap[uiEntry].push_back(pTemp);
            ++uiNodeCount;
        } while (pResult->NextRow());

        delete pResult;

        //outstring_log("");
        outstring_log(">> Loaded %u Script Waypoint nodes.", uiNodeCount);
    }
    else
    {
        BarGoLink bar(1);
        bar.step();
        //outstring_log("");
        outstring_log(">> Loaded 0 Script Waypoints. DB table `script_waypoint` is empty.");
    }
}



//wuzhu start
void SystemMgr::LoadWUZHU_texts()
{
	outstring_log("SD2: Loading WUZHU_texts...");
	LoadMangosStrings(SD2Database,"WUZHU_texts",TEXT_SOURCE_RANGE*6,1+(TEXT_SOURCE_RANGE*7));
}

void SystemMgr::LoadGameTele_Map()
{
	QueryResult* result = SD2Database.PQuery("SELECT id, position_x, position_y, position_z,orientation,map FROM game_tele order by id");
	GameTele_Map.clear();

	if (result)
	{
		outstring_log( "SD2: Loading Game_Tele...");
		BarGoLink bar(result->GetRowCount());
		uint32 Count = 0;
		do
		{
			bar.step();
			Field *fields = result->Fetch();
			uint32 i = fields[0].GetUInt32();
			WUZHU_GameTele temp;
			temp.target_mapId=fields[5].GetUInt32();
			temp.target_X=fields[1].GetFloat();
			temp.target_Y=fields[2].GetFloat();
			temp.target_Z=fields[3].GetFloat();
			temp.target_Orientation=fields[4].GetFloat();
			GameTele_Map[i]=temp;
			++Count;
		}while(result->NextRow());
		delete result;
		outstring_log("");
		outstring_log("SD2: >> Loaded %u Game_Tele", Count);
	}else outstring_log("SD2: WARNING >> Loaded 0 Game_Tele. DB table `Game_Tele` is empty.");
}


void SystemMgr::LoadTeleport_Template_Map()
{
	//                                   0    1              2            3           4     5

	QueryResult *result = SD2Database.PQuery(
		//		0	1		2		3		4	5	6		7		8		9	10		11		12	13	14
		"SELECT id,`Type`,MenuClass,Icon,Title,PRG,`Action`,Level,Message,Money,Integral,Team,VIP,Spell,P_Class FROM teleport_template order by id"
		);
	Teleport_Template_Map.clear();

	if (result)
	{
		outstring_log( "SD2: Loading Teleport_Template...");
		BarGoLink bar(result->GetRowCount());
		uint32 Count = 0;
		do
		{
			bar.step();
			Field *fields = result->Fetch();
			uint32 i = fields[0].GetUInt32();
			WUZHU_Teleport_Template temp;
			temp.Type=fields[1].GetUInt32();
			temp.MenuClass=fields[2].GetUInt32();
			temp.Icon=fields[3].GetUInt32();
			if(temp.Icon<0||temp.Icon>15)
				temp.Icon=0;
			temp.Title=fields[4].GetString();
			temp.PRG=fields[5].GetUInt32();
			temp.Action=fields[6].GetUInt32();
			temp.Level=fields[7].GetUInt32();
			temp.Message=fields[8].GetString();
			temp.Money=fields[9].GetUInt32();
			temp.Integral=fields[10].GetUInt32();
			temp.PTeam=fields[11].GetUInt32();
			temp.VIP=fields[12].GetUInt32();
			temp.SpellID=fields[13].GetUInt32();
			temp.P_class=fields[14].GetUInt32();
			Teleport_Template_Map[i]=temp;
			++Count;
		}while(result->NextRow());
		delete result;
		outstring_log("");
		outstring_log("SD2: >> Loaded %u Teleport_Template", Count);
	}else outstring_log("SD2: WARNING >> Loaded 0 Teleport_Template. DB table `Teleport_Template` is empty.");
	//wuzhu end
}

void SystemMgr::FreeFly_Data()
{
	if(m_mFlyData_S40)
		delete(m_mFlyData_S40);
	if(m_mFlyData_S60)
		delete(m_mFlyData_S60);
	if(m_mFlyData_S80)
		delete(m_mFlyData_S80);

	if(m_mFlyData_T40)
		delete(m_mFlyData_T40);
	if(m_mFlyData_T60)
		delete(m_mFlyData_T60);
	if(m_mFlyData_T80)
		delete(m_mFlyData_T80);

}

uint32 SystemMgr::LoadWUZHU_Fly_Data(int minlevel,int maxlevel,int flags)
{
	uint32 Count = 0;
	QueryResult *result = SD2Database.PQuery(
		//		0		1			2		3		4	 5		6				7				8		9
		"SELECT entry, minlevel, maxlevel, name, Speed, Flags, AllowableClass, AllowableRace, itemid, spell FROM fly_data where minlevel>=%d and maxlevel<=%d and flags=%d  order by entry",minlevel,maxlevel,flags
		);
	WUZHU_FLY_DATA *fdm=NULL;

	if (result)
	{
		int RowCount =result->GetRowCount();
		outstring_log( "SD2: Loading fly_data...(%d)",RowCount);
		BarGoLink bar(RowCount);
		fdm= new WUZHU_FLY_DATA[RowCount]; //(struct WUZHU_FLY_DATA*)malloc(sizeof(WUZHU_FLY_DATA)*RowCount);
		if(!fdm)
		{
			outstring_log("SD2: >> fly_data malloc faile.Count %u,minlevel %u,maxlevel %u,flags %u", RowCount,minlevel,maxlevel,flags);
		}
		else
		do
		{
			bar.step();
			Field *fields = result->Fetch();
			fdm[Count].entry=fields[0].GetUInt32();
			fdm[Count].minlevel=fields[1].GetUInt32();
			fdm[Count].maxlevel=fields[2].GetUInt32();
			fdm[Count].name=fields[3].GetCppString();
			fdm[Count].Speed=fields[4].GetUInt32();
			fdm[Count].Flags=fields[5].GetUInt32();
			fdm[Count].AllowableClass=fields[6].GetUInt32();
			fdm[Count].AllowableRace=fields[7].GetUInt32();
			fdm[Count].itemid=fields[8].GetUInt32();
			fdm[Count].spell=fields[9].GetUInt32();
			++Count;
		}while(result->NextRow());
		delete result;
		outstring_log("");
		outstring_log("SD2: >> Loaded %u fly_data.minlevel %u,maxlevel %u,flags %u", Count,minlevel,maxlevel,flags);
	}else outstring_log("SD2: WARNING >> Loaded 0 fly_data. DB table `fly_data` is empty.minlevel %u,maxlevel %u,flags %u",minlevel,maxlevel,flags);
	if(maxlevel<=40)
	{
		if(flags==0)
			m_mFlyData_S40=fdm;
		else
			m_mFlyData_T40=fdm;
	}
	else
	if(maxlevel<=60)
	{
		if(flags==0)
			m_mFlyData_S60=fdm;
		else
			m_mFlyData_T60=fdm;
	}
	else
		{
			if(flags==0)
				m_mFlyData_S80=fdm;
			else
				m_mFlyData_T80=fdm;
		}

	return Count;
}


void SystemMgr::LoadWUZHU_Fly_Data()
{
	m_uFlyDataMap_S40Count=LoadWUZHU_Fly_Data(0,40,0);
	//outstring_log("wuzhu s40 count:%d,%s",m_uFlyDataMap_S40Count,m_mFlyData_S40?"not null":"null");
	m_uFlyDataMap_S60Count=LoadWUZHU_Fly_Data(41,60,0);
	m_uFlyDataMap_S80Count=LoadWUZHU_Fly_Data(61,99,0);

	m_uFlyDataMap_T40Count=LoadWUZHU_Fly_Data(0,40,1);
	m_uFlyDataMap_T60Count=LoadWUZHU_Fly_Data(41,60,1);
	m_uFlyDataMap_T80Count=LoadWUZHU_Fly_Data(61,99,1);
}

WUZHU_FLY_DATA * SystemMgr::GetFlyData(uint32 level,int flags) 
{
	uint32 plevel=level;
	WUZHU_FLY_DATA *tmpdm=NULL;
	uint32 Count=0;
	
	if(plevel<=40)
	{
		if(flags==0)
		{
			tmpdm=m_mFlyData_S40;
			Count=m_uFlyDataMap_S40Count;
		}
		else
		{
			tmpdm=m_mFlyData_T40;
			Count=m_uFlyDataMap_T40Count;
		}
	}
	else
	if(plevel<=60)
	{
		if(flags==0)
		{
			tmpdm=m_mFlyData_S60;
			Count=m_uFlyDataMap_S60Count;
		}
		else
		{
			tmpdm=m_mFlyData_T60;
			Count=m_uFlyDataMap_T60Count;
		}
	}
	else
	{
		if(flags==0)
		{
			tmpdm=m_mFlyData_S80;
			Count=m_uFlyDataMap_S80Count;
		}
		else
		{
			tmpdm=m_mFlyData_T80;
			Count=m_uFlyDataMap_T80Count;
		}
	}

	if(Count==0||!tmpdm)
	{
		outstring_log("wuzhu getflydata %u,%u [Count==%u||!tmpdm]",level,flags,Count);
		return NULL;
	}
	else
		{
			uint32 ran =0;
			if(Count>1)
				ran=urand(0,Count-1);
			else
				ran=0;

			//outstring_log("wuzhu getflydata %u,%u [ran %u/Count %u]",level,flags,ran,Count);
			return &tmpdm[ran];
		}
	return NULL;
}
//wuzhu end