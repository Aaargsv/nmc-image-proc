#ifndef PPM_CONTROL_GUARD
#define PPM_CONTROL_GUARD

struct ppm_header {
	char format[3];
	int width;
	int height;
	int depth;
	int start_raw;
};

enum errors {ERR_FORMAT, ERR_COMMENT, ERR_WIDTH, 
			 ERR_HEIGHT, ERR_DEPTH};

typedef union {
    struct {
      unsigned char red;
      unsigned char green;
      unsigned char blue;
    };
    
    unsigned char grey;
} pixel_t;

typedef struct ppm_header ppm_header_t;

extern int ppm_read_header(void *data_ptr, ppm_header_t *header_info);
extern int ppm_save_header(void *data_ptr, ppm_header_t *header_info, const char *comment);
					

#endif