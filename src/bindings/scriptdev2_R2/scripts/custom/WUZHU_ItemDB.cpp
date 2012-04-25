#include "precompiled.h"
#include "Database/DatabaseMysql.h"
#include "DBCStores.h"
#include "../../../shared/Config/Config.h"
#include "sc_gossip.h"
#include "SharedDefines.h"
#include "Timer.h"
#include "Item.h"
#include "sc_creature.h"
#include "SpellMgr.h"
#include "Spell.h" 
#include "WUZHU.h"
#include "../system/system.h"


//extern  UNORDERED_MAP<uint32, WUZHU_GameTele> GameTele_Map;//����
//extern  UNORDERED_MAP<uint32, WUZHU_Teleport_Template> Teleport_Template_Map;


bool GossipDBItemHello(Player *pPlayer, Item* _Item, SpellCastTargets const& targets)
{
	if(pPlayer->isInCombat())
	{ 
		pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-55,pPlayer));
		pPlayer->CLOSE_GOSSIP_MENU();
	}
	else
	if(pPlayer->IsTaxiFlying()||pPlayer->IsMounted())
	{ 
		pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-56,pPlayer));
		pPlayer->CLOSE_GOSSIP_MENU();
	}
	else
	{
		if (!pPlayer->isDead())
		{ 
			UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
			std::list<TeleportHolder> TeleportList;
			TeleportList.clear();

			uint32 count=0;//����16���Ͳ�����
			bool baddmenu=true;
			for (i =pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
			{
				//outstring_log("wuzhu %d %s",(*i).first,(*i).second.Title);
				baddmenu=true;
				if(count>=16)
					break;				
				if ((*i).second.MenuClass==0&&(*i).second.PRG!=130&&((*i).second.Type==2||(*i).second.Type==3))//��MC=0����type=1��3ʱ����ʾ
				{
					if((*i).second.VIP>0)
					{
						if(pPlayer->GetVIP()==0)
							baddmenu=false;
					}
					if((*i).second.Level>pPlayer->getLevel())
						baddmenu=false;
					if((*i).second.P_class>0)
					{
						if((*i).second.P_class!=pPlayer->getClass())
							baddmenu=false;
					}
					if((*i).second.PTeam==67)//469���ˣ�67���� ����ֵ����Ϊ��ȫ��������
					{
						if(!isbl(pPlayer))
							baddmenu=false;
					}
					else
					if((*i).second.PTeam==469)
					{
						if(isbl(pPlayer))
							baddmenu=false;
					}	
					if(baddmenu||pPlayer->isGameMaster())
					{
						++count;
						TeleportList.push_back(TeleportHolder((*i).first, (*i).second));
						
					}
				}
			}
			if(!TeleportList.empty())
			{
				count=0;
				TeleportList.sort();
				for(std::list<TeleportHolder>::iterator th = TeleportList.begin();th!=TeleportList.end();++th)
				{
					++count;
					if(count>=16)
						break;
					if(th->Teleport.PRG==90)
						pPlayer->ADD_GOSSIP_ITEM(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.Action);
					else
					{
						if(th->Teleport.PRG==110||th->Teleport.PRG==111)
							pPlayer->ADD_GOSSIP_ITEM_EXTENDED(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.SpellID,th->Teleport.Message,th->Teleport.Money?th->Teleport.Money:th->Teleport.Integral,false);
						else
							pPlayer->ADD_GOSSIP_ITEM_EXTENDED(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.Action,th->Teleport.Message,th->Teleport.Money?th->Teleport.Money:th->Teleport.Integral,false);
					}
				}	
			}
		}
		else 
		if(pPlayer->isDead())
		{
			UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;

			bool baddmenu=true;
			for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
			{
				if ((*i).second.MenuClass==0&&(*i).second.PRG==130&&((*i).second.Type==2||(*i).second.Type==3))//��MC=0����type=1��3ʱ����ʾ
				{
					baddmenu=true;
					if((*i).second.VIP>0)
					{
						if(pPlayer->GetVIP()==0)
							baddmenu=false;
					}
					if((*i).second.Level>pPlayer->getLevel())
						baddmenu=false;
					if((*i).second.P_class>0)
					{
						if((*i).second.P_class!=pPlayer->getClass())
							baddmenu=false;
					}
					if((*i).second.PTeam==67)//469���ˣ�67���� ����ֵ����Ϊ��ȫ��������
					{
						if(!isbl(pPlayer))
							baddmenu=false;
					}
					else
						if((*i).second.PTeam==469)
						{
							if(isbl(pPlayer))
								baddmenu=false;
						}	
						if(baddmenu||pPlayer->isGameMaster())
						{
							pPlayer->ADD_GOSSIP_ITEM_EXTENDED((*i).second.Icon,(*i).second.Title,(*i).second.PRG,GOSSIP_ACTION_INFO_DEF+(*i).second.Action,(*i).second.Message,(*i).second.Money?(*i).second.Money:(*i).second.Integral,false);
						}

					break;
				}
			}
		} 
		pPlayer->SEND_GOSSIP_MENU(80000,_Item->GetObjectGuid());
	}

	return true;
}

void SendDefaultDBItemMenu(Player *pPlayer, Item *_Item, uint32 action)
{
	uint32 baseaction=action-GOSSIP_ACTION_INFO_DEF;
	if(pPlayer->isInCombat())
	{ 
		pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-55,pPlayer));
		pPlayer->CLOSE_GOSSIP_MENU();
	}
	else
	if(pPlayer->IsTaxiFlying()||pPlayer->IsMounted())
	{ 
		pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-56,pPlayer));
		pPlayer->CLOSE_GOSSIP_MENU();
	}
	else
	{
		if (!pPlayer->isDead())
		{ 
			UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
			std::list<TeleportHolder> TeleportList;
			TeleportList.clear();
			uint32 count=0;//����16���Ͳ�����
			bool baddmenu=true;
			for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
			{
				baddmenu=true;
				if(count>=16)
					break;				
				if ((*i).second.MenuClass==baseaction&&(*i).second.PRG!=130&&((*i).second.Type==2||(*i).second.Type==3))//��MC=0����type=1��3ʱ����ʾ
				{
					if((*i).second.VIP>0)
					{
						if(pPlayer->GetVIP()==0)
							baddmenu=false;
						//outstring_log("wuzhu vip %d %d",(*i).second.VIP,pPlayer->GetVIP());
					}
					if((*i).second.Level>pPlayer->getLevel())
					{
						baddmenu=false;
						//outstring_log("wuzhu Level %d %d",(*i).second.Level,pPlayer->getLevel());
					}
					if((*i).second.P_class>0)
					{
						if((*i).second.P_class!=pPlayer->getClass())
							baddmenu=false;
						//outstring_log("wuzhu P_class %d %d",(*i).second.P_class,pPlayer->getClass());
					}
					if((*i).second.PTeam==67)//469���ˣ�67���� ����ֵ����Ϊ��ȫ��������
					{
						if(!isbl(pPlayer))
							baddmenu=false;
					}
					else
					{
						if((*i).second.PTeam==469)
						{
							if(isbl(pPlayer))
								baddmenu=false;
						}	
					}
					//outstring_log("wuzhu PTeam %d %d",(*i).second.PTeam,pPlayer->getRace());
					if(baddmenu||pPlayer->isGameMaster())
					{
						++count;
						TeleportList.push_back(TeleportHolder((*i).first, (*i).second));
					}
				}
			}
			if(!TeleportList.empty())
			{
				count=0;
				TeleportList.sort();
				for(std::list<TeleportHolder>::iterator th = TeleportList.begin();th!=TeleportList.end();++th)
				{
					++count;
					if(count>=16)
						break;
					if(th->Teleport.PRG==90)
						pPlayer->ADD_GOSSIP_ITEM(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.Action);
					else
					{
						if(th->Teleport.PRG==110||th->Teleport.PRG==111)
							pPlayer->ADD_GOSSIP_ITEM_EXTENDED(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.SpellID,th->Teleport.Message,th->Teleport.Money?th->Teleport.Money:th->Teleport.Integral,false);
						else
							pPlayer->ADD_GOSSIP_ITEM_EXTENDED(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.Action,th->Teleport.Message,th->Teleport.Money?th->Teleport.Money:th->Teleport.Integral,false);
					}
				}	
			}
		}		
		pPlayer->SEND_GOSSIP_MENU(80006,_Item->GetObjectGuid());
	}
}

bool GossipDBItemSelect(Player *pPlayer, Item *_Item, uint32 sender, uint32 action )
{
	uint32 baseaction=action-GOSSIP_ACTION_INFO_DEF;
	if (!isstone(pPlayer))
	{
		switch(sender) {
			// ��ѡ��
				case GOSSIP_SENDER_MAIN :
					SendDefaultDBItemMenu(pPlayer, _Item, action);
					break;
			//���� 
				case 5 :
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==2||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										WUZHU_Common::SendMoneyError(pPlayer);
										break;
									}
								}
								else
								if((*i).second.Integral>0)
								{
									if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
									{
										btelete=2;//��Ҫ����
									}
									else
									{
										pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
										break;
									}
								}
								UNORDERED_MAP<uint32, WUZHU_GameTele>::iterator j = pSystemMgr.GameTele_Map.find(baseaction);
								if(j!=pSystemMgr.GameTele_Map.end())
								{
									pPlayer->TeleportTo((*j).second.target_mapId,(*j).second.target_X,
										(*j).second.target_Y,(*j).second.target_Z,(*j).second.target_Orientation);
									if(btelete==1)
										pPlayer->ModifyMoney(0-(*i).second.Money);
									else
										if(btelete==2)
											pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
								} 
								break;
							}
						}
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					//�����е�
				case 10:
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==2||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										WUZHU_Common::SendMoneyError(pPlayer);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
								 pPlayer->SetTaxiCheater(true);
								 if(btelete==1)
								 {
									pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
									 if(btelete==2)
								 {
									 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
								 }
								 pPlayer->GetSession()->SendAreaTriggerMessage(" pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-148,pPlayer) ");
								 break;
							}
						}
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					//����
				case 20 :
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==2||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										WUZHU_Common::SendMoneyError(pPlayer);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->SEND_BANKERLIST(_Item->GetObjectGuid() );
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
								 {
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
								 }
								break;
							}
						}
					}	
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 22://��
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==2||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										WUZHU_Common::SendMoneyError(pPlayer);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->GetSession()->SendBindPoint();
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
								 {
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
								 }
									break;
							}
						}
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;	
				case 40://����װ��
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==2||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										WUZHU_Common::SendMoneyError(pPlayer);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->DurabilityRepairAll(true,1,false);
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
								 {
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
								 }
									break;
							}
						}
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 70://�̵�
					pPlayer->GetSession()->OpenShop(_Item->GetObjectGuid(),action-GOSSIP_ACTION_INFO_DEF);					
					break;
				case 90://��ȡ����
					//��ȡ��ǰʱ��
					{
						//uint32 ingametime=WorldTimer::getMSTimeDiff(pPlayer->GetInGameTime(),getMSTime())/1000;
						//if(ingametime > 60) // �������������ʱ�����1���ӣ�������Լ���(��λ:��)
						//{
						//	UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						//	for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						//	{
						//		if ((*i).second.Action==baseaction&&((*i).second.Type==2||(*i).second.Type==3))
						//		{
						//			float money = 0;
						//			//TODO:����ϵͳ��������Ϸʱ����������
						//			//���򣺹���=1����1G
						//			money = (float)(ingametime / 60 *(*i).second.Money);

						//			pPlayer->ModifyMoney(int32(money));      //����������ý��
						//			pPlayer->SetInGameTime(getMSTime());   //�����������ʱ�����
						//			pPlayer->GetSession()->SendAreaTriggerMessage(" |cff7000ff��ȡ�˹��ʣ�%d���.|r ",int32(money)/10000);
						//			break;

						//		}
						//	}
						//}
						//else
						//{
						//	pPlayer->GetSession()->SendAreaTriggerMessage(" |cffff0000��ȡ����ʱ����̫��.|r ");
						//}
						pPlayer->CLOSE_GOSSIP_MENU();
						break;
					}
				case 110://��������
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.SpellID==baseaction&&((*i).second.Type==2||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										WUZHU_Common::SendMoneyError(pPlayer);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->CastSpell(pPlayer,(*i).second.SpellID,true);
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
								 {
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
								 }
									break;
							}
						}
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 111://����ģ��
					{
						if(pPlayer->getClass()==CLASS_HUNTER)
						{
							Pet* pet = pPlayer->GetPet();
							if(!pet||pet->getPetType()!=HUNTER_PET)
							{
								pPlayer->GetSession()->SendAreaTriggerMessage(" |cffff0000��û����Ц�ɣ�������?|r ");
								break;
							}
							if(!pPlayer->IsWithinDistInMap(pet, MAX_VISIBILITY_DISTANCE))
							{
								pPlayer->GetSession()->SendAreaTriggerMessage(" |cffff0000��ĳ���̫���ߣ��ܵ�̫Զ��.|r ");
								break;
							}
							UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
							for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
							{
								if ((*i).second.SpellID==baseaction&&((*i).second.Type==2||(*i).second.Type==3))
								{
									uint32 btelete=0;//���ܴ���
									if((*i).second.Money>0)
									{
										if(pPlayer->GetMoney() >= (*i).second.Money)
										{
											btelete=1;//��Ҫmoney
										}
										else
										{
											WUZHU_Common::SendMoneyError(pPlayer);
											break;
										}
									}
									else
										if((*i).second.Integral>0)
										{
											if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
											{
												btelete=2;//��Ҫ����
											}
											else
											{
												pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
												break;
											}
										}
										pet->SetDisplayId((*i).second.SpellID);
										pet->SetNativeDisplayId((*i).second.SpellID);
										pet->SetByteValue(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_RENAMED);
										//pPlayer->CastSpell(pPlayer,(*i).second.SpellID,true);
										if(btelete==1)
										{
											pPlayer->ModifyMoney(0-(*i).second.Money);									 
										}
										else
										{
											if(btelete==2)
											{
												pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
											}
										}
										break;
								}
							}
						}
						else
						{
							pPlayer->GetSession()->SendAreaTriggerMessage(" |cffff0000Ŀǰ�������ֻ�����˿���.|r ");
							break;
						}						
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 120://���ֲ�ѯ
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==2||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										WUZHU_Common::SendMoneyError(pPlayer);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->GetSession()->SendAreaTriggerMessage(" |cffaa0080�㵱ǰ���л��֣�%u.|r ",pPlayer->GetVIP_Integral());
									if(btelete==1)
									{
										pPlayer->ModifyMoney(0-(*i).second.Money);									 
									}
									else
									{
										if(btelete==2)
										{
											pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
										}
									}
									break;
							}
						}
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 130://���ʹ��
					{
						if(!pPlayer->isDead())
							break;
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==2||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										WUZHU_Common::SendMoneyError(pPlayer);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer-> GetSession()->SendSpiritResurrect();
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
								 {
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
								 }
									break;
							}
						}
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
		}
	}
	return true;
}


bool GossipDBTeleportHello(Player *pPlayer, Creature *_Creature)
{
	if(pPlayer->isInCombat())
	{ 
		pPlayer->GetSession()->SendAreaTriggerMessage(" |cffff0000�޷���ս����ʹ�ñ�����.|r ");
		pPlayer->CLOSE_GOSSIP_MENU();
	}
	else
		if(pPlayer->IsTaxiFlying()||pPlayer->IsMounted())
		{ 
			pPlayer->GetSession()->SendAreaTriggerMessage(" |cffff0000�޷���������ʹ�ñ�����.|r ");
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		else
		{
			if (!pPlayer->isDead())
			{ 
				UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
				std::list<TeleportHolder> TeleportList;
				TeleportList.clear();
				uint32 count=0;//����16���Ͳ�����
				bool baddmenu=true;
				for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
				{
					if(count>=16)
						break;				
					if ((*i).second.MenuClass==0&&(*i).second.PRG!=130&&((*i).second.Type==1||(*i).second.Type==3))//��MC=0����type=1��3ʱ����ʾ
					{
						baddmenu=true;
						if((*i).second.VIP>0)
						{
							if(pPlayer->GetVIP()==0)
								baddmenu=false;
						}
						if((*i).second.Level>pPlayer->getLevel())
							baddmenu=false;
						if((*i).second.P_class>0)
						{
							if((*i).second.P_class!=pPlayer->getClass())
								baddmenu=false;
						}
						if((*i).second.PTeam==67)//469���ˣ�67���� ����ֵ����Ϊ��ȫ��������
						{
							if(!isbl(pPlayer))
								baddmenu=false;
						}
						else
							if((*i).second.PTeam==469)
							{
								if(isbl(pPlayer))
									baddmenu=false;
							}	
							if(baddmenu||pPlayer->isGameMaster())
							{
								++count;
								TeleportList.push_back(TeleportHolder((*i).first, (*i).second));								
							}
					}
				}

				if(!TeleportList.empty())
				{
					count=0;
					TeleportList.sort();
					for(std::list<TeleportHolder>::iterator th = TeleportList.begin();th!=TeleportList.end();++th)
					{
						++count;
						if (count>=16)
						{
							break;
						}
						if(th->Teleport.PRG==90)
							pPlayer->ADD_GOSSIP_ITEM(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.Action);
						else
						{
							if(th->Teleport.PRG==110||th->Teleport.PRG==111)								
								pPlayer->ADD_GOSSIP_ITEM_EXTENDED(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.SpellID,th->Teleport.Message,th->Teleport.Money?th->Teleport.Money:th->Teleport.Integral,false);
							else									
								pPlayer->ADD_GOSSIP_ITEM_EXTENDED(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.Action,th->Teleport.Message,th->Teleport.Money?th->Teleport.Money:th->Teleport.Integral,false);
						}
					}
				}
				
			}
			else 
				if(pPlayer->isDead())
				{
					UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;

					bool baddmenu=true;
					for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
					{
						if ((*i).second.MenuClass==0&&(*i).second.PRG==130&&((*i).second.Type==1||(*i).second.Type==3))//��MC=0����type=1��3ʱ����ʾ
						{
							baddmenu=true;
							if((*i).second.VIP>0)
							{
								if(pPlayer->GetVIP()==0)
									baddmenu=false;
							}
							if((*i).second.Level>pPlayer->getLevel())
								baddmenu=false;
							if((*i).second.P_class>0)
							{
								if((*i).second.P_class!=pPlayer->getClass())
									baddmenu=false;
							}
							if((*i).second.PTeam==67)//469���ˣ�67���� ����ֵ����Ϊ��ȫ��������
							{
								if(!isbl(pPlayer))
									baddmenu=false;
							}
							else
								if((*i).second.PTeam==469)
								{
									if(isbl(pPlayer))
										baddmenu=false;
								}	
								if(baddmenu||pPlayer->isGameMaster())
								{
									pPlayer->ADD_GOSSIP_ITEM_EXTENDED((*i).second.Icon,(*i).second.Title,(*i).second.PRG,GOSSIP_ACTION_INFO_DEF+(*i).second.Action,(*i).second.Message,(*i).second.Money?(*i).second.Money:(*i).second.Integral,false);
								}

								break;
						}
					}
				} 
				pPlayer->SEND_GOSSIP_MENU(80001,_Creature->GetObjectGuid());
		}

		return true;
}

void SendDefaultDBTeleportMenu(Player *pPlayer, Creature *_Creature, uint32 action)
{
	uint32 baseaction=action-GOSSIP_ACTION_INFO_DEF;
	if(pPlayer->isInCombat())
	{ 
		pPlayer->GetSession()->SendAreaTriggerMessage(" |cffff0000�޷���ս����ʹ�ñ�����.|r ");
		pPlayer->CLOSE_GOSSIP_MENU();
	}
	else
		if(pPlayer->IsTaxiFlying()||pPlayer->IsMounted())
		{ 
			pPlayer->GetSession()->SendAreaTriggerMessage(" |cffff0000�޷���������ʹ�ñ�����.|r ");
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		else
		{
			if (!pPlayer->isDead())
			{ 
				UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
				std::list<TeleportHolder> TeleportList;
				TeleportList.clear();
				uint32 count=0;//����16���Ͳ�����
				bool baddmenu=true;
				for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
				{
					baddmenu=true;
					if(count>=16)
						break;				
					if ((*i).second.MenuClass==baseaction&&(*i).second.PRG!=130&&((*i).second.Type==1||(*i).second.Type==3))//��MC=0����type=1��3ʱ����ʾ
					{
						if((*i).second.VIP>0)
						{
							if(pPlayer->GetVIP()==0)
								baddmenu=false;
						}
						if((*i).second.Level>pPlayer->getLevel())
							baddmenu=false;
						if((*i).second.P_class>0)
						{
							if((*i).second.P_class!=pPlayer->getClass())
								baddmenu=false;
						}
						if((*i).second.PTeam==67)//469���ˣ�67���� ����ֵ����Ϊ��ȫ��������
						{
							if(!isbl(pPlayer))
								baddmenu=false;
						}
						else
							if((*i).second.PTeam==469)
							{
								if(isbl(pPlayer))
									baddmenu=false;
							}	
							if(baddmenu||pPlayer->isGameMaster())
							{
								++count;
								TeleportList.push_back(TeleportHolder((*i).first, (*i).second));
								
							}
					}
				}
				if(!TeleportList.empty())
				{
					count=0;
					TeleportList.sort();
					for(std::list<TeleportHolder>::iterator th = TeleportList.begin();th!=TeleportList.end();++th)
					{
						++count;
						if (count>=16)
						{
							break;
						}
						if(th->Teleport.PRG==90)
							pPlayer->ADD_GOSSIP_ITEM(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.Action);
						else
						{
							if(th->Teleport.PRG==110||th->Teleport.PRG==111)
								pPlayer->ADD_GOSSIP_ITEM_EXTENDED(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.SpellID,th->Teleport.Message,th->Teleport.Money?th->Teleport.Money:th->Teleport.Integral,false);
							else
								pPlayer->ADD_GOSSIP_ITEM_EXTENDED(th->Teleport.Icon,th->Teleport.Title,th->Teleport.PRG,GOSSIP_ACTION_INFO_DEF+th->Teleport.Action,th->Teleport.Message,th->Teleport.Money?th->Teleport.Money:th->Teleport.Integral,false);
						}
					}
				}
			}		
			pPlayer->SEND_GOSSIP_MENU(80007,_Creature->GetObjectGuid());
		}
}

bool GossipDBTeleportSelect(Player *pPlayer, Creature *_Creature, uint32 sender, uint32 action )
{
	uint32 baseaction=action-GOSSIP_ACTION_INFO_DEF;
	if (!isstone(pPlayer))
	{
		switch(sender) {
			// ��ѡ��
				case GOSSIP_SENDER_MAIN :
					SendDefaultDBTeleportMenu(pPlayer, _Creature, action);
					break;
					//���� 
				case 5 :
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==1||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									UNORDERED_MAP<uint32, WUZHU_GameTele>::iterator j = pSystemMgr.GameTele_Map.find(baseaction);
									if(j!=pSystemMgr.GameTele_Map.end())
									{
										pPlayer->TeleportTo((*j).second.target_mapId,(*j).second.target_X,
											(*j).second.target_Y,(*j).second.target_Z,(*j).second.target_Orientation);
										if(btelete==1)
											pPlayer->ModifyMoney(0-(*i).second.Money);
										else
											if(btelete==2)
												pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									} 
									break;
							}
						}
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					//�����е�
				case 10:
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==1||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->SetTaxiCheater(true);
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
									 pPlayer->GetSession()->SendAreaTriggerMessage(" pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-148,pPlayer) ");
									 break;
							}
						}
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
					//����
				case 20 :
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==1||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->SEND_BANKERLIST(_Creature->GetObjectGuid() );
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
								 {
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
								 }
									break;
							}
						}
					}					
					break;
				case 22://��
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==1||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->GetSession()->SendBindPoint();
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
								 {
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
								 }
									break;
							}
						}
					}					
					pPlayer->CLOSE_GOSSIP_MENU();
					break;	
				case 40://����װ��
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==1||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->DurabilityRepairAll(true,1,false);
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
								 {
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
								 }
									break;
							}
						}
					}					
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 90://��ȡ����
					//��ȡ��ǰʱ��
					{
						//uint32 ingametime=WorldTimer::getMSTimeDiff(pPlayer->GetInGameTime(),getMSTime())/1000;
						//if(ingametime > 60) // �������������ʱ�����1���ӣ�������Լ���(��λ:��)
						//{
						//	UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						//	for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						//	{
						//		if ((*i).second.Action==baseaction&&((*i).second.Type==1||(*i).second.Type==3))
						//		{
						//			float money = 0;
						//			//TODO:����ϵͳ��������Ϸʱ����������
						//			//���򣺹���=1����1G
						//			money = (float)(ingametime / 60 *(*i).second.Money);

						//			pPlayer->ModifyMoney(int32(money));      //����������ý��
						//			pPlayer->SetInGameTime(getMSTime());   //�����������ʱ�����
						//			pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-149,pPlayer),int32(money)/10000);
						//			break;

						//		}
						//	}
						//}
						//else
						//{
						//	pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-139,pPlayer));
						//}
						pPlayer->CLOSE_GOSSIP_MENU();
						break;
					}
				case 110://��������
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.SpellID==baseaction&&((*i).second.Type==1||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->CastSpell(pPlayer,(*i).second.SpellID,true);
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
								 {
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
								 }
									break;
							}
						}
					}					
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 111://����ģ��
					{
						if(pPlayer->getClass()==CLASS_HUNTER)
						{
							Pet* pet = pPlayer->GetPet();
							if(!pet||pet->getPetType()!=HUNTER_PET)
							{
								pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-150,pPlayer));
								break;
							}
							if(!pPlayer->IsWithinDistInMap(pet, MAX_VISIBILITY_DISTANCE))
							{
								pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-151,pPlayer));
								break;
							}
							UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
							for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
							{
								if ((*i).second.SpellID==baseaction&&((*i).second.Type==1||(*i).second.Type==3))
								{
									uint32 btelete=0;//���ܴ���
									if((*i).second.Money>0)
									{
										if(pPlayer->GetMoney() >= (*i).second.Money)
										{
											btelete=1;//��Ҫmoney
										}
										else
										{
											WUZHU_Common::SendMoneyError(pPlayer);
											break;
										}
									}
									else
										if((*i).second.Integral>0)
										{
											if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
											{
												btelete=2;//��Ҫ����
											}
											else
											{
												pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
												break;
											}
										}
										pet->SetDisplayId((*i).second.SpellID);
										pet->SetNativeDisplayId((*i).second.SpellID);
										pet->SetByteValue(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_RENAMED);
										//pPlayer->CastSpell(pPlayer,(*i).second.SpellID,true);
										if(btelete==1)
										{
											pPlayer->ModifyMoney(0-(*i).second.Money);									 
										}
										else
										{
											if(btelete==2)
											{
												pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
											}
										}
										break;
								}
							}
						}
						else
						{
							pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-152,pPlayer));
							break;
						}						
					}
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 120://���ֲ�ѯ
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==1||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-45,pPlayer),pPlayer->GetVIP_Integral());
									if(btelete==1)
									{
										pPlayer->ModifyMoney(0-(*i).second.Money);									 
									}
									else
									{
										if(btelete==2)
										{
											pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
										}
									}
									break;
							}
						}
					}					
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 130://���ʹ��
					{
						UNORDERED_MAP<uint32, WUZHU_Teleport_Template>::iterator i;
						for (i = pSystemMgr.Teleport_Template_Map.begin(); i != pSystemMgr.Teleport_Template_Map.end(); ++i)
						{
							if ((*i).second.Action==baseaction&&((*i).second.Type==1||(*i).second.Type==3))
							{
								uint32 btelete=0;//���ܴ���
								if((*i).second.Money>0)
								{
									if(pPlayer->GetMoney() >= (*i).second.Money)
									{
										btelete=1;//��Ҫmoney
									}
									else
									{
										pPlayer->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
										break;
									}
								}
								else
									if((*i).second.Integral>0)
									{
										if(pPlayer->GetVIP_Integral() >= (*i).second.Integral)
										{
											btelete=2;//��Ҫ����
										}
										else
										{
											pPlayer->GetSession()->SendAreaTriggerMessage(pPlayer->GetWUZHUString(WUZHU_TEXT_SOURCE_RANGE-48,pPlayer));
											break;
										}
									}
									pPlayer-> GetSession()->SendSpiritResurrect();
									if(btelete==1)
								 {
									 pPlayer->ModifyMoney(0-(*i).second.Money);									 
								 }
								 else
								 {
									 if(btelete==2)
									 {
										 pPlayer->ModifyVIP_Integral(0-(*i).second.Integral);
									 }
								 }
									break;
							}
						}
					}					
					pPlayer->CLOSE_GOSSIP_MENU();
					break;
				case 140://�������˵�
					GossipDBTeleportHello(pPlayer,_Creature);
					break;
		}
	}
	return true;
}



void AddSC_WUZHU_DBTeleport() 
{ 
	Script *newscript; 

	newscript = new Script; 
	newscript->Name="WUZHUDBTeleport"; 
	newscript->pGossipHello = &GossipDBTeleportHello; 
	newscript->pGossipSelect = &GossipDBTeleportSelect;
	newscript->RegisterSelf(); 


	newscript = new Script; 
	newscript->Name="WUZHUDBItem"; 
	newscript->pItemUse= &GossipDBItemHello; 
	newscript->pGossipItemSelect = &GossipDBItemSelect; 
	newscript->RegisterSelf(); 
}