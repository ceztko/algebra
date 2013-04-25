#pragma once

#include <Dims.h>

using namespace System;
using namespace Algebra::Linear;
using namespace NET::Persistence;

#pragma make_public(::Dims)

namespace Interop { namespace Algebra { namespace Linear
{
    public value struct Dims : IPersistable
    {
    public:
        int Rows;
        int Cols;
        Dims(const ::Dims &dims)
        {
            Rows = dims.Rows;
            Cols = dims.Cols;
        }
        Dims(int rows, int cols)
        {
            Rows = rows;
            Cols = cols;
        }
        operator ::Dims()
        {
            return ::Dims(Rows, Cols);
        }
        virtual void Serialize(SerializerStream ^writer)
        {
            writer->WriteElement("Rows", Rows);
            writer->WriteElement("Cols", Cols);
        }
        virtual void Deserialize(DeserializerStream ^reader)
        {
            reader->ReadElementAs(Rows);
            reader->ReadElementAs(Cols);
        }
        virtual void SetInitList(array<Object ^> ^%args)
        {
        }
        virtual void Revise(ReviseMode mode)
        {
        }
    };    
} } }
