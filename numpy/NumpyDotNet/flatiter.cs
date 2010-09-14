﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using IronPython.Runtime;

namespace NumpyDotNet
{
    public class flatiter : IDisposable, IEnumerator<object>
    {
        internal flatiter(IntPtr coreIter)
        {
            iter = coreIter;
            arr = NpyCoreApi.DecrefToInterface<ndarray>(
                NpyCoreApi.IterArray(iter));
        }

        ~flatiter()
        {
            Dispose(false);
        }

        protected void Dispose(bool disposing)
        {
            if (iter != IntPtr.Zero)
            {
                lock (this) {
                    IntPtr a = iter;
                    iter = IntPtr.Zero;
                    NpyCoreApi.Dealloc(a);
                }
            }
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        public Object this[params object[] args]
        {
            get
            {
                ndarray result;

                using (NpyIndexes indexes = new NpyIndexes())
                {
                    NpyUtil_IndexProcessing.IndexConverter(args, indexes);
                    result = NpyCoreApi.IterSubscript(this, indexes);
                }
                if (result.ndim == 0)
                {
                    // TODO: Should return a numpy scalar
                    return result.GetItem(0);
                }
                else
                {
                    return result;
                }
            }

            set
            {
                using (NpyIndexes indexes = new NpyIndexes())
                {
                    NpyUtil_IndexProcessing.IndexConverter(args, indexes);

                    if (indexes.NumIndexes == 1)
                    {
                        // Special cases for single assigment.
                        switch (indexes.IndexType(0))
                        {
                            case NpyIndexes.NpyIndexTypes.INTP:
                                SingleAssign(indexes.GetIntPtr(0), value);
                                return;
                            case NpyIndexes.NpyIndexTypes.BOOL:
                                if (indexes.GetBool(0))
                                {
                                    SingleAssign(IntPtr.Zero, value);
                                }
                                return;
                            default:
                                break;
                        }
                    }

                    ndarray array_val = NpyArray.FromAny(value, arr.dtype, 0, 0, 0, null);
                    NpyCoreApi.IterSubscriptAssign(this, indexes, array_val);
                }
            }
        }

        public long __len__()
        {
            return Marshal.ReadIntPtr(iter + NpyCoreApi.IterOffsets.off_size).ToInt64();
        }

        public ndarray @base {
            get
            {
                return arr;
            }
        }

        public long index
        {
            get
            {
                return Marshal.ReadIntPtr(iter + NpyCoreApi.IterOffsets.off_index).ToInt64();
            }
        }

        public PythonTuple coords
        {
            get
            {
                int nd = arr.ndim;
                long[] result = new long[nd];
                IntPtr coords = NpyCoreApi.IterCoords(iter);
                for (int i = 0; i < nd; i++)
                {
                    result[i] = Marshal.ReadIntPtr(coords).ToInt64();
                    coords += IntPtr.Size;
                }
                return new PythonTuple(result);
            }
        }

        public ndarray copy()
        {
            return NpyCoreApi.Flatten(arr, NpyDefs.NPY_ORDER.NPY_CORDER);
        }

        #region IEnumerator<object>

        public object Current
        {
            get {
                return arr.GetItem(current.ToInt64()-arr.data.ToInt64());
            }
        }


        public bool MoveNext()
        {
            current = NpyCoreApi.IterNext(iter);
            return (current != IntPtr.Zero);
        }

        public void Reset()
        {
            current = IntPtr.Zero;
            NpyCoreApi.IterReset(iter);
        }

        #endregion

        #region internal methods

        private void SingleAssign(IntPtr index, object value)
        {
            IntPtr pos = NpyCoreApi.IterGoto1D(iter, index);
            if (pos == IntPtr.Zero)
            {
                NpyCoreApi.CheckError();
            }
            arr.SetItem(value, pos.ToInt64() - arr.data.ToInt64());
        }

        #endregion

        internal IntPtr Iter
        {
            get
            {
                return iter;
            }
        }

        private IntPtr iter;
        private IntPtr current;
        private ndarray arr;
    }
}
