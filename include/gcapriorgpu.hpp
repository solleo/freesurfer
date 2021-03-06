/**
 * @file  gcaprior.hpp
 * @brief Class to hold a volume of GCA priors in linear memory on the GPU
 *
 */
/*
 * Original Authors: Richard Edgar
 * CVS Revision Info:
 *    $Author: rge21 $
 *    $Date: 2011/01/25 15:55:30 $
 *    $Revision: 1.1 $
 *
 * Copyright (C) 2002-2010,
 * The General Hospital Corporation (Boston, MA).
 * All rights reserved.
 *
 * Distribution, usage and copying of this software is covered under the
 * terms found in the License Agreement file named 'COPYING' found in the
 * FreeSurfer source code root directory, and duplicated here:
 * https://surfer.nmr.mgh.harvard.edu/fswiki/FreeSurferOpenSourceLicense
 *
 * General inquiries: freesurfer@nmr.mgh.harvard.edu
 *
 */

#ifndef GCA_PRIOR_GPU_HPP
#define GCA_PRIOR_GPU_HPP

#include <iostream>

#include "gca.h"
#include "gcalinearprior.hpp"



namespace GPU {
  namespace Classes {


    // =============================================================

    //! Management class for GCA prior data on the GPU
    class GCApriorGPU {
    public:
      //! Default constructor
      GCApriorGPU( void ) :  xDim(0), yDim(0), zDim(0),
			     n4D(0),
			     d_offsets4D(NULL),
			     d_maxLabels(NULL),
			     d_labels(NULL),
			     d_priors(NULL),
			     d_totTraining(NULL) {};

      //! Destructor
      ~GCApriorGPU( void ) {
	this->Release();
      }


      // -------------------------
      // Memory management
      
      //! Allocate all arrays
      void Allocate( const long long nxDim,
		     const long long nyDim,
		     const long long nzDim,
		     const size_t num4D );

      //! Release all arrays
      void Release( void );

      // --------------------------
      // Transfers

      //! Send data to the GPU
      void Send( const Freesurfer::GCAlinearPrior& src );


      // ============================
    private:
      // Dimensions
      long long xDim;
      long long yDim;
      long long zDim;
      size_t n4D;

      //! Stores offsets of the (variable length) 4th dimension
      size_t *d_offsets4D;

      //! Stores max_labels of GCA_PRIOR
      short *d_maxLabels;
      //! Stores labels of GCA_PRIOR (4D)
      unsigned short *d_labels;
      //! Stores priors of GCA_PRIOR (4D)
      float *d_priors;
      //! Stores total_training of GCA_PRIOR
      int *d_totTraining;


      // -------------------------

      //! Inhibit copy constructor
      GCApriorGPU( GCApriorGPU& src ) :  xDim(0), yDim(0), zDim(0),
					 n4D(0),
					 d_offsets4D(NULL),
					 d_maxLabels(NULL),
					 d_labels(NULL),
					 d_priors(NULL),
					 d_totTraining(NULL) {
	std::cerr << __FUNCTION__
		  << ": Please don't copy"
		  << std::endl;
	abort();
      }

      //! Inhibit assignment
      GCApriorGPU& operator=( const GCApriorGPU& src ) {
	std::cerr << __FUNCTION__
		  << ": Please don't copy"
		  << std::endl;
	abort();
      }
    };

  }
}















#endif
