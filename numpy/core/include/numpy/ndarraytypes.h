#ifndef NDARRAYTYPES_H
#define NDARRAYTYPES_H

#include <assert.h>

/* This is auto-generated by the installer */
#include "numpyconfig.h"

#include "npy_common.h"
#include "npy_defs.h"
#include "npy_endian.h"
#include "utils.h"
#include "numpy/npy_arrayobject.h"

#ifdef NPY_ENABLE_SEPARATE_COMPILATION
        #define NPY_NO_EXPORT NPY_VISIBILITY_HIDDEN
#else
        #define NPY_NO_EXPORT static
#endif

/* Only use thread if configured in config and python supports it */
#if defined WITH_THREAD && !NPY_NO_SMP
        #define NPY_ALLOW_THREADS 1
#else
        #define NPY_ALLOW_THREADS 0
#endif



/* Used for Converter Functions "O&" code in ParseTuple */
#define NPY_FAIL 0
#define NPY_SUCCEED 1

/*
 * Binary compatibility version number.  This number is increased
 * whenever the C-API is changed such that binary compatibility is
 * broken, i.e. whenever a recompile of extension modules is needed.
 */
#define NPY_VERSION NPY_ABI_VERSION

/*
 * Minor API version.  This number is increased whenever a change is
 * made to the C-API -- whether it breaks binary compatibility or not.
 * Some changes, such as adding a function pointer to the end of the
 * function table, can be made without breaking binary compatibility.
 * In this case, only the NPY_FEATURE_VERSION (*not* NPY_VERSION)
 * would be increased.  Whenever binary compatibility is broken, both
 * NPY_VERSION and NPY_FEATURE_VERSION should be increased.
 */
#define NPY_FEATURE_VERSION NPY_API_VERSION

/* basetype array priority */
#define NPY_PRIORITY 0.0

/* default subtype priority */
#define NPY_SUBTYPE_PRIORITY 1.0

/* default scalar priority */
#define NPY_SCALAR_PRIORITY -1000000.0

/* How many floating point types are there */
#define NPY_NUM_FLOATTYPE 3

/*
 * We need to match npy_intp to a signed integer of the same size as a
 * pointer variable. npy_uintp to the equivalent unsigned integer
 */


/*
 * These characters correspond to the array type and the struct
 * module
 */

/*  except 'p' -- signed integer for pointer type */

enum NPY_TYPECHAR { NPY_BOOLLTR = '?',
                        NPY_BYTELTR = 'b',
                        NPY_UBYTELTR = 'B',
                        NPY_SHORTLTR = 'h',
                        NPY_USHORTLTR = 'H',
                        NPY_INTLTR = 'i',
                        NPY_UINTLTR = 'I',
                        NPY_LONGLTR = 'l',
                        NPY_ULONGLTR = 'L',
                        NPY_LONGLONGLTR = 'q',
                        NPY_ULONGLONGLTR = 'Q',
                        NPY_FLOATLTR = 'f',
                        NPY_DOUBLELTR = 'd',
                        NPY_LONGDOUBLELTR = 'g',
                        NPY_CFLOATLTR = 'F',
                        NPY_CDOUBLELTR = 'D',
                        NPY_CLONGDOUBLELTR = 'G',
                        NPY_OBJECTLTR = 'O',
                        NPY_STRINGLTR = 'S',
                        NPY_STRINGLTR2 = 'a',
                        NPY_UNICODELTR = 'U',
                        NPY_VOIDLTR = 'V',
                        NPY_DATETIMELTR = 'M',
                        NPY_TIMEDELTALTR = 'm',
                        NPY_CHARLTR = 'c',

                        /*
                         * No Descriptor, just a define -- this let's
                         * Python users specify an array of integers
                         * large enough to hold a pointer on the
                         * platform
                         */
                        NPY_INTPLTR = 'p',
                        NPY_UINTPLTR = 'P',

                        NPY_GENBOOLLTR ='b',
                        NPY_SIGNEDLTR = 'i',
                        NPY_UNSIGNEDLTR = 'u',
                        NPY_FLOATINGLTR = 'f',
                        NPY_COMPLEXLTR = 'c'
};

typedef enum {
        NPY_QUICKSORT=0,
        NPY_HEAPSORT=1,
        NPY_MERGESORT=2
} NPY_SORTKIND;
#define NPY_NSORTS (NPY_MERGESORT + 1)


typedef enum {
        NPY_SEARCHLEFT=0,
        NPY_SEARCHRIGHT=1
} NPY_SEARCHSIDE;
#define NPY_NSEARCHSIDES (NPY_SEARCHRIGHT + 1)


typedef enum {
        NPY_NOSCALAR=-1,
        NPY_BOOL_SCALAR,
        NPY_INTPOS_SCALAR,
        NPY_INTNEG_SCALAR,
        NPY_FLOAT_SCALAR,
        NPY_COMPLEX_SCALAR,
        NPY_OBJECT_SCALAR
} NPY_SCALARKIND;
#define NPY_NSCALARKINDS (NPY_OBJECT_SCALAR + 1)

typedef enum {
        NPY_ANYORDER=-1,
        NPY_CORDER=0,
        NPY_FORTRANORDER=1
} NPY_ORDER;


typedef enum {
        NPY_CLIP=0,
        NPY_WRAP=1,
        NPY_RAISE=2
} NPY_CLIPMODE;

typedef enum {
        NPY_FR_Y,
        NPY_FR_M,
        NPY_FR_W,
        NPY_FR_B,
        NPY_FR_D,
        NPY_FR_h,
        NPY_FR_m,
        NPY_FR_s,
        NPY_FR_ms,
        NPY_FR_us,
        NPY_FR_ns,
        NPY_FR_ps,
        NPY_FR_fs,
        NPY_FR_as
} NPY_DATETIMEUNIT;

#define NPY_DATETIME_NUMUNITS (NPY_FR_as + 1)
#define NPY_DATETIME_DEFAULTUNIT NPY_FR_us

#define NPY_STR_Y "Y"
#define NPY_STR_M "M"
#define NPY_STR_W "W"
#define NPY_STR_B "B"
#define NPY_STR_D "D"
#define NPY_STR_h "h"
#define NPY_STR_m "m"
#define NPY_STR_s "s"
#define NPY_STR_ms "ms"
#define NPY_STR_us "us"
#define NPY_STR_ns "ns"
#define NPY_STR_ps "ps"
#define NPY_STR_fs "fs"
#define NPY_STR_as "as"


#ifdef constchar
#undef constchar
#endif

#if (PY_VERSION_HEX < 0x02050000)
  #ifndef PY_SSIZE_T_MIN
    typedef int Py_ssize_t;
    #define PY_SSIZE_T_MAX INT_MAX
    #define PY_SSIZE_T_MIN INT_MIN
  #endif
#define NPY_SSIZE_T_PYFMT "i"
#undef PyIndex_Check
#define constchar const char
#define PyIndex_Check(op) 0
#else
#define NPY_SSIZE_T_PYFMT "n"
#define constchar char
#endif

#if NPY_SIZEOF_PY_INTPTR_T == NPY_SIZEOF_INT
        #define NPY_INTP NPY_INT
        #define NPY_UINTP NPY_UINT
        #define PyIntpArrType_Type PyIntArrType_Type
        #define PyUIntpArrType_Type PyUIntArrType_Type
        #define NPY_MAX_INTP NPY_MAX_INT
        #define NPY_MIN_INTP NPY_MIN_INT
        #define NPY_MAX_UINTP NPY_MAX_UINT
        #define NPY_INTP_FMT "d"
#elif NPY_SIZEOF_PY_INTPTR_T == NPY_SIZEOF_LONG
        #define NPY_INTP NPY_LONG
        #define NPY_UINTP NPY_ULONG
        #define PyIntpArrType_Type PyLongArrType_Type
        #define PyUIntpArrType_Type PyULongArrType_Type
        #define NPY_MAX_INTP NPY_MAX_LONG
        #define NPY_MIN_INTP MIN_LONG
        #define NPY_MAX_UINTP NPY_MAX_ULONG
        #define NPY_INTP_FMT "ld"
#elif defined(PY_LONG_LONG) && (NPY_SIZEOF_PY_INTPTR_T == NPY_SIZEOF_LONGLONG)
        #define NPY_INTP NPY_LONGLONG
        #define NPY_UINTP NPY_ULONGLONG
        #define PyIntpArrType_Type PyLongLongArrType_Type
        #define PyUIntpArrType_Type PyULongLongArrType_Type
        #define NPY_MAX_INTP NPY_MAX_LONGLONG
        #define NPY_MIN_INTP NPY_MIN_LONGLONG
        #define NPY_MAX_UINTP NPY_MAX_ULONGLONG
        #define NPY_INTP_FMT "Ld"
#endif

/*
 * We can only use C99 formats for npy_int_p if it is the same as
 * intp_t, hence the condition on HAVE_UNITPTR_T
 */
#if (NPY_USE_C99_FORMATS) == 1 \
        && (defined HAVE_UINTPTR_T) \
        && (defined HAVE_INTTYPES_H)
        #include <inttypes.h>
        #undef NPY_INTP_FMT
        #define NPY_INTP_FMT PRIdPTR
#endif

#define NPY_ERR(str) fprintf(stderr, #str); fflush(stderr);
#define NPY_ERR2(str) fprintf(stderr, str); fflush(stderr);

#define NPY_STRINGIFY(x) #x
#define NPY_TOSTRING(x) NPY_STRINGIFY(x)

  /*
   * Macros to define how array, and dimension/strides data is
   * allocated.
   */

  /* Data buffer */
#define PyDataMem_NEW(size) ((char *)malloc(size))
#define PyDataMem_FREE(ptr)  free(ptr)
#define PyDataMem_RENEW(ptr,size) ((char *)realloc(ptr,size))

#define NPY_USE_PYMEM 1

#if NPY_USE_PYMEM == 1
#define PyArray_malloc PyMem_Malloc
#define PyArray_free PyMem_Free
#define PyArray_realloc PyMem_Realloc
#else
#define PyArray_malloc malloc
#define PyArray_free free
#define PyArray_realloc realloc
#endif

/* Dimensions and strides */
#define PyDimMem_NEW(size)                                         \
    ((npy_intp *)PyArray_malloc(size*sizeof(npy_intp)))

#define PyDimMem_FREE(ptr) PyArray_free(ptr)

#define PyDimMem_RENEW(ptr,size)                                   \
        ((npy_intp *)PyArray_realloc(ptr,size*sizeof(npy_intp)))

/* forward declaration */
struct _PyArray_Descr;

/* These must deal with unaligned and swapped data if necessary */
typedef PyObject * (PyArray_GetItemFunc) (void *, void *);
typedef int (PyArray_SetItemFunc)(PyObject *, void *, void *);

typedef void (PyArray_CopySwapNFunc)(void *, npy_intp, void *, npy_intp,
                                     npy_intp, int, void *);

typedef void (PyArray_CopySwapFunc)(void *, void *, int, void *);
typedef npy_bool (PyArray_NonzeroFunc)(void *, void *);


/*
 * These assume aligned and notswapped data -- a buffer will be used
 * before or contiguous data will be obtained
 */

typedef int (PyArray_CompareFunc)(const void *, const void *, void *);
typedef int (PyArray_ArgFunc)(void*, npy_intp, npy_intp*, void *);

typedef void (PyArray_DotFunc)(void *, npy_intp, void *, npy_intp, void *,
                               npy_intp, void *);

typedef void (PyArray_VectorUnaryFunc)(void *, void *, npy_intp, void *,
                                       void *);

/*
 * XXX the ignore argument should be removed next time the API version
 * is bumped. It used to be the separator.
 */
typedef int (PyArray_ScanFunc)(FILE *fp, void *dptr,
                               char *ignore, struct _PyArray_Descr *);
typedef int (PyArray_FromStrFunc)(char *s, void *dptr, char **endptr,
                                  struct _PyArray_Descr *);

typedef int (PyArray_FillFunc)(void *, npy_intp, void *);

typedef int (PyArray_SortFunc)(void *, npy_intp, void *);
typedef int (PyArray_ArgSortFunc)(void *, npy_intp *, npy_intp, void *);

typedef int (PyArray_FillWithScalarFunc)(void *, npy_intp, void *, void *);

typedef int (PyArray_ScalarKindFunc)(void *);

typedef void (PyArray_FastClipFunc)(void *in, npy_intp n_in, void *min,
                                    void *max, void *out);
typedef void (PyArray_FastPutmaskFunc)(void *in, void *mask, npy_intp n_in,
                                       void *values, npy_intp nv);
typedef int  (PyArray_FastTakeFunc)(void *dest, void *src, npy_intp *indarray,
                                       npy_intp nindarray, npy_intp n_outer,
                                       npy_intp m_middle, npy_intp nelem,
                                       NPY_CLIPMODE clipmode);

typedef struct PyArray_Dims {
        npy_intp *ptr;
        int len;
} PyArray_Dims;

typedef struct {
    int totype;
    PyArray_VectorUnaryFunc* castfunc;
} PyArray_CastFuncsItem;

typedef struct {
        /* The next four functions *cannot* be NULL */

        /*
         * Functions to get and set items with standard Python types
         * -- not array scalars
         */
        PyArray_GetItemFunc *getitem;
        PyArray_SetItemFunc *setitem;

        /*
         * Copy and/or swap data.  Memory areas may not overlap
         * Use memmove first if they might
         */
        PyArray_CopySwapNFunc *copyswapn;
        PyArray_CopySwapFunc *copyswap;

        /*
         * Function to compare items
         * Can be NULL
         */
        PyArray_CompareFunc *compare;

        /*
         * Function to select largest
         * Can be NULL
         */
        PyArray_ArgFunc *argmax;

        /*
         * Function to compute dot product
         * Can be NULL
         */
        PyArray_DotFunc *dotfunc;

        /*
         * Function to scan an ASCII file and
         * place a single value plus possible separator
         * Can be NULL
         */
        PyArray_ScanFunc *scanfunc;

        /*
         * Function to read a single value from a string
         * and adjust the pointer; Can be NULL
         */
        PyArray_FromStrFunc *fromstr;

        /*
         * Function to determine if data is zero or not
         * If NULL a default version is
         * used at Registration time.
         */
        PyArray_NonzeroFunc *nonzero;

        /*
         * Used for arange.
         * Can be NULL.
         */
        PyArray_FillFunc *fill;

        /*
         * Function to fill arrays with scalar values
         * Can be NULL
         */
        PyArray_FillWithScalarFunc *fillwithscalar;

        /*
         * Sorting functions
         * Can be NULL
         */
        PyArray_SortFunc *sort[NPY_NSORTS];
        PyArray_ArgSortFunc *argsort[NPY_NSORTS];

        /*
         * Array of PyArray_CastFuncsItem given cast functions to 
         * user defined types. The array it terminated with PyArray_NOTYPE.
         * Can be NULL.
         */
        PyArray_CastFuncsItem* castfuncs;

        /*
         * Functions useful for generalizing
         * the casting rules.
         * Can be NULL;
         */
        PyArray_ScalarKindFunc *scalarkind;
        int **cancastscalarkindto;
        int *cancastto;

        PyArray_FastClipFunc *fastclip;
        PyArray_FastPutmaskFunc *fastputmask;
        PyArray_FastTakeFunc *fasttake;

        /*
         * A little room to grow --- should use generic function
         * interface for most additions
         */
        void *pad1;
        void *pad2;
        void *pad3;
        void *pad4;

        /*
         * Functions to cast to all other standard types
         * Can have some NULL entries
         */
        PyArray_VectorUnaryFunc *cast[NPY_NTYPES];

} PyArray_ArrFuncs;

/* The item must be reference counted when it is inserted or extracted. */
#define NPY_ITEM_REFCOUNT   0x01
/* Same as needing REFCOUNT */
#define NPY_ITEM_HASOBJECT  0x01
/* Convert to list for pickling */
#define NPY_LIST_PICKLE     0x02
/* The item is a POINTER  */
#define NPY_ITEM_IS_POINTER 0x04
/* memory needs to be initialized for this data-type */
#define NPY_NEEDS_INIT      0x08
/* operations need Python C-API so don't give-up thread. */
#define NPY_NEEDS_PYAPI     0x10
/* Use f.getitem when extracting elements of this data-type */
#define NPY_USE_GETITEM     0x20
/* Use f.setitem when setting creating 0-d array from this data-type.*/
#define NPY_USE_SETITEM     0x40


/* Data-type needs extra initialization on creation */
#define NPY_EXTRA_DTYPE_INIT 0x80

/* When creating an array of this type -- call extra function */
#define NPY_UFUNC_OUTPUT_CREATION 0x100

/*
 *These are inherited for global data-type if any data-types in the
 * field have them
 */
#define NPY_FROM_FIELDS    (NPY_NEEDS_INIT | NPY_LIST_PICKLE |             \
                            NPY_ITEM_REFCOUNT | NPY_NEEDS_PYAPI)

#define NPY_OBJECT_DTYPE_FLAGS (NPY_LIST_PICKLE | NPY_USE_GETITEM |       \
                                NPY_ITEM_IS_POINTER | NPY_ITEM_REFCOUNT | \
                                NPY_NEEDS_INIT | NPY_NEEDS_PYAPI)

#define PyDataType_FLAGCHK(dtype, flag)                                   \
        (((dtype)->flags & (flag)) == (flag))

#define PyDataType_REFCHK(dtype)                                          \
        PyDataType_FLAGCHK(dtype, NPY_ITEM_REFCOUNT)


struct NpyDict_struct;     /* TODO: From numpy_api.h, needed until PyArray_Descr is split into
                              CPython and core parts */

typedef struct {
        NPY_DATETIMEUNIT base;
        int num;
        int den;      /*
                       * Converted to 1 on input for now -- an
                       * input-only mechanism
                       */
        int events;
} PyArray_DateTimeInfo;	

typedef struct _PyArray_Descr {
        PyObject_HEAD
        void *typeobj;          /* Opaque pointer provided by interface layer to describe the
                                 * scalar type. For CPython this is a PyTypeObject. */
        int magic_number;       /* Initialized to NPY_VALID_MAGIC initialization and 
                                   NPY_INVALID_MAGIC on dealloc */
        char kind;              /* kind for this type */
        char type;              /* unique-character representing this type */
        char byteorder;         /*
                                 * '>' (big), '<' (little), '|'
                                 * (not-applicable), or '=' (native).
                                 */
        char unused;
        int flags;              /* flag describing data type */
        int type_num;           /* number representing this type */
        int elsize;             /* element size for this type */
        int alignment;          /* alignment needed for this type */

        struct _arr_descr				\
        *subarray;              /*
                                 * Non-NULL if this type is
                                 * is an array (C-contiguous)
                                 * of some other type
                                 */
        struct NpyDict_struct 
            *fields;            /* The fields dictionary for this type
                                 * For statically defined descr this
                                 * is always NULL.
                                 */

        char **names;           /* Array of char *, NULL indicates end of array. 
                                 * char* lifetime is exactly lifetime of array itself. */

        PyArray_ArrFuncs *f;     /*
                                  * a table of functions specific for each
                                  * basic data descriptor
                                  */


	PyArray_DateTimeInfo  \
	*dtinfo;		/*
				 * Non-NULL if this type is array of 
				 DATETIME or TIMEDELTA */

        
} PyArray_Descr;

	

typedef struct _arr_descr {
    PyArray_Descr *base;
    npy_intp shape_num_dims;    /* shape_num_dims and shape_dims essentially implement */
    npy_intp *shape_dims;       /* a tuple. When shape_num_dims  >= 1 shape_dims is an */
                                /* allocated array of ints; shape_dims == NULL iff */
                                /* shape_num_dims == 1 */
} PyArray_ArrayDescr;

/*
 * The main array object structure. It is recommended to use the macros
 * defined below (PyArray_DATA and friends) access fields here, instead
 * of the members themselves.
 */

typedef struct PyArrayObject {
        PyObject_HEAD
        int magic_number;       /* Initialized to NPY_VALID_MAGIC initialization and NPY_INVALID_MAGIC on dealloc */
        void *interface;        /* Interface-specific wrapper, may be NULL */
        char *data;             /* pointer to raw data buffer */
        int nd;                 /* number of dimensions, also called ndim */
        npy_intp *dimensions;   /* size in each dimension */
        npy_intp *strides;      /*
                                 * bytes to jump to get to the
                                 * next element in each dimension
                                 */
        struct PyArrayObject *base_arr; /* Base when it's specifically an array object */
        void *base_obj;         /* Base when it's an opaque interface object */
    
        PyArray_Descr *descr;   /* Pointer to type structure */
        int flags;              /* Flags describing array -- see below */
        PyObject *weakreflist;  /* For weakreferences */
} PyArrayObject;

#define NPY_AO PyArrayObject

#define fortran fortran_        /* For some compilers */

/* Array Flags Object */
typedef struct PyArrayFlagsObject {
        PyObject_HEAD
        PyObject *arr;
        int flags;
} PyArrayFlagsObject;

/* Mirrors buffer object to ptr */

typedef struct {
        PyObject_HEAD
        PyObject *base;
        void *ptr;
        npy_intp len;
        int flags;
} PyArray_Chunk;


typedef struct {
        npy_longlong year;
        int month, day, hour, min, sec, us, ps, as;
} npy_datetimestruct;

typedef struct {
        npy_longlong day;
        int sec, us, ps, as;
} npy_timedeltastruct;


typedef int (PyArray_FinalizeFunc)(PyArrayObject *, PyObject *);

/*
 * Means c-style contiguous (last index varies the fastest). The data
 * elements right after each other.
 */
#define NPY_CONTIGUOUS    0x0001

/*
 * set if array is a contiguous Fortran array: the first index varies
 * the fastest in memory (strides array is reverse of C-contiguous
 * array)
 */
#define NPY_FORTRAN       0x0002

#define NPY_C_CONTIGUOUS NPY_CONTIGUOUS
#define NPY_F_CONTIGUOUS NPY_FORTRAN

/*
 * Note: all 0-d arrays are CONTIGUOUS and FORTRAN contiguous. If a
 * 1-d array is CONTIGUOUS it is also FORTRAN contiguous
 */

/*
 * If set, the array owns the data: it will be free'd when the array
 * is deleted.
 */
#define NPY_OWNDATA       0x0004

/*
 * An array never has the next four set; they're only used as parameter
 * flags to the the various FromAny functions
 */

/* Cause a cast to occur regardless of whether or not it is safe. */
#define NPY_FORCECAST     0x0010

/*
 * Always copy the array. Returned arrays are always CONTIGUOUS,
 * ALIGNED, and WRITEABLE.
 */
#define NPY_ENSURECOPY    0x0020

/* Make sure the returned array is a base-class ndarray */
#define NPY_ENSUREARRAY   0x0040

/*
 * Make sure that the strides are in units of the element size Needed
 * for some operations with record-arrays.
 */
#define NPY_ELEMENTSTRIDES 0x0080

/*
 * Array data is aligned on the appropiate memory address for the type
 * stored according to how the compiler would align things (e.g., an
 * array of integers (4 bytes each) starts on a memory address that's
 * a multiple of 4)
 */
#define NPY_ALIGNED       0x0100

/* Array data has the native endianness */
#define NPY_NOTSWAPPED    0x0200

/* Array data is writeable */
#define NPY_WRITEABLE     0x0400

/*
 * If this flag is set, then base contains a pointer to an array of
 * the same size that should be updated with the current contents of
 * this array when this array is deallocated
 */
#define NPY_UPDATEIFCOPY  0x1000

/* This flag is for the array interface */
#define NPY_ARR_HAS_DESCR  0x0800


#define NPY_BEHAVED (NPY_ALIGNED | NPY_WRITEABLE)
#define NPY_BEHAVED_NS (NPY_ALIGNED | NPY_WRITEABLE | NPY_NOTSWAPPED)
#define NPY_CARRAY (NPY_CONTIGUOUS | NPY_BEHAVED)
#define NPY_CARRAY_RO (NPY_CONTIGUOUS | NPY_ALIGNED)
#define NPY_FARRAY (NPY_FORTRAN | NPY_BEHAVED)
#define NPY_FARRAY_RO (NPY_FORTRAN | NPY_ALIGNED)
#define NPY_DEFAULT NPY_CARRAY
#define NPY_IN_ARRAY NPY_CARRAY_RO
#define NPY_OUT_ARRAY NPY_CARRAY
#define NPY_INOUT_ARRAY (NPY_CARRAY | NPY_UPDATEIFCOPY)
#define NPY_IN_FARRAY NPY_FARRAY_RO
#define NPY_OUT_FARRAY NPY_FARRAY
#define NPY_INOUT_FARRAY (NPY_FARRAY | NPY_UPDATEIFCOPY)

#define NPY_UPDATE_ALL (NPY_CONTIGUOUS | NPY_FORTRAN | NPY_ALIGNED)


/*
 * Size of internal buffers used for alignment Make BUFSIZE a multiple
 * of sizeof(cdouble) -- ususally 16 so that ufunc buffers are aligned
 */
#define NPY_MIN_BUFSIZE ((int)sizeof(cdouble))
#define NPY_MAX_BUFSIZE (((int)sizeof(cdouble))*1000000)
#define NPY_BUFSIZE 10000
/* #define NPY_BUFSIZE 80*/

#define PyArray_MAX(a,b) (((a)>(b))?(a):(b))
#define PyArray_MIN(a,b) (((a)<(b))?(a):(b))
#define PyArray_CLT(p,q) ((((p).real==(q).real) ? ((p).imag < (q).imag) : \
                               ((p).real < (q).real)))
#define PyArray_CGT(p,q) ((((p).real==(q).real) ? ((p).imag > (q).imag) : \
                               ((p).real > (q).real)))
#define PyArray_CLE(p,q) ((((p).real==(q).real) ? ((p).imag <= (q).imag) : \
                               ((p).real <= (q).real)))
#define PyArray_CGE(p,q) ((((p).real==(q).real) ? ((p).imag >= (q).imag) : \
                               ((p).real >= (q).real)))
#define PyArray_CEQ(p,q) (((p).real==(q).real) && ((p).imag == (q).imag))
#define PyArray_CNE(p,q) (((p).real!=(q).real) || ((p).imag != (q).imag))

/*
 * C API: consists of Macros and functions.  The MACROS are defined
 * here.
 */

#define PyArray_ARRAY(m) ((m) ? assert(PyArray_Check(m)),((PyArrayObject *)(m)) : NULL)
#define PAA(m) PyArray_ARRAY(m)

#define PyArray_CHKFLAGS(m, FLAGS) NpyArray_CHKFLAGS(PAA(m), FLAGS)

#define PyArray_ISCONTIGUOUS(m) NpyArray_ISCONTIGUOUS(PAA(m))
#define PyArray_ISWRITEABLE(m) NpyArray_ISWRITEABLE(PAA(m))
#define PyArray_ISALIGNED(m) NpyArray_ISALIGNED(PAA(m))


#if NPY_ALLOW_THREADS
#define NPY_BEGIN_ALLOW_THREADS Py_BEGIN_ALLOW_THREADS
#define NPY_END_ALLOW_THREADS Py_END_ALLOW_THREADS
#define NPY_BEGIN_THREADS_DEF PyThreadState *_save=NULL;
#define NPY_BEGIN_THREADS _save = PyEval_SaveThread();
#define NPY_END_THREADS   do {if (_save) PyEval_RestoreThread(_save);} while (0);

#define NPY_BEGIN_THREADS_DESCR(dtype)                          \
        do {if (!(PyDataType_FLAGCHK(dtype, NPY_NEEDS_PYAPI)))      \
                NPY_BEGIN_THREADS;} while (0);

#define NPY_END_THREADS_DESCR(dtype)                            \
        do {if (!(PyDataType_FLAGCHK(dtype, NPY_NEEDS_PYAPI)))      \
                NPY_END_THREADS; } while (0);

#define NPY_ALLOW_C_API_DEF  PyGILState_STATE __save__;
#define NPY_ALLOW_C_API      __save__ = PyGILState_Ensure();
#define NPY_DISABLE_C_API    PyGILState_Release(__save__);
#else
#define NPY_BEGIN_ALLOW_THREADS
#define NPY_END_ALLOW_THREADS
#define NPY_BEGIN_THREADS_DEF
#define NPY_BEGIN_THREADS
#define NPY_END_THREADS
#define NPY_BEGIN_THREADS_DESCR(dtype)
#define NPY_END_THREADS_DESCR(dtype)
#define NPY_ALLOW_C_API_DEF
#define NPY_ALLOW_C_API
#define NPY_DISABLE_C_API
#endif

/*****************************
 * Basic iterator object
 *****************************/

/* FWD declaration */
#include <numpy/npy_iterators.h>

typedef struct PyArrayIterObject_tag {
        PyObject_HEAD
        int  magic_offset;      /* Moves magic number to different offset than core, improves checking of Npy_* vs Py_* macros */
        int  magic_number;       /* Initialized to NPY_VALID_MAGIC initialization and NPY_INVALID_MAGIC on dealloc */
        struct NpyArrayIterObject* iter;
} PyArrayIterObject;


/* Iterator API */
#define PyArrayIter_Check(op) PyObject_TypeCheck(op, &PyArrayIter_Type)

#define _PyAIT(it) ((PyArrayIterObject *)(it))
#define _NpyAIT(it) _PyAIT(it)->iter
#define PyArray_ITER_RESET(it) \
    assert(PyArrayIter_Check(it)); \
    NpyArray_ITER_RESET(_NpyAIT(it))
#define PyArray_ITER_NEXT(it) \
    assert(PyArrayIter_Check(it)); \
    NpyArray_ITER_NEXT(_NpyAIT(it))
#define PyArray_ITER_GOTO(it, destination) \
    assert(PyArrayIter_Check(it)); \
    NpyArray_ITER_GOTO(_NpyAIT(it), destination)
#define PyArray_ITER_GOTO1D(it, ind) \
    assert(PyArrayIter_Check(it)); \
    NpyArray_ITER_GOTO1D(_NpyAIT(it), ind)
#define PyArray_ITER_DATA(it) (assert(PyArrayIter_Check(it)), NpyArray_ITER_DATA(_NpyAIT(it)))

#define PyArray_ITER_NOTDONE(it) (assert(PyArrayIter_Check(it)), NpyArray_ITER_NOTDONE(_NpyAIT(it)))



typedef struct {
    PyObject_HEAD
    int  magic_offset;      /* Moves magic number to different offset than core, improves checking of Npy_* vs Py_* macros */
    int               magic_number;       /* Initialized to NPY_VALID_MAGIC initialization and NPY_INVALID_MAGIC on dealloc */
    NpyArrayMultiIterObject* iter;
} PyArrayMultiIterObject;

#define _PyMIT(m) ((PyArrayMultiIterObject *)(m))
#define _NpyMIT(m) _PyMIT(m)->iter
#define PyArray_MultiIter_RESET(multi) \
    NpyArray_MultiIter_RESET(_NpyMIT(multi))
#define PyArray_MultiIter_NEXT(multi) \
    NpyArray_MultiIter_NEXT(_NpyMIT(multi))
#define PyArray_MultiIter_GOTO(multi, dest) \
    NpyArray_MultiIter_GOTO(_NpyMIT(multi), dest)
#define PyArray_MultiIter_GOTO1D(multi, ind) \
    NpyArray_MultiIter_GOTO1D(_NpyMIT(multi), ind)
#define PyArray_MultiIter_DATA(multi, i)                \
    NpyArray_MultiIter_DATA(_NpyMIT(multi), i)
#define PyArray_MultiIter_NEXTi(multi, i)               \
    NpyArray_MultiIter_NEXTi(_NpyMIT(multi), i)

#define PyArray_MultiIter_NOTDONE(multi)                \
    NpyArray_MultiIter_NOTDONE(_NpyMIT(multi))

/* Store the information needed for fancy-indexing over an array */

typedef struct {
        PyObject_HEAD
        /*
         * Multi-iterator portion --- needs to be present in this
         * order to work with PyArray_Broadcast
         */
        int  magic_offset;      /* Moves magic number to different offset than core, improves checking of Npy_* vs Py_* macros */
        int  magic_number;            /* Initialized to NPY_VALID_MAGIC initialization and NPY_INVALID_MAGIC on dealloc */
        NpyArrayMapIterObject* iter;
} PyArrayMapIterObject;

typedef struct {
    PyObject_HEAD
    int  magic_offset;      /* Moves magic number to different offset than core, improves checking of Npy_* vs Py_* macros */
    int  magic_number;       /* Initialized to NPY_VALID_MAGIC initialization and NPY_INVALID_MAGIC on dealloc */
    NpyArrayNeighborhoodIterObject* iter;
} PyArrayNeighborhoodIterObject;

#if 0
/*
 * Neighborhood iterator API
 */

/* General: those work for any mode */
static NPY_INLINE int
PyArrayNeighborhoodIter_Reset(PyArrayNeighborhoodIterObject* iter);
static NPY_INLINE int
PyArrayNeighborhoodIter_Next(PyArrayNeighborhoodIterObject* iter);
#if 0
static NPY_INLINE int
PyArrayNeighborhoodIter_Next2D(PyArrayNeighborhoodIterObject* iter);
#endif

/*
 * Include inline implementations - functions defined there are not
 * considered public API
 */
#define _NPY_INCLUDE_NEIGHBORHOOD_IMP
#include "_neighborhood_iterator_imp.h"
#undef _NPY_INCLUDE_NEIGHBORHOOD_IMP

#endif

/* The default array type */
#define NPY_DEFAULT_TYPE NPY_DOUBLE
#define PyArray_DEFAULT NPY_DEFAULT_TYPE

/*
 * All sorts of useful ways to look into a PyArrayObject.  These are
 * the recommended over casting to PyArrayObject and accessing the
 * members directly.
 */

#define PyArray_NDIM(obj) NpyArray_NDIM(PAA(obj))
#define PyArray_ISONESEGMENT(m) NpyArray_ISONESEGMENT(PAA(m))
#define PyArray_ISFORTRAN(m) NpyArray_ISFORTRAN(PAA(m))
#define PyArray_FORTRAN_IF(m) NpyArray_FORTRAN_IF(PAA(m))
#define FORTRAN_IF PyArray_FORTRAN_IF
#define PyArray_DATA(obj) NpyArray_DATA(PAA(obj))
#define PyArray_BYTES(obj) NpyArray_BYTES(PAA(obj))
#define PyArray_DIMS(obj) NpyArray_DIMS(PAA(obj))
#define PyArray_STRIDES(obj) NpyArray_STRIDES(PAA(obj))
#define PyArray_DIM(obj,n) NpyArray_DIM(PAA(obj),n)
#define PyArray_STRIDE(obj,n) NpyArray_STRIDE(PAA(obj),n)
#define PyArray_DESCR(obj) NpyArray_DESCR(PAA(obj))
#define PyArray_FLAGS(obj) NpyArray_FLAGS(PAA(obj))
#define PyArray_ITEMSIZE(obj) NpyArray_ITEMSIZE(PAA(obj))
#define PyArray_TYPE(obj) NpyArray_TYPE(PAA(obj))
#define PyArray_BASE_ARRAY(obj) NpyArray_BASE_ARRAY(PAA(obj))
#define PyArray_BASE(obj) NpyArray_BASE(PAA(obj))

#define PyArray_GETITEM(obj,itemptr) NpyArray_GETITEM(PAA(obj),itemptr)
#define PyArray_SETITEM(obj,itemptr,v) NpyArray_SETITEM(PAA(obj),itemptr,v)


#define PyDataType_ISBOOL(obj) NpyTypeNum_ISBOOL(_PyADt(obj))
#define PyDataType_ISUNSIGNED(obj) NpyTypeNum_ISUNSIGNED(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISSIGNED(obj) NpyTypeNum_ISSIGNED(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISINTEGER(obj) NpyTypeNum_ISINTEGER(((PyArray_Descr*)(obj))->type_num )
#define PyDataType_ISFLOAT(obj) NpyTypeNum_ISFLOAT(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISNUMBER(obj) NpyTypeNum_ISNUMBER(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISSTRING(obj) NpyTypeNum_ISSTRING(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISCOMPLEX(obj) NpyTypeNum_ISCOMPLEX(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISPYTHON(obj) NpyTypeNum_ISPYTHON(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISFLEXIBLE(obj) NpyTypeNum_ISFLEXIBLE(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISDATETIME(obj) NpyTypeNum_ISDATETIME(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISUSERDEF(obj) NpyTypeNum_ISUSERDEF(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISEXTENDED(obj) NpyTypeNum_ISEXTENDED(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_ISOBJECT(obj) NpyTypeNum_ISOBJECT(((PyArray_Descr*)(obj))->type_num)
#define PyDataType_HASFIELDS(obj) (((PyArray_Descr *)(obj))->names != NULL)

#define PyArray_ISBOOL(obj) NpyTypeNum_ISBOOL(PyArray_TYPE(obj))
#define PyArray_ISUNSIGNED(obj) NpyTypeNum_ISUNSIGNED(PyArray_TYPE(obj))
#define PyArray_ISSIGNED(obj) NpyTypeNum_ISSIGNED(PyArray_TYPE(obj))
#define PyArray_ISINTEGER(obj) NpyTypeNum_ISINTEGER(PyArray_TYPE(obj))
#define PyArray_ISFLOAT(obj) NpyTypeNum_ISFLOAT(PyArray_TYPE(obj))
#define PyArray_ISNUMBER(obj) NpyTypeNum_ISNUMBER(PyArray_TYPE(obj))
#define PyArray_ISSTRING(obj) NpyTypeNum_ISSTRING(PyArray_TYPE(obj))
#define PyArray_ISCOMPLEX(obj) NpyTypeNum_ISCOMPLEX(PyArray_TYPE(obj))
#define PyArray_ISPYTHON(obj) NpyTypeNum_ISPYTHON(PyArray_TYPE(obj))
#define PyArray_ISFLEXIBLE(obj) NpyTypeNum_ISFLEXIBLE(PyArray_TYPE(obj))
#define PyArray_ISDATETIME(obj) NpyTypeNum_ISDATETIME(PyArray_TYPE(obj))
#define PyArray_ISUSERDEF(obj) NpyTypeNum_ISUSERDEF(PyArray_TYPE(obj))
#define PyArray_ISEXTENDED(obj) NpyTypeNum_ISEXTENDED(PyArray_TYPE(obj))
#define PyArray_ISOBJECT(obj) NpyTypeNum_ISOBJECT(PyArray_TYPE(obj))
#define PyArray_HASFIELDS(obj) PyDataType_HASFIELDS(PyArray_DESCR(obj))

    /*
     * FIXME: This should check for a flag on the data-type that
     * states whether or not it is variable length.  Because the
     * ISFLEXIBLE check is hard-coded to the built-in data-types.
     */
#define PyArray_ISVARIABLE(obj) NpyArray_ISVARIABLE(PAA(obj))

#define PyArray_SAFEALIGNEDCOPY(obj) NpyArray_SAFEALIGNEDCOPY(PAA(obj))


#define PyArray_ISNOTSWAPPED(m) NpyArray_ISNOTSWAPPED(PAA(m))
#define PyArray_ISBYTESWAPPED(m) NpyArray_ISBYTESWAPPED(PAA(m))

#define PyArray_FLAGSWAP(m, flags) NpyArray_FLAGSWAP(PAA(m), flags)

#define PyArray_ISCARRAY(m) NpyArray_ISCARRAY(PAA(m))
#define PyArray_ISCARRAY_RO(m) NpyArray_ISCARRAY_RO(PAA(m))
#define PyArray_ISFARRAY(m) NpyArray_ISFARRAY(PAA(m))
#define PyArray_ISFARRAY_RO(m) NpyArray_ISFARRAY_RO(PAA(m))
#define PyArray_ISBEHAVED(m) NpyArray_ISBEHAVED(PAA(m))
#define PyArray_ISBEHAVED_RO(m) NpyArray_ISBEHAVED_RO(PAA(m))


#define PyDataType_ISNOTSWAPPED(d) NpyArray_ISNBO(((PyArray_Descr *)(d))->byteorder)
#define PyDataType_ISBYTESWAPPED(d) (!PyDataType_ISNOTSWAPPED(d))


/*
 * This is the form of the struct that's returned pointed by the
 * PyCObject attribute of an array __array_struct__. See
 * http://numpy.scipy.org/array_interface.shtml for the full
 * documentation.
 */
typedef struct {
    int two;              /*
                           * contains the integer 2 as a sanity
                           * check
                           */

    int nd;               /* number of dimensions */

    char typekind;        /*
                           * kind in array --- character code of
                           * typestr
                           */

    int itemsize;         /* size of each element */

    int flags;            /*
                           * how should be data interpreted. Valid
                           * flags are CONTIGUOUS (1), FORTRAN (2),
                           * ALIGNED (0x100), NOTSWAPPED (0x200), and
                           * WRITEABLE (0x400).  ARR_HAS_DESCR (0x800)
                           * states that arrdescr field is present in
                           * structure
                           */

    npy_intp *shape;       /*
                            * A length-nd array of shape
                            * information
                            */

    npy_intp *strides;    /* A length-nd array of stride information */

    void *data;           /* A pointer to the first element of the array */

    PyObject *descr;      /*
                           * A list of fields or NULL (ignored if flags
                           * does not have ARR_HAS_DESCR flag set)
                           */
} PyArrayInterface;

#endif /* NPY_ARRAYTYPES_H */
