//=========================================================================
//
//  dlg_headset.cpp
//
//=========================================================================

#include "entropy.hpp"

#include "ui\ui_font.hpp"
#include "ui\ui_manager.hpp"
#include "ui\ui_control.hpp"
#include "ui\ui_combo.hpp"
#include "ui\ui_button.hpp"

#include "dlg_Headset.hpp"
#include "stringmgr\stringmgr.hpp"
#include "StateMgr\StateMgr.hpp"

//=========================================================================
//  Main Options Dialog
//=========================================================================

enum controls
{
    IDC_HEADSET_VOLUME_SPEAKER_TEXT,
    IDC_HEADSET_VOLUME_MIC_TEXT,
    IDC_HEADSET_TOGGLE_HEADSET_TEXT,

    IDC_HEADSET_VOLUME_SPEAKER,
    IDC_HEADSET_VOLUME_MIC,
    IDC_HEADSET_TOGGLE_HEADSET,
    IDC_HEADSET_BUTTON_ACCEPT,

    IDC_HEADSET_NAV_TEXT,
};


ui_manager::control_tem HeadsetControls_PAL[] = 
{
    // Frames.
    { IDC_HEADSET_TOGGLE_HEADSET_TEXT,  "IDS_OPTIONS_HEADSET_AUDIO",    "text",      40,  40, 220, 40, 0, 0, 0, 0, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    { IDC_HEADSET_VOLUME_SPEAKER_TEXT,  "IDS_SPEAKER_VOLUME",           "text",      40,  75, 220, 40, 0, 0, 0, 0, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    { IDC_HEADSET_VOLUME_MIC_TEXT,      "IDS_MIC_VOLUME",               "text",      40, 110, 220, 40, 0, 0, 0, 0, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },

    { IDC_HEADSET_TOGGLE_HEADSET,       "IDS_NULL",                     "combo",    225,  49, 202, 40, 0, 0, 1, 1, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    { IDC_HEADSET_VOLUME_SPEAKER,       "IDS_NULL",                     "slider",   270,  85, 120, 40, 0, 1, 1, 1, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    { IDC_HEADSET_VOLUME_MIC,           "IDS_NULL",                     "slider",   270, 120, 120, 40, 0, 2, 1, 1, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    
    { IDC_HEADSET_BUTTON_ACCEPT,        "IDS_PROFILE_OPTIONS_ACCEPT",   "button",    40, 285, 220, 40, 0, 3, 1, 1, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    { IDC_HEADSET_NAV_TEXT,             "IDS_NULL",                     "text",       0,   0,   0,  0, 0, 0, 0, 0, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
};

ui_manager::control_tem HeadsetControls_ENG[] = 
{
    // Frames.
    { IDC_HEADSET_TOGGLE_HEADSET_TEXT,  "IDS_OPTIONS_HEADSET_AUDIO",    "text",      40,  40, 220, 40, 0, 0, 0, 0, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    { IDC_HEADSET_VOLUME_SPEAKER_TEXT,  "IDS_SPEAKER_VOLUME",           "text",      40,  75, 220, 40, 0, 0, 0, 0, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    { IDC_HEADSET_VOLUME_MIC_TEXT,      "IDS_MIC_VOLUME",               "text",      40, 110, 220, 40, 0, 0, 0, 0, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },

    { IDC_HEADSET_TOGGLE_HEADSET,       "IDS_NULL",                     "combo",    280,  49, 140, 40, 0, 0, 1, 1, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    { IDC_HEADSET_VOLUME_SPEAKER,       "IDS_NULL",                     "slider",   290,  85, 120, 40, 0, 1, 1, 1, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    { IDC_HEADSET_VOLUME_MIC,           "IDS_NULL",                     "slider",   290, 120, 120, 40, 0, 2, 1, 1, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
    { IDC_HEADSET_BUTTON_ACCEPT,        "IDS_PROFILE_OPTIONS_ACCEPT",   "button",    40, 285, 220, 40, 0, 3, 1, 1, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },

    { IDC_HEADSET_NAV_TEXT,             "IDS_NULL",                     "text",       0,   0,   0,  0, 0, 0, 0, 0, ui_win::WF_VISIBLE | ui_win::WF_SCALE_XPOS | ui_win::WF_SCALE_XSIZE },
};


ui_manager::dialog_tem HeadsetDialog =
{
    "IDS_PROFILE_HEADSET",
    1, 9,
    sizeof(HeadsetControls_ENG)/sizeof(ui_manager::control_tem),
    &HeadsetControls_ENG[0],
    0
};

//=========================================================================
//  Defines
//=========================================================================

//=========================================================================
//  Structs
//=========================================================================

//=========================================================================
//  Data
//=========================================================================

//=========================================================================
//  Registration function
//=========================================================================

void dlg_headset_register( ui_manager* pManager )
{
#ifndef X_EDITOR
    switch( x_GetLocale() )
    {        
    case XL_LANG_ENGLISH:    // English uses default
        break;

    default:  // PAL
        {
            // set up new profile options dialog controls
            HeadsetDialog.StringID = "IDS_PROFILE_HEADSET";
            HeadsetDialog.NavW = 1;
            HeadsetDialog.NavH = 9;
            HeadsetDialog.nControls = sizeof(HeadsetControls_PAL)/sizeof(ui_manager::control_tem);
            HeadsetDialog.pControls = &HeadsetControls_PAL[0];
            HeadsetDialog.FocusControl = 0;
        }
        break;

    }
#endif

    pManager->RegisterDialogClass( "headset", &HeadsetDialog, &dlg_headset_factory );
}

//=========================================================================
//  Factory function
//=========================================================================

ui_win* dlg_headset_factory( s32 UserID, ui_manager* pManager, ui_manager::dialog_tem* pDialogTem, const irect& Position, ui_win* pParent, s32 Flags, void* pUserData )
{
    dlg_headset* pDialog = new dlg_headset;
    pDialog->Create( UserID, pManager, pDialogTem, Position, pParent, Flags, pUserData );

    return (ui_win*)pDialog;
}

//=========================================================================
//  dlg_headset
//=========================================================================

dlg_headset::dlg_headset( void )
{
}

//=========================================================================

dlg_headset::~dlg_headset( void )
{
    Destroy();
}

//=========================================================================

xbool dlg_headset::Create( s32                        UserID,
                             ui_manager*                pManager,
                             ui_manager::dialog_tem*    pDialogTem,
                             const irect&               Position,
                             ui_win*                    pParent,
                             s32                        Flags,
                             void*                      pUserData )
{
    xbool   Success = FALSE;

    (void)pUserData;

    ASSERT( pManager );

    // Do dialog creation
	Success = ui_dialog::Create( UserID, pManager, pDialogTem, Position, pParent, Flags );

    m_pToggleHeadsetAudio	    = (ui_combo*)   FindChildByID( IDC_HEADSET_TOGGLE_HEADSET       );  
    m_pVolumeSpeaker            = (ui_slider*)  FindChildByID( IDC_HEADSET_VOLUME_SPEAKER       );    
    m_pVolumeMic	            = (ui_slider*)  FindChildByID( IDC_HEADSET_VOLUME_MIC           );
    m_pButtonAccept             = (ui_button*)  FindChildByID( IDC_HEADSET_BUTTON_ACCEPT        );

    m_pToggleHeadsetAudioText	= (ui_text*)    FindChildByID( IDC_HEADSET_TOGGLE_HEADSET_TEXT  );
    m_pVolumeSpeakerText	    = (ui_text*)    FindChildByID( IDC_HEADSET_VOLUME_SPEAKER_TEXT  );
    m_pVolumeMicText	        = (ui_text*)    FindChildByID( IDC_HEADSET_VOLUME_MIC_TEXT      );
    m_pNavText                  = (ui_text*)    FindChildByID( IDC_HEADSET_NAV_TEXT             );

    GotoControl( (ui_control*)m_pToggleHeadsetAudio );
    m_CurrentControl = IDC_HEADSET_TOGGLE_HEADSET;
    m_CurrHL = 0;

    // set range
    m_pVolumeSpeaker ->SetRange( 0, 100 );
    m_pVolumeMic     ->SetRange( 0, 100 );

    // switch off the controls to start
    m_pToggleHeadsetAudio      ->SetFlag( ui_win::WF_VISIBLE, FALSE );
    m_pVolumeSpeaker           ->SetFlag( ui_win::WF_VISIBLE, FALSE );
    m_pVolumeMic               ->SetFlag( ui_win::WF_VISIBLE, FALSE );
    m_pButtonAccept            ->SetFlag( ui_win::WF_VISIBLE, FALSE );

    m_pToggleHeadsetAudioText  ->SetFlag( ui_win::WF_VISIBLE, FALSE );
    m_pVolumeSpeakerText       ->SetFlag( ui_win::WF_VISIBLE, FALSE );
    m_pVolumeMicText           ->SetFlag( ui_win::WF_VISIBLE, FALSE );
    m_pNavText                 ->SetFlag( ui_win::WF_VISIBLE, FALSE );

    m_pToggleHeadsetAudioText  ->SetLabelFlags( ui_font::h_left|ui_font::v_center );
    m_pVolumeSpeakerText       ->SetLabelFlags( ui_font::h_left|ui_font::v_center );
    m_pVolumeMicText           ->SetLabelFlags( ui_font::h_left|ui_font::v_center );

    // set button alignment
    m_pButtonAccept            ->SetFlag( ui_win::WF_BUTTON_LEFT, TRUE );

    // initialize headset audio toggle
    m_pToggleHeadsetAudio->SetNavFlags( ui_combo::CB_CHANGE_ON_NAV | ui_combo::CB_CHANGE_ON_SELECT );

    #ifndef TARGET_XBOX
    m_pToggleHeadsetAudio->AddItem( g_StringTableMgr( "ui", "IDS_OFF"         ), HEADSET_DISABLED           );
    #endif
    m_pToggleHeadsetAudio->AddItem( g_StringTableMgr( "ui", "IDS_HEADSET"     ), HEADSET_HEADSET_ONLY       );
    m_pToggleHeadsetAudio->AddItem( g_StringTableMgr( "ui", "IDS_TV_SPEAKERS" ), HEADSET_THROUGH_SPEAKERS   );

    // set up nav text
    xwstring navText(g_StringTableMgr( "ui", "IDS_NAV_SELECT" ));
    navText += g_StringTableMgr( "ui", "IDS_NAV_CANCEL" );
    navText += g_StringTableMgr( "ui", "IDS_NAV_RESTORE_DEFAULTS" );
  
    m_pNavText->SetLabel( navText );
    m_pNavText->SetLabelFlags( ui_font::h_center|ui_font::v_top|ui_font::is_help_text );
    m_pNavText->UseSmallText(TRUE);

    // set default values from pending settings
    global_settings& Settings = g_StateMgr.GetPendingSettings();

    // Ignore the global headset settings if the user is voice banned
    headset_mode HeadsetMode = Settings.GetHeadsetMode();

    // Lookup the correct item index for the desired headset mode
    s32 Selection = 0;
    for( s32 i = 0; i < m_pToggleHeadsetAudio->GetItemCount(); i++ )
    {
        if( HeadsetMode == m_pToggleHeadsetAudio->GetItemData( i ) )
        {
            Selection = i;
            break;
        }
    }

    m_pVolumeSpeaker        ->SetValue     ( Settings.GetVolume( VOLUME_SPEAKER ) );
    m_pVolumeMic            ->SetValue     ( Settings.GetVolume( VOLUME_MIC     ) );
    m_pToggleHeadsetAudio   ->SetSelection ( Selection );

    // initialize screen scaling
    InitScreenScaling( Position );

    // disable background filter
    m_bRenderBlackout = FALSE;

    // make the dialog active
    m_State = DIALOG_STATE_ACTIVE;

    // Return success code
    return Success;
}

//=========================================================================

void dlg_headset::Destroy( void )
{
    ui_dialog::Destroy();

    // kill screen wipe
    g_UiMgr->ResetScreenWipe();
}

//=========================================================================

void dlg_headset::Render( s32 ox, s32 oy )
{
    static s32 offset   =  0;
    static s32 gap      =  9;
    static s32 width    =  4;

	irect rb;
    
    if( m_bRenderBlackout )
    {
	    s32 XRes, YRes;
        eng_GetRes(XRes, YRes);
#ifdef TARGET_PS2
        // Nasty hack to force PS2 to draw to rb.l = 0
        rb.Set( -1, 0, XRes, YRes );
#else
        rb.Set( 0, 0, XRes, YRes );
#endif
        g_UiMgr->RenderGouraudRect(rb, xcolor(0,0,0,180),
                                    xcolor(0,0,0,180),
                                    xcolor(0,0,0,180),
                                    xcolor(0,0,0,180),FALSE);
    }

    // render transparent screen
    rb.l = m_CurrPos.l + 22;
    rb.t = m_CurrPos.t;
    rb.r = m_CurrPos.r - 23;
    rb.b = m_CurrPos.b;

    g_UiMgr->RenderGouraudRect(rb, xcolor(56,115,58,64),
                                   xcolor(56,115,58,64),
                                   xcolor(56,115,58,64),
                                   xcolor(56,115,58,64),FALSE);


    // render the screen bars
    s32 y = rb.t + offset;    

    while (y < rb.b)
    {
        irect bar;

        if ((y+width) > rb.b)
        {
            bar.Set(rb.l, y, rb.r, rb.b);
        }
        else
        {
            bar.Set(rb.l, y, rb.r, y+width);
        }

        // draw the bar
        g_UiMgr->RenderGouraudRect(bar, xcolor(56,115,58,30),
                                        xcolor(56,115,58,30),
                                        xcolor(56,115,58,30),
                                        xcolor(56,115,58,30),FALSE);

        y+=gap;
    }
    
    // increment the offset
    if (++offset > 9)
        offset = 0;

    // render the normal dialog stuff
    ui_dialog::Render( ox, oy );

    // render the glow bar
    g_UiMgr->RenderGlowBar();
}

//=========================================================================

void dlg_headset::OnPadSelect( ui_win* pWin )
{
    // accept changes
    if ( m_State == DIALOG_STATE_ACTIVE )
    {
        if( pWin == (ui_win*)m_pButtonAccept )
        {
            // get the pending settings
            global_settings& Settings = g_StateMgr.GetPendingSettings();

            // update the settings
            Settings.SetVolume( VOLUME_MIC,     m_pVolumeMic->GetValue()     );
            Settings.SetVolume( VOLUME_SPEAKER, m_pVolumeSpeaker->GetValue() );            
            Settings.SetHeadsetMode( (headset_mode)m_pToggleHeadsetAudio->GetSelectedItemData() );

            g_AudioMgr.Play( "Select_Norm" );
            m_State = DIALOG_STATE_BACK;
        }
    }
}

//=========================================================================

void dlg_headset::OnPadBack( ui_win* pWin )
{
    (void)pWin;

    // cancel
    if ( m_State == DIALOG_STATE_ACTIVE )
    {
        g_AudioMgr.Play( "Backup" );
        m_State = DIALOG_STATE_BACK;
    }
}

//=========================================================================

void dlg_headset::OnPadDelete( ui_win* pWin )
{
    (void)pWin;

    // restore defaults
    if ( m_State == DIALOG_STATE_ACTIVE )
    {
        g_AudioMgr.Play("Select_Norm");

        // get the default HEADSET settings
        global_settings TempSettings;
        TempSettings.Reset( RESET_HEADSET );

        // Ignore the global headset settings if the user is voice banned
        headset_mode HeadsetMode = TempSettings.GetHeadsetMode();
        TempSettings.UpdateHeadsetMode( HeadsetMode );

        // Lookup the correct item index for the desired headset mode
        s32 Selection = 0;
        for( s32 i = 0; i < m_pToggleHeadsetAudio->GetItemCount(); i++ )
        {
            if( HeadsetMode == m_pToggleHeadsetAudio->GetItemData( i ) )
            {
                Selection = i;
                break;
            }
        }

        // update controls with changes
        m_pVolumeSpeaker        ->SetValue    ( TempSettings.GetVolume( VOLUME_SPEAKER ) );
        m_pVolumeMic            ->SetValue    ( TempSettings.GetVolume( VOLUME_MIC     ) );
        m_pToggleHeadsetAudio   ->SetSelection( Selection );
    }
}

//=========================================================================

void dlg_headset::OnUpdate ( ui_win* pWin, f32 DeltaTime )
{
    (void)pWin;
    (void)DeltaTime;

    s32 highLight = -1;

    // scale window if necessary
    if( g_UiMgr->IsScreenScaling() )
    {
        if( UpdateScreenScaling( DeltaTime ) == FALSE )
        {
            // turn on the buttons
            m_pToggleHeadsetAudio       ->SetFlag( ui_win::WF_VISIBLE, TRUE );
            m_pVolumeSpeaker            ->SetFlag( ui_win::WF_VISIBLE, TRUE );
            m_pVolumeMic                ->SetFlag( ui_win::WF_VISIBLE, TRUE );
            m_pButtonAccept             ->SetFlag( ui_win::WF_VISIBLE, TRUE );

            m_pToggleHeadsetAudioText   ->SetFlag( ui_win::WF_VISIBLE, TRUE );
            m_pVolumeSpeakerText        ->SetFlag( ui_win::WF_VISIBLE, TRUE );
            m_pVolumeMicText            ->SetFlag( ui_win::WF_VISIBLE, TRUE );
            m_pNavText                  ->SetFlag( ui_win::WF_VISIBLE, TRUE );

            #ifdef TARGET_XBOX
            m_pVolumeMic                ->SetFlag( ui_win::WF_VISIBLE, FALSE );
            m_pVolumeMic                ->SetFlag( ui_win::WF_DISABLED,TRUE  );
            m_pVolumeMicText            ->SetFlag( ui_win::WF_VISIBLE, FALSE );
            m_pVolumeMicText            ->SetFlag( ui_win::WF_DISABLED,TRUE  );
            #endif

            GotoControl( (ui_control*)m_pToggleHeadsetAudio );
            m_pToggleHeadsetAudio->SetFlag(WF_HIGHLIGHT, TRUE);        
            g_UiMgr->SetScreenHighlight( m_pToggleHeadsetAudioText->GetPosition() );
        }
    }

    // update the glow bar
    g_UiMgr->UpdateGlowBar(DeltaTime);

    // update labels
    if( m_pToggleHeadsetAudio->GetFlags(WF_HIGHLIGHT) )
    {
        highLight = 0;
        m_pToggleHeadsetAudioText->SetLabelColor( xcolor(255,252,204,255) );
        g_UiMgr->SetScreenHighlight( m_pToggleHeadsetAudioText->GetPosition() );
    }
    else
        m_pToggleHeadsetAudioText->SetLabelColor( xcolor(126,220,60,255) );

    if( m_pVolumeSpeaker->GetFlags(WF_HIGHLIGHT) )
    {
        highLight = 1;
        m_pVolumeSpeakerText->SetLabelColor( xcolor(255,252,204,255) );
        g_UiMgr->SetScreenHighlight( m_pVolumeSpeakerText->GetPosition() );
    }
    else
        m_pVolumeSpeakerText->SetLabelColor( xcolor(126,220,60,255) );

    if( m_pVolumeMic->GetFlags(WF_HIGHLIGHT) )
    {
        highLight = 2;
        m_pVolumeMicText->SetLabelColor( xcolor(255,252,204,255) );
        g_UiMgr->SetScreenHighlight( m_pVolumeMicText->GetPosition() );
    }
    else
        m_pVolumeMicText->SetLabelColor( xcolor(126,220,60,255) );
    
    if( m_pButtonAccept->GetFlags(WF_HIGHLIGHT) )
    {
        highLight = 3;
        g_UiMgr->SetScreenHighlight( m_pButtonAccept->GetPosition() );
    }

    if( highLight != m_CurrHL )
    {
        if( highLight != -1 )
            g_AudioMgr.Play("Cusor_Norm");

        m_CurrHL = highLight;
    }
}

//=========================================================================
