#pragma once

// A simple 3D vector with x, y and z components.
//
// The components are kept private (encapsulation): outside code cannot touch
// them directly, it has to go through the public functions below. This lets us
// change how the vector works internally later without breaking other code.
class Vector {
public:
    // Create a vector. Defaults to (0, 0, 0) if no values are given.
    Vector(double x = 0.0, double y = 0.0, double z = 0.0);

    // Read-only access to each component (getters).
    double x() const;
    double y() const;
    double z() const;

    // Return a new vector that is this vector plus the other one.
    // Lets you write: Vector c = a + b;
    Vector operator+(const Vector& other) const;

    // Return a new vector that is this vector minus the other one.
    // Lets you write: Vector c = a - b;
    Vector operator-(const Vector& other) const;

    // Return a new vector that is this vector scaled by a number.
    // Lets you write: Vector c = a * 2;
    Vector operator*(double scalar) const;

    // The dot product of this vector and the other one.
    double dot(const Vector& other) const;

    // The length (magnitude) of this vector.
    double length() const;

    // This vector divided by its own length: same direction, length 1.
    Vector normalised() const;

private:
    double _x;
    double _y;
    double _z;
};
