/****************************************************************************

                     (C) Copyright Fraunhofer IIS (2004)
                               All Rights Reserved

    Please be advised that this software and/or program delivery is
    Confidential Information of Fraunhofer and subject to and covered by the

    Fraunhofer IIS Software Evaluation Agreement
    between Google Inc. and  Fraunhofer
    effective and in full force since March 1, 2012.

    You may use this software and/or program only under the terms and
    conditions described in the above mentioned Fraunhofer IIS Software
    Evaluation Agreement. Any other and/or further use requires a separate agreement.


   This software and/or program is protected by copyright law and international
   treaties. Any reproduction or distribution of this software and/or program,
   or any portion of it, may result in severe civil and criminal penalties, and
   will be prosecuted to the maximum extent possible under law.

 $Id$

*******************************************************************************/
/*!
  \file
  \brief Memory layout
  $Revision: 36847 $

  This module declares all static and dynamic memory spaces
*/
#include "sbr_ram.h"

#include "sbr.h"
#include "genericStds.h"

C_ALLOC_MEM (Ram_SbrDynamic_RAM, FIXP_DBL, ((SBR_ENC_DYN_RAM_SIZE)/sizeof(FIXP_DBL)))

/*!
  \name StaticSbrData

  Static memory areas, must not be overwritten in other sections of the encoder
*/
/* @{ */

/*! static sbr encoder instance for one encoder (2 channels)
  all major static and dynamic memory areas are located
  in module sbr_ram and sbr rom
*/
C_ALLOC_MEM (Ram_SbrEncoder, SBR_ENCODER, 1)
C_ALLOC_MEM2(Ram_SbrChannel, SBR_CHANNEL, 1, (6))
C_ALLOC_MEM2(Ram_SbrElement, SBR_ELEMENT, 1, (6))

/*! Filter states for QMF-analysis. <br>
  Dimension: #MAXNRSBRCHANNELS * #SBR_QMF_FILTER_LENGTH
*/
C_AALLOC_MEM2_L (Ram_Sbr_QmfStatesAnalysis, FIXP_QAS, QMF_FILTER_LENGTH, (6), SECT_DATA_L1)


/*! Matrix holding the quota values for all estimates, all channels
  Dimension #MAXNRSBRCHANNELS * +#SBR_QMF_CHANNELS* #MAX_NO_OF_ESTIMATES
*/
C_ALLOC_MEM2_L (Ram_Sbr_quotaMatrix, FIXP_DBL, (MAX_NO_OF_ESTIMATES*QMF_CHANNELS), (6), SECT_DATA_L1)

/*! Matrix holding the sign values for all estimates, all channels
  Dimension #MAXNRSBRCHANNELS * +#SBR_QMF_CHANNELS* #MAX_NO_OF_ESTIMATES
*/
C_ALLOC_MEM2 (Ram_Sbr_signMatrix, INT, (MAX_NO_OF_ESTIMATES*QMF_CHANNELS), (6))

/*! Frequency band table (low res) <br>
  Dimension #MAX_FREQ_COEFFS/2+1
*/
C_ALLOC_MEM2 (Ram_Sbr_freqBandTableLO, UCHAR, (MAX_FREQ_COEFFS/2+1), (6))

/*! Frequency band table (high res) <br>
  Dimension #MAX_FREQ_COEFFS +1
*/
C_ALLOC_MEM2 (Ram_Sbr_freqBandTableHI, UCHAR, (MAX_FREQ_COEFFS+1), (6))

/*! vk matser table <br>
  Dimension #MAX_FREQ_COEFFS +1
*/
C_ALLOC_MEM2 (Ram_Sbr_v_k_master, UCHAR, (MAX_FREQ_COEFFS+1), (6))


/*
  Missing harmonics detection
*/

/*! sbr_detectionVectors <br>
  Dimension #MAX_NUM_CHANNELS*#MAX_NO_OF_ESTIMATES*#MAX_FREQ_COEFFS]
*/
C_ALLOC_MEM2 (Ram_Sbr_detectionVectors, UCHAR, (MAX_NO_OF_ESTIMATES*MAX_FREQ_COEFFS), (6))

/*! sbr_prevCompVec[ <br>
  Dimension #MAX_NUM_CHANNELS*#MAX_FREQ_COEFFS]
*/
C_ALLOC_MEM2 (Ram_Sbr_prevEnvelopeCompensation, UCHAR, MAX_FREQ_COEFFS, (6))
/*! sbr_guideScfb[ <br>
  Dimension #MAX_NUM_CHANNELS*#MAX_FREQ_COEFFS]
*/
C_ALLOC_MEM2 (Ram_Sbr_guideScfb, UCHAR, MAX_FREQ_COEFFS, (6))

/*! sbr_guideVectorDetected <br>
  Dimension #MAX_NUM_CHANNELS*#MAX_NO_OF_ESTIMATES*#MAX_FREQ_COEFFS]
*/
C_ALLOC_MEM2 (Ram_Sbr_guideVectorDetected, UCHAR, (MAX_NO_OF_ESTIMATES*MAX_FREQ_COEFFS), (6))
C_ALLOC_MEM2 (Ram_Sbr_guideVectorDiff, FIXP_DBL, (MAX_NO_OF_ESTIMATES*MAX_FREQ_COEFFS), (6))
C_ALLOC_MEM2 (Ram_Sbr_guideVectorOrig, FIXP_DBL, (MAX_NO_OF_ESTIMATES*MAX_FREQ_COEFFS), (6))

/*
  Static Parametric Stereo memory
*/
C_AALLOC_MEM_L(Ram_PsQmfStatesSynthesis, FIXP_DBL, QMF_FILTER_LENGTH/2, SECT_DATA_L1)

C_ALLOC_MEM   (Ram_PsEnvRBuffer, FIXP_DBL, QMF_MAX_TIME_SLOTS*QMF_CHANNELS/2)
C_ALLOC_MEM   (Ram_PsEnvIBuffer, FIXP_DBL, QMF_MAX_TIME_SLOTS*QMF_CHANNELS/2)
C_ALLOC_MEM2  (Ram_PsChData,    PS_CHANNEL_DATA, 1, MAX_PS_CHANNELS)
C_ALLOC_MEM   (Ram_PsEncConf,   PSENC_CONFIG, 1)
C_ALLOC_MEM_L (Ram_PsEncode,    PS_ENCODE, 1, SECT_DATA_L1)
C_ALLOC_MEM   (Ram_PsData,      PS_DATA, 1)
C_ALLOC_MEM   (Ram_ParamStereo, PARAMETRIC_STEREO, 1)
C_ALLOC_MEM2  (Ram_PsOut,       PS_OUT, 1, 2)


/* QMF data
 */
C_ALLOC_MEM   (Ram_PsQmfNewSamples,      FIXP_DBL, QMF_CHANNELS)

C_ALLOC_MEM2  (Ram_PsQmfData, PS_QMF_DATA, 1, MAX_PS_CHANNELS)

/*  HYBRID data
 */
C_AALLOC_MEM (Ram_PsHybFFT, FIXP_DBL, 16)

C_ALLOC_MEM2(Ram_HybData,     PS_HYBRID_DATA, 1, MAX_PS_CHANNELS)
C_ALLOC_MEM2(Ram_PsHybrid,    PS_HYBRID,      1, MAX_PS_CHANNELS)
C_ALLOC_MEM (Ram_PsHybConfig, PS_HYBRID_CONFIG, 1)

C_ALLOC_MEM2(Ram_PsRhyb, FIXP_QMF, ((HYBRID_FRAMESIZE+HYBRID_WRITEOFFSET)*HYBRID_NUM_BANDS), MAX_PS_CHANNELS)
C_ALLOC_MEM2(Ram_PsIhyb, FIXP_QMF, ((HYBRID_FRAMESIZE+HYBRID_WRITEOFFSET)*HYBRID_NUM_BANDS), MAX_PS_CHANNELS)

C_ALLOC_MEM (Ram_PsHybWkReal, FIXP_QMF, (HYBRID_FRAMESIZE + QMF_BUFFER_MOVE))
C_ALLOC_MEM (Ram_PsHybWkImag, FIXP_QMF, (HYBRID_FRAMESIZE + QMF_BUFFER_MOVE))

C_ALLOC_MEM2(Ram_PsMtmpReal, FIXP_QMF, (MAX_HYBRID_RES), HYBRID_FRAMESIZE)
C_ALLOC_MEM2(Ram_PsMtmpImag, FIXP_QMF, (MAX_HYBRID_RES), HYBRID_FRAMESIZE)


/* @} */


/*!
  \name DynamicSbrData

  Dynamic memory areas, might be reused in other algorithm sections,
  e.g. the core encoder.
*/
/* @{ */

  /*! Energy buffer for envelope extraction <br>
    Dimension #MAXNRSBRCHANNELS * +#SBR_QMF_SLOTS *  #SBR_QMF_CHANNELS
  */
  C_ALLOC_MEM2 (Ram_Sbr_envYBuffer, FIXP_DBL, (QMF_MAX_TIME_SLOTS/2 * QMF_CHANNELS), (6))

  FIXP_DBL* GetRam_Sbr_envYBuffer (int n, UCHAR* dynamic_RAM) {
    FDK_ASSERT(dynamic_RAM!=0);
    return ((FIXP_DBL*) (dynamic_RAM + OFFSET_NRG + (n*Y_2_BUF_BYTE) ));
  }

  /*
   * QMF data
   */
  /* The SBR encoder uses a single channel overlapping buffer set (always n=0), but PS does not. */
  FIXP_DBL* GetRam_Sbr_envRBuffer (int n, UCHAR* dynamic_RAM) {
    FDK_ASSERT(dynamic_RAM!=0);
    return ((FIXP_DBL*) (dynamic_RAM + OFFSET_QMF + (n*ENV_R_BUFF_BYTE*2) ));
  }
  FIXP_DBL* GetRam_Sbr_envIBuffer (int n, UCHAR* dynamic_RAM) {
    FDK_ASSERT(dynamic_RAM!=0);
    //return ((FIXP_DBL*) (dynamic_RAM + OFFSET_QMF + (MAX_NUM_CHANNELS*ENV_R_BUFF_BYTE) + n*ENV_I_BUFF_BYTE));
    return ((FIXP_DBL*) (dynamic_RAM + OFFSET_QMF + (ENV_R_BUFF_BYTE) + (n*ENV_I_BUFF_BYTE*2)));
  }

  /* reuse QMF buffer in PS module. We Require space to hold 2 channels. */
  C_ALLOC_MEM2(Ram_PsRqmf, FIXP_QMF, ((PSENC_QMF_BUFFER_LENGTH-QMF_MAX_TIME_SLOTS)*(QMF_CHANNELS)), MAX_PS_CHANNELS)
  C_ALLOC_MEM2(Ram_PsIqmf, FIXP_QMF, ((PSENC_QMF_BUFFER_LENGTH-QMF_MAX_TIME_SLOTS)*(QMF_CHANNELS)), MAX_PS_CHANNELS)

  FIXP_QMF* FDKsbrEnc_SliceRam_PsRqmf(FIXP_DBL* rQmfData, UCHAR* dynamic_RAM, int ch, int i, int qmfSlots)
  {
       FDK_ASSERT(dynamic_RAM!=0);
       if (i<HYBRID_READ_OFFSET)
         return rQmfData + (i*(QMF_CHANNELS));
       else if ((i<(HYBRID_READ_OFFSET+qmfSlots)))
         return  GetRam_Sbr_envRBuffer(ch, dynamic_RAM) + ( (i-(HYBRID_READ_OFFSET))*(QMF_CHANNELS) );
       else
         return rQmfData + ((i-qmfSlots)*(QMF_CHANNELS));
  }

  FIXP_QMF* FDKsbrEnc_SliceRam_PsIqmf(FIXP_DBL* iQmfData, UCHAR* dynamic_RAM, int ch, int i, int qmfSlots)
  {
       FDK_ASSERT(dynamic_RAM!=0);
       if (i<HYBRID_READ_OFFSET)
         return iQmfData + (i*(QMF_CHANNELS));
       else if ((i<(HYBRID_READ_OFFSET+qmfSlots)))
         return  GetRam_Sbr_envIBuffer(ch, dynamic_RAM) + ( (i-(HYBRID_READ_OFFSET))*(QMF_CHANNELS) );
       else
         return iQmfData + ((i-qmfSlots)*(QMF_CHANNELS));
  }




/* @} */




