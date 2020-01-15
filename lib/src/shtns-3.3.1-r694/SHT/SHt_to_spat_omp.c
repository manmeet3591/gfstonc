// This file was automatically generated by 'make' from file 'omp_SH_to_spat.gen.c'.
// To modify it, please consider modifying omp_SH_to_spat.gen.c
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


	static
  #ifndef SHT_GRAD
	void GEN3(_sy2o,NWAY,SUFFIX)(shtns_cfg shtns, cplx *Slm, cplx *Tlm, v2d *BtF, v2d *BpF, const long int llim, const int imlim) {
  #else
	void GEN3(_sy1ot,NWAY,SUFFIX)(shtns_cfg shtns, cplx *Tlm, v2d *BtF, v2d *BpF, const long int llim, const int imlim) {
  #endif

	#if !defined( _GCC_VEC_ ) && (NWAY & 1)
	#error "NWAY must be even when compiled without explicit vectorization."
	#endif

  #ifndef SHT_AXISYM
   #ifndef SHTNS_ISHIOKA
   #else
   #endif
	#define vr(l) vall( ((double*) VWl)[4*(l)]   )
	#define vi(l) vall( ((double*) VWl)[4*(l)+1] )
	#define wr(l) vall( ((double*) VWl)[4*(l)+2] )
	#define wi(l) vall( ((double*) VWl)[4*(l)+3] )
	unsigned im;
  #endif
	unsigned m0, mstep;
	long int nk,k,l,m;
	double *alm, *al;
	double *ct, *st;
	int robert_form;
	v2d VWl[llim*2+4];
  #ifdef SHTNS_ISHIOKA
	v2d QQl[llim+2];
  #endif

	ct = shtns->ct;		st = shtns->st;
	nk = NLAT_2;
	#if _GCC_VEC_
		nk = ((unsigned)(nk+VSIZE2-1)) / VSIZE2;
	#endif
	robert_form = shtns->robert_form;

	#ifndef _OPENMP
		m0 = 0;		mstep = 1;
	#else
		m0 = omp_get_thread_num();
		mstep = omp_get_num_threads();
		if (m0 == 0)
	#endif
	{	//	im=0;
		double* const Tl0 = (double*) VWl + llim+2;
		#ifdef SHT_GRAD
		  #ifndef SHT_AXISYM
				k=0; do { BtF[k]=vdup(0.0); } while(++k<NLAT_2);
		  #else
			if (BtF != NULL) { int k=0; do { BtF[k]=vdup(0.0); } while(++k<NLAT_2); }
		  #endif
		#endif
 		l=1;
		alm = shtns->alm;
		do {		// for m=0, compress the complex Q,S,T to double
			Tl0[l-1] = creal( Tlm[l] );	//	Tl[l] = (double) Tlm[l+1];
			++l;
		} while(l<=llim);
		k=0;
		do {
			l=0;	al = alm;
			rnd cost[NWAY], y0[NWAY], y1[NWAY];
			rnd sint[NWAY], dy0[NWAY], dy1[NWAY];
			rnd pe[NWAY], po[NWAY];
			for (int j=0; j<NWAY; ++j) {
				cost[j] = vread(ct, j+k);
				sint[j] = -vread(st, j+k);
				y0[j] = vall(al[0]);
				dy0[j] = vall(0.0);
				po[j] = dy0[j];
			}
			if (robert_form) {
				for (int j=0; j<NWAY; ++j) sint[j] *= -sint[j];
			}
			for (int j=0; j<NWAY; ++j) {
				y1[j]  = vall(al[0]*al[1]) * cost[j];
				dy1[j] = vall(al[0]*al[1]) * sint[j];
			}
			for (int j=0; j<NWAY; ++j) {
				pe[j] = -dy1[j] * vall(Tl0[0]);
			}
			al+=2;	l+=2;
			while(l<llim) {
				for (int j=0; j<NWAY; ++j) {
					dy0[j] = vall(al[1])*(cost[j]*dy1[j] + y1[j]*sint[j]) + vall(al[0])*dy0[j];
					y0[j]  = vall(al[1])*(cost[j]*y1[j]) + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					po[j] -= dy0[j] * vall(Tl0[l-1]);
				}
				for (int j=0; j<NWAY; ++j) {
					dy1[j] = vall(al[3])*(cost[j]*dy0[j] + y0[j]*sint[j]) + vall(al[2])*dy1[j];
					y1[j]  = vall(al[3])*(cost[j]*y0[j]) + vall(al[2])*y1[j];
				}
				for (int j=0; j<NWAY; ++j) {
					pe[j] -= dy1[j] * vall(Tl0[l]);
				}
				al+=4;	l+=2;
			}
			if (l==llim) {
				for (int j=0; j<NWAY; ++j) {
					dy0[j] = vall(al[1])*(cost[j]*dy1[j] + y1[j]*sint[j]) + vall(al[0])*dy0[j];
					y0[j]  = vall(al[1])*cost[j]*y1[j] + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					po[j] -= dy0[j] * vall(Tl0[l-1]);
				}
			}
		#ifndef SHTNS4MAGIC
			for (int j=0; j<NWAY; ++j) {
				S2D_STORE(BpF, j+k, pe[j], po[j])
			}
		#else
			for (int j=0; j<NWAY; ++j) {
				if ((k+j)>=nk) break;
				S2D_STORE_4MAGIC((double*)BpF, j+k, pe[j], po[j]);
			}
		#endif
			k+=NWAY;
		} while (k < nk);
		m0=mstep;
	}

  #ifndef SHT_AXISYM
		BtF += m0*NLAT_2;	BpF += m0*NLAT_2;
	for (im=m0; im<imlim; im+=mstep) {
		m = im*MRES;
		l = (im*(2*(LMAX+1)-(m+MRES)))>>1;		//l = LiM(shtns, 0,im);
		#ifndef SHTNS_ISHIOKA
		alm = shtns->alm + 2*(l+m);		// shtns->alm + im*(2*(LMAX+1) -m+MRES);
		#else
		alm = shtns->clm + (l+m);		// shtns->clm + im*(2*(LMAX+1) -m+MRES)/2;
		#endif

  #ifndef SHT_GRAD
		SH_vect_to_2scal(shtns->mx_stdt + 2*l, llim, m, &Slm[l], &Tlm[l], (cplx*) VWl);
  #else
		SHtor_to_2scal(shtns->mx_stdt + 2*l, llim, m, &Tlm[l], (cplx*) VWl);
  #endif

	#ifndef SHTNS_ISHIOKA
	#else
		// pre-processing for recurrence relation of Ishioka
		const double* restrict xlm = shtns->xlm + 3*im*(2*(LMAX+4) -m+MRES)/4;
		SH2_to_ishioka(xlm, VWl+2*m, llim-m+1);
	#endif

		k=0;	l=shtns->tm[im];
		l>>=1;		// stay on a 16 byte boundary
		while (k<l) {	// polar optimization
		  #ifndef SHTNS4MAGIC
			BtF[k] = vdup(0.0);				BtF[(NPHI-2*im)*NLAT_2 + k] = vdup(0.0);
			BtF[NLAT_2-l+k] = vdup(0.0);	BtF[(NPHI+1-2*im)*NLAT_2 -l+k] = vdup(0.0);
			BpF[k] = vdup(0.0);				BpF[(NPHI-2*im)*NLAT_2 + k] = vdup(0.0);
			BpF[NLAT_2-l+k] = vdup(0.0);	BpF[(NPHI+1-2*im)*NLAT_2 -l+k] = vdup(0.0);
		  #else
			BtF[2*k] = vdup(0.0);			BtF[(NPHI-2*im)*NLAT_2 + 2*k] = vdup(0.0);
			BtF[2*k+1] = vdup(0.0);			BtF[(NPHI-2*im)*NLAT_2 +2*k+1] = vdup(0.0);
			BpF[2*k] = vdup(0.0);			BpF[(NPHI-2*im)*NLAT_2 + 2*k] = vdup(0.0);
			BpF[2*k+1] = vdup(0.0);			BpF[(NPHI-2*im)*NLAT_2 +2*k+1] = vdup(0.0);
		  #endif
			++k;
		}
		#if _GCC_VEC_
		k = ((unsigned) k) / (VSIZE2/2);
		#else
		k *= 2;
		#endif
		do {
			rnd cost[NWAY], y0[NWAY], y1[NWAY];
			rnd ter[NWAY], tei[NWAY], tor[NWAY], toi[NWAY];
			rnd per[NWAY], pei[NWAY], por[NWAY], poi[NWAY];
			for (int j=0; j<NWAY; ++j) {
				cost[j] = vread(st, k+j);
				y0[j] = vall(1.0);
			}
			l=m;
			if (robert_form == 0) l=m-1;
			long int ny = 0;
		if ((int)llim <= SHT_L_RESCALE_FLY) {
			do {		// sin(theta)^m
				if (l&1) for (int j=0; j<NWAY; ++j) y0[j] *= cost[j];
				for (int j=0; j<NWAY; ++j) cost[j] *= cost[j];
			} while(l >>= 1);
		} else {
			long int nsint = 0;
			do {		// sin(theta)^m		(use rescaling to avoid underflow)
				if (l&1) {
					for (int j=NWAY-1; j>=0; --j) y0[j] *= cost[j];
					ny += nsint;
					if (vlo(y0[NWAY-1]) < (SHT_ACCURACY+1.0/SHT_SCALE_FACTOR)) {
						ny--;
						for (int j=NWAY-1; j>=0; --j) y0[j] *= vall(SHT_SCALE_FACTOR);
					}
				}
				for (int j=NWAY-1; j>=0; --j) cost[j] *= cost[j];
				nsint += nsint;
				if (vlo(cost[NWAY-1]) < 1.0/SHT_SCALE_FACTOR) {
					nsint--;
					for (int j=NWAY-1; j>=0; --j) cost[j] *= vall(SHT_SCALE_FACTOR);
				}
			} while(l >>= 1);
		}
			al = alm;
			for (int j=0; j<NWAY; ++j) {
				cost[j] = vread(ct, j+k);
				#ifndef SHTNS_ISHIOKA
				y0[j] *= vall(al[0]);
				#else
				cost[j] *= cost[j];		// cos(theta)^2
				#endif
			}
			for (int j=0; j<NWAY; ++j) {
				#ifndef SHTNS_ISHIOKA
				y1[j]  = (vall(al[1])*y0[j]) *cost[j];		//	y1[j] = vall(al[1])*cost[j]*y0[j];
				#else
				y1[j] = (vall(al[1])*cost[j] + vall(al[0]))*y0[j];
				#endif
				por[j] = vall(0.0);		tei[j] = vall(0.0);
				tor[j] = vall(0.0);		pei[j] = vall(0.0);
				poi[j] = vall(0.0);		ter[j] = vall(0.0);
				toi[j] = vall(0.0);		per[j] = vall(0.0);
			}
			l=m;		al+=2;
			while ((ny<0) && (l<llim)) {		// ylm treated as zero and ignored if ny < 0
				#ifndef SHTNS_ISHIOKA
				for (int j=0; j<NWAY; ++j) {
					y0[j] = (vall(al[1])*cost[j])*y1[j] + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {
					y1[j] = (vall(al[3])*cost[j])*y0[j] + vall(al[2])*y1[j];
				}
				l+=2;	al+=4;
				#else
				rnd a[NWAY];
				for (int j=0; j<NWAY; ++j)	a[j] = vall(al[1])*cost[j] + vall(al[0]);
				l+=2;	al+=2;
				for (int j=0; j<NWAY; ++j) {
					rnd tmp = y1[j];
					y1[j] = a[j]*y1[j] + y0[j];
					y0[j] = tmp;
				}
				#endif
				if (fabs(vlo(y0[NWAY-1])) > SHT_ACCURACY*SHT_SCALE_FACTOR + 1.0) {		// rescale when value is significant
					++ny;
					for (int j=0; j<NWAY; ++j) {
						y0[j] *= vall(1.0/SHT_SCALE_FACTOR);		y1[j] *= vall(1.0/SHT_SCALE_FACTOR);
					}
				}
			}
		  if (ny == 0) {
		#ifndef SHTNS_ISHIOKA
			while (l<llim) {	// compute even and odd parts
				for (int j=0; j<NWAY; ++j) {	ter[j] += y0[j]  * vr(l);		tei[j] += y0[j] * vi(l);	}
				for (int j=0; j<NWAY; ++j) {	per[j] += y0[j]  * wr(l);		pei[j] += y0[j] * wi(l);	}
				for (int j=0; j<NWAY; ++j) {
					y0[j] = vall(al[1])*(cost[j]*y1[j]) + vall(al[0])*y0[j];
				}
				for (int j=0; j<NWAY; ++j) {	tor[j] += y1[j]  * vr(l+1);		toi[j] += y1[j] * vi(l+1);	}
				for (int j=0; j<NWAY; ++j) {	por[j] += y1[j]  * wr(l+1);		poi[j] += y1[j] * wi(l+1);	}
				for (int j=0; j<NWAY; ++j) {
					y1[j] = vall(al[3])*(cost[j]*y0[j]) + vall(al[2])*y1[j];
				}
				l+=2;	al+=4;
			}
				for (int j=0; j<NWAY; ++j) {	ter[j] += y0[j]  * vr(l);		tei[j] += y0[j] * vi(l);	}
				for (int j=0; j<NWAY; ++j) {	per[j] += y0[j]  * wr(l);		pei[j] += y0[j] * wi(l);	}
			if (l==llim) {
				for (int j=0; j<NWAY; ++j) {	tor[j] += y1[j]  * vr(l+1);		toi[j] += y1[j] * vi(l+1);	}
				for (int j=0; j<NWAY; ++j) {	por[j] += y1[j]  * wr(l+1);		poi[j] += y1[j] * wi(l+1);	}
			}
		#else
			while (l<llim) {	// compute even and odd parts
				for (int j=0; j<NWAY; ++j) {	ter[j] += y0[j]  * vr(l);		tei[j] += y0[j] * vi(l);	}
				for (int j=0; j<NWAY; ++j) {	per[j] += y0[j]  * wr(l);		pei[j] += y0[j] * wi(l);	}
				for (int j=0; j<NWAY; ++j) {	tor[j] += y0[j]  * vr(l+1);		toi[j] += y0[j] * vi(l+1);	}
				for (int j=0; j<NWAY; ++j) {	por[j] += y0[j]  * wr(l+1);		poi[j] += y0[j] * wi(l+1);	}
				rnd aa[NWAY];
				for (int j=0; j<NWAY; ++j) aa[j] = vall(al[1])*cost[j] + vall(al[0]);
				l+=2;	al+=2;
				for (int j=0; j<NWAY; ++j) {
					rnd tmp = y1[j];
					y1[j] = aa[j]*y1[j] + y0[j];
					y0[j] = tmp;
				}
			}
				for (int j=0; j<NWAY; ++j) {	ter[j] += y0[j]  * vr(l);		tei[j] += y0[j] * vi(l);	}
				for (int j=0; j<NWAY; ++j) {	per[j] += y0[j]  * wr(l);		pei[j] += y0[j] * wi(l);	}
			if (l==llim) {
				for (int j=0; j<NWAY; ++j) {	tor[j] += y0[j]  * vr(l+1);		toi[j] += y0[j] * vi(l+1);	}
				for (int j=0; j<NWAY; ++j) {	por[j] += y0[j]  * wr(l+1);		poi[j] += y0[j] * wi(l+1);	}
			}
			// correct the odd part:
			for (int j=0; j<NWAY; ++j) cost[j] = vread(ct, k+j);
			for (int j=0; j<NWAY; ++j) {  tor[j] *= cost[j];	toi[j] *= cost[j]; }
			for (int j=0; j<NWAY; ++j) {  por[j] *= cost[j];	poi[j] *= cost[j]; }
		#endif
		  }
		#ifndef SHTNS4MAGIC
		  #ifdef _GCC_VEC_
			for (int j=0; j<NWAY; ++j) {
				S2D_CSTORE(BtF, k+j, ter[j], tor[j], tei[j], toi[j])
				S2D_CSTORE(BpF, k+j, per[j], por[j], pei[j], poi[j])
			}
		  #else
			for (int j=0; j<NWAY/2; ++j) {		// NWAY is even when _GCC_VEC_ is not defined
				S2D_CSTOREX(BtF, k/2+j, 2*j, ter, tor, tei, toi)
				S2D_CSTOREX(BpF, k/2+j, 2*j, per, por, pei, poi)
			}
		  #endif
		#else
			for (int j=0; j<NWAY; ++j) {
				if ((k+j)>=nk) break;
				S2D_CSTORE_4MAGIC((double*)BtF, (double*) (BtF + (NPHI-2*im)*NLAT_2), k+j, ter[j], tor[j], tei[j], toi[j]);
				S2D_CSTORE_4MAGIC((double*)BpF, (double*) (BpF + (NPHI-2*im)*NLAT_2), k+j, per[j], por[j], pei[j], poi[j]);
			}
		#endif
			k+=NWAY;
		} while (k < nk);
		BtF += mstep*NLAT_2;	BpF += mstep*NLAT_2;
	}

	while(im <= NPHI-imlim) {	// padding for high m's
		k=0;
		do {
			BtF[k] = vdup(0.0);		BpF[k] = vdup(0.0);
		} while (++k < NLAT_2);
		BtF += mstep*NLAT_2;	BpF += mstep*NLAT_2;
	  im+=mstep;
	}
  #endif
}

	#undef tr
	#undef ti

  #ifndef SHT_GRAD
	static void GEN3(SHsphtor_to_spat_omp,NWAY,SUFFIX)(shtns_cfg shtns, cplx *Slm, cplx *Tlm, double *Vt, double *Vp, long int llim) {
  #else
	static void GEN3(SHtor_to_spat_omp,NWAY,SUFFIX)(shtns_cfg shtns, cplx *Tlm, double *Vt, double *Vp, long int llim) {
  #endif

	unsigned imlim = 0;
	v2d* BtF = (v2d*) Vt;	v2d* BpF = (v2d*) Vp;

  #ifndef SHT_AXISYM
	imlim = MTR;
	#ifdef SHT_VAR_LTR
		if (imlim*MRES > (unsigned) llim) imlim = ((unsigned) llim)/MRES;		// 32bit mul and div should be faster
	#endif
	if (shtns->fftc_mode > 0) {		// alloc memory for the FFT
		unsigned long nv = shtns->nspat;
		BtF = (v2d*) VMALLOC( 2*nv * sizeof(double) );
		BpF = BtF + nv/2;
	}
  #endif
	imlim += 1;
  
  #pragma omp parallel num_threads(shtns->nthreads)
  {
	#ifndef SHT_GRAD
		GEN3(_sy2o,NWAY,SUFFIX)(shtns, Slm, Tlm, BtF, BpF, llim, imlim);
	#else
		GEN3(_sy1ot,NWAY,SUFFIX)(shtns, Tlm, BtF, BpF, llim, imlim);
	#endif


  #ifndef SHT_AXISYM
	#ifndef HAVE_LIBFFTW3_OMP
	  #pragma omp barrier
		if (shtns->fftc_mode >= 0) {
		if (shtns->fftc_mode != 1) {
			#pragma omp single nowait
			fftw_execute_dft(shtns->ifftc, (cplx *) BtF, (cplx *) Vt);
			#pragma omp single nowait
			fftw_execute_dft(shtns->ifftc, (cplx *) BpF, (cplx *) Vp);
		} else {		// split dft
			#pragma omp single nowait
			fftw_execute_split_dft(shtns->ifftc,((double*)BtF)+1, ((double*)BtF), Vt+NPHI, Vt);
			#pragma omp single nowait
			fftw_execute_split_dft(shtns->ifftc,((double*)BpF)+1, ((double*)BpF), Vp+NPHI, Vp);
		}
		}
	#endif
  #endif

  }

  #ifndef SHT_AXISYM
    // NPHI > 1 as SHT_AXISYM is not defined.
  	if (shtns->fftc_mode >= 0) {
		if (shtns->fftc_mode != 1) {
		  #ifdef HAVE_LIBFFTW3_OMP
			fftw_execute_dft(shtns->ifftc, (cplx *) BtF, (cplx *) Vt);
			fftw_execute_dft(shtns->ifftc, (cplx *) BpF, (cplx *) Vp);
		  #endif
		} else {		// split dft
		  #ifdef HAVE_LIBFFTW3_OMP
			fftw_execute_split_dft(shtns->ifftc,((double*)BtF)+1, ((double*)BtF), Vt+NPHI, Vt);
			fftw_execute_split_dft(shtns->ifftc,((double*)BpF)+1, ((double*)BpF), Vp+NPHI, Vp);
		  #endif
			VFREE(BtF);		// this frees also BpF.
		}
	}
  #endif

  }
