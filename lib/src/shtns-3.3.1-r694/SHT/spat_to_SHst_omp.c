// This file was automatically generated by 'make' from file 'omp_spat_to_SH.gen.c'.
// To modify it, please consider modifying omp_spat_to_SH.gen.c
/*
 * Copyright (c) 2010-2019 Centre National de la Recherche Scientifique.
 * written by Nathanael Schaeffer (CNRS, ISTerre, Grenoble, France).
 * 
 * nathanael.schaeffer@univ-grenoble-alpes.fr
 * 
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software. You can use,
 * modify and/or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 * 
 */

//////////////////////////////////////////////////

	void GEN3(_an2,NWAY,SUFFIX)(shtns_cfg shtns, double *BtF, double *BpF, cplx *Slm, cplx *Tlm, const long int llim, const int imlim);
	void GEN3(_an2_hi,NWAY,SUFFIX)(shtns_cfg shtns, double *BtF, double *BpF, cplx *Slm, cplx *Tlm, const long int llim, const int imlim);



	static
	void GEN3(spat_to_SHsphtor_omp,NWAY,SUFFIX)(shtns_cfg shtns, double *Vt, double *Vp, cplx *Slm, cplx *Tlm, long int llim) {

	double *BtF, *BpF;	// contains the Fourier transformed data
	unsigned imlim=0;

	BtF = Vt;	BpF = Vp;
  #ifndef SHT_AXISYM
	imlim = MTR;
	#ifdef SHT_VAR_LTR
		if (imlim*MRES > (unsigned) llim) imlim = ((unsigned) llim)/MRES;		// 32bit mul and div should be faster
	#endif
	if (shtns->fftc_mode >= 0) {
		if (shtns->fftc_mode > 0) {		// alloc memory for out-of-place FFT
			unsigned long nv = shtns->nspat;
			BtF = (double*) VMALLOC( 2*nv * sizeof(double) );
			BpF = BtF + nv;
		}
	    if (shtns->fftc_mode != 1) {	// regular FFT
			fftw_execute_dft(shtns->fftc,(cplx*)Vt, (cplx*)BtF);
			fftw_execute_dft(shtns->fftc,(cplx*)Vp, (cplx*)BpF);
		} else {	// split FFT
			fftw_execute_split_dft(shtns->fftc, Vt+NPHI, Vt, BtF+1, BtF);
			fftw_execute_split_dft(shtns->fftc, Vp+NPHI, Vp, BpF+1, BpF);
	    }
	}
  #endif
	imlim += 1;

	if (llim < SHT_L_RESCALE_FLY) {
		#pragma omp parallel num_threads(shtns->nthreads)
		{
			GEN3(_an2,NWAY,SUFFIX)(shtns, BtF, BpF, Slm, Tlm, llim, imlim);
		}
	} else {
		#pragma omp parallel num_threads(shtns->nthreads)
		{
			GEN3(_an2_hi,NWAY,SUFFIX)(shtns, BtF, BpF, Slm, Tlm, llim, imlim);
		}
	}

  #ifndef SHT_AXISYM
  	if (shtns->fftc_mode > 0) {		// free memory
	    VFREE(BtF);	// this frees also BpF.
	}
  #endif

  }

	#undef LSPAN