#ifndef MATRIXTEST_MATRIXOPTIONS_H
#define MATRIXTEST_MATRIXOPTIONS_H

enum MatrixOptions {
    DefaultOptions         = 0, // horizontal serpentine layout. first pixel is top-left

    MatrixHorizontal       = 0b0000, // stripe is left to right
    MatrixVertical         = 0b0001, // stripe is top down

    MatrixSerpentine       = 0b0000, // rows/cols change direction
    MatrixStraight         = 0b0010, // all rows/cols follow same direction

    MatrixInvertVertical   = 0b0100, // first pixel is on bottom
    MatrixInvertHorizontal = 0b1000, // first pixel is right instead of left

    MatrixRotate_0         = 0b00000000,
    MatrixRotate_90        = 0b00010000,
    MatrixRotate_180       = 0b00100000,
    MatrixRotate_270       = 0b01000000,
};

#endif //MATRIXTEST_MATRIXOPTIONS_H
