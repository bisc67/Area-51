#ifndef __ELEMENT_CYLINDER_HPP
#define __ELEMENT_CYLINDER_HPP

#include "element.hpp"

namespace fx_core
{

//============================================================================
//  element_cylinder
//============================================================================

class element_cylinder : public element
{

protected:
    // Cylinder element data
    xstring             m_BitmapName;
    s32                 m_CombineMode;
    xbool               m_MapPlanar;
    f32                 m_MappingTileU;
    f32                 m_MappingTileV;
    f32                 m_MappingScrollU;
    f32                 m_MappingScrollV;
    s32                 m_nSegments;
    f32                 m_SizeTop;
    f32                 m_SizeBottom;
    xcolor              m_ColorTop;
    xcolor              m_ColorBottom;

public:
                        element_cylinder    ( );
                       ~element_cylinder    ( );

    void                Create              ( const char* pElementID, effect& Effect );
    virtual element*    Duplicate           ( void );

    virtual void        PostCopyPtrFix      ( void );

    virtual void        Render              ( f32 T );

    virtual void        Save                ( igfmgr& Igf );
    virtual void        Load                ( igfmgr& Igf );

    virtual void        ExportData          ( export::fx_elementhdr& ElemHdr, 
                                              xstring& Type,
                                              xbytestream& Stream, 
                                              s32 ExportTarget );

    virtual void        FlagExportTextures  ( void );
    virtual void        ActivateTextures    ( void );

    virtual xbool       OnPropertyChanged   ( s32 T, xstring& Field, xstring& Value );


    //========================================================================
    // Function for enumerating element properties
    //========================================================================
    virtual xbool       GetProperty         ( s32               Idx,
                                              s32               T,
                                              xcolor&           UIColor,
                                              xstring&          Name,
                                              xstring&          Value,
                                              xbool&            IsDisabled,
                                              base::prop_type&  Type );

};


//============================================================================
// export structure
struct element_cylinder_export
{
    xbool               m_MapPlanar;
    f32                 m_MappingTileU;
    f32                 m_MappingTileV;
    f32                 m_MappingScrollU;
    f32                 m_MappingScrollV;
    s32                 m_nSegments;
    f32                 m_SizeTop;
    f32                 m_SizeBottom;
    xcolor              m_ColorTop;
    xcolor              m_ColorBottom;
};


//============================================================================

} // namespace fx_core

#endif
