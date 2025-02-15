/*
 *	lame utility library include file
 *
 *	Copyright (c) 1999 Albert L Faber
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef LAME_UTIL_H
#define LAME_UTIL_H

/***********************************************************************
*
*  Global Include Files
*
***********************************************************************/
#include "machine.h"
#include "encoder.h"
#include "lame.h"
#include "lame_global_flags.h"
#include "lame-analysis.h"
#include "id3tag.h"

#if HAVE_INTTYPES_H
# include <inttypes.h>
#else
# if HAVE_STDINT_H
#  include <stdint.h>
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
*
*  Global Definitions
*
***********************************************************************/

#ifndef FALSE
#define         FALSE                   0
#endif

#ifndef TRUE
#define         TRUE                    (!FALSE)
#endif

#ifdef UINT_MAX
# define         MAX_U_32_NUM            UINT_MAX
#else
# define         MAX_U_32_NUM            0xFFFFFFFF
#endif

#ifndef PI
# ifdef M_PI
#  define       PI                      M_PI
# else
#  define       PI                      3.14159265358979323846
# endif
#endif


#ifdef M_LN2
# define        LOG2                    M_LN2
#else
# define        LOG2                    0.69314718055994530942
#endif

#ifdef M_LN10
# define        LOG10                   M_LN10
#else
# define        LOG10                   2.30258509299404568402
#endif


#ifdef M_SQRT2
# define        SQRT2                   M_SQRT2
#else
# define        SQRT2                   1.41421356237309504880
#endif


#define         HAN_SIZE                512
#define         CRC16_POLYNOMIAL        0x8005
#define MAX_BITS 4095

/* "bit_stream.h" Definitions */
#define         BUFFER_SIZE     LAME_MAXMP3BUFFER 

#define         Min(A, B)       ((A) < (B) ? (A) : (B))
#define         Max(A, B)       ((A) > (B) ? (A) : (B))

/* log/log10 approximations */
#ifdef TAKEHIRO_IEEE754_HACK
#define USE_FAST_LOG
#endif

#ifdef USE_FAST_LOG
#define         FAST_LOG10(x)       (fast_log2(x)*(LOG2/LOG10))
#define         FAST_LOG(x)         (fast_log2(x)*LOG2)
#else
#define         FAST_LOG10(x)       log10(x)
#define         FAST_LOG(x)         log(x)
#endif


/***********************************************************************
*
*  Global Type Definitions
*
***********************************************************************/



/* "bit_stream.h" Type Definitions */

typedef struct  bit_stream_struc {
    unsigned char *buf;         /* bit stream buffer */
    int         buf_size;       /* size of buffer (in number of bytes) */
    int         totbit;         /* bit counter of bit stream */
    int         buf_byte_idx;   /* pointer to top byte in buffer */
    int         buf_bit_idx;    /* pointer to top bit of top byte in buffer */
    
    /* format of file in rd mode (BINARY/ASCII) */
} Bit_stream_struc;

#include "l3side.h"


/* variables used for --nspsytune */
typedef struct {
  /* variables for nspsytune */
  int   use; /* indicates the use of nspsytune */
  int   safejoint; /* safe joint stereo mode */
  FLOAT last_en_subshort[4][9];
  FLOAT last_attack_intensity[4][9];
  FLOAT	last_thm[4][SBMAX_s][3];
  int   last_attacks[4][3];
  FLOAT pe_l[4],pe_s[4];
  FLOAT pefirbuf[19];
  FLOAT bass,alto,treble,sfb21;

  /* variables for nspsytune2 */
  int use2; /* indicates the use of nspsytune2 */
  FILE *pass1fp;
} nsPsy_t;

/* variables used for --alt-preset */
typedef struct {

  // indicates the use of alt-preset
  int     use;

  // short block tuning
  int     attackthre;
  int     attackthre_s;

  // adjustment to joint stereo
  FLOAT8  ms_maskadjust;

  // adjustments to quantization selection
  int     quantcomp_current;          // current quant_compare mode we are using
  FLOAT8  quantcomp_adjust_rh_tot;    // adjustments for tot_noise with vbr-old
  FLOAT8  quantcomp_adjust_rh_max;    // adjustments for max_noise with vbr-old
  FLOAT8  quantcomp_adjust_mtrh;      // adjustments for calc_scalefac "c" with vbr-mtrh
  int     quantcomp_type_s;           // quantization comparison to switch to on non-normal blocks
  int     quantcomp_alt_type;          // third quantization comparison to use for special cases
                                       // such as high athadjust values, or long blocks, etc

  // tunings reliant upon athadjust
  FLOAT8  athadjust_max_val;           // maximum value of athadjust before limit is applied
  FLOAT8  athadjust_switch_level;      // level of athadjust at which to apply tunings at
                                       // x <= 0 == never switch, x >= 1 == always switch
  FLOAT8  athadjust_msfix;             // msfix adjustment based on athadjust
  int     athadjust_safe_noiseshaping; // if 0, noise shaping 2 will not be used no matter what
                                       // the noise shaping type would normally be set to
  FLOAT8  athadjust_safe_noiseshaping_thre; // value which max_pow_alt must be greater than
                                            // for noise shaping 2 to be used "safely"                                                     
  FLOAT8  athadjust_safe_athaasensitivity; // used for second determination if it is safe to switch
	                                      // to noise shaping 2
} presetTune_t;

typedef struct 
{
    int sum;    // what we have seen so far
    int seen;   // how many frames we have seen in this chunk
    int want;   // how many frames we want to collect into one chunk
    int pos;    // actual position in our bag
    int size;   // size of our bag
    int *bag;   // pointer to our bag
} VBR_seek_info_t;


/**
 *  ATH related stuff, if something new ATH related has to be added,
 *  please plugg it here into the ATH_t struct
 */
typedef struct
{
    int     use_adjust;     /* method for the auto adjustment */
    FLOAT8  adjust;         /* lowering based on peak volume, 1 = no lowering */
    FLOAT8  adjust_limit;   /* limit for dynamic ATH adjust */
    FLOAT8  decay;          /* determined to lower x dB each second */
    FLOAT8  floor;          /* lowest ATH value */
    FLOAT8  l[SBMAX_l];     /* ATH for sfbs in long blocks */
    FLOAT8  s[SBMAX_s];     /* ATH for sfbs in short blocks */
    FLOAT8  cb[CBANDS];     /* ATH for convolution bands */
    FLOAT   eql_w[BLKSIZE/2];	/* equal loudness weights (based on ATH) */
} ATH_t;

/**
 *  VBR related stuff
 */
typedef struct
{
    FLOAT8  scratch[192];
    FLOAT8  mask_adjust;    // the dbQ stuff
    int     quality;
    int     smooth;         // 0=no, 1=peaks, 2=+-4
} VBR_t;

/**
 *  PSY Model related stuff
 */
typedef struct
{
    int     tonalityPatch;      // temporaly needed by VBR
    FLOAT   cwlimit;
    FLOAT8  prvTonRed[CBANDS];
} PSY_t; 


/* Guest structure, only temporarly here */

typedef enum {
    coding_MPEG_Layer_1 = 1,
    coding_MPEG_Layer_2 = 2,
    coding_MPEG_Layer_3 = 3,
    coding_MPEG_AAC     = 4,
    coding_Ogg_Vorbis   = 5,
    coding_MPEG_plus    = 6
} coding_t;

#define MAX_CHANNELS  2

typedef struct {
    unsigned long  Class_ID;        /* Class ID to recognize a resample_t
                                       object */
    FLOAT8   sample_freq_in;  /* Input sample frequency in Hz */
    FLOAT8   sample_freq_out; /* requested Output sample frequency in Hz */
    FLOAT8   lowpass_freq;    /* lowpass frequency, this is the -6 dB
                                       point */
    int            scale_in;        /* the resampling is actually done by
                                       scale_out: */
    int            scale_out;       /* frequency is
                                         samplefreq_in * scale_out / scal */
    int            taps;            /* number of taps for every FIR resample
                                       filter */

    sample_t**     fir;             /* the FIR resample filters:
                                         fir [scale_out] [taps */
    void*          firfree;         /* start address of the alloced memory for
                                       fir, */
    unsigned char* src_step;
    sample_t*      in_old       [MAX_CHANNELS];
    //    uint64_t       sample_count [MAX_CHANNELS];
    unsigned       fir_stepper  [MAX_CHANNELS];
    int            inp_stepper  [MAX_CHANNELS];

} resample_t;


struct lame_internal_flags {

  /********************************************************************
   * internal variables NOT set by calling program, and should not be *
   * modified by the calling program                                  *
   ********************************************************************/
  
  /*  
   * Some remarks to the Class_ID field:
   * The Class ID is an Identifier for a pointer to this struct.
   * It is very unlikely that a pointer to lame_global_flags has the same 32 bits 
   * in it's structure (large and other special properties, for instance prime).
   *
   * To test that the structure is right and initialized, use:
   *     if ( gfc -> Class_ID == LAME_ID ) ...
   * Other remark:
   *     If you set a flag to 0 for uninit data and 1 for init data, the right test
   *     should be "if (flag == 1)" and NOT "if (flag)". Unintended modification
   *     of this element will be otherwise misinterpreted as an init.
   */
  
  #define  LAME_ID   0xFFF88E3B
  unsigned long Class_ID;

  struct {
    void (*msgf)  (const char *format, va_list ap);
    void (*debugf)(const char *format, va_list ap);
    void (*errorf)(const char *format, va_list ap);
  } report;
  
  int lame_encode_frame_init;     
  int iteration_init_init;
  int fill_buffer_resample_init;
  int psymodel_init;

  int padding;                  /* padding for the current frame? */
  int mode_gr;                    /* granules per frame */
  int          channels_in;	/* number of channels in the input data stream (PCM or decoded PCM) */
  int          channels_out;  /* number of channels in the output data stream (not used for decoding) */
  resample_t*  resample_in;   /* context for coding (PCM=>MP3) resampling */
  resample_t*  resample_out;	/* context for decoding (MP3=>PCM) resampling */
  FLOAT8  samplefreq_in;
  FLOAT8  samplefreq_out;
  uint16_t nMusicCRC;

#ifndef  MFSIZE
# define MFSIZE  ( 3*1152 + ENCDELAY - MDCTDELAY )
#endif
#ifdef  KLEMM_44
  sample_t*    mfbuf [MAX_CHANNELS];
#else
  sample_t     mfbuf [2] [MFSIZE];
#endif
  size_t       frame_size;    /* size of one frame in samples per channel */
  lame_global_flags* gfp;     /* needed as long as the frame encoding functions must access gfp (all needed information can be added to gfc) */
  coding_t     coding;        /* MPEG Layer 1/2/3, Ogg Vorbis, MPEG AAC, ... */
  unsigned long frame_count;  /* Number of frames coded, 2^32 > 3 years */
  int          mf_samples_to_encode;
  int          mf_size;
  FLOAT8       ampl;	  /* amplification at the end of the current chunk (1. = 0 dB) */
  FLOAT8       last_ampl;	  /* amplification at the end of the last chunk    (1. = 0 dB) */
  int VBR_min_bitrate;            /* min bitrate index */
  int VBR_max_bitrate;            /* max bitrate index */
  FLOAT resample_ratio;           /* input_samp_rate/output_samp_rate */
  int bitrate_index;
  int samplerate_index;
  int mode_ext;


  /* lowpass and highpass filter control */
  FLOAT8 lowpass1,lowpass2;        /* normalized frequency bounds of passband */
  FLOAT8 highpass1,highpass2;      /* normalized frequency bounds of passband */
                                  
  /* polyphase filter (filter_type=0)  */
  int lowpass_band;          /* zero bands >= lowpass_band in the polyphase filterbank */
  int highpass_band;         /* zero bands <= highpass_band */
  int lowpass_start_band;    /* amplify bands between start */
  int lowpass_end_band;      /* and end for lowpass */
  int highpass_start_band;   /* amplify bands between start */
  int highpass_end_band;     /* and end for highpass */


  int filter_type;          /* 0=polyphase filter, 1= FIR filter 2=MDCT filter(bad)*/
  int quantization;         /* 0 = ISO formual,  1=best amplitude */
  int noise_shaping;        /* 0 = none 
                               1 = ISO AAC model
                               2 = allow scalefac_select=1  
                             */

  int noise_shaping_amp;    /*  0 = ISO model: amplify all distorted bands
                                1 = amplify within 50% of max (on db scale)
                                2 = amplify only most distorted band
			     */
  int substep_shaping;      /* 0 = no substep
			       1 = use substep shaping at last step(VBR only)
			           (not implemented yet)
			       2 = use substep inside loop
			    */

  int psymodel;             /* 1 = gpsycho. 0 = none */
  int noise_shaping_stop;   /* 0 = stop at over=0, all scalefacs amplified or
                                   a scalefac has reached max value
                               1 = stop when all scalefacs amplified or        
                                   a scalefac has reached max value
                               2 = stop when all scalefacs amplified 
			    */

  int use_best_huffman;     /* 0 = no.  1=outside loop  2=inside loop(slow) */




  /* variables used by lame.c */
  Bit_stream_struc   bs;
  III_side_info_t l3_side;
  FLOAT8 ms_ratio[2];
  /* used for padding */
  int frac_SpF;
  int slot_lag;


  /* optional ID3 tags, used in id3tag.c  */
  struct id3tag_spec tag_spec;


  /* variables used by quantize.c */
  int OldValue[2];
  int CurrentStep;

  FLOAT8 masking_lower;
  char bv_scf[576];
  
  int sfb21_extra; /* will be set in lame_init_params */
  
  int is_mpeg1; /* 1 for MPEG-1, 0 for MPEG-2(.5) */

#ifndef KLEMM_44
  /* variables used by util.c */
  /* BPC = maximum number of filter convolution windows to precompute */
#define BPC 320
  sample_t *inbuf_old [2];
  sample_t *blackfilt [2*BPC+1];
  FLOAT8 itime[2];
#endif
  int sideinfo_len;

  /* variables for newmdct.c */
  FLOAT8 sb_sample[2][2][18][SBLIMIT];
  FLOAT8 amp_lowpass[32];
  FLOAT8 amp_highpass[32];

  /* variables for bitstream.c */
  /* mpeg1: buffer=511 bytes  smallest frame: 96-38(sideinfo)=58
   * max number of frames in reservoir:  8 
   * mpeg2: buffer=255 bytes.  smallest frame: 24-23bytes=1
   * with VBR, if you are encoding all silence, it is possible to
   * have 8kbs/24khz frames with 1byte of data each, which means we need
   * to buffer up to 255 headers! */
  /* also, max_header_buf has to be a power of two */
#define MAX_HEADER_BUF 256
#define MAX_HEADER_LEN 40 /* max size of header is 38 */
  struct {
    int write_timing;
    int ptr;
    char buf[MAX_HEADER_LEN];
  } header[MAX_HEADER_BUF];

  int h_ptr;
  int w_ptr;
  int ancillary_flag;
  

  /* variables for reservoir.c */
  int ResvSize; /* in bits */
  int ResvMax;  /* in bits */

  
  scalefac_struct scalefac_band;

  /* DATA FROM PSYMODEL.C */
/* The static variables "r", "phi_sav", "new", "old" and "oldest" have    */
/* to be remembered for the unpredictability measure.  For "r" and        */
/* "phi_sav", the first index from the left is the channel select and     */
/* the second index is the "age" of the data.                             */
  FLOAT8	minval[CBANDS];
  FLOAT8	nb_1[4][CBANDS], nb_2[4][CBANDS];
  FLOAT8	nb_s1[4][CBANDS], nb_s2[4][CBANDS];
  FLOAT8  *s3_ss;
  FLOAT8  *s3_ll;
  FLOAT8 decay;

  III_psy_xmin thm[4];
  III_psy_xmin en[4];
  
  /* unpredictability calculation
   */
  int cw_upper_index;
  int cw_lower_index;
  FLOAT ax_sav[4][2][HBLKSIZE];
  FLOAT bx_sav[4][2][HBLKSIZE];
  FLOAT rx_sav[4][2][HBLKSIZE];
  FLOAT cw[HBLKSIZE];

  /* fft and energy calculation    */
  FLOAT wsamp_L[2][BLKSIZE];
  FLOAT energy[HBLKSIZE];
  FLOAT wsamp_S[2][3][BLKSIZE_s];
  FLOAT energy_s[3][HBLKSIZE_s];
  FLOAT tot_ener[4];


  /* loudness calculation (for adaptive threshold of hearing) */
  FLOAT loudness_sq[2][2];  /* loudness^2 approx. per granule and channel */
  FLOAT loudness_sq_save[2];/* account for granule delay of L3psycho_anal */

  /* factor for tuning the (sample power) point below which adaptive threshold
     of hearing adjustment occurs 
   */
  FLOAT athaa_sensitivity_p;

 
  /* fft.c    */
  FLOAT window[BLKSIZE], window_s[BLKSIZE_s/2];
  
  
  /* Scale Factor Bands    */
  III_scalefac_t pseudohalf;
  FLOAT8	w1_l[SBMAX_l], w2_l[SBMAX_l];
  FLOAT8	w1_s[SBMAX_s], w2_s[SBMAX_s];
  FLOAT8 mld_l[SBMAX_l],mld_s[SBMAX_s];
  int	bu_l[SBMAX_l],bo_l[SBMAX_l] ;
  int	bu_s[SBMAX_s],bo_s[SBMAX_s] ;
  int	npart_l,npart_s;
  int	npart_l_orig,npart_s_orig;
  
  int	s3ind[CBANDS][2];
  int	s3ind_s[CBANDS][2];
  FLOAT8 SNR_s[CBANDS];

  int	numlines_s[CBANDS];
  int	numlines_l[CBANDS];
  
  
  /* frame analyzer    */
  FLOAT energy_save[4][HBLKSIZE];
  FLOAT8 pe_save[4];
  FLOAT8 ers_save[4];
  
  /* simple statistics */
  int   bitrate_stereoMode_Hist [16] [4+1];
  int	bitrate_blockType_Hist  [16] [4+1+1];/*norm/start/short/stop/mixed(short)/sum*/

  /* ratios  */
  FLOAT8 pe[4];
  FLOAT8 ms_ratio_s_old,ms_ratio_l_old;
  FLOAT8 ms_ener_ratio_old;

  /* block type */
  int	blocktype_old[2];

  /* used by the frame analyzer */
  plotting_data *pinfo;

  /* CPU features */
  struct {
    unsigned int  i387      : 1; /* FPU is a normal Intel CPU */
    unsigned int  MMX       : 1; /* Pentium MMX, Pentium II...IV, K6, K6-2,
                                    K6-III, Athlon */
    unsigned int  AMD_3DNow : 1; /* K6-2, K6-III, Athlon      */
    unsigned int  SIMD      : 1; /* Pentium III, Pentium 4    */
    unsigned int  SIMD2     : 1; /* Pentium 4, K8             */
  } CPU_features;
   
  /* functions to replace with CPU feature optimized versions in takehiro.c */
  int (*choose_table)(const int *ix, const int *end, int *s);
  
  void (*fft_fht)(FLOAT *, int);

  nsPsy_t nsPsy;  /* variables used for --nspsytune */
  presetTune_t presetTune;  /* variables used for --alt-preset */
  
  unsigned crcvalue;
  
  VBR_seek_info_t VBR_seek_table; // used for Xing VBR header
  
  ATH_t *ATH;   // all ATH related stuff
  VBR_t *VBR;
  PSY_t *PSY;

  int nogap_total;
  int nogap_current;  
};



 

/***********************************************************************
*
*  Global Function Prototype Declarations
*
***********************************************************************/
void                  freegfc(lame_internal_flags * const gfc);
extern int            BitrateIndex(int, int,int);
extern int            FindNearestBitrate(int,int,int);
extern int            map2MP3Frequency(int freq);
extern int            SmpFrqIndex(int, int* const);
extern int            nearestBitrateFullIndex(const int brate);
extern FLOAT8         ATHformula(FLOAT8 f,lame_global_flags *gfp);
extern FLOAT8         freq2bark(FLOAT8 freq);
extern FLOAT8         freq2cbw(FLOAT8 freq);
void disable_FPE(void);

/* log/log10 approximations */
extern void init_log_table(void);
extern ieee754_float32_t fast_log2(ieee754_float32_t x);


extern void 
getframebits( const lame_global_flags *gfp, int *bitsPerFrame, int *mean_bits);

void fill_buffer(lame_global_flags *gfp,
		 sample_t *mfbuf[2],
		 sample_t *in_buffer[2],
		 int nsamples, int *n_in, int *n_out);

int  fill_buffer_resample (
        lame_global_flags *gfp,
        sample_t*  outbuf,
        int        desired_len,
        sample_t*  inbuf,
        int        len,
        int*       num_used,
        int        channels );


extern int  has_i387  ( void );
extern int  has_MMX   ( void );
extern int  has_3DNow ( void );
extern int  has_SIMD  ( void );
extern int  has_SIMD2 ( void );

extern void updateStats (lame_internal_flags * const gfc);



/***********************************************************************
*
*  Macros about Message Printing and Exit
*
***********************************************************************/
extern void lame_errorf(const lame_internal_flags *gfc, const char *, ...);
extern void lame_debugf(const lame_internal_flags *gfc, const char *, ...);
extern void lame_msgf  (const lame_internal_flags *gfc, const char *, ...);
#define DEBUGF  lame_debugf
#define ERRORF	lame_errorf
#define MSGF	lame_msgf


int select_kth_int(int b[], int N, int k);


#ifdef __cplusplus
}
#endif

#endif /* LAME_UTIL_H */
