///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  ai_state_idle.hpp
//
//      - implements an idle state for an actor
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef AI_STATE_IDLE_HPP
#define AI_STATE_IDLE_HPP
#include "ai_state.hpp"

class ai_state_idle : public ai_state
{
public:
                                ai_state_idle(brain* myBrain = NULL);
    virtual                     ~ai_state_idle();

    virtual     void            OnAdvanceLogic( f32 deltaTime );
    virtual     void            OnDamaged(s32 thisDamage, vector3* thisDirection );

    virtual     void            OnEnterState( void ); 
    virtual     xbool           OnAttemptExit( void );
    virtual     void            OnExitState( void );
    
    virtual     void            OnInit( void );
    
    virtual     ai_state_type   GetType(void) { return ai_state::AI_STATE_TYPE_IDLE; }
    virtual     const char*     GetTypeName(void) { return ("IDLE"); }



///////////////////////////////////////////////////////////////////////////////////////////////////
//  Editor
///////////////////////////////////////////////////////////////////////////////////////////////////

    virtual     void            OnEnumProp( prop_enum&  List );
    virtual     xbool           OnProperty( prop_query& I    );



protected:

    char                        m_ExitStateCurious[32];


};


#endif//AI_STATE_IDLE_HPP