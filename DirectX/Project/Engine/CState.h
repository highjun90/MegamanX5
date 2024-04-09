#pragma once
#include "CEntity.h"


class CFSM;
class CStateMachine;

class CState :
    public CEntity
{
private:
    CFSM*       m_FSM;

public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

protected:
    void* GetBlackboardData(const wstring& _strKey);
    CFSM* GetFSM() { return m_FSM; }

    void ChangeState(const wstring& _strStateName);



public:
    CLONE_DISABLE(CState);

    CState();
    ~CState();

    friend class CFSM;

    CFSM* GetFSMDebug() { return m_FSM; }
};

//엄청 고생해서 알아낸것
/* 기본적으로 State들은 Enter와 Exit 상태에서 FSM을 불러오면 FSM 복사본(CStateMachine::m_FSM_Init)을 불러온다.
   하지만 FinalTick()에선 원본 FSM(CStateMachine::m_FSM)을 불러온다.
   
   이게 중요했던 이유는 원본 FSM은 statemachine이 nullptr 이고, 복사본 FSM은 어떤 오브젝트의 컴포넌트인 CStateMachine 객체를 제대로 가리키고 있기 때문이다.
   무슨 이유인진 모르겠는데 어쨌든 Enter, Exit()함수에서는 GetFSM()함수 호출하면 원본 FSM이 불러와지고 finaltick()함수에선 복사본 FSM이 불러와진다.

   이걸 몰라서 아 선생님이 짠 코드는 막 상태머신, 오브젝트 불러오는데 나는 계속 enter, exit()함수에서 똑같은걸 하려다보니 자꾸 접근 오류가 났다.. 진짜 너무너무 힘들었다.
   가만히 보니 선생님은 예시로준 state 다 finaltick()에서 소스코드를 짰다. 근데난 딴 함수들에서 똑같은 코드 넣었는데 왜 안되지 이러고 있었음..

   * 내가 Enter, Exit()함수에서 코드 짠거 고집했냐면 애니메이션은 한번Play()하면 다시 Play()하지 말아야 프레임이 돌아가는데 finaltick()에서 그걸 해버리면 매틱마다 Play()가 호출되니까 1프레임만 애니메이션이 재생되서그럼
     지금은 bool값으로 finaltick()에서 애니메이션 재생하게 했음
 */