//=============================================================================

#ifndef _SKIN_HPP_
#define _SKIN_HPP_

//=============================================================================

#include "Entropy.hpp"

//=============================================================================

void    skin_Init           ( void );
void    skin_UploadBones    ( const quaternion* pQuat, const vector3* pVert, s32 NumVectors );
void    skin_UploadMatrices ( const matrix4* pMatrix, s32 NumMatrices );

//=============================================================================

inline void skin_LoadVertex0( void* pVert, void* pBone )
{
    // Transfer first vertex to registers and kick the VU0
    asm __volatile__ ("
    .set noreorder

    lhu  $8,    0x00(%1)        # Load Bone0 and Bone1 to CPU register
    lqc2 $vf01, 0x00(%0)        # Load Position and Weight0 to VU0 register
    lqc2 $vf02, 0x10(%0)        # Load Normal   and Weight1 to VU0 register
    srl  $9, $8, 8              # Get Bone1 into register t1
    andi $8, $8, 0xFF           # Get Bone0 into register t0
    ctc2 $8, $vi1               # Transfer Bone0 to VU0 integer register
    ctc2 $9, $vi2               # Transfer Bone1 to VU0 integer register
    .set reorder"
    : : "r"(pVert), "r"(pBone) : "$8", "$9" );
}

//=============================================================================

inline void skin_LoadVertex1( void* pVert, void* pBone )
{
    asm __volatile__ ("
    .set noreorder

    lhu  $8,    0x00(%1)        # Load Bone0 and Bone1 to CPU register
    lqc2 $vf03, 0x00(%0)        # Load Position and Weight0 to VU0 register
    lqc2 $vf04, 0x10(%0)        # Load Normal   and Weight1 to VU0 register
    srl  $9, $8, 8              # Get Bone1 into register t1
    andi $8, $8, 0xFF           # Get Bone0 into register t0
    ctc2 $8, $vi3               # Transfer Bone0 to VU0 integer register
    ctc2 $9, $vi4               # Transfer Bone1 to VU0 integer register
    .set reorder"
    : : "r"(pVert), "r"(pBone) : "$8", "$9" );
}

//=============================================================================

inline void skin_StoreVertex0( void* pOutput )
{
    asm __volatile__ ("
    .set noreorder
    sqc2 $vf01, 0x00(%0)        # Store new position
    sqc2 $vf02, 0x10(%0)        # Store new normal
    .set reorder"
    : : "r"(pOutput) );
}

//=============================================================================

inline void skin_StoreVertex1( void* pOutput )
{
    asm __volatile__ ("
    .set noreorder
    sqc2 $vf03, 0x00(%0)        # Store new position
    sqc2 $vf04, 0x10(%0)        # Store new normal
    .set reorder"
    : : "r"(pOutput) );
}

//=============================================================================

#endif
