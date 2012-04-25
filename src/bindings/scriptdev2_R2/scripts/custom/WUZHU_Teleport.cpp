#include "precompiled.h"
#include "sc_gossip.h"
#include "SharedDefines.h"
#include "Timer.h"
#include "WUZHU.h"
//#include "InstanceSaveMgr.h"

bool GossipHello_teleport(Player *pPlayer, Creature *_Creature)
{ 
	if(!pPlayer||!_Creature)
		return false;
	if(pPlayer->isInCombat())
	{ 
		pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-153,pPlayer));
		pPlayer->CLOSE_GOSSIP_MENU();
		//return false;
	}
	else
	{
		if (!pPlayer->isDead())
		{ 
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-154,pPlayer),1,GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-155,pPlayer),1,GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-157,pPlayer),1,GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-158,pPlayer),1,GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-159,pPlayer),1,GOSSIP_ACTION_INFO_DEF + 5);
			//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,"��Ұ�⡿[����Ұ��BOSS�������] ",1,GOSSIP_ACTION_INFO_DEF + 6);
			if(pPlayer->getLevel()>=70)
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-160,pPlayer),1,GOSSIP_ACTION_INFO_DEF + 7);
			pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-161,pPlayer),10,GOSSIP_ACTION_INFO_DEF,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Taxi,false);
			//����
			//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-90,pPlayer),20,GOSSIP_ACTION_INFO_DEF);
			//���߹���
			//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-88,pPlayer),90,GOSSIP_ACTION_INFO_DEF);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-89,pPlayer),40,GOSSIP_ACTION_INFO_DEF);
			if(pPlayer->isGameMaster())
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-91,pPlayer), 22, GOSSIP_ACTION_INFO_DEF + 22);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-325,pPlayer), 141, GOSSIP_ACTION_INFO_DEF);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER,pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-162,pPlayer),1,GOSSIP_ACTION_INFO_DEF+200);

		}
		pPlayer->SEND_GOSSIP_MENU(80000,_Creature->GetObjectGuid());
	}
	return true;
}

void SendDefaultMenu_Teleport(Player *pPlayer, Creature *_Creature, uint32 action)
{
	switch(action) {
		// ����
				case GOSSIP_ACTION_INFO_DEF + 1 :
					if(isbl(pPlayer))
					{
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-93,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 4,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-94,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 5,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-95,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 6,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-96,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 11,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
						if(pPlayer->getLevel()>=68)
						{
							pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-321,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 13,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
							pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-320,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 14,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
						}

					}
					else
					{
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-97,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 1,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-98,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 2,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-99,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 3,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-100,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 12,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
						if(pPlayer->getLevel()>=68)
						{
							pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-323,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 16,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
							pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-322,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 17,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
						}
					}
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-101,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-102,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 8,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-103,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 9,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-104,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 10,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-105,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7210,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
					if(pPlayer->getLevel()<71)
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-106,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 15,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-107,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7700,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-108,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 715,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
					if(pPlayer->getLevel()>=71)
					{
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-324,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 714,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_MainCity,false);
					}
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-15,pPlayer), 140, GOSSIP_ACTION_INFO_DEF);
					pPlayer->SEND_GOSSIP_MENU(88000,_Creature->GetObjectGuid());
					break;									
				case GOSSIP_ACTION_INFO_DEF + 2 :// ��������
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-165,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 101,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-166,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 102,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-167,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 103,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-168,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 104,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-169,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 105,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-170,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 106,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-171,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 107,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-172,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 108,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-173,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 109,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-174,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 110,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-175,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 111,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-15,pPlayer), 140, GOSSIP_ACTION_INFO_DEF);
					pPlayer->SEND_GOSSIP_MENU(88001,_Creature->GetObjectGuid());
					break;					
				case GOSSIP_ACTION_INFO_DEF + 3 :// �м�����
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-176,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 201,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-177,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 202,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-178,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 203,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-179,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 204,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_Copy,false);					
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-180,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 205,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-181,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 206,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-182,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 207,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-183,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 208,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-184,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 209,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-185,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 210,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-15,pPlayer), 140, GOSSIP_ACTION_INFO_DEF);
					pPlayer->SEND_GOSSIP_MENU(88002,_Creature->GetObjectGuid());
					break;					
				case GOSSIP_ACTION_INFO_DEF + 4 :// �߼�����
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-186,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 301,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-187,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 302,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-188,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 303,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-189,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 304,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-190,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 305,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-191,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 306,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-192,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 307,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_Copy,false);
					//pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, "�ɿ�����˹[60��] ", 5, GOSSIP_ACTION_INFO_DEF + 308,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_Copy,false);
					//pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, "������Ѩ[60��] ", 5, GOSSIP_ACTION_INFO_DEF + 309,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_Copy,false);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-15,pPlayer), 140, GOSSIP_ACTION_INFO_DEF);
					pPlayer->SEND_GOSSIP_MENU(88003,_Creature->GetObjectGuid());
					break;
				case GOSSIP_ACTION_INFO_DEF + 5 :// ���򸱱�����1
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-193,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 405,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-194,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 415,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-195,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7200,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-196,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7201,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_TBCCopy,false);					
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-197,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7204,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-198,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7205,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-199,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7212,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-200,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7206,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_1_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-164,pPlayer), 1, GOSSIP_ACTION_INFO_DEF + 9051);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-15,pPlayer), 140, GOSSIP_ACTION_INFO_DEF);
					pPlayer->SEND_GOSSIP_MENU(88004,_Creature->GetObjectGuid());
					break;
				case GOSSIP_ACTION_INFO_DEF + 6 :// Ұ��BOSS����
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-201,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 501,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Boss,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-202,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 502,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Boss,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-203,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 503,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Boss,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-204,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 504,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Boss,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-205,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 505,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Boss,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-206,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 506,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Boss,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-207,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 507,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Boss,false);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-15,pPlayer), 140, GOSSIP_ACTION_INFO_DEF);
					pPlayer->SEND_GOSSIP_MENU(88005,_Creature->GetObjectGuid());
					break;
				case GOSSIP_ACTION_INFO_DEF + 7 :// ŵɭ��					
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-208,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 701,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-209,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 702,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-210,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 703,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-211,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 704,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-212,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 705,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-213,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 706,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-214,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 707,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-215,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 708,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-217,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 710,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Copy,false);
					if(pPlayer->GetVIP()==5)//��ʱֻ��vip5����
					{
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-216,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 709,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TRAINER, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-218,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 711,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Boss_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TRAINER, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-219,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 712,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Boss_Copy,false);
						pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TRAINER, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-220,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 713,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Extent_Boss_Copy,false);
					}
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-15,pPlayer), 140, GOSSIP_ACTION_INFO_DEF);
					pPlayer->SEND_GOSSIP_MENU(88006,_Creature->GetObjectGuid());
					break;
				case GOSSIP_ACTION_INFO_DEF+200://��ʾ����
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-163,pPlayer), 140, GOSSIP_ACTION_INFO_DEF);
					pPlayer->SEND_GOSSIP_MENU(88803,_Creature->GetObjectGuid());
					break;
				case GOSSIP_ACTION_INFO_DEF + 9051 :// ���򸱱�����2
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-131,pPlayer), 1, GOSSIP_ACTION_INFO_DEF + 5);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-221,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 414,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-222,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7202,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-223,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7207,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-224,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 418,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_TBCCopy,false);					
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-225,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 416,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-226,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7211,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-227,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 417,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-228,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 3885,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_2_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-164,pPlayer), 1, GOSSIP_ACTION_INFO_DEF + 11051);					
					pPlayer->SEND_GOSSIP_MENU(88006,_Creature->GetObjectGuid());
					break;
				case GOSSIP_ACTION_INFO_DEF + 11051 :// ���򸱱�����3
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-131,pPlayer), 1, GOSSIP_ACTION_INFO_DEF + 9051);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-229,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 402,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-231,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 410,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-232,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 413,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-233,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 406,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_TBCCopy,false);					
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-234,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 7203,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-235,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 419,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-236,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 423,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-237,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 3889,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM_EXTENDED( GOSSIP_ICON_TAXI, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-238,pPlayer), 5, GOSSIP_ACTION_INFO_DEF + 408,pPlayer->GetWUZHUString(Cost_BOXMessage_ID,pPlayer),Cost_Level_3_TBCCopy,false);
					pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-15,pPlayer), 140, GOSSIP_ACTION_INFO_DEF);				
					pPlayer->SEND_GOSSIP_MENU(88006,_Creature->GetObjectGuid());
					break;
	}
}

bool GossipSelect_teleport(Player *pPlayer, Creature *_Creature, uint32 sender, uint32 action )
{
	if (!isstone(pPlayer))
	{
		switch(sender) {
			// ��ѡ��
				case GOSSIP_SENDER_MAIN :
					SendDefaultMenu_Teleport(pPlayer, _Creature, action);
					break;
					//���� 
				case 5 :
					switch(action) 
					{
						/*ͳһ��ʽ˵����(MapID, X, Y, Z, 0);

						case GOSSIP_ACTION_INFO_DEF + 9 :
						pPlayer->TeleportTo(533,3700.35,-5185.92,143.957,4.403038,0);
						break;
						*/
					case GOSSIP_ACTION_INFO_DEF +1://	���� �����
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
							pPlayer->TeleportTo(0,	-9065.0f,	434.0f,	94.0f,	0.0f);
							pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +2://	���� ��¯��
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
						pPlayer->TeleportTo(0,	-5032.0f,	-819.0f,	495.0f,	0.0f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +3://	���� ������˹	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
						pPlayer->TeleportTo(1,	9961.0f,	2055.0f,	1329.0f,	0.0f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +4://	���� �¸�����	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
						pPlayer->TeleportTo(1,	1317.0f	,-4383.0f,	27.0f,	0.0f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +5://	���� ������	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
						pPlayer->TeleportTo(1,	-1391.0f,	140.0f,	23.0f,	0.0f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +6://	���� �İ���	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
						pPlayer->TeleportTo(0,	1909.0f,	235.0f,	53.0f,	0.0f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7://	���� ���ݳ�	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{pPlayer->TeleportTo(1,	-977.0f,	-3788.0f,	6.0f,	0.0f);
							pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}						
						break;
					case GOSSIP_ACTION_INFO_DEF +8://	���� �ر�����	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{pPlayer->TeleportTo(0,	-14302.0f,	518.0f,	9.0f,	0.0f);
							pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}						
						break;
					case GOSSIP_ACTION_INFO_DEF +9://	���� ��Ȫ��	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{pPlayer->TeleportTo(1,	6723.47f,	-4649.3f,	720.981f,	4.65348f);
							pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}						
						break;
					case GOSSIP_ACTION_INFO_DEF +10://	���� �ӻ�ɭ	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
						pPlayer->TeleportTo(1,	-7177.1f	,-3788.08f,	8.37018f,	3.62134f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +11://	���� ���³�	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
						pPlayer->TeleportTo(530,	9301.71f	,-7268.83f	,15.2522f	,0.38392f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +12://	���� ������	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
						pPlayer->TeleportTo(530,	-4073.83f,	-12030.6f	,1.59961f	,1.40306f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +13://	�C�L�{�����ͳ��_��  X: 2018.871216 Y: -6175.680176 Z: 15.392685 Map: 571 or:1.040551	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
							pPlayer->TeleportTo(571,	2018.871216f, -6175.680176f	,15.392685f	,1.040551f);
							pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							WUZHU_Common::SendMoneyError(pPlayer);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +14://	���L��ԭ����豤	X: 2915.007568 Y: 6256.863770 Z: 208.750229 Map: 571 or :0.575959
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
							pPlayer->TeleportTo(571,	2915.007568f,	6256.863770f	,208.750229f	,0.575959f);
							pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							WUZHU_Common::SendMoneyError(pPlayer);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +15://	���� ��������˹�� 	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
						pPlayer->TeleportTo(530,	13011.5f,	-6900.8f,	10.59f,	3.803f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +16://	�C�L�{�����ߠ��ӵ� 	X: 589.297852 Y: -5104.841309 Z: 5.260796 Map: 571 or:1.251140
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
							pPlayer->TeleportTo(571,	589.297852f,	-5104.841309f,	5.260796f,	1.251140f);
							pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							WUZHU_Common::SendMoneyError(pPlayer);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +17://	���L��ԭ�����Ҫ��X: 2231.822754 Y: 5131.532227 Z: 5.344474 Map: 571 or:1.570800	 
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
							pPlayer->TeleportTo(571,	2231.822754f,	5131.532227f,	5.344474f,	1.5708f);
							pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							WUZHU_Common::SendMoneyError(pPlayer);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +101://	[13��] ŭ���ѹ�	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(389	,2.02465f	,-10.021f,	-16.1875f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +102://	[15��] ������	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(36	,-16.4f,	-383.07f,	61.78f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +103://	[15��] ������Ѩ	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(43,	-161.842f,	133.267f,	-73.8662f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +104://	[22��] Ӱ���Ǳ�	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(33,	-228.19f	,2110.56f	,76.89f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +105://	[24��] �ڰ���Ԩ	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(48	,-150.367f,	102.995f	,-40.5558f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +106://	[24��] ����Ǽ���	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(34,	48.29f	,0.45f	,-16.14f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +107://	[29��] �굶����	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(47	,1943.0f	,1544.0f,	82.0f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +108://	[29��] ŵĪ���	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(90	,-332.563f,	-3.445f,	-152.846f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +109://	[34��] Ѫɫ�޵�Ժ	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(189,	855.904f,	1321.94f,	18.673f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +110://	[37��] �굶�ߵ�	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(129,	2593.21f,	1109.46f,	51.0933f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +111://	[35��] �´���	
						if(pPlayer->GetMoney() >= Cost_Level_1_Copy)
						{
						pPlayer->TeleportTo(70,	-227.529f,	45.0098f,	-46.0196f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +201://	[44] ���������	
						if(pPlayer->GetMoney() >= Cost_Level_2_Copy)
						{
						pPlayer->TeleportTo(209,	1213.0f,	841.0f,	8.9f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +202://	[46] ������	
						if(pPlayer->GetMoney() >= Cost_Level_2_Copy)
						{
						pPlayer->TeleportTo(349,	1012.7f,	-459.318f,	-43.5471f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +203://	[45] ʧ�������	
						if(pPlayer->GetMoney() >= Cost_Level_2_Copy)
						{
						pPlayer->TeleportTo(109,	-313.37f	,99.9554f,	-131.849f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +204://	[52] ��ʯ��Ԩ	
						if(pPlayer->GetMoney() >= Cost_Level_2_Copy)
						{
						pPlayer->TeleportTo(230	,456.929f,	34.9277f,	-69.3881f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +205://	[57] ͨ��ѧԺ	
						if(pPlayer->GetMoney() >= Cost_Level_2_Copy)
						{pPlayer->TeleportTo(289	,199.0f,	126.0f,	135.0f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +206://	[55] ����֮� (����)	
						if(pPlayer->GetMoney() >= Cost_Level_2_Copy)
						{pPlayer->TeleportTo(429,	255.164f,	-17.0242f,	-2.5606f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +207://	[55] ����֮� (����)	
						if(pPlayer->GetMoney() >= Cost_Level_2_Copy)
						{pPlayer->TeleportTo(429,	46.24f,	-155.53f,	-2.71349f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +208://	[55] ����֮� (����)	
						if(pPlayer->GetMoney() >= Cost_Level_2_Copy)
						{pPlayer->TeleportTo(429	,32.7226f,	159.417f,	-3.47017f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +209://	[58] ˹̹��ķ	
						if(pPlayer->GetMoney() >= Cost_Level_2_Copy)
						{pPlayer->TeleportTo(329,	3392.0f,	-3379.0f,	143.0f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +210://	[55] ��ʯ��	
						if(pPlayer->GetMoney() >= Cost_Level_2_Copy)
						{pPlayer->TeleportTo(229,	78.19f,	-227.63f,	49.72f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +301://	[��] �ܻ�֮��	
						if(pPlayer->GetMoney() >= Cost_Level_3_Copy)
						{pPlayer->TeleportTo(409,	1089.6f	,-470.19f,	-106.413f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +302://	[��] ��ʯ��	
						if(pPlayer->GetMoney() >= Cost_Level_3_Copy)
						{pPlayer->TeleportTo(229,	78.3398f,	-227.794f,	49.7103f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +303://	[��] ���������	
						if(pPlayer->GetMoney() >= Cost_Level_3_Copy)
						{pPlayer->TeleportTo(309,	-11916.0f,	-1251.47f,	92.32f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +304://	[��] ����֮��	
						if(pPlayer->GetMoney() >= Cost_Level_3_Copy)
						{pPlayer->TeleportTo(469,	-7674.47f,	-1108.38f	,396.65f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +305://	[��] ����������	
						if(pPlayer->GetMoney() >= Cost_Level_3_Copy)
						{pPlayer->TeleportTo(531,	-8212.0f,	2034.47f,	129.141f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +306://	[��] ����������	
						if(pPlayer->GetMoney() >= Cost_Level_3_Copy)
						{pPlayer->TeleportTo(509,	-8443.48f,	1518.65f,	31.907f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +	307://	[��] ���ݿ�ϣ�ǵĳ�Ѩ	
						if(pPlayer->GetMoney() >= Cost_Level_3_Copy)
						{pPlayer->TeleportTo(249,	30.0103f,	-58.8405f,	-5.32537f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +308://	[��] �ɿ�����˹	
						if(pPlayer->GetMoney() >= Cost_Level_3_Copy)
						{
							pPlayer->TeleportTo(533,3005.87f,-3435.01f,293.882f,0.0f);
							pPlayer->ModifyMoney(-Cost_Level_3_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +309://	[��] ������Ѩ	
						if(pPlayer->GetMoney() >= Cost_Level_3_Copy)
						{pPlayer->TeleportTo(533,	3700.35f	,-5185.92f,	143.957f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +402://	������(70 �� ����)	
						if(pPlayer->GetMoney() >= Cost_Level_3_TBCCopy)
						{pPlayer->TeleportTo(532,	-11108.0f,	-2002.06f,	49.89f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +405://	�������ǽ(60+)	
						if(pPlayer->GetMoney() >= Cost_Level_1_TBCCopy)
						{pPlayer->TeleportTo(543,	-1355.82f,	1646.83f,	68.4474f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +406://	�籩Ҫ��(70 ��)	
						if(pPlayer->GetMoney() >= Cost_Level_3_TBCCopy)
						{pPlayer->TeleportTo(530,	3087.56f,	1387.23f	,185.037f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +408://	�ڰ�����(70 ��)	
						if(pPlayer->GetMoney() >= Cost_Level_3_TBCCopy)
						{pPlayer->TeleportTo(530,	-3622.897705f,	325.230438f,	38.87447f,	1.70429f);
						//X: -3622.897705 Y: 325.230438 Z: 38.874470 Map: 530 Or 1.704290
						//pPlayer->TeleportTo(530,	-3562.8,	247.6,	42.8969,	0);
						pPlayer->ModifyMoney(-Cost_Level_3_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +410://	��³���ĳ�Ѩ(70 ��)	
						if(pPlayer->GetMoney() >= Cost_Level_3_TBCCopy)
						{pPlayer->TeleportTo(530,	3543.44f,	5079.01f,	0.952552f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +413://	��ɪ��ٵĳ�Ѩ(70 ��)	
						if(pPlayer->GetMoney() >= Cost_Level_3_TBCCopy)
						{pPlayer->TeleportTo(544,	188.414f,	29.3279f,	67.9345f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +414://	�������(70)	
						if(pPlayer->GetMoney() >= Cost_Level_2_TBCCopy)
						{pPlayer->TeleportTo(540,	-41.0f,	-22.0f,	-14.0f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +415://	��Ѫ��¯(61+)	
						if(pPlayer->GetMoney() >= Cost_Level_1_TBCCopy)
						{pPlayer->TeleportTo(542,	-3.0f,	11.0f,	-45.0f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +416://	��̬��(70)	
						if(pPlayer->GetMoney() >= Cost_Level_2_TBCCopy)
						{pPlayer->TeleportTo(553,	40.0f	,-28.6f,	-1.1f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +417://	��ħ����(70)	
						if(pPlayer->GetMoney() >= Cost_Level_2_TBCCopy)
						{pPlayer->TeleportTo(552,	-1.2f,	0.0f,	-0.2f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +418://	��Դ��(70)	
						if(pPlayer->GetMoney() >= Cost_Level_2_TBCCopy)
						{pPlayer->TeleportTo(554,	-28.9f,	0.7f,	-1.8f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +419://	�氢��(70 ��)	
						if(pPlayer->GetMoney() >= Cost_Level_3_TBCCopy)
						{pPlayer->TeleportTo(530,	6837.86f	,-7948.4f,	170.045f,	5.167f);
						pPlayer->ModifyMoney(-Cost_Level_3_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +423://	���Ӷ�ɽ(70 ��)	
						if(pPlayer->GetMoney() >= Cost_Level_3_TBCCopy)
						{pPlayer->TeleportTo(1,	-8176.82f,	-4184.0f	,-168.095f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +501://	ĺɫɭ��	
						if(pPlayer->GetMoney() >= Cost_Boss)
						{pPlayer->TeleportTo(0	,-10526.2f,	-434.997f,	50.8948f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Boss);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +502://	������	
						if(pPlayer->GetMoney() >= Cost_Boss)
						{
							pPlayer->TeleportTo(0,759.606f,-3893.34f,116.475f,0.0f);
							pPlayer->ModifyMoney(-Cost_Boss);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +503://	�ҹ�	
						if(pPlayer->GetMoney() >= Cost_Boss)
						{
							pPlayer->TeleportTo(1,	3120.29f	,-3439.44f	,139.566f,	1.0f);
							pPlayer->ModifyMoney(-Cost_Boss);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +504://	������	
						if(pPlayer->GetMoney() >= Cost_Boss)
						{pPlayer->TeleportTo(1	,2622.22f,	-5977.93f,	100.563f	,1.0f);
						pPlayer->ModifyMoney(-Cost_Boss);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +505://	����˹	
						if(pPlayer->GetMoney() >= Cost_Boss)
						{pPlayer->TeleportTo(1	,-2741.29f,	2009.48f	,31.8773f,	1.0f);
						pPlayer->ModifyMoney(-Cost_Boss);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +506://	����֮��	
						if(pPlayer->GetMoney() >= Cost_Boss)
						{
							pPlayer->TeleportTo(0,-12234.0f,-2474.0f,-3.0f,0.0f);
							pPlayer->ModifyMoney(-Cost_Boss);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +507://	ˮ����	
						if(pPlayer->GetMoney() >= Cost_Boss)
						{pPlayer->TeleportTo(1	,-6292.46f	,1578.03f,	0.155348f,	1.0f);
						pPlayer->ModifyMoney(-Cost_Boss);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;

						// ��������
					case GOSSIP_ACTION_INFO_DEF + 701 :
						if(pPlayer->GetMoney() >= Cost_Extent_Copy)
						{
							pPlayer->TeleportTo(571,4260.314453f,-2314.690430f,218.016953f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}						
						break;
						// ����̦ԭ
					case GOSSIP_ACTION_INFO_DEF + 702 :
						if(pPlayer->GetMoney() >= Cost_Extent_Copy)
						{
							pPlayer->TeleportTo(571,3292.6875f,5258.383301f,37.055984f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
						// ���ǻ�Ұ
					case GOSSIP_ACTION_INFO_DEF + 703 :
						if(pPlayer->GetMoney() >= Cost_Extent_Copy)
						{
							pPlayer->TeleportTo(571,4289.433105f,905.629639f,78.972702f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
						// ����Ͽ��
					case GOSSIP_ACTION_INFO_DEF + 704 :
						if(pPlayer->GetMoney() >= Cost_Extent_Copy)
						{
							pPlayer->TeleportTo(571,1347.795654f,-4532.550293f,175.921127f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
						//����
					case GOSSIP_ACTION_INFO_DEF + 705 :
						if(pPlayer->GetMoney() >= Cost_Extent_Copy)
						{
							pPlayer->TeleportTo(571,5687.527832f,-3325.282471f,372.795776f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
						// ���籩�ͱ�
					case GOSSIP_ACTION_INFO_DEF + 706 :
						if(pPlayer->GetMoney() >= Cost_Extent_Copy)
						{
							pPlayer->TeleportTo(571,8913.091797f,-1309.078735f,1025.499146f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
						// �����ڱ���
					case GOSSIP_ACTION_INFO_DEF + 707 :
						if(pPlayer->GetMoney() >= Cost_Extent_Copy)
						{
							pPlayer->TeleportTo(571,7520.01416f,2301.520508f,384.003876f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
						// �����������
					case GOSSIP_ACTION_INFO_DEF + 708 :
						if(pPlayer->GetMoney() >= Cost_Extent_Copy)
						{
							pPlayer->TeleportTo(571,5878.264648f,4122.9375f,-85.512115f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
						// ��ӵ��
					case GOSSIP_ACTION_INFO_DEF + 709 :
						if(pPlayer->GetMoney() >= Cost_Extent_Copy)
						{
							pPlayer->TeleportTo(571,4610.811523f,2837.539551f,396.896851f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}						
						break;
						// ����ɭ��
					case GOSSIP_ACTION_INFO_DEF + 710 :
						if(pPlayer->GetMoney() >= Cost_Extent_Copy)
						{
							pPlayer->TeleportTo(571,5470.397461f,53.802029f,149.789978f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
						//�º�֮��
					case GOSSIP_ACTION_INFO_DEF + 711 :
						if(pPlayer->GetMoney() >= Cost_Extent_Boss_Copy)
						{
							pPlayer->TeleportTo(576,146.0f,-10.0f,-16.0f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Boss_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}						
						break; 
						// ������֮Ԩ
					case GOSSIP_ACTION_INFO_DEF + 712 :
						if(pPlayer->GetMoney() >= Cost_Extent_Boss_Copy)
						{
							pPlayer->TeleportTo(601,404.28f,53.53f,252.42f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Boss_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}						
						break;
						// ����ɫ����
					case GOSSIP_ACTION_INFO_DEF + 713 :
						if(pPlayer->GetMoney() >= Cost_Extent_Boss_Copy)
						{
							pPlayer->TeleportTo(609,2363.65f,-5659.17f,382.27f,0.0f);
							pPlayer->ModifyMoney(-Cost_Extent_Boss_Copy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF + 714 ://����Ȼ
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{
							pPlayer->TeleportTo(571,5813.874512f,448.283173f,658.752319f,1.008073f);
							pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;

					case GOSSIP_ACTION_INFO_DEF +715://	�ڰ�֮��	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{pPlayer->TeleportTo(530	,-246.6f	,946.0f,84.4f,0.0f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +3885://	ħ��ʦƽ̨(70)	
						if(pPlayer->GetMoney() >= Cost_Level_2_TBCCopy)
						{pPlayer->TeleportTo(530,	12884.6f,	-7336.17f	,65.48f,	1.09f);
						pPlayer->ModifyMoney(-Cost_Level_2_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +3889://	̫��֮��(70��)	
						if(pPlayer->GetMoney() >= Cost_Level_3_TBCCopy)
						{pPlayer->TeleportTo(530,	12557.93f	,-6774.05f	,15.0364f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7200://	ū��Χ��(62+)	
						if(pPlayer->GetMoney() >= Cost_Level_1_TBCCopy)
						{pPlayer->TeleportTo(547,	120.26f,	-130.292f,	-0.614219f,	1.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7201://	�İ�����(63+)	
						if(pPlayer->GetMoney() >= Cost_Level_1_TBCCopy)
						{pPlayer->TeleportTo(546,	11.6211f,	-17.8479f,	-2.75473f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7202://	��������(70)	
						if(pPlayer->GetMoney() >= Cost_Level_2_TBCCopy)
						{
							pPlayer->TeleportTo(545,-6.50007f,1.23076f,-4.00102f,0.0f);
							pPlayer->ModifyMoney(-Cost_Level_2_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7203://	�������(70 ��)	
						if(pPlayer->GetMoney() >= Cost_Level_3_TBCCopy)
						{pPlayer->TeleportTo(548,	8.87624f	,0.006297f,	821.727f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Level_3_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7204://	������Ĺ(64+)	
						if(pPlayer->GetMoney() >= Cost_Level_1_TBCCopy)
						{pPlayer->TeleportTo(557,	0.0191f	,0.9478f,	-0.9543f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7205://	�½����Ѩ(65+)	
						if(pPlayer->GetMoney() >= Cost_Level_1_TBCCopy)
						{pPlayer->TeleportTo(558,	-23.982f,	-0.406389f,	-0.1206f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7206://	��̩�˴���(67+)	
						if(pPlayer->GetMoney() >= Cost_Level_1_TBCCopy)
						{pPlayer->TeleportTo(556,	-4.6811f,	-0.09308f,	0.0062f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7207://	��Ӱ�Թ�(70)	
						if(pPlayer->GetMoney() >= Cost_Level_2_TBCCopy)
						{pPlayer->TeleportTo(555,	2.16401f	,0.402381f	,-1.12788f,	0.0f);
						pPlayer->ModifyMoney(-Cost_Level_2_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7210://	���� ɳ��˹��	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{pPlayer->TeleportTo(530,	-1813.51f,	5413.34f	,-12.4281f,	1.0f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7211://	��ɫ����(70)	
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{pPlayer->TeleportTo(269,	-1496.62f,	7036.72f,	32.4903f,	0.0f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7212://	�ػ�����(66+)	
						if(pPlayer->GetMoney() >= Cost_Level_1_TBCCopy)
						{pPlayer->TeleportTo(560,	2384.44f,	1184.31f,	67.1144f	,0.0f);
						pPlayer->ModifyMoney(-Cost_Level_1_TBCCopy);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					case GOSSIP_ACTION_INFO_DEF +7700://52
						//���� 52��X: 3027.937988 Y: 3571.022461 Z: 143.480347 Map: 530 Or5.754831
						if(pPlayer->GetMoney() >= Cost_MainCity)
						{pPlayer->TeleportTo(530,3027.937988f,3571.022461f,143.480347f,5.754831f);
						pPlayer->ModifyMoney(-Cost_MainCity);
						}else{
							pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
						}
						break;
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					//�����е�
				case 10:
					if(pPlayer->GetMoney() >= Cost_Taxi)
					{
						pPlayer->SetTaxiCheater(true);
						pPlayer->ModifyMoney(-Cost_Taxi);
						pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-230,pPlayer),Cost_Taxi/10000);
					}					
					else{
						pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					//����
				case 20 :
					pPlayer->SEND_BANKERLIST(_Creature->GetObjectGuid() );
					break;

				case 22://��					
					pPlayer->GetSession()->SendBindPoint();
					pPlayer->CLOSE_GOSSIP_MENU();
					break;	
				case 40://����װ��
					pPlayer->DurabilityRepairAll(true,1,false);
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 90://��ȡ����
					//��ȡ��ǰʱ��
					{
						//uint32 ingametime=WorldTimer::getMSTimeDiff(pPlayer->GetInGameTime(),WorldTimer::getMSTime())/1000;
						//if(ingametime > 60) // �������������ʱ�����1���ӣ�������Լ���(��λ:��)
						//{
						//	float money = 0;
						//	//TODO:����ϵͳ��������Ϸʱ����������
						//	//���򣺹���=1����1G
						//	money = (float)(ingametime / 60 *WUZHU_Wages_Money);

						//	pPlayer->ModifyMoney(int32(money));      //����������ý��
						//	pPlayer->SetInGameTime(WorldTimer::getMSTime());   //�����������ʱ�����
						//	pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-239,pPlayer),int32(money)/10000);
						//	pPlayer->CLOSE_GOSSIP_MENU();
						//}
						//else
						//{
						//	pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-139,pPlayer));
						//	//_Creature->Say("��ȡ����ʱ����̫��.", LANG_UNIVERSAL, 0);
						//	pPlayer->CLOSE_GOSSIP_MENU();
						//}
						pPlayer->CLOSE_GOSSIP_MENU();
						break;
					}
					
				case 140://�������˵�
					GossipHello_teleport(pPlayer,_Creature);
					break;
				case 141://1000���������ŶӸ���
					{
						if(pPlayer->GetVIP_Integral() >= 2000)
						{
							uint32 counter = 0;
							for(uint8 i = 0; i < MAX_DIFFICULTY; ++i)
							{
								Player::BoundInstancesMap &binds = pPlayer->GetBoundInstances(Difficulty(i));
								for(Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
								{
									if(itr->first != pPlayer->GetMapId())
									{										
										pPlayer->UnbindInstance(itr, Difficulty(i));
										counter++;
									}
									else
										++itr;
								}
							}
							if(counter>0)
							{
								pPlayer->ModifyVIP_Integral(-2000);
								pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-326,pPlayer),counter);
							}
							else
							{
								pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-327,pPlayer));
							}
							//PSendSysMessage("instances unbound: %d", counter);
						}					
						else{
							pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
						}
						pPlayer->CLOSE_GOSSIP_MENU();						
						break;
					}


						///*case 23://���ʹ��
						//	pPlayer-> GetSession()->SendSpiritResurrect();
						//	pPlayer->CLOSE_GOSSIP_MENU();
						//	break;*/


		} 
	}
	return true;
}

//std::string GetTimeString(uint32 time)
//{
//	uint16 days = time / DAY, hours = (time % DAY) / HOUR, minute = (time % HOUR) / MINUTE;
//	std::ostringstream ss;
//	if(days) ss << days << "d ";
//	if(hours) ss << hours << "h ";
//	ss << minute << "m";
//	return ss.str();
//}


void AddSC_WUZHU_Teleport() 
{ 
	Script *newscript; 

	newscript = new Script; 
	newscript->Name="WUZHUTeleport"; 
	newscript->pGossipHello = &GossipHello_teleport; 
	newscript->pGossipSelect = &GossipSelect_teleport;
	newscript->RegisterSelf(); 
}