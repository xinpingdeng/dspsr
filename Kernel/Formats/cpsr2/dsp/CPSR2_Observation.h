//-*-C++-*-

/* $Source: /cvsroot/dspsr/dspsr/Kernel/Formats/cpsr2/dsp/CPSR2_Observation.h,v $
   $Revision: 1.5 $
   $Date: 2004/10/18 07:36:12 $
   $Author: sord $ */

#ifndef __CPSR2_Observation_h
#define __CPSR2_Observation_h

#include "dsp/Observation.h"

namespace dsp {
 
  //! General means of constructing Observation attributes from CPSR2 data
  /*! This class parses the ASCII header block used for CPSR2 data and
    initializes all of the attributes of the Observation base class.
    The header block may come from a CPSR2 data file, or from the
    shared memory (data block) of the machines in the CPSR2
    cluster. */
  class CPSR2_Observation : public Observation {

  public:

    //! Construct from a CPSR2 ASCII header block
    CPSR2_Observation (const char* header=0);

    //! Number of bytes offset from the beginning of acquisition
    uint64 offset_bytes;

    //! The digitizer thresholds for a SimpleFB file
    virtual void set_thresh();
  };
  
}

#endif
