#pragma once

// A colour with red, green and blue components.
class Colour {
public:
    // Create a colour. Defaults to (0, 0, 0) if no values are given.
    Colour(double r = 0.0, double g = 0.0, double b = 0.0);

    // Read-only access to each component (getters).
    double r() const;
    double g() const;
    double b() const;

    // Return a new colour that is this colour scaled by a number.
    // Lets you write: Colour c = a * 0.5;
    Colour operator*(double scalar) const;

private:
    double _r;
    double _g;
    double _b;
};
