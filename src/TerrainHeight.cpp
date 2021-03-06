/*
 * @file
 * @author Vsevolod (Seva) Ivanov
*/

#include "TerrainHeight.hpp"

TerrainHeight::TerrainHeight():
    OCTAVES(4), AMPLITUDE(6.0f), IRREGULARITY(0.5f),
    SEED(rand() % (unsigned int)pow(10, 10))
{
}

//! Generate terrain height (y) using x >= 0 and y >= 0
float TerrainHeight::get(const float x, const float z)
{
    if (x <= 0.000000 && z <= 0.000000)
        return 0.00;

    float height = 0;
    float divisor = (float) pow(2, this->OCTAVES - 1);

    for (int octave = 0; octave < this->OCTAVES; octave++)
    {
        float frequency = (float) (pow(2, octave) / divisor);

        float amplitude = (float) pow(this->IRREGULARITY, octave) * AMPLITUDE;

        height += inoise(x * frequency, z * frequency) * amplitude;
    }

    return height;
}

void TerrainHeight::setAmplitude(float a)
{
    this->AMPLITUDE = a;
}

// Private

//! Smooth noise
float TerrainHeight::snoise(float x, float z)
{
    // dividor reduces their influence
    // corners
    float c = noise(x-1, z+1) + noise(x+1, z+1) +
              noise(x-1, z-1) + noise(x+1, z-1);
    c /= 16;
    // sides
    float s = noise(x-1, z) + (x, z-1) +
              noise(x+1, z) + (x, z+1);
    s /= 8;
    // middle
    float m = noise(x, z);
    m /= 4;
    // combined influence
    return c + s + m;
}

//! Sharp noise
float TerrainHeight::noise(const float x, const float z)
{
    // set random seed
    srand(x * 6786 + z * 23054 + this->SEED);
    return this->randf(1.0f) * 2 - 1;
}

float TerrainHeight::inoise(float x, float z)
{
    // noise input
    int ix = (int) x; float fx = x - ix;
    int iz = (int) z; float fz = z - iz;
    // smooth noise
    float n  = snoise   (ix,   iz);
    float n2 = snoise   (ix+1, iz);
    float n3 = snoise   (ix,   iz+1);
    float n4 = snoise   (ix+1, iz+1);
    // interpolated curves
    float i1 = icurve  (n,    n2,  fx);
    float i2 = icurve  (n3,   n4,  fx);
    return     icurve  (i1,   i2,  fz);
}

//! Interpolated curve
float TerrainHeight::icurve(float a, float b, float bl)
{
    double angle = bl * M_PI;
    float f = (float)(1.0f - cos(angle)) * 0.5f;
    return a * (1.0f - f) + b * f;
}

//! Random float in range : [0, upperBound]
float TerrainHeight::randf(const unsigned int upperBound)
{
    return static_cast <float> (
        rand() / (static_cast <float> (RAND_MAX / upperBound))
    );
}
