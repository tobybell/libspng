#ifndef SPNG_H
#define SPNG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

#define SPNG_VERSION_MAJOR 0
#define SPNG_VERSION_MINOR 2
#define SPNG_VERSION_PATCH 0

#define SPNG_OK 0
#define SPNG_EINVAL 1
#define SPNG_EMEM 2
#define SPNG_EOVERFLOW 3
#define SPNG_ESIGNATURE 4
#define SPNG_EWIDTH 5
#define SPNG_EHEIGHT 6
#define SPNG_EUSER_WIDTH 7
#define SPNG_EUSER_HEIGHT 8
#define SPNG_EBIT_DEPTH 9
#define SPNG_ECOLOUR_TYPE 10
#define SPNG_ECOMPRESSION_METHOD 11
#define SPNG_EFILTER_METHOD 12
#define SPNG_EINTERLACE_METHOD 13
#define SPNG_EIHDR_SIZE 14
#define SPNG_ENOIHDR 15
#define SPNG_ECHUNK_POS 50
#define SPNG_ECHUNK_SIZE 51
#define SPNG_ECHUNK_CRC 52
#define SPNG_ECHUNK_TYPE 53
#define SPNG_ECHUNK_UNKNOWN_CRITICAL 54
#define SPNG_EDUP_PLTE 55
#define SPNG_EDUP_CHRM 56
#define SPNG_EDUP_GAMA 57
#define SPNG_EDUP_ICCP 58
#define SPNG_EDUP_SBIT 59
#define SPNG_EDUP_SRGB 60
#define SPNG_EDUP_BKGD 61
#define SPNG_EDUP_HIST 62
#define SPNG_EDUP_TRNS 63
#define SPNG_EDUP_PHYS 64
#define SPNG_EDUP_TIME 65
#define SPNG_EDUP_OFFS 150
#define SPNG_EDUP_EXIF 800
#define SPNG_EEXIF 801
#define SPNG_EOFFS 802
#define SPNG_ESRGB 803
#define SPNG_ESBIT 66
#define SPNG_EPHYS 67
#define SPNG_ETIME 68
#define SPNG_ECHRM 300
#define SPNG_EGAMA 301
#define SPNG_ESPLT_NAME 303
#define SPNG_ESPLT_DUP_NAME 303
#define SPNG_ESPLT_DEPTH 304
#define SPNG_EICCP_NAME 320
#define SPNG_EICCP_COMPRESSION_METHOD 321
#define SPNG_EPLTE_IDX 69
#define SPNG_ETRNS_COLOUR_TYPE 70
#define SPNG_ETRNS_NO_PLTE 71
#define SPNG_EIDAT_TOO_SHORT 80
#define SPNG_EIDAT_STREAM 83
#define SPNG_EZLIB 84
#define SPNG_EFILTER 85
#define SPNG_EBKGD_NO_PLTE 100
#define SPNG_EBKGD_PLTE_IDX 101
#define SPNG_EHIST_NO_PLTE 102
#define SPNG_EBUFSIZ 120
#define SPNG_EIO 130
#define SPNG_EOF 131
#define SPNG_EBUF_SET 140
#define SPNG_EBADSTATE 141
#define SPNG_EFMT 142
#define SPNG_EFLAGS 143
#define SPNG_ECHUNKAVAIL 144
#define SPNG_ETEXT 310
#define SPNG_ETEXT_KEYWORD 311
#define SPNG_EZTXT 312
#define SPNG_EZTXT_COMPRESSION_METHOD 313
#define SPNG_EITXT 314
#define SPNG_EITXT_COMPRESSION_FLAG 315
#define SPNG_EITXT_COMPRESSION_METHOD 316
#define SPNG_EITXT_LANG_TAG 317
#define SPNG_EITXT_TRANSLATED_KEY 318
#define SPNG_EINCOMPLETE 900

#define SPNG_TEXT 1
#define SPNG_ZTXT 2
#define SPNG_ITXT 3

#define SPNG_COLOUR_TYPE_GRAYSCALE 0
#define SPNG_COLOUR_TYPE_TRUECOLOR 2
#define SPNG_COLOUR_TYPE_INDEXED 3
#define SPNG_COLOUR_TYPE_GRAYSCALE_ALPHA 4
#define SPNG_COLOUR_TYPE_TRUECOLOR_ALPHA 6

#define SPNG_IO_EOF -1
#define SPNG_IO_ERROR -2

#define SPNG_FMT_RGBA8 1
#define SPNG_FMT_RGBA16 2

#define SPNG_DECODE_USE_TRNS 1
#define SPNG_DECODE_USE_GAMA 2
#define SPNG_DECODE_USE_SBIT 8 /* Rescale samples using sBIT values */

struct spng_ihdr
{
    uint32_t width;
    uint32_t height;
    uint8_t bit_depth;
    uint8_t colour_type;
    uint8_t compression_method;
    uint8_t filter_method;
    uint8_t interlace_method;
};

struct spng_plte_entry
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct spng_plte
{
    uint32_t n_entries;
    struct spng_plte_entry entries[256];
};

struct spng_trns_type2
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
};

struct spng_trns
{
    uint32_t n_type3_entries;
    union
    {
        uint16_t type0_grey_sample;
        struct spng_trns_type2 type2;
        uint8_t type3_alpha[256];
    };
};

struct spng_chrm
{
    uint32_t white_point_x;
    uint32_t white_point_y;
    uint32_t red_x;
    uint32_t red_y;
    uint32_t green_x;
    uint32_t green_y;
    uint32_t blue_x;
    uint32_t blue_y;
};

struct spng_iccp
{
    char profile_name[80];
    size_t profile_len;
    char *profile;
};

struct spng_sbit
{
    uint8_t greyscale_bits;
    uint8_t red_bits;
    uint8_t green_bits;
    uint8_t blue_bits;
    uint8_t alpha_bits;
};

struct spng_text
{
    char keyword[80];
    int type;

    size_t length;
    char *text;

    uint8_t compression_flag; /* iTXt only */
    uint8_t compression_method; /* iTXt, ztXt only */
    char *language_tag; /* iTXt only */
    char *translated_keyword; /* iTXt only */
};

struct spng_bkgd_type2_6
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
};

struct spng_bkgd
{
    union
    {
        uint16_t type0_4_greyscale;
        struct spng_bkgd_type2_6 type2_6;
        uint8_t type3_plte_index;
    };
};

struct spng_hist
{
    uint16_t frequency[256];
};

struct spng_phys
{
    uint32_t ppu_x, ppu_y;
    uint8_t unit_specifier;
};

struct spng_splt_entry
{
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t alpha;
    uint16_t frequency;
};

struct spng_splt
{
    char name[80];
    uint8_t sample_depth;
    uint32_t n_entries;
    struct spng_splt_entry *entries;
};

struct spng_time
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

struct spng_offs
{
    int32_t x, y;
    uint8_t unit_specifier;
};

struct spng_exif
{
    size_t length;
    char *data;
};

struct spng_chunk
{
    size_t offset;
    uint32_t length;
    uint8_t type[4];
    uint32_t crc;
};

struct spng_ctx;

/* A read callback function should copy "n" bytes to *data and return 0 or
   SPNG_IO_EOF/SPNG_IO_ERROR on error. */
typedef int spng_read_fn(struct spng_ctx *ctx, void *user, void *data, size_t n);


struct spng_ctx
{
    size_t data_size;
    unsigned char *data;

    spng_read_fn *read_fn;
    void *read_user_ptr;

    unsigned valid_state: 1;
    unsigned streaming: 1;

    unsigned have_ihdr: 1;
    unsigned have_plte: 1;
    unsigned have_chrm: 1;
    unsigned have_iccp: 1;
    unsigned user_iccp: 1;
    unsigned have_gama: 1;
    unsigned have_sbit: 1;
    unsigned have_srgb: 1;
    unsigned have_text: 1;
    unsigned user_text: 1;
    unsigned have_bkgd: 1;
    unsigned have_hist: 1;
    unsigned have_trns: 1;
    unsigned have_phys: 1;
    unsigned have_splt: 1;
    unsigned user_splt: 1;
    unsigned have_time: 1;
    unsigned file_time: 1;
    unsigned have_offs: 1;
    unsigned have_exif: 1;
    unsigned file_exif: 1;
    unsigned user_exif: 1;

    unsigned have_first_idat: 1;
    unsigned have_last_idat: 1;

    struct spng_chunk first_idat, last_idat;

    uint32_t max_width, max_height;
    struct spng_ihdr ihdr;

    size_t plte_offset;
    struct spng_plte plte;

    struct spng_chrm chrm;
    struct spng_iccp iccp;

    uint32_t gama;
    uint32_t lut_entries;
    uint16_t *gamma_lut;

    struct spng_sbit sbit;

    uint8_t srgb_rendering_intent;

    uint32_t n_text;
    struct spng_text *text_list;

    struct spng_bkgd bkgd;
    struct spng_hist hist;
    struct spng_trns trns;
    struct spng_phys phys;

    uint32_t n_splt;
    struct spng_splt *splt_list;

    struct spng_time time;
    struct spng_offs offs;
    struct spng_exif exif;
};


struct spng_ctx *spng_ctx_new(void);
void spng_ctx_free(struct spng_ctx *ctx);

int spng_set_png_buffer(struct spng_ctx *ctx, void *buf, size_t size);
int spng_set_png_stream(struct spng_ctx *ctx, spng_read_fn *read_fn, void *user);

int spng_set_image_limits(struct spng_ctx *ctx, uint32_t width, uint32_t height);
int spng_get_image_limits(struct spng_ctx *ctx, uint32_t *width, uint32_t *height);

int spng_decoded_image_size(struct spng_ctx *ctx, int fmt, size_t *out);

int spng_decode_image(struct spng_ctx *ctx, void *out, size_t out_size, int fmt, int flags);

int spng_get_ihdr(struct spng_ctx *ctx, struct spng_ihdr *ihdr);
int spng_get_plte(struct spng_ctx *ctx, struct spng_plte *plte);
int spng_get_trns(struct spng_ctx *ctx, struct spng_trns *trns);
int spng_get_chrm(struct spng_ctx *ctx, struct spng_chrm *chrm);
int spng_get_gama(struct spng_ctx *ctx, double *gamma);
int spng_get_iccp(struct spng_ctx *ctx, struct spng_iccp *iccp);
int spng_get_sbit(struct spng_ctx *ctx, struct spng_sbit *sbit);
int spng_get_srgb(struct spng_ctx *ctx, uint8_t *rendering_intent);
int spng_get_text(struct spng_ctx *ctx, struct spng_text *text, uint32_t *n_text);
int spng_get_bkgd(struct spng_ctx *ctx, struct spng_bkgd *bkgd);
int spng_get_hist(struct spng_ctx *ctx, struct spng_hist *hist);
int spng_get_phys(struct spng_ctx *ctx, struct spng_phys *phys);
int spng_get_splt(struct spng_ctx *ctx, struct spng_splt *splt, uint32_t *n_splt);
int spng_get_time(struct spng_ctx *ctx, struct spng_time *time);

int spng_get_offs(struct spng_ctx *ctx, struct spng_offs *offs);
int spng_get_exif(struct spng_ctx *ctx, struct spng_exif *exif);


int spng_set_ihdr(struct spng_ctx *ctx, struct spng_ihdr *ihdr);
int spng_set_plte(struct spng_ctx *ctx, struct spng_plte *plte);
int spng_set_trns(struct spng_ctx *ctx, struct spng_trns *trns);
int spng_set_chrm(struct spng_ctx *ctx, struct spng_chrm *chrm);
int spng_set_gama(struct spng_ctx *ctx, double gamma);
int spng_set_iccp(struct spng_ctx *ctx, struct spng_iccp *iccp);
int spng_set_sbit(struct spng_ctx *ctx, struct spng_sbit *sbit);
int spng_set_srgb(struct spng_ctx *ctx, uint8_t rendering_intent);
int spng_set_text(struct spng_ctx *ctx, struct spng_text *text, uint32_t n_text);
int spng_set_bkgd(struct spng_ctx *ctx, struct spng_bkgd *bkgd);
int spng_set_hist(struct spng_ctx *ctx, struct spng_hist *hist);
int spng_set_phys(struct spng_ctx *ctx, struct spng_phys *phys);
int spng_set_splt(struct spng_ctx *ctx, struct spng_splt *splt, uint32_t n_splt);
int spng_set_time(struct spng_ctx *ctx, struct spng_time *time);

int spng_set_offs(struct spng_ctx *ctx, struct spng_offs *offs);
int spng_set_exif(struct spng_ctx *ctx, struct spng_exif *exif);

#ifdef __cplusplus
}
#endif

#endif /* SPNG_H */
