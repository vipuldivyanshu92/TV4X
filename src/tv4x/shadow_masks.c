
/*

One of the advantages to using matrix multiplication for scaling, is that it's
incredibly simple to create new pixel layouts. Each pixel layout consists of
two components: a primary matrix, which is applied to all RGB channels, and a
secondary "Phosphor" matrix, which can be used to apply phosphor on top of the
primary matrix. For debugging, there are passthru matrices, for both primary
and phosphor, so that it's easier to track down problems while building out
new pixel layouts.

*/

// Pasthru Phosphor
float tv4x_crt_passthru_phosphor[2][16][3] = {{
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
}, {
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
}};

// Passthru Matrix
float tv4x_crt_passthru[2][16] = {{
        1.00f, 1.00f, 1.00f, 1.00f,
        1.00f, 1.00f, 1.00f, 1.00f,
        1.00f, 1.00f, 1.00f, 1.00f,
        1.00f, 1.00f, 1.00f, 1.00f,
    }, {
        1.00f, 1.00f, 1.00f, 1.00f,
        1.00f, 1.00f, 1.00f, 1.00f,
        1.00f, 1.00f, 1.00f, 1.00f,
        1.00f, 1.00f, 1.00f, 1.00f,
}};

// Slot Mask RGB Phosphor Layout
float tv4x_crt_slotmask_phosphor[2][16][3] = {{
        {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f}, {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f},
        {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f}, {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f},
        {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f}, {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
}, {
        {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f},
        {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f},
        {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f},
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
}};

// Slot Mask Matrix
float tv4x_crt_slotmask[2][16] = {{
        1.25f, 1.25f, 1.25f, 1.00f,
        1.30f, 1.30f, 1.30f, 1.00f,
        0.85f, 0.85f, 0.85f, 0.75f,
        0.85f, 0.85f, 0.85f, 0.75f
    }, {
        1.25f, 1.00f, 1.25f, 1.25f,
        1.30f, 1.00f, 1.30f, 1.30f,
        0.85f, 0.75f, 0.85f, 0.85f,
        0.85f, 0.75f, 0.85f, 0.85f
}};

// Scanline Phosphor
float tv4x_crt_scanline_phosphor[2][16][3] = {{
        {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f}, {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f},
        {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f}, {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f},
        {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f}, {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f},
        {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f}, {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f},
}, {
        {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f},
        {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f},
        {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f},
        {-5.0f, -5.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {5.0f, -5.0f, -5.0f}, {-5.0f, 5.0f, -5.0f},
}};

// Scanline Matrix
float tv4x_crt_scanline[2][16] = {{
        1.20f, 1.20f, 1.20f, 1.20f,
        1.30f, 1.30f, 1.30f, 1.30f,
        0.80f, 0.80f, 0.80f, 0.80f,
        0.70f, 0.70f, 0.70f, 0.70f,
    }, {
        1.20f, 1.20f, 1.20f, 1.20f,
        1.30f, 1.30f, 1.30f, 1.30f,
        0.80f, 0.80f, 0.80f, 0.80f,
        0.70f, 0.70f, 0.70f, 0.70f,
}};

// Silly Phosphor
float tv4x_crt_silly_phosphor[2][16][3] = {{
        {0.0f, 0.0f, 0.0f}, {10.0f, -10.0f, -10.0f}, {10.0f, -10.0f, -10.0f}, {0.0f, 0.0f, 0.0f},
        {-10.0f, 10.0f, -10.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {-10.0f, 10.0f, -10.0f},
        {-10.0f, 10.0f, -10.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {-10.0f, 10.0f, -10.0f},
        {0.0f, 0.0f, 0.0f}, {-10.0f, -10.0f, 10.0f}, {-10.0f, -10.0f, 10.0f}, {0.0f, 0.0f, 0.0f},
}, {
        {0.0f, 0.0f, 0.0f}, {10.0f, -10.0f, -10.0f}, {10.0f, -10.0f, -10.0f}, {0.0f, 0.0f, 0.0f},
        {-10.0f, 10.0f, -10.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {-10.0f, 10.0f, -10.0f},
        {-10.0f, 10.0f, -10.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {-10.0f, 10.0f, -10.0f},
        {0.0f, 0.0f, 0.0f}, {-10.0f, -10.0f, 10.0f}, {-10.0f, -10.0f, 10.0f}, {0.0f, 0.0f, 0.0f},
}};

// Silly Matrix
float tv4x_crt_silly[2][16] = {{
        0.50f, 1.20f, 1.20f, 0.50f,
        1.20f, 0.80f, 0.50f, 1.20f,
        1.20f, 0.50f, 0.50f, 1.20f,
        0.50f, 1.20f, 1.20f, 0.50f,
    }, {
        0.50f, 1.20f, 1.20f, 0.50f,
        1.20f, 0.80f, 0.50f, 1.20f,
        1.20f, 0.50f, 0.50f, 1.20f,
        0.50f, 1.20f, 1.20f, 0.50f,
}};
