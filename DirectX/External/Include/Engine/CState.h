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

//��û ����ؼ� �˾Ƴ���
/* �⺻������ State���� Enter�� Exit ���¿��� FSM�� �ҷ����� FSM ���纻(CStateMachine::m_FSM_Init)�� �ҷ��´�.
   ������ FinalTick()���� ���� FSM(CStateMachine::m_FSM)�� �ҷ��´�.
   
   �̰� �߿��ߴ� ������ ���� FSM�� statemachine�� nullptr �̰�, ���纻 FSM�� � ������Ʈ�� ������Ʈ�� CStateMachine ��ü�� ����� ����Ű�� �ֱ� �����̴�.
   ���� �������� �𸣰ڴµ� ��·�� Enter, Exit()�Լ������� GetFSM()�Լ� ȣ���ϸ� ���� FSM�� �ҷ������� finaltick()�Լ����� ���纻 FSM�� �ҷ�������.

   �̰� ���� �� �������� § �ڵ�� �� ���¸ӽ�, ������Ʈ �ҷ����µ� ���� ��� enter, exit()�Լ����� �Ȱ����� �Ϸ��ٺ��� �ڲ� ���� ������ ����.. ��¥ �ʹ��ʹ� �������.
   ������ ���� �������� ���÷��� state �� finaltick()���� �ҽ��ڵ带 ®��. �ٵ��� �� �Լ��鿡�� �Ȱ��� �ڵ� �־��µ� �� �ȵ��� �̷��� �־���..

   * ���� Enter, Exit()�Լ����� �ڵ� §�� �����߳ĸ� �ִϸ��̼��� �ѹ�Play()�ϸ� �ٽ� Play()���� ���ƾ� �������� ���ư��µ� finaltick()���� �װ� �ع����� ��ƽ���� Play()�� ȣ��Ǵϱ� 1�����Ӹ� �ִϸ��̼��� ����Ǽ��׷�
     ������ bool������ finaltick()���� �ִϸ��̼� ����ϰ� ����
 */