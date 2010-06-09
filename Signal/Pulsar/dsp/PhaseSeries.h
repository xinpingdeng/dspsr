//-*-C++-*-
/***************************************************************************
 *
 *   Copyright (C) 2002 by Willem van Straten
 *   Licensed under the Academic Free License version 2.1
 *
 ***************************************************************************/

/* $Source: /cvsroot/dspsr/dspsr/Signal/Pulsar/dsp/PhaseSeries.h,v $
   $Revision: 1.38 $
   $Date: 2010/06/09 04:34:50 $
   $Author: straten $ */

#ifndef __PhaseSeries_h
#define __PhaseSeries_h

#include "dsp/TimeSeries.h"

namespace Pulsar {
  class Predictor;
  class Parameters;
}

namespace dsp {

  class Extensions;
  
  //! Data as a function of pulse phase
  class PhaseSeries : public TimeSeries {

    friend class Fold;

  public:

    //! Default constructor
    PhaseSeries ();

    //! Copy constructor
    PhaseSeries (const PhaseSeries&);

    //! Assigment operator
    PhaseSeries& operator = (const PhaseSeries&);

    //! Destructor
    ~PhaseSeries ();

    //! Clone operator
    PhaseSeries* clone() const;

    //! Allocate the space required to store nsamples time samples.
    virtual void resize (int64_t nsamples);

    //! Add the given PhaseSeries to this
    void combine (const PhaseSeries*);

    //! Set the reference phase (phase of bin zero)
    void set_reference_phase (double phase) { reference_phase = phase; }
    //! Get the reference phase (phase of bin zero)
    double get_reference_phase () const { return reference_phase; }

    //! Set the period at which to fold data (in seconds)
    /*! The Pulsar::Predictor and ephemeris are set to null values upon
      setting the folding period */
    void set_folding_period (double _folding_period);
    //! Get the period at which to fold data (in seconds)
    double get_folding_period () const;

    //! Set the phase predictor with which the data were folded 
    void set_folding_predictor (const Pulsar::Predictor*);
    //! Get the phase predictor with which the data were folded
    const Pulsar::Predictor* get_folding_predictor () const;
    //! Return true if the folding predictor attribute is set
    bool has_folding_predictor () const;
     
    //! Set the pulsar ephemeris used to fold.
    void set_pulsar_ephemeris (const Pulsar::Parameters*);
    //! Returns the pulsar ephemeris stored
    const Pulsar::Parameters* get_pulsar_ephemeris () const;
    //! Return true if the pulsar ephemeris attribute is set
    bool has_pulsar_ephemeris () const;

    //! Get the number of seconds integrated
    double get_integration_length () const { return integration_length; }

    //! Increment the integration length
    void increment_integration_length (double seconds)
    { integration_length += seconds; }

    //! Get the end time
    MJD get_end_time () const { return end_time; }
    //! Set the end time
    void set_end_time (const MJD& mjd) { end_time = mjd; }

    //! Get the number of phase bins
    unsigned get_nbin () const { return unsigned(get_ndat()); }

    //! Get the hit for the given bin
    unsigned get_hit (unsigned ibin) const { return hits[ibin]; }

    //! Get the hits array
    unsigned* get_hits () { return &hits[0]; }
    const unsigned* get_hits () const { return &hits[0]; }

    //! Set the hits in all bins
    void set_hits (unsigned value);

    //! Get the mid-time of the integration 
    /*! \param phased if true, round to the nearest reference phase */
    MJD get_mid_time (bool phased = true) const;

    //! Reset all phase bin totals to zero
    void zero ();

    //! Over-ride Observation::combinable_rate
    bool combinable_rate (double) const { return true; }

    //! Set the expected number of time samples
    void set_ndat_expected (uint64_t);

    //! Return the expected number of time samples
    uint64_t get_ndat_expected () const;

    //! Return the total number of time samples
    uint64_t get_ndat_total () const;

    //! Return the number of time samples folded into the profiles
    uint64_t get_ndat_folded () const;

    //! Set the Extensions to be communicated to the Archiver class
    void set_extensions (Extensions*);
    //! Get the Extensions to be communicated to the Archiver class
    const Extensions* get_extensions () const;
    Extensions* get_extensions ();

    //! Return true if Extensions have been set
    bool has_extensions () const;

    //! Copy the configuration of another PhaseSeries instance (hits array)
    virtual void copy_configuration (const Observation* copy);

  protected:

    //! Period at which CAL data is folded
    double folding_period;

    //! Phase polynomial(s) with which PSR is folded
    Reference::To<const Pulsar::Predictor> folding_predictor;

    //! The ephemeris (if any) that was used to generate the Pulsar::Predictor
    Reference::To<const Pulsar::Parameters> pulsar_ephemeris;

    //! The Extensions to be communicated to the Archiver class
    Reference::To<Extensions> extensions;

    //! Reference phase (phase of bin zero)
    double reference_phase;

    //! Number of time samples integrated into each phase bin
    std::vector<unsigned> hits;

    //! Total number of time samples passed to folding routine
    uint64_t ndat_total;

    //! Total number of time samples expected to be passed to folding routine
    uint64_t ndat_expected;

    //! The number of seconds integrated into the profile(s)
    double integration_length;

    //! The MJD of the last-integrated time sample's tail edge
    MJD end_time;

    //! Return true when Observation can be integrated (and prepare for it)
    bool mixable (const Observation& obs, unsigned nbin,
		  int64_t istart=0, int64_t fold_ndat=0);

  private:

    //! Ensure that the old operator += interface is not used
    void operator += (const PhaseSeries&);

    void init ();
    void copy_attributes (const PhaseSeries*);

  };

}

#endif
