#include "ServerWorld.h"
#include <LogicValue.h>
#include <GameEngineTime.h>
#include "ServerMonster.h"
#include "WorldMsgFunc.h"
#include <GameEngineRandom.h>

// Static Var
// Static Func

// constructer destructer
ServerWorld::ServerWorld()  : CurMonsterCreateTime(LogicValue::MonsterRegenTime), CurMonsterCount(0)
{

}

ServerWorld::~ServerWorld() 
{

}
// member Func

void ServerWorld::WorldUpdate() 
{
	float Time = GameEngineTime::GetInst().FTime();

	CurMonsterCreateTime -= Time;

	if (0 >= CurMonsterCreateTime)
	{
		if (LogicValue::MaxMonsterCount > CurMonsterCount)
		{
			srand(static_cast<unsigned int>(time(nullptr)));
			// 몬스터 만들어주고.
			// 패킷도 각 유저들에게 쏴줍니다.
			// 여기에서 메세지를 날려도 되고요.
			std::shared_ptr<ServerMonster> NewMonster = CreateActor<ServerMonster>(3);

			float4 RandomPos;

			RandomPos.x = GameEngineRandom::GetRandomFloat(-GetSize().x, GetSize().x);
			RandomPos.y = GameEngineRandom::GetRandomFloat(-GetSize().y, GetSize().y);

			// GEVector Pos = { (rand() % (GetSize().ix() - 2)) + 1, (rand() % (GetSize().iy() - 2)) + 1 };

			NewMonster->SetPos(RandomPos);
			NewMonster->Setting();

			MsgInsert(&WorldMsgFunc::MonsterUpdate, NewMonster->MonsterData);
			CurMonsterCreateTime = LogicValue::MonsterRegenTime;
			++CurMonsterCount;
		}
	}
}