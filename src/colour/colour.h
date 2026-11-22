#pragma once

// A colour with red, green and blue components, nominally between 0 and 1.
// Its own class, not a Vector (see ADR 0007): the compiler then refuses to
// add a colour to a position.
class Colour {
public:
    Colour(double r = 0.0, double g = 0.0, double b = 0.0);

    double r() const;
    double g() const;
    double b() const;

private:
    double _r;
    double _g;
    double _b;
};

// t * colour: scales each component, e.g. by a brightness.
Colour operator*(double t, const Colour& colour);
