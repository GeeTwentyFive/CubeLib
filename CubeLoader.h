#ifndef _CUBE_LOADER_H
#define _CUBE_LOADER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef _CUBE_TYPES
#define _CUBE_TYPES

typedef struct {
        float position[3];
        float size[3];
        uint8_t color_RGB[3];
} Cube_Cube;

#endif // _CUBE_TYPES


// Returns NULL on failure
Cube_Cube* Cube_Load(const char* IN_path, uint32_t* OUT_num_cubes) {
        FILE* file = fopen(IN_path, "rb");
        if (!file) return NULL;

        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        char* file_data = (char*)malloc(file_size);
        if (!file_data) {
                fclose(file);
                return NULL;
        }
        if (fread(file_data, 1, file_size, file) != file_size) {
                fclose(file);
                free(file_data);
                return NULL;
        }

        fclose(file);


        char* file_data_offset = file_data;


        uint32_t num_cubes = *((uint32_t*) file_data_offset);
        file_data_offset += sizeof(uint32_t);
        Cube_Cube* cubes = (Cube_Cube*) malloc(sizeof(Cube_Cube) * num_cubes);
        if (!cubes) {
                free(file_data);
                return NULL;
        }

        for (uint32_t i = 0; i < num_cubes; i++) {
                cubes[i] = (Cube_Cube) {
                        .position = {
                                *((float*) (file_data_offset + sizeof(float)*0)),
                                *((float*) (file_data_offset + sizeof(float)*1)),
                                *((float*) (file_data_offset + sizeof(float)*2))
                        },
                        .size = {
                                *((float*) (file_data_offset + sizeof(float)*3)),
                                *((float*) (file_data_offset + sizeof(float)*4)),
                                *((float*) (file_data_offset + sizeof(float)*5))
                        },
                        .color_RGB = {
                                *((uint8_t*) (file_data_offset + sizeof(float)*6 + sizeof(uint8_t)*0)),
                                *((uint8_t*) (file_data_offset + sizeof(float)*6 + sizeof(uint8_t)*1)),
                                *((uint8_t*) (file_data_offset + sizeof(float)*6 + sizeof(uint8_t)*2))
                        }
                };

                file_data_offset += 6*sizeof(float) + 3*sizeof(uint8_t);
        }

        free(file_data);

        *OUT_num_cubes = num_cubes;
        return cubes;
}

#endif // _CUBE_LOADER_H