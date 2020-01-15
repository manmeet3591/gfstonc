/* File: _read_sfcflx_nemsiomodule.c
 * This file is auto-generated with f2py (version:2).
 * f2py is a Fortran to Python Interface Generator (FPIG), Second Edition,
 * written by Pearu Peterson <pearu@cens.ioc.ee>.
 * Generation date: Wed Jan 15 01:04:08 2020
 * Do not edit this file directly unless you know what you are doing!!!
 */

#ifdef __cplusplus
extern "C" {
#endif

/*********************** See f2py2e/cfuncs.py: includes ***********************/
#include "Python.h"
#include <stdarg.h>
#include "fortranobject.h"
#include <string.h>
#include <math.h>

/**************** See f2py2e/rules.py: mod_rules['modulebody'] ****************/
static PyObject *_read_sfcflx_nemsio_error;
static PyObject *_read_sfcflx_nemsio_module;

/*********************** See f2py2e/cfuncs.py: typedefs ***********************/
typedef char * string;

/****************** See f2py2e/cfuncs.py: typedefs_generated ******************/
/*need_typedefs_generated*/

/********************** See f2py2e/cfuncs.py: cppmacros **********************/
\
#define FAILNULL(p) do {                                            \
    if ((p) == NULL) {                                              \
        PyErr_SetString(PyExc_MemoryError, "NULL pointer found");   \
        goto capi_fail;                                             \
    }                                                               \
} while (0)

#define STRINGMALLOC(str,len)\
    if ((str = (string)malloc(sizeof(char)*(len+1))) == NULL) {\
        PyErr_SetString(PyExc_MemoryError, "out of memory");\
        goto capi_fail;\
    } else {\
        (str)[len] = '\0';\
    }

#if defined(PREPEND_FORTRAN)
#if defined(NO_APPEND_FORTRAN)
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) _##F
#else
#define F_FUNC(f,F) _##f
#endif
#else
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) _##F##_
#else
#define F_FUNC(f,F) _##f##_
#endif
#endif
#else
#if defined(NO_APPEND_FORTRAN)
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) F
#else
#define F_FUNC(f,F) f
#endif
#else
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) F##_
#else
#define F_FUNC(f,F) f##_
#endif
#endif
#endif
#if defined(UNDERSCORE_G77)
#define F_FUNC_US(f,F) F_FUNC(f##_,F##_)
#else
#define F_FUNC_US(f,F) F_FUNC(f,F)
#endif

#define rank(var) var ## _Rank
#define shape(var,dim) var ## _Dims[dim]
#define old_rank(var) (PyArray_NDIM((PyArrayObject *)(capi_ ## var ## _tmp)))
#define old_shape(var,dim) PyArray_DIM(((PyArrayObject *)(capi_ ## var ## _tmp)),dim)
#define fshape(var,dim) shape(var,rank(var)-dim-1)
#define len(var) shape(var,0)
#define flen(var) fshape(var,0)
#define old_size(var) PyArray_SIZE((PyArrayObject *)(capi_ ## var ## _tmp))
/* #define index(i) capi_i ## i */
#define slen(var) capi_ ## var ## _len
#define size(var, ...) f2py_size((PyArrayObject *)(capi_ ## var ## _tmp), ## __VA_ARGS__, -1)

#define STRINGFREE(str) do {if (!(str == NULL)) free(str);} while (0)

#ifdef DEBUGCFUNCS
#define CFUNCSMESS(mess) fprintf(stderr,"debug-capi:"mess);
#define CFUNCSMESSPY(mess,obj) CFUNCSMESS(mess) \
    PyObject_Print((PyObject *)obj,stderr,Py_PRINT_RAW);\
    fprintf(stderr,"\n");
#else
#define CFUNCSMESS(mess)
#define CFUNCSMESSPY(mess,obj)
#endif

#ifndef max
#define max(a,b) ((a > b) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) ((a < b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a > b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) ((a < b) ? (a) : (b))
#endif

#define CHECKSCALAR(check,tcheck,name,show,var)\
    if (!(check)) {\
        char errstring[256];\
        sprintf(errstring, "%s: "show, "("tcheck") failed for "name, var);\
        PyErr_SetString(_read_sfcflx_nemsio_error,errstring);\
        /*goto capi_fail;*/\
    } else 
#define STRINGCOPYN(to,from,buf_size)                           \
    do {                                                        \
        int _m = (buf_size);                                    \
        char *_to = (to);                                       \
        char *_from = (from);                                   \
        FAILNULL(_to); FAILNULL(_from);                         \
        (void)strncpy(_to, _from, sizeof(char)*_m);             \
        _to[_m-1] = '\0';                                      \
        /* Padding with spaces instead of nulls */              \
        for (_m -= 2; _m >= 0 && _to[_m] == '\0'; _m--) {      \
            _to[_m] = ' ';                                      \
        }                                                       \
    } while (0)


/************************ See f2py2e/cfuncs.py: cfuncs ************************/
static int f2py_size(PyArrayObject* var, ...)
{
  npy_int sz = 0;
  npy_int dim;
  npy_int rank;
  va_list argp;
  va_start(argp, var);
  dim = va_arg(argp, npy_int);
  if (dim==-1)
    {
      sz = PyArray_SIZE(var);
    }
  else
    {
      rank = PyArray_NDIM(var);
      if (dim>=1 && dim<=rank)
        sz = PyArray_DIM(var, dim-1);
      else
        fprintf(stderr, "f2py_size: 2nd argument value=%d fails to satisfy 1<=value<=%d. Result will be 0.\n", dim, rank);
    }
  va_end(argp);
  return sz;
}

static int string_from_pyobj(string *str,int *len,const string inistr,PyObject *obj,const char *errmess) {
    PyArrayObject *arr = NULL;
    PyObject *tmp = NULL;
#ifdef DEBUGCFUNCS
fprintf(stderr,"string_from_pyobj(str='%s',len=%d,inistr='%s',obj=%p)\n",(char*)str,*len,(char *)inistr,obj);
#endif
    if (obj == Py_None) {
        if (*len == -1)
            *len = strlen(inistr); /* Will this cause problems? */
        STRINGMALLOC(*str,*len);
        STRINGCOPYN(*str,inistr,*len+1);
        return 1;
    }
    if (PyArray_Check(obj)) {
        if ((arr = (PyArrayObject *)obj) == NULL)
            goto capi_fail;
        if (!ISCONTIGUOUS(arr)) {
            PyErr_SetString(PyExc_ValueError,"array object is non-contiguous.");
            goto capi_fail;
        }
        if (*len == -1)
            *len = (PyArray_ITEMSIZE(arr))*PyArray_SIZE(arr);
        STRINGMALLOC(*str,*len);
        STRINGCOPYN(*str,PyArray_DATA(arr),*len+1);
        return 1;
    }
    if (PyString_Check(obj)) {
        tmp = obj;
        Py_INCREF(tmp);
    }
#if PY_VERSION_HEX >= 0x03000000
    else if (PyUnicode_Check(obj)) {
        tmp = PyUnicode_AsASCIIString(obj);
    }
    else {
        PyObject *tmp2;
        tmp2 = PyObject_Str(obj);
        if (tmp2) {
            tmp = PyUnicode_AsASCIIString(tmp2);
            Py_DECREF(tmp2);
        }
        else {
            tmp = NULL;
        }
    }
#else
    else {
        tmp = PyObject_Str(obj);
    }
#endif
    if (tmp == NULL) goto capi_fail;
    if (*len == -1)
        *len = PyString_GET_SIZE(tmp);
    STRINGMALLOC(*str,*len);
    STRINGCOPYN(*str,PyString_AS_STRING(tmp),*len+1);
    Py_DECREF(tmp);
    return 1;
capi_fail:
    Py_XDECREF(tmp);
    {
        PyObject* err = PyErr_Occurred();
        if (err==NULL) err = _read_sfcflx_nemsio_error;
        PyErr_SetString(err,errmess);
    }
    return 0;
}

static int int_from_pyobj(int* v,PyObject *obj,const char *errmess) {
    PyObject* tmp = NULL;
    if (PyInt_Check(obj)) {
        *v = (int)PyInt_AS_LONG(obj);
        return 1;
    }
    tmp = PyNumber_Int(obj);
    if (tmp) {
        *v = PyInt_AS_LONG(tmp);
        Py_DECREF(tmp);
        return 1;
    }
    if (PyComplex_Check(obj))
        tmp = PyObject_GetAttrString(obj,"real");
    else if (PyString_Check(obj) || PyUnicode_Check(obj))
        /*pass*/;
    else if (PySequence_Check(obj))
        tmp = PySequence_GetItem(obj,0);
    if (tmp) {
        PyErr_Clear();
        if (int_from_pyobj(v,tmp,errmess)) {Py_DECREF(tmp); return 1;}
        Py_DECREF(tmp);
    }
    {
        PyObject* err = PyErr_Occurred();
        if (err==NULL) err = _read_sfcflx_nemsio_error;
        PyErr_SetString(err,errmess);
    }
    return 0;
}


/********************* See f2py2e/cfuncs.py: userincludes *********************/
/*need_userincludes*/

/********************* See f2py2e/capi_rules.py: usercode *********************/


/* See f2py2e/rules.py */
extern void F_FUNC_US(read_nemsio_header,READ_NEMSIO_HEADER)(string,int*,int*,int*,int*,int*,size_t);
extern void F_FUNC_US(read_nemsio_latlons,READ_NEMSIO_LATLONS)(string,int*,int*,float*,float*,size_t);
extern void F_FUNC_US(read_nemsio_varnames,READ_NEMSIO_VARNAMES)(string,int*,int*,int*,int*,size_t);
extern void F_FUNC_US(read_nemsio_2dgriddata,READ_NEMSIO_2DGRIDDATA)(string,int*,int*,int*,int*,int*,int*,float*,size_t);
/*eof externroutines*/

/******************** See f2py2e/capi_rules.py: usercode1 ********************/


/******************* See f2py2e/cb_rules.py: buildcallback *******************/
/*need_callbacks*/

/*********************** See f2py2e/rules.py: buildapi ***********************/

/***************************** read_nemsio_header *****************************/
static char doc_f2py_rout__read_sfcflx_nemsio_read_nemsio_header[] = "\
nlons,nlats,nrecs,idate,nfhour = read_nemsio_header(filename)\n\nWrapper for ``read_nemsio_header``.\
\n\nParameters\n----------\n"
"filename : input string(len=500)\n"
"\nReturns\n-------\n"
"nlons : int\n"
"nlats : int\n"
"nrecs : int\n"
"idate : rank-1 array('i') with bounds (7)\n"
"nfhour : int";
/* extern void F_FUNC_US(read_nemsio_header,READ_NEMSIO_HEADER)(string,int*,int*,int*,int*,int*,size_t); */
static PyObject *f2py_rout__read_sfcflx_nemsio_read_nemsio_header(const PyObject *capi_self,
                           PyObject *capi_args,
                           PyObject *capi_keywds,
                           void (*f2py_func)(string,int*,int*,int*,int*,int*,size_t)) {
  PyObject * volatile capi_buildvalue = NULL;
  volatile int f2py_success = 1;
/*decl*/

  string filename = NULL;
  int slen(filename);
  PyObject *filename_capi = Py_None;
  int nlons = 0;
  int nlats = 0;
  int nrecs = 0;
  int *idate = NULL;
  npy_intp idate_Dims[1] = {-1};
  const int idate_Rank = 1;
  PyArrayObject *capi_idate_tmp = NULL;
  int capi_idate_intent = 0;
  int nfhour = 0;
  static char *capi_kwlist[] = {"filename",NULL};

/*routdebugenter*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_clock();
#endif
  if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
    "O:_read_sfcflx_nemsio.read_nemsio_header",\
    capi_kwlist,&filename_capi))
    return NULL;
/*frompyobj*/
  /* Processing variable filename */
  slen(filename) = 500;
  f2py_success = string_from_pyobj(&filename,&slen(filename),"",filename_capi,"string_from_pyobj failed in converting 1st argument `filename' of _read_sfcflx_nemsio.read_nemsio_header to C string");
  if (f2py_success) {
  /* Processing variable nlons */
  /* Processing variable nlats */
  /* Processing variable nrecs */
  /* Processing variable idate */
  idate_Dims[0]=7;
  capi_idate_intent |= F2PY_INTENT_OUT|F2PY_INTENT_HIDE;
  capi_idate_tmp = array_from_pyobj(NPY_INT,idate_Dims,idate_Rank,capi_idate_intent,Py_None);
  if (capi_idate_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_read_sfcflx_nemsio_error,"failed in converting hidden `idate' of _read_sfcflx_nemsio.read_nemsio_header to C/Fortran array" );
  } else {
    idate = (int *)(PyArray_DATA(capi_idate_tmp));

  /* Processing variable nfhour */
/*end of frompyobj*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_call_clock();
#endif
/*callfortranroutine*/
        (*f2py_func)(filename,&nlons,&nlats,&nrecs,idate,&nfhour,slen(filename));
if (PyErr_Occurred())
  f2py_success = 0;
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_call_clock();
#endif
/*end of callfortranroutine*/
    if (f2py_success) {
/*pyobjfrom*/
/*end of pyobjfrom*/
    CFUNCSMESS("Building return value.\n");
    capi_buildvalue = Py_BuildValue("iiiNi",nlons,nlats,nrecs,capi_idate_tmp,nfhour);
/*closepyobjfrom*/
/*end of closepyobjfrom*/
    } /*if (f2py_success) after callfortranroutine*/
/*cleanupfrompyobj*/
  /* End of cleaning variable nfhour */
  }  /*if (capi_idate_tmp == NULL) ... else of idate*/
  /* End of cleaning variable idate */
  /* End of cleaning variable nrecs */
  /* End of cleaning variable nlats */
  /* End of cleaning variable nlons */
    STRINGFREE(filename);
  }  /*if (f2py_success) of filename*/
  /* End of cleaning variable filename */
/*end of cleanupfrompyobj*/
  if (capi_buildvalue == NULL) {
/*routdebugfailure*/
  } else {
/*routdebugleave*/
  }
  CFUNCSMESS("Freeing memory.\n");
/*freemem*/
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_clock();
#endif
  return capi_buildvalue;
}
/************************* end of read_nemsio_header *************************/

/**************************** read_nemsio_latlons ****************************/
static char doc_f2py_rout__read_sfcflx_nemsio_read_nemsio_latlons[] = "\
lats,lons = read_nemsio_latlons(filename,nlons,nlats)\n\nWrapper for ``read_nemsio_latlons``.\
\n\nParameters\n----------\n"
"filename : input string(len=500)\n"
"nlons : input int\n"
"nlats : input int\n"
"\nReturns\n-------\n"
"lats : rank-1 array('f') with bounds (nlats)\n"
"lons : rank-1 array('f') with bounds (nlons)";
/* extern void F_FUNC_US(read_nemsio_latlons,READ_NEMSIO_LATLONS)(string,int*,int*,float*,float*,size_t); */
static PyObject *f2py_rout__read_sfcflx_nemsio_read_nemsio_latlons(const PyObject *capi_self,
                           PyObject *capi_args,
                           PyObject *capi_keywds,
                           void (*f2py_func)(string,int*,int*,float*,float*,size_t)) {
  PyObject * volatile capi_buildvalue = NULL;
  volatile int f2py_success = 1;
/*decl*/

  string filename = NULL;
  int slen(filename);
  PyObject *filename_capi = Py_None;
  int nlons = 0;
  PyObject *nlons_capi = Py_None;
  int nlats = 0;
  PyObject *nlats_capi = Py_None;
  float *lats = NULL;
  npy_intp lats_Dims[1] = {-1};
  const int lats_Rank = 1;
  PyArrayObject *capi_lats_tmp = NULL;
  int capi_lats_intent = 0;
  float *lons = NULL;
  npy_intp lons_Dims[1] = {-1};
  const int lons_Rank = 1;
  PyArrayObject *capi_lons_tmp = NULL;
  int capi_lons_intent = 0;
  static char *capi_kwlist[] = {"filename","nlons","nlats",NULL};

/*routdebugenter*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_clock();
#endif
  if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
    "OOO:_read_sfcflx_nemsio.read_nemsio_latlons",\
    capi_kwlist,&filename_capi,&nlons_capi,&nlats_capi))
    return NULL;
/*frompyobj*/
  /* Processing variable filename */
  slen(filename) = 500;
  f2py_success = string_from_pyobj(&filename,&slen(filename),"",filename_capi,"string_from_pyobj failed in converting 1st argument `filename' of _read_sfcflx_nemsio.read_nemsio_latlons to C string");
  if (f2py_success) {
  /* Processing variable nlons */
    f2py_success = int_from_pyobj(&nlons,nlons_capi,"_read_sfcflx_nemsio.read_nemsio_latlons() 2nd argument (nlons) can't be converted to int");
  if (f2py_success) {
  /* Processing variable nlats */
    f2py_success = int_from_pyobj(&nlats,nlats_capi,"_read_sfcflx_nemsio.read_nemsio_latlons() 3rd argument (nlats) can't be converted to int");
  if (f2py_success) {
  /* Processing variable lats */
  lats_Dims[0]=nlats;
  capi_lats_intent |= F2PY_INTENT_OUT|F2PY_INTENT_HIDE;
  capi_lats_tmp = array_from_pyobj(NPY_FLOAT,lats_Dims,lats_Rank,capi_lats_intent,Py_None);
  if (capi_lats_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_read_sfcflx_nemsio_error,"failed in converting hidden `lats' of _read_sfcflx_nemsio.read_nemsio_latlons to C/Fortran array" );
  } else {
    lats = (float *)(PyArray_DATA(capi_lats_tmp));

  /* Processing variable lons */
  lons_Dims[0]=nlons;
  capi_lons_intent |= F2PY_INTENT_OUT|F2PY_INTENT_HIDE;
  capi_lons_tmp = array_from_pyobj(NPY_FLOAT,lons_Dims,lons_Rank,capi_lons_intent,Py_None);
  if (capi_lons_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_read_sfcflx_nemsio_error,"failed in converting hidden `lons' of _read_sfcflx_nemsio.read_nemsio_latlons to C/Fortran array" );
  } else {
    lons = (float *)(PyArray_DATA(capi_lons_tmp));

/*end of frompyobj*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_call_clock();
#endif
/*callfortranroutine*/
        (*f2py_func)(filename,&nlons,&nlats,lats,lons,slen(filename));
if (PyErr_Occurred())
  f2py_success = 0;
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_call_clock();
#endif
/*end of callfortranroutine*/
    if (f2py_success) {
/*pyobjfrom*/
/*end of pyobjfrom*/
    CFUNCSMESS("Building return value.\n");
    capi_buildvalue = Py_BuildValue("NN",capi_lats_tmp,capi_lons_tmp);
/*closepyobjfrom*/
/*end of closepyobjfrom*/
    } /*if (f2py_success) after callfortranroutine*/
/*cleanupfrompyobj*/
  }  /*if (capi_lons_tmp == NULL) ... else of lons*/
  /* End of cleaning variable lons */
  }  /*if (capi_lats_tmp == NULL) ... else of lats*/
  /* End of cleaning variable lats */
  } /*if (f2py_success) of nlats*/
  /* End of cleaning variable nlats */
  } /*if (f2py_success) of nlons*/
  /* End of cleaning variable nlons */
    STRINGFREE(filename);
  }  /*if (f2py_success) of filename*/
  /* End of cleaning variable filename */
/*end of cleanupfrompyobj*/
  if (capi_buildvalue == NULL) {
/*routdebugfailure*/
  } else {
/*routdebugleave*/
  }
  CFUNCSMESS("Freeing memory.\n");
/*freemem*/
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_clock();
#endif
  return capi_buildvalue;
}
/************************* end of read_nemsio_latlons *************************/

/**************************** read_nemsio_varnames ****************************/
static char doc_f2py_rout__read_sfcflx_nemsio_read_nemsio_varnames[] = "\
irecnames,ireclevtypes,ireclevs = read_nemsio_varnames(filename,nrecs)\n\nWrapper for ``read_nemsio_varnames``.\
\n\nParameters\n----------\n"
"filename : input string(len=500)\n"
"nrecs : input int\n"
"\nReturns\n-------\n"
"irecnames : rank-2 array('i') with bounds (nrecs,32)\n"
"ireclevtypes : rank-2 array('i') with bounds (nrecs,32)\n"
"ireclevs : rank-1 array('i') with bounds (nrecs)";
/* extern void F_FUNC_US(read_nemsio_varnames,READ_NEMSIO_VARNAMES)(string,int*,int*,int*,int*,size_t); */
static PyObject *f2py_rout__read_sfcflx_nemsio_read_nemsio_varnames(const PyObject *capi_self,
                           PyObject *capi_args,
                           PyObject *capi_keywds,
                           void (*f2py_func)(string,int*,int*,int*,int*,size_t)) {
  PyObject * volatile capi_buildvalue = NULL;
  volatile int f2py_success = 1;
/*decl*/

  string filename = NULL;
  int slen(filename);
  PyObject *filename_capi = Py_None;
  int nrecs = 0;
  PyObject *nrecs_capi = Py_None;
  int *irecnames = NULL;
  npy_intp irecnames_Dims[2] = {-1, -1};
  const int irecnames_Rank = 2;
  PyArrayObject *capi_irecnames_tmp = NULL;
  int capi_irecnames_intent = 0;
  int *ireclevtypes = NULL;
  npy_intp ireclevtypes_Dims[2] = {-1, -1};
  const int ireclevtypes_Rank = 2;
  PyArrayObject *capi_ireclevtypes_tmp = NULL;
  int capi_ireclevtypes_intent = 0;
  int *ireclevs = NULL;
  npy_intp ireclevs_Dims[1] = {-1};
  const int ireclevs_Rank = 1;
  PyArrayObject *capi_ireclevs_tmp = NULL;
  int capi_ireclevs_intent = 0;
  static char *capi_kwlist[] = {"filename","nrecs",NULL};

/*routdebugenter*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_clock();
#endif
  if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
    "OO:_read_sfcflx_nemsio.read_nemsio_varnames",\
    capi_kwlist,&filename_capi,&nrecs_capi))
    return NULL;
/*frompyobj*/
  /* Processing variable filename */
  slen(filename) = 500;
  f2py_success = string_from_pyobj(&filename,&slen(filename),"",filename_capi,"string_from_pyobj failed in converting 1st argument `filename' of _read_sfcflx_nemsio.read_nemsio_varnames to C string");
  if (f2py_success) {
  /* Processing variable nrecs */
    f2py_success = int_from_pyobj(&nrecs,nrecs_capi,"_read_sfcflx_nemsio.read_nemsio_varnames() 2nd argument (nrecs) can't be converted to int");
  if (f2py_success) {
  /* Processing variable irecnames */
  irecnames_Dims[0]=nrecs,irecnames_Dims[1]=32;
  capi_irecnames_intent |= F2PY_INTENT_OUT|F2PY_INTENT_HIDE;
  capi_irecnames_tmp = array_from_pyobj(NPY_INT,irecnames_Dims,irecnames_Rank,capi_irecnames_intent,Py_None);
  if (capi_irecnames_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_read_sfcflx_nemsio_error,"failed in converting hidden `irecnames' of _read_sfcflx_nemsio.read_nemsio_varnames to C/Fortran array" );
  } else {
    irecnames = (int *)(PyArray_DATA(capi_irecnames_tmp));

  /* Processing variable ireclevtypes */
  ireclevtypes_Dims[0]=nrecs,ireclevtypes_Dims[1]=32;
  capi_ireclevtypes_intent |= F2PY_INTENT_OUT|F2PY_INTENT_HIDE;
  capi_ireclevtypes_tmp = array_from_pyobj(NPY_INT,ireclevtypes_Dims,ireclevtypes_Rank,capi_ireclevtypes_intent,Py_None);
  if (capi_ireclevtypes_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_read_sfcflx_nemsio_error,"failed in converting hidden `ireclevtypes' of _read_sfcflx_nemsio.read_nemsio_varnames to C/Fortran array" );
  } else {
    ireclevtypes = (int *)(PyArray_DATA(capi_ireclevtypes_tmp));

  /* Processing variable ireclevs */
  ireclevs_Dims[0]=nrecs;
  capi_ireclevs_intent |= F2PY_INTENT_OUT|F2PY_INTENT_HIDE;
  capi_ireclevs_tmp = array_from_pyobj(NPY_INT,ireclevs_Dims,ireclevs_Rank,capi_ireclevs_intent,Py_None);
  if (capi_ireclevs_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_read_sfcflx_nemsio_error,"failed in converting hidden `ireclevs' of _read_sfcflx_nemsio.read_nemsio_varnames to C/Fortran array" );
  } else {
    ireclevs = (int *)(PyArray_DATA(capi_ireclevs_tmp));

/*end of frompyobj*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_call_clock();
#endif
/*callfortranroutine*/
        (*f2py_func)(filename,&nrecs,irecnames,ireclevtypes,ireclevs,slen(filename));
if (PyErr_Occurred())
  f2py_success = 0;
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_call_clock();
#endif
/*end of callfortranroutine*/
    if (f2py_success) {
/*pyobjfrom*/
/*end of pyobjfrom*/
    CFUNCSMESS("Building return value.\n");
    capi_buildvalue = Py_BuildValue("NNN",capi_irecnames_tmp,capi_ireclevtypes_tmp,capi_ireclevs_tmp);
/*closepyobjfrom*/
/*end of closepyobjfrom*/
    } /*if (f2py_success) after callfortranroutine*/
/*cleanupfrompyobj*/
  }  /*if (capi_ireclevs_tmp == NULL) ... else of ireclevs*/
  /* End of cleaning variable ireclevs */
  }  /*if (capi_ireclevtypes_tmp == NULL) ... else of ireclevtypes*/
  /* End of cleaning variable ireclevtypes */
  }  /*if (capi_irecnames_tmp == NULL) ... else of irecnames*/
  /* End of cleaning variable irecnames */
  } /*if (f2py_success) of nrecs*/
  /* End of cleaning variable nrecs */
    STRINGFREE(filename);
  }  /*if (f2py_success) of filename*/
  /* End of cleaning variable filename */
/*end of cleanupfrompyobj*/
  if (capi_buildvalue == NULL) {
/*routdebugfailure*/
  } else {
/*routdebugleave*/
  }
  CFUNCSMESS("Freeing memory.\n");
/*freemem*/
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_clock();
#endif
  return capi_buildvalue;
}
/************************ end of read_nemsio_varnames ************************/

/*************************** read_nemsio_2dgriddata ***************************/
static char doc_f2py_rout__read_sfcflx_nemsio_read_nemsio_2dgriddata[] = "\
grids = read_nemsio_2dgriddata(filename,nlons,nlats,irecnames,ireclevtypes,reclevs,[nrecs])\n\nWrapper for ``read_nemsio_2dgriddata``.\
\n\nParameters\n----------\n"
"filename : input string(len=500)\n"
"nlons : input int\n"
"nlats : input int\n"
"irecnames : input rank-2 array('i') with bounds (nrecs,32)\n"
"ireclevtypes : input rank-2 array('i') with bounds (nrecs,32)\n"
"reclevs : input rank-1 array('i') with bounds (nrecs)\n"
"\nOther Parameters\n----------------\n"
"nrecs : input int, optional\n    Default: shape(irecnames,0)\n"
"\nReturns\n-------\n"
"grids : rank-3 array('f') with bounds (nlons,nlats,nrecs)";
/* extern void F_FUNC_US(read_nemsio_2dgriddata,READ_NEMSIO_2DGRIDDATA)(string,int*,int*,int*,int*,int*,int*,float*,size_t); */
static PyObject *f2py_rout__read_sfcflx_nemsio_read_nemsio_2dgriddata(const PyObject *capi_self,
                           PyObject *capi_args,
                           PyObject *capi_keywds,
                           void (*f2py_func)(string,int*,int*,int*,int*,int*,int*,float*,size_t)) {
  PyObject * volatile capi_buildvalue = NULL;
  volatile int f2py_success = 1;
/*decl*/

  string filename = NULL;
  int slen(filename);
  PyObject *filename_capi = Py_None;
  int nlons = 0;
  PyObject *nlons_capi = Py_None;
  int nlats = 0;
  PyObject *nlats_capi = Py_None;
  int nrecs = 0;
  PyObject *nrecs_capi = Py_None;
  int *irecnames = NULL;
  npy_intp irecnames_Dims[2] = {-1, -1};
  const int irecnames_Rank = 2;
  PyArrayObject *capi_irecnames_tmp = NULL;
  int capi_irecnames_intent = 0;
  PyObject *irecnames_capi = Py_None;
  int *ireclevtypes = NULL;
  npy_intp ireclevtypes_Dims[2] = {-1, -1};
  const int ireclevtypes_Rank = 2;
  PyArrayObject *capi_ireclevtypes_tmp = NULL;
  int capi_ireclevtypes_intent = 0;
  PyObject *ireclevtypes_capi = Py_None;
  int *reclevs = NULL;
  npy_intp reclevs_Dims[1] = {-1};
  const int reclevs_Rank = 1;
  PyArrayObject *capi_reclevs_tmp = NULL;
  int capi_reclevs_intent = 0;
  PyObject *reclevs_capi = Py_None;
  float *grids = NULL;
  npy_intp grids_Dims[3] = {-1, -1, -1};
  const int grids_Rank = 3;
  PyArrayObject *capi_grids_tmp = NULL;
  int capi_grids_intent = 0;
  static char *capi_kwlist[] = {"filename","nlons","nlats","irecnames","ireclevtypes","reclevs","nrecs",NULL};

/*routdebugenter*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_clock();
#endif
  if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
    "OOOOOO|O:_read_sfcflx_nemsio.read_nemsio_2dgriddata",\
    capi_kwlist,&filename_capi,&nlons_capi,&nlats_capi,&irecnames_capi,&ireclevtypes_capi,&reclevs_capi,&nrecs_capi))
    return NULL;
/*frompyobj*/
  /* Processing variable filename */
  slen(filename) = 500;
  f2py_success = string_from_pyobj(&filename,&slen(filename),"",filename_capi,"string_from_pyobj failed in converting 1st argument `filename' of _read_sfcflx_nemsio.read_nemsio_2dgriddata to C string");
  if (f2py_success) {
  /* Processing variable nlons */
    f2py_success = int_from_pyobj(&nlons,nlons_capi,"_read_sfcflx_nemsio.read_nemsio_2dgriddata() 2nd argument (nlons) can't be converted to int");
  if (f2py_success) {
  /* Processing variable nlats */
    f2py_success = int_from_pyobj(&nlats,nlats_capi,"_read_sfcflx_nemsio.read_nemsio_2dgriddata() 3rd argument (nlats) can't be converted to int");
  if (f2py_success) {
  /* Processing variable irecnames */
  irecnames_Dims[1]=32;
  capi_irecnames_intent |= F2PY_INTENT_IN;
  capi_irecnames_tmp = array_from_pyobj(NPY_INT,irecnames_Dims,irecnames_Rank,capi_irecnames_intent,irecnames_capi);
  if (capi_irecnames_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_read_sfcflx_nemsio_error,"failed in converting 4th argument `irecnames' of _read_sfcflx_nemsio.read_nemsio_2dgriddata to C/Fortran array" );
  } else {
    irecnames = (int *)(PyArray_DATA(capi_irecnames_tmp));

  /* Processing variable nrecs */
  if (nrecs_capi == Py_None) nrecs = shape(irecnames,0); else
    f2py_success = int_from_pyobj(&nrecs,nrecs_capi,"_read_sfcflx_nemsio.read_nemsio_2dgriddata() 1st keyword (nrecs) can't be converted to int");
  if (f2py_success) {
  CHECKSCALAR(shape(irecnames,0)==nrecs,"shape(irecnames,0)==nrecs","1st keyword nrecs","read_nemsio_2dgriddata:nrecs=%d",nrecs) {
  /* Processing variable ireclevtypes */
  ireclevtypes_Dims[0]=nrecs,ireclevtypes_Dims[1]=32;
  capi_ireclevtypes_intent |= F2PY_INTENT_IN;
  capi_ireclevtypes_tmp = array_from_pyobj(NPY_INT,ireclevtypes_Dims,ireclevtypes_Rank,capi_ireclevtypes_intent,ireclevtypes_capi);
  if (capi_ireclevtypes_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_read_sfcflx_nemsio_error,"failed in converting 5th argument `ireclevtypes' of _read_sfcflx_nemsio.read_nemsio_2dgriddata to C/Fortran array" );
  } else {
    ireclevtypes = (int *)(PyArray_DATA(capi_ireclevtypes_tmp));

  /* Processing variable reclevs */
  reclevs_Dims[0]=nrecs;
  capi_reclevs_intent |= F2PY_INTENT_IN;
  capi_reclevs_tmp = array_from_pyobj(NPY_INT,reclevs_Dims,reclevs_Rank,capi_reclevs_intent,reclevs_capi);
  if (capi_reclevs_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_read_sfcflx_nemsio_error,"failed in converting 6th argument `reclevs' of _read_sfcflx_nemsio.read_nemsio_2dgriddata to C/Fortran array" );
  } else {
    reclevs = (int *)(PyArray_DATA(capi_reclevs_tmp));

  /* Processing variable grids */
  grids_Dims[0]=nlons,grids_Dims[1]=nlats,grids_Dims[2]=nrecs;
  capi_grids_intent |= F2PY_INTENT_OUT|F2PY_INTENT_HIDE;
  capi_grids_tmp = array_from_pyobj(NPY_FLOAT,grids_Dims,grids_Rank,capi_grids_intent,Py_None);
  if (capi_grids_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_read_sfcflx_nemsio_error,"failed in converting hidden `grids' of _read_sfcflx_nemsio.read_nemsio_2dgriddata to C/Fortran array" );
  } else {
    grids = (float *)(PyArray_DATA(capi_grids_tmp));

/*end of frompyobj*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_call_clock();
#endif
/*callfortranroutine*/
        (*f2py_func)(filename,&nlons,&nlats,&nrecs,irecnames,ireclevtypes,reclevs,grids,slen(filename));
if (PyErr_Occurred())
  f2py_success = 0;
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_call_clock();
#endif
/*end of callfortranroutine*/
    if (f2py_success) {
/*pyobjfrom*/
/*end of pyobjfrom*/
    CFUNCSMESS("Building return value.\n");
    capi_buildvalue = Py_BuildValue("N",capi_grids_tmp);
/*closepyobjfrom*/
/*end of closepyobjfrom*/
    } /*if (f2py_success) after callfortranroutine*/
/*cleanupfrompyobj*/
  }  /*if (capi_grids_tmp == NULL) ... else of grids*/
  /* End of cleaning variable grids */
  if((PyObject *)capi_reclevs_tmp!=reclevs_capi) {
    Py_XDECREF(capi_reclevs_tmp); }
  }  /*if (capi_reclevs_tmp == NULL) ... else of reclevs*/
  /* End of cleaning variable reclevs */
  if((PyObject *)capi_ireclevtypes_tmp!=ireclevtypes_capi) {
    Py_XDECREF(capi_ireclevtypes_tmp); }
  }  /*if (capi_ireclevtypes_tmp == NULL) ... else of ireclevtypes*/
  /* End of cleaning variable ireclevtypes */
  } /*CHECKSCALAR(shape(irecnames,0)==nrecs)*/
  } /*if (f2py_success) of nrecs*/
  /* End of cleaning variable nrecs */
  if((PyObject *)capi_irecnames_tmp!=irecnames_capi) {
    Py_XDECREF(capi_irecnames_tmp); }
  }  /*if (capi_irecnames_tmp == NULL) ... else of irecnames*/
  /* End of cleaning variable irecnames */
  } /*if (f2py_success) of nlats*/
  /* End of cleaning variable nlats */
  } /*if (f2py_success) of nlons*/
  /* End of cleaning variable nlons */
    STRINGFREE(filename);
  }  /*if (f2py_success) of filename*/
  /* End of cleaning variable filename */
/*end of cleanupfrompyobj*/
  if (capi_buildvalue == NULL) {
/*routdebugfailure*/
  } else {
/*routdebugleave*/
  }
  CFUNCSMESS("Freeing memory.\n");
/*freemem*/
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_clock();
#endif
  return capi_buildvalue;
}
/*********************** end of read_nemsio_2dgriddata ***********************/
/*eof body*/

/******************* See f2py2e/f90mod_rules.py: buildhooks *******************/
/*need_f90modhooks*/

/************** See f2py2e/rules.py: module_rules['modulebody'] **************/

/******************* See f2py2e/common_rules.py: buildhooks *******************/

/*need_commonhooks*/

/**************************** See f2py2e/rules.py ****************************/

static FortranDataDef f2py_routine_defs[] = {
  {"read_nemsio_header",-1,{{-1}},0,(char *)F_FUNC_US(read_nemsio_header,READ_NEMSIO_HEADER),(f2py_init_func)f2py_rout__read_sfcflx_nemsio_read_nemsio_header,doc_f2py_rout__read_sfcflx_nemsio_read_nemsio_header},
  {"read_nemsio_latlons",-1,{{-1}},0,(char *)F_FUNC_US(read_nemsio_latlons,READ_NEMSIO_LATLONS),(f2py_init_func)f2py_rout__read_sfcflx_nemsio_read_nemsio_latlons,doc_f2py_rout__read_sfcflx_nemsio_read_nemsio_latlons},
  {"read_nemsio_varnames",-1,{{-1}},0,(char *)F_FUNC_US(read_nemsio_varnames,READ_NEMSIO_VARNAMES),(f2py_init_func)f2py_rout__read_sfcflx_nemsio_read_nemsio_varnames,doc_f2py_rout__read_sfcflx_nemsio_read_nemsio_varnames},
  {"read_nemsio_2dgriddata",-1,{{-1}},0,(char *)F_FUNC_US(read_nemsio_2dgriddata,READ_NEMSIO_2DGRIDDATA),(f2py_init_func)f2py_rout__read_sfcflx_nemsio_read_nemsio_2dgriddata,doc_f2py_rout__read_sfcflx_nemsio_read_nemsio_2dgriddata},

/*eof routine_defs*/
  {NULL}
};

static PyMethodDef f2py_module_methods[] = {

  {NULL,NULL}
};

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  "_read_sfcflx_nemsio",
  NULL,
  -1,
  f2py_module_methods,
  NULL,
  NULL,
  NULL,
  NULL
};
#endif

#if PY_VERSION_HEX >= 0x03000000
#define RETVAL m
PyMODINIT_FUNC PyInit__read_sfcflx_nemsio(void) {
#else
#define RETVAL
PyMODINIT_FUNC init_read_sfcflx_nemsio(void) {
#endif
  int i;
  PyObject *m,*d, *s;
#if PY_VERSION_HEX >= 0x03000000
  m = _read_sfcflx_nemsio_module = PyModule_Create(&moduledef);
#else
  m = _read_sfcflx_nemsio_module = Py_InitModule("_read_sfcflx_nemsio", f2py_module_methods);
#endif
  Py_TYPE(&PyFortran_Type) = &PyType_Type;
  import_array();
  if (PyErr_Occurred())
    {PyErr_SetString(PyExc_ImportError, "can't initialize module _read_sfcflx_nemsio (failed to import numpy)"); return RETVAL;}
  d = PyModule_GetDict(m);
  s = PyString_FromString("$Revision: $");
  PyDict_SetItemString(d, "__version__", s);
#if PY_VERSION_HEX >= 0x03000000
  s = PyUnicode_FromString(
#else
  s = PyString_FromString(
#endif
    "This module '_read_sfcflx_nemsio' is auto-generated with f2py (version:2).\nFunctions:\n"
"  nlons,nlats,nrecs,idate,nfhour = read_nemsio_header(filename)\n"
"  lats,lons = read_nemsio_latlons(filename,nlons,nlats)\n"
"  irecnames,ireclevtypes,ireclevs = read_nemsio_varnames(filename,nrecs)\n"
"  grids = read_nemsio_2dgriddata(filename,nlons,nlats,irecnames,ireclevtypes,reclevs,nrecs=shape(irecnames,0))\n"
".");
  PyDict_SetItemString(d, "__doc__", s);
  _read_sfcflx_nemsio_error = PyErr_NewException ("_read_sfcflx_nemsio.error", NULL, NULL);
  Py_DECREF(s);
  for(i=0;f2py_routine_defs[i].name!=NULL;i++)
    PyDict_SetItemString(d, f2py_routine_defs[i].name,PyFortranObject_NewAsAttr(&f2py_routine_defs[i]));




/*eof initf2pywraphooks*/
/*eof initf90modhooks*/

/*eof initcommonhooks*/


#ifdef F2PY_REPORT_ATEXIT
  if (! PyErr_Occurred())
    on_exit(f2py_report_on_exit,(void*)"_read_sfcflx_nemsio");
#endif

  return RETVAL;
}
#ifdef __cplusplus
}
#endif