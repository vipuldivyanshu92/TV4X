#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

/* RGB Format Conversion Tables */
double tvxx_rgb24_to_rgb24[3] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000  };
double tvxx_rgb24_to_rgb16[3] = {0.1215686274509804, 0.2470588235294118, 0.1215686274509804  };
double tvxx_rgb24_to_rgb15[3] = {0.1215686274509804, 0.1215686274509804, 0.1215686274509804  };
double tvxx_rgb16_to_rgb24[3] = {8.2258064516129039, 4.0476190476190474, 8.2258064516129039  };
double tvxx_rgb16_to_rgb16[3] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000  };
double tvxx_rgb16_to_rgb15[3] = {1.0000000000000000, 0.4920634920634920, 1.0000000000000000  };
double tvxx_rgb15_to_rgb24[3] = {8.2258064516129039, 8.2258064516129039, 8.2258064516129039  };
double tvxx_rgb15_to_rgb16[3] = {1.0000000000000000, 2.0322580645161290, 1.0000000000000000  };
double tvxx_rgb15_to_rgb15[3] = {1.0000000000000000, 1.0000000000000000, 1.0000000000000000  };

/* RGB15 Format Definition */
struct tvxx_rgb_format tvxx_rgb_format_rgb15 = {
    0x1f,           /* r_mask */
    0x1f,           /* g_mask */
    0x1f,           /* b_mask */
    
    10,          /* r_shift */
    5,           /* g_shift */
    0,           /* b_shift */
    
    &tvxx_rgb15_to_rgb24,   /* to RGB24 conversion table */
    &tvxx_rgb15_to_rgb16,   /* to RGB16 conversion table */
    &tvxx_rgb15_to_rgb15,   /* to RGB15 conversion table */
};

/* RGB16 Format Definition */
struct tvxx_rgb_format tvxx_rgb_format_rgb16 = {
    0x1f,           /* r_mask */
    0x3f,           /* g_mask */
    0x1f,           /* b_mask */
    
    11,          /* r_shift */
    5,           /* g_shift */
    0,           /* b_shift */
    
    &tvxx_rgb16_to_rgb24,   /* to RGB24 conversion table */
    &tvxx_rgb16_to_rgb16,   /* to RGB16 conversion table */
    &tvxx_rgb16_to_rgb15,   /* to RGB15 conversion table */
};

/* RGB24 Format Definition */
struct tvxx_rgb_format tvxx_rgb_format_rgb24 = {
    0xff,           /* r_mask */
    0xff,           /* g_mask */
    0xff,           /* b_mask */
    
    16,          /* r_shift */
    8,           /* g_shift */
    0,           /* b_shift */
    
    &tvxx_rgb24_to_rgb24,   /* to RGB24 conversion table */
    &tvxx_rgb24_to_rgb16,   /* to RGB16 conversion table */
    &tvxx_rgb24_to_rgb15,   /* to RGB15 conversion table */
};

/* Lookup table for rgb_conversion_table() */
struct format_lookup_table {
    struct tvxx_rgb_format *in;
    struct tvxx_rgb_format *out;
    double (*cnvtable)[3];
};

static struct format_lookup_table fmt_lk_table[] = {
    {&tvxx_rgb_format_rgb15, &tvxx_rgb_format_rgb15, &tvxx_rgb15_to_rgb15},
    {&tvxx_rgb_format_rgb15, &tvxx_rgb_format_rgb16, &tvxx_rgb15_to_rgb16},
    {&tvxx_rgb_format_rgb15, &tvxx_rgb_format_rgb24, &tvxx_rgb15_to_rgb24},
    {&tvxx_rgb_format_rgb16, &tvxx_rgb_format_rgb15, &tvxx_rgb16_to_rgb15},
    {&tvxx_rgb_format_rgb16, &tvxx_rgb_format_rgb16, &tvxx_rgb16_to_rgb16},
    {&tvxx_rgb_format_rgb16, &tvxx_rgb_format_rgb24, &tvxx_rgb16_to_rgb24},
    {&tvxx_rgb_format_rgb24, &tvxx_rgb_format_rgb15, &tvxx_rgb24_to_rgb15},
    {&tvxx_rgb_format_rgb24, &tvxx_rgb_format_rgb16, &tvxx_rgb24_to_rgb16},
    {&tvxx_rgb_format_rgb24, &tvxx_rgb_format_rgb24, &tvxx_rgb24_to_rgb24},
};

/**
* Get conversion table for in/out format, using simple array search.
*
* @param    struct tv4x_rgb_format *in
* @param    struct tv4x_rgb_format *out
* @param    double (*cnvtable)[3]
* @return   1 on success, 0 on error
**/
int tvxx_rgb_get_conversion_table(
            struct tvxx_rgb_format *in,
            struct tvxx_rgb_format *out,
            double (*cnvtable)[3]) {
    
    int i, len;
    
    len = sizeof(fmt_lk_table)/sizeof(fmt_lk_table[0]);
    for (i = 0; i < len; i++) {
        if (in == fmt_lk_table[i].in && out == fmt_lk_table[i].out) {
            memcpy(cnvtable, fmt_lk_table[i].cnvtable, sizeof(*cnvtable));
            return 1;
        }
    }
    
    return 0;
}

/**
* Convert between various RGB formats.
*
* @param    struct tvxx_rgb_format *in_fmt
* @param    struct tvxx_rgb_format *out_fmt
* @param    uint32_t *in
* @param    uint32_t *out
* @param    uint32_t size
* @return   void
**/
void tvxx_rgb_convert(
                    struct tvxx_rgb_format *in_fmt,
                    struct tvxx_rgb_format *out_fmt,
                    uint32_t *in,
                    uint32_t *out,
                    uint32_t size) {
    
    uint32_t i;
    float r, g, b;
    
    /* Calculate scales */
    float   rs = (float)out_fmt->r_mask / (float)in_fmt->r_mask,
            gs = (float)out_fmt->g_mask / (float)in_fmt->g_mask,
            bs = (float)out_fmt->b_mask / (float)in_fmt->b_mask;
    
    for (i = 0; i < size; i++) {
        /* Unpack RGB */
        r = in[i] >> in_fmt->r_shift & in_fmt->r_mask;
        g = in[i] >> in_fmt->g_shift & in_fmt->g_mask;
        b = in[i] >> in_fmt->b_shift & in_fmt->b_mask;
        
        /* Scale */
        r *= rs;
        g *= gs;
        b *= bs;
        
        /* Clamp */
        CLAMP(r, 0, out_fmt->r_mask);
        CLAMP(g, 0, out_fmt->g_mask);
        CLAMP(b, 0, out_fmt->b_mask);
        
        /* Pack into out buffer */
        out[i] =    (uint8_t)r << out_fmt->r_shift |
                    (uint8_t)g << out_fmt->g_shift |
                    (uint8_t)b << out_fmt->b_shift;
    }
}
