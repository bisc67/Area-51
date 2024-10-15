///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  blueprint_anchor.hpp
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef blueprint_anchor_hpp
#define blueprint_anchor_hpp

///////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Obj_mgr\obj_mgr.hpp"
#include "x_types.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
// CLASS
///////////////////////////////////////////////////////////////////////////////////////////////////

class blueprint_anchor : public object
{
public:

    CREATE_RTTI( blueprint_anchor, object, object )

                            blueprint_anchor        ( void );
                            ~blueprint_anchor       ( void );
                            
    virtual         bbox    GetLocalBBox    ( void ) const;
    virtual         s32     GetMaterial     ( void ) const { return MAT_TYPE_NULL; }

    virtual         void    OnEnumProp      ( prop_enum& List );
    virtual         xbool   OnProperty      ( prop_query&        I    );
    virtual         void    OnMove( const vector3& newPos );

    virtual const object_desc&  GetTypeDesc     ( void ) const;
    static  const object_desc&  GetObjectType   ( void );

protected:

    virtual         void    OnInit          ( void );
    virtual         void    OnImport        ( text_in& TextIn );

#ifndef X_RETAIL
    virtual         void    OnDebugRender   ( void );
#endif // X_RETAIL
};

///////////////////////////////////////////////////////////////////////////////////////////////////
// END
///////////////////////////////////////////////////////////////////////////////////////////////////
#endif//blueprint_anchor_hpp