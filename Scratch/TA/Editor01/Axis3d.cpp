
#include "Axis3d.hpp"
#include "Entropy.hpp"


//=========================================================================
// DEFINES
//=========================================================================
#define ARROW_VERTEX_COUNT ( 50 )
#define ARROW_TRIANGLE_COUNT ( 50 )

//=========================================================================
// VARIABLES
//=========================================================================
static vector3 s_Arrow[3][ ARROW_VERTEX_COUNT + 3 ];
static xbool   s_InititalizeArrows = TRUE;

//=========================================================================
// FUNCTIONS
//=========================================================================

//=========================================================================

axis3d::axis3d( void )
{
    L2W.Identity();

    //
    // Generate the axis for drawing
    //
    if( s_InititalizeArrows )
    {
        s32      i,j;
        radian   r;
        f32      R,L,RL;

        s_InititalizeArrows = FALSE;
        R  = 10;   // Radious of the arrow
        L  = 100;   // Length of the line
        RL = 30;    // Length of the arrow     
        for( i=0; i<3; i++ )
        {
            s_Arrow[i][0].X = 0;
            s_Arrow[i][0].Y = 0;
            s_Arrow[i][0].Z = L;

            s_Arrow[i][1].X = 0;
            s_Arrow[i][1].Y = 0;
            s_Arrow[i][1].Z = L+RL;

            for( j=2, r=0; j<(ARROW_VERTEX_COUNT+3); r += R_1 *(360.0f/(ARROW_VERTEX_COUNT-1)), j++ )
            {
                ASSERT( j < (ARROW_VERTEX_COUNT+3) );
                s_Arrow[i][j].X = x_sin( -r ) * R;
                s_Arrow[i][j].Y = x_cos( -r ) * R;
                s_Arrow[i][j].Z = L;
            }

            // Close the arrow polygon
            s_Arrow[i][j] = s_Arrow[i][2];
        
            if( i == 0 ) 
                for( ; j>=0; j-- ) 
                {
                    s_Arrow[i][j].Rotate( radian3( 0,R_1*90, 0) );
                }

            if( i == 1 ) 
                for( ; j>=0; j-- ) 
                {
                    s_Arrow[i][j].Rotate( radian3(-R_1*90, 0, 0) );
                }
        }
    }
}

//=========================================================================

void axis3d::SetPosition( vector3& Pos )
{   
    L2W.SetTranslation( Pos );
}


//=========================================================================

void axis3d::Render( void )
{
    s32     i;
    vertex  LineBuff[ARROW_VERTEX_COUNT*2];

    g_pd3dDevice->SetTransform( D3DTS_WORLDMATRIX(0), (D3DMATRIX*)&L2W );

    //
    // Set somce basic render modes
    //
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,           FALSE   );
    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   FALSE   );
    g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,           D3DBLEND_ONE  );
    g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,          D3DBLEND_ZERO );

    g_pd3dDevice->SetVertexShader( D3DFVF_XYZ );

    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,      D3DTOP_SELECTARG1 );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1,    D3DTA_TFACTOR     );

    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,      D3DTOP_SELECTARG1 );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1,    D3DTA_TFACTOR     );

    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP,      D3DTOP_DISABLE    );
    g_pd3dDevice->SetTextureStageState( 1, D3DTSS_ALPHAOP,      D3DTOP_DISABLE    );


    //
    // Render the axis line
    //
    g_pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR,      xcolor(255,0,0,255) );
    LineBuff[0].Pos.Set( 0, 0, 0 );
    LineBuff[1].Pos.Set( s_Arrow[0][0].X, s_Arrow[0][0].Y, s_Arrow[0][0].Z );
    g_pd3dDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, LineBuff, sizeof(vertex) );


    g_pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR,      xcolor(0,255,0,255) );
    LineBuff[0].Pos.Set( 0, 0, 0 );
    LineBuff[1].Pos.Set( s_Arrow[1][0].X, s_Arrow[1][0].Y, s_Arrow[1][0].Z );
    g_pd3dDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, LineBuff, sizeof(vertex) );


    g_pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR,      xcolor(0,0,255,255) );
    LineBuff[0].Pos.Set( 0, 0, 0 );
    LineBuff[1].Pos.Set( s_Arrow[2][0].X, s_Arrow[2][0].Y, s_Arrow[2][0].Z );
    g_pd3dDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, LineBuff, sizeof(vertex) );

    //
    // Render the axis arrows
    //
    g_pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR, xcolor(255,0,0,255) );
    for( i=1; i<(ARROW_VERTEX_COUNT+2); i++ ) 
		LineBuff[i-1].Pos.Set( s_Arrow[0][i].X, s_Arrow[0][i].Y, s_Arrow[0][i].Z );
    g_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, ARROW_TRIANGLE_COUNT-1, LineBuff, sizeof(vertex) );


    g_pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR, xcolor(0,255,0,255) );
    for( i=1; i<(ARROW_VERTEX_COUNT+2); i++ ) 
		LineBuff[i-1].Pos.Set( s_Arrow[1][i].X, s_Arrow[1][i].Y, s_Arrow[1][i].Z );
    g_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, ARROW_TRIANGLE_COUNT-1, LineBuff, sizeof(vertex) );


    g_pd3dDevice->SetRenderState( D3DRS_TEXTUREFACTOR, xcolor(0,0,255,255) );
    for( i=1; i<(ARROW_VERTEX_COUNT+2); i++ ) 
		LineBuff[i-1].Pos.Set( s_Arrow[2][i].X, s_Arrow[2][i].Y, s_Arrow[2][i].Z );
    g_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, ARROW_TRIANGLE_COUNT-1, LineBuff, sizeof(vertex) );
    

}