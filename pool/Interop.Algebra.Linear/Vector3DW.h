#pragma once

#include <Vector3D.h>

#include "CommonsW.h"

using namespace System;
using namespace Algebra::Linear;
using namespace NET::Persistence;

#pragma make_public(::Vector3D)

namespace Interop { namespace Algebra { namespace Linear
{
    public interface class IVector3D
    {
        property TFLOAT X
        {
            TFLOAT get();
        }
        property TFLOAT Y
        {
            TFLOAT get();
        }
        property TFLOAT Z
        {
            TFLOAT get();
        }
    };

    public value struct Vector3D : IPersistableItem
    {
    private:
        TFLOAT _X;
        TFLOAT _Y;
        TFLOAT _Z;
    public:
        Vector3D(TFLOAT x, TFLOAT y, TFLOAT z)
        {
            _X = x;
            _Y = y;
            _Z = z;
        }
        Vector3D(const ::Vector3D &u)
        {
            _X = u.X;
            _Y = u.Y;
            _Z = u.Z;
        }
        operator ::Vector3D()
        {
            return ::Vector3D(_X, _Y, _Z);
        }
        property TFLOAT X
        {
	        virtual TFLOAT get() { return _X; }
            void set(TFLOAT value) { _X = value; }
        }
        property TFLOAT Y
        {
	        virtual TFLOAT get() { return _Y; }
            void set(TFLOAT value) { _Y = value; }
        }
        property TFLOAT Z
        {
	        virtual TFLOAT get() { return _Z; }
            void set(TFLOAT value) { _Z = value; }
        }
        property TFLOAT default[Axis2D]
        {
	        TFLOAT get(Axis3D axis)
            {
                switch (axis)
                {
                    case Axis3D::X:
                        return _X;
                    case Axis3D::Y:
                        return _Y;
                    case Axis3D::Z:
                        return _Z;
                    default:
                        throw gcnew Exception("Invalid axis");
                }
            }
        }
        property TFLOAT default[int]
        {
	        TFLOAT get(int index)
            {
                switch (index)
                {
                    case 0:
                        return _X;
                    case 1:
                        return _Y;
                    case 2:
                        return _Z;
                    default:
                        throw gcnew Exception("Invalid index");
                }
            }
        }
        static Vector3D operator +(Vector3D u)
        {
            return Vector3D(u.X, u.Y, u.Z);
        }
        static Vector3D operator -(Vector3D u)
        {
            return Vector3D(-u.X, -u.Y, -u.Z);
        }
        static Vector3D operator +(Vector3D u, Vector3D v)
        {
            return Vector3D(u.X + v.X, u.Y + v.Y, u.Z + v.Z);
        }
        static Vector3D operator -(Vector3D u, Vector3D v)
        {
            return Vector3D(u.X - v.X, u.Y - v.Y, u.Z - v.Z);
        }
        static Vector3D operator *(Vector3D u, TFLOAT scalar)
        {
            return Vector3D(u.X * scalar, u.Y * scalar, u.Z * scalar);
        }
        static Vector3D operator /(Vector3D u, TFLOAT scalar)
        {
            return Vector3D(u.X / scalar, u.Y / scalar, u.Z * scalar);
        }
        static TFLOAT operator *(Vector3D u, Vector3D v)
        {
            return u.X * v.X + u.Y * v.Y + u.Z * v.Z;
        }
        static Vector3D operator ^(Vector3D u, Vector3D v)
        {
            TFLOAT uX = u.X;
            TFLOAT uY = u.Y;
            TFLOAT uZ = u.Z;
            TFLOAT vX = v.X;
            TFLOAT vY = v.Y;
            TFLOAT vZ = v.Z;

            return Vector3D(
                uY * vZ - uZ * vY,
                uZ * vX - uX * vZ,
                uX * vY - uY * vX);
        }
        virtual void Serialize(SerializerStream ^writer)
        {
            writer->WriteElement("X", _X);
            writer->WriteElement("Y", _Y);
            writer->WriteElement("Z", _Z);
        }
        virtual void Deserialize(DeserializerStream ^reader)
        {
            reader->ReadElementAs(_X);
            reader->ReadElementAs(_Y);
            reader->ReadElementAs(_Z);
        }
        virtual void SetInitList(array<Object ^> ^%args)
        {
        }
        virtual void Revise(ReviseMode mode)
        {
        }
    };
} } }
