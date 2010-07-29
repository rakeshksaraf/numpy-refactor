#ifndef _NPY_DESCRIPTOR_H_
#define _NPY_DESCRIPTOR_H_

#include "npy_defs.h"
#include "npy_object.h"

#define NpyDataType_HASFIELDS(obj) ((obj)->names != NULL)
#define NpyDataType_FLAGCHK(dtype, flag)                                   \
    (((dtype)->flags & (flag)) == (flag))

#define NpyDataType_REFCHK(dtype)                                          \
    NpyDataType_FLAGCHK(dtype, NPY_ITEM_REFCOUNT)




/*
 * Structure definitions
 */

struct NpyArray_DateTimeInfo {
    NPY_DATETIMEUNIT base;
    int num;
    int den;      /*
                   * Converted to 1 on input for now -- an
                   * input-only mechanism
                   */
    int events;
};	


struct NpyArray_Descr {
    NpyObject_HEAD
    
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
    struct NpyArray_ArrayDescr
        *subarray;          /*
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
    
    struct NpyArray_ArrFuncs *f; /*
                              * a table of functions specific for each
                              * basic data descriptor
                              */
    
	NpyArray_DateTimeInfo  
        *dtinfo;            /*
                             * Non-NULL if this type is array of 
                             * DATETIME or TIMEDELTA 
                             */
    
};


struct NpyArray_ArrFuncs {
    /* The next four functions *cannot* be NULL */
    
    /*
     * Functions to get and set items with standard Python types
     * -- not array scalars
     */
    NpyArray_GetItemFunc *getitem;
    NpyArray_SetItemFunc *setitem;
    
    /*
     * Copy and/or swap data.  Memory areas may not overlap
     * Use memmove first if they might
     */
    NpyArray_CopySwapNFunc *copyswapn;
    NpyArray_CopySwapFunc *copyswap;
    
    /*
     * Function to compare items
     * Can be NULL
     */
    NpyArray_CompareFunc *compare;
    
    /*
     * Function to select largest
     * Can be NULL
     */
    NpyArray_ArgFunc *argmax;
    
    /*
     * Function to compute dot product
     * Can be NULL
     */
    NpyArray_DotFunc *dotfunc;
    
    /*
     * Function to scan an ASCII file and
     * place a single value plus possible separator
     * Can be NULL
     */
    NpyArray_ScanFunc *scanfunc;
    
    /*
     * Function to read a single value from a string
     * and adjust the pointer; Can be NULL
     */
    NpyArray_FromStrFunc *fromstr;
    
    /*
     * Function to determine if data is zero or not
     * If NULL a default version is
     * used at Registration time.
     */
    NpyArray_NonzeroFunc *nonzero;
    
    /*
     * Used for arange.
     * Can be NULL.
     */
    NpyArray_FillFunc *fill;
    
    /*
     * Function to fill arrays with scalar values
     * Can be NULL
     */
    NpyArray_FillWithScalarFunc *fillwithscalar;
    
    /*
     * Sorting functions
     * Can be NULL
     */
    NpyArray_SortFunc *sort[NPY_NSORTS];
    NpyArray_ArgSortFunc *argsort[NPY_NSORTS];
    
    /*
     * Array of PyArray_CastFuncsItem given cast functions to 
     * user defined types. The array it terminated with PyArray_NOTYPE.
     * Can be NULL.
     */
    struct NpyArray_CastFuncsItem* castfuncs;
    
    /*
     * Functions useful for generalizing
     * the casting rules.
     * Can be NULL;
     */
    NpyArray_ScalarKindFunc *scalarkind;
    int **cancastscalarkindto;
    int *cancastto;
    
    NpyArray_FastClipFunc *fastclip;
    NpyArray_FastPutmaskFunc *fastputmask;
    NpyArray_FastTakeFunc *fasttake;
    
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
    NpyArray_VectorUnaryFunc *cast[NPY_NTYPES];
    
};


struct NpyArray_ArrayDescr {
    NpyArray_Descr *base;
    npy_intp shape_num_dims;    /* shape_num_dims and shape_dims essentially implement */
    npy_intp *shape_dims;       /* a tuple. When shape_num_dims  >= 1 shape_dims is an */
    /* allocated array of ints; shape_dims == NULL iff */
    /* shape_num_dims == 1 */
};



/* Used as the value of an NpyDict to record the fields in an NpyArray_Descr object */
struct NpyArray_DescrField {
    NpyArray_Descr *descr;
    int offset;
    char *title;                /* String owned/managed by each instance */
};


struct NpyArray_CastFuncsItem {
    int totype;
    NpyArray_VectorUnaryFunc* castfunc;
};



extern _NpyTypeObject NpyArrayDescr_Type;


/* Descriptor API */

NpyArray_Descr *NpyArray_DescrNewFromType(int type_num);
NpyArray_Descr *NpyArray_DescrNew(NpyArray_Descr *base);
void NpyArray_DescrDestroy(NpyArray_Descr *);
char **NpyArray_DescrAllocNames(int n);
struct NpyDict_struct *NpyArray_DescrAllocFields(void);
NpyArray_ArrayDescr *NpyArray_DupSubarray(NpyArray_ArrayDescr *src);
void NpyArray_DestroySubarray(NpyArray_ArrayDescr *);
void NpyArray_DescrDeallocNamesAndFields(NpyArray_Descr *base);
NpyArray_Descr *NpyArray_DescrNewByteorder(NpyArray_Descr *self, char newendian);
void NpyArray_DescrSetField(struct NpyDict_struct *self, const char *key, 
                            NpyArray_Descr *descr,
                            int offset, const char *title);
struct NpyDict_struct *NpyArray_DescrFieldsCopy(struct NpyDict_struct *fields);
char **NpyArray_DescrNamesCopy(char **names);
int NpyArray_DescrReplaceNames(NpyArray_Descr *self, char **nameslist);
void NpyArray_DescrSetNames(NpyArray_Descr *self, char **nameslist);

NpyArray_Descr *
NpyArray_SmallType(NpyArray_Descr *chktype, NpyArray_Descr *mintype);
NpyArray_Descr *
NpyArray_DescrFromArray(struct NpyArray *ap, struct NpyArray_Descr *mintype);


#endif
