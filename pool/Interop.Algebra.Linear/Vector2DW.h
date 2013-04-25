#pragma once

#include <Vector2D.h>

#include "CommonsW.h"

using namespace System;
using namespace Algebra::Linear;
using namespace NET::Persistence;

#pragma make_public(::Vector2D)

namespace Interop { namespace Algebra { namespace Linear
{
    public interface class IVector2D
    {
        property TFLOAT X
        {
            TFLOAT get();
        }
        property TFLOAT Y
        {
            TFLOAT get();
        }
    };

    public value struct Vector2D : IVector2D, IPersistable
    {
    private:
        TFLOAT _X;
        TFLOAT _Y;
    public:
        Vector2D(TFLOAT x, TFLOAT y)
        {
            _X = x;
            _Y = y;
        }
        Vector2D(const ::Vector2D &u)
        {
            _X = u.X;
            _Y = u.Y;
        }
		/*
		operator ::Vector2D()
		{
			return ::Vector2D(_X, _Y);
		}*/
        property TFLOAT X
        {
	        virtual TFLOAT get() { return _X; }
            void set(TFLOAT value) { _X = value; }
        }
        property TFLOAT Y
        {
	        virtual TFLOAT get() { return _Y; }
            void set(TFLOAT value) { _X = value; }
        }
        property TFLOAT default[Axis2D]
        {
	        TFLOAT get(Axis2D axis)
            {
                switch (axis)
                {
                    case Axis2D::X:
                        return _X;
                    case Axis2D::Y:
                        return _Y;
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
                    default:
                        throw gcnew Exception("Invalid index");
                }
            }
        }
        static Vector2D operator +(Vector2D u)
        {
            return Vector2D(u.X, u.Y);
        }
        static Vector2D operator -(Vector2D u)
        {
            return Vector2D(-u.X, -u.Y);
        }
        static Vector2D operator +(Vector2D u, Vector2D v)
        {
            return Vector2D(u.X + v.X, u.Y + v.Y);
        }
        static Vector2D operator -(Vector2D u, Vector2D v)
        {
            return Vector2D(u.X - v.X, u.Y - v.Y);
        }
        static Vector2D operator *(Vector2D u, TFLOAT scalar)
        {
            return Vector2D(u.X * scalar, u.Y * scalar);
        }
        static Vector2D operator /(Vector2D u, TFLOAT scalar)
        {
            return Vector2D(u.X / scalar, u.Y / scalar);
        }
        static TFLOAT operator *(Vector2D u, Vector2D v)
        {
            return u.X * v.X + u.Y * v.Y;
        }
        static TFLOAT operator ^(Vector2D u, Vector2D v)
        {
            return u.X * v.X - u.Y * v.Y;
        }
        virtual void Serialize(SerializerStream ^writer)
        {
            writer->WriteElement("X", _X);
            writer->WriteElement("Y", _Y);
        }
        virtual void Deserialize(DeserializerStream ^reader)
        {
            reader->ReadElementAs(_X);
            reader->ReadElementAs(_Y);
        }
        virtual void SetInitList(array<Object ^> ^%args)
        {
        }
        virtual void Revise(ReviseMode mode)
        {
        }
    };
} } }
