#ifndef _CUBE_WRITER_H
#define _CUBE_WRITER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef _CUBE_TYPES
#define _CUBE_TYPES

typedef struct {
        float position[3];
        float rotation[3];
        float size[3];
        uint8_t color_RGB[3];
} Cube_Cube;

#endif // _CUBE_TYPES


// Returns 1 on success, 0 on error
int Cube_Write(Cube_Cube* IN_cubes, uint32_t IN_num_cubes, const char* IN_out_path) {
        size_t out_data_size = (
                4 +
                (9*sizeof(float) + 3*sizeof(uint8_t)) * IN_num_cubes
        );
        char* out_buf = (char*) malloc(out_data_size);
        if (!out_buf) return 0;


        char* out_buf_front = out_buf;

        *((uint32_t*) out_buf_front) = IN_num_cubes;
        out_buf_front += sizeof(uint32_t);

        for (uint32_t i = 0; i < IN_num_cubes; i++) {
                *((float*) out_buf_front) = IN_cubes[i].position[0];
                out_buf_front += sizeof(float);
                *((float*) out_buf_front) = IN_cubes[i].position[1];
                out_buf_front += sizeof(float);
                *((float*) out_buf_front) = IN_cubes[i].position[2];
                out_buf_front += sizeof(float);

                *((float*) out_buf_front) = IN_cubes[i].rotation[0];
                out_buf_front += sizeof(float);
                *((float*) out_buf_front) = IN_cubes[i].rotation[1];
                out_buf_front += sizeof(float);
                *((float*) out_buf_front) = IN_cubes[i].rotation[2];
                out_buf_front += sizeof(float);

                *((float*) out_buf_front) = IN_cubes[i].size[0];
                out_buf_front += sizeof(float);
                *((float*) out_buf_front) = IN_cubes[i].size[1];
                out_buf_front += sizeof(float);
                *((float*) out_buf_front) = IN_cubes[i].size[2];
                out_buf_front += sizeof(float);

                *((uint8_t*) out_buf_front) = IN_cubes[i].color_RGB[0];
                out_buf_front += sizeof(uint8_t);
                *((uint8_t*) out_buf_front) = IN_cubes[i].color_RGB[1];
                out_buf_front += sizeof(uint8_t);
                *((uint8_t*) out_buf_front) = IN_cubes[i].color_RGB[2];
                out_buf_front += sizeof(uint8_t);
        }


        FILE* out_file = fopen(IN_out_path, "wb");
        if (!out_file) {
                free(out_buf);
                return 0;
        }
        if (fwrite(out_buf, 1, out_data_size, out_file) != out_data_size) {
                free(out_buf);
                fclose(out_file);
                return 0;
        }
        fclose(out_file);


        free(out_buf);

        return 1;
}

#endif // _CUBE_WRITER_H