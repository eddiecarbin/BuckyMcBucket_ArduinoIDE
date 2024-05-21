#ifndef STATEMACHINE_H__
#define STATEMACHINE_H__

#include <Arduino.h>
#include "BuckeyContext.h"
#include "State.h"

// https://github.com/Arekushi/Finite-State-Machine-Arduino/tree/master/src

// https://github.com/Arekushi/Finite-Statte-Machine-Arduino

// class State;

class StateMachine
{

public:
    StateMachine(BuckeyContext &data, State *initState)
        : m_data(data), m_currentState(nullptr), m_currentStateIndex(-1)
    {
        setCurrentState(initState);
    }

    void setCurrentState(State *newState)
    {
        exitCurrentState();
        m_currentState = newState;
        enterCurrentState();
    }

    // void executeMachine()
    // {
    //     if (m_currentState)
    //     {
    //         m_currentState->executeState(*this);
    //     }
    // }

    void transitionNextState(State *nextState)
    {
        if (nextState)
        {
            setCurrentState(nextState);
        }
    }

    int currentStateIndex() const
    {
        return m_currentStateIndex;
    }

    State *currentState() const
    {
        return m_currentState;
    }

    BuckeyContext &data()
    {
        return m_data;
    }

    void update()
    {
        if (m_currentState)
        {
            m_currentState->update(m_data);
        }
    }

private:
    State *m_currentState;

    BuckeyContext &m_data;

    int m_currentStateIndex;

    void exitCurrentState()
    {
        if (m_currentStateIndex > 0)
        {
            m_currentState->exit(m_data);
        }
    }

    void enterCurrentState()
    {
        if (!m_currentState->hasSetup)
        {
            m_currentState->setup();
        }

        m_currentState->enter(m_data);
        m_currentStateIndex++;
    }
};

#endif