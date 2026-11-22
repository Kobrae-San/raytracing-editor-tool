#pragma once

// A 3D vector, used both for points and for directions (see ADR 0008).
// Immutable: private components, no setters, and every operation returns a
// new Vector.
class Vector {
public:
    Vector(double x = 0.0, double y = 0.0, double z = 0.0);

    double x() const;
    double y() const;
    double z() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    double dot(const Vector& other) const;
    double length() const;

    // Same direction, length 1. The zero vector has no direction: the result
    // is NaN (parked until a caller needs another behaviour).
    Vector normalised() const;

private:
    double _x;
    double _y;
    double _z;
};

// t * v: a free function because the left operand is a number, not a Vector.
// Named t as in the ray equation O + t * D.
Vector operator*(double t, const Vector& vector);
