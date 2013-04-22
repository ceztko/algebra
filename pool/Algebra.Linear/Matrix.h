#pragma once

#include <vector>
#include <exception>
#include <cstring>

#include "Dims.h"

#define AUTO_STEP -1

namespace Algebra { namespace Linear
{
    template <typename T>
    class Matrix
    {
    private:
        Dims _Dims;
        int _Step;
        T *_M;
        T *_allocEntry;
    public:
        Matrix(const Dims &dims);
        Matrix(const Matrix &other, bool copyData = false);
        Matrix(T *m, const Dims &dims, int step = AUTO_STEP);

        template <typename TRow>
        Matrix(std::vector<TRow> &vec);

        ~Matrix();
        const Dims & GetDims() const;
        int GetStep() const;
        void Transpose();
        void Invert();
        void ToZeroes();
        T * operator [](int row);
        T & operator ()(int row, int col);
        Matrix GetCol(int col);
        Matrix GetRow(int row);
        const T * operator [](int row) const;
        const T & operator ()(int row, int col) const;
        const Matrix GetCol(int col) const;
        const Matrix GetRow(int row) const;
        Matrix & operator =(const Matrix &other);
        Matrix & operator =(T scalar);

        class LUDecomposition
        {
        public:
            LUDecomposition(const Matrix &matrix);
            T GetDeterminant();
        };
    };

    template <typename T>
    Matrix<T>::Matrix(const Dims &dims)
        : _Dims(dims)
    {
        if (dims.Rows < 0 || dims.Cols < 0)
            throw std::exception("Invalid matrix dimsensions");

        _Step = dims.Cols * sizeof(T);
        _M = new T[dims.Rows * dims.Cols];
        _allocEntry = _M;
        ToZeroes();
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix &o, bool copyData)
        : _Dims(o._Dims)
    {
        _Step = o._Step;
        if (copyData)
        {
            _M = new T[_Dims.Rows * _Dims.Cols];
            memcpy(_M, o._M, sizeof(T) * _Dims.Rows * _Dims.Cols);
            _allocEntry = _M;
        }
        else
        {
            _M = o._M;
            _allocEntry = NULL;
        }
    }

    template <typename T>
    Matrix<T>::Matrix(T *m, const Dims &dims, int step)
        : _Dims(dims)
    {
        if (dims.Rows < 0 || dims.Cols < 0)
            throw std::exception("Invalid matrix dimsensions");

        if (step == AUTO_STEP)
            _Step = dims.Cols * sizeof(T);
        else
            _Step = step;

        _M = m;
        _allocEntry = NULL;
    }

    template <typename T>
    template <typename TRow>
    Matrix<T>::Matrix(std::vector<TRow> &vec)
    {
        if (vec.size() < 1)
            throw std::exception("Vector empty");

        const Matrix sample = vec[0];
        Dims sampleDim = sample.GetDims();

        if (sampleDim.Rows != 1)
            throw std::exception("Not a row vector");

		_Dims.Cols = sampleDim.Cols;
		_Dims.Rows = vec.size();
        _Step = sample._Step;
        _M = sample._M;
        _allocEntry = NULL;
    }

    template <typename T>
    Matrix<T>::~Matrix()
    {
        if (_allocEntry != NULL)
            delete [] _M;
    }

    template <typename T>
    const Dims & Matrix<T>::GetDims() const
    {
        return _Dims;
    }

    template <typename T>
    int Matrix<T>::GetStep() const
    {
        return _Step;
    }

    template <typename T>
    void Matrix<T>::Transpose()
    {
        if (_Dims.Rows != _Dims.Cols)
            throw std::exception("Matrix is not squared");

        Matrix copy(*this);

        for (int itr = 0; itr < _Dims.Rows; itr++)
        {
            T *rowCopy = copy[itr];
            for (int itc = 0; itc < _Dims.Cols; itc++)
                (*this)[itc][itr] = rowCopy[itc];
        }
    }

    template <typename T>
    void Matrix<T>::Invert()
    {
        if (_Dims.Rows != _Dims.Cols)
            throw std::exception("Matrix is not squared");

        throw std::exception("Not implemented");
    }

    template <typename T>
    void Matrix<T>::ToZeroes()
    {
        for (int itr = 0; itr < _Dims.Rows; itr++)
        {
            T *row = (*this)[itr];
            for (int itc = 0; itc < _Dims.Cols; itc++)
                row[itc] = 0;
        }
    }

    template <typename T>
    T * Matrix<T>::operator [](int row)
    {
        return &_M[row * _Step];
    }

    template <typename T>
    T & Matrix<T>::operator ()(int row, int col)
    {
        return _M[row * _Step + col];
    }

    template <typename T>
    Matrix<T> Matrix<T>::GetCol(int col)
    {
        return Matrix<T>(&_M[col], Dims(_Dims.Rows, 1), _Step);
    }

    template <typename T>
    Matrix<T> Matrix<T>::GetRow(int row)
    {
        return Matrix<T>(&_M[row * _Step], Dims(1, _Dims.Cols), _Step);
    }

    template <typename T>
    const T * Matrix<T>::operator [](int row) const
    {
        return &_M[row * this->_Step];
    }

    template <typename T>
    const T & Matrix<T>::operator ()(int row, int col) const
    {
        return _M[row * _Step + col];
    }

    template <typename T>
    const Matrix<T> Matrix<T>::GetCol(int col) const
    {
        return Matrix<T>(&_M[col], Dims(_Dims.Rows, 1), _Step);
    }

    template <typename T>
    const Matrix<T> Matrix<T>::GetRow(int row) const
    {
        return Matrix<T>(&_M[row * _Step], Dims(1, _Dims.Cols), 0);
    }

    template <typename T>
    Matrix<T> & Matrix<T>::operator =(T scalar)
    {
        for (int itr = 0; itr < _Dims.Rows; itr++)
        {
            T *row = (*this)[itr];
            for (int itc = 0; itc < _Dims.Cols; itc++)
                row[itc] = scalar;
        }
        return *this;
    }

    template <typename T>
    Matrix<T> & Matrix<T>::operator =(const Matrix &o)
    {
        if (this->_Dims.Rows != o._Dims.Rows || this->_Dims.Cols != o._Dims.Cols)
            throw std::exception("Matrix incompatible");

        for (int itr = 0; itr < this->_Dims.Rows; itr++)
            memcpy((*this)[itr], o[itr], sizeof(T) * this->_Dims.Cols);

        return *this;
    }

    template <typename T>
    Matrix<T>::LUDecomposition::LUDecomposition(const Matrix &A)
    {
        throw std::exception("Not implemented");
    }

    template <typename T>
    T Matrix<T>::LUDecomposition::GetDeterminant()
    {
        throw std::exception("Not implemented");
    }

    template <typename T>
    bool operator ==(const Matrix<T> &A, const Matrix<T> &B)
    {
        Dims dimsA = A.GetDims();

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            const T *rowA = A[itr];
            const T *rowB = B[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
            {
                if (rowA[itc] != rowB[itc])
                    return false;
            }
        }

        return true;
    }

    template <typename T>
    bool operator !=(const Matrix<T> &A, const Matrix<T> &B)
    {
        Dims dimsA = A.GetDims();

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            const T *rowA = A[itr];
            const T *rowB = B[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
            {
                if (rowA[itc] != rowB[itc])
                    return true;
            }
        }

        return false;
    }

    template <typename T>
    bool operator ==(const Matrix<T> &A, T scalar)
    {
        Dims dimsA = A.GetDims();

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            const T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
            {
                if (rowA[itc] != scalar)
                    return false;
            }
        }

        return true;
    }

    template <typename T>
    bool operator !=(const Matrix<T> &A, T scalar)
    {
        Dims dimsA = A.GetDims();

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            const T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
            {
                if (rowA[itc] != scalar)
                    return true;
            }
        }

        return false;
    }

    template <typename T>
    Matrix<T> & operator +=(Matrix<T> &A, const Matrix<T> &B)
    {
        Dims dimsA = A.GetDims();
        Dims dimsB = B.GetDims();

        if (dimsA.Rows != dimsB.Rows || dimsA.Cols != dimsB.Cols)
            throw std::exception("Matrix incompatible");

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowA = A[itr];
            const T *rowB = B[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                rowA[itc] += rowB[itc];
        }

        return A;
    }

    template <typename T>
    Matrix<T> & operator +=(Matrix<T> &A, T scalar)
    {
        Dims dimsA = A.GetDims();

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                rowA[itc] += scalar;
        }

        return A;
    }

    template <typename T>
    Matrix<T> & operator -=(Matrix<T> &A, const Matrix<T> &B)
    {
        Dims dimsA = A.GetDims();
        Dims dimsB = B.GetDims();

        if (dimsA.Rows!= dimsB.Rows || dimsA.Cols != dimsB.Cols)
            throw std::exception("Matrix incompatible");

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowA = A[itr];
            const T *rowB = B[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                rowA[itc] -= rowB[itc];
        }

        return A;
    }

    template <typename T>
    Matrix<T> & operator -=(Matrix<T> &A, T scalar)
    {
        Dims dimsA = A.GetDims();

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                rowA[itc] -= scalar;
        }

        return A;
    }

    template <typename T>
    Matrix<T> & operator *=(Matrix<T> &A, const Matrix<T> &B)
    {
        Dims dimsA = A.GetDims();
        Dims dimsB = B.GetDims();

        if (dimsA.Rows != dimsB.Rows || dimsA.Cols != dimsB.Cols)
            throw std::exception("Matrix incompatible");

        Matrix<T> Acp(A);

        A.ToZeroes();

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowAcp = Acp[itr];
            T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc)
            {
                T const *rowB = B[itc];
                T acpRC = rowAcp[itc];
                for (int inner = 0; inner < dimsB.Cols; inner++)
                    rowA[inner] += acpRC * rowB[inner];
            }
        }

        return A;
    }

    template <typename T>
    Matrix<T> & operator *=(Matrix<T> &A, T scalar)
    {
        Dims dimsA = A.GetDims();

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                rowA[itc] *= scalar;
        }

        return A;
    }

    template <typename T>
    Matrix<T> & operator /=(Matrix<T> &A, T scalar)
    {
        Dims dimsA = A.GetDims();

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                rowA[itc] /= scalar;
        }

        return A;
    }

    template <typename T>
    Matrix<T> operator *(const Matrix<T> &A, const Matrix<T> &B)
    {
        Dims dimsA = A.GetDims();
        Dims dimsB = B.GetDims();

        if (dimsA.Cols != dimsB.Rows)
            throw std::exception("Matrix incompatible");

        Matrix<T> ret(Dims(dimsA.Rows, dimsB.Cols));

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            const T *rowA = A[itr];
            T *rowRet = ret[itr];
            for (int itc = 0; itc < dimsA.Cols; itc)
            {
                const T *rowB = B[itc];
                T aRC = rowA[itc];
                for (int inner = 0; inner < dimsB.Cols; inner++)
                    rowRet[inner] += aRC * rowB[inner];
            }
        }

        return ret;
    }

    template <typename T>
    void HorizSum(Matrix<T> &A, const Matrix<T> &v)
    {
        Dims dimsA = A.GetDims();
        Dims dimsv = v.GetDims();

        if (dimsv.Rows != 1 && dimsv.Cols != dimsA.Rows)
            throw std::exception("Invalid vector");

        const T *rowv = v[0];
        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                rowA[itc] += rowv[itc];
        }
    }

    template <typename T>
    void HorizSub(Matrix<T> &A, const Matrix<T> &v)
    {
        Dims dimsA = A.GetDims();
        Dims dimsv = v.GetDims();

        if (dimsv.Rows != 1 && dimsv.Cols != dimsA.Rows)
            throw std::exception("Invalid vector");

        const T *rowv = v[0];
        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                rowA[itc] -= rowv[itc];
        }
    }

    template <typename T>
    void HorizMul(Matrix<T> &A, const Matrix<T> &v)
    {
        Dims dimsA = A.GetDims();
        Dims dimsv = v.GetDims();

        if (dimsv.Rows != 1 && dimsv.Cols != dimsA.Rows)
            throw std::exception("Invalid vector");

        const T *rowv = v[0];
        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                rowA[itc] *= rowv[itc];
        }
    }

    template <typename T>
    void HorizDiv(Matrix<T> &A, const Matrix<T> &v)
    {
        Dims dimsA = A.GetDims();
        Dims dimsv = v.GetDims();

        if (dimsv.Rows != 1 && dimsv.Cols != dimsA.Rows)
            throw std::exception("Invalid vector");

        const T *rowv = v[0];
        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                rowA[itc] /= rowv[itc];
        }
    }

    template <typename T>
    Matrix<T> operator *(T scalar, const Matrix<T> &A)
    {
        Matrix<T> ret(A);

        ret *= scalar;

        return ret;
    }

    template <typename T>
    Matrix<T> operator *(const Matrix<T> &A, T scalar)
    {
        Matrix<T> ret(A);

        ret *= scalar;

        return ret;
    }

    template <typename T>
    Matrix<T> operator +(const Matrix<T> &A, const Matrix<T> &B)
    {
        Dims dimsA = A.GetDims();
        Dims dimsB = B.GetDims();

        if (dimsA.Rows!= dimsB.Rows || dimsA.Cols != dimsB.Cols)
            throw std::exception("Matrix incompatible");

        Matrix<T> ret(A);

        ret += B;

        return ret;
    }

    template <typename T>
    Matrix<T> operator +(const Matrix<T> &A, T scalar)
    {
        Matrix<T> ret(A);

        ret += scalar;

        return ret;
    }

    template <typename T>
    Matrix<T> operator -(const Matrix<T> &A, const Matrix<T> &B)
    {
        Dims dimsA = A.GetDims();
        Dims dimsB = B.GetDims();

        if (dimsA.Rows != dimsB.Rows || dimsA.Cols != dimsB.Cols)
            throw std::exception("Matrix incompatible");

        Matrix<T> ret(A);

        ret -= B;

        return ret;
    }

    template <typename T>
    Matrix<T> operator -(const Matrix<T> &A, T scalar)
    {
        Matrix<T> ret(A);

        ret -= scalar;

        return ret;
    }

    template <typename T>
    Matrix<T> operator /(const Matrix<T> &A, T scalar)
    {
        Matrix<T> ret(A);

        ret /= scalar;

        return ret;
    }

    template <typename T>
    Matrix<T> HorizSumEd(const Matrix<T> &A, const Matrix<TFLOAT> &v)
    {
        Matrix<T> ret(A);

        HorizSum(ret, v);

        return ret;
    }

    template <typename T>
    Matrix<T> HorizSubEd(const Matrix<T> &A, const Matrix<TFLOAT> &v)
    {
        Matrix<T> ret(A);

        HorizSub(ret, v);

        return ret;
    }

    template <typename T>
    Matrix<T> HorizMulEd(const Matrix<T> &A, const Matrix<TFLOAT> &v)
    {
        Matrix<T> ret(A);

        HorizMul(ret, v);

        return ret;
    }

    template <typename T>
    Matrix<T> HorizDivEd(const Matrix<T> &A, const Matrix<TFLOAT> &v)
    {
        Matrix<T> ret(A);

        HorizDiv(ret, v);

        return ret;
    }

    template <typename T>
    Matrix<T> Transpose(const Matrix<T> &A)
    {
        Dims dimsA = A.GetDims();

        Matrix<T> ret(Dims(dimsA.Cols, dimsA.Rows));

        for (int itr = 0; itr < dimsA.Rows; itr++)
        {
            const T *rowA = A[itr];
            for (int itc = 0; itc < dimsA.Cols; itc++)
                ret[itc][itr] = rowA[itc];
        }

        return ret;
    }

    template <typename T>
    Matrix<T> Invert(const Matrix<T> &A)
    {
        throw std::exception("Not implemented");
    }

    template <typename T>
    T Determinant(const Matrix<T> &A)
    {
        Matrix<T>::LUDecomposition luDecomposition(A);
        return luDecomposition.GetDeterminant();
    }
} }
