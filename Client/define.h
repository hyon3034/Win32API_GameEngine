#pragma once

#define SINGLE(type) public:\
					   static type* GetInst()\
				       {\
					       static type mgr;\
						   return &mgr;\
				       }\
					private:\
						type();\
						~type();

#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

enum class GROUP_TYPE
{
    DEFAULT,
    PLAYER,
    MISSILE,
    MONSTER,

    END = 32,
};

enum class SCENE_TYPE
{
    TOOL,
    START,
    STAGE_01,
    STAGE_02,

    END,
};