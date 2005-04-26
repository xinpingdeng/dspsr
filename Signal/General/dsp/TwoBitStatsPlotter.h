//-*-C++-*-

/* $Source: /cvsroot/dspsr/dspsr/Signal/General/dsp/Attic/TwoBitStatsPlotter.h,v $
   $Revision: 1.8 $
   $Date: 2005/04/26 13:06:16 $
   $Author: wvanstra $ */

#ifndef __TwoBitStatsPlotter_h
#define __TwoBitStatsPlotter_h

#include "dsp/BitStatsPlotter.h"

namespace dsp {
  
  class TwoBitCorrection;

  //! Plots the histograms maintained by TwoBitCorrection
  class TwoBitStatsPlotter : public BitStatsPlotter {

  public:

    //! Null constructor
    TwoBitStatsPlotter ();

    //! Virtual destructor
    virtual ~TwoBitStatsPlotter ();

    //! Set the data to be plotted
    void set_data (const HistUnpacker* stats);

    //! The label on the x-axis
    std::string get_xlabel () const;

    //! The label on the y-axis
    std::string get_ylabel () const;

     //! Get the colour used to plot the theoretical distribution
    int get_theory_colour () { return theory_colour; };

    //! Get a measure of the difference between the histogram and the theory
    double get_chi_squared (int idig);

    //! Plot vertical bars to indicate the cut-off thresholds
    bool show_cutoff_sigma;

    //! Plot vertical bars to indicate the cut-off thresholds
    bool plot_only_range;

  protected:

    //! Theoretical, optimal histogram
    std::vector<float> theory;

    //! Maxmimum value of theory
    float theory_max;

    //! Set true when the theoretical, optimal histogram is calculated
    bool theory_calculated;

    //! Colour used when plotting theoretical
    int theory_colour;

    //! Data to be plotted
    Reference::To<const TwoBitCorrection> twobit;

    void calculate_theory ();
    void set_theory_colour ();
    void check_colours ();
    bool special (unsigned imin, unsigned imax, float& ymax);

  };
  
}

#endif
