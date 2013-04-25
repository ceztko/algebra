#pragma once

#include <RTMatrix.h>

#include "CommonsW.h"

using namespace System;
using namespace Algebra::Linear;
using namespace NET::Persistence;
using namespace System::Runtime::InteropServices;

#pragma make_public(::RTMatrix)

namespace Interop { namespace Algebra { namespace Linear
{
    public ref class RTMatrix : IPersistable
    {
    private:
        ::RTMatrix *_wrapped;
    public:
        RTMatrix()
        {
            _wrapped = new ::RTMatrix();
        }
        RTMatrix(const ::RTMatrix &matrix)
        {
            _wrapped = new ::RTMatrix(matrix);
        }
        RTMatrix(array<TFLOAT> ^m)
        {
            TFLOAT _m[12];
            Marshal::Copy(m, 0, IntPtr(_m), 12);
            _wrapped = new ::RTMatrix(_m);
        }
        RTMatrix(array<TFLOAT> ^rotation, array<TFLOAT> ^translation)
        {
            TFLOAT _rotation[9];
            Marshal::Copy(rotation, 0, IntPtr(_rotation), 9);

            TFLOAT _translation[3];
            Marshal::Copy(translation, 0, IntPtr(_translation), 3);

            _wrapped = new ::RTMatrix(_rotation, _translation);
        }
        !RTMatrix()
        {
            delete _wrapped;
        }
        property TFLOAT R11
        {
            TFLOAT get() { return (*_wrapped)[0][0];}
        }
        property TFLOAT R12
        {
            TFLOAT get() { return (*_wrapped)[0][1];}
        }
        property TFLOAT R13
        {
            TFLOAT get() { return (*_wrapped)[0][2];}
        }
        property TFLOAT R21
        {
            TFLOAT get() { return (*_wrapped)[1][0];}
        }
        property TFLOAT R22
        {
            TFLOAT get() { return (*_wrapped)[1][1];}
        }
        property TFLOAT R23
        {
            TFLOAT get() { return (*_wrapped)[1][2];}
        }
        property TFLOAT R31
        {
            TFLOAT get() { return (*_wrapped)[2][0];}
        }
        property TFLOAT R32
        {
            TFLOAT get() { return (*_wrapped)[2][1];}
        }
        property TFLOAT R33
        {
            TFLOAT get() { return (*_wrapped)[2][2];}
        }
        property TFLOAT TX
        {
            TFLOAT get() { return (*_wrapped)[0][3];}
        }
        property TFLOAT TY
        {
            TFLOAT get() { return (*_wrapped)[1][3];}
        }
        property TFLOAT TZ
        {
            TFLOAT get() { return (*_wrapped)[2][3];}
        }
		/*
        void Assign(const ::RTMatrix &matrix)
        {
            *_wrapped = matrix;
        }
        void Assign(RTMatrix ^matrix)
        {
            *_wrapped = *matrix->_wrapped;
        }*/
        void Assign(array<TFLOAT> ^m)
        {
            TFLOAT _m[12];
            Marshal::Copy(m, 0, IntPtr(_m), 12);
            _wrapped->Assign(_m);
        }
        void Assign(array<TFLOAT> ^rotation, array<TFLOAT> ^translation)
        {
            TFLOAT _rotation[9];
            TFLOAT *__rotation;
            if (rotation == nullptr)
                __rotation = NULL;
            else
            {
                Marshal::Copy(rotation, 0, IntPtr(_rotation), 9);
                __rotation = _rotation;
            }

            TFLOAT _translation[3];
            TFLOAT *__translation;
            if (rotation == nullptr)
                __translation = NULL;
            else
            {
                Marshal::Copy(translation, 0, IntPtr(_translation), 3);
                __translation = _translation;
            }

            _wrapped->Assign(__rotation, __translation);
        }
        void GetRotation(array<TFLOAT> ^%rotation)
        {
            if (rotation == nullptr)
                rotation = gcnew array<TFLOAT>(9);

            TFLOAT _rotation[9];
            _wrapped->GetRotation(_rotation);

            Marshal::Copy(IntPtr(_rotation), rotation, 0, 9);
        }
        void GetTranslation(array<TFLOAT> ^%translation)
        {
            if (translation == nullptr)
                translation = gcnew array<TFLOAT>(3);

            TFLOAT _translation[3];
            _wrapped->GetTranslation(_translation);

            Marshal::Copy(IntPtr(_translation), translation, 0, 3);
        }
        property TFLOAT default[int,int]
        {
	        TFLOAT get(int row, int col)
            {
                if (row < 0 || row > 3 || col < 0 || col > 3)
                    throw gcnew Exception("Matrix bounds violation");

                return (*_wrapped)[row][col];
            }
        }
        operator ::RTMatrix &()
        {
            return *_wrapped;
        }
        virtual void Serialize(SerializerStream ^writer)
        {
            // Rotation
            writer->WriteElement("R11", (*_wrapped)[0][0]);
            writer->WriteElement("R12", (*_wrapped)[0][1]);
            writer->WriteElement("R13", (*_wrapped)[0][2]);
            writer->WriteElement("R21", (*_wrapped)[1][0]);
            writer->WriteElement("R22", (*_wrapped)[1][1]);
            writer->WriteElement("R23", (*_wrapped)[1][2]);
            writer->WriteElement("R31", (*_wrapped)[2][0]);
            writer->WriteElement("R32", (*_wrapped)[2][1]);
            writer->WriteElement("R33", (*_wrapped)[2][2]);
            // Translation
            writer->WriteElement("TX", (*_wrapped)[0][3]);
            writer->WriteElement("TY", (*_wrapped)[1][3]);
            writer->WriteElement("TZ", (*_wrapped)[2][3]);
        }
        virtual void Deserialize(DeserializerStream ^reader)
        {
            TFLOAT m[4][4];

            // Rotation
            reader->ReadElementAs(m[0][0]);
            reader->ReadElementAs(m[0][1]);
            reader->ReadElementAs(m[0][2]);
            reader->ReadElementAs(m[1][0]);
            reader->ReadElementAs(m[1][1]);
            reader->ReadElementAs(m[1][2]);
            reader->ReadElementAs(m[2][0]);
            reader->ReadElementAs(m[2][1]);
            reader->ReadElementAs(m[2][2]);
            // Translation
            reader->ReadElementAs(m[0][3]);
            reader->ReadElementAs(m[1][3]);
            reader->ReadElementAs(m[2][3]);

            _wrapped->Assign(m[0]);
        }
        virtual void SetInitList(array<Object ^> ^%args)
        {
        }
        virtual void Revise(ReviseMode mode)
        {
            switch (mode)
            {
                case ReviseMode::INIT:
                {
                    _wrapped = new ::RTMatrix();
                    break;
                }
            }
        }
    };
} } }
