/** FILE AUTOGENERATED BY package-tvxx.py **/

/* include/tvxx_internal.h */

#ifndef TVXX_INTERNAL_H
#define TVXX_INTERNAL_H

#if defined(_MSC_VER)
    #define TVXX_INLINE __forceinline
    #define TVXX_RESTRICT
#elif defined(__GNUC__)
    #define TVXX_INLINE __inline
    #define TVXX_RESTRICT __restrict__
#elif defined(__clang__)
    #define TVXX_INLINE __inline
    #define TVXX_RESTRICT __restrict__
#else
    #define TVXX_INLINE
    #define TVXX_RESTRICT
#endif

/* Input/Output Data Types */
#ifndef tv4x_in_type
    #define tv4x_in_type uint32_t
#endif

#ifndef tv4x_out_type
    #define tv4x_out_type uint32_t
#endif

/* Input/Output Data Types */
#ifndef tv2x_in_type
    #define tv2x_in_type uint32_t
#endif

#ifndef tv2x_out_type
    #define tv2x_out_type uint32_t
#endif

/* TVXX_INTERNAL_H */ #endif

/* include/rgb.h */

#ifndef TVXX_RGB_H
#define TVXX_RGB_H

#include <stdint.h>

#ifdef __cplusplus
    extern "C" {
#endif

/*
    Common packed video formats are as follows:
    
    FMT   | R Bits | G Bits | B Bits  |
    ______|________|________|_________|
    RGB15 |    5   |    5   |    5    |
    RGB16 |    5   |    6   |    5    |
    RGB24 |    8   |    8   |    8    |

*/

/* Packed RGB Format. */
struct tvxx_rgb_format {
    uint8_t r_mask;
    uint8_t g_mask;
    uint8_t b_mask;
    
    uint8_t r_shift;
    uint8_t g_shift;
    uint8_t b_shift;
    
    double (*to_rgb24)[3];
    double (*to_rgb16)[3];
    double (*to_rgb15)[3];
};

/* Various RGB Formats */
extern struct tvxx_rgb_format tvxx_rgb_format_rgb15;
extern struct tvxx_rgb_format tvxx_rgb_format_rgb16;
extern struct tvxx_rgb_format tvxx_rgb_format_rgb24;

extern double tvxx_rgb24_to_rgb24[3];
extern double tvxx_rgb24_to_rgb16[3];
extern double tvxx_rgb24_to_rgb15[3];
extern double tvxx_rgb16_to_rgb24[3];
extern double tvxx_rgb16_to_rgb16[3];
extern double tvxx_rgb16_to_rgb15[3];
extern double tvxx_rgb15_to_rgb24[3];
extern double tvxx_rgb15_to_rgb16[3];
extern double tvxx_rgb15_to_rgb15[3];

/* Get RGB conversion table for in/out combination. Result copied into
   cnvtable, which is a pointer to an array of double with 3 elements. */
int rgb_get_conversion_table(
            struct tvxx_rgb_format *in,
            struct tvxx_rgb_format *out,
            double (*cnvtable)[3]);

/* Convert between RGB formats */
void rgb_convert(
                    struct tvxx_rgb_format *in_fmt,
                    struct tvxx_rgb_format *out_fmt,
                    uint32_t *in,
                    uint32_t *out,
                    uint32_t size);

/* Pack RGB */
#define PACK_RGB(r, g, b, fmt, out)\
    (out) =     (r) << (fmt).r_shift |\
                (g) << (fmt).g_shift |\
                (b) << (fmt).b_shift;

/* Pack RGB with RGB Conversion Matrix */
#define PACK_RGB_CONV(r, g, b, fmt, conv, out)\
    (out) =     (uint8_t)((r) * (conv)[0]) << (fmt).r_shift |\
                (uint8_t)((g) * (conv)[1]) << (fmt).g_shift |\
                (uint8_t)((b) * (conv)[2]) << (fmt).b_shift;

/* Unpack RGB */
#define UNPACK_RGB(r, g, b, fmt, in)\
    (r) =       (in) >> (fmt).r_shift & (fmt).r_mask;\
    (g) =       (in) >> (fmt).g_shift & (fmt).g_mask;\
    (b) =       (in) >> (fmt).b_shift & (fmt).b_mask;

/* Unpack RGB with RGB Conversion Matrix */
#define UNPACK_RGB_CONV(r, g, b, fmt, conv, in)\
    (r) =       ((in) >> (fmt).r_shift & (fmt).r_mask) * (conv)[0];\
    (g) =       ((in) >> (fmt).g_shift & (fmt).g_mask) * (conv)[1];\
    (b) =       ((in) >> (fmt).b_shift & (fmt).b_mask) * (conv)[2];

/* Clamp value macro */
#define CLAMP(in, min, max) {\
    if ((in) > max) {\
        (in) = max;\
    } else if ((in) < min) {\
        (in) = min;\
    }\
}

#ifdef __cplusplus
    }
#endif

/* TVXX_RGB_H */ #endif


/* include/rgb_defines.h */

#ifndef TVXX_RGB_DEFINES_H
#define TVXX_RGB_DEFINES_H

#ifdef __cplusplus
    extern "C" {
#endif

/* Pack RGB */
#define PACK_RGB(r, g, b, fmt, out)\
    (out) =     (r) << (fmt).r_shift |\
                (g) << (fmt).g_shift |\
                (b) << (fmt).b_shift;

/* Pack RGB with RGB Conversion Matrix */
#define PACK_RGB_CONV(r, g, b, fmt, conv, out)\
    (out) =     (uint8_t)((r) * (conv)[0]) << (fmt).r_shift |\
                (uint8_t)((g) * (conv)[1]) << (fmt).g_shift |\
                (uint8_t)((b) * (conv)[2]) << (fmt).b_shift;

/* Unpack RGB */
#define UNPACK_RGB(r, g, b, fmt, in)\
    (r) =       (in) >> (fmt).r_shift & (fmt).r_mask;\
    (g) =       (in) >> (fmt).g_shift & (fmt).g_mask;\
    (b) =       (in) >> (fmt).b_shift & (fmt).b_mask;

/* Unpack RGB with RGB Conversion Matrix */
#define UNPACK_RGB_CONV(r, g, b, fmt, conv, in)\
    (r) =       ((in) >> (fmt).r_shift & (fmt).r_mask) * (conv)[0];\
    (g) =       ((in) >> (fmt).g_shift & (fmt).g_mask) * (conv)[1];\
    (b) =       ((in) >> (fmt).b_shift & (fmt).b_mask) * (conv)[2];

/* Clamp value macro */
#define CLAMP(in, min, max) {\
    if ((in) > max) {\
        (in) = max;\
    } else if ((in) < min) {\
        (in) = min;\
    }\
}

#ifdef __cplusplus
    }
#endif

/* TVXX_RGB_DEFINES_H */ #endif


/* include/tv2x.h */

#ifndef TV2X_H
#define TV2X_H

#include <stdint.h>

#ifdef __cplusplus
    extern "C" {
#endif

#include "tvxx_internal.h"

struct tv2x_kernel {
    float brightness;
    float contrast;
    float scan_brightness;
    float scan_contrast;
    
    uint32_t brcn_table_r[256];
    uint32_t brcn_table_g[256];
    uint32_t brcn_table_b[256];
    
    struct tvxx_rgb_format *in_format;
    struct tvxx_rgb_format *out_format;
};

int tv2x_init_kernel(
            struct tv2x_kernel *kernel,
            float brightness,
            float contrast,
            float scan_brightness,
            float scan_contrast,
            struct tvxx_rgb_format *in_fmt);

void tv2x_process(
            struct tv2x_kernel *k,
            tv2x_in_type * TVXX_RESTRICT in,
            tv2x_out_type * TVXX_RESTRICT out,
            uint32_t in_pitch,
            uint32_t out_pitch,
            uint32_t in_width,
            uint32_t in_height);

#ifdef __cplusplus
    }
#endif

/* TV2X_H */ #endif

/* src/rgb/rgb.c */

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
int rgb_get_conversion_table(
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
* @param    struct rgb_convert *config
* @param    uint32_t *in
* @param    uint32_t *out
* @param    uint32_t size
* @return   void
**/
void rgb_convert(
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


/* src/tv2x/tv2x.c */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <stdint.h>

#ifndef PI
    static const float PI = 3.141592653589793f;
#endif

/*

TODO:
    - rgb_* functions need to be renamed to tvxx_rgb_*... Is rgb_convert() even
      needed in rgb.c? It isn't used outside of the tests.
    - Merge common code between tv4x and tv2x.
    - Tool to package up source/header files into a single source/header file,
      for easy integration into existing projects.

*/

/**
* Allocate memory, and pre-process data for brightness/contrast filter.
*
* @param    float brightness
* @param    float contrast
* @param    float in_range
*
* @return   double *
*               - Heap allocated array for 4 doubles
**/
static double *brcn_get_filter(float brightness, float contrast, float in_range)
{
    double *filter = malloc(sizeof(*filter) * 4);
    
    filter[0] = (double)in_range;
    filter[1] = 1.0 / filter[0];
    filter[2] = tan((PI * (contrast / 100.0 + 1.0) / 4.0));
    if (filter[2] < 0.0) filter[2] = 0.0;
    filter[3] = brightness / 100.0 + ((100.0 - brightness) / 200.0) * (1.0 - filter[2]);
    
    return filter;
}

/**
* Process value for brightness/contrast filter.
*
* @param    double *f       - Filter, double of 4
* @param    uint32_r value  - Value to process
* @return   double
**/
static double brcn_filter_process(double *f, uint32_t value)
{
    double result;
    
    #define RANGE(i)        i[0]
    #define SCALE(i)        i[1]
    #define SLOPE(i)        i[2]
    #define INTERCEPT(i)    i[3]
    
    result = ((SLOPE(f) * SCALE(f)) * value + INTERCEPT(f)) * RANGE(f);
    if (result > RANGE(f)) {
        result = RANGE(f);
    } else if (result < 0.0) {
        result = 0.0;
    }
    
    #undef RANGE
    #undef SCALE
    #undef SLOPE
    #undef INTERCEPT
    
    return result;
}

int tv2x_init_kernel(
            struct tv2x_kernel *kernel,
            float brightness,
            float contrast,
            float scan_brightness,
            float scan_contrast,
            struct tvxx_rgb_format *in_fmt) {
    
    int i;
    double result;
    double  *brcn_filter_red,
            *brcn_filter_green,
            *brcn_filter_blue;
    
    memset(kernel, 0, sizeof(*kernel));
    kernel->brightness = brightness;
    kernel->contrast = contrast;
    kernel->scan_brightness = scan_brightness;
    kernel->scan_contrast = scan_contrast;
    kernel->in_format = in_fmt;
    kernel->out_format = in_fmt;

    /* Generate brightness/contrast lookup tables */
    brcn_filter_red = brcn_get_filter(brightness, contrast, in_fmt->r_mask);
    brcn_filter_green = brcn_get_filter(brightness, contrast, in_fmt->g_mask);
    brcn_filter_blue = brcn_get_filter(brightness, contrast, in_fmt->b_mask);
    
    /* TODO: Controlable Red/Green/Blue levels */
    
    for (i = 0; i <= in_fmt->r_mask; i++) {
        result = brcn_filter_process(brcn_filter_red, i);
        kernel->brcn_table_r[i] = (int)floor(result);
    }
    
    for (i = 0; i <= in_fmt->g_mask; i++) {
        result = brcn_filter_process(brcn_filter_green, i);
        kernel->brcn_table_g[i] = (int)floor(result);
    }
    
    for (i = 0; i <= in_fmt->b_mask; i++) {
        result = brcn_filter_process(brcn_filter_blue, i);
        kernel->brcn_table_b[i] = (int)floor(result);
    }
    
    free(brcn_filter_red);
    free(brcn_filter_green);
    free(brcn_filter_blue);

    return 1;
}

static float rgb_matrix[3][2][3] = {
    {{1.10f, 1.00f, 1.00f}, {1.00f, 1.10f, 1.00f}},
    {{1.00f, 1.00f, 1.10f}, {1.10f, 1.00f, 1.00f}},
    {{1.00f, 1.10f, 1.00f}, {1.00f, 1.00f, 1.10f}},
    
    /*
    {{1.05f, 1.00f, 1.00f}, {1.00f, 1.05f, 1.00f}},
    {{1.00f, 1.00f, 1.05f}, {1.05f, 1.00f, 1.00f}},
    {{1.00f, 1.05f, 1.00f}, {1.00f, 1.00f, 1.05f}},*/
};

/*

RG BR GB

*/

void tv2x_process(
            struct tv2x_kernel *kernel,
            tv2x_in_type * TVXX_RESTRICT in,
            tv2x_out_type * TVXX_RESTRICT out,
            uint32_t in_pitch,
            uint32_t out_pitch,
            uint32_t in_width,
            uint32_t in_height) {
    
    int x, y;
    //int i1, i2;
    uint32_t in_r, in_g, in_b;
    uint32_t out_r, out_g, out_b;
    
    //int out_width, out_height;
    
    tv2x_in_type    *in_ptr;
    tv2x_in_type    *out_ptr, *out_ptr2;
    
    uint32_t linear[2][3];
    uint32_t shift_mask;
    
    //out_width = in_width * 2;
    //out_height = in_height * 2;
    
    /* Bit hack that allows fast "divide by two" on packed RGB values */
    PACK_RGB(1, 1, 1, (*kernel->out_format), shift_mask);
    shift_mask = ~ shift_mask;
    
    #define DIVIDE_TWO(IN) ((IN) >> 1)
    
    #define APPLY_CONTRAST(IN, TABLE)\
        (IN) = (TABLE)[(IN)];
    
    #define CLAMP_OUTPUT()\
        if (out_r > kernel->in_format->r_mask) out_r = kernel->in_format->r_mask;\
        if (out_g > kernel->in_format->g_mask) out_g = kernel->in_format->g_mask;\
        if (out_b > kernel->in_format->b_mask) out_b = kernel->in_format->b_mask;
    
    #if 0
        #define APPLY_OUT_MATRIX(COLUMN)\
            out_r = (float)linear[(COLUMN)][0] * rgb_matrix[(x+(y%2))%3][(COLUMN)][0];\
            out_g = (float)linear[(COLUMN)][1] * rgb_matrix[(x+(y%2))%3][(COLUMN)][1];\
            out_b = (float)linear[(COLUMN)][2] * rgb_matrix[(x+(y%2))%3][(COLUMN)][2];
    #else
        #define APPLY_OUT_MATRIX(COLUMN)\
            out_r = linear[(COLUMN)][0];\
            out_g = linear[(COLUMN)][1];\
            out_b = linear[(COLUMN)][2];
    #endif
    
    for (y = 0; y < in_height; y++) {
        //i1 = (y * in_pitch);
        //i2 = (y * out_pitch * 4);
        
        in_ptr = (tv2x_in_type *) ((uint8_t *) in + y * in_pitch);
        out_ptr = (tv2x_out_type *) ((uint8_t *) out + y * 2 * out_pitch);
        out_ptr2 = (tv2x_out_type *) ((uint8_t *) out + ((y * 2) + 1) * out_pitch);
        
        //in_ptr = &in[i1];
        //out_ptr = &out[i2];
        
        /* Unpack first pixel */
        UNPACK_RGB(in_r, in_g, in_b, (*kernel->in_format), *in_ptr);
        APPLY_CONTRAST(in_r, kernel->brcn_table_r);
        APPLY_CONTRAST(in_g, kernel->brcn_table_g);
        APPLY_CONTRAST(in_b, kernel->brcn_table_b);
        
        for (x = 0; x < in_width-1; x++) {
            linear[0][0] = DIVIDE_TWO(in_r);
            linear[0][1] = DIVIDE_TWO(in_g);
            linear[0][2] = DIVIDE_TWO(in_b);
            
            /* Unpack next pixel */
            UNPACK_RGB(in_r, in_g, in_b, (*kernel->in_format), *(in_ptr+1));
            APPLY_CONTRAST(in_r, kernel->brcn_table_r);
            APPLY_CONTRAST(in_g, kernel->brcn_table_g);
            APPLY_CONTRAST(in_b, kernel->brcn_table_b);
            
            /* Basicall (a+b)/2, where a is the current pixel, and b is the next pixel. */
            linear[0][0] += DIVIDE_TWO(in_r);
            linear[0][1] += DIVIDE_TWO(in_g);
            linear[0][2] += DIVIDE_TWO(in_b);
            
            /* Then get linear of current and next... Since there are only two columns
               to fill, this is just: (a+b)/2 */
            linear[1][0] = DIVIDE_TWO(linear[0][0]+in_r);
            linear[1][1] = DIVIDE_TWO(linear[0][1]+in_g);
            linear[1][2] = DIVIDE_TWO(linear[0][2]+in_b);
        
            /* Run linear through out matrix to get out_r, out_g, out_b */
            APPLY_OUT_MATRIX(0);
            
            /* Clamp */
            CLAMP_OUTPUT();
            
            /* Pack to out_ptr */
            PACK_RGB(out_r, out_g, out_b, (*kernel->out_format), *out_ptr);
            
            //*(out_ptr+out_width) = (*out_ptr & shift_mask) >> 1;
            
            /* Fast "divide by two" for scanline. Uses the value we just packed, with
               some bit hacks. */
            //*(out_ptr+(out_pitch*2)) = (*out_ptr & shift_mask) >> 1;
            *(out_ptr2)++ = (*out_ptr & shift_mask) >> 1;
            
            /* Increment to next column */
            out_ptr++;

            /* Run linear through out matrix to get out_r, out_g, out_b */
            APPLY_OUT_MATRIX(1);
            
            /* Clamp */
            CLAMP_OUTPUT();
            
            /* Pack to out_ptr */
            PACK_RGB(out_r, out_g, out_b, (*kernel->out_format), *out_ptr);
            
            //*(out_ptr+out_width) = (*out_ptr & shift_mask) >> 1;
            
            /* Fast "divide by two" */
            //*(out_ptr+(out_pitch*2)) = (*out_ptr & shift_mask) >> 1;
            *(out_ptr2)++ = (*out_ptr & shift_mask) >> 1;
            
            in_ptr++;
            out_ptr++;
        }
        
        /* Process last two out pixels */
        linear[0][0] = in_r >> 1;
        linear[0][1] = in_g >> 1;
        linear[0][2] = in_b >> 1;
        linear[1][0] = in_r >> 2;
        linear[1][1] = in_g >> 2;
        linear[1][2] = in_b >> 2;
        
        APPLY_OUT_MATRIX(0);
        CLAMP_OUTPUT();
        PACK_RGB(out_r, out_g, out_b, (*kernel->out_format), *out_ptr);
        
        *(out_ptr2)++ = (*out_ptr & shift_mask) >> 1;
        out_ptr++;
        
        APPLY_OUT_MATRIX(1);
        CLAMP_OUTPUT();
        PACK_RGB(out_r, out_g, out_b, (*kernel->out_format), *out_ptr);
            
        /* Fast "divide by two" */
        //*(out_ptr+out_width) = (*out_ptr & shift_mask) >> 1;
        *(out_ptr2)++ = (*out_ptr & shift_mask) >> 1;
    }
}
