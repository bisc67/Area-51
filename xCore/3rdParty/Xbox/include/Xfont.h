//****************************************************************************
//
// XBox font library
//
//****************************************************************************

// NOTE: You need to #define "XFONT_TRUETYPE" before including this
//  : file if you're planning on using the TypeType font scaler.  This 
//  : really should be a rare case and using it does bring in a whole
//  : wad of code. 

#pragma once

// The errors returned from these methods are generally fatal.  Close the 
// current font if you get one.

//****************************************************************************
// Structure definitions.
//****************************************************************************

typedef struct IDirect3DSurface8 IDirect3DSurface8;

//============================================================================
// An opaque structure which holds an active font.  The consumer can get
// and set this structure to allow it to use multiple fonts without 
// unloading them.
//============================================================================
              
typedef struct XFONT XFONT;

#if defined(__cplusplus)

struct XFONT
{
    void    __stdcall AddRef();
    void    __stdcall Release();

    unsigned __stdcall GetTextHeight();
    HRESULT  __stdcall SetTextHeight(unsigned uHeight);

    unsigned __stdcall GetTextAntialiasLevel();
    HRESULT  __stdcall SetTextAntialiasLevel(unsigned uAntialiasLevel);

    unsigned __stdcall GetRLEWidth();
    HRESULT  __stdcall SetRLEWidth(unsigned uRLEWidth);

    unsigned __stdcall GetTextStyle();
    HRESULT  __stdcall SetTextStyle(unsigned uStyle);

    unsigned __stdcall GetTextAlignment();
    void     __stdcall SetTextAlignment(unsigned uMode);

    D3DCOLOR __stdcall GetTextColor();
    void     __stdcall SetTextColor(D3DCOLOR color);

    D3DCOLOR __stdcall GetBkColor();
    void     __stdcall SetBkColor(D3DCOLOR color);

    int      __stdcall GetBkMode();
    void     __stdcall SetBkMode(int iBkMode);

    unsigned __stdcall GetIntercharacterSpacing();
    void     __stdcall SetIntercharacterSpacing(unsigned uSpaces);

    D3DRECT *__stdcall GetClippingRectangle();
    void     __stdcall SetClippingRectangle(D3DRECT *pRectangle);

    void     __stdcall GetFontMetrics(unsigned *puCellHeight, unsigned *puDescent);
    HRESULT  __stdcall GetTextExtent(LPCWSTR wstr,   unsigned cch, unsigned *puWidth);
    HRESULT  __stdcall TextOutToMemory(LPCVOID pBits, unsigned Pitch, unsigned Width, unsigned Height, D3DFORMAT Format, LPCWSTR wstr, unsigned cch, long x, long y);
    HRESULT  __stdcall TextOut(IDirect3DSurface8 *pSurface, LPCWSTR wstr, unsigned cch, long x, long y);
};

#endif !defined(__cplusplus)

//****************************************************************************
// The APIs
//****************************************************************************

#if defined(__cplusplus)

extern "C" {

#endif !defined(__cplusplus)

//============================================================================
// Loads a bitmap font of the format defined in xfontformat.h from a file.
//
// This method always allocates ~112 bytes for each font to store the
// font's state.  Additional memory will be allocated depending on the
// value of the uCacheSize parameter:
//
//    0                            - an allocation to hold the bitmap for the 
//                                   last drawn glyph.  The glyph information
//                                   is ready directly out of the file as
//                                   each glyph is drawn.  Very slow.
//
//    uCacheSize < font file size  - a block of memory of size uCacheSize 
//                                   holds the most recently drawn glyphs.  
//                                   The glyph information is ready directly 
//                                   out of the file.  This can perform 
//                                   reasonably if the cache is sized
//                                   correctly via experimentation.
//
//    uCacheSize >= font file size - a block of memory just large enough to 
//                                   hold the contents of the file will be 
//                                   allocated and the entire font file will 
//                                   be loaded into it.  Very fast.
//
//============================================================================

HRESULT __stdcall XFONT_OpenBitmapFont
(
    LPCWSTR wszFileName,    // [in] The file name of the font
    unsigned uCacheSize,    // [in] The size of the font cache, in bytes.
    XFONT **ppFont          // [out] The font identifier
);

//============================================================================
// Loads a bitmap font of the format defined in xfontformat.h from a block
// of memory, either one that has been loaded into memory by the caller
// or one that is compiled into the title from a source code file
// generated by makefont.exe.
//
// This method always allocates ~112 bytes for each font to store the font's
// current state.  No additional memory will be allocated throughout the 
// lifetime of the font.
//
// The caller must ensure that the memory block that contains the font data
// will live at least as long as the font as it will keep referencing that
// data when it draws.
// 
//============================================================================

HRESULT __stdcall XFONT_OpenBitmapFontFromMemory
(
    CONST void *pFontData,  // [in] The block of font data
    unsigned uFontDataSize, // [in] The size of the font data
    XFONT **ppFont          // [out] The font identifier
);

//============================================================================
// Loads the default bitmap font that is compiled directy into the library.
// This is a 24 pixel hight= arial font the contains only the western 
// character set and is intended as a convenience for titles that just need a 
// quick way of displaying information.
//
// This will also allocate ~112 bytes of memory each time this method is 
// called but will never allocate any more memory throughout the lifetime
// of the font.
//
//============================================================================

HRESULT __stdcall XFONT_OpenDefaultFont
(
    XFONT **ppFont          // [out] The font identifier
);

#if defined(XFONT_TRUETYPE)

//============================================================================
// Load a TrueType font into the scan converter.  
//
// This call will use more memory than just the the cache because the 
// TrueType scan converter needs a bit of workspace to process the font.  If 
// memory is a concern, use a bitmap font instead.
//
// This automatically sets the opened font as the one that is currently
// active.  The attributes of the font are all set to their defaults.
//============================================================================

HRESULT __stdcall XFONT_OpenTrueTypeFont
(
    LPCWSTR wszFileName,    // [in] The path name to the font
    unsigned uCacheSize,    // [in] The size of the font cache, in bytes.
    XFONT **ppFont          // [out] The font identifier
);

#endif 

//============================================================================
// Add a refcount to the font.
//============================================================================

void __stdcall XFONT_AddRef
(
    XFONT *pXFont           // [in] The id of the font
);

//============================================================================
// Unload a font and free all of its memory.  The XFONT identifier will be 
// invalidated.
//============================================================================

void __stdcall XFONT_Release
(
    XFONT *pXFont           // [in] The id of the font to unload
);

//============================================================================
// Sets the height of the text cell, in pixels, for the current font.
//
// Defaults to 16 pixels high.  This may only be set on a TrueType font.
//============================================================================

unsigned __stdcall XFONT_GetTextHeight
(
    XFONT *pXFont           // [in] The id of the font
);

HRESULT __stdcall XFONT_SetTextHeight
(
    XFONT *pXFont,          // [in] The id of the font
    unsigned uHeight        // [in] The total height of the text cell   
);

//============================================================================
// Sets the amount of antialias information to include in the bitmap with
// valid values of 0 (no information), 2, or 4 (lots of information).
//
// The antialiasing works best for larger or bold fonts whose strokes are 
// more the one pixel wide.  
//
// This may only be set on a TrueType font.  Defaults to 0.
//============================================================================

unsigned __stdcall XFONT_GetTextAntialiasLevel
(
    XFONT *pXFont           // [in] The id of the font
);

HRESULT __stdcall XFONT_SetTextAntialiasLevel
(
    XFONT *pXFont,          // [in] The id of the font
    unsigned uAntialiasLevel
);

//============================================================================
// Sets the size of the RLE packet used to compress the internal bitmaps
// used by the font.  This may effect the number of bitmaps that can fit
// in the internal cache depending on the size and characteristics of your
// font.  May be 2-8.
//
// This may only be set on a TrueType font.  Defaults to 2.
//============================================================================

unsigned __stdcall XFONT_GetRLEWidth
(
    XFONT *pXFont           // [in] The id of the font
);

HRESULT __stdcall XFONT_SetRLEWidth
(
    XFONT *pXFont,          // [in] The id of the font
    unsigned uRLEWidth
);

//============================================================================
// Sets the style for the text, one of NORMAL, BOLD, ITALICS or BOLDITALICS.
// This will cause the TrueType font scaler to simulate these styles when
// generating the bitmaps for the font.  If the font defines the different
// styles in separate TTF files then load each individually instead of 
// using this method.
//
// Defaults to XFONT_NORMAL.  This may only be set on a TrueType font.
//============================================================================

#define XFONT_NORMAL          1
#define XFONT_BOLD            2
#define XFONT_ITALICS         3
#define XFONT_BOLDITALICS     4

unsigned __stdcall XFONT_GetTextStyle
(
    XFONT *pXFont           // [in] The id of the font
);

HRESULT __stdcall XFONT_SetTextStyle
(
    XFONT *pXFont,          // [in] The id of the font
    unsigned uStyle
);

//============================================================================
// Sets to what part of the text the coordinates passed to XFONT_TextOut refers.
//
// The only parameter must contain one vertical value ORed with one 
// horizontal value.
//
// The vertical alignment value specifies which part of the text is pointed
// to by the y coordinate:
//
//      XFONT_BASELINE  - the baseline of the text
//      XFONT_BOTTOM    - the bottom of the character cell
//      XFONT_TOP       - the top of the character cell
//
// The horizontal alignment value specifies which part of the text is pointed
// to by the x coordinate:
//
//      XFONT_CENTER    - the center of the text
//      XFONT_LEFT      - the leftmost edge of the text
//      XFONT_RIGHT     - the rightmost edge of the text
//
// Defaults to XFONT__TOP | XFONT__LEFT.
//============================================================================

#define XFONT_LEFT                      0
#define XFONT_RIGHT                     2
#define XFONT_CENTER                    6

#define XFONT_TOP                       0
#define XFONT_BOTTOM                    8
#define XFONT_BASELINE                  24

unsigned __stdcall XFONT_GetTextAlignment
(
    XFONT *pXFont           // [in] The id of the font
);

void __stdcall XFONT_SetTextAlignment
(
    XFONT *pXFont,          // [in] The id of the font
    unsigned uMode
);

//============================================================================
// Sets the color for the text.
//
// Defaults to white.
//============================================================================

D3DCOLOR __stdcall XFONT_GetTextColor
(
    XFONT *pXFont           // [in] The id of the font
);

void __stdcall XFONT_SetTextColor
(
    XFONT *pXFont,          // [in] The id of the font
    D3DCOLOR color          // [in] The color of the text
);

//============================================================================
// Sets the color with which to fill the background of the text.  The format
// of the color must match the format of the surfacing being drawn on.
//
// Defaults to black.
//============================================================================

D3DCOLOR __stdcall XFONT_GetBkColor
(
    XFONT *pXFont           // [in] The id of the font
);

void __stdcall XFONT_SetBkColor
(
    XFONT *pXFont,          // [in] The id of the font
    D3DCOLOR color          // [in] The color of the text
);

//============================================================================
// Sets whether to fill the background of the text cell with the background
// color.
//
// Defaults to XFONT_TRANSPARENT because it is faster.
//============================================================================

#define XFONT_TRANSPARENT         1
#define XFONT_OPAQUE              2

int __stdcall XFONT_GetBkMode
(
    XFONT *pXFont           // [in] The id of the font
);

void __stdcall XFONT_SetBkMode
(
    XFONT *pXFont,          // [in] The id of the font
    int iBkMode             // [in] Either XFONT_OPAQUE or XFONT_TRANSPARENT
);

//============================================================================
// Sets the number of additional pixels to put between each character.
//============================================================================

unsigned __stdcall XFONT_GetIntercharacterSpacing
(
    XFONT *pXFont           // [in] The id of the font
);

void __stdcall XFONT_SetIntercharacterSpacing
(
    XFONT *pXFont,          // [in] The id of the font
    unsigned uSpaces        // [in] Extra pixels between each character
);

//============================================================================
// Sets the clipping rectangle.  Pass NULL to clear.
//============================================================================

// Returns NULL if no clipping rectangle is set.  The memory returned gets
// overwritten each time this method is called.
//
D3DRECT *__stdcall XFONT_GetClippingRectangle
(
    XFONT *pXFont           // [in] The id of the font
);

void __stdcall XFONT_SetClippingRectangle
(
    XFONT *pXFont,          // [in] The id of the font
    D3DRECT *pRectangle     // [in] Clipping rectangle
);

//============================================================================
// Get the vertical metrics for the current font settings.  
//============================================================================

void __stdcall XFONT_GetFontMetrics
(
    XFONT *pXFont,          // [in] The id of the font
    unsigned *puCellHeight,     
    unsigned *puDescent
);

//============================================================================
// Get the width of a string in pixels. This method applies any 
// intercharacter spacing.
//============================================================================

HRESULT __stdcall XFONT_GetTextExtent
(
    XFONT *pXFont,          // [in] The id of the font
    LPCWSTR wstr,           // [in] The string
    unsigned cch,           // [in] The length of the string, -1 for a zero 
                            //      terminated string
    unsigned *puWidth       // [out] The width of the string in pixels
);

//============================================================================
// Draw the text in a chunk of memory.  See XFONT_SetTextAlignment for the 
// meaning of the x and y coordinates.
//============================================================================
                        
HRESULT __stdcall XFONT_TextOutToMemory
(
    XFONT *pXFont,          // [in] The id of the font to unload
    LPCVOID pBits,          // [in] Memory to write to.
    unsigned Pitch,         // [in] The pitch of that memory.
    unsigned Width,         // [in] Width, in pixels, of the memory
    unsigned Height,        // [in] Hight, in pixels, of the memory.
    D3DFORMAT Format,       // [in] Format of the pixels in the memory.
    LPCWSTR wstr,           // [in] The string
    unsigned cch,           // [in] The length of the string, -1 for a zero terminated string
    long x,                 // [in] The x coordinate of the string
    long y                  // [in] The y coordinate of the string
);


//============================================================================
// Draw the text on a surface.  See XFONT_SetTextAlignment for the meaning of
// the x and y coordinates.  This does not work for swizzled surfaces!
//============================================================================

HRESULT __stdcall XFONT_TextOut
(
    XFONT *pXFont,          // [in] The id of the font
    IDirect3DSurface8 *pSurface,    // [in] The surface to draw the text on
    LPCWSTR wstr,           // [in] The string
    unsigned cch,           // [in] The length of the string, -1 for a zero terminated string
    long x,                 // [in] The x coordinate of the string
    long y                  // [in] The y coordinate of the string
);


#if defined(__cplusplus)

};

#endif defined(__cplusplus)


#if defined(__cplusplus)

__forceinline void     __stdcall XFONT::AddRef() { XFONT_AddRef(this); }
__forceinline void     __stdcall XFONT::Release() { XFONT_Release(this); }

__forceinline unsigned __stdcall XFONT::GetTextHeight() { return XFONT_GetTextHeight(this); }
__forceinline HRESULT  __stdcall XFONT::SetTextHeight(unsigned uHeight) { return XFONT_SetTextHeight(this, uHeight); }
__forceinline unsigned __stdcall XFONT::GetTextAntialiasLevel() { return XFONT_GetTextAntialiasLevel(this); }
__forceinline HRESULT  __stdcall XFONT::SetTextAntialiasLevel(unsigned uAntialiasLevel) { return XFONT_SetTextAntialiasLevel(this, uAntialiasLevel); }
__forceinline unsigned __stdcall XFONT::GetRLEWidth() { return XFONT_GetRLEWidth(this); }
__forceinline HRESULT  __stdcall XFONT::SetRLEWidth(unsigned uRLEWidth) { return XFONT_SetRLEWidth(this, uRLEWidth); }
__forceinline unsigned __stdcall XFONT::GetTextStyle() { return XFONT_GetTextStyle(this); }
__forceinline HRESULT  __stdcall XFONT::SetTextStyle(unsigned uStyle) { return XFONT_SetTextStyle(this, uStyle); }
__forceinline unsigned __stdcall XFONT::GetTextAlignment() { return XFONT_GetTextAlignment(this); }
__forceinline void     __stdcall XFONT::SetTextAlignment(unsigned uMode) { XFONT_SetTextAlignment(this, uMode); }
__forceinline D3DCOLOR __stdcall XFONT::GetTextColor() { return XFONT_GetTextColor(this); }
__forceinline void     __stdcall XFONT::SetTextColor(D3DCOLOR color) { XFONT_SetTextColor(this, color); }
__forceinline D3DCOLOR __stdcall XFONT::GetBkColor() { return XFONT_GetBkColor(this); }
__forceinline void     __stdcall XFONT::SetBkColor(D3DCOLOR color) { XFONT_SetBkColor(this, color); }
__forceinline int      __stdcall XFONT::GetBkMode() { return XFONT_GetBkMode(this); }
__forceinline void     __stdcall XFONT::SetBkMode(int iBkMode) { XFONT_SetBkMode(this, iBkMode); }
__forceinline unsigned __stdcall XFONT::GetIntercharacterSpacing() { return XFONT_GetIntercharacterSpacing(this); }
__forceinline void     __stdcall XFONT::SetIntercharacterSpacing(unsigned uSpaces) { XFONT_SetIntercharacterSpacing(this, uSpaces); }
__forceinline D3DRECT *__stdcall XFONT::GetClippingRectangle() { return XFONT_GetClippingRectangle(this); }
__forceinline void     __stdcall XFONT::SetClippingRectangle(D3DRECT *pRectangle) { XFONT_SetClippingRectangle(this, pRectangle); }

__forceinline void     __stdcall XFONT::GetFontMetrics(unsigned *puCellHeight, unsigned *puDescent) { XFONT_GetFontMetrics(this, puCellHeight, puDescent); }
__forceinline HRESULT  __stdcall XFONT::GetTextExtent(LPCWSTR wstr, unsigned cch, unsigned *puWidth) { return XFONT_GetTextExtent(this, wstr, cch, puWidth); }
__forceinline HRESULT  __stdcall XFONT::TextOutToMemory(LPCVOID pBits, unsigned Pitch, unsigned Width, unsigned Height, D3DFORMAT Format, LPCWSTR wstr, unsigned cch, long x, long y) { return XFONT_TextOutToMemory(this, pBits, Pitch, Width, Height, Format, wstr, cch, x, y); }
__forceinline HRESULT  __stdcall XFONT::TextOut(IDirect3DSurface8 *pSurface, LPCWSTR wstr, unsigned cch, long x, long y) { return XFONT_TextOut(this, pSurface, wstr, cch, x, y); }

#endif defined(__cplusplus)


