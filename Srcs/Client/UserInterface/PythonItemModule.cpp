#include "StdAfx.h"
#include "PythonItem.h"

#include "../gamelib/ItemManager.h"
#include "../gamelib/GameLibDefines.h"
#include "InstanceBase.h"
#include "AbstractApplication.h"

extern int TWOHANDED_WEWAPON_ATT_SPEED_DECREASE_VALUE;

PyObject * itemSetUseSoundFileName(PyObject * poSelf, PyObject * poArgs)
{
	int iUseSound;
	if (!PyTuple_GetInteger(poArgs, 0, &iUseSound))
		return Py_BadArgument();

	char* szFileName;
	if (!PyTuple_GetString(poArgs, 1, &szFileName))
		return Py_BadArgument();

	CPythonItem& rkItem=CPythonItem::Instance();
	rkItem.SetUseSoundFileName(iUseSound, szFileName);
	return Py_BuildNone();
}

PyObject * itemSetDropSoundFileName(PyObject * poSelf, PyObject * poArgs)
{
	int iDropSound;
	if (!PyTuple_GetInteger(poArgs, 0, &iDropSound))
		return Py_BadArgument();

	char* szFileName;
	if (!PyTuple_GetString(poArgs, 1, &szFileName))
		return Py_BadArgument();

	CPythonItem& rkItem=CPythonItem::Instance();
	rkItem.SetDropSoundFileName(iDropSound, szFileName);
	return Py_BuildNone();
}

PyObject * itemSelectItem(PyObject * poSelf, PyObject * poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BadArgument();

	if (!CItemManager::Instance().SelectItemData(iIndex))
	{
		TraceError("Cannot find item by %d", iIndex);
		CItemManager::Instance().SelectItemData(60001);
	}

	return Py_BuildNone();
}

PyObject * itemGetItemName(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("s", pItemData->GetName());
}

PyObject * itemGetItemDescription(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("s", pItemData->GetDescription());
}

PyObject * itemGetItemSummary(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("s", pItemData->GetSummary());
}

PyObject * itemGetIconImage(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

//	if (CItemData::ITEM_TYPE_SKILLBOOK == pItemData->GetType())
//	{
//		char szItemName[64+1];
//		_snprintf(szItemName, "d:/ymir work/ui/items/etc/book_%02d.sub", );
//		CGraphicImage * pImage = (CGraphicImage *)CResourceManager::Instance().GetResourcePointer(szItemName);
//	}

	return Py_BuildValue("i", pItemData->GetIconImage());
}

PyObject * itemGetIconImageFileName(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	CGraphicSubImage * pImage = pItemData->GetIconImage();
	if (!pImage)
		return Py_BuildValue("s", "Noname");

	return Py_BuildValue("s", pImage->GetFileName());
}

PyObject * itemGetItemSize(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("(ii)", 1, pItemData->GetSize());
}

PyObject * itemGetItemType(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("i", pItemData->GetType());
}

PyObject * itemGetItemSubType(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("i", pItemData->GetSubType());
}

PyObject * itemGetIBuyItemPrice(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();

	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("i", pItemData->GetIBuyItemPrice());
}

PyObject * itemGetISellItemPrice(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();

	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("i", pItemData->GetISellItemPrice());
}

PyObject * itemIsAntiFlag(PyObject * poSelf, PyObject * poArgs)
{
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 0, &iFlag))
		return Py_BadArgument();

	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("i", pItemData->IsAntiFlag(iFlag));
}

PyObject * itemIsFlag(PyObject * poSelf, PyObject * poArgs)
{
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 0, &iFlag))
		return Py_BadArgument();

	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("i", pItemData->IsFlag(iFlag));
}

PyObject * itemIsWearableFlag(PyObject * poSelf, PyObject * poArgs)
{
	int iFlag;
	if (!PyTuple_GetInteger(poArgs, 0, &iFlag))
		return Py_BadArgument();

	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("i", pItemData->IsWearableFlag(iFlag));
}

PyObject * itemIs1GoldItem(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("no selected item data");

	return Py_BuildValue("i", pItemData->IsFlag(CItemData::ITEM_FLAG_COUNT_PER_1GOLD));
}

PyObject * itemGetLimit(PyObject * poSelf, PyObject * poArgs)
{
	int iValueIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iValueIndex))
		return Py_BadArgument();

	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Not yet select item data");

	CItemData::TItemLimit ItemLimit;
	if (!pItemData->GetLimit(iValueIndex, &ItemLimit))
		return Py_BuildException();

	return Py_BuildValue("ii", ItemLimit.bType, ItemLimit.lValue);
}

PyObject * itemGetAffect(PyObject * poSelf, PyObject * poArgs)
{
	int iValueIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iValueIndex))
		return Py_BadArgument();

	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Not yet select item data");

	CItemData::TItemApply ItemApply;
	if (!pItemData->GetApply(iValueIndex, &ItemApply))
		return Py_BuildException();

	if ((CItemData::APPLY_ATT_SPEED == ItemApply.bType) && (CItemData::ITEM_TYPE_WEAPON == pItemData->GetType()) && (CItemData::WEAPON_TWO_HANDED == pItemData->GetSubType()))
	{
		ItemApply.lValue -= TWOHANDED_WEWAPON_ATT_SPEED_DECREASE_VALUE;
	}

	return Py_BuildValue("ii", ItemApply.bType, ItemApply.lValue);
}

PyObject * itemGetValue(PyObject * poSelf, PyObject * poArgs)
{
	int iValueIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iValueIndex))
		return Py_BadArgument();

	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Not yet select item data");

	return Py_BuildValue("i", pItemData->GetValue(iValueIndex));
}

PyObject * itemGetSocket(PyObject * poSelf, PyObject * poArgs)
{
	int iValueIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iValueIndex))
		return Py_BadArgument();

	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Not yet select item data");

	return Py_BuildValue("i", pItemData->GetSocket(iValueIndex));
}

PyObject * itemGetIconInstance(PyObject * poSelf, PyObject * poArgs)
{
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Not yet select item data");

	CGraphicSubImage * pImage = pItemData->GetIconImage();
	if (!pImage)
		return Py_BuildException("Cannot get icon image by %d", pItemData->GetIndex());

	CGraphicImageInstance * pImageInstance = CGraphicImageInstance::New();
	pImageInstance->SetImagePointer(pImage);

	return Py_BuildValue("i", pImageInstance);
}

PyObject * itemDeleteIconInstance(PyObject * poSelf, PyObject * poArgs)
{
	int iHandle;
	if (!PyTuple_GetInteger(poArgs, 0, &iHandle))
		return Py_BadArgument();

	CGraphicImageInstance::Delete((CGraphicImageInstance *) iHandle);

	return Py_BuildNone();
}

PyObject * itemIsEquipmentVID(PyObject * poSelf, PyObject * poArgs)
{
	int iItemVID;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemVID))
		return Py_BadArgument();

	CItemManager::Instance().SelectItemData(iItemVID);
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Not yet select item data");

	return Py_BuildValue("i", pItemData->IsEquipment());
}

PyObject* itemGetUseType(PyObject * poSelf, PyObject * poArgs)
{
	int iItemVID;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemVID))
		return Py_BadArgument();

	CItemManager::Instance().SelectItemData(iItemVID);
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Can't find select item data");

	return Py_BuildValue("s", pItemData->GetUseTypeString());
}

PyObject * itemIsRefineScroll(PyObject * poSelf, PyObject * poArgs)
{
	int iItemIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemIndex))
		return Py_BadArgument();

	CItemManager::Instance().SelectItemData(iItemIndex);
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Can't find select item data");

	if (pItemData->GetType() != CItemData::ITEM_TYPE_USE)
		return Py_BuildValue("i", FALSE);

	switch (pItemData->GetSubType())
	{
		case CItemData::USE_TUNING:
			return Py_BuildValue("i", TRUE);
			break;
	}

	return Py_BuildValue("i", FALSE);
}

PyObject * itemIsDetachScroll(PyObject * poSelf, PyObject * poArgs)
{
	int iItemIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemIndex))
		return Py_BadArgument();

	CItemManager::Instance().SelectItemData(iItemIndex);
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Can't find select item data");

	int iType = pItemData->GetType();
	int iSubType = pItemData->GetSubType();
	if (iType == CItemData::ITEM_TYPE_USE)
	if (iSubType == CItemData::USE_DETACHMENT)
	{
		return Py_BuildValue("i", TRUE);
	}

	return Py_BuildValue("i", FALSE);
}

PyObject * itemCanAddToQuickSlotItem(PyObject * poSelf, PyObject * poArgs)
{
	int iItemIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemIndex))
		return Py_BadArgument();

	CItemManager::Instance().SelectItemData(iItemIndex);
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Can't find select item data");

	if (CItemData::ITEM_TYPE_USE == pItemData->GetType() || CItemData::ITEM_TYPE_QUEST == pItemData->GetType())
	{
		return Py_BuildValue("i", TRUE);
	}

	return Py_BuildValue("i", FALSE);
}

PyObject * itemIsKey(PyObject * poSelf, PyObject * poArgs)
{
	int iItemIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemIndex))
		return Py_BadArgument();

	CItemManager::Instance().SelectItemData(iItemIndex);
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Can't find select item data");

	if (CItemData::ITEM_TYPE_TREASURE_KEY == pItemData->GetType())
	{
		return Py_BuildValue("i", TRUE);
	}

	return Py_BuildValue("i", FALSE);
}

PyObject * itemIsMetin(PyObject * poSelf, PyObject * poArgs)
{
	int iItemIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iItemIndex))
		return Py_BadArgument();

	CItemManager::Instance().SelectItemData(iItemIndex);
	CItemData * pItemData = CItemManager::Instance().GetSelectedItemDataPointer();
	if (!pItemData)
		return Py_BuildException("Can't find select item data");

	if (CItemData::ITEM_TYPE_METIN == pItemData->GetType())
	{
		return Py_BuildValue("i", TRUE);
	}

	return Py_BuildValue("i", FALSE);
}

PyObject * itemRender(PyObject * poSelf, PyObject * poArgs)
{
	CPythonItem::Instance().Render();
	return Py_BuildNone();
}

PyObject * itemUpdate(PyObject * poSelf, PyObject * poArgs)
{
	IAbstractApplication& rkApp=IAbstractApplication::GetSingleton();

	POINT ptMouse;
	rkApp.GetMousePosition(&ptMouse);

	CPythonItem::Instance().Update(ptMouse);
	return Py_BuildNone();
}

PyObject * itemCreateItem(PyObject * poSelf, PyObject * poArgs)
{
	int iVirtualID;
	if (!PyTuple_GetInteger(poArgs, 0, &iVirtualID))
		return Py_BadArgument();
	int iVirtualNumber;
	if (!PyTuple_GetInteger(poArgs, 1, &iVirtualNumber))
		return Py_BadArgument();

	float x;
	if (!PyTuple_GetFloat(poArgs, 2, &x))
		return Py_BadArgument();
	float y;
	if (!PyTuple_GetFloat(poArgs, 3, &y))
		return Py_BadArgument();
	float z;
	if (!PyTuple_GetFloat(poArgs, 4, &z))
		return Py_BadArgument();

	bool bDrop = true;
	PyTuple_GetBoolean(poArgs, 5, &bDrop);

	CPythonItem::Instance().CreateItem(iVirtualID, iVirtualNumber, x, y, z, bDrop);

	return Py_BuildNone();
}

PyObject * itemDeleteItem(PyObject * poSelf, PyObject * poArgs)
{
	int iVirtualID;
	if (!PyTuple_GetInteger(poArgs, 0, &iVirtualID))
		return Py_BadArgument();

	CPythonItem::Instance().DeleteItem(iVirtualID);
	return Py_BuildNone();
}

PyObject * itemPick(PyObject * poSelf, PyObject * poArgs)
{
	DWORD dwItemID;
	if (CPythonItem::Instance().GetPickedItemID(&dwItemID))
		return Py_BuildValue("i", dwItemID);
	else
		return Py_BuildValue("i", -1);
}

PyObject* itemLoadItemTable(PyObject* poSelf, PyObject* poArgs)
{
	char * szFileName;
	if (!PyTuple_GetString(poArgs, 0, &szFileName))
		return Py_BadArgument();

	CItemManager::Instance().LoadItemTable(szFileName);
	return Py_BuildNone();
}

#include "../UserInterface/Packet.h"

typedef struct SApplyInfo
{
	BYTE	bPointType;                          // APPLY -> POINT
} TApplyInfo;

int GetApplyPoint(int iApply)
{
	static const std::vector<TApplyInfo> aApplyInfo =
	{
		// Point Type
		{ POINT_NONE,			},   // APPLY_NONE,		0
		{ POINT_MAX_HP,		        },   // APPLY_MAX_HP,		1
		{ POINT_MAX_SP,		        },   // APPLY_MAX_SP,		2
		{ POINT_HT,			        },   // APPLY_CON,		3
		{ POINT_IQ,			        },   // APPLY_INT,		4
		{ POINT_ST,			        },   // APPLY_STR,		5
		{ POINT_DX,			        },   // APPLY_DEX,		6
		{ POINT_ATT_SPEED,		        },   // APPLY_ATT_SPEED,	7
		{ POINT_MOV_SPEED,		        },   // APPLY_MOV_SPEED,	8
		{ POINT_CASTING_SPEED,	        },   // APPLY_CAST_SPEED,	9
		{ POINT_HP_REGEN,			},   // APPLY_HP_REGEN,		10
		{ POINT_SP_REGEN,			},   // APPLY_SP_REGEN,		11
		{ POINT_POISON_PCT,		        },   // APPLY_POISON_PCT,	12
		{ POINT_STUN_PCT,		        },   // APPLY_STUN_PCT,		13
		{ POINT_SLOW_PCT,		        },   // APPLY_SLOW_PCT,		14
		{ POINT_CRITICAL_PCT,		},   // APPLY_CRITICAL_PCT,	15
		{ POINT_PENETRATE_PCT,	        },   // APPLY_PENETRATE_PCT,	16
		{ POINT_ATTBONUS_HUMAN,	        },   // APPLY_ATTBONUS_HUMAN,	17
		{ POINT_ATTBONUS_ANIMAL,	        },   // APPLY_ATTBONUS_ANIMAL,	18
		{ POINT_ATTBONUS_ORC,		},   // APPLY_ATTBONUS_ORC,	19
		{ POINT_ATTBONUS_MILGYO,	        },   // APPLY_ATTBONUS_MILGYO,	20
		{ POINT_ATTBONUS_UNDEAD,	        },   // APPLY_ATTBONUS_UNDEAD,	21
		{ POINT_ATTBONUS_DEVIL,	        },   // APPLY_ATTBONUS_DEVIL,	22
		{ POINT_STEAL_HP,		        },   // APPLY_STEAL_HP,		23
		{ POINT_STEAL_SP,		        },   // APPLY_STEAL_SP,		24
		{ POINT_MANA_BURN_PCT,	        },   // APPLY_MANA_BURN_PCT,	25
		{ POINT_DAMAGE_SP_RECOVER,	        },   // APPLY_DAMAGE_SP_RECOVER,26
		{ POINT_BLOCK,		        },   // APPLY_BLOCK,		27
		{ POINT_DODGE,		        },   // APPLY_DODGE,		28
		{ POINT_RESIST_SWORD,		},   // APPLY_RESIST_SWORD,	29
		{ POINT_RESIST_TWOHAND,	        },   // APPLY_RESIST_TWOHAND,	30
		{ POINT_RESIST_DAGGER,	        },   // APPLY_RESIST_DAGGER,	31
		{ POINT_RESIST_BELL,		},   // APPLY_RESIST_BELL,	32
		{ POINT_RESIST_FAN,		        },   // APPLY_RESIST_FAN,	33
		{ POINT_RESIST_BOW,		        },   // APPLY_RESIST_BOW,	34
		{ POINT_RESIST_FIRE,		},   // APPLY_RESIST_FIRE,	35
		{ POINT_RESIST_ELEC,		},   // APPLY_RESIST_ELEC,	36
		{ POINT_RESIST_MAGIC,		},   // APPLY_RESIST_MAGIC,	37
		{ POINT_RESIST_WIND,		},   // APPLY_RESIST_WIND,	38
		{ POINT_REFLECT_MELEE,	        },   // APPLY_REFLECT_MELEE,	39
		{ POINT_REFLECT_CURSE,	        },   // APPLY_REFLECT_CURSE,	40
		{ POINT_POISON_REDUCE,	        },   // APPLY_POISON_REDUCE,	41
		{ POINT_KILL_SP_RECOVER,	        },   // APPLY_KILL_SP_RECOVER,	42
		{ POINT_EXP_DOUBLE_BONUS,	        },   // APPLY_EXP_DOUBLE_BONUS,	43
		{ POINT_GOLD_DOUBLE_BONUS,	        },   // APPLY_GOLD_DOUBLE_BONUS,44
		{ POINT_ITEM_DROP_BONUS,	        },   // APPLY_ITEM_DROP_BONUS,	45
		{ POINT_POTION_BONUS,		},   // APPLY_POTION_BONUS,	46
		{ POINT_KILL_HP_RECOVERY,	        },   // APPLY_KILL_HP_RECOVER,	47
		{ POINT_IMMUNE_STUN,		},   // APPLY_IMMUNE_STUN,	48
		{ POINT_IMMUNE_SLOW,		},   // APPLY_IMMUNE_SLOW,	49
		{ POINT_IMMUNE_FALL,		},   // APPLY_IMMUNE_FALL,	50
		{ POINT_NONE,			},   // APPLY_SKILL,		51
		{ POINT_BOW_DISTANCE,		},   // APPLY_BOW_DISTANCE,	52
		{ POINT_ATT_GRADE_BONUS,	        },   // APPLY_ATT_GRADE,	53
		{ POINT_DEF_GRADE_BONUS,	        },   // APPLY_DEF_GRADE,	54
		{ POINT_MAGIC_ATT_GRADE_BONUS,      },   // APPLY_MAGIC_ATT_GRADE,	55
		{ POINT_MAGIC_DEF_GRADE_BONUS,      },   // APPLY_MAGIC_DEF_GRADE,	56
		{ POINT_CURSE_PCT,			},   // APPLY_CURSE_PCT,	57
		{ POINT_MAX_STAMINA			},   // APPLY_MAX_STAMINA	58
		{ POINT_ATTBONUS_WARRIOR		},   // APPLY_ATTBONUS_WARRIOR  59
		{ POINT_ATTBONUS_ASSASSIN		},   // APPLY_ATTBONUS_ASSASSIN 60
		{ POINT_ATTBONUS_SURA		},   // APPLY_ATTBONUS_SURA     61
		{ POINT_ATTBONUS_SHAMAN		},   // APPLY_ATTBONUS_SHAMAN   62
		{ POINT_ATTBONUS_MONSTER		},   //	APPLY_ATTBONUS_MONSTER  63
		{ POINT_ATT_BONUS		},   // 64 // APPLY_MALL_ATTBONUS
		{ POINT_MALL_DEFBONUS		},   // 65
		{ POINT_MALL_EXPBONUS		},   // 66 APPLY_MALL_EXPBONUS
		{ POINT_MALL_ITEMBONUS		},   // 67
		{ POINT_MALL_GOLDBONUS		},   // 68
		{ POINT_MAX_HP_PCT			},		// 69
		{ POINT_MAX_SP_PCT			},		// 70
		{ POINT_SKILL_DAMAGE_BONUS		},	// 71
		{ POINT_NORMAL_HIT_DAMAGE_BONUS	},	// 72

		// DEFEND_BONUS_ATTRIBUTES
		{ POINT_SKILL_DEFEND_BONUS		},	// 73
		{ POINT_NORMAL_HIT_DEFEND_BONUS	},	// 74
		// END_OF_DEFEND_BONUS_ATTRIBUTES

		{ POINT_PC_BANG_EXP_BONUS	},		// 75
		{ POINT_PC_BANG_DROP_BONUS	},		// 76

		{ POINT_NONE,		},

		{ POINT_RESIST_WARRIOR,		},
		{ POINT_RESIST_ASSASSIN,	},
		{ POINT_RESIST_SURA,		},
		{ POINT_RESIST_SHAMAN,		},
		{ POINT_ENERGY				},
		{ POINT_DEF_GRADE			},
		{ POINT_COSTUME_ATTR_BONUS	},
		{ POINT_MAGIC_ATT_BONUS_PER },
		{ POINT_MELEE_MAGIC_ATT_BONUS_PER		},			// 86 APPLY_MELEE_MAGIC_ATTBONUS_PER
		{ POINT_RESIST_ICE,			},   // APPLY_RESIST_ICE,	87
		{ POINT_RESIST_EARTH,		},   // APPLY_RESIST_EARTH,	88
		{ POINT_RESIST_DARK,		},   // APPLY_RESIST_DARK,	89
		{ POINT_RESIST_CRITICAL,		},   // APPLY_ANTI_CRITICAL_PCT,	90
		{ POINT_RESIST_PENETRATE,		},   // APPLY_ANTI_PENETRATE_PCT,	91

	#ifdef ENABLE_WOLFMAN_CHARACTER
		{ POINT_BLEEDING_REDUCE,		},	// APPLY_BLEEDING_REDUCE, 		92
		{ POINT_BLEEDING_PCT,			},	// APPLY_BLEEDING_PCT, 			93
		{ POINT_ATTBONUS_WOLFMAN,		},
		{ POINT_RESIST_WOLFMAN,			},
		{ POINT_RESIST_CLAW,			},
	#else
		{ POINT_NONE,					},	// APPLY_BLEEDING_REDUCE, 		92
		{ POINT_NONE,					},	// APPLY_BLEEDING_PCT, 			93
		{ POINT_NONE,					},
		{ POINT_NONE,					},
		{ POINT_NONE,					},
	#endif

	#ifdef ENABLE_ACCE_COSTUME_SYSTEM
		{ POINT_ACCEDRAIN_RATE,			},	// APPLY_ACCEDRAIN_RATE,		97
	#else
		{ POINT_NONE,			},			// APPLY_ACCEDRAIN_RATE,		97
	#endif

	#ifdef ENABLE_MAGIC_REDUCTION_SYSTEM
		{ POINT_RESIST_MAGIC_REDUCTION,	},	// APPLY_RESIST_MAGIC_REDUCTION,98
	#else
		{ POINT_NONE,					},	// APPLY_RESIST_MAGIC_REDUCTION,98
	#endif

		{ POINT_ENCHANT_ELECT,			},	// APPLY_ENCHANT_ELECT,99
		{ POINT_ENCHANT_FIRE,			},	// APPLY_ENCHANT_FIRE,100
		{ POINT_ENCHANT_ICE,			},	// APPLY_ENCHANT_ICE,101
		{ POINT_ENCHANT_WIND,			},	// APPLY_ENCHANT_WIND,102
		{ POINT_ENCHANT_EARTH,			},	// APPLY_ENCHANT_EARTH,103
		{ POINT_ENCHANT_DARK,			},	// APPLY_ENCHANT_DARK,104

		{ POINT_ATTBONUS_CZ,			},	// APPLY_ATTBONUS_CZ,105
		{ POINT_ATTBONUS_INSECT,		},	// APPLY_ATTBONUS_INSECT,106
		{ POINT_ATTBONUS_DESERT,		},	// APPLY_ATTBONUS_DESERT,107
		{ POINT_ATTBONUS_SWORD,			},	// APPLY_ATTBONUS_SWORD,108
		{ POINT_ATTBONUS_TWOHAND,		},	// APPLY_ATTBONUS_TWOHAND,109
		{ POINT_ATTBONUS_DAGGER,		},	// APPLY_ATTBONUS_DAGGER,110
		{ POINT_ATTBONUS_BELL,			},	// APPLY_ATTBONUS_BELL,111
		{ POINT_ATTBONUS_FAN,			},	// APPLY_ATTBONUS_FAN,112
		{ POINT_ATTBONUS_BOW,			},	// APPLY_ATTBONUS_BOW,113
	#ifdef ENABLE_WOLFMAN_CHARACTER
		{ POINT_ATTBONUS_CLAW,			},	// APPLY_ATTBONUS_CLAW,114
	#else
		{ POINT_NONE,					},	// APPLY_ATTBONUS_CLAW,114
	#endif

		{ POINT_RESIST_HUMAN,			},	// APPLY_RESIST_HUMAN,115
		{ POINT_RESIST_MOUNT_FALL,		},	// APPLY_RESIST_MOUNT_FALL,116
		{ POINT_NONE,					},	// APPLY_UNK117 (unimplemented)
	#ifdef ENABLE_MOUNT_COSTUME_EX_SYSTEM
		{ POINT_MOUNT,					},	// APPLY_MOUNT,118
	#else
		{ POINT_NONE,					},	// APPLY_MOUNT,118
	#endif
	};

	if (iApply >= aApplyInfo.size())
		return -1;

	return aApplyInfo[iApply].bPointType;
}

PyObject* itemGetApplyPoint(PyObject* poSelf, PyObject* poArgs)
{
	int iApply = -1;
	if (!PyTuple_GetInteger(poArgs, 0, &iApply))
		return Py_BadArgument();

	return Py_BuildValue("i", GetApplyPoint(iApply));
}

void initItem()
{
	static PyMethodDef s_methods[] =
	{
		{ "SetUseSoundFileName",			itemSetUseSoundFileName,				METH_VARARGS },
		{ "SetDropSoundFileName",			itemSetDropSoundFileName,				METH_VARARGS },
		{ "SelectItem",						itemSelectItem,							METH_VARARGS },

		{ "GetItemName",					itemGetItemName,						METH_VARARGS },
		{ "GetItemDescription",				itemGetItemDescription,					METH_VARARGS },
		{ "GetItemSummary",					itemGetItemSummary,						METH_VARARGS },
		{ "GetIconImage",					itemGetIconImage,						METH_VARARGS },
		{ "GetIconImageFileName",			itemGetIconImageFileName,				METH_VARARGS },
		{ "GetItemSize",					itemGetItemSize,						METH_VARARGS },
		{ "GetItemType",					itemGetItemType,						METH_VARARGS },
		{ "GetItemSubType",					itemGetItemSubType,						METH_VARARGS },
		{ "GetIBuyItemPrice",				itemGetIBuyItemPrice,					METH_VARARGS },
		{ "GetISellItemPrice",				itemGetISellItemPrice,					METH_VARARGS },
		{ "IsAntiFlag",						itemIsAntiFlag,							METH_VARARGS },
		{ "IsFlag",							itemIsFlag,								METH_VARARGS },
		{ "IsWearableFlag",					itemIsWearableFlag,						METH_VARARGS },
		{ "Is1GoldItem",					itemIs1GoldItem,						METH_VARARGS },
		{ "GetLimit",						itemGetLimit,							METH_VARARGS },
		{ "GetAffect",						itemGetAffect,							METH_VARARGS },
		{ "GetValue",						itemGetValue,							METH_VARARGS },
		{ "GetSocket",						itemGetSocket,							METH_VARARGS },
		{ "GetIconInstance",				itemGetIconInstance,					METH_VARARGS },
		{ "GetUseType",						itemGetUseType,							METH_VARARGS },
		{ "DeleteIconInstance",				itemDeleteIconInstance,					METH_VARARGS },
		{ "IsEquipmentVID",					itemIsEquipmentVID,						METH_VARARGS },
		{ "IsRefineScroll",					itemIsRefineScroll,						METH_VARARGS },
		{ "IsDetachScroll",					itemIsDetachScroll,						METH_VARARGS },
		{ "IsKey",							itemIsKey,								METH_VARARGS },
		{ "IsMetin",						itemIsMetin,							METH_VARARGS },
		{ "CanAddToQuickSlotItem",			itemCanAddToQuickSlotItem,				METH_VARARGS },

		{ "Update",							itemUpdate,								METH_VARARGS },
		{ "Render",							itemRender,								METH_VARARGS },
		{ "CreateItem",						itemCreateItem,							METH_VARARGS },
		{ "DeleteItem",						itemDeleteItem,							METH_VARARGS },
		{ "Pick",							itemPick,								METH_VARARGS },

		{ "LoadItemTable",					itemLoadItemTable,						METH_VARARGS },

		{ "GetApplyPoint",					itemGetApplyPoint,						METH_VARARGS },

#ifdef ENABLE_SEALBIND_SYSTEM
		{ "IsSealScroll",					itemIsSealScroll,						METH_VARARGS },
		{ "GetDefaultSealDate",				itemGetDefaultSealDate,					METH_VARARGS },
		{ "GetUnlimitedSealDate",			itemGetUnlimitedSealDate,				METH_VARARGS },
#endif

		{ NULL,								NULL,									NULL		 },
	};

	PyObject * poModule = Py_InitModule("item", s_methods);

	PyModule_AddIntConstant(poModule, "USESOUND_ACCESSORY",			CPythonItem::USESOUND_ACCESSORY);
	PyModule_AddIntConstant(poModule, "USESOUND_ARMOR",				CPythonItem::USESOUND_ARMOR);
	PyModule_AddIntConstant(poModule, "USESOUND_BOW",				CPythonItem::USESOUND_BOW);
	PyModule_AddIntConstant(poModule, "USESOUND_DEFAULT",			CPythonItem::USESOUND_DEFAULT);
	PyModule_AddIntConstant(poModule, "USESOUND_WEAPON",			CPythonItem::USESOUND_WEAPON);
	PyModule_AddIntConstant(poModule, "USESOUND_POTION",			CPythonItem::USESOUND_POTION);
	PyModule_AddIntConstant(poModule, "USESOUND_PORTAL",			CPythonItem::USESOUND_PORTAL);

	PyModule_AddIntConstant(poModule, "DROPSOUND_ACCESSORY",		CPythonItem::DROPSOUND_ACCESSORY);
	PyModule_AddIntConstant(poModule, "DROPSOUND_ARMOR",			CPythonItem::DROPSOUND_ARMOR);
	PyModule_AddIntConstant(poModule, "DROPSOUND_BOW",				CPythonItem::DROPSOUND_BOW);
	PyModule_AddIntConstant(poModule, "DROPSOUND_DEFAULT",			CPythonItem::DROPSOUND_DEFAULT);
	PyModule_AddIntConstant(poModule, "DROPSOUND_WEAPON",			CPythonItem::DROPSOUND_WEAPON);

	PyModule_AddIntConstant(poModule, "EQUIPMENT_COUNT",			c_Equipment_Count);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_HEAD",				c_Equipment_Head);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_BODY",				c_Equipment_Body);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_WEAPON",			c_Equipment_Weapon);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_WRIST",			c_Equipment_Wrist);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_SHOES",			c_Equipment_Shoes);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_NECK",				c_Equipment_Neck);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_EAR",				c_Equipment_Ear);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_UNIQUE1",			c_Equipment_Unique1);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_UNIQUE2",			c_Equipment_Unique2);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_ARROW",			c_Equipment_Arrow);
	PyModule_AddIntConstant(poModule, "EQUIPMENT_SHIELD",			c_Equipment_Shield);

#ifdef ENABLE_NEW_EQUIPMENT_SYSTEM
	PyModule_AddIntConstant(poModule, "EQUIPMENT_BELT",				c_Equipment_Belt);
#endif
#ifdef ENABLE_PENDANT_SYSTEM
	PyModule_AddIntConstant(poModule, "EQUIPMENT_PENDANT",			c_Equipment_Pendant);
#endif
#ifdef ENABLE_GLOVE_SYSTEM
	PyModule_AddIntConstant(poModule, "EQUIPMENT_GLOVE",			c_Equipment_Glove);
#endif

	PyModule_AddIntConstant(poModule, "ITEM_TYPE_NONE",				CItemData::ITEM_TYPE_NONE);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_WEAPON",			CItemData::ITEM_TYPE_WEAPON);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_ARMOR",			CItemData::ITEM_TYPE_ARMOR);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_USE",				CItemData::ITEM_TYPE_USE);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_AUTOUSE",			CItemData::ITEM_TYPE_AUTOUSE);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_MATERIAL",			CItemData::ITEM_TYPE_MATERIAL);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_SPECIAL",			CItemData::ITEM_TYPE_SPECIAL);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_TOOL",				CItemData::ITEM_TYPE_TOOL);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_LOTTERY",			CItemData::ITEM_TYPE_LOTTERY);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_ELK",				CItemData::ITEM_TYPE_ELK);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_METIN",			CItemData::ITEM_TYPE_METIN);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_CONTAINER",		CItemData::ITEM_TYPE_CONTAINER);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_FISH",				CItemData::ITEM_TYPE_FISH);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_ROD",				CItemData::ITEM_TYPE_ROD);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_RESOURCE",			CItemData::ITEM_TYPE_RESOURCE);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_CAMPFIRE",			CItemData::ITEM_TYPE_CAMPFIRE);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_UNIQUE",			CItemData::ITEM_TYPE_UNIQUE);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_SKILLBOOK",		CItemData::ITEM_TYPE_SKILLBOOK);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_QUEST",			CItemData::ITEM_TYPE_QUEST);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_POLYMORPH",		CItemData::ITEM_TYPE_POLYMORPH);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_TREASURE_BOX",		CItemData::ITEM_TYPE_TREASURE_BOX);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_TREASURE_KEY",		CItemData::ITEM_TYPE_TREASURE_KEY);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_SKILLFORGET",		CItemData::ITEM_TYPE_SKILLFORGET);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_GIFTBOX",			CItemData::ITEM_TYPE_GIFTBOX);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_PICK",				CItemData::ITEM_TYPE_PICK);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_HAIR",				CItemData::ITEM_TYPE_HAIR);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_TOTEM",			CItemData::ITEM_TYPE_TOTEM);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_BLEND",			CItemData::ITEM_TYPE_BLEND);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_COSTUME",			CItemData::ITEM_TYPE_COSTUME);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_DS",				CItemData::ITEM_TYPE_DS);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_SPECIAL_DS",		CItemData::ITEM_TYPE_SPECIAL_DS);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_EXTRACT",			CItemData::ITEM_TYPE_EXTRACT);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_SECONDARY_COIN",	CItemData::ITEM_TYPE_SECONDARY_COIN);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_RING",				CItemData::ITEM_TYPE_RING);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_BELT",				CItemData::ITEM_TYPE_BELT);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_PET",				CItemData::ITEM_TYPE_PET);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_MEDIUM",			CItemData::ITEM_TYPE_MEDIUM);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_GACHA",			CItemData::ITEM_TYPE_GACHA);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_SOUL",				CItemData::ITEM_TYPE_SOUL);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_PASSIVE",			CItemData::ITEM_TYPE_PASSIVE);

#ifdef ENABLE_COSTUME_SYSTEM
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_COSTUME",			CItemData::ITEM_TYPE_COSTUME);

	// Item Sub Type
	PyModule_AddIntConstant(poModule, "COSTUME_TYPE_BODY",			CItemData::COSTUME_BODY);
	PyModule_AddIntConstant(poModule, "COSTUME_TYPE_HAIR",			CItemData::COSTUME_HAIR);
#ifdef ENABLE_MOUNT_COSTUME_SYSTEM
	PyModule_AddIntConstant(poModule, "COSTUME_TYPE_MOUNT",			CItemData::COSTUME_MOUNT);
#endif
#ifdef ENABLE_ACCE_COSTUME_SYSTEM
	PyModule_AddIntConstant(poModule, "COSTUME_TYPE_ACCE",			CItemData::COSTUME_ACCE);
#endif
#ifdef ENABLE_WEAPON_COSTUME_SYSTEM
	PyModule_AddIntConstant(poModule, "COSTUME_TYPE_WEAPON",		CItemData::COSTUME_WEAPON);
#endif

	PyModule_AddIntConstant(poModule, "COSTUME_SLOT_START",			c_Costume_Slot_Start);
	PyModule_AddIntConstant(poModule, "COSTUME_SLOT_COUNT",			c_Costume_Slot_Count);
	PyModule_AddIntConstant(poModule, "COSTUME_SLOT_BODY",			c_Costume_Slot_Body);
	PyModule_AddIntConstant(poModule, "COSTUME_SLOT_HAIR",			c_Costume_Slot_Hair);
#ifdef ENABLE_MOUNT_COSTUME_SYSTEM
	PyModule_AddIntConstant(poModule, "COSTUME_SLOT_MOUNT",			c_Costume_Slot_Mount);
#endif
#ifdef ENABLE_ACCE_COSTUME_SYSTEM
	PyModule_AddIntConstant(poModule, "COSTUME_SLOT_ACCE",			c_Costume_Slot_Acce);
#endif
#ifdef ENABLE_WEAPON_COSTUME_SYSTEM
	PyModule_AddIntConstant(poModule, "COSTUME_SLOT_WEAPON",		c_Costume_Slot_Weapon);
#endif
	PyModule_AddIntConstant(poModule, "COSTUME_SLOT_END",			c_Costume_Slot_End);
#endif

#ifdef ENABLE_NEW_EQUIPMENT_SYSTEM
	PyModule_AddIntConstant(poModule, "BELT_INVENTORY_SLOT_START",			c_Belt_Inventory_Slot_Start);
	PyModule_AddIntConstant(poModule, "BELT_INVENTORY_SLOT_COUNT",			c_Belt_Inventory_Slot_Count);
	PyModule_AddIntConstant(poModule, "BELT_INVENTORY_SLOT_END",			c_Belt_Inventory_Slot_End);

#endif

	PyModule_AddIntConstant(poModule, "WEAPON_SWORD",				CItemData::WEAPON_SWORD);
	PyModule_AddIntConstant(poModule, "WEAPON_DAGGER",				CItemData::WEAPON_DAGGER);
	PyModule_AddIntConstant(poModule, "WEAPON_BOW",					CItemData::WEAPON_BOW);
	PyModule_AddIntConstant(poModule, "WEAPON_TWO_HANDED",			CItemData::WEAPON_TWO_HANDED);
	PyModule_AddIntConstant(poModule, "WEAPON_BELL",				CItemData::WEAPON_BELL);
	PyModule_AddIntConstant(poModule, "WEAPON_FAN",					CItemData::WEAPON_FAN);
	PyModule_AddIntConstant(poModule, "WEAPON_ARROW",				CItemData::WEAPON_ARROW);
	PyModule_AddIntConstant(poModule, "WEAPON_MOUNT_SPEAR",			CItemData::WEAPON_MOUNT_SPEAR);
#ifdef ENABLE_WOLFMAN_CHARACTER
	PyModule_AddIntConstant(poModule, "WEAPON_CLAW",				CItemData::WEAPON_CLAW);
#endif
#ifdef ENABLE_QUIVER_SYSTEM
	PyModule_AddIntConstant(poModule, "WEAPON_QUIVER",				CItemData::WEAPON_QUIVER);
#endif
#ifdef __UNIMPLEMENTED__
	PyModule_AddIntConstant(poModule, "WEAPON_BOUQUET",				CItemData::WEAPON_BOUQUET);
#endif
	PyModule_AddIntConstant(poModule, "WEAPON_NUM_TYPES",			CItemData::WEAPON_NUM_TYPES);

	PyModule_AddIntConstant(poModule, "USE_POTION",					CItemData::USE_POTION);
	PyModule_AddIntConstant(poModule, "USE_TALISMAN",				CItemData::USE_TALISMAN);
	PyModule_AddIntConstant(poModule, "USE_TUNING",					CItemData::USE_TUNING);
	PyModule_AddIntConstant(poModule, "USE_MOVE",					CItemData::USE_MOVE);
	PyModule_AddIntConstant(poModule, "USE_TREASURE_BOX",			CItemData::USE_TREASURE_BOX);
	PyModule_AddIntConstant(poModule, "USE_MONEYBAG",				CItemData::USE_MONEYBAG);
	PyModule_AddIntConstant(poModule, "USE_BAIT",					CItemData::USE_BAIT);
	PyModule_AddIntConstant(poModule, "USE_ABILITY_UP",				CItemData::USE_ABILITY_UP);
	PyModule_AddIntConstant(poModule, "USE_AFFECT",					CItemData::USE_AFFECT);
	PyModule_AddIntConstant(poModule, "USE_CREATE_STONE",			CItemData::USE_CREATE_STONE);
	PyModule_AddIntConstant(poModule, "USE_SPECIAL",				CItemData::USE_SPECIAL);
	PyModule_AddIntConstant(poModule, "USE_POTION_NODELAY",			CItemData::USE_POTION_NODELAY);
	PyModule_AddIntConstant(poModule, "USE_CLEAR",					CItemData::USE_CLEAR);
	PyModule_AddIntConstant(poModule, "USE_INVISIBILITY",			CItemData::USE_INVISIBILITY);
	PyModule_AddIntConstant(poModule, "USE_DETACHMENT",				CItemData::USE_DETACHMENT);
	PyModule_AddIntConstant(poModule, "USE_TIME_CHARGE_PER",		CItemData::USE_TIME_CHARGE_PER);
	PyModule_AddIntConstant(poModule, "USE_TIME_CHARGE_FIX",		CItemData::USE_TIME_CHARGE_FIX);

	PyModule_AddIntConstant(poModule, "MATERIAL_DS_REFINE_NORMAL",	CItemData::MATERIAL_DS_REFINE_NORMAL);
	PyModule_AddIntConstant(poModule, "MATERIAL_DS_REFINE_BLESSED",	CItemData::MATERIAL_DS_REFINE_BLESSED);
	PyModule_AddIntConstant(poModule, "MATERIAL_DS_REFINE_HOLLY",	CItemData::MATERIAL_DS_REFINE_HOLLY);

	PyModule_AddIntConstant(poModule, "METIN_NORMAL",				CItemData::METIN_NORMAL);
	PyModule_AddIntConstant(poModule, "METIN_GOLD",					CItemData::METIN_GOLD);

	PyModule_AddIntConstant(poModule, "LIMIT_NONE",					CItemData::LIMIT_NONE);
	PyModule_AddIntConstant(poModule, "LIMIT_LEVEL",				CItemData::LIMIT_LEVEL);
	PyModule_AddIntConstant(poModule, "LIMIT_STR",					CItemData::LIMIT_STR);
	PyModule_AddIntConstant(poModule, "LIMIT_DEX",					CItemData::LIMIT_DEX);
	PyModule_AddIntConstant(poModule, "LIMIT_INT",					CItemData::LIMIT_INT);
	PyModule_AddIntConstant(poModule, "LIMIT_CON",					CItemData::LIMIT_CON);
	PyModule_AddIntConstant(poModule, "LIMIT_PCBANG",				CItemData::LIMIT_PCBANG);
	PyModule_AddIntConstant(poModule, "LIMIT_REAL_TIME",			CItemData::LIMIT_REAL_TIME);
	PyModule_AddIntConstant(poModule, "LIMIT_REAL_TIME_START_FIRST_USE",	CItemData::LIMIT_REAL_TIME_START_FIRST_USE);
	PyModule_AddIntConstant(poModule, "LIMIT_TIMER_BASED_ON_WEAR",	CItemData::LIMIT_TIMER_BASED_ON_WEAR);
	PyModule_AddIntConstant(poModule, "LIMIT_NEWWORLD_LEVEL",		CItemData::LIMIT_NEWWORLD_LEVEL);
	PyModule_AddIntConstant(poModule, "LIMIT_TYPE_MAX_NUM",			CItemData::LIMIT_MAX_NUM);
	PyModule_AddIntConstant(poModule, "LIMIT_MAX_NUM",				CItemData::ITEM_LIMIT_MAX_NUM);

	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_FEMALE",		CItemData::ITEM_ANTIFLAG_FEMALE);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_MALE",			CItemData::ITEM_ANTIFLAG_MALE);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_WARRIOR",		CItemData::ITEM_ANTIFLAG_WARRIOR);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_ASSASSIN",		CItemData::ITEM_ANTIFLAG_ASSASSIN);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_SURA",			CItemData::ITEM_ANTIFLAG_SURA);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_SHAMAN",		CItemData::ITEM_ANTIFLAG_SHAMAN);
#ifdef ENABLE_WOLFMAN_CHARACTER
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_WOLFMAN",		CItemData::ITEM_ANTIFLAG_WOLFMAN);
#endif
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_GET",			CItemData::ITEM_ANTIFLAG_GET);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_DROP",			CItemData::ITEM_ANTIFLAG_DROP);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_SELL",			CItemData::ITEM_ANTIFLAG_SELL);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_EMPIRE_A",		CItemData::ITEM_ANTIFLAG_EMPIRE_A);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_EMPIRE_B",		CItemData::ITEM_ANTIFLAG_EMPIRE_B);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_EMPIRE_R",		CItemData::ITEM_ANTIFLAG_EMPIRE_R);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_SAVE",			CItemData::ITEM_ANTIFLAG_SAVE);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_GIVE",			CItemData::ITEM_ANTIFLAG_GIVE);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_PKDROP",		CItemData::ITEM_ANTIFLAG_PKDROP);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_STACK",		CItemData::ITEM_ANTIFLAG_STACK);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_MYSHOP",		CItemData::ITEM_ANTIFLAG_MYSHOP);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_SAFEBOX",		CItemData::ITEM_ANTIFLAG_SAFEBOX);

	PyModule_AddIntConstant(poModule, "ITEM_FLAG_REFINEABLE", CItemData::ITEM_FLAG_REFINEABLE);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_SAVE", CItemData::ITEM_FLAG_SAVE);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_STACKABLE", CItemData::ITEM_FLAG_STACKABLE);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_COUNT_PER_1GOLD", CItemData::ITEM_FLAG_COUNT_PER_1GOLD);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_SLOW_QUERY", CItemData::ITEM_FLAG_SLOW_QUERY);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_RARE", CItemData::ITEM_FLAG_RARE);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_UNIQUE", CItemData::ITEM_FLAG_UNIQUE);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_MAKECOUNT", CItemData::ITEM_FLAG_MAKECOUNT);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_IRREMOVABLE", CItemData::ITEM_FLAG_IRREMOVABLE);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_CONFIRM_WHEN_USE", CItemData::ITEM_FLAG_CONFIRM_WHEN_USE);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_QUEST_USE", CItemData::ITEM_FLAG_QUEST_USE);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_QUEST_USE_MULTIPLE", CItemData::ITEM_FLAG_QUEST_USE_MULTIPLE);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_QUEST_GIVE", CItemData::ITEM_FLAG_QUEST_GIVE);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_LOG", CItemData::ITEM_FLAG_LOG);
	PyModule_AddIntConstant(poModule, "ITEM_FLAG_APPLICABLE", CItemData::ITEM_FLAG_APPLICABLE);

	PyModule_AddIntConstant(poModule, "ANTIFLAG_FEMALE",			CItemData::ITEM_ANTIFLAG_FEMALE);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_MALE",				CItemData::ITEM_ANTIFLAG_MALE);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_WARRIOR",			CItemData::ITEM_ANTIFLAG_WARRIOR);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_ASSASSIN",			CItemData::ITEM_ANTIFLAG_ASSASSIN);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_SURA",				CItemData::ITEM_ANTIFLAG_SURA);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_SHAMAN",			CItemData::ITEM_ANTIFLAG_SHAMAN);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_GET",				CItemData::ITEM_ANTIFLAG_GET);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_DROP",				CItemData::ITEM_ANTIFLAG_DROP);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_SELL",				CItemData::ITEM_ANTIFLAG_SELL);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_EMPIRE_A",			CItemData::ITEM_ANTIFLAG_EMPIRE_A);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_EMPIRE_B",			CItemData::ITEM_ANTIFLAG_EMPIRE_B);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_EMPIRE_R",			CItemData::ITEM_ANTIFLAG_EMPIRE_R);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_SAVE",				CItemData::ITEM_ANTIFLAG_SAVE);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_GIVE",				CItemData::ITEM_ANTIFLAG_GIVE);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_PKDROP",			CItemData::ITEM_ANTIFLAG_PKDROP);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_STACK",				CItemData::ITEM_ANTIFLAG_STACK);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_MYSHOP",			CItemData::ITEM_ANTIFLAG_MYSHOP);
	PyModule_AddIntConstant(poModule, "ANTIFLAG_SAFEBOX",			CItemData::ITEM_ANTIFLAG_SAFEBOX);
#ifdef ENABLE_WOLFMAN_CHARACTER
	PyModule_AddIntConstant(poModule, "ANTIFLAG_WOLFMAN",			CItemData::ITEM_ANTIFLAG_WOLFMAN);
#endif
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_CHANGELOOK",	CItemData::ITEM_ANTIFLAG_CHANGELOOK);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_REINFORCE",	CItemData::ITEM_ANTIFLAG_REINFORCE);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_ENCHANT",		CItemData::ITEM_ANTIFLAG_ENCHANT);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_ENERGY",		CItemData::ITEM_ANTIFLAG_ENERGY);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_PETFEED",		CItemData::ITEM_ANTIFLAG_PETFEED);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_APPLY",		CItemData::ITEM_ANTIFLAG_APPLY);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_ACCE",			CItemData::ITEM_ANTIFLAG_ACCE);
	PyModule_AddIntConstant(poModule, "ITEM_ANTIFLAG_MAIL",			CItemData::ITEM_ANTIFLAG_MAIL);

	PyModule_AddIntConstant(poModule, "WEARABLE_BODY",				CItemData::WEARABLE_BODY);
	PyModule_AddIntConstant(poModule, "WEARABLE_HEAD",				CItemData::WEARABLE_HEAD);
	PyModule_AddIntConstant(poModule, "WEARABLE_FOOTS",				CItemData::WEARABLE_FOOTS);
	PyModule_AddIntConstant(poModule, "WEARABLE_WRIST",				CItemData::WEARABLE_WRIST);
	PyModule_AddIntConstant(poModule, "WEARABLE_WEAPON",			CItemData::WEARABLE_WEAPON);
	PyModule_AddIntConstant(poModule, "WEARABLE_NECK",				CItemData::WEARABLE_NECK);
	PyModule_AddIntConstant(poModule, "WEARABLE_EAR",				CItemData::WEARABLE_EAR);
	PyModule_AddIntConstant(poModule, "WEARABLE_UNIQUE",			CItemData::WEARABLE_UNIQUE);
	PyModule_AddIntConstant(poModule, "WEARABLE_SHIELD",			CItemData::WEARABLE_SHIELD);
	PyModule_AddIntConstant(poModule, "WEARABLE_ARROW",				CItemData::WEARABLE_ARROW);
	PyModule_AddIntConstant(poModule, "WEARABLE_HAIR",				CItemData::WEARABLE_HAIR);
	PyModule_AddIntConstant(poModule, "WEARABLE_ABILITY",			CItemData::WEARABLE_ABILITY);
#ifdef ENABLE_PENDANT_SYSTEM
	PyModule_AddIntConstant(poModule, "WEARABLE_PENDANT",			CItemData::WEARABLE_PENDANT);
#endif
#ifdef ENABLE_GLOVE_SYSTEM
	PyModule_AddIntConstant(poModule, "WEARABLE_GLOVE",				CItemData::WEARABLE_GLOVE);
#endif

	PyModule_AddIntConstant(poModule, "ARMOR_BODY",					CItemData::ARMOR_BODY);
	PyModule_AddIntConstant(poModule, "ARMOR_HEAD",					CItemData::ARMOR_HEAD);
	PyModule_AddIntConstant(poModule, "ARMOR_SHIELD",				CItemData::ARMOR_SHIELD);
	PyModule_AddIntConstant(poModule, "ARMOR_WRIST",				CItemData::ARMOR_WRIST);
	PyModule_AddIntConstant(poModule, "ARMOR_FOOTS",				CItemData::ARMOR_FOOTS);
	PyModule_AddIntConstant(poModule, "ARMOR_NECK",					CItemData::ARMOR_NECK);
	PyModule_AddIntConstant(poModule, "ARMOR_EAR",					CItemData::ARMOR_EAR);
#ifdef ENABLE_PENDANT_SYSTEM
	PyModule_AddIntConstant(poModule, "ARMOR_PENDANT",				CItemData::ARMOR_PENDANT);
#endif
#ifdef ENABLE_GLOVE_SYSTEM
	PyModule_AddIntConstant(poModule, "ARMOR_GLOVE",				CItemData::ARMOR_GLOVE);
#endif

	PyModule_AddIntConstant(poModule, "ITEM_APPLY_MAX_NUM",			CItemData::ITEM_APPLY_MAX_NUM);
	PyModule_AddIntConstant(poModule, "ITEM_SOCKET_MAX_NUM",		CItemData::ITEM_SOCKET_MAX_NUM);

	PyModule_AddIntConstant(poModule, "APPLY_NONE",					CItemData::APPLY_NONE);
	PyModule_AddIntConstant(poModule, "APPLY_STR",					CItemData::APPLY_STR);
	PyModule_AddIntConstant(poModule, "APPLY_DEX",					CItemData::APPLY_DEX);
	PyModule_AddIntConstant(poModule, "APPLY_CON",					CItemData::APPLY_CON);
	PyModule_AddIntConstant(poModule, "APPLY_INT",					CItemData::APPLY_INT);
	PyModule_AddIntConstant(poModule, "APPLY_MAX_HP",				CItemData::APPLY_MAX_HP);
	PyModule_AddIntConstant(poModule, "APPLY_MAX_SP",				CItemData::APPLY_MAX_SP);
	PyModule_AddIntConstant(poModule, "APPLY_HP_REGEN",				CItemData::APPLY_HP_REGEN);
	PyModule_AddIntConstant(poModule, "APPLY_SP_REGEN",				CItemData::APPLY_SP_REGEN);
	PyModule_AddIntConstant(poModule, "APPLY_DEF_GRADE_BONUS",		CItemData::APPLY_DEF_GRADE_BONUS);
	PyModule_AddIntConstant(poModule, "APPLY_ATT_GRADE_BONUS",		CItemData::APPLY_ATT_GRADE_BONUS);
	PyModule_AddIntConstant(poModule, "APPLY_ATT_SPEED",			CItemData::APPLY_ATT_SPEED);
	PyModule_AddIntConstant(poModule, "APPLY_MOV_SPEED",			CItemData::APPLY_MOV_SPEED);
	PyModule_AddIntConstant(poModule, "APPLY_CAST_SPEED",			CItemData::APPLY_CAST_SPEED);
	PyModule_AddIntConstant(poModule, "APPLY_MAGIC_ATT_GRADE",		CItemData::APPLY_MAGIC_ATT_GRADE);
	PyModule_AddIntConstant(poModule, "APPLY_MAGIC_DEF_GRADE",		CItemData::APPLY_MAGIC_DEF_GRADE);
	PyModule_AddIntConstant(poModule, "APPLY_SKILL",				CItemData::APPLY_SKILL);
    PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_ANIMAL",		CItemData::APPLY_ATTBONUS_ANIMAL);
    PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_UNDEAD",		CItemData::APPLY_ATTBONUS_UNDEAD);
    PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_DEVIL", 		CItemData::APPLY_ATTBONUS_DEVIL);
    PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_HUMAN",		CItemData::APPLY_ATTBONUS_HUMAN);
    PyModule_AddIntConstant(poModule, "APPLY_BOW_DISTANCE", 		CItemData::APPLY_BOW_DISTANCE);
    PyModule_AddIntConstant(poModule, "APPLY_RESIST_BOW", 			CItemData::APPLY_RESIST_BOW);
    PyModule_AddIntConstant(poModule, "APPLY_RESIST_FIRE", 			CItemData::APPLY_RESIST_FIRE);
    PyModule_AddIntConstant(poModule, "APPLY_RESIST_ELEC", 			CItemData::APPLY_RESIST_ELEC);
    PyModule_AddIntConstant(poModule, "APPLY_RESIST_MAGIC", 		CItemData::APPLY_RESIST_MAGIC);
    PyModule_AddIntConstant(poModule, "APPLY_POISON_PCT",			CItemData::APPLY_POISON_PCT);
    PyModule_AddIntConstant(poModule, "APPLY_SLOW_PCT", 			CItemData::APPLY_SLOW_PCT);
    PyModule_AddIntConstant(poModule, "APPLY_STUN_PCT", 			CItemData::APPLY_STUN_PCT);
	PyModule_AddIntConstant(poModule, "APPLY_CRITICAL_PCT",			CItemData::APPLY_CRITICAL_PCT);
	PyModule_AddIntConstant(poModule, "APPLY_PENETRATE_PCT",		CItemData::APPLY_PENETRATE_PCT);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_ORC",			CItemData::APPLY_ATTBONUS_ORC);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_MILGYO",		CItemData::APPLY_ATTBONUS_MILGYO);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_UNDEAD",		CItemData::APPLY_ATTBONUS_UNDEAD);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_DEVIL",		CItemData::APPLY_ATTBONUS_DEVIL);
	PyModule_AddIntConstant(poModule, "APPLY_STEAL_HP",				CItemData::APPLY_STEAL_HP);
	PyModule_AddIntConstant(poModule, "APPLY_STEAL_SP",				CItemData::APPLY_STEAL_SP);
	PyModule_AddIntConstant(poModule, "APPLY_MANA_BURN_PCT",		CItemData::APPLY_MANA_BURN_PCT);
	PyModule_AddIntConstant(poModule, "APPLY_DAMAGE_SP_RECOVER",	CItemData::APPLY_DAMAGE_SP_RECOVER);
	PyModule_AddIntConstant(poModule, "APPLY_BLOCK",				CItemData::APPLY_BLOCK);
	PyModule_AddIntConstant(poModule, "APPLY_DODGE",				CItemData::APPLY_DODGE);
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_SWORD",			CItemData::APPLY_RESIST_SWORD);
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_TWOHAND",		CItemData::APPLY_RESIST_TWOHAND);
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_DAGGER",		CItemData::APPLY_RESIST_DAGGER);
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_BELL",			CItemData::APPLY_RESIST_BELL);
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_FAN",			CItemData::APPLY_RESIST_FAN);
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_WIND",			CItemData::APPLY_RESIST_WIND);
	PyModule_AddIntConstant(poModule, "APPLY_REFLECT_MELEE",		CItemData::APPLY_REFLECT_MELEE);
	PyModule_AddIntConstant(poModule, "APPLY_REFLECT_CURSE",		CItemData::APPLY_REFLECT_CURSE);
	PyModule_AddIntConstant(poModule, "APPLY_POISON_REDUCE",		CItemData::APPLY_POISON_REDUCE);
	PyModule_AddIntConstant(poModule, "APPLY_KILL_SP_RECOVER",		CItemData::APPLY_KILL_SP_RECOVER);
	PyModule_AddIntConstant(poModule, "APPLY_EXP_DOUBLE_BONUS",		CItemData::APPLY_EXP_DOUBLE_BONUS);
	PyModule_AddIntConstant(poModule, "APPLY_GOLD_DOUBLE_BONUS",	CItemData::APPLY_GOLD_DOUBLE_BONUS);
	PyModule_AddIntConstant(poModule, "APPLY_ITEM_DROP_BONUS",		CItemData::APPLY_ITEM_DROP_BONUS);
	PyModule_AddIntConstant(poModule, "APPLY_POTION_BONUS",			CItemData::APPLY_POTION_BONUS);
	PyModule_AddIntConstant(poModule, "APPLY_KILL_HP_RECOVER",		CItemData::APPLY_KILL_HP_RECOVER);
	PyModule_AddIntConstant(poModule, "APPLY_IMMUNE_STUN",			CItemData::APPLY_IMMUNE_STUN);
	PyModule_AddIntConstant(poModule, "APPLY_IMMUNE_SLOW",			CItemData::APPLY_IMMUNE_SLOW);
	PyModule_AddIntConstant(poModule, "APPLY_IMMUNE_FALL",			CItemData::APPLY_IMMUNE_FALL);
	PyModule_AddIntConstant(poModule, "APPLY_MAX_STAMINA",			CItemData::APPLY_MAX_STAMINA);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_WARRIOR",		CItemData::APPLY_ATT_BONUS_TO_WARRIOR);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_ASSASSIN",	CItemData::APPLY_ATT_BONUS_TO_ASSASSIN);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_SURA",		CItemData::APPLY_ATT_BONUS_TO_SURA);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_SHAMAN",		CItemData::APPLY_ATT_BONUS_TO_SHAMAN);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_MONSTER",		CItemData::APPLY_ATT_BONUS_TO_MONSTER);
	PyModule_AddIntConstant(poModule, "APPLY_MALL_ATTBONUS",		CItemData::APPLY_MALL_ATTBONUS);
	PyModule_AddIntConstant(poModule, "APPLY_MALL_DEFBONUS",		CItemData::APPLY_MALL_DEFBONUS);
	PyModule_AddIntConstant(poModule, "APPLY_MALL_EXPBONUS",		CItemData::APPLY_MALL_EXPBONUS);
	PyModule_AddIntConstant(poModule, "APPLY_MALL_ITEMBONUS",		CItemData::APPLY_MALL_ITEMBONUS);
	PyModule_AddIntConstant(poModule, "APPLY_MALL_GOLDBONUS",		CItemData::APPLY_MALL_GOLDBONUS);
	PyModule_AddIntConstant(poModule, "APPLY_MAX_HP_PCT",			CItemData::APPLY_MAX_HP_PCT);
	PyModule_AddIntConstant(poModule, "APPLY_MAX_SP_PCT",			CItemData::APPLY_MAX_SP_PCT);
	PyModule_AddIntConstant(poModule, "APPLY_SKILL_DAMAGE_BONUS",		CItemData::APPLY_SKILL_DAMAGE_BONUS);
	PyModule_AddIntConstant(poModule, "APPLY_NORMAL_HIT_DAMAGE_BONUS",	CItemData::APPLY_NORMAL_HIT_DAMAGE_BONUS);
	PyModule_AddIntConstant(poModule, "APPLY_SKILL_DEFEND_BONUS",		CItemData::APPLY_SKILL_DEFEND_BONUS);
	PyModule_AddIntConstant(poModule, "APPLY_NORMAL_HIT_DEFEND_BONUS",	CItemData::APPLY_NORMAL_HIT_DEFEND_BONUS);

	PyModule_AddIntConstant(poModule, "APPLY_PC_BANG_EXP_BONUS",	CItemData::APPLY_PC_BANG_EXP_BONUS);
	PyModule_AddIntConstant(poModule, "APPLY_PC_BANG_DROP_BONUS",	CItemData::APPLY_PC_BANG_DROP_BONUS);

	PyModule_AddIntConstant(poModule, "APPLY_RESIST_WARRIOR",	CItemData::APPLY_RESIST_WARRIOR );
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_ASSASSIN",	CItemData::APPLY_RESIST_ASSASSIN );
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_SURA",		CItemData::APPLY_RESIST_SURA );
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_SHAMAN",	CItemData::APPLY_RESIST_SHAMAN );
	PyModule_AddIntConstant(poModule, "APPLY_ENERGY",	CItemData::APPLY_ENERGY );
	PyModule_AddIntConstant(poModule, "APPLY_COSTUME_ATTR_BONUS",	CItemData::APPLY_COSTUME_ATTR_BONUS );

	PyModule_AddIntConstant(poModule, "APPLY_MAGIC_ATTBONUS_PER",	CItemData::APPLY_MAGIC_ATTBONUS_PER );
	PyModule_AddIntConstant(poModule, "APPLY_MELEE_MAGIC_ATTBONUS_PER",	CItemData::APPLY_MELEE_MAGIC_ATTBONUS_PER );
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_ICE",	CItemData::APPLY_RESIST_ICE );
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_EARTH",	CItemData::APPLY_RESIST_EARTH );
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_DARK",	CItemData::APPLY_RESIST_DARK );
	PyModule_AddIntConstant(poModule, "APPLY_ANTI_CRITICAL_PCT",	CItemData::APPLY_ANTI_CRITICAL_PCT );
	PyModule_AddIntConstant(poModule, "APPLY_ANTI_PENETRATE_PCT",	CItemData::APPLY_ANTI_PENETRATE_PCT );
#ifdef ENABLE_WOLFMAN_CHARACTER
	PyModule_AddIntConstant(poModule, "APPLY_BLEEDING_PCT",	CItemData::APPLY_BLEEDING_PCT );
	PyModule_AddIntConstant(poModule, "APPLY_BLEEDING_REDUCE",	CItemData::APPLY_BLEEDING_REDUCE );
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_WOLFMAN",	CItemData::APPLY_ATT_BONUS_TO_WOLFMAN );
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_WOLFMAN",	CItemData::APPLY_RESIST_WOLFMAN );
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_CLAW",	CItemData::APPLY_RESIST_CLAW );
#endif

#ifdef ENABLE_ACCE_COSTUME_SYSTEM
	PyModule_AddIntConstant(poModule, "APPLY_ACCEDRAIN_RATE",			CItemData::APPLY_ACCEDRAIN_RATE);
#endif
#ifdef ENABLE_MAGIC_REDUCTION_SYSTEM
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_MAGIC_REDUCTION",	CItemData::APPLY_RESIST_MAGIC_REDUCTION);
#endif

	PyModule_AddIntConstant(poModule, "APPLY_ENCHANT_ELECT", CItemData::APPLY_ENCHANT_ELECT);
	PyModule_AddIntConstant(poModule, "APPLY_ENCHANT_FIRE", CItemData::APPLY_ENCHANT_FIRE);
	PyModule_AddIntConstant(poModule, "APPLY_ENCHANT_ICE", CItemData::APPLY_ENCHANT_ICE);
	PyModule_AddIntConstant(poModule, "APPLY_ENCHANT_WIND", CItemData::APPLY_ENCHANT_WIND);
	PyModule_AddIntConstant(poModule, "APPLY_ENCHANT_EARTH", CItemData::APPLY_ENCHANT_EARTH);
	PyModule_AddIntConstant(poModule, "APPLY_ENCHANT_DARK", CItemData::APPLY_ENCHANT_DARK);

	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_CZ", CItemData::APPLY_ATTBONUS_CZ);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_INSECT", CItemData::APPLY_ATTBONUS_INSECT);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_DESERT", CItemData::APPLY_ATTBONUS_DESERT);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_SWORD", CItemData::APPLY_ATTBONUS_SWORD);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_TWOHAND", CItemData::APPLY_ATTBONUS_TWOHAND);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_DAGGER", CItemData::APPLY_ATTBONUS_DAGGER);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_BELL", CItemData::APPLY_ATTBONUS_BELL);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_FAN", CItemData::APPLY_ATTBONUS_FAN);
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_BOW", CItemData::APPLY_ATTBONUS_BOW);
#ifdef ENABLE_WOLFMAN_CHARACTER
	PyModule_AddIntConstant(poModule, "APPLY_ATTBONUS_CLAW", CItemData::APPLY_ATTBONUS_CLAW);
#endif
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_HUMAN", CItemData::APPLY_RESIST_HUMAN);
	PyModule_AddIntConstant(poModule, "APPLY_RESIST_MOUNT_FALL", CItemData::APPLY_RESIST_MOUNT_FALL);
	PyModule_AddIntConstant(poModule, "APPLY_MOUNT", CItemData::APPLY_MOUNT);

#ifdef ENABLE_SEALBIND_SYSTEM
	PyModule_AddIntConstant(poModule, "E_SEAL_DATE_DEFAULT_TIMESTAMP",		CItemData::SEAL_DATE_DEFAULT_TIMESTAMP);
	PyModule_AddIntConstant(poModule, "E_SEAL_DATE_UNLIMITED_TIMESTAMP",	CItemData::SEAL_DATE_UNLIMITED_TIMESTAMP);
#endif

#ifdef ENABLE_PET_SYSTEM_EX
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_PET", CItemData::ITEM_TYPE_PET);
	PyModule_AddIntConstant(poModule, "PET_EGG", CItemData::PET_EGG);
	PyModule_AddIntConstant(poModule, "PET_UPBRINGING", CItemData::PET_UPBRINGING);
	PyModule_AddIntConstant(poModule, "PET_BAG", CItemData::PET_BAG);
	PyModule_AddIntConstant(poModule, "PET_FEEDSTUFF", CItemData::PET_FEEDSTUFF);
	PyModule_AddIntConstant(poModule, "PET_SKILL", CItemData::PET_SKILL);
	PyModule_AddIntConstant(poModule, "PET_SKILL_DEL_BOOK", CItemData::PET_SKILL_DEL_BOOK);
	PyModule_AddIntConstant(poModule, "PET_NAME_CHANGE", CItemData::PET_NAME_CHANGE);
	PyModule_AddIntConstant(poModule, "PET_EXPFOOD", CItemData::PET_EXPFOOD);
	PyModule_AddIntConstant(poModule, "PET_SKILL_ALL_DEL_BOOK", CItemData::PET_SKILL_ALL_DEL_BOOK);
	PyModule_AddIntConstant(poModule, "PET_EXPFOOD_PER", CItemData::PET_EXPFOOD_PER);
	PyModule_AddIntConstant(poModule, "PET_ATTR_DETERMINE", CItemData::PET_ATTR_DETERMINE);
	PyModule_AddIntConstant(poModule, "PET_ATTR_CHANGE", CItemData::PET_ATTR_CHANGE);
	PyModule_AddIntConstant(poModule, "PET_PAY", CItemData::PET_PAY);
	PyModule_AddIntConstant(poModule, "PET_PRIMIUM_FEEDSTUFF", CItemData::PET_PRIMIUM_FEEDSTUFF);
#endif
}
//martysama0134's a288e6779da68f768431f9975e780da3
