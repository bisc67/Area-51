//=========================================================================
//
//  ui_friendlist.cpp
//
//=========================================================================

#include "entropy.hpp"

#include "ui\ui_listbox.hpp"
#include "ui\ui_manager.hpp"
#include "ui\ui_font.hpp"
#include "ui_friendlist.hpp"

#include "StateMgr/StateMgr.hpp"
#include "StringMgr\StringMgr.hpp"

#include "NetworkMgr\NetworkMgr.hpp"
#include "NetworkMgr\GameMgr.hpp"

#if defined(TARGET_PS2)
#include "Entropy\PS2\ps2_misc.hpp"
#endif

//=========================================================================
//  Defines
//=========================================================================

#define SPACE_TOP       4
#define SPACE_BOTTOM    4
#define TEXT_OFFSET     -2

//=========================================================================
//  Structs
//=========================================================================

//=========================================================================
//  Data
//=========================================================================

//=========================================================================
//  Factory function
//=========================================================================

ui_win* ui_friendlist_factory( s32 UserID, ui_manager* pManager, const irect& Position, ui_win* pParent, s32 Flags )
{
    ui_friendlist* pList = new ui_friendlist;
    pList->Create( UserID, pManager, Position, pParent, Flags );

    return (ui_win*)pList;
}

//=========================================================================
//  ui_listbox
//=========================================================================

ui_friendlist::ui_friendlist( void )
{
    // look up IDs for presence icons
    m_IconID[ICON_FRIEND]           =   g_UiMgr->FindBitmap( "icon_friend"          );
    m_IconID[ICON_VOICE_ON]         =   g_UiMgr->FindBitmap( "icon_voice_on"        );
    m_IconID[ICON_VOICE_MUTED]      =   g_UiMgr->FindBitmap( "icon_voice_muted"     );
    m_IconID[ICON_VOICE_THRU_TV]    =   g_UiMgr->FindBitmap( "icon_voice_thru_tv"   );
    m_IconID[ICON_VOICE_SPEAKING]   =   g_UiMgr->FindBitmap( "icon_voice_speaking"  );
    m_IconID[ICON_FRIEND_REQ_SENT]  =   g_UiMgr->FindBitmap( "icon_friend_req_sent" );
    m_IconID[ICON_FRIEND_REQ_RCVD]  =   g_UiMgr->FindBitmap( "icon_friend_req_rcvd" );
    m_IconID[ICON_INVITE_SENT]      =   g_UiMgr->FindBitmap( "icon_invite_sent"     );
    m_IconID[ICON_INVITE_RCVD]      =   g_UiMgr->FindBitmap( "icon_invite_rcvd"     );
    m_IsFriendsList                 =   TRUE;
}

//=========================================================================

ui_friendlist::~ui_friendlist( void )
{
}

//=========================================================================

void ui_friendlist::Render( s32 ox, s32 oy )
{
    s32     i;

    // Only render is visible
    if( m_Flags & WF_VISIBLE )
    {
        xcolor  TextColor1  = XCOLOR_WHITE;
        xcolor  TextColor2  = XCOLOR_BLACK;
        s32     State       = ui_manager::CS_NORMAL;

        // Calculate rectangle
        irect   br;
        irect   r;
        irect   r2;
        br.Set( (m_Position.l+ox), (m_Position.t+oy), (m_Position.r+ox), (m_Position.b+oy) );
        r = br;
        r2 = r;
        r.r -= 14;
        r2.l = r.r;

        // Render appropriate state
        if( m_Flags & WF_DISABLED )
        {
            State = ui_manager::CS_DISABLED;
            TextColor1  = XCOLOR_GREY;
            TextColor2  = xcolor(0,0,0,0);
        }
        else if( (m_Flags & (WF_HIGHLIGHT|WF_SELECTED)) == WF_HIGHLIGHT )
        {
            State = ui_manager::CS_HIGHLIGHT;
            TextColor1  = XCOLOR_WHITE;
            TextColor2  = XCOLOR_BLACK;
        }
        else if( (m_Flags & (WF_HIGHLIGHT|WF_SELECTED)) == WF_SELECTED )
        {
            State = ui_manager::CS_SELECTED;
            TextColor1  = XCOLOR_WHITE;
            TextColor2  = XCOLOR_BLACK;
        }
        else if( (m_Flags & (WF_HIGHLIGHT|WF_SELECTED)) == (WF_HIGHLIGHT|WF_SELECTED) )
        {
            State = ui_manager::CS_HIGHLIGHT_SELECTED;
            TextColor1  = XCOLOR_WHITE;
            TextColor2  = XCOLOR_BLACK;
        }
        else
        {
            State = ui_manager::CS_NORMAL;
            TextColor1  = XCOLOR_WHITE;
            TextColor2  = XCOLOR_BLACK;
        }

        // Add Highlight to list
        if( m_Flags & WF_HIGHLIGHT )
            m_pManager->AddHighlight( m_UserID, br, !(m_Flags & WF_SELECTED) );

        if (g_UiMgr->IsWipeActive())
        {
            irect wipePos;
            g_UiMgr->GetWipePos(wipePos);

            if ( wipePos.b > r.t )
            {
                if ( wipePos.b > r.b )
                {
#ifdef TARGET_PS2
                    gsreg_Begin( 1 );
                    gsreg_SetScissor( r.l, r.t, r.r, r.b );
                    gsreg_End();
#endif
                }
                else
                {
#ifdef TARGET_PS2
                    gsreg_Begin( 1 );
                    gsreg_SetScissor( r.l, r.t, r.r, wipePos.b );
                    gsreg_End();
#endif
                }
            }
        }
        else
        {
            m_pManager->PushClipWindow( r );
        }


        irect   rb = r;

        if (m_ShowFrame)
            rb.Deflate( 1, 1 );


        // render header bar
        if( m_ShowHeaderBar )
        {
            irect hb = rb;
            hb.SetHeight( 22 );          

            m_pManager->RenderRect( hb, m_HeaderBarColor, FALSE );

            //hb.l += 5;
            //RenderTitle( hb, ui_font::h_left|ui_font::v_center, g_StringTableMgr( "ui", "IDS_HEADER_PLAYER" ) );
            
            //hb.l += m_PlayerWidth;
            //hb.r = hb.l + 35;

            //if( m_ScoreFieldMask & SCORE_POINTS )
            //{
            //    RenderTitle( hb, ui_font::h_right|ui_font::v_center, g_StringTableMgr( "ui", "IDS_SCORE" ) );
            //}
            //r.l += 5;

            // move to line below title bar
            rb.t += 22;
            r2.t += 22;
        }
        
        // Render background color       
        m_pManager->RenderRect( rb, m_BackgroundColor, FALSE );
         
        // Render Text & Selection Marker
        irect rl = rb;
        rl.SetHeight( m_LineHeight );
        rl.Deflate( 2, 0 );
        rl.r -= 2;
        rl.Translate( 0, SPACE_TOP );

        // check for empty list
        if ( m_Items.GetCount() == 0 )
        {
            if( m_Flags & (WF_SELECTED) )
            {
                // render cursor bar
                m_pManager->RenderRect( rl, xcolor(79,214,60,192), FALSE );
                if( m_Flags & WF_HIGHLIGHT )
                    m_pManager->AddHighlight( m_UserID, rl );
            }
        }
        else
        {
            for( i=0 ; i<m_nVisibleItems ; i++ )
            {
                s32 iItem = m_iFirstVisibleItem + i;

                if( (iItem >= 0) && (iItem < m_Items.GetCount()) )
                {
                    // Render Selection Rectangle
                    if( (iItem == m_iSelection)  && m_ShowBorders )
                    {
                        if( m_Flags & (WF_SELECTED) )
                        {
                            m_pManager->RenderRect( rl, xcolor(79,214,60,192), FALSE );
                            if( m_Flags & WF_HIGHLIGHT )
                                m_pManager->AddHighlight( m_UserID, rl );
                        }
                        else
                            m_pManager->RenderRect( rl, xcolor(66,158,11,192), FALSE );
                    }
    #ifdef TARGET_PC
                    // Let the hight light track the mouse cursor.
                    if( iItem == m_TrackHighLight )
                    {
                        m_pManager->AddHighlight( m_UserID, rl );
                    }
    #endif

                    // Render Text
                    xcolor c1 = m_Items[iItem].Color;
                    xcolor c2 = TextColor2;
                    if( !m_Items[iItem].Enabled )
                    {
                        c1 = XCOLOR_GREY;
                        c2 = xcolor(0,0,0,0);
                    }
                    else if (iItem == m_iSelection)
                    {
                        if ( m_Flags & WF_SELECTED )
                        {
                            c1 = xcolor(0,0,0,255);
                        }
                        else
                        {
                            c1 = xcolor(126,220,60,255);
                        }
                        c2 = xcolor(0,0,0,0);
                    }
                    irect rl2 = rl;

    //				m_pManager->PushClipWindow( rl2 );

                    RenderItem( rl2, m_Items[iItem], c1, c2 );

				    // Clear the clip window
    //				m_pManager->PopClipWindow();

                }
                rl.Translate( 0, m_LineHeight );
            }
        }

        if (g_UiMgr->IsWipeActive())
        {
#ifdef TARGET_PS2
            // restore correct scissor
            irect wipePos;
            g_UiMgr->GetWipePos(wipePos);

            irect screen;
            g_UiMgr->GetScreenSize(screen);
            
            gsreg_Begin( 1 );
            gsreg_SetScissor( screen.l, screen.t, screen.r, wipePos.b );
            gsreg_End();
#endif
        }
        else
        {
            m_pManager->PopClipWindow();
        }

        if (m_ShowBorders)
        {
            // Render Frame
            if (m_ShowFrame)
                m_pManager->RenderElement( m_iElementFrame, r, 0 );

            irect r3 = r2;
            irect r4 = r2;
            r3.b = r3.t + 16;
            r4.t = r4.b - 16;
            r2.t = r3.b;
            r2.b = r4.t;

#ifdef TARGET_PC
            m_UpArrow = r3;
            m_DownArrow = r4;
#endif
            m_pManager->RenderElement( m_iElement_sb_container, r2, State );
            m_pManager->RenderElement( m_iElement_sb_arrowup,   r3, State );
            m_pManager->RenderElement( m_iElement_sb_arrowdown, r4, State );

            // Render thumb background
            r2.Deflate( 1, 1 );
            r2.l += 1;
            m_pManager->RenderRect( r2, xcolor(20,80,13,128), FALSE );


            // Render Thumb
            r2.Deflate( 1, 1 );
            r2.l += 1;
         
			s32 itemcount;

			itemcount = m_Items.GetCount(); //0;
			//for (s32 i=0;i<m_Items.GetCount();i++)
			//{
			//	if (m_Items[i].Enabled)
			//		itemcount++;
			//}

            if( itemcount > m_nVisibleItems )
            {
                s32 ThumbSize = (s32)(r2.GetHeight() * ((f32)m_nVisibleItems / itemcount));
                if( ThumbSize < 16 )
                    ThumbSize = 16;

                s32 ThumbPos  = (s32)((r2.GetHeight()-ThumbSize) * ((f32)m_iFirstVisibleItem / (itemcount - m_nVisibleItems)));

                r2.Set( r2.l, r2.t + ThumbPos, r2.r, r2.t + ThumbPos + ThumbSize );
            }

            m_pManager->RenderElement( m_iElement_sb_thumb,     r2, State );
#ifdef TARGET_PC
            m_ScrollBar = r2;
#endif
        }

        // Render children
        for( s32 i=0 ; i<m_Children.GetCount() ; i++ )
        {
            m_Children[i]->Render( m_Position.l+ox, m_Position.t+oy );
        }
    }
}

//=========================================================================

void ui_friendlist::RenderString( irect r, u32 Flags, const xcolor& c1, const xcolor& c2, const char* pString )
{
    m_pManager->RenderText( m_Font, r, Flags, c2, pString );
    r.Translate( -1, -1 );
    m_pManager->RenderText( m_Font, r, Flags, c1, pString );
}

//=========================================================================

void ui_friendlist::RenderString( irect r, u32 Flags, const xcolor& c1, const xcolor& c2, const xwchar* pString )
{
    m_pManager->RenderText( m_Font, r, Flags, c2, pString );
    r.Translate( -1, -1 );
    m_pManager->RenderText( m_Font, r, Flags, c1, pString );
}

//=========================================================================

void ui_friendlist::RenderTitle( irect r, u32 Flags, const xwchar* pString )
{
    m_pManager->RenderText( m_Font, r, Flags, XCOLOR_BLACK, pString );
    r.Translate( -1, -1 );
    m_pManager->RenderText( m_Font, r, Flags, m_HeaderColor, pString );
}

//=========================================================================

void ui_friendlist::RenderItem( irect r, const item& Item, const xcolor& c1, const xcolor& c2 )
{
    (void)r;
    (void)Item;
    (void)c1;
    (void)c2;

    r.Deflate( 4, 0 );
    r.Translate( 1, -2 );

    // render the item based on the flags
    if( Item.Flags & FLAG_ITEM_SEPARATOR )
    {
        // render separator
        RenderString( r, ui_font::h_center|ui_font::v_center, c1, c2, xstring("--------------------------------") );
    }
    //else if( Item.Flags & FLAG_ITEM_RECENT_PLAYER )
    //{
    //    // render player name
    //    RenderString( r, ui_font::h_left|ui_font::v_center, c1, c2, Item.Label );
    //}
    else
    {
        // render current player information in the list
        buddy_info* pBuddy = (buddy_info*)Item.Data[0];

        // render presence icon
        r.l += 8;
        r.r = r.l + 26;  
        irect r2 = r;
        r2.t += 3;
        r2.b -= 3;

        // Is there any buddy information existing about this player?
        if( pBuddy )
        {
            // mreed 3/11/05 Here's the TCR for the priority of the buddy icons:
            //  - Received Invitation � Player has received a game invitation from the indicated Friend.
            //  - Received Friend Request � Player has received a Friend Request from the indicated player.
            //  - Sent Invitation � Player has sent a Game Invitation to the indicated Friend [if the game supports multiplayer mode].
            //  - Sent Friend Request � Player has sent a Friend Request to the indicated player.
            //  - Online � Friend is signed in.
            //
            //  We don't have icons for these, but they're in the TCR. I'm leaving them "just in case"
            //  - Offline � Friend is either not signed in or has chosen to appear offline.
            //  - Voice enabled � Friend has a voice peripheral and voice permissions.
            //  - No voice � Player has a Friend who has been voice banned.
            //  - No voice � Player has a Friend who has voice turned off in the Dashboard.
            //  - No voice � Player has a Friend who has no voice peripheral connected.
            //  - Muted � Player has muted the Friend.

            xbool IsInviteAnswered = (pBuddy->Flags & USER_REJECTED_INVITE) ||
                                     (pBuddy->Flags & USER_ACCEPTED_INVITE);

            // check player flags to determine what icon to display (check order for XBox Live)
            if( pBuddy->Flags & USER_HAS_INVITE )
            {
                g_UiMgr->RenderBitmap( m_IconID[ICON_INVITE_RCVD], r2, c1 );
            }
            else if( pBuddy->Flags & USER_REQUEST_RECEIVED )
            {
                g_UiMgr->RenderBitmap( m_IconID[ICON_FRIEND_REQ_RCVD], r2, c1 );
            }
            else if( (pBuddy->Flags & USER_SENT_INVITE) && !IsInviteAnswered )
            {
                g_UiMgr->RenderBitmap( m_IconID[ICON_INVITE_SENT], r2, c1 );
            }
            else if( pBuddy->Flags & USER_REQUEST_SENT )
            {
                g_UiMgr->RenderBitmap( m_IconID[ICON_FRIEND_REQ_SENT], r2, c1 );
            }
            else if( pBuddy->Status == BUDDY_STATUS_ONLINE )
            {
                g_UiMgr->RenderBitmap( m_IconID[ICON_FRIEND], r2, c1 );
            }
            else if( pBuddy->Status == BUDDY_STATUS_INGAME )
            {
                g_UiMgr->RenderBitmap( m_IconID[ICON_FRIEND], r2, c1 );
            }
        }

        // render player name
        r.l += 40;
        r.r = r.l + 300;
        RenderString( r, ui_font::h_center|ui_font::v_center, c1, c2, Item.Label );
        //RenderString( r, ui_font::h_center|ui_font::v_center, c1, c2, playerName );

        // render voice icon
        r.l += 311;
        r.r = r.l + 26;
        r2 = r;
        r2.t += 3;
        r2.b -= 3;
        if( pBuddy )
        {
            if( m_IsFriendsList == TRUE )
            {
                // We are displaying the friends list so user will have valid voice
                // status in the Flags field.
                if( pBuddy->Flags & USER_VOICE_ENABLED )
                {
                    g_UiMgr->RenderBitmap( m_IconID[ ICON_VOICE_ON ], r2, c1 );
                }
            }
            else
            {
                if( pBuddy->Flags & FRIENDLIST_IS_MUTED )
                {
                    g_UiMgr->RenderBitmap( m_IconID[ ICON_VOICE_MUTED ], r2, c1 );
                }
                else
                {
                    if( pBuddy->Flags & FRIENDLIST_IS_VOICE_ALLOWED )
                    {
                        s32 Icon = (pBuddy->Flags & FRIENDLIST_IS_VOICE_CAPABLE) ? ICON_VOICE_ON : ICON_VOICE_THRU_TV;

                        if( pBuddy->Flags & FRIENDLIST_IS_TALKING )
                            Icon = ICON_VOICE_SPEAKING;

                        g_UiMgr->RenderBitmap( m_IconID[ Icon ], r2, c1 );
                    }
                }
            }
        }
    }
}

//=========================================================================

void ui_friendlist::Configure( xbool IsFriendsList )
{
    m_IsFriendsList = IsFriendsList;
}

//=========================================================================
