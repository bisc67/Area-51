///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  ai_state_attack_passive.hpp
//
//      - attack passive is what would be considered a passive attack state.  AI tried to get to an
//          appropriate range and then attack.
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef AI_STATE_ATTACK_PASSIVE_HPP
#define AI_STATE_ATTACK_PASSIVE_HPP
#include "ai_state_attack.hpp"

class ai_state_attack_passive : public ai_state_attack
{
public:
                                ai_state_attack_passive(brain* myBrain = NULL);
    virtual                     ~ai_state_attack_passive();

    virtual     void            OnAdvanceLogic( f32 deltaTime );

    virtual     void            OnEnterState( void ); 
    virtual     xbool           OnAttemptExit( void );
    virtual     void            OnExitState( void );
    
    virtual     void            OnInit( void );
    
    virtual     ai_state_type   GetType(void) { return ai_state::AI_STATE_TYPE_ATTACK_PASSIVE; }
    virtual     const char*     GetTypeName(void) { return ("ATTACK_PASSIVE"); }




///////////////////////////////////////////////////////////////////////////////////////////////////
//  Editor
///////////////////////////////////////////////////////////////////////////////////////////////////

    virtual     void            OnEnumProp( prop_enum&  List );
    virtual     xbool           OnProperty( prop_query& I    );




protected:
    
    guid        m_Target;


};


#endif//AI_STATE_ATTACK_PASSIVE_HPP