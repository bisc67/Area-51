//==============================================================================
//  
//  dlg_ProfileControls.hpp
//  
//==============================================================================

#ifndef DLG_PROFILE_CONTROLS_HPP
#define DLG_PROFILE_CONTROLS_HPP

//==============================================================================
//  INCLUDES
//==============================================================================

#include "ui\ui_dialog.hpp"
#include "ui\ui_frame.hpp"
#include "ui\ui_text.hpp"
#include "ui\ui_combo.hpp"
#include "ui\ui_slider.hpp"
#include "ui\ui_check.hpp"
#include "ui\ui_button.hpp"

#include "StateMgr\StateMgr.hpp"

//==============================================================================
//  dlg_profile_controls
//==============================================================================

extern void     dlg_profile_controls_register  ( ui_manager* pManager );
extern ui_win*  dlg_profile_controls_factory   ( s32 UserID, ui_manager* pManager, ui_manager::dialog_tem* pDialogTem, const irect& Position, ui_win* pParent, s32 Flags, void* pUserData );

class ui_button;

class dlg_profile_controls : public ui_dialog
{
public:
                        dlg_profile_controls       ( void );
    virtual            ~dlg_profile_controls       ( void );

    xbool               Create              ( s32                       UserID,
                                              ui_manager*               pManager,
                                              ui_manager::dialog_tem*   pDialogTem,
                                              const irect&              Position,
                                              ui_win*                   pParent,
                                              s32                       Flags,
                                              void*                     pUserData);

    virtual void        Destroy             ( void );

    virtual void        Render              ( s32 ox=0, s32 oy=0 );

    virtual void        OnPadSelect         ( ui_win* pWin );
    virtual void        OnPadBack           ( ui_win* pWin );
    virtual void        OnPadDelete         ( ui_win* pWin );
    virtual void        OnUpdate            ( ui_win* pWin, f32 DeltaTime );

    void                EnableBlackout      ( void )                    { m_bRenderBlackout = TRUE; }

protected:
    ui_frame*           m_pFrame1;


    ui_slider*          m_pSensitivityX;
    ui_slider*          m_pSensitivityY;

    ui_check*           m_pToggleInvertY;
    ui_check*           m_pToggleCrouch;
    ui_check*           m_pToggleLookspring;
    ui_check*           m_pToggleVibration;
    ui_check*           m_pToggleAutoSwitch;

    ui_text*            m_pInvertYText;
    ui_text*            m_pSensitivityXText;
    ui_text*            m_pSensitivityYText;
    ui_text*            m_pCrouchText;
    ui_text*            m_pLookspringText;
    ui_text*            m_pVibrationText;
    ui_text*            m_pAutoSwitchText;

    ui_button*          m_pButtonAccept;

    ui_text*            m_pNavText;

    s32                 m_CurrHL;

    xbool               m_bRenderBlackout;

    player_profile      m_Profile;
};

//==============================================================================
#endif // DLG_PROFILE_CONTROLS_HPP
//==============================================================================
